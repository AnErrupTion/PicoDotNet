namespace PicoDotNet.Builder.Library;

public class Command
{
    public string Name  { get; }
    public Action<string, List<string>> Handler { get; }

    public Command(string name, Action<string, List<string>> handler)
    {
        Name    = name;
        Handler = handler;
    }
}