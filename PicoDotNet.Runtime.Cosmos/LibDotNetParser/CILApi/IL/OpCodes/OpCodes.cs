﻿namespace LibDotNetParser.CILApi.IL;

/// <summary>
/// List of CIL Opcodes
/// </summary>
public static class OpCodes
{
    //This File was generated by a tool that MishaProductions made. OpCodes list is generated from .NET 7

    // List of CIL Opcodes
    // Single opcodes
    public static readonly OpCode[] SingleOpCodes = new OpCode[256]
    {
        new("nop", 0, OpCodeOperandType.InlineNone),
        new("break", 1, OpCodeOperandType.InlineNone),
        new("ldarg.0", 2, OpCodeOperandType.InlineNone),
        new("ldarg.1", 3, OpCodeOperandType.InlineNone),
        new("ldarg.2", 4, OpCodeOperandType.InlineNone),
        new("ldarg.3", 5, OpCodeOperandType.InlineNone),
        new("ldloc.0", 6, OpCodeOperandType.InlineNone),
        new("ldloc.1", 7, OpCodeOperandType.InlineNone),
        new("ldloc.2", 8, OpCodeOperandType.InlineNone),
        new("ldloc.3", 9, OpCodeOperandType.InlineNone),
        new("stloc.0", 10, OpCodeOperandType.InlineNone),
        new("stloc.1", 11, OpCodeOperandType.InlineNone),
        new("stloc.2", 12, OpCodeOperandType.InlineNone),
        new("stloc.3", 13, OpCodeOperandType.InlineNone),
        new("ldarg.s", 14, OpCodeOperandType.ShortInlineVar),
        new("ldarga.s", 15, OpCodeOperandType.ShortInlineVar),
        new("starg.s", 16, OpCodeOperandType.ShortInlineVar),
        new("ldloc.s", 17, OpCodeOperandType.ShortInlineVar),
        new("ldloca.s", 18, OpCodeOperandType.ShortInlineVar),
        new("stloc.s", 19, OpCodeOperandType.ShortInlineVar),
        new("ldnull", 20, OpCodeOperandType.InlineNone),
        new("ldc.i4.m1", 21, OpCodeOperandType.InlineNone),
        new("ldc.i4.0", 22, OpCodeOperandType.InlineNone),
        new("ldc.i4.1", 23, OpCodeOperandType.InlineNone),
        new("ldc.i4.2", 24, OpCodeOperandType.InlineNone),
        new("ldc.i4.3", 25, OpCodeOperandType.InlineNone),
        new("ldc.i4.4", 26, OpCodeOperandType.InlineNone),
        new("ldc.i4.5", 27, OpCodeOperandType.InlineNone),
        new("ldc.i4.6", 28, OpCodeOperandType.InlineNone),
        new("ldc.i4.7", 29, OpCodeOperandType.InlineNone),
        new("ldc.i4.8", 30, OpCodeOperandType.InlineNone),
        new("ldc.i4.s", 31, OpCodeOperandType.ShortInlineI),
        new("ldc.i4", 32, OpCodeOperandType.InlineI),
        new("ldc.i8", 33, OpCodeOperandType.InlineI8),
        new("ldc.r4", 34, OpCodeOperandType.ShortInlineR),
        new("ldc.r8", 35, OpCodeOperandType.InlineR),
        null,
        new("dup", 37, OpCodeOperandType.InlineNone),
        new("pop", 38, OpCodeOperandType.InlineNone),
        new("jmp", 39, OpCodeOperandType.InlineMethod),
        new("call", 40, OpCodeOperandType.InlineMethod),
        new("calli", 41, OpCodeOperandType.InlineSig),
        new("ret", 42, OpCodeOperandType.InlineNone),
        new("br.s", 43, OpCodeOperandType.ShortInlineBrTarget),
        new("brfalse.s", 44, OpCodeOperandType.ShortInlineBrTarget),
        new("brtrue.s", 45, OpCodeOperandType.ShortInlineBrTarget),
        new("beq.s", 46, OpCodeOperandType.ShortInlineBrTarget),
        new("bge.s", 47, OpCodeOperandType.ShortInlineBrTarget),
        new("bgt.s", 48, OpCodeOperandType.ShortInlineBrTarget),
        new("ble.s", 49, OpCodeOperandType.ShortInlineBrTarget),
        new("blt.s", 50, OpCodeOperandType.ShortInlineBrTarget),
        new("bne.un.s", 51, OpCodeOperandType.ShortInlineBrTarget),
        new("bge.un.s", 52, OpCodeOperandType.ShortInlineBrTarget),
        new("bgt.un.s", 53, OpCodeOperandType.ShortInlineBrTarget),
        new("ble.un.s", 54, OpCodeOperandType.ShortInlineBrTarget),
        new("blt.un.s", 55, OpCodeOperandType.ShortInlineBrTarget),
        new("br", 56, OpCodeOperandType.InlineBrTarget),
        new("brfalse", 57, OpCodeOperandType.InlineBrTarget),
        new("brtrue", 58, OpCodeOperandType.InlineBrTarget),
        new("beq", 59, OpCodeOperandType.InlineBrTarget),
        new("bge", 60, OpCodeOperandType.InlineBrTarget),
        new("bgt", 61, OpCodeOperandType.InlineBrTarget),
        new("ble", 62, OpCodeOperandType.InlineBrTarget),
        new("blt", 63, OpCodeOperandType.InlineBrTarget),
        new("bne.un", 64, OpCodeOperandType.InlineBrTarget),
        new("bge.un", 65, OpCodeOperandType.InlineBrTarget),
        new("bgt.un", 66, OpCodeOperandType.InlineBrTarget),
        new("ble.un", 67, OpCodeOperandType.InlineBrTarget),
        new("blt.un", 68, OpCodeOperandType.InlineBrTarget),
        new("switch", 69, OpCodeOperandType.InlineSwitch),
        new("ldind.i1", 70, OpCodeOperandType.InlineNone),
        new("ldind.u1", 71, OpCodeOperandType.InlineNone),
        new("ldind.i2", 72, OpCodeOperandType.InlineNone),
        new("ldind.u2", 73, OpCodeOperandType.InlineNone),
        new("ldind.i4", 74, OpCodeOperandType.InlineNone),
        new("ldind.u4", 75, OpCodeOperandType.InlineNone),
        new("ldind.i8", 76, OpCodeOperandType.InlineNone),
        new("ldind.i", 77, OpCodeOperandType.InlineNone),
        new("ldind.r4", 78, OpCodeOperandType.InlineNone),
        new("ldind.r8", 79, OpCodeOperandType.InlineNone),
        new("ldind.ref", 80, OpCodeOperandType.InlineNone),
        new("stind.ref", 81, OpCodeOperandType.InlineNone),
        new("stind.i1", 82, OpCodeOperandType.InlineNone),
        new("stind.i2", 83, OpCodeOperandType.InlineNone),
        new("stind.i4", 84, OpCodeOperandType.InlineNone),
        new("stind.i8", 85, OpCodeOperandType.InlineNone),
        new("stind.r4", 86, OpCodeOperandType.InlineNone),
        new("stind.r8", 87, OpCodeOperandType.InlineNone),
        new("add", 88, OpCodeOperandType.InlineNone),
        new("sub", 89, OpCodeOperandType.InlineNone),
        new("mul", 90, OpCodeOperandType.InlineNone),
        new("div", 91, OpCodeOperandType.InlineNone),
        new("div.un", 92, OpCodeOperandType.InlineNone),
        new("rem", 93, OpCodeOperandType.InlineNone),
        new("rem.un", 94, OpCodeOperandType.InlineNone),
        new("and", 95, OpCodeOperandType.InlineNone),
        new("or", 96, OpCodeOperandType.InlineNone),
        new("xor", 97, OpCodeOperandType.InlineNone),
        new("shl", 98, OpCodeOperandType.InlineNone),
        new("shr", 99, OpCodeOperandType.InlineNone),
        new("shr.un", 100, OpCodeOperandType.InlineNone),
        new("neg", 101, OpCodeOperandType.InlineNone),
        new("not", 102, OpCodeOperandType.InlineNone),
        new("conv.i1", 103, OpCodeOperandType.InlineNone),
        new("conv.i2", 104, OpCodeOperandType.InlineNone),
        new("conv.i4", 105, OpCodeOperandType.InlineNone),
        new("conv.i8", 106, OpCodeOperandType.InlineNone),
        new("conv.r4", 107, OpCodeOperandType.InlineNone),
        new("conv.r8", 108, OpCodeOperandType.InlineNone),
        new("conv.u4", 109, OpCodeOperandType.InlineNone),
        new("conv.u8", 110, OpCodeOperandType.InlineNone),
        new("callvirt", 111, OpCodeOperandType.InlineMethod),
        new("cpobj", 112, OpCodeOperandType.InlineType),
        new("ldobj", 113, OpCodeOperandType.InlineType),
        new("ldstr", 114, OpCodeOperandType.InlineString),
        new("newobj", 115, OpCodeOperandType.InlineMethod),
        new("castclass", 116, OpCodeOperandType.InlineType),
        new("isinst", 117, OpCodeOperandType.InlineType),
        new("conv.r.un", 118, OpCodeOperandType.InlineNone),
        null,
        null,
        new("unbox", 121, OpCodeOperandType.InlineType),
        new("throw", 122, OpCodeOperandType.InlineNone),
        new("ldfld", 123, OpCodeOperandType.InlineField),
        new("ldflda", 124, OpCodeOperandType.InlineField),
        new("stfld", 125, OpCodeOperandType.InlineField),
        new("ldsfld", 126, OpCodeOperandType.InlineField),
        new("ldsflda", 127, OpCodeOperandType.InlineField),
        new("stsfld", 128, OpCodeOperandType.InlineField),
        new("stobj", 129, OpCodeOperandType.InlineType),
        new("conv.ovf.i1.un", 130, OpCodeOperandType.InlineNone),
        new("conv.ovf.i2.un", 131, OpCodeOperandType.InlineNone),
        new("conv.ovf.i4.un", 132, OpCodeOperandType.InlineNone),
        new("conv.ovf.i8.un", 133, OpCodeOperandType.InlineNone),
        new("conv.ovf.u1.un", 134, OpCodeOperandType.InlineNone),
        new("conv.ovf.u2.un", 135, OpCodeOperandType.InlineNone),
        new("conv.ovf.u4.un", 136, OpCodeOperandType.InlineNone),
        new("conv.ovf.u8.un", 137, OpCodeOperandType.InlineNone),
        new("conv.ovf.i.un", 138, OpCodeOperandType.InlineNone),
        new("conv.ovf.u.un", 139, OpCodeOperandType.InlineNone),
        new("box", 140, OpCodeOperandType.InlineType),
        new("newarr", 141, OpCodeOperandType.InlineType),
        new("ldlen", 142, OpCodeOperandType.InlineNone),
        new("ldelema", 143, OpCodeOperandType.InlineType),
        new("ldelem.i1", 144, OpCodeOperandType.InlineNone),
        new("ldelem.u1", 145, OpCodeOperandType.InlineNone),
        new("ldelem.i2", 146, OpCodeOperandType.InlineNone),
        new("ldelem.u2", 147, OpCodeOperandType.InlineNone),
        new("ldelem.i4", 148, OpCodeOperandType.InlineNone),
        new("ldelem.u4", 149, OpCodeOperandType.InlineNone),
        new("ldelem.i8", 150, OpCodeOperandType.InlineNone),
        new("ldelem.i", 151, OpCodeOperandType.InlineNone),
        new("ldelem.r4", 152, OpCodeOperandType.InlineNone),
        new("ldelem.r8", 153, OpCodeOperandType.InlineNone),
        new("ldelem.ref", 154, OpCodeOperandType.InlineNone),
        new("stelem.i", 155, OpCodeOperandType.InlineNone),
        new("stelem.i1", 156, OpCodeOperandType.InlineNone),
        new("stelem.i2", 157, OpCodeOperandType.InlineNone),
        new("stelem.i4", 158, OpCodeOperandType.InlineNone),
        new("stelem.i8", 159, OpCodeOperandType.InlineNone),
        new("stelem.r4", 160, OpCodeOperandType.InlineNone),
        new("stelem.r8", 161, OpCodeOperandType.InlineNone),
        new("stelem.ref", 162, OpCodeOperandType.InlineNone),
        new("ldelem", 163, OpCodeOperandType.InlineType),
        new("stelem", 164, OpCodeOperandType.InlineType),
        new("unbox.any", 165, OpCodeOperandType.InlineType),
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        new("conv.ovf.i1", 179, OpCodeOperandType.InlineNone),
        new("conv.ovf.u1", 180, OpCodeOperandType.InlineNone),
        new("conv.ovf.i2", 181, OpCodeOperandType.InlineNone),
        new("conv.ovf.u2", 182, OpCodeOperandType.InlineNone),
        new("conv.ovf.i4", 183, OpCodeOperandType.InlineNone),
        new("conv.ovf.u4", 184, OpCodeOperandType.InlineNone),
        new("conv.ovf.i8", 185, OpCodeOperandType.InlineNone),
        new("conv.ovf.u8", 186, OpCodeOperandType.InlineNone),
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        new("refanyval", 194, OpCodeOperandType.InlineType),
        new("ckfinite", 195, OpCodeOperandType.InlineNone),
        null,
        null,
        new("mkrefany", 198, OpCodeOperandType.InlineType),
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        new("ldtoken", 208, OpCodeOperandType.InlineTok),
        new("conv.u2", 209, OpCodeOperandType.InlineNone),
        new("conv.u1", 210, OpCodeOperandType.InlineNone),
        new("conv.i", 211, OpCodeOperandType.InlineNone),
        new("conv.ovf.i", 212, OpCodeOperandType.InlineNone),
        new("conv.ovf.u", 213, OpCodeOperandType.InlineNone),
        new("add.ovf", 214, OpCodeOperandType.InlineNone),
        new("add.ovf.un", 215, OpCodeOperandType.InlineNone),
        new("mul.ovf", 216, OpCodeOperandType.InlineNone),
        new("mul.ovf.un", 217, OpCodeOperandType.InlineNone),
        new("sub.ovf", 218, OpCodeOperandType.InlineNone),
        new("sub.ovf.un", 219, OpCodeOperandType.InlineNone),
        new("endfinally", 220, OpCodeOperandType.InlineNone),
        new("leave", 221, OpCodeOperandType.InlineBrTarget),
        new("leave.s", 222, OpCodeOperandType.ShortInlineBrTarget),
        new("stind.i", 223, OpCodeOperandType.InlineNone),
        new("conv.u", 224, OpCodeOperandType.InlineNone),
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        new("prefix7", 248, OpCodeOperandType.InlineNone),
        new("prefix6", 249, OpCodeOperandType.InlineNone),
        new("prefix5", 250, OpCodeOperandType.InlineNone),
        new("prefix4", 251, OpCodeOperandType.InlineNone),
        new("prefix3", 252, OpCodeOperandType.InlineNone),
        new("prefix2", 253, OpCodeOperandType.InlineNone),
        new("prefix1", 254, OpCodeOperandType.InlineNone),
        new("prefixref", 255, OpCodeOperandType.InlineNone),
    };


