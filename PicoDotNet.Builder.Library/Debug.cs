namespace PicoDotNet.Builder.Library;

public static class Debug
{
    public static string CreateFormattedString(string fmt, object[] args)
    {
        string output = string.Empty;
        int i = 0, a = 0;

        while (i < fmt.Length)
        {
            if (fmt[i] == '%')
            {
                i++;
                if (a < 0 || a >= args.Length) { output += fmt[i]; }
                else
                {
                    switch (fmt[i])
                    {
                        case 'd':
                            output += ((int)args[a++]).ToString();
                            break;
                        case 'u':
                            output += ((uint)args[a++]).ToString();
                            break;
                        case 'l':
                            output += ((ulong)args[a++]).ToString();
                            break;
                        case 'f':
                            output += ((float)args[a++]).ToString();
                            break;
                        case 'p':
                            output += ((uint)args[a++]).ToString("X8");
                            break;
                        case 'c':
                            output += (char)args[a++];
                            break;
                        case 's':
                            output += args[a++].ToString();
                            break;
                        default:
                            output += fmt[i];
                            break;
                    }
                }
            }
            else { output += fmt[i]; }
            i++;
        }
        return output;
    }

    public static void LogArguments(string fmt, object[] args)
    {
        string str = CreateFormattedString(fmt, args);
        Log(str);
    }

    public static void Log(string fmt, params object[] args)
    {
        string str = CreateFormattedString(fmt, args);
        Log(str);
    }

    public static void Log(string txt) { Console.Write(txt); }

    public static void Error(string fmt, params object[] args)
    {
        Console.Write('[');
        Console.ForegroundColor = ConsoleColor.Red;
        Console.Write("ERROR");
        Console.ForegroundColor = ConsoleColor.White;
        Console.Write("] ");
        LogArguments(fmt, args);
        Console.Write('\n');
        Console.ReadLine();
        Environment.Exit(1);
    }
}
