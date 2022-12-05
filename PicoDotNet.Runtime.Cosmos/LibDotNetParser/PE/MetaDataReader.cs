using System;
using System.IO;

namespace LibDotNetParser.PE;

public class MetadataReader : BinaryReader
{
    public StreamOffsetSizeFlags StreamOffsetSizeFlags { get; set; }
    public HeapSizes HeapSizes { get; }
    public MetadataReader(Stream input, HeapSizes s) : base(input)
    {
        HeapSizes = s;
    }
    public uint ReadSize(uint size)
    {
        return size switch
        {
            1 => ReadByte(),
            2 => ReadUInt16(),
            4 => ReadUInt32(),
            _ => throw new NotImplementedException("Unsupported size: " + size)
        };
    }
    public uint ReadStringStreamIndex()
    {
        return ReadSize(HeapSizes.String);
    }

    public uint ReadGuidStreamIndex()
    {
        return ReadSize(HeapSizes.Guid);
    }

    public uint ReadBlobStreamIndex()
    {
        return ReadSize(HeapSizes.Blob);
    }
}