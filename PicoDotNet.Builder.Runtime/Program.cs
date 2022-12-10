﻿using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Text;
using DiscUtils.Iso9660;

namespace PicoDotNet.Builder.Runtime;

public static class Program
{
    private const string KernelArgs =
        "-IInclude -nostdlib -ffreestanding -Wall -Wextra -fno-exceptions -Wno-write-strings -Wno-unused-parameter -Wno-unused-variable";

    public static void Main(string[] _)
    {
        Console.WriteLine("Detected platform - " + RuntimeInformation.OSDescription);
        Directory.SetCurrentDirectory("../PicoDotNet.Runtime.C");

        BuildPaths.LoadConfiguration();

        if (Directory.Exists("Bin")) { Directory.Delete("Bin", true); }
        Directory.CreateDirectory("Bin/Obj");

        Process.Start(BuildPaths.Nasm, "-felf32 Source/Boot/Start.asm -o Bin/Start.o").WaitForExit();
        Process.Start(BuildPaths.Nasm, "-felf32 Source/HAL/System/RealMode.asm -o Bin/Obj/RealMode.o").WaitForExit();
        Process.Start(BuildPaths.Nasm, "-felf32 Source/HAL/Interrupts/IRQs.asm -o Bin/Obj/IRQs.o").WaitForExit();
        Process.Start(BuildPaths.Nasm, "-felf32 Source/Core/Multitasking/ThreadSwitch.asm -o Bin/Obj/ThreadSwitch.o").WaitForExit();
        Process.Start(BuildPaths.Nasm, "-felf32 Source/HAL/System/Registers.asm -o Bin/Obj/Registers.o").WaitForExit();

        foreach (var file in Directory.GetFiles("Source", "*.c", SearchOption.AllDirectories))
            Process.Start(BuildPaths.Gcc,
                    $"-c \"{file}\" -o \"Bin/Obj/{Path.GetFileNameWithoutExtension(file) + ".o"}\" {KernelArgs}")
                .WaitForExit();

        Process.Start(BuildPaths.Ld,
            Directory.GetFiles("Bin/Obj", "*.o", SearchOption.AllDirectories).Aggregate(
                "-T \"Build/linker.ld\" -o \"Bin/Kernel.elf\" \"Bin/Start.o\"",
                (current, file) => current + $" \"{file}\"")).WaitForExit();

        var p = Process.Start(new ProcessStartInfo
        {
            FileName = BuildPaths.Objdump,
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
        using var ramdisk = File.OpenRead("Build/ramdisk.img");

        var iso = new CDBuilder
        {
            UseJoliet = true,
            VolumeIdentifier = "PicoDotNet",
            UpdateIsolinuxBootTable = true
        };
        iso.AddFile("limine.sys", sys);
        iso.AddFile("limine.cfg", Encoding.ASCII.GetBytes("TIMEOUT=0\n:PicoDotNet\nPROTOCOL=multiboot1\nKERNEL_PATH=boot:///kernel.elf\nMODULE_PATH=boot:///ramdisk.img\n"));
        iso.AddFile("kernel.elf", kernel);
        iso.AddFile("ramdisk.img", ramdisk);
        iso.SetBootImage(cd, BootDeviceEmulation.NoEmulation, 0);
        iso.Build("Bin/PicoDotNet.iso");

        Process.Start(BuildPaths.LimineDeploy, "--force-mbr Bin/PicoDotNet.iso").WaitForExit();
        Process.Start(BuildPaths.Qemu,
                "-usb -m 2G -cdrom Bin/PicoDotNet.iso -serial stdio -device AC97 -rtc base=localtime -no-reboot -no-shutdown")
            .WaitForExit();
    }
}