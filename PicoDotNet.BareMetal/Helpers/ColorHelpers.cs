using System.Drawing;

namespace PicoDotNet.Helpers;

internal static class ColorHelpers
{
    private static readonly Color DarkYellow = Color.FromArgb(205, 150, 0);

    public static Color ToColor(ConsoleColor color)
    {
        return color switch
        {
            ConsoleColor.Black => Color.Black,
            ConsoleColor.DarkBlue => Color.DarkBlue,
            ConsoleColor.DarkGreen => Color.DarkGreen,
            ConsoleColor.DarkCyan => Color.DarkCyan,
            ConsoleColor.DarkRed => Color.DarkRed,
            ConsoleColor.DarkMagenta => Color.DarkMagenta,
            ConsoleColor.DarkYellow => DarkYellow,
            ConsoleColor.Gray => Color.Gray,
            ConsoleColor.DarkGray => Color.DarkGray,
            ConsoleColor.Blue => Color.Blue,
            ConsoleColor.Green => Color.Green,
            ConsoleColor.Cyan => Color.Cyan,
            ConsoleColor.Red => Color.Red,
            ConsoleColor.Magenta => Color.Magenta,
            ConsoleColor.Yellow => Color.Yellow,
            ConsoleColor.White => Color.White,
            _ => throw new ArgumentOutOfRangeException(nameof(color), color, "Unknown console color.")
        };
    }
}