using System.Drawing;

namespace VerminOS.Framework;

public static class Config
{
    public static Color AccentColor = Color.Coral;
    public static Color BodyColor = Color.White;
    public static Color TextColor = Color.Black;
    public static Color BorderColor = Color.OrangeRed;
    public static Color BackgroundColor = Color.Black;

    public static readonly uint TaskbarHeight = 25;
    public static readonly Alignment TaskbarAlignment = Alignment.Top;

    public static readonly uint TitlebarHeight = 20;
}