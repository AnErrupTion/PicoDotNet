using System.Drawing;
using PicoDotNet.BareMetal.Drivers;

namespace PicoDotNet.BareMetal;

public static class Canvas
{
    /// <summary>
    /// Checks if the canvas was already initialized.
    /// </summary>
    public static bool Initialized { get; private set; }
    
    /// <summary>
    /// Gets the width of the canvas.
    /// </summary>
    public static uint Width { get; private set; }
    
    /// <summary>
    /// Gets the height of the canvas.
    /// </summary>
    public static uint Height { get; private set; }

    /// <summary>
    /// Initializes the canvas.
    /// </summary>
    /// <param name="width">The width.</param>
    /// <param name="height">The height.</param>
    public static void Initialize(uint width, uint height)
    {
        if (Initialized)
        {
            Clear(Color.Black);
            return;
        }

        GOP.Initialize((ushort)width, (ushort)height);

        Width = width;
        Height = height;
        Initialized = true;
    }

    /// <summary>
    /// Checks if specific coordinates are in bounds.
    /// </summary>
    /// <param name="x1">The first X coordinate.</param>
    /// <param name="x2">The second X coordinate.</param>
    /// <param name="y1">The first Y coordinate.</param>
    /// <param name="y2">The second Y coordinate.</param>
    /// <param name="width">The width.</param>
    /// <param name="height">The height.</param>
    /// <returns></returns>
    public static bool IsInBounds(uint x1, uint x2, uint y1, uint y2, uint width, uint height) =>
        x1 >= x2 && x1 <= x2 + width && y1 >= y2 && y1 <= y2 + height;

    /// <summary>
    /// Clears the screen with a specified color.
    /// </summary>
    /// <param name="color">The color.</param>
    public static void Clear(Color color)
    {
        GOP.Clear((uint)color.ToArgb());
    }

    /// <summary>
    /// Draws a point at specified coordinates with a specified color.
    /// </summary>
    /// <param name="x">The X coordinate.</param>
    /// <param name="y">The Y coordinate.</param>
    /// <param name="color">The color.</param>
    public static void DrawPoint(uint x, uint y, Color color)
    {
        GOP.SetPixel(x, y, (uint)color.ToArgb());
    }

    /// <summary>
    /// Draws text at specified coordinates with a specified color.
    /// </summary>
    /// <param name="x"></param>
    /// <param name="y"></param>
    /// <param name="text"></param>
    public static void DrawText(uint x, uint y, string text, Color color)
    {
        // TODO: Draw text on GOP
    }

    /// <summary>
    /// Draws a filled rectangle at specified coordinates with a specified width, height and color.
    /// </summary>
    /// <param name="x">The X coordinate.</param>
    /// <param name="y">The Y coordinate.</param>
    /// <param name="width">The width.</param>
    /// <param name="height">The height.</param>
    /// <param name="color">The color.</param>
    public static void DrawFilledRectangle(uint x, uint y, uint width, uint height, Color color)
    {
        var col = (uint)color.ToArgb();
        for (var xx = x; xx < width; xx++)
            for (var yy = y; yy < height; yy++)
                GOP.SetPixel(xx, yy, col);
    }

    /// <summary>
    /// Draws a rectangle at specified coordinates with a specified width, height and color.
    /// </summary>
    /// <param name="x">The X coordinate.</param>
    /// <param name="y">The Y coordinate.</param>
    /// <param name="width">The width.</param>
    /// <param name="height">The height.</param>
    /// <param name="color">The color.</param>
    public static void DrawRectangle(uint x, uint y, uint width, uint height, Color color)
    {
        // TODO: Draw rectangle on GOP
    }

    /// <summary>
    /// Calculates the real screen width of a string.
    /// </summary>
    /// <param name="text">The string to calculate.</param>
    /// <returns>The real screen width of the chosen string.</returns>
    public static uint CalculateWidth(string text)
    {
        // TODO: Calculate text width on GOP
        return 0;
    }

    /// <summary>
    /// Calculates the real screen height of a string.
    /// </summary>
    /// <param name="text">The string to calculate.</param>
    /// <returns>The real screen height of the chosen string.</returns>
    public static uint CalculateHeight(string text)
    {
        // TODO: Calculate text height on GOP
        return 0;
    }

    /// <summary>
    /// Renders the pixels to the screen.
    /// </summary>
    public static void Update() => GOP.Update();
}