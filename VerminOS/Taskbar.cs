using PicoDotNet;

namespace VerminOS;

public class Taskbar : Component
{
    public Taskbar() : base(null, 0, Canvas.Height - 20, Canvas.Width, 20, Config.AccentColor) {}

    public override void Draw()
    {
        Canvas.DrawFilledRectangle(X, Y, Width, Height, Config.AccentColor);
    }
}