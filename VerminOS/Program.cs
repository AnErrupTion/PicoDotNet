using PicoDotNet;
using VerminOS.Commands;
using VerminOS.Gui;
using Console = PicoDotNet.Console;

Utils.Initialize();

CommandManager.Register("help", () => Console.WriteLine("help - Shows all commands.\nver - Shows the VerminOS version.\ngui - Enters GUI mode."));
CommandManager.Register("ver", () => Console.WriteLine("VerminOS - Written using PicoDotNet"));
CommandManager.Register("gui", GuiManager.Initialize);

for (;;)
{
    Console.Write("> ");
    var cmd = Console.ReadLine();

    CommandManager.Run(cmd);

    Utils.Process();
}