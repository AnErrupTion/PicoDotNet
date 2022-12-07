namespace VerminOS.Commands;

public static class CommandManager
{
    private static readonly Dictionary<string, Action> Commands = new();

    public static void Register(string cmd, Action action) => Commands.Add(cmd, action);

    public static void Run(string cmd)
    {
        if (!Commands.TryGetValue(cmd, out var action))
        {
            Console.WriteLine("Unknown command!");
            return;
        }

        action.Invoke();
    }
}