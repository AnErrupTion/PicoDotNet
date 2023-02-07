using System.Drawing;
using System.Text;
using PicoDotNet.SDL.Windowing;
using static SDL2.Bindings.SDL_ttf;
using static SDL2.Bindings.SDL;

namespace PicoDotNet.SDL;

// TODO: '\n', '\r', '\t', etc... characters on SDL 2
public static class Console
{
    public static ConsoleColor ForegroundColor { get; set; } = ConsoleColor.White;

    // TODO: Background color when drawing text with SDL 2
    public static ConsoleColor BackgroundColor { get; set; } = ConsoleColor.Black;

    internal static Dictionary<Rectangle, IntPtr> LastFrames { get; } = new();

    private static int _x, _y;

    public static void Clear()
    {
        Canvas.Clear(Color.Black);

        _x = 0;
        _y = 0;
    }

    public static void Write(char c) => Write(c.ToString());

    public static void Write(string text)
    {
        foreach (var frame in LastFrames)
        {
            var r = new SDL_Rect
            {
                x = frame.Key.X,
                y = frame.Key.Y,
                w = frame.Key.Width,
                h = frame.Key.Height
            };
            SDL_RenderCopy(Sdl.Renderer, frame.Value, IntPtr.Zero, ref r);
        }
        
        var surface = TTF_RenderText_Solid(Sdl.Font, text, Sdl.ToSdlColor(ForegroundColor));
        var message = SDL_CreateTextureFromSurface(Sdl.Renderer, surface);

        SDL_FreeSurface(surface);
        SDL_QueryTexture(message, out _, out _, out var width, out var height);

        var rect = new SDL_Rect
        {
            x = _x,
            y = _y,
            w = width,
            h = height
        };

        SDL_RenderCopy(Sdl.Renderer, message, IntPtr.Zero, ref rect);
        SDL_RenderPresent(Sdl.Renderer);
        
        LastFrames.Add(new Rectangle(_x, _y, width, height), message);

        _x += width;
        if (_x < Canvas.Width)
            return;

        _x = 0;
        _y += height;
    }

    public static void WriteLine(string text)
    {
        foreach (var frame in LastFrames)
        {
            var r = new SDL_Rect
            {
                x = frame.Key.X,
                y = frame.Key.Y,
                w = frame.Key.Width,
                h = frame.Key.Height
            };
            SDL_RenderCopy(Sdl.Renderer, frame.Value, IntPtr.Zero, ref r);
        }
        
        var surface = TTF_RenderText_Solid(Sdl.Font, text, Sdl.ToSdlColor(ForegroundColor));
        var message = SDL_CreateTextureFromSurface(Sdl.Renderer, surface);

        SDL_FreeSurface(surface);
        SDL_QueryTexture(message, out _, out _, out var width, out var height);

        var rect = new SDL_Rect
        {
            x = _x,
            y = _y,
            w = width,
            h = height
        };

        SDL_RenderCopy(Sdl.Renderer, message, IntPtr.Zero, ref rect);
        SDL_RenderPresent(Sdl.Renderer);
        
        LastFrames.Add(new Rectangle(_x, _y, width, height), message);

        _x = 0;
        _y += height;
    }

