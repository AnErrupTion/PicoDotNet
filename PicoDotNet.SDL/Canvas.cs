using System.Drawing;
using PicoDotNet.SDL.Windowing;
using static SDL2.Bindings.SDL_ttf;
using static SDL2.Bindings.SDL;

namespace PicoDotNet;

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

        SDL_Init(SDL_INIT_VIDEO);
        SDL_CreateWindowAndRenderer((int)width, (int)height, 0, out Sdl.Window, out Sdl.Renderer);
        SDL_RenderPresent(Sdl.Renderer);

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
        SDL_SetRenderDrawColor(Sdl.Renderer, color.R, color.G, color.B, color.A);
        SDL_RenderClear(Sdl.Renderer);
    }

    /// <summary>
    /// Draws a point at specified coordinates with a specified color.
    /// </summary>
    /// <param name="x">The X coordinate.</param>
    /// <param name="y">The Y coordinate.</param>
    /// <param name="color">The color.</param>
    public static void DrawPoint(uint x, uint y, Color color)
    {
        SDL_SetRenderDrawColor(Sdl.Renderer, color.R, color.G, color.B, color.A);
        SDL_RenderDrawPoint(Sdl.Renderer, (int)x, (int)y);
    }

    /// <summary>
    /// Draws text at specified coordinates with a specified color.
    /// </summary>
    /// <param name="x"></param>
    /// <param name="y"></param>
    /// <param name="text"></param>
    public static void DrawText(uint x, uint y, string text, Color color)
    {
        var surface = TTF_RenderText_Solid(Sdl.Font, text, Sdl.ToSdlColor(color));
        var message = SDL_CreateTextureFromSurface(Sdl.Renderer, surface);

        SDL_FreeSurface(surface);
        SDL_QueryTexture(message, out _, out _, out var width, out var height);

        var rect = new SDL_Rect
        {
            x = (int)x,
            y = (int)y,
            w = width,
            h = height
        };

        SDL_RenderCopy(Sdl.Renderer, message, IntPtr.Zero, ref rect);
        SDL_DestroyTexture(message);
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
        var rect = new SDL_Rect
        {
            x = (int)x,
            y = (int)y,
            w = (int)width,
            h = (int)height
        };

        SDL_SetRenderDrawColor(Sdl.Renderer, color.R, color.G, color.B, color.A);
        SDL_RenderFillRect(Sdl.Renderer, ref rect);
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
        var rect = new SDL_Rect
        {
            x = (int)x,
            y = (int)y,
            w = (int)width,
            h = (int)height
        };

        SDL_SetRenderDrawColor(Sdl.Renderer, color.R, color.G, color.B, color.A);
        SDL_RenderDrawRect(Sdl.Renderer, ref rect);
    }

    /// <summary>
    /// Calculates the real screen width of a string.
    /// </summary>
    /// <param name="text">The string to calculate.</param>
    /// <returns>The real screen width of the chosen string.</returns>
    public static uint CalculateWidth(string text)
    {
        var surface = TTF_RenderText_Solid(Sdl.Font, text, Sdl.EmptyColor);
        var message = SDL_CreateTextureFromSurface(Sdl.Renderer, surface);

        SDL_FreeSurface(surface);
        SDL_QueryTexture(message, out _, out _, out var width, out _);
        SDL_DestroyTexture(message);

        return (uint)width;
    }

    /// <summary>
    /// Calculates the real screen height of a string.
    /// </summary>
    /// <param name="text">The string to calculate.</param>
    /// <returns>The real screen height of the chosen string.</returns>
    public static uint CalculateHeight(string text)
    {
        var surface = TTF_RenderText_Solid(Sdl.Font, text, Sdl.EmptyColor);
        var message = SDL_CreateTextureFromSurface(Sdl.Renderer, surface);

        SDL_FreeSurface(surface);
        SDL_QueryTexture(message, out _, out _, out _, out var height);
        SDL_DestroyTexture(message);

        return (uint)height;
    }

    /// <summary>
    /// Renders the pixels to the screen.
    /// </summary>
    public static void Update() => SDL_RenderPresent(Sdl.Renderer);
}