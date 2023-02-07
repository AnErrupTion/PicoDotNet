using PicoDotNet.SDL;
using VerminOS.Framework;

namespace VerminOS.Apps;

public class Desktop : Component
{
    public Desktop() : base(null, 0, 0, Canvas.Width, Canvas.Height, Config.BackgroundColor)
    {
        var taskbar = new Taskbar();
        taskbar.Children.Add(new Button(taskbar, 10, 0, 70, taskbar.Height, "Window", () => WindowManager.Windows.Add(new Window(60, 80, 250, 130, "New Window"))));

        Children.Add(taskbar);
    }

    public override void Draw() => Canvas.Clear(Color);
}