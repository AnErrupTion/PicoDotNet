using PicoDotNet;

namespace VerminOS.Framework;

public class Window : Component
{
    private bool _held;
    private uint _offsetX, _offsetY;

    public string Text { get; set; }

    public Window(uint x, uint y, uint width, uint height, string text) : base(null, x, y, width, height, Config.BodyColor)
    {
        Text = text;
    }

    public override void Draw()
    {
        Canvas.DrawFilledRectangle(X, Y, Width, Config.TitlebarHeight, Config.AccentColor);
        Canvas.DrawFilledRectangle(X, Y + Config.TitlebarHeight, Width, Height, Color);
        Canvas.DrawText(X + Width / 2 - Canvas.CalculateWidth(Text) / 2, Y + Config.TitlebarHeight / 2 - Canvas.CalculateHeight(Text) / 2, Text, Config.BodyColor);
        Canvas.DrawRectangle(X, Y, Width, Height + Config.TitlebarHeight, Config.BorderColor);
    }

    public override void Update()
    {
        base.Update();

        if (WindowManager.IsWindowMoving && WindowManager.ActiveWindow != this)
            return;

        if (!_held && Mouse.State == MouseState.Left && Mouse.IsInBounds(X, Y, Width, Config.TitlebarHeight))
        {
            // Prevent inactive window from getting active if active window is overlapping that window
            if (WindowManager.ActiveWindow != this && IsTitlebarColliding())
                return;

            _held = true;
            WindowManager.IsWindowMoving = true;

            _offsetX = Mouse.X - X;
            _offsetY = Mouse.Y - Y;

            WindowManager.ActiveWindow = this;
        }

        if (!_held)
            return;

        X = Mouse.X - _offsetX;
        Y = Mouse.Y - _offsetY;

        _held = Mouse.State == MouseState.Left;
        WindowManager.IsWindowMoving = _held;
    }

    private bool IsTitlebarColliding() => WindowManager.ActiveWindow?.X < X + Width &&
                                          WindowManager.ActiveWindow.X + WindowManager.ActiveWindow.Width > X &&
                                          WindowManager.ActiveWindow.Y < Y + Config.TitlebarHeight &&
                                          Config.TitlebarHeight + WindowManager.ActiveWindow.Y > Y;
}