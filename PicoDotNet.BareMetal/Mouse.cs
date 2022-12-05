using System.Drawing;

namespace PicoDotNet;

public static class Mouse
{
    public static uint X { get; private set; }
    
    public static uint Y { get; private set; }

    public static MouseState State { get; private set; }

    public static bool IsInBounds(uint x, uint y, uint width, uint height) => Canvas.IsInBounds(X, x, Y, y, width, height);

    public static void Update()
    {
        // TODO: Mouse update
        
        Canvas.DrawPoint(X, Y, Color.Blue);
    }
}