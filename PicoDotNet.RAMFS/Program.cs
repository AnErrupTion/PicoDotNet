﻿using PicoDotNet.Builder.Library;

namespace PicoDotNet.RAMFS;

public static class Program
{
    public static RAMFileSystem RAMFS = new();

    private static void Main(string[] args)
    {
        Debug.Log("PicoDotNet RAMFS Utility\n");
        RegisterCommands();
        
        if (args.Length == 0) { Debug.Error("No input file specified."); }
        else
        {
            if (!File.Exists(args[0])) { Debug.Error("Unable to locate command file at '%s'", args[0]); }
            var lines = File.ReadAllLines(args[0]);
            foreach (var line in lines) { CommandParser.Execute(line); }
        }
        Environment.Exit(0);
    }

    private static void RegisterCommands()
    {
        CommandParser.Register(CommandDeclarations.NEW);
        CommandParser.Register(CommandDeclarations.SAVE);
        CommandParser.Register(CommandDeclarations.LOAD);
        CommandParser.Register(CommandDeclarations.ADD);
        CommandParser.Register(CommandDeclarations.ADDN);
        CommandParser.Register(CommandDeclarations.LIST);
    }
}