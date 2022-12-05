using LibDotNetParser;
using System;

namespace libDotNetClr;

public static class MathOperations
{
    public enum Operation
    {
        Add,
        Subtract,
        Multiply,
        Divide,
        Remainder,
        Equal,
        NotEqual,
        GreaterThan,
        LessThan,
        GreaterThanEqual,
        LessThanEqual,
        Negate
    }

    private static MethodArgStack ConvertToInt32(MethodArgStack arg)
    {
        return arg.type switch
        {
            StackItemType.Int32 => arg,
            StackItemType.Char => MethodArgStack.Int32((int)(char)arg.value),
            _ => throw new Exception("Unsupported type conversion")
        };
    }

    public static MethodArgStack Op(MethodArgStack arg, Operation op)
    {
        return arg.type switch
        {
            StackItemType.Float32 => OpWithFloat32(arg, arg, op),
            StackItemType.Float64 => OpWithFloat64(arg, arg, op),
            StackItemType.Int32 => OpWithInt32(arg, arg, op),
            StackItemType.Int64 => OpWithInt64(arg, arg, op),
            _ => throw new NotImplementedException()
        };
    }

    public static MethodArgStack Op(MethodArgStack arg1, MethodArgStack arg2, Operation op)
    {
        if (arg1.type == StackItemType.Int32 || arg2.type == StackItemType.Int32)
        {
            // int32 is a special case where types such as 'char' and 'boolean' can be converted to an int32 implicitely
            arg1 = ConvertToInt32(arg1);
            arg2 = ConvertToInt32(arg2);
        }



        if (arg1.type != arg2.type && arg2.type != StackItemType.ldnull) throw new Exception("Inconsistent type definitions");

        return arg1.type switch
        {
            StackItemType.Float32 => OpWithFloat32(arg1, arg2, op),
            StackItemType.Float64 => OpWithFloat64(arg1, arg2, op),
            StackItemType.Int32 => OpWithInt32(arg1, arg2, op),
            StackItemType.Int64 => OpWithInt64(arg1, arg2, op),
            StackItemType.UInt64 => OpWithUInt64(arg1, arg2, op),
            StackItemType.ldnull => OpWithLdNull(arg1, arg2, op),
            StackItemType.Object => OpWithObject(arg1, arg2, op),
            StackItemType.Array => OpWithArray(arg1, arg2, op),
            StackItemType.String => OpWithString(arg1, arg2, op),
            _ => throw new NotImplementedException()
        };
    }
    private static MethodArgStack OpWithString(MethodArgStack arg1, MethodArgStack arg2, Operation op)
    {
        var v1 = arg1.value;
        var v2 = arg2.value;

        return op switch
        {
            Operation.Equal => MethodArgStack.Int32(v1 == v2 ? 1 : 0),
            _ => throw new Exception("Invalid operation")
        };
    }
    private static MethodArgStack OpWithArray(MethodArgStack arg1, MethodArgStack arg2, Operation op)
    {
        var v1 = arg1.value;
        var v2 = arg2.value;

        return op switch
        {
            Operation.Equal => MethodArgStack.Int32(v1 == v2 ? 1 : 0),
            _ => throw new Exception("Invalid operation")
        };
    }

    private static MethodArgStack OpWithObject(MethodArgStack arg1, MethodArgStack arg2, Operation op)
    {
        var v1 = arg1.value;
        var v2 = arg2.value;

        return op switch
        {
            Operation.Equal => MethodArgStack.Int32(v1 == v2 ? 1 : 0),
            _ => throw new Exception("Invalid operation")
        };
    }

    public static MethodArgStack OpWithFloat32(MethodArgStack arg1, MethodArgStack arg2, Operation op)
    {
        var v1 = (float)arg1.value;
        var v2 = (float)arg2.value;

        return op switch
        {
            Operation.Add => MethodArgStack.Float32(v1 + v2),
            Operation.Subtract => MethodArgStack.Float32(v1 - v2),
            Operation.Multiply => MethodArgStack.Float32(v1 * v2),
            Operation.Divide => MethodArgStack.Float32(v1 / v2),
            Operation.Remainder => MethodArgStack.Float32(v1 % v2),
            Operation.Equal => MethodArgStack.Int32(v1 == v2 ? 1 : 0),
            Operation.GreaterThan => MethodArgStack.Int32(v1 > v2 ? 1 : 0),
            Operation.LessThan => MethodArgStack.Int32(v1 < v2 ? 1 : 0),
            Operation.GreaterThanEqual => MethodArgStack.Int32(v1 >= v2 ? 1 : 0),
            Operation.LessThanEqual => MethodArgStack.Int32(v1 <= v2 ? 1 : 0),
            Operation.Negate => MethodArgStack.Float32(-v1),
            _ => throw new Exception("Invalid operation")
        };
    }