    // Multi opcodes

    public static readonly OpCode[] MultiOpCodes = new OpCode[256]
    {
        new("arglist", 0, OpCodeOperandType.InlineNone, true),
        new("ceq", 1, OpCodeOperandType.InlineNone, true),
        new("cgt", 2, OpCodeOperandType.InlineNone, true),
        new("cgt.un", 3, OpCodeOperandType.InlineNone, true),
        new("clt", 4, OpCodeOperandType.InlineNone, true),
        new("clt.un", 5, OpCodeOperandType.InlineNone, true),
        new("ldftn", 6, OpCodeOperandType.InlineMethod, true),
        new("ldvirtftn", 7, OpCodeOperandType.InlineMethod, true),
        null,
        new("ldarg", 9, OpCodeOperandType.InlineVar, true),
        new("ldarga", 10, OpCodeOperandType.InlineVar, true),
        new("starg", 11, OpCodeOperandType.InlineVar, true),
        new("ldloc", 12, OpCodeOperandType.InlineVar, true),
        new("ldloca", 13, OpCodeOperandType.InlineVar, true),
        new("stloc", 14, OpCodeOperandType.InlineVar, true),
        new("localloc", 15, OpCodeOperandType.InlineNone, true),
        null,
        new("endfilter", 17, OpCodeOperandType.InlineNone, true),
        new("unaligned.", 18, OpCodeOperandType.ShortInlineI, true),
        new("volatile.", 19, OpCodeOperandType.InlineNone, true),
        new("tail.", 20, OpCodeOperandType.InlineNone, true),
        new("initobj", 21, OpCodeOperandType.InlineType, true),
        new("constrained.", 22, OpCodeOperandType.InlineType, true),
        new("cpblk", 23, OpCodeOperandType.InlineNone, true),
        new("initblk", 24, OpCodeOperandType.InlineNone, true),
        null,
        new("rethrow", 26, OpCodeOperandType.InlineNone, true),
        null,
        new("sizeof", 28, OpCodeOperandType.InlineType, true),
        new("refanytype", 29, OpCodeOperandType.InlineNone, true),
        new("readonly.", 30, OpCodeOperandType.InlineNone, true),
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
    };


