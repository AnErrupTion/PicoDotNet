using System.Runtime.CompilerServices;

namespace PicoDotNet;

/// <summary>
/// The native functions plugged by the runtime.
/// </summary>

// TODO: Documentation on methods
internal static unsafe class NativeHost
{
    [MethodImpl(MethodImplOptions.InternalCall)]
    public static extern void* Memory_Allocate(ulong size);

    [MethodImpl(MethodImplOptions.InternalCall)]
    public static extern void Memory_Free(void* buffer, ulong size);

    [MethodImpl(MethodImplOptions.InternalCall)]
    public static extern void Port_WriteByte(ushort port, byte value);

    [MethodImpl(MethodImplOptions.InternalCall)]
    public static extern void Port_WriteUShort(ushort port, ushort value);

    [MethodImpl(MethodImplOptions.InternalCall)]
    public static extern void Port_WriteUInt(ushort port, uint value);

    [MethodImpl(MethodImplOptions.InternalCall)]
    public static extern void Port_WriteULong(ushort port, ulong value);

    [MethodImpl(MethodImplOptions.InternalCall)]
    public static extern byte Port_ReadByte(ushort port);

    [MethodImpl(MethodImplOptions.InternalCall)]
    public static extern ushort Port_ReadUShort(ushort port);

    [MethodImpl(MethodImplOptions.InternalCall)]
    public static extern uint Port_ReadUInt(ushort port);

    [MethodImpl(MethodImplOptions.InternalCall)]
    public static extern ulong Port_ReadULong(ushort port);
}