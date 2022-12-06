using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Text;
using DiscUtils.Iso9660;

namespace PicoDotNet.Builder.Runtime;

public static class Program
{
    private static string Nasm, Gcc, Ld, Objdump, LimineDeploy, Qemu;

    private const string KernelArgs =
        "-nostdlib -ffreestanding -Wall -Wextra -fno-exceptions -Wno-write-strings -Wno-unused-parameter -Wno-unused-variable";

    public static void Main(string[] _)
    {
        Directory.SetCurrentDirectory("../PicoDotNet.Runtime.C");

        if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows))
        {
            Nasm = Path.Combine("Build", "nasm.exe");
            Gcc = Path.Combine("Build", "i686-elf-tools-windows", "bin", "i686-elf-gcc.exe");
            Ld = Path.Combine("Build", "i686-elf-tools-windows", "bin", "i686-elf-ld.exe");
            Objdump = Path.Combine("Build", "i686-elf-tools-windows", "bin", "i686-elf-objdump.exe");
            LimineDeploy = Path.Combine("Build", "limine-deploy.exe");
            Qemu = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ProgramFiles), "qemu",
                "qemu-system-i386");
        }
        else
        {
            Nasm = "nasm";
            Gcc = "i686-elf-gcc";
            Ld = "i686-elf-ld";
            Objdump = "i686-elf-objdump";
            Nasm = "xorriso";
            LimineDeploy = "limine-deploy";
            Qemu = "qemu-system-i386";
        }

        if (Directory.Exists("Bin"))
            Directory.Delete("Bin", true);
        Directory.CreateDirectory("Bin/Obj");

        Process.Start(Nasm, "-felf32 Source/Start.asm -o Bin/Start.o").WaitForExit();

        foreach (var file in Directory.GetFiles("Source", "*.c", SearchOption.AllDirectories))
            Process.Start(Gcc,
                    $"-Iinclude -I../libk/include -c \"{file}\" -o \"Bin/Obj/{Path.GetFileNameWithoutExtension(file) + ".o"}\" {KernelArgs}")
                .WaitForExit();

        Process.Start(Ld,
            Directory.GetFiles("Bin/Obj", "*.o", SearchOption.AllDirectories).Aggregate(
                "-T \"Build/linker.ld\" -o \"Bin/Kernel.elf\" \"Bin/Start.o\"",
                (current, file) => current + $" \"{file}\"")).WaitForExit();

        var p = Process.Start(new ProcessStartInfo
        {
            FileName = Objdump,
            Arguments = "-t -dwarf -Mintel \"Bin/Kernel.elf\"",
            UseShellExecute = false,
            CreateNoWindow = false,
            RedirectStandardOutput = true
        });

        if (!Directory.Exists("Bin/Dumps"))
            Directory.CreateDirectory("Bin/Dumps");
        File.WriteAllText("Bin/Dumps/Kernel.dump", p?.StandardOutput.ReadToEnd());

        using var cd = File.OpenRead("Build/limine-cd.bin");
        using var sys = File.OpenRead("Build/limine.sys");
        using var kernel = File.OpenRead("Bin/Kernel.elf");

        var iso = new CDBuilder
        {
            UseJoliet = true,
            VolumeIdentifier = "PicoDotNet",
            UpdateIsolinuxBootTable = true
        };
        iso.AddFile("limine.sys", sys);
        iso.AddFile("limine.cfg", Encoding.ASCII.GetBytes("TIMEOUT=0\n:PicoDotNet\nPROTOCOL=multiboot1\nKERNEL_PATH=boot:///kernel.elf"));
        iso.AddFile("kernel.elf", kernel);
        iso.SetBootImage(cd, BootDeviceEmulation.NoEmulation, 0);
        iso.Build("Bin/PicoDotNet.iso");

        Process.Start(LimineDeploy, "--force-mbr Bin/PicoDotNet.iso").WaitForExit();
        Process.Start(Qemu,
                "-usb -m 2G -cdrom Bin/PicoDotNet.iso -serial stdio -device AC97 -rtc base=localtime -no-reboot -no-shutdown")
            .WaitForExit();
    }
}