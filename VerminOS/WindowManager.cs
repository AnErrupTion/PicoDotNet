namespace VerminOS;

public static class WindowManager
{
    public static bool IsWindowMoving = false;
    public static Window? ActiveWindow = null;

    public static readonly List<Window> Windows = new();

    public static void Update()
    {
        foreach (var window in Windows)
        {
            if (window == ActiveWindow)
                continue;
                    
            window.Draw();
            window.Update();
        }
                
        ActiveWindow?.Draw();
        ActiveWindow?.Update();
    }
}