using System;
using System.IO;
using System.Text;
using System.Collections.Generic;

namespace PicoDotNet.RAMFS;

public static class Program
{
    public static RAMFileSystem RAMFS = new RAMFileSystem();

    private static void Main(string[] args)
    {
        Debug.Log("PicoDotNet RAMFS Utility\n");
        if (args.Length == 0) { Debug.Error("No input file specified."); }
        else
        {
            if (!File.Exists(args[0])) { Debug.Error("Unable to locate command file at '%s'", args[0]); }
            string[] lines = File.ReadAllLines(args[0]);
            foreach (string line in lines) { CommandParser.Execute(line); }
        }
        Console.Read();
    }
}