using PicoDotNet.SDL;
using VerminOS.Apps;
using VerminOS.Framework;

namespace VerminOS.Gui;

public static class GuiManager
{
    public static void Initialize()
    {
        Canvas.Initialize(1280, 720);

        var components = new List<Component> { new Desktop() };

        for (;;)
        {
            var length = components.Count;
            for (var i = 0; i < length; i++)
            {
                var component = components[i];
                component.Draw();
                component.Update();
            }

            WindowManager.Update();
            Mouse.Update();

            Canvas.Update();
            Utils.Process();
        }
    }
}