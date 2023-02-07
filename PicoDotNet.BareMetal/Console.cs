using System.Drawing;
using System.Text;
using PicoDotNet.BareMetal.Fonts;
using PicoDotNet.BareMetal.Helpers;

namespace PicoDotNet.BareMetal;

public static class Console
{
    public static ConsoleColor ForegroundColor { get; set; } = ConsoleColor.White;

    // TODO: Background color on graphical console
    public static ConsoleColor BackgroundColor { get; set; } = ConsoleColor.Black;

    private static uint _x, _y;

    public static void Clear()
    {
        Canvas.Clear(Color.Black);

        _x = 0;
        _y = 0;
    }

    public static void Write(char c)
    {
        switch (c)
        {
            case '\n':
                _x = 0;
                _y += ASC16.Height;
                return;
            
            case '\r':
                _x = 0;
                return;
            
            case '\t':
                _x += 4;
                return;
            
            default:
                ASC16.DrawChar(_x, _y, c, ColorHelpers.ToColor(ForegroundColor));
                return;
        }
    }

    public static void Write(string text)
    {
        for (var i = 0; i < text.Length; i++)
            Write(text[i]);
    }

    public static void WriteLine(string text)
    {
        Write(text);
        Write('\n');
    }
    
    public static ConsoleKeyInfo ReadKey(bool intercept = false)
    {
        throw new Exception("Not implemented: ReadKey()");
    }

    public static string ReadLine()
    {
        var sb = new StringBuilder();
        
        ConsoleKeyInfo key;
        while ((key = ReadKey()).Key != ConsoleKey.Enter)
        {
            switch (key.Key) 
            {
                case ConsoleKey.Delete:
                case ConsoleKey.Backspace:
                    if (sb.Length == 0) continue;
                    sb.Remove(0, sb.Length - 1);
                    break;
                default:
                    sb.Append(key.KeyChar);
                    break;

            }
            
            Utils.Process();
        }
        
        return sb.ToString();
    }
}