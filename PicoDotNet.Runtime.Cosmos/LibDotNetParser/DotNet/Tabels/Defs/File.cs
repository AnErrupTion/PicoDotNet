using LibDotNetParser.PE;

namespace LibDotNetParser.DotNet.Tabels.Defs;

public class File : IMetadataTableRow
{
    public uint Flags { get; set; }
    public uint Name { get; set; }
    public uint HashValue { get; set; }
    public void Read(MetadataReader reader)
    {
        Flags = reader.ReadUInt32();
        Name = reader.ReadStringStreamIndex();
        HashValue = reader.ReadBlobStreamIndex();
    }
}