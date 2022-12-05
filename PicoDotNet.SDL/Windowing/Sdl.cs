using System.Drawing;
using static SDL2.Bindings.SDL;

namespace PicoDotNet.SDL.Windowing;

internal static class Sdl
{
    internal static IntPtr Window, Renderer, Font;
    internal static SDL_Color EmptyColor = new();

    internal static SDL_Color ToSdlColor(ConsoleColor color)
    {
        var sdlColor = new SDL_Color();
        
        switch (color)
        {
            case ConsoleColor.Black:
                sdlColor.r = Color.Black.R;
                sdlColor.g = Color.Black.G;
                sdlColor.b = Color.Black.B;
                sdlColor.a = Color.Black.A;
                break;
            case ConsoleColor.DarkBlue:
                sdlColor.r = Color.DarkBlue.R;
                sdlColor.g = Color.DarkBlue.G;
                sdlColor.b = Color.DarkBlue.B;
                sdlColor.a = Color.DarkBlue.A;
                break;
            case ConsoleColor.DarkGreen:
                sdlColor.r = Color.DarkGreen.R;
                sdlColor.g = Color.DarkGreen.G;
                sdlColor.b = Color.DarkGreen.B;
                sdlColor.a = Color.DarkGreen.A;
                break;
            case ConsoleColor.DarkCyan:
                sdlColor.r = Color.DarkCyan.R;
                sdlColor.g = Color.DarkCyan.G;
                sdlColor.b = Color.DarkCyan.B;
                sdlColor.a = Color.DarkCyan.A;
                break;
            case ConsoleColor.DarkRed:
                sdlColor.r = Color.DarkRed.R;
                sdlColor.g = Color.DarkRed.G;
                sdlColor.b = Color.DarkRed.B;
                sdlColor.a = Color.DarkRed.A;
                break;
            case ConsoleColor.DarkMagenta:
                sdlColor.r = Color.DarkMagenta.R;
                sdlColor.g = Color.DarkMagenta.G;
                sdlColor.b = Color.DarkMagenta.B;
                sdlColor.a = Color.DarkMagenta.A;
                break;
            case ConsoleColor.DarkYellow:
                sdlColor.r = 205;
                sdlColor.g = 150;
                sdlColor.b = 0;
                sdlColor.a = 255;
                break;
            case ConsoleColor.Gray:
                sdlColor.r = Color.Gray.R;
                sdlColor.g = Color.Gray.G;
                sdlColor.b = Color.Gray.B;
                sdlColor.a = Color.Gray.A;
                break;
            case ConsoleColor.DarkGray:
                sdlColor.r = Color.DarkGray.R;
                sdlColor.g = Color.DarkGray.G;
                sdlColor.b = Color.DarkGray.B;
                sdlColor.a = Color.DarkGray.A;
                break;
            case ConsoleColor.Blue:
                sdlColor.r = Color.Blue.R;
                sdlColor.g = Color.Blue.G;
                sdlColor.b = Color.Blue.B;
                sdlColor.a = Color.Blue.A;
                break;
            case ConsoleColor.Green:
                sdlColor.r = Color.Green.R;
                sdlColor.g = Color.Green.G;
                sdlColor.b = Color.Green.B;
                sdlColor.a = Color.Green.A;
                break;
            case ConsoleColor.Cyan:
                sdlColor.r = Color.Cyan.R;
                sdlColor.g = Color.Cyan.G;
                sdlColor.b = Color.Cyan.B;
                sdlColor.a = Color.Cyan.A;
                break;
            case ConsoleColor.Red:
                sdlColor.r = Color.Red.R;
                sdlColor.g = Color.Red.G;
                sdlColor.b = Color.Red.B;
                sdlColor.a = Color.Red.A;
                break;
            case ConsoleColor.Magenta:
                sdlColor.r = Color.Magenta.R;
                sdlColor.g = Color.Magenta.G;
                sdlColor.b = Color.Magenta.B;
                sdlColor.a = Color.Magenta.A;
                break;
            case ConsoleColor.Yellow:
                sdlColor.r = Color.Yellow.R;
                sdlColor.g = Color.Yellow.G;
                sdlColor.b = Color.Yellow.B;
                sdlColor.a = Color.Yellow.A;
                break;
            case ConsoleColor.White:
                sdlColor.r = Color.White.R;
                sdlColor.g = Color.White.G;
                sdlColor.b = Color.White.B;
                sdlColor.a = Color.White.A;
                break;
        }

        return sdlColor;
    }
    
     internal static SDL_Color ToSdlColor(Color color) 
     { 
         return new SDL_Color 
         { 
             r = color.R, 
             g = color.G, 
             b = color.B, 
             a = color.A 
         };
     }
}