using System.Text;
using PicoDotNet.Builder.Library;

namespace PicoDotNet.RAMFS;

public struct RAMFile
{
    public const int EntrySz       = 73;
    public const int MaxNameLength = 64;

    public char[] Name;
    public bool   Hidden;
    public uint   Offset;
    public uint   Size;

    public RAMFile(string name, bool hidden, uint offset, uint size)
    {
        Name   = new char[MaxNameLength];
        Hidden = hidden;
        Offset = offset;
        Size   = size;
        SetName(name);
    }

    public void Read(byte[] data, int offset)
    {
        var reader = new BinaryReader(new MemoryStream(data, offset, EntrySz, false), Encoding.ASCII);
        Name                = reader.ReadChars(64);
        Hidden              = reader.ReadBoolean();
        Offset              = reader.ReadUInt32();
        Size                = reader.ReadUInt32();
    }

    public byte[] Write()
    {
        var data = new byte[EntrySz];
        var writer = new BinaryWriter(new MemoryStream(data), Encoding.ASCII);
        writer.Write(Name, 0, MaxNameLength);
        writer.Write(Hidden);
        writer.Write(Offset);
        writer.Write(Size);
        return data;
    }

    public void SetName(string name)
    {
        if (name.Length >= MaxNameLength) { Debug.Error("File name excceeds 80 characters - '%s'\n", name); }
        Array.Fill(Name, (char)0);
        Array.Copy(name.ToCharArray(), Name, name.Length);
    }

    public string GetName() 
    { 
        var name = String.Empty;
        var i = 0;
        while (Name[i] != 0) { name += Name[i++]; }
        return name;
    }
}

public struct RAMFSHeader
{
    public uint TableOffset;
    public uint TableSize;
    public uint DataOffset;
    public uint DataSize;
    public uint DataPosition;
    public uint Count;
    public uint CountMax;

    public RAMFSHeader(uint taddr, uint tsz, uint daddr, uint dsz, uint dp, uint c, uint max)
    {
        TableOffset    = taddr;
        TableSize      = tsz;
        DataOffset     = daddr;
        DataSize       = dsz;
        DataPosition   = dp;
        Count          = c;
        CountMax       = max;
    }

    public void Read(byte[] data, int offset)
    {
        var reader = new BinaryReader(new MemoryStream(data, offset, 28, false), Encoding.ASCII);
        TableOffset         = reader.ReadUInt32();
        TableSize           = reader.ReadUInt32();
        DataOffset          = reader.ReadUInt32();
        DataSize            = reader.ReadUInt32();
        DataPosition        = reader.ReadUInt32();
        Count               = reader.ReadUInt32();
        CountMax            = reader.ReadUInt32();
    }

    public byte[] Write()
    {
        var data = new byte[28];
        var writer = new BinaryWriter(new MemoryStream(data), Encoding.ASCII);
        writer.Write(TableOffset);
        writer.Write(TableSize);
        writer.Write(DataOffset);
        writer.Write(DataSize);
        writer.Write(DataPosition);
        writer.Write(Count);
        writer.Write(CountMax);
        return data;
    }
}

public class RAMFileSystem
{
    public readonly byte[] Data;
    public RAMFSHeader     Header;

    public RAMFileSystem()
    {
        Data = new byte[1];
        Header = new RAMFSHeader();
    }

    public RAMFileSystem(byte[] data)
    {
        Data = new byte[data.Length];
        Array.Copy(Data, data, data.Length);
        Header = new RAMFSHeader();
        Header.Read(Data, 0);
        Debug.Log("Initialized RAMFS\n");
    }

    public RAMFileSystem(uint max_files, uint sz)
    {
        Data = new byte[max_files * RAMFile.EntrySz + sz];
        Header = new RAMFSHeader(28, max_files * RAMFile.EntrySz, 28 + max_files * RAMFile.EntrySz, sz, 0, 0, max_files);
        Array.Copy(Header.Write(), 0, Data, 0, 28);
        Debug.Log("Created RAMFS - Max:%u Size:%u bytes\n", max_files, sz);
    }

    public RAMFile AddFile(string name, byte[] data, bool hidden = false)
    {
        if (data == null || data.Length == 0) { Debug.Log("Attempt to create blank file"); return new RAMFile(); }

        var i = GetNextIndex();
        if (i == -1) { Debug.Error("Maximum amount of files reached"); return new RAMFile(); }

        var file = new RAMFile(name, hidden, Header.DataPosition, (uint)data.Length);
        Array.Copy(file.Write(), 0, Data, Header.TableOffset + i * RAMFile.EntrySz, RAMFile.EntrySz);
        Array.Copy(data, 0, Data, Header.DataOffset + Header.DataPosition, data.Length);
        Header.DataPosition += (uint)data.Length;
        Array.Copy(Header.Write(), 0, Data, 0, 28);
        Debug.Log("Added file - Name:%s Hidden:%d Size:%d bytes\n", name, hidden ? 1 : 0, data.Length);
        return GetFile(i);
    }

    private RAMFile GetFile(int index, bool rd_hdr = true)
    {
        if (rd_hdr) { Header.Read(Data, 0); }
        var file = new RAMFile();
        file.Read(Data, (int)(Header.TableOffset + index * RAMFile.EntrySz));
        return file;
    }

    public RAMFile GetFile(string name, bool rd_hdr = true)
    {
        if (rd_hdr) { Header.Read(Data, 0); }
        for (var i = 0; i < Header.CountMax; i++)
        {
            var file = GetFile(i, false);
            if (new string(file.Name) == name) { return file; }
        }
        return new RAMFile();
    }

    public byte[] GetFileData(RAMFile file)
    {
        var data = new byte[file.Size];
        Array.Copy(Data, Header.DataOffset + file.Offset, data, 0, file.Size);
        return data;
    }

    public List<RAMFile> GetFiles()
    {
        var files = new List<RAMFile>();
        Header.Read(Data, 0);
        for (var i = 0; i < Header.CountMax; i++)
        {
            var file = GetFile(i, false);
            if (file.Name[0] == 0) { continue; }
            files.Add(file);
        }
        return files;
    }

    private int GetNextIndex()
    {
        Header.Read(Data, 0);
        for (var i = 0; i < Header.CountMax; i++)
        {
            var file = GetFile(i, false);
            if (file.Name[0] == 0) { return i; }
        }
        return -1;
    }
}
