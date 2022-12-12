using System;
using System.IO;
using System.Collections.Generic;
using System.Text;
using System.Linq;
using System.Threading;
using PicoDotNet.Builder.Library;

namespace PicoDotNet.RAMFS;

public class CommandDeclarations
{
    public static Command NEW   { get; private set; } = new("NEW",  CommandHandlers.NEW);
    public static Command SAVE  { get; private set; } = new("SAVE", CommandHandlers.SAVE);
    public static Command LOAD  { get; private set; } = new("LOAD", CommandHandlers.LOAD);
    public static Command ADD   { get; private set; } = new("ADD", CommandHandlers.ADD);
    public static Command ADDN  { get; private set; } = new("ADDN", CommandHandlers.ADDN);
    public static Command LIST  { get; private set; } = new("LIST", CommandHandlers.LIST);

    public static List<Command> List = new()
    {
        NEW, SAVE, LOAD, ADD, ADDN, LIST,
    };
}

public static class CommandHandlers
{
    public static void NEW(string input, List<string> args)
    {
        if (args.Count == 1) { Debug.Error("Expected size of image"); }
        if (args.Count == 2) { Debug.Error("Expected maximum amount of files"); }

        int max_ents, sz;
        if (!int.TryParse(args[1], out max_ents)) { Debug.Error("Invalid value for max entries - '%s'", args[1]); }
        if (!int.TryParse(args[2], out sz))       { Debug.Error("Invalid value for size - '%s'", args[2]); }

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
        Debug.Log("Saved image file to '%s'\n", fname);
    }

    public static void ADD(string input, List<string> args)
    {
        if (args.Count == 1) { Debug.Error("Expected hidden flag for new file"); }
        if (args.Count == 2) { Debug.Error("Expected name for new file"); }
        if (args.Count == 3) { Debug.Error("Expected source path for new file"); }
        if (args[1] != "1" && args[1] != "0") { Debug.Error("Invalid value for hidden flag - '%s'", args[1]); }

        if (!File.Exists(args[3])) { Debug.Error("Unable to locate source file '%s'", args[3]); }
        var data = File.ReadAllBytes(args[3]);
        Program.RAMFS.AddFile(args[2], data, (args[1] == "1"));
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