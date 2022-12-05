namespace PicoDotNet.Drivers;

public static unsafe class BGA
{
    private const ushort Index = 0x01CE;
    private const ushort Data = 0x01CF;

    private static readonly uint* FrameBuffer = (uint*)0xE0000000;

    private static ushort _width, _height;
    private static ulong _frameSize;
    private static uint* _backBuffer;

    public static void Initialize(ushort width, ushort height)
    {
        WriteRegister(4, 0);
        WriteRegister(1, width);
        WriteRegister(2, height);
        WriteRegister(3, 32);
        WriteRegister(4, 1 | 0x40);

        _width = width;
        _height = height;
        _frameSize = (ulong)(width * height);
        _backBuffer = (uint*)NativeHost.Memory_Allocate(_frameSize * 4);
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
            FrameBuffer[i] = _backBuffer[i];
    }

    private static void WriteRegister(ushort index, ushort data)
    {
        NativeHost.Port_WriteUShort(Index, index);
        NativeHost.Port_WriteUShort(Data, data);
    }
}