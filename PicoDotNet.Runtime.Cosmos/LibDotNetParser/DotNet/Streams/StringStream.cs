using System.IO;

namespace LibDotNetParser.DotNet.Streams;

public class StringsStream
{
    private BinaryReader r;
    public StringsStream(byte[] data)
    {
        r = new BinaryReader(new MemoryStream(data));
    }

    public string GetByOffset(uint offset)
    {
        r.BaseStream.Seek(offset, SeekOrigin.Begin);
        return r.ReadNullTermString();
    }
}