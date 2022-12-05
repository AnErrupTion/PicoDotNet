using LibDotNetParser.PE;

namespace LibDotNetParser.DotNet.Tabels.Defs;

public class EventMap : IMetadataTableRow
{
    public uint Parrent { get; private set; }
    public uint EventList { get; private set; }
    public void Read(MetadataReader reader)
    {
        Parrent = reader.ReadUInt16();
        EventList = reader.ReadUInt16();
    }
}