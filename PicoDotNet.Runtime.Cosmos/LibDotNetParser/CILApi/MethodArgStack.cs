using LibDotNetParser.CILApi;
using System.Collections.Generic;

namespace LibDotNetParser;

public class MethodArgStack
{
    public static readonly MethodArgStack ldnull = new() { type = StackItemType.ldnull };
    public StackItemType type
    {
        get
        {
            return MethodArgStackHolder.methodArgStackVals[index].type;
        }
        set
        {
            MethodArgStackHolder.methodArgStackVals[index].type = value;
        }
    }
    public object value
    {
        get { return MethodArgStackHolder.methodArgStackVals[index].value; }
        set
        {
            if (value == null)
                throw new System.Exception("Cannot write null to value");
            MethodArgStackHolder.methodArgStackVals[index].value = value;
        }
    }

    public DotNetType ObjectType
    {
        get
        {
            return MethodArgStackHolder.methodArgStackVals[index].ObjectType;
        }
        set
        {
            MethodArgStackHolder.methodArgStackVals[index].ObjectType = value;
        }
    }
    public DotNetMethod ObjectContructor
    {
        get
        {
            return MethodArgStackHolder.methodArgStackVals[index].ObjectContructor;
        }
        set
        {
            MethodArgStackHolder.methodArgStackVals[index].ObjectContructor = value;
        }
    }

    private int index { get; set; }

    public MethodArgStack()
    {
        var i = MethodArgStackHolder.AllocMethodArgStack();
        index = i.Index;
    }

    public override string ToString()
    {
        return type switch
        {
            StackItemType.String => (string)value,
            StackItemType.Int32 => ((int)value).ToString(),
            StackItemType.Int64 => ((ulong)value).ToString(),
            StackItemType.ldnull => "NULL",
            StackItemType.Float32 => ((float)value).ToString(),
            StackItemType.Float64 => ((decimal)value).ToString(),
            StackItemType.Object => "Object: " + ObjectType.FullName,
            StackItemType.Array => "Array",
            StackItemType.ObjectRef => "Object reference to " + ObjectType.FullName,
            StackItemType.MethodPtr => "Method Pointer to " + ((DotNetMethod)value).ToString(),
            _ => "Unknown"
        };
    }
    public static MethodArgStack UInt32(uint value)
    {
        return new MethodArgStack { type = StackItemType.UInt32, value = value };
    }
    public static MethodArgStack Int32(int value)
    {
        return new MethodArgStack { type = StackItemType.Int32, value = value };
    }
    public static MethodArgStack UInt64(ulong value)
    {
        return new MethodArgStack { type = StackItemType.UInt64, value = value };
    }
    public static MethodArgStack Int64(long value)
    {
        return new MethodArgStack { type = StackItemType.Int64, value = value };
    }
    public static MethodArgStack String(string value)
    {
        return new MethodArgStack { type = StackItemType.String, value = value };
    }
    public static MethodArgStack Null()
    {
        return ldnull;
    }
    public static MethodArgStack Float32(float value)
    {
        return new MethodArgStack { type = StackItemType.Float32, value = value };
    }
    public static MethodArgStack Float64(double value)
    {
        return new MethodArgStack { type = StackItemType.Float64, value = value };
    }
    public static MethodArgStack ObjectRef(DotNetType type)
    {
        return new MethodArgStack { type = StackItemType.ObjectRef, ObjectType = type };
    }
    public static MethodArgStack MethodPtr(DotNetMethod method)
    {
        return new MethodArgStack { type = StackItemType.MethodPtr, value = method };
    }
    public static MethodArgStack Bool(bool val)
    {
        return new MethodArgStack { type = StackItemType.Boolean, value = val };
    }

    public static MethodArgStack Array(ArrayRef a)
    {
        return new MethodArgStack { type = StackItemType.Array, value = (int)a.Index };
    }

       
}

internal class MethodArgStackHolder
{
    public static List<MethodArgStackVal> methodArgStackVals = new();
    private static int CurrentIndex;

    public static MethodArgStackVal AllocMethodArgStack()
    {
        var a = new MethodArgStackVal();
        a.Index = CurrentIndex;
        methodArgStackVals.Add(a);
        CurrentIndex++;

        return a;
    }
}
internal class MethodArgStackVal
{
    public StackItemType type;
    public object value;
    public DotNetType ObjectType;
    public DotNetMethod ObjectContructor;

    public int Index;
}
public enum StackItemType
{
    None,
    Boolean,
    Char,
    SByte,
    Byte,
    Int16,
    UInt16,
    Int32,
    UInt32,
    Int64,
    UInt64,
    Float32,
    Float64,
    Decimal,
    String,
    ldnull,
    Object,
    Array,
    ObjectRef,
    MethodPtr,
    IntPtr,
    UIntPtr,
    Any
}