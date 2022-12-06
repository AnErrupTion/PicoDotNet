using System;
using System.IO;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Text;

namespace PicoDotNet.Builder.Runtime;

public static class BuildPaths
{
    public const string ConfigFile = "Build/builer_config.ini";

    public static string Nasm           { get; private set; } = "";
    public static string Gcc            { get; private set; } = "";
    public static string Ld             { get; private set; } = "";
    public static string Objdump        { get; private set; } = "";
    public static string LimineDeploy   { get; private set; } = "";
    public static string Qemu           { get; private set; } = "";

    public static void GenerateDefaultConfiguration()
    {
        if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows))
        {
            Nasm         = Path.Combine("Build", "nasm.exe");
            Gcc          = Path.Combine("Build", "i686-elf-tools-windows", "bin", "i686-elf-gcc.exe");
            Ld           = Path.Combine("Build", "i686-elf-tools-windows", "bin", "i686-elf-ld.exe");
            Objdump      = Path.Combine("Build", "i686-elf-tools-windows", "bin", "i686-elf-objdump.exe");
            LimineDeploy = Path.Combine("Build", "limine-deploy.exe");
            Qemu         = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ProgramFiles), "qemu", "qemu-system-i386");
        }
        else if (RuntimeInformation.IsOSPlatform(OSPlatform.Linux))
        {
            Nasm         = "nasm";
            Gcc          = "i686-elf-gcc";
            Ld           = "i686-elf-ld";
            Objdump      = "objdump";
            LimineDeploy = "Build/limine-deploy";
            Qemu         = "qemu-system-i386";
        }
        Console.WriteLine("Generated default configuration for " + RuntimeInformation.OSDescription);
    }

    public static void SaveConfiguration()
    {
        List<string> lines = new List<string>();
        lines.Add("nasm,"         + Nasm);
        lines.Add("gcc,"          + Gcc);
        lines.Add("ld,"           + Ld);
        lines.Add("objdump,"      + Objdump);
        lines.Add("limine," + LimineDeploy);
        lines.Add("qemu,"         + Qemu);
        File.WriteAllLines(ConfigFile, lines.ToArray());
        Console.WriteLine("Saved build configuration");
    }

    public static void LoadConfiguration()
    {
        if (!File.Exists(ConfigFile))
        {
            GenerateDefaultConfiguration();
            SaveConfiguration();
            return;
        }

        string[] lines = File.ReadAllLines(ConfigFile);
        for (int i = 0; i < lines.Length; i++)
        {
            string[] parts = lines[i].Split(',');
            if (parts.Length < 2) { continue; }
            if (parts[0] == "nasm")    { Nasm         = parts[1]; }
            if (parts[0] == "gcc")     { Gcc          = parts[1]; }
            if (parts[0] == "ld")      { Ld           = parts[1]; }
            if (parts[0] == "objdump") { Objdump      = parts[1]; }
            if (parts[0] == "limine")  { LimineDeploy = parts[1]; }
            if (parts[0] == "qemu")    { Qemu         = parts[1]; }
        }

        Console.WriteLine("Loaded build configuration");
    }
}