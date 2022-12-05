namespace LibDotNetParser.CILApi.IL;

public class FieldInfo
{
    public string Name { get; set; }
    public int IndexInTabel { get; set; }
    public bool IsInFieldTabel { get; set; }
    public string Namespace { get; internal set; }
    public string Class { get; internal set; }
}