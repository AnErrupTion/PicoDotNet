using PicoDotNet.Builder.Library;

namespace PicoDotNet.RAMFS;

public class CommandDeclarations
{
    public static Command NEW   { get; } = new("NEW",  CommandHandlers.NEW);
    public static Command SAVE  { get; } = new("SAVE", CommandHandlers.SAVE);
    public static Command LOAD  { get; } = new("LOAD", CommandHandlers.LOAD);
    public static Command ADD   { get; } = new("ADD", CommandHandlers.ADD);
    public static Command ADDN  { get; } = new("ADDN", CommandHandlers.ADDN);
    public static Command LIST  { get; } = new("LIST", CommandHandlers.LIST);

    public static List<Command> List = new()
    {
        NEW, SAVE, LOAD, ADD, ADDN, LIST
    };
}

public static class CommandHandlers
{
    public static void NEW(string input, List<string> args)
    {
        switch (args.Count)
        {
            case 1:
                Debug.Error("Expected size of image");
                break;
            case 2:
                Debug.Error("Expected maximum amount of files");
                break;
        }

        if (!int.TryParse(args[1], out var max_ents)) { Debug.Error("Invalid value for max entries - '%s'", args[1]); }
        if (!int.TryParse(args[2], out var sz))       { Debug.Error("Invalid value for size - '%s'", args[2]); }

        Program.RAMFS = new RAMFileSystem((uint)max_ents, (uint)sz);
    }

    public static void SAVE(string input, List<string> args)
    {
        if (args.Count < 2) { Debug.Error("Expected filename"); }

        var fname = input[5..];
        File.WriteAllBytes(fname, Program.RAMFS.Data);
        Debug.Log("Saved image file to '%s'\n", fname);
    }

    public static void LOAD(string input, List<string> args)
    {
        var fname = input[5..];
        if (!File.Exists(fname)) { Debug.Error("Unable to locate image file at '%s'", fname); }
        Program.RAMFS = new RAMFileSystem(File.ReadAllBytes(fname));
        Debug.Log("Loaded image file from '%s'\n", fname);
    }

    public static void ADD(string input, List<string> args)
    {
        switch (args.Count)
        {
            case 1:
                Debug.Error("Expected hidden flag for new file");
                break;
            case 2:
                Debug.Error("Expected name for new file");
                break;
            case 3:
                Debug.Error("Expected source path for new file");
                break;
        }

        if (args[1] != "1" && args[1] != "0") { Debug.Error("Invalid value for hidden flag - '%s'", args[1]); }

        if (!File.Exists(args[3])) { Debug.Error("Unable to locate source file '%s'", args[3]); }
        var data = File.ReadAllBytes(args[3]);
        Program.RAMFS.AddFile(args[2], data, args[1] == "1");
    }

    public static void ADDN(string input, List<string> args)
    {
        if (args.Count == 1) { Debug.Error("Expected directory to import"); }

        var dir = input[5..].Replace("\\", "/");
        if (!Directory.Exists(dir)) { Debug.Error("Unable to locate source directory '%s'", dir); }
        if (!dir.EndsWith("/")) { dir += "/"; }

        var files = Directory.GetFiles(dir);
        foreach (var file in files) { CommandParser.Execute("ADD 0 " + Path.GetFileName(file) + " " + file); }        
    }

    public static void LIST(string input, List<string> args)
    {
        var files = Program.RAMFS.GetFiles();

        Debug.Log("NAME                    HIDDEN  SIZE\n");
        foreach (var file in files)
        {
            Debug.Log(file.GetName().PadRight(24, ' '));
            Debug.Log((file.Hidden ? "1" : "0") + "       ");
            Debug.Log(file.Size + " bytes\n");
        }
    }
}