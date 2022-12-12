using PicoDotNet.Builder.Library;

namespace PicoDotNet.OSMake;

public static class Program
{    
    private static void Main(string[] _)
    {
        Debug.Log("PicoDotNet Builder Utility\n");
        RegisterCommands();
        
        Directory.SetCurrentDirectory("../PicoDotNet.Runtime.C");
        var lines = File.ReadAllLines("Build/build.osmake");
        foreach (var line in lines) { CommandParser.Execute(line); }
        Console.Read();
    }

    private static void RegisterCommands()
    {
        CommandParser.Register(CommandDeclarations.INFO);
        CommandParser.Register(CommandDeclarations.SET_ASSEMBLER);
        CommandParser.Register(CommandDeclarations.SET_COMPILER);
        CommandParser.Register(CommandDeclarations.SET_LINKER);
        CommandParser.Register(CommandDeclarations.SET_OBJDUMP);
        CommandParser.Register(CommandDeclarations.SET_GRUB);
        CommandParser.Register(CommandDeclarations.SET_LIMINE);
        CommandParser.Register(CommandDeclarations.SET_EMULATOR);
        CommandParser.Register(CommandDeclarations.SET_RAMFSMGR);
        CommandParser.Register(CommandDeclarations.SET_DIR);
        CommandParser.Register(CommandDeclarations.MK_DIR);
        CommandParser.Register(CommandDeclarations.RM_DIR);
        CommandParser.Register(CommandDeclarations.RMMK_DIR);
        CommandParser.Register(CommandDeclarations.COMPILE);
        CommandParser.Register(CommandDeclarations.COMPILE_PATH);
        CommandParser.Register(CommandDeclarations.ASSEMBLE);
        CommandParser.Register(CommandDeclarations.ASSEMBLE_PATH);
        CommandParser.Register(CommandDeclarations.LINK);
        CommandParser.Register(CommandDeclarations.LINK_PATH);
        CommandParser.Register(CommandDeclarations.MK_ISO);
        CommandParser.Register(CommandDeclarations.MK_RAMDISK);
        CommandParser.Register(CommandDeclarations.LIMINE);
        CommandParser.Register(CommandDeclarations.RUN);
    }
}