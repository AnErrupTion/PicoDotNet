using System.Drawing;
using PicoDotNet;

namespace VerminOS;

public class Button : Component
{
    public string Text { get; set; }
    
    public Action? Action { get; set; }

    private byte _clicked;

    public Button(Component parent, uint x, uint y, uint width, uint height, string text, Action? action) : base(parent, x, y, width, height, Config.BodyColor)
    {
        Text = text;
        Action = action;
    }

    public override void Draw()
    {
        Canvas.DrawFilledRectangle(X, Y, Width, Height, Color);
        Canvas.DrawText(X + Width / 2 - Canvas.CalculateWidth(Text) / 2, Y, Text, Config.TextColor);
    }

    public override void Update()
    {
        if (IsClicked(MouseState.Left))
        {
            _clicked++;
            if (_clicked > 1)
            {
                _clicked = 1;
                return;
            }
            
            Color = Color.DimGray;
            Action?.Invoke();
        }
        else
        {
            _clicked = 0;
            Color = IsHovered() ? Color.Gray : Color.White;
        }
    }

    private bool IsClicked(MouseState state)
    {
        return IsHovered() && Mouse.State == state;
    }

    private bool IsHovered()
    {
        return !WindowManager.IsWindowMoving && Mouse.IsInBounds(X, Y, Width, Height);
    }
}