    // OpCode enum
    public enum OpCodesList : ushort
    {
        Add = 88,
        Add_Ovf = 214,
        Add_Ovf_Un = 215,
        And = 95,
        Arglist = 65024,
        Beq = 59,
        Beq_S = 46,
        Bge = 60,
        Bge_S = 47,
        Bge_Un = 65,
        Bge_Un_S = 52,
        Bgt = 61,
        Bgt_S = 48,
        Bgt_Un = 66,
        Bgt_Un_S = 53,
        Ble = 62,
        Ble_S = 49,
        Ble_Un = 67,
        Ble_Un_S = 54,
        Blt = 63,
        Blt_S = 50,
        Blt_Un = 68,
        Blt_Un_S = 55,
        Bne_Un = 64,
        Bne_Un_S = 51,
        Box = 140,
        Br = 56,
        Br_S = 43,
        Break = 1,
        Brfalse = 57,
        Brfalse_S = 44,
        Brtrue = 58,
        Brtrue_S = 45,
        Call = 40,
        Calli = 41,
        Callvirt = 111,
        Castclass = 116,
        Ceq = 65025,
        Cgt = 65026,
        Cgt_Un = 65027,
        Ckfinite = 195,
        Clt = 65028,
        Clt_Un = 65029,
        Constrained = 65046,
        Conv_I = 211,
        Conv_I1 = 103,
        Conv_I2 = 104,
        Conv_I4 = 105,
        Conv_I8 = 106,
        Conv_Ovf_I = 212,
        Conv_Ovf_I_Un = 138,
        Conv_Ovf_I1 = 179,
        Conv_Ovf_I1_Un = 130,
        Conv_Ovf_I2 = 181,
        Conv_Ovf_I2_Un = 131,
        Conv_Ovf_I4 = 183,
        Conv_Ovf_I4_Un = 132,
        Conv_Ovf_I8 = 185,
        Conv_Ovf_I8_Un = 133,
        Conv_Ovf_U = 213,
        Conv_Ovf_U_Un = 139,
        Conv_Ovf_U1 = 180,
        Conv_Ovf_U1_Un = 134,
        Conv_Ovf_U2 = 182,
        Conv_Ovf_U2_Un = 135,
        Conv_Ovf_U4 = 184,
        Conv_Ovf_U4_Un = 136,
        Conv_Ovf_U8 = 186,
        Conv_Ovf_U8_Un = 137,
        Conv_R_Un = 118,
        Conv_R4 = 107,
        Conv_R8 = 108,
        Conv_U = 224,
        Conv_U1 = 210,
        Conv_U2 = 209,
        Conv_U4 = 109,
        Conv_U8 = 110,
        Cpblk = 65047,
        Cpobj = 112,
        Div = 91,
        Div_Un = 92,
        Dup = 37,
        Endfilter = 65041,
        Endfinally = 220,
        Initblk = 65048,
        Initobj = 65045,
        Isinst = 117,
        Jmp = 39,
        Ldarg = 65033,
        Ldarg_0 = 2,
        Ldarg_1 = 3,
        Ldarg_2 = 4,
        Ldarg_3 = 5,
        Ldarg_S = 14,
        Ldarga = 65034,
        Ldarga_S = 15,
        Ldc_I4 = 32,
        Ldc_I4_0 = 22,
        Ldc_I4_1 = 23,
        Ldc_I4_2 = 24,
        Ldc_I4_3 = 25,
        Ldc_I4_4 = 26,
        Ldc_I4_5 = 27,
        Ldc_I4_6 = 28,
        Ldc_I4_7 = 29,
        Ldc_I4_8 = 30,
        Ldc_I4_M1 = 21,
        Ldc_I4_S = 31,
        Ldc_I8 = 33,
        Ldc_R4 = 34,
        Ldc_R8 = 35,
        Ldelem = 163,
        Ldelem_I = 151,
        Ldelem_I1 = 144,
        Ldelem_I2 = 146,
        Ldelem_I4 = 148,
        Ldelem_I8 = 150,
        Ldelem_R4 = 152,
        Ldelem_R8 = 153,
        Ldelem_Ref = 154,
        Ldelem_U1 = 145,
        Ldelem_U2 = 147,
        Ldelem_U4 = 149,
        Ldelema = 143,
        Ldfld = 123,
        Ldflda = 124,
        Ldftn = 65030,
        Ldind_I = 77,
        Ldind_I1 = 70,
        Ldind_I2 = 72,
        Ldind_I4 = 74,
        Ldind_I8 = 76,
        Ldind_R4 = 78,
        Ldind_R8 = 79,
        Ldind_Ref = 80,
        Ldind_U1 = 71,
        Ldind_U2 = 73,
        Ldind_U4 = 75,
        Ldlen = 142,
        Ldloc = 65036,
        Ldloc_0 = 6,
        Ldloc_1 = 7,
        Ldloc_2 = 8,
        Ldloc_3 = 9,
        Ldloc_S = 17,
        Ldloca = 65037,
        Ldloca_S = 18,
        Ldnull = 20,
        Ldobj = 113,
        Ldsfld = 126,
        Ldsflda = 127,
        Ldstr = 114,
        Ldtoken = 208,
        Ldvirtftn = 65031,
        Leave = 221,
        Leave_S = 222,
        Localloc = 65039,
        Mkrefany = 198,
        Mul = 90,
        Mul_Ovf = 216,
        Mul_Ovf_Un = 217,
        Neg = 101,
        Newarr = 141,
        Newobj = 115,
        Nop = 0,
        Not = 102,
        Or = 96,
        Pop = 38,
        Prefix1 = 254,
        Prefix2 = 253,
        Prefix3 = 252,
        Prefix4 = 251,
        Prefix5 = 250,
        Prefix6 = 249,
        Prefix7 = 248,
        Prefixref = 255,
        Readonly = 65054,
        Refanytype = 65053,
        Refanyval = 194,
        Rem = 93,
        Rem_Un = 94,
        Ret = 42,
        Rethrow = 65050,
        Shl = 98,
        Shr = 99,
        Shr_Un = 100,
        Sizeof = 65052,
        Starg = 65035,
        Starg_S = 16,
        Stelem = 164,
        Stelem_I = 155,
        Stelem_I1 = 156,
        Stelem_I2 = 157,
        Stelem_I4 = 158,
        Stelem_I8 = 159,
        Stelem_R4 = 160,
        Stelem_R8 = 161,
        Stelem_Ref = 162,
        Stfld = 125,
        Stind_I = 223,
        Stind_I1 = 82,
        Stind_I2 = 83,
        Stind_I4 = 84,
        Stind_I8 = 85,
        Stind_R4 = 86,
        Stind_R8 = 87,
        Stind_Ref = 81,
        Stloc = 65038,
        Stloc_0 = 10,
        Stloc_1 = 11,
        Stloc_2 = 12,
        Stloc_3 = 13,
        Stloc_S = 19,
        Stobj = 129,
        Stsfld = 128,
        Sub = 89,
        Sub_Ovf = 218,
        Sub_Ovf_Un = 219,
        Switch = 69,
        Tailcall = 65044,
        Throw = 122,
        Unaligned = 65042,
        Unbox = 121,
        Unbox_Any = 165,
        Volatile = 65043,
        Xor = 97,
    }
}