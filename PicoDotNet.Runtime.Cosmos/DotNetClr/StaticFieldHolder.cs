using LibDotNetParser;
using LibDotNetParser.CILApi;
using System.Collections.Generic;

namespace libDotNetClr;

internal class StaticFieldHolder
{
    public static List<StaticField> staticFields = new();
}
internal class StaticField
{
    public MethodArgStack value;
    public DotNetField theField;
    public override string ToString()
    {
        return "Field: " + theField.ToString() + ", Value: " + theField.ToString();
    }
}