using LibDotNetParser.PE;

namespace LibDotNetParser.DotNet.Tabels.Defs;

public class ExportedType : IMetadataTableRow
{
    public uint Flags { get; set; }
    public uint TypeDefId { get; set; }
    public uint TypeName { get; set; }
    public uint TypeNamespace { get; set; }
    public void Read(MetadataReader reader)
    {
        Flags = reader.ReadUInt32();
        TypeDefId = reader.ReadUInt32();
        TypeName = reader.ReadStringStreamIndex();
        TypeNamespace = reader.ReadStringStreamIndex();
    }
}