    public static string ReadLine()
    {
        var sb = new StringBuilder();
        var capsLock = false;
        var disableCapsLock = false;
        var exit = false;

        while (!exit)
        {
            if (SDL_PollEvent(out var ev) == 0)
                continue;

            var lastLength = sb.Length;

            // TODO: Numbers and other characters
            switch (ev.type)
            {
                case SDL_EventType.SDL_KEYDOWN:
                    switch (ev.key.keysym.sym)
                    {
                        case SDL_Keycode.SDLK_KP_ENTER:
                        case SDL_Keycode.SDLK_RETURN:
                            exit = true;
                            break;
                        
                        case SDL_Keycode.SDLK_LSHIFT:
                        case SDL_Keycode.SDLK_RSHIFT:
                            capsLock = true;
                            disableCapsLock = true;
                            break;
                        
                        case SDL_Keycode.SDLK_CAPSLOCK: capsLock = !capsLock; break;
                        
                        case SDL_Keycode.SDLK_a: sb.Append(capsLock ? 'A' : 'a'); break;
                        case SDL_Keycode.SDLK_b: sb.Append(capsLock ? 'B' : 'b'); break;
                        case SDL_Keycode.SDLK_c: sb.Append(capsLock ? 'C' : 'c'); break;
                        case SDL_Keycode.SDLK_d: sb.Append(capsLock ? 'D' : 'd'); break;
                        case SDL_Keycode.SDLK_e: sb.Append(capsLock ? 'E' : 'e'); break;
                        case SDL_Keycode.SDLK_f: sb.Append(capsLock ? 'F' : 'f'); break;
                        case SDL_Keycode.SDLK_g: sb.Append(capsLock ? 'G' : 'g'); break;
                        case SDL_Keycode.SDLK_h: sb.Append(capsLock ? 'H' : 'h'); break;
                        case SDL_Keycode.SDLK_i: sb.Append(capsLock ? 'I' : 'i'); break;
                        case SDL_Keycode.SDLK_j: sb.Append(capsLock ? 'J' : 'j'); break;
                        case SDL_Keycode.SDLK_k: sb.Append(capsLock ? 'K' : 'k'); break;
                        case SDL_Keycode.SDLK_l: sb.Append(capsLock ? 'L' : 'l'); break;
                        case SDL_Keycode.SDLK_m: sb.Append(capsLock ? 'M' : 'm'); break;
                        case SDL_Keycode.SDLK_n: sb.Append(capsLock ? 'N' : 'n'); break;
                        case SDL_Keycode.SDLK_o: sb.Append(capsLock ? 'O' : 'o'); break;
                        case SDL_Keycode.SDLK_p: sb.Append(capsLock ? 'P' : 'p'); break;
                        case SDL_Keycode.SDLK_q: sb.Append(capsLock ? 'Q' : 'q'); break;
                        case SDL_Keycode.SDLK_r: sb.Append(capsLock ? 'R' : 'r'); break;
                        case SDL_Keycode.SDLK_s: sb.Append(capsLock ? 'S' : 's'); break;
                        case SDL_Keycode.SDLK_t: sb.Append(capsLock ? 'T' : 't'); break;
                        case SDL_Keycode.SDLK_u: sb.Append(capsLock ? 'U' : 'u'); break;
                        case SDL_Keycode.SDLK_v: sb.Append(capsLock ? 'V' : 'v'); break;
                        case SDL_Keycode.SDLK_w: sb.Append(capsLock ? 'W' : 'w'); break;
                        case SDL_Keycode.SDLK_x: sb.Append(capsLock ? 'X' : 'x'); break;
                        case SDL_Keycode.SDLK_y: sb.Append(capsLock ? 'Y' : 'y'); break;
                        case SDL_Keycode.SDLK_z: sb.Append(capsLock ? 'Z' : 'z'); break;
                        
                        case SDL_Keycode.SDLK_SPACE: sb.Append(' '); break;
                    }
                    break;
            }

            // If we pressed a key...
            if (sb.Length > lastLength)
            {
                var count = sb.Length - lastLength;
                var data = new char[count];
                sb.CopyTo(sb.Length - count, data, count);
                
                Write(new string(data));
                
                // ...while we had left or right shift pressed at the same time, then disable caps lock
                if (disableCapsLock)
                {
                    capsLock = false;
                    disableCapsLock = false;
                }
            }

            // We need to process other SDL events if we don't want the window to freeze
            Utils.Process();
        }

        var newFrames = LastFrames.Skip(LastFrames.Count - sb.Length).ToList();
        var height = 0;

        // Get the frame with the largest height
        foreach (var pair in newFrames)
        {
            var frame = pair.Value;
            SDL_QueryTexture(frame, out _, out _, out _, out var h);

            if (h > height)
                height = h;
        }

        _x = 0;
        _y += height;

        return sb.ToString();
    }
}