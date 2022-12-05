using System.Drawing;
using PicoDotNet;
using VerminOS;
using Console = PicoDotNet.Console;

Utils.Initialize();

for (;;)
{
    Console.Write("> ");
    var cmd = Console.ReadLine();

    switch (cmd)
    {
        case "help":
            Console.WriteLine("WIP!");
            break;

        case "gui":
        {
            Canvas.Initialize(1280, 720);

            var taskbar = new Taskbar();
            taskbar.Children.Add(new Button(taskbar, 10, 0, 70, taskbar.Height, "Window", () => WindowManager.Windows.Add(new Window(20, 20, 250, 130, "New Window"))));

            for (;;)
            {
                Canvas.Clear(Color.Black);

                WindowManager.Update();
                taskbar.Draw();
                taskbar.Update();
                Mouse.Update();

                Canvas.Update();
                Utils.Process();
            }
        }
    
        default:
            Console.WriteLine("Unknown command!");
            break;
    }

    Utils.Process();
}