using LibDotNetParser.CILApi;
using LibDotNetParser.CILApi.IL;

namespace LibDotNetParser;

/// <summary>
/// Converts ILInstruction[] to a string
/// </summary>
public class ILFormater
{
    ILInstruction[] insts;
    public ILFormater(ILInstruction[] insts)
    {
        this.insts = insts;
    }

    public string Format()
    {
        var output = "";
        foreach (var item in insts)
        {
            output += $"IL_{item.Position.ToString("X4")}: {item.OpCodeName}";
            output += item.Operand switch
            {
                string @string => $" {@string}\"\n",
                InlineMethodOperandData me => $" {me.NameSpace}.{me.ClassName}.{me.FunctionName}()\n",
                int i => $" {i}\n",
                byte b => $" {b}\n",
                _ => $"\n"
            };
        }
        return output;
    }
}