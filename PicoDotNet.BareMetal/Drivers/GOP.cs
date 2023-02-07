namespace PicoDotNet.BareMetal.Drivers;

public static unsafe class GOP
{
    private static uint* _frameBuffer, _backBuffer;
    private static uint _width, _height;
    private static ulong _frameSize;

    public static void Initialize(uint width, uint height)
    {
        NativeHost.GOP_SetMode(width, height);

        _frameBuffer = (uint*)NativeHost.GOP_GetFramebuffer();
        _backBuffer = (uint*)NativeHost.Memory_Allocate(_frameSize * 4);
        _width = width;
        _height = height;
        _frameSize = width * height;
    }

    public static void Clear(uint color)
    {
        for (ulong i = 0; i < _frameSize; i++)
            _backBuffer[i] = color;
    }

    public static void SetPixel(uint x, uint y, uint color)
    {
        _backBuffer[_width * y + x] = color;
    }

    public static void Update()
    {
        for (ulong i = 0; i < _frameSize; i++)
            _frameBuffer[i] = _backBuffer[i];
    }
}