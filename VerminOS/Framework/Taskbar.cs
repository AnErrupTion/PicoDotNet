using PicoDotNet;

namespace VerminOS.Framework;

public class Taskbar : Component
{
    public Taskbar() : base(null, 0, 0, 0, 0, Config.AccentColor) => UpdateAlignment();

    public override void Draw()
    {
        UpdateAlignment();
        Canvas.DrawFilledRectangle(X, Y, Width, Height, Config.AccentColor);
    }

    private void UpdateAlignment()
    {
        switch (Config.TaskbarAlignment)
        {
            case Alignment.Left:
                Width = Config.TaskbarHeight;
                Height = Canvas.Width;
                X = 0;
                Y = 0;
                break;
            case Alignment.Right:
                Width = Config.TaskbarHeight;
                Height = Canvas.Width;
                X = Canvas.Width - Width;
                Y = 0;
                break;
            case Alignment.Top:
                Width = Canvas.Width;
                Height = Config.TaskbarHeight;
                X = 0;
                Y = 0;
                break;
            case Alignment.Bottom:
                Width = Canvas.Width;
                Height = Config.TaskbarHeight;
                X = 0;
                Y = Canvas.Height - Config.TaskbarHeight;
                break;
        }
    }
}