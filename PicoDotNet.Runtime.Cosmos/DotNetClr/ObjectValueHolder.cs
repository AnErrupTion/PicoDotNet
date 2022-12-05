using LibDotNetParser;
using System.Collections.Generic;

namespace libDotNetClr;

internal class ObjectValueHolder
{
    public Dictionary<string, MethodArgStack> Fields = new();
    public ObjectValueHolder()
    {
    }
}