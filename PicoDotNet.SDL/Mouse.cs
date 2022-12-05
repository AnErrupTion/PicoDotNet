using System.Drawing;
using static SDL2.Bindings.SDL;

namespace PicoDotNet;

public static class Mouse
{
    public static uint X { get; private set; }
    
    public static uint Y { get; private set; }

    public static MouseState State { get; private set; }

    public static bool IsInBounds(uint x, uint y, uint width, uint height) => Canvas.IsInBounds(X, x, Y, y, width, height);

    public static void Update()
    {
        var buttons = SDL_GetMouseState(out var x, out var y);

        X = (uint)x;
        Y = (uint)y;

        State = MouseState.None;

        if ((buttons & SDL_BUTTON_LMASK) != 0)
            State |= MouseState.Left;
        
        if ((buttons & SDL_BUTTON_MMASK) != 0)
            State |= MouseState.Middle;
        
        if ((buttons & SDL_BUTTON_RMASK) != 0)
            State |= MouseState.Right;
        
        Canvas.DrawPoint(X, Y, Color.Blue);
    }
}