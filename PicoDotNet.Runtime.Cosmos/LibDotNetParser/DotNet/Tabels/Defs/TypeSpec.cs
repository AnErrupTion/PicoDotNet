using LibDotNetParser.PE;

namespace LibDotNetParser.DotNet.Tabels.Defs;

public class TypeSpec : IMetadataTableRow
{
    public uint Signature { get; private set; }
    public void Read(MetadataReader reader)
    {
        Signature = reader.ReadBlobStreamIndex();
    }
}