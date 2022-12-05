using LibDotNetParser.PE;

namespace LibDotNetParser.DotNet.Tabels.Defs;

public class MethodSpec : IMetadataTableRow
{
    public ushort Method { get; set; }
    public ushort Instantiation { get; set; }
    public void Read(MetadataReader reader)
    {
        Method = reader.ReadUInt16();
        Instantiation = reader.ReadUInt16();
    }
}