    public static MethodArgStack OpWithFloat64(MethodArgStack arg1, MethodArgStack arg2, Operation op)
    {
        var v1 = (double)arg1.value;
        var v2 = (double)arg2.value;

        return op switch
        {
            Operation.Add => MethodArgStack.Float64(v1 + v2),
            Operation.Subtract => MethodArgStack.Float64(v1 - v2),
            Operation.Multiply => MethodArgStack.Float64(v1 * v2),
            Operation.Divide => MethodArgStack.Float64(v1 / v2),
            Operation.Remainder => MethodArgStack.Float64(v1 % v2),
            Operation.Equal => MethodArgStack.Int32(v1 == v2 ? 1 : 0),
            Operation.GreaterThan => MethodArgStack.Int32(v1 > v2 ? 1 : 0),
            Operation.LessThan => MethodArgStack.Int32(v1 < v2 ? 1 : 0),
            Operation.GreaterThanEqual => MethodArgStack.Int32(v1 >= v2 ? 1 : 0),
            Operation.LessThanEqual => MethodArgStack.Int32(v1 <= v2 ? 1 : 0),
            Operation.Negate => MethodArgStack.Float64(-v1),
            _ => throw new Exception("Invalid operation")
        };
    }

    public static MethodArgStack OpWithInt32(MethodArgStack arg1, MethodArgStack arg2, Operation op)
    {
        var v1 = (int)arg1.value;
        var v2 = (int)arg2.value;

        return op switch
        {
            Operation.Add => MethodArgStack.Int32(v1 + v2),
            Operation.Subtract => MethodArgStack.Int32(v1 - v2),
            Operation.Multiply => MethodArgStack.Int32(v1 * v2),
            Operation.Divide => MethodArgStack.Int32(v1 / v2),
            Operation.Remainder => MethodArgStack.Int32(v1 % v2),
            Operation.Equal => MethodArgStack.Int32(v1 == v2 ? 1 : 0),
            Operation.GreaterThan => MethodArgStack.Int32(v1 > v2 ? 1 : 0),
            Operation.LessThan => MethodArgStack.Int32(v1 < v2 ? 1 : 0),
            Operation.GreaterThanEqual => MethodArgStack.Int32(v1 >= v2 ? 1 : 0),
            Operation.LessThanEqual => MethodArgStack.Int32(v1 <= v2 ? 1 : 0),
            Operation.Negate => MethodArgStack.Int32(-v1),
            _ => throw new Exception("Invalid operation")
        };
    }

    public static MethodArgStack OpWithInt64(MethodArgStack arg1, MethodArgStack arg2, Operation op)
    {
        var v1 = (long)arg1.value;
        var v2 = (long)arg2.value;

        return op switch
        {
            Operation.Add => MethodArgStack.Int64(v1 + v2),
            Operation.Subtract => MethodArgStack.Int64(v1 - v2),
            Operation.Multiply => MethodArgStack.Int64(v1 * v2),
            Operation.Divide => MethodArgStack.Int64(v1 / v2),
            Operation.Remainder => MethodArgStack.Int64(v1 % v2),
            Operation.Equal => MethodArgStack.Int32(v1 == v2 ? 1 : 0),
            Operation.GreaterThan => MethodArgStack.Int32(v1 > v2 ? 1 : 0),
            Operation.LessThan => MethodArgStack.Int32(v1 < v2 ? 1 : 0),
            Operation.GreaterThanEqual => MethodArgStack.Int32(v1 >= v2 ? 1 : 0),
            Operation.LessThanEqual => MethodArgStack.Int32(v1 <= v2 ? 1 : 0),
            Operation.Negate => MethodArgStack.Int64(-v1),
            _ => throw new Exception("Invalid operation")
        };
    }


    public static MethodArgStack OpWithUInt64(MethodArgStack arg1, MethodArgStack arg2, Operation op)
    {
        var v1 = (ulong)arg1.value;
        var v2 = (ulong)arg2.value;

        return op switch
        {
            Operation.Add => MethodArgStack.UInt64(v1 + v2),
            Operation.Subtract => MethodArgStack.UInt64(v1 - v2),
            Operation.Multiply => MethodArgStack.UInt64(v1 * v2),
            Operation.Divide => MethodArgStack.UInt64(v1 / v2),
            Operation.Remainder => MethodArgStack.UInt64(v1 % v2),
            Operation.Equal => MethodArgStack.UInt64(v1 == v2 ? (ulong)1 : (ulong)0),
            Operation.GreaterThan => MethodArgStack.UInt64(v1 > v2 ? (ulong)1 : (ulong)0),
            Operation.LessThan => MethodArgStack.UInt64(v1 < v2 ? (ulong)1 : (ulong)0),
            Operation.GreaterThanEqual => MethodArgStack.UInt64(v1 >= v2 ? (ulong)1 : (ulong)0),
            Operation.LessThanEqual => MethodArgStack.UInt64(v1 <= v2 ? (ulong)1 : (ulong)0),
            _ => throw new Exception("Invalid operation")
        };
    }

    public static MethodArgStack OpWithLdNull(MethodArgStack arg1, MethodArgStack arg2, Operation op)
    {
        var v1 = arg1.value;
        var v2 = arg2.value;

        return op switch
        {
            Operation.Equal => MethodArgStack.Int32(v1 == v2 ? 1 : 0),
            _ => throw new Exception("Invalid operation")
        };
    }
}