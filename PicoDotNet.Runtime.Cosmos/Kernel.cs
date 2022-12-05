using System;
using Cosmos.System.FileSystem;
using Cosmos.System.FileSystem.VFS;
using libDotNetClr;
using LibDotNetParser.CILApi;
using Sys = Cosmos.System;

namespace PicoDotNet.Runtime.Cosmos;

public class Kernel : Sys.Kernel
{
    protected override void OnBoot()
    {
        Sys.Global.Init(GetTextScreen(), false, false, false);
    }

    protected override void BeforeRun()
    {
        Console.Clear();
        VFSManager.RegisterVFS(new CosmosVFS());
        Console.WriteLine("[Loaded VFS]");
    }

    protected override void Run()
    {
        var file = new DotNetFile("1:\\VerminOS.dll");
        var clr = new DotNetClr(file, "1:\\");
        clr.Start();

        for (;;) ;
    }
}