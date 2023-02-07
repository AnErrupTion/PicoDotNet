using PicoDotNet.SDL.Windowing;
using static SDL2.Bindings.SDL_ttf;
using static SDL2.Bindings.SDL;

namespace PicoDotNet.SDL;

public static class Utils
{
    /// <summary>
    /// Initializes stuff, if needed.
    /// </summary>
    public static void Initialize()
    {
        TTF_Init();
        
        Sdl.Font = TTF_OpenFont("Sans.ttf", 16);
        
        Canvas.Initialize(1280, 720);
    }

    /// <summary>
    /// Processes information, if required. Should be used in a continuous loop.
    /// </summary>
    public static void Process()
    {
        if (SDL_PollEvent(out var ev) == 0 || ev.type != SDL_EventType.SDL_QUIT)
            return;
        
        TTF_CloseFont(Sdl.Font);
        TTF_Quit();

        foreach (var frame in Console.LastFrames)
            SDL_DestroyTexture(frame.Value);

        SDL_DestroyRenderer(Sdl.Renderer);
        SDL_DestroyWindow(Sdl.Window);
        SDL_Quit();

        Environment.Exit(0);
    }
}