
ulong decodeToMCInst_4_constprop_0_isra_0
                (uint param_1,undefined4 param_2,ulong param_3,undefined8 param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  bool bVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  long lVar10;
  undefined8 uVar11;
  ulong uVar12;
  uint uVar13;
  ulong uVar14;
  ulong uVar15;
  undefined1 *puVar16;
  
  uVar14 = param_3 & 0xffffffff;
  uVar7 = (uint)param_3;
  uVar5 = (uint)(uVar14 >> 0x10);
  switch(param_2) {
  case 1:
    MCOperand_CreateReg0
              (param_4,*(undefined4 *)(MatrixIndexGPR32_12_15DecoderTable + (uVar14 >> 0xd & 3) * 4)
              );
    MCOperand_CreateImm0(param_4,param_3 & 0xf);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 2:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0
              (param_4,*(undefined4 *)(MatrixIndexGPR32_12_15DecoderTable + (uVar14 >> 0xd & 3) * 4)
              );
    MCOperand_CreateImm0(param_4,uVar14 >> 5 & 0xf);
    break;
  case 3:
    MCOperand_CreateImm0(param_4,param_3 & 0xff);
    break;
  case 4:
    MCOperand_CreateReg0
              (param_4,*(undefined4 *)(MatrixIndexGPR32_12_15DecoderTable + (uVar14 >> 0xd & 3) * 4)
              );
    MCOperand_CreateImm0(param_4,param_3 & 0xf);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 5:
    MCOperand_CreateReg0
              (param_4,*(undefined4 *)(MatrixZATileDecoderTable + (uVar14 >> 3 & 1) * 4 + 4));
    MCOperand_CreateReg0
              (param_4,*(undefined4 *)(MatrixIndexGPR32_12_15DecoderTable + (uVar14 >> 0xd & 3) * 4)
              );
    MCOperand_CreateImm0(param_4,param_3 & 7);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 6:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0
              (param_4,*(undefined4 *)(MatrixZATileDecoderTable + (uVar14 >> 8 & 1) * 4 + 4));
    MCOperand_CreateReg0
              (param_4,*(undefined4 *)(MatrixIndexGPR32_12_15DecoderTable + (uVar14 >> 0xd & 3) * 4)
              );
    MCOperand_CreateImm0(param_4,uVar14 >> 5 & 7);
    break;
  case 7:
    MCOperand_CreateReg0
              (param_4,*(undefined4 *)(MatrixZATileDecoderTable + (uVar14 >> 3 & 1) * 4 + 4));
    MCOperand_CreateReg0
              (param_4,*(undefined4 *)(MatrixIndexGPR32_12_15DecoderTable + (uVar14 >> 0xd & 3) * 4)
              );
    MCOperand_CreateImm0(param_4,param_3 & 7);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar14 >> 5 & 0x1f);
    if (iVar6 == 0) {
      return 0;
    }
    goto LAB_001c87c4;
  case 8:
    MCOperand_CreateReg0
              (param_4,*(undefined4 *)(MatrixZATileDecoderTable + (param_3 & 3) * 4 + 0xc));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 0xd & 7) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 9:
    MCOperand_CreateReg0
              (param_4,*(undefined4 *)(MatrixZATileDecoderTable + (uVar14 >> 2 & 3) * 4 + 0xc));
    MCOperand_CreateReg0
              (param_4,*(undefined4 *)(MatrixIndexGPR32_12_15DecoderTable + (uVar14 >> 0xd & 3) * 4)
              );
    MCOperand_CreateImm0(param_4,param_3 & 3);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 10:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0
              (param_4,*(undefined4 *)(MatrixZATileDecoderTable + (uVar14 >> 7 & 3) * 4 + 0xc));
    MCOperand_CreateReg0
              (param_4,*(undefined4 *)(MatrixIndexGPR32_12_15DecoderTable + (uVar14 >> 0xd & 3) * 4)
              );
    MCOperand_CreateImm0(param_4,uVar14 >> 5 & 3);
    break;
  case 0xb:
    MCOperand_CreateReg0
              (param_4,*(undefined4 *)(MatrixZATileDecoderTable + (param_3 & 3) * 4 + 0xc));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 0xd & 7) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0xc:
    MCOperand_CreateReg0
              (param_4,*(undefined4 *)(MatrixZATileDecoderTable + (uVar14 >> 2 & 3) * 4 + 0xc));
    MCOperand_CreateReg0
              (param_4,*(undefined4 *)(MatrixIndexGPR32_12_15DecoderTable + (uVar14 >> 0xd & 3) * 4)
              );
    MCOperand_CreateImm0(param_4,param_3 & 3);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar14 >> 5 & 0x1f);
    if (iVar6 == 0) {
      return 0;
    }
    goto LAB_001c87c4;
  case 0xd:
    MCOperand_CreateReg0
              (param_4,*(undefined4 *)(MatrixZATileDecoderTable + (param_3 & 7) * 4 + 0x1c));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 0xd & 7) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0xe:
    MCOperand_CreateReg0
              (param_4,*(undefined4 *)(MatrixZATileDecoderTable + (uVar14 >> 1 & 7) * 4 + 0x1c));
    MCOperand_CreateReg0
              (param_4,*(undefined4 *)(MatrixIndexGPR32_12_15DecoderTable + (uVar14 >> 0xd & 3) * 4)
              );
    MCOperand_CreateImm0(param_4,param_3 & 1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0xf:
    MCOperand_CreateReg0
              (param_4,*(undefined4 *)(MatrixZATileDecoderTable + (param_3 & 0xf) * 4 + 0x3c));
    MCOperand_CreateReg0
              (param_4,*(undefined4 *)(MatrixIndexGPR32_12_15DecoderTable + (uVar14 >> 0xd & 3) * 4)
              );
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x10:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0
              (param_4,*(undefined4 *)(MatrixZATileDecoderTable + (uVar14 >> 6 & 7) * 4 + 0x1c));
    MCOperand_CreateReg0
              (param_4,*(undefined4 *)(MatrixIndexGPR32_12_15DecoderTable + (uVar14 >> 0xd & 3) * 4)
              );
    MCOperand_CreateImm0(param_4,uVar14 >> 5 & 1);
    break;
  case 0x11:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0
              (param_4,*(undefined4 *)(MatrixZATileDecoderTable + (uVar14 >> 5 & 0xf) * 4 + 0x3c));
    MCOperand_CreateReg0
              (param_4,*(undefined4 *)(MatrixIndexGPR32_12_15DecoderTable + (uVar14 >> 0xd & 3) * 4)
              );
    break;
  case 0x12:
    MCOperand_CreateReg0
              (param_4,*(undefined4 *)(MatrixZATileDecoderTable + (param_3 & 7) * 4 + 0x1c));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 0xd & 7) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x13:
    MCOperand_CreateReg0
              (param_4,*(undefined4 *)(MatrixZATileDecoderTable + (uVar14 >> 1 & 7) * 4 + 0x1c));
    MCOperand_CreateReg0
              (param_4,*(undefined4 *)(MatrixIndexGPR32_12_15DecoderTable + (uVar14 >> 0xd & 3) * 4)
              );
    MCOperand_CreateImm0(param_4,param_3 & 1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar14 >> 5 & 0x1f);
    if (iVar6 == 0) {
      return 0;
    }
    goto LAB_001c87c4;
  case 0x14:
    MCOperand_CreateReg0
              (param_4,*(undefined4 *)(MatrixIndexGPR32_12_15DecoderTable + (uVar14 >> 0xd & 3) * 4)
              );
    MCOperand_CreateImm0(param_4,param_3 & 0xf);
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0x15:
    MCOperand_CreateReg0
              (param_4,*(undefined4 *)(MatrixZATileDecoderTable + (param_3 & 0xf) * 4 + 0x3c));
    MCOperand_CreateReg0
              (param_4,*(undefined4 *)(MatrixIndexGPR32_12_15DecoderTable + (uVar14 >> 0xd & 3) * 4)
              );
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar14 >> 5 & 0x1f);
    if (iVar6 == 0) {
      return 0;
    }
LAB_001c87c4:
    uVar7 = 1;
    if (iVar6 != 1) {
      uVar7 = param_1;
    }
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    return (ulong)uVar7;
  case 0x16:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x17:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x18:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x19:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x1a:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,8 - ((uint)(uVar14 >> 5) & 7));
    break;
  case 0x1b:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,0x10 - ((uint)(uVar14 >> 5) & 0xf));
    break;
  case 0x1c:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,0x20 - ((uint)(uVar14 >> 5) & 0x1f));
    break;
  case 0x1d:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,uVar14 >> 5 & 7);
    break;
  case 0x1e:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,uVar14 >> 5 & 0xf);
    break;
  case 0x1f:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,uVar14 >> 5 & 0x1f);
    break;
  case 0x20:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x21:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,0x40 - ((uint)(uVar14 >> 5) & 0x1f | (uVar7 & 0x400000) >> 0x11));
    break;
  case 0x22:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 5) & 0x1f | (uVar7 & 0x400000) >> 0x11);
    break;
  case 0x23:
    uVar5 = (uint)(uVar14 >> 5) & 0x3f;
    uVar7 = uVar5 ^ 0x3f | ((uint)(uVar14 >> 0x11) & 1) << 6;
    if (uVar7 == 0) {
      return 0;
    }
    if (((1 << (ulong)(0x1fU - (int)LZCOUNT(uVar7) & 0x1f)) - 1U & (uVar5 ^ 0xffffffff)) == 0) {
      return 0;
    }
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    iVar6 = MCInst_getOpcode(param_4);
    if (iVar6 != 0x68b) {
      MCOperand_CreateReg0(param_4,uVar1);
    }
    MCOperand_CreateImm0(param_4,uVar14 >> 5 & 0x1fff);
    break;
  case 0x24:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 0x10 & 0xf) * 4));
    if ((uVar7 >> 0xd & 1) != 0) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar14 >> 5 & 0xff);
    MCOperand_CreateImm0(param_4,0);
    break;
  case 0x25:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 0x10 & 0xf) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 5 & 0xff);
    MCOperand_CreateImm0(param_4,uVar7 >> 10 & 8);
    break;
  case 0x26:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 0x10 & 0xf) * 4));
    if ((uVar7 >> 0xd & 1) != 0) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar14 >> 5 & 0xff);
    MCOperand_CreateImm0(param_4,0);
    break;
  case 0x27:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 0x10 & 0xf) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 5 & 0xff);
    MCOperand_CreateImm0(param_4,uVar7 >> 10 & 8);
    break;
  case 0x28:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 0x10 & 0xf) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 5 & 0xff);
    break;
  case 0x29:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 0x10 & 0xf) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 5 & 0xff);
    MCOperand_CreateImm0(param_4,uVar7 >> 10 & 8);
    break;
  case 0x2a:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 0x10 & 0xf) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 5 & 0xff);
    MCOperand_CreateImm0(param_4,uVar7 >> 10 & 8);
    break;
  case 0x2b:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 0x10 & 0xf) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 5 & 0xff);
    MCOperand_CreateImm0(param_4,uVar7 >> 10 & 8);
    break;
  case 0x2c:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 0x10 & 0xf) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 5 & 0xff);
    MCOperand_CreateImm0(param_4,uVar7 >> 10 & 8);
    break;
  case 0x2d:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x2e:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 10) & 7 | (uVar7 & 0x1f0000) >> 0xd);
    break;
  case 0x2f:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZZDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 10) & 7 | (uVar7 & 0x1f0000) >> 0xd);
    break;
  case 0x30:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x16 & 3);
    break;
  case 0x31:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0x14) & 1 | (uVar7 & 0xc00000) >> 0x15);
    break;
  case 0x32:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0x13) & 3 | (uVar7 & 0xc00000) >> 0x14);
    break;
  case 0x33:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0x12) & 7 | (uVar7 & 0xc00000) >> 0x13);
    break;
  case 0x34:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0x11) & 0xf | (uVar7 & 0xc00000) >> 0x12);
    break;
  case 0x35:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZZDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x36:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x37:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,8 - (uVar5 & 7));
    break;
  case 0x38:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,0x10 - (uVar5 & 0xf));
    break;
  case 0x39:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,0x20 - (uVar5 & 0x1f));
    break;
  case 0x3a:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,0x40 - (uVar5 & 0x1f | (uVar7 & 0x400000) >> 0x11));
    break;
  case 0x3b:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x3c:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    iVar6 = *(int *)(GPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 8) {
      iVar6 = 7;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0x3d:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x3e:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x3f:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x40:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0x41:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x42:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    uVar12 = uVar14 >> 5 & 0x1f;
    uVar15 = uVar12 | 0xffffffffffffffe0;
    if ((uVar7 >> 5 & 0x10) == 0) {
      uVar15 = uVar12;
    }
    MCOperand_CreateImm0(param_4,uVar15);
    uVar15 = uVar14 >> 0x10 & 0x1f;
    uVar14 = uVar15 | 0xffffffffffffffe0;
    if ((uVar7 >> 0x10 & 0x10) == 0) {
      uVar14 = uVar15;
    }
    MCOperand_CreateImm0(param_4,uVar14);
    break;
  case 0x43:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    uVar15 = uVar14 >> 0x10 & 0x1f;
    uVar14 = uVar15 | 0xffffffffffffffe0;
    if ((uVar7 >> 0x10 & 0x10) == 0) {
      uVar14 = uVar15;
    }
    MCOperand_CreateImm0(param_4,uVar14);
    break;
  case 0x44:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    uVar12 = uVar14 >> 5 & 0x1f;
    uVar15 = uVar12 | 0xffffffffffffffe0;
    if ((uVar7 >> 5 & 0x10) == 0) {
      uVar15 = uVar12;
    }
    MCOperand_CreateImm0(param_4,uVar15);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x45:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x46:
    iVar6 = *(int *)(GPR64DecoderTable + (param_3 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar14 >> 0x10 & 0x1f);
    if (iVar6 == 0) {
      return 0;
    }
    uVar5 = 1;
    if (iVar6 != 1) {
      uVar5 = param_1;
    }
    uVar15 = uVar14 >> 5 & 0x3f;
    uVar14 = uVar15 | 0xffffffffffffffc0;
    if ((uVar7 >> 5 & 0x20) == 0) {
      uVar14 = uVar15;
    }
    MCOperand_CreateImm0(param_4,uVar14);
    return (ulong)uVar5;
  case 0x47:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (param_3 & 0x1f) * 4));
    uVar15 = uVar14 >> 5 & 0x3f;
    uVar14 = uVar15 | 0xffffffffffffffc0;
    if ((uVar7 >> 5 & 0x20) == 0) {
      uVar14 = uVar15;
    }
    MCOperand_CreateImm0(param_4,uVar14);
    break;
  case 0x48:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    uVar15 = uVar14 >> 0x10 & 0x1f;
    uVar14 = uVar15 | 0xffffffffffffffe0;
    if ((uVar7 >> 0x10 & 0x10) == 0) {
      uVar14 = uVar15;
    }
    MCOperand_CreateImm0(param_4,uVar14);
    break;
  case 0x49:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    uVar12 = uVar14 >> 5 & 0x1f;
    uVar15 = uVar12 | 0xffffffffffffffe0;
    if ((uVar7 >> 5 & 0x10) == 0) {
      uVar15 = uVar12;
    }
    MCOperand_CreateImm0(param_4,uVar15);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x4a:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x4b:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (param_3 & 0xf) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 5 & 0xf) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 0x10 & 0xf) * 4));
    break;
  case 0x4c:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (param_3 & 0xf) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 5 & 0xf) * 4));
    break;
  case 0x4d:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,8 - (uVar5 & 7));
    break;
  case 0x4e:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,0x10 - (uVar5 & 0xf));
    break;
  case 0x4f:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,0x20 - (uVar5 & 0x1f));
    break;
  case 0x50:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x10 & 7);
    break;
  case 0x51:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x10 & 0xf);
    break;
  case 0x52:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x10 & 0x1f);
    break;
  case 0x53:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,0x40 - (uVar5 & 0x1f | (uVar7 & 0x400000) >> 0x11));
    break;
  case 0x54:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar5 & 0x1f | (uVar7 & 0x400000) >> 0x11);
    break;
  case 0x55:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR8DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x56:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x57:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x58:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR8DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x59:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x5a:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    iVar6 = *(int *)(GPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 8) {
      iVar6 = 7;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0x5b:
    uVar1 = *(undefined4 *)(FPR8DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x5c:
    uVar1 = *(undefined4 *)(FPR16DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x5d:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZZDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x5e:
    uVar1 = *(undefined4 *)(GPR32DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x5f:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x60:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x61:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x62:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 99:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 100:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0x65:
    uVar1 = *(undefined4 *)(FPR32DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x66:
    uVar1 = *(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x67:
    uVar1 = *(undefined4 *)(GPR64DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x68:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 5 & 0x1f);
    MCOperand_CreateImm0(param_4,(uVar14 >> 0x10 & 0xf) + 1);
    break;
  case 0x69:
    uVar1 = *(undefined4 *)(GPR64DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,uVar14 >> 5 & 0x1f);
    MCOperand_CreateImm0(param_4,(uVar14 >> 0x10 & 0xf) + 1);
    break;
  case 0x6a:
    uVar1 = *(undefined4 *)(GPR32DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,uVar14 >> 5 & 0x1f);
    MCOperand_CreateImm0(param_4,(uVar14 >> 0x10 & 0xf) + 1);
    break;
  case 0x6b:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,uVar14 >> 5 & 0x1f);
    MCOperand_CreateImm0(param_4,(uVar14 >> 0x10 & 0xf) + 1);
    break;
  case 0x6c:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 0xf) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x6d:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (param_3 & 0xf) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x6e:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (param_3 & 0xf) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    uVar15 = uVar14 >> 0x10 & 0x1f;
    uVar14 = uVar15 | 0xffffffffffffffe0;
    if ((uVar7 >> 0x10 & 0x10) == 0) {
      uVar14 = uVar15;
    }
    MCOperand_CreateImm0(param_4,uVar14);
    break;
  case 0x6f:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (param_3 & 0xf) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 0xf) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 5 & 0xf) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 0x10 & 0xf) * 4));
    break;
  case 0x70:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (param_3 & 0xf) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 0xf) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 5 & 0xf) * 4));
    break;
  case 0x71:
    uVar1 = *(undefined4 *)(PPRDecoderTable + (param_3 & 0xf) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 0xf) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 5 & 0xf) * 4));
    MCOperand_CreateReg0(param_4,uVar1);
    break;
  case 0x72:
    uVar1 = *(undefined4 *)(PPRDecoderTable + (param_3 & 0xf) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 0xf) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 5 & 0xf) * 4));
    break;
  case 0x73:
    uVar1 = *(undefined4 *)(PPRDecoderTable + (param_3 & 0xf) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 5 & 0xf) * 4));
    MCOperand_CreateReg0(param_4,uVar1);
    break;
  case 0x74:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (param_3 & 0xf) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 5 & 0x1f);
    break;
  case 0x75:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (param_3 & 0xf) * 4));
    break;
  case 0x76:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 0xf) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 5 & 0xf) * 4));
    break;
  case 0x77:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (param_3 & 0xf) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0xe & 0x7f);
    break;
  case 0x78:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (param_3 & 0xf) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x79:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (param_3 & 0xf) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x7a:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x7b:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x7c:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (param_3 & 0xf) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 0xf) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 5 & 0xf) * 4));
    MCOperand_CreateReg0
              (param_4,*(undefined4 *)
                        (MatrixIndexGPR32_12_15DecoderTable + (uVar14 >> 0x10 & 3) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x17 & 1);
    break;
  case 0x7d:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (param_3 & 0xf) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 0xf) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 5 & 0xf) * 4));
    MCOperand_CreateReg0
              (param_4,*(undefined4 *)
                        (MatrixIndexGPR32_12_15DecoderTable + (uVar14 >> 0x10 & 3) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x16 & 3);
    break;
  case 0x7e:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (param_3 & 0xf) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 0xf) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 5 & 0xf) * 4));
    MCOperand_CreateReg0
              (param_4,*(undefined4 *)
                        (MatrixIndexGPR32_12_15DecoderTable + (uVar14 >> 0x10 & 3) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0x14) & 1 | (uVar7 & 0xc00000) >> 0x15);
    break;
  case 0x7f:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (param_3 & 0xf) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 0xf) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 5 & 0xf) * 4));
    MCOperand_CreateReg0
              (param_4,*(undefined4 *)
                        (MatrixIndexGPR32_12_15DecoderTable + (uVar14 >> 0x10 & 3) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0x13) & 3 | (uVar7 & 0xc00000) >> 0x14);
    break;
  case 0x80:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 0xf) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 5 & 0xf) * 4));
    break;
  case 0x81:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 5 & 0xf) * 4));
    break;
  case 0x82:
    uVar1 = *(undefined4 *)(GPR64DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 5 & 0xf) * 4));
    MCOperand_CreateReg0(param_4,uVar1);
    break;
  case 0x83:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 5 & 0xf) * 4));
    break;
  case 0x84:
    uVar1 = *(undefined4 *)(GPR32DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 5 & 0xf) * 4));
    MCOperand_CreateReg0(param_4,uVar1);
    break;
  case 0x85:
    break;
  case 0x86:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    if ((uVar7 >> 0xd & 1) != 0) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar14 >> 5 & 0xff);
    MCOperand_CreateImm0(param_4,0);
    break;
  case 0x87:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,uVar14 >> 5 & 0xff);
    MCOperand_CreateImm0(param_4,uVar7 >> 10 & 8);
    break;
  case 0x88:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,uVar14 >> 5 & 0xff);
    MCOperand_CreateImm0(param_4,uVar7 >> 10 & 8);
    break;
  case 0x89:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,uVar14 >> 5 & 0xff);
    MCOperand_CreateImm0(param_4,uVar7 >> 10 & 8);
    break;
  case 0x8a:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    uVar15 = uVar14 >> 5 & 0xff;
    uVar14 = uVar15 | 0xffffffffffffff00;
    if ((uVar7 >> 5 & 0x80) == 0) {
      uVar14 = uVar15;
    }
    MCOperand_CreateImm0(param_4,uVar14);
    break;
  case 0x8b:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,uVar14 >> 5 & 0xff);
    break;
  case 0x8c:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    if ((uVar7 >> 0xd & 1) != 0) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar14 >> 5 & 0xff);
    MCOperand_CreateImm0(param_4,0);
    break;
  case 0x8d:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 5 & 0xff);
    MCOperand_CreateImm0(param_4,uVar7 >> 10 & 8);
    break;
  case 0x8e:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 5 & 0xff);
    MCOperand_CreateImm0(param_4,uVar7 >> 10 & 8);
    break;
  case 0x8f:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 5 & 0xff);
    MCOperand_CreateImm0(param_4,uVar7 >> 10 & 8);
    break;
  case 0x90:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 5 & 0xff);
    break;
  case 0x91:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 0x10 & 7) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0x13) & 3 | (uVar7 & 0x400000) >> 0x14);
    break;
  case 0x92:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 10 & 3);
    break;
  case 0x93:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 0x10 & 7) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x13 & 3);
    break;
  case 0x94:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 0x10 & 0xf) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x14 & 1);
    break;
  case 0x95:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 0x10 & 7) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xb) & 1 | (uVar7 & 0x180000) >> 0x12);
    break;
  case 0x96:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 0x10 & 0xf) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xb) & 1 | (uVar7 & 0x100000) >> 0x13);
    break;
  case 0x97:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 0x10 & 7) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x13 & 3);
    MCOperand_CreateImm0(param_4,uVar14 >> 10 & 3);
    break;
  case 0x98:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 0x10 & 0xf) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x14 & 1);
    MCOperand_CreateImm0(param_4,uVar14 >> 10 & 3);
    break;
  case 0x99:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,uVar1);
    break;
  case 0x9a:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 0x10 & 7) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xb) & 1 | (uVar7 & 0x180000) >> 0x12);
    break;
  case 0x9b:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 0x10 & 0xf) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xb) & 1 | (uVar7 & 0x100000) >> 0x13);
    break;
  case 0x9c:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 10 & 1);
    break;
  case 0x9d:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x9e:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 0x10 & 7) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0x13) & 3 | (uVar7 & 0x400000) >> 0x14);
    break;
  case 0x9f:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 0x10 & 7) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x13 & 3);
    break;
  case 0xa0:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 0x10 & 0xf) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x14 & 1);
    break;
  case 0xa1:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    break;
  case 0xa2:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x10 & 7);
    break;
  case 0xa3:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x10 & 0xf);
    break;
  case 0xa4:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x10 & 0x1f);
    break;
  case 0xa5:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar5 & 0x1f | (uVar7 & 0x400000) >> 0x11);
    break;
  case 0xa6:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0xd & 3);
    break;
  case 0xa7:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x10 & 1);
    break;
  case 0xa8:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (param_3 & 0xf) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0xa9:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x10 & 7);
    break;
  case 0xaa:
    uVar1 = *(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,uVar14 >> 5 & 1);
    break;
  case 0xab:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0xac:
    MCOperand_CreateImm0(param_4,param_3 & 0xf);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0xad:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (param_3 & 0xf) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    uVar7 = (uVar7 & 0x3f0000) >> 0xd;
    uVar15 = (ulong)((uint)(uVar14 >> 10) & 7 | uVar7);
    uVar14 = uVar15 | 0xfffffffffffffe00;
    if ((uVar7 & 0x100) == 0) {
      uVar14 = uVar15;
    }
    MCOperand_CreateImm0(param_4,uVar14);
    break;
  case 0xae:
    MCOperand_CreateImm0(param_4,param_3 & 0xf);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    uVar15 = uVar14 >> 0x10 & 0x3f;
    uVar14 = uVar15 | 0xffffffffffffffc0;
    if ((uVar7 >> 0x10 & 0x20) == 0) {
      uVar14 = uVar15;
    }
    MCOperand_CreateImm0(param_4,uVar14);
    break;
  case 0xaf:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    uVar7 = (uVar7 & 0x3f0000) >> 0xd;
    uVar15 = (ulong)((uint)(uVar14 >> 10) & 7 | uVar7);
    uVar14 = uVar15 | 0xfffffffffffffe00;
    if ((uVar7 & 0x100) == 0) {
      uVar14 = uVar15;
    }
    MCOperand_CreateImm0(param_4,uVar14);
    break;
  case 0xb0:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0xb1:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x10 & 0x1f);
    break;
  case 0xb2:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    MCOperand_CreateImm0(param_4,uVar14 >> 0x10 & 0x3f);
    break;
  case 0xb3:
    MCOperand_CreateImm0(param_4,param_3 & 0xf);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    if ((uVar5 & 0x1f) == 0x1f) {
      return 0;
    }
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (ulong)(uVar5 & 0x1f) * 4));
    break;
  case 0xb4:
    MCOperand_CreateImm0(param_4,param_3 & 0xf);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x10 & 0x1f);
    break;
  case 0xb5:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    if ((uVar5 & 0x1f) == 0x1f) {
      return 0;
    }
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (ulong)(uVar5 & 0x1f) * 4));
    break;
  case 0xb6:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    uVar15 = uVar14 >> 0x10 & 0xf;
    uVar14 = uVar15 | 0xfffffffffffffff0;
    if ((uVar7 >> 0x10 & 8) == 0) {
      uVar14 = uVar15;
    }
    MCOperand_CreateImm0(param_4,uVar14);
    break;
  case 0xb7:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZPRDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0xb8:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZZDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    if ((uVar5 & 0x1f) == 0x1f) {
      return 0;
    }
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (ulong)(uVar5 & 0x1f) * 4));
    break;
  case 0xb9:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZZDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    uVar15 = uVar14 >> 0x10 & 0xf;
    uVar14 = uVar15 | 0xfffffffffffffff0;
    if ((uVar7 >> 0x10 & 8) == 0) {
      uVar14 = uVar15;
    }
    MCOperand_CreateImm0(param_4,uVar14);
    break;
  case 0xba:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZZZDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    if ((uVar5 & 0x1f) == 0x1f) {
      return 0;
    }
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (ulong)(uVar5 & 0x1f) * 4));
    break;
  case 0xbb:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZZZDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    uVar15 = uVar14 >> 0x10 & 0xf;
    uVar14 = uVar15 | 0xfffffffffffffff0;
    if ((uVar7 >> 0x10 & 8) == 0) {
      uVar14 = uVar15;
    }
    MCOperand_CreateImm0(param_4,uVar14);
    break;
  case 0xbc:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZZZZDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    if ((uVar5 & 0x1f) == 0x1f) {
      return 0;
    }
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (ulong)(uVar5 & 0x1f) * 4));
    break;
  case 0xbd:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(ZZZZDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(PPRDecoderTable + (uVar14 >> 10 & 7) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    uVar15 = uVar14 >> 0x10 & 0xf;
    uVar14 = uVar15 | 0xfffffffffffffff0;
    if ((uVar7 >> 0x10 & 8) == 0) {
      uVar14 = uVar15;
    }
    MCOperand_CreateImm0(param_4,uVar14);
    break;
  case 0xbe:
    uVar15 = uVar14 >> 5 & 0x1f;
    uVar5 = MCInst_getOpcode(param_4);
    uVar7 = uVar7 & 0x1f;
    uVar12 = uVar14 >> 10 & 0x1f;
    if (0x14cb < uVar5) {
      return 0;
    }
    if (uVar5 < 0x1454) {
      if (uVar5 < 0xcee) {
        if (uVar5 < 0xceb) {
          if (uVar5 == 0xcb4) goto LAB_001cad7c;
          if (uVar5 < 0xcb5) {
            if (uVar5 == 0xcb3) goto LAB_001caca8;
            if (0xcb1 < uVar5) goto switchD_001c6370_caseD_1457;
            if (uVar5 < 0xcaf) {
              return 0;
            }
          }
          else if (0xcb7 < uVar5) {
            if (uVar5 != 0xcb8) {
              return 0;
            }
            goto switchD_001c6370_caseD_1457;
          }
        }
        goto switchD_001c6370_caseD_1454;
      }
      if (uVar5 == 0xde5) goto LAB_001cad7c;
      if (0xde5 < uVar5) {
        if (uVar5 < 0xde9) goto switchD_001c6370_caseD_1454;
        if (uVar5 != 0xde9) {
          return 0;
        }
switchD_001c6370_caseD_1457:
        goto LAB_001cae90;
      }
      if (uVar5 == 0xcee) goto switchD_001c6370_caseD_1457;
      if (uVar5 != 0xde4) {
        return 0;
      }
LAB_001caca8:
      MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (ulong)uVar7 * 4));
      MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + uVar12 * 4));
      if (*(int *)(GPR64DecoderTable + uVar15 * 4) == 9) goto LAB_001cad40;
      MCOperand_CreateReg0(param_4);
      goto LAB_001cacf0;
    }
    uVar14 = uVar14 >> 0x10 & 0x1f;
    switch(uVar5) {
    case 0x1454:
    case 0x1455:
    case 0x1456:
    case 0x1458:
    case 0x1459:
    case 0x145a:
switchD_001c6370_caseD_1454:
      break;
    case 0x1457:
    case 0x145b:
      goto switchD_001c6370_caseD_1457;
    case 0x145c:
    case 0x145d:
    case 0x145e:
    case 0x145f:
    case 0x1466:
    case 0x1467:
    case 0x1468:
    case 0x1469:
    case 0x146a:
    case 0x146b:
    case 0x146c:
    case 0x146d:
    case 0x146e:
    case 0x146f:
    case 0x1470:
    case 0x1471:
    case 0x1472:
    case 0x1473:
    case 0x1474:
    case 0x1475:
    case 0x1476:
    case 0x1477:
    case 0x1478:
    case 0x1479:
    case 0x147a:
    case 0x147b:
    case 0x147c:
    case 0x147d:
    case 0x147e:
    case 0x147f:
    case 0x1480:
    case 0x1481:
    case 0x1482:
    case 0x1483:
    case 0x1484:
    case 0x1485:
    case 0x1486:
    case 0x1487:
    case 0x1488:
    case 0x1489:
    case 0x148a:
    case 0x148b:
    case 0x148c:
    case 0x148d:
    case 0x148e:
    case 0x148f:
    case 0x1490:
    case 0x1491:
    case 0x1492:
    case 0x1493:
    case 0x1494:
    case 0x1495:
    case 0x1496:
    case 0x1497:
    case 0x1498:
    case 0x1499:
    case 0x149a:
    case 0x149b:
    case 0x149c:
    case 0x149d:
    case 0x149e:
    case 0x149f:
    case 0x14a0:
    case 0x14a1:
    case 0x14a2:
    case 0x14a3:
    case 0x14a4:
    case 0x14a5:
    case 0x14a6:
    case 0x14a7:
    case 0x14a8:
    case 0x14a9:
    case 0x14aa:
    case 0x14ab:
    case 0x14ac:
    case 0x14ad:
    case 0x14ae:
    case 0x14af:
    case 0x14b0:
    case 0x14b1:
    case 0x14b2:
    case 0x14b3:
    case 0x14b4:
    case 0x14b5:
    case 0x14b6:
    case 0x14b7:
    case 0x14b8:
    case 0x14b9:
    case 0x14ba:
    case 0x14bb:
    case 0x14bc:
    case 0x14bd:
    case 0x14be:
    case 0x14bf:
    case 0x14c0:
    case 0x14c1:
    case 0x14c2:
    case 0x14c3:
    case 0x14c4:
    case 0x14c5:
      return 0;
    case 0x1460:
    case 0x14c6:
      MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + uVar14 * 4));
      MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (ulong)uVar7 * 4));
      MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + uVar12 * 4));
      if (*(int *)(GPR64DecoderTable + uVar15 * 4) == 9) goto LAB_001cad40;
      MCOperand_CreateReg0(param_4);
      goto LAB_001cad5c;
    case 0x1461:
    case 0x14c7:
      MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + uVar14 * 4));
LAB_001cad7c:
      MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (ulong)uVar7 * 4));
      MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + uVar12 * 4));
      goto LAB_001cada4;
    case 0x1462:
    case 0x1463:
    case 0x1464:
    case 0x14c8:
    case 0x14c9:
    case 0x14ca:
      MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + uVar14 * 4));
      break;
    case 0x1465:
    case 0x14cb:
      MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + uVar14 * 4));
LAB_001cae90:
      MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (ulong)uVar7 * 4));
LAB_001cada4:
      iVar6 = *(int *)(GPR64DecoderTable + uVar15 * 4);
      if (iVar6 != 9) goto LAB_001cad44;
      MCOperand_CreateReg0(param_4,5);
      goto LAB_001cad5c;
    default:
      return 0;
    }
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (ulong)uVar7 * 4));
    if (*(int *)(GPR64DecoderTable + uVar15 * 4) == 9) {
LAB_001cad40:
      iVar6 = 5;
LAB_001cad44:
      MCOperand_CreateReg0(param_4,iVar6);
      if (uVar5 != 0xcb3 && uVar5 != 0xde4) goto LAB_001cad5c;
    }
    else {
      MCOperand_CreateReg0(param_4);
LAB_001cad5c:
      if (uVar5 != 0xcb4 && uVar5 != 0xde5) break;
    }
LAB_001cacf0:
    if (uVar7 == (uint)uVar12) {
      return 1;
    }
    break;
  case 0xbf:
    if ((uVar7 >> 0x10 & 1) != 0) {
      return 0;
    }
    uVar5 = uVar7 >> 0x10 & 0x1f;
    iVar6 = DecodeWSeqPairsClassRegisterClass_part_0(param_4,uVar5);
    if (iVar6 == 0) {
      return 0;
    }
    uVar13 = 1;
    if (iVar6 != 1) {
      uVar13 = param_1;
    }
    iVar6 = DecodeWSeqPairsClassRegisterClass_part_0(param_4,uVar5);
    if (iVar6 == 0) {
      return 0;
    }
    uVar5 = 1;
    if (iVar6 != 1) {
      uVar5 = uVar13;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar6 = DecodeWSeqPairsClassRegisterClass_part_0(param_4,uVar7 & 0x1f);
    if (iVar6 == 0) {
      return 0;
    }
    uVar7 = 1;
    if (iVar6 != 1) {
      uVar7 = uVar5;
    }
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar14 >> 5 & 0x1f);
    if (iVar6 == 0) {
      return 0;
    }
    goto LAB_001caa6c;
  case 0xc0:
    uVar1 = *(undefined4 *)(GPR32DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (param_3 & 0x1f) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0xc1:
    uVar5 = (uint)(uVar14 >> 0x16) & 3;
    uVar13 = (uint)(uVar14 >> 10) & 0x3f;
    uVar9 = MCInst_getOpcode(param_4);
    if (uVar9 == 0x6ab) goto LAB_001ca638;
    if (uVar9 < 0x6ac) {
      if (uVar9 != 0x3f6) {
        if (0x3f6 < uVar9) {
          if (uVar9 != 0x48f) {
            if (uVar9 < 0x490) {
              if (uVar9 != 0x431) {
                if (uVar9 < 0x432) {
                  if (uVar9 == 0x428) goto LAB_001ca638;
                  if (uVar9 != 0x42a) {
                    return 0;
                  }
                }
                else if (uVar9 != 0x433) {
                  return 0;
                }
                goto LAB_001c6254;
              }
            }
            else if (uVar9 != 0x492) {
              if ((uVar9 != 0x493) && (uVar9 != 0x490)) {
                return 0;
              }
              goto LAB_001c6254;
            }
          }
          goto LAB_001ca638;
        }
        if (uVar9 != 999) {
          if ((uVar9 != 0x3f3) && (uVar9 != 0x3e4)) {
            return 0;
          }
          goto LAB_001cac74;
        }
      }
LAB_001ca9cc:
      if (uVar5 == 3) {
        return 0;
      }
      goto LAB_001c6254;
    }
    if (uVar9 == 0x14eb) {
LAB_001cac74:
      if (uVar5 == 3) {
        return 0;
      }
LAB_001ca638:
      if (uVar13 >> 5 != 0) {
        return 0;
      }
      puVar16 = GPR32DecoderTable;
    }
    else {
      if (0x14eb < uVar9) {
        if (uVar9 != 0x14f2) {
          if ((uVar9 != 0x14f5) && (uVar9 != 0x14ee)) {
            return 0;
          }
          goto LAB_001ca9cc;
        }
        goto LAB_001cac74;
      }
      if (uVar9 == 0xea5) goto LAB_001ca638;
      if (uVar9 < 0xea6) {
        if (uVar9 == 0x6bd) goto LAB_001ca638;
        if ((uVar9 != 0x6bf) && (uVar9 != 0x6ac)) {
          return 0;
        }
      }
      else {
        if (uVar9 == 0xeac) goto LAB_001ca638;
        if ((uVar9 & 0xfffffff7) != 0xea6) {
          return 0;
        }
      }
LAB_001c6254:
      puVar16 = GPR64DecoderTable;
    }
    MCOperand_CreateReg0(param_4,*(undefined4 *)(puVar16 + (ulong)(uVar7 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(puVar16 + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(puVar16 + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar13 | uVar5 << 6);
    break;
  case 0xc2:
    if (4 < ((uint)(uVar14 >> 10) & 7)) {
      return 0;
    }
    uVar5 = MCInst_getOpcode(param_4);
    uVar15 = (ulong)(uVar7 & 0x1f);
    uVar12 = uVar14 >> 5 & 0x1f;
    uVar14 = uVar14 >> 0x10 & 0x1f;
    if (uVar5 == 0x14ec) {
LAB_001c6194:
      MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + uVar15 * 4));
      iVar6 = *(int *)(GPR32DecoderTable + uVar12 * 4);
      if (iVar6 == 8) {
        iVar6 = 7;
      }
LAB_001c61c4:
      MCOperand_CreateReg0(param_4,iVar6);
      MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + uVar14 * 4));
    }
    else if (uVar5 < 0x14ed) {
      if (uVar5 == 0x3f4) {
LAB_001cb138:
        iVar6 = *(int *)(GPR32DecoderTable + uVar15 * 4);
        if (iVar6 == 8) {
          iVar6 = 7;
        }
        MCOperand_CreateReg0(param_4,iVar6);
        iVar6 = *(int *)(GPR32DecoderTable + uVar12 * 4);
        if (iVar6 == 8) {
          iVar6 = 7;
        }
        goto LAB_001c61c4;
      }
      if (uVar5 < 0x3f5) {
        if (uVar5 != 1000) {
          if (uVar5 == 0x3e9) goto LAB_001ca944;
          if (uVar5 != 0x3e5) {
            return 0;
          }
          goto LAB_001c6194;
        }
LAB_001cb0fc:
        MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + uVar15 * 4));
        DecodeGPR64spRegisterClass_part_0(param_4,uVar12);
        MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + uVar14 * 4));
      }
      else {
        if (uVar5 != 0x3f7) {
          if (uVar5 != 0x3f8) {
            return 0;
          }
          goto LAB_001cafd8;
        }
LAB_001cb204:
        DecodeGPR64spRegisterClass_part_0(param_4,uVar15);
        DecodeGPR64spRegisterClass_part_0(param_4,uVar12);
        MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + uVar14 * 4));
      }
    }
    else {
      if (uVar5 == 0x14f3) goto LAB_001cb138;
      if (uVar5 < 0x14f4) {
        if (uVar5 == 0x14ef) goto LAB_001cb0fc;
        if (uVar5 != 0x14f0) {
          return 0;
        }
LAB_001ca944:
        MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + uVar15 * 4));
        DecodeGPR64spRegisterClass_part_0(param_4,uVar12);
        MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + uVar14 * 4));
      }
      else {
        if (uVar5 == 0x14f6) goto LAB_001cb204;
        if (uVar5 != 0x14f7) {
          return 0;
        }
LAB_001cafd8:
        DecodeGPR64spRegisterClass_part_0(param_4,uVar15);
        DecodeGPR64spRegisterClass_part_0(param_4,uVar12);
        MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + uVar14 * 4));
      }
    }
    MCOperand_CreateImm0(param_4,uVar7 >> 10 & 0x3f);
    break;
  case 0xc3:
    uVar5 = uVar7 & 0x1f;
    uVar15 = uVar14 >> 10 & 0x1f;
    uVar9 = (uint)(uVar14 >> 0xf) & 0x7f;
    uVar12 = uVar14 >> 5 & 0x1f;
    uVar8 = MCInst_getOpcode(param_4);
    uVar13 = uVar9 | 0xffffff80;
    if ((uVar7 >> 0xf & 0x40) == 0) {
      uVar13 = uVar9;
    }
    if (0xd29 < uVar8) {
      if (0xd < uVar8 - 0x147b) {
        if (0x22 < uVar8 - 0x1466) {
          return 0;
        }
        goto LAB_001cab30;
      }
      if ((0x36dbUL >> ((ulong)(uVar8 - 0x147b) & 0x3f) & 1) != 0) goto LAB_001ca540;
LAB_001ca570:
      if (0x22 < uVar8 - 0x1466) {
        return 0;
      }
LAB_001cab30:
                    /* WARNING: Could not recover jumptable at 0x001cab44. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      uVar14 = (*(code *)((long)*(short *)(&DAT_0028e614 + (ulong)(uVar8 - 0x1466) * 2) * 4 +
                         0x1cab48))();
      return uVar14;
    }
    if (uVar8 < 0xd19) {
      if (uVar8 < 0xcff) {
        return 0;
      }
    }
    else if ((0x1b6dbUL >> ((ulong)(uVar8 - 0xd19) & 0x3f) & 1) != 0) {
LAB_001ca540:
      iVar6 = *(int *)(GPR64DecoderTable + uVar12 * 4);
      if (iVar6 == 9) {
        iVar6 = 5;
      }
      MCOperand_CreateReg0(param_4,iVar6);
      if (0xd29 < uVar8) goto LAB_001ca570;
    }
    switch(uVar8) {
    case 0xcff:
    case 0xd18:
    case 0xd19:
    case 0xd1a:
      puVar16 = FPR64DecoderTable;
      break;
    case 0xd00:
    case 0xd1b:
    case 0xd1c:
    case 0xd1d:
      puVar16 = FPR128DecoderTable;
      break;
    case 0xd01:
    case 0xd21:
    case 0xd22:
    case 0xd23:
      puVar16 = FPR32DecoderTable;
      break;
    case 0xd02:
    case 0xd24:
      bVar4 = false;
      goto LAB_001cae1c;
    case 0xd03:
    case 0xd1e:
    case 0xd27:
      bVar4 = false;
      goto LAB_001cade8;
    case 0xd04:
    case 0xd05:
    case 0xd06:
    case 0xd07:
    case 0xd08:
    case 0xd09:
    case 0xd0a:
    case 0xd0b:
    case 0xd0c:
    case 0xd0d:
    case 0xd0e:
    case 0xd0f:
    case 0xd10:
    case 0xd11:
    case 0xd12:
    case 0xd13:
    case 0xd14:
    case 0xd15:
    case 0xd16:
    case 0xd17:
      return 0;
    case 0xd1f:
    case 0xd20:
    case 0xd28:
    case 0xd29:
      bVar4 = true;
LAB_001cade8:
      puVar16 = GPR64DecoderTable;
      goto LAB_001cadf4;
    case 0xd25:
    case 0xd26:
      bVar4 = true;
LAB_001cae1c:
      puVar16 = GPR32DecoderTable;
LAB_001cadf4:
      MCOperand_CreateReg0(param_4,*(undefined4 *)(puVar16 + (ulong)uVar5 * 4));
      MCOperand_CreateReg0(param_4,*(undefined4 *)(puVar16 + uVar15 * 4));
      goto LAB_001cab78;
    default:
      return 0;
    }
    MCOperand_CreateReg0(param_4,*(undefined4 *)(puVar16 + (ulong)uVar5 * 4));
    bVar4 = false;
    MCOperand_CreateReg0(param_4,*(undefined4 *)(puVar16 + uVar15 * 4));
LAB_001cab78:
    iVar6 = *(int *)(GPR64DecoderTable + uVar12 * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    MCOperand_CreateImm0(param_4,(long)(int)uVar13);
    if (((uVar14 >> 0x16 & 1) != 0 && uVar5 == (uint)uVar15) ||
       ((uVar7 = (uint)uVar12, bVar4 && uVar7 != 0x1f && (uVar5 == uVar7 || uVar7 == (uint)uVar15)))
       ) {
      return 1;
    }
    break;
  case 0xc4:
    if ((uVar7 >> 0x10 & 1) != 0) {
      return 0;
    }
    uVar5 = uVar7 >> 0x10 & 0x1f;
    iVar6 = DecodeXSeqPairsClassRegisterClass_part_0(param_4,uVar5);
    if (iVar6 == 0) {
      return 0;
    }
    uVar13 = 1;
    if (iVar6 != 1) {
      uVar13 = param_1;
    }
    iVar6 = DecodeXSeqPairsClassRegisterClass_part_0(param_4,uVar5);
    if (iVar6 == 0) {
      return 0;
    }
    uVar5 = 1;
    if (iVar6 != 1) {
      uVar5 = uVar13;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar6 = DecodeXSeqPairsClassRegisterClass_part_0(param_4,uVar7 & 0x1f);
    if (iVar6 == 0) {
      return 0;
    }
    uVar7 = 1;
    if (iVar6 != 1) {
      uVar7 = uVar5;
    }
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar14 >> 5 & 0x1f);
    if (iVar6 == 0) {
      return 0;
    }
LAB_001caa6c:
    if (iVar6 == 1) {
      return 1;
    }
    return (ulong)uVar7;
  case 0xc5:
    uVar1 = *(undefined4 *)(GPR64DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (param_3 & 0x1f) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0xc6:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(DDDDDecoderTable + (param_3 & 0x1f) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 199:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(DDDDecoderTable + (param_3 & 0x1f) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 200:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0xc9:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(DDDecoderTable + (param_3 & 0x1f) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0xca:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(QQQQDecoderTable + (param_3 & 0x1f) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0xcb:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(QQQDecoderTable + (param_3 & 0x1f) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0xcc:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0xcd:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(QQDecoderTable + (param_3 & 0x1f) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0xce:
    uVar15 = uVar14 >> 5 & 0x1f;
    iVar6 = *(int *)(GPR64DecoderTable + uVar15 * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(DDDDDecoderTable + (param_3 & 0x1f) * 4));
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar15);
    if (iVar6 == 0) {
      return 0;
    }
    goto LAB_001c3f40;
  case 0xcf:
    uVar15 = uVar14 >> 5 & 0x1f;
    iVar6 = *(int *)(GPR64DecoderTable + uVar15 * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(DDDDecoderTable + (param_3 & 0x1f) * 4));
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar15);
    if (iVar6 == 0) {
      return 0;
    }
    goto LAB_001c3f40;
  case 0xd0:
    uVar15 = uVar14 >> 5 & 0x1f;
    iVar6 = *(int *)(GPR64DecoderTable + uVar15 * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4));
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar15);
    if (iVar6 == 0) {
      return 0;
    }
    goto LAB_001c3f40;
  case 0xd1:
    uVar15 = uVar14 >> 5 & 0x1f;
    iVar6 = *(int *)(GPR64DecoderTable + uVar15 * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(DDDecoderTable + (param_3 & 0x1f) * 4));
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar15);
    if (iVar6 == 0) {
      return 0;
    }
    goto LAB_001c3f40;
  case 0xd2:
    uVar15 = uVar14 >> 5 & 0x1f;
    iVar6 = *(int *)(GPR64DecoderTable + uVar15 * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(QQQQDecoderTable + (param_3 & 0x1f) * 4));
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar15);
    if (iVar6 == 0) {
      return 0;
    }
    goto LAB_001c3f40;
  case 0xd3:
    uVar15 = uVar14 >> 5 & 0x1f;
    iVar6 = *(int *)(GPR64DecoderTable + uVar15 * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(QQQDecoderTable + (param_3 & 0x1f) * 4));
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar15);
    if (iVar6 == 0) {
      return 0;
    }
    goto LAB_001c3f40;
  case 0xd4:
    uVar15 = uVar14 >> 5 & 0x1f;
    iVar6 = *(int *)(GPR64DecoderTable + uVar15 * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4));
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar15);
    if (iVar6 == 0) {
      return 0;
    }
    goto LAB_001c3f40;
  case 0xd5:
    uVar15 = uVar14 >> 5 & 0x1f;
    iVar6 = *(int *)(GPR64DecoderTable + uVar15 * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(QQDecoderTable + (param_3 & 0x1f) * 4));
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar15);
    if (iVar6 == 0) {
      return 0;
    }
    goto LAB_001c3f40;
  case 0xd6:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 10) & 7 | (uVar7 & 0x40000000) >> 0x1b);
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0xd7:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(QQQDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 10) & 7 | (uVar7 & 0x40000000) >> 0x1b);
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0xd8:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xb) & 3 | (uVar7 & 0x40000000) >> 0x1c);
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0xd9:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(QQQDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xb) & 3 | (uVar7 & 0x40000000) >> 0x1c);
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0xda:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xc) & 1 | (uVar7 & 0x40000000) >> 0x1d);
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0xdb:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x1e & 1);
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0xdc:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(QQQDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xc) & 1 | (uVar7 & 0x40000000) >> 0x1d);
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0xdd:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(QQQDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x1e & 1);
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0xde:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(QQDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 10) & 7 | (uVar7 & 0x40000000) >> 0x1b);
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0xdf:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(QQQQDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 10) & 7 | (uVar7 & 0x40000000) >> 0x1b);
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0xe0:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(QQDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xb) & 3 | (uVar7 & 0x40000000) >> 0x1c);
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0xe1:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(QQQQDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xb) & 3 | (uVar7 & 0x40000000) >> 0x1c);
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0xe2:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(QQDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xc) & 1 | (uVar7 & 0x40000000) >> 0x1d);
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0xe3:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(QQDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x1e & 1);
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0xe4:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(QQQQDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xc) & 1 | (uVar7 & 0x40000000) >> 0x1d);
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0xe5:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(QQQQDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x1e & 1);
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0xe6:
    uVar1 = *(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 10) & 7 | (uVar7 & 0x40000000) >> 0x1b);
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0xe7:
    uVar1 = *(undefined4 *)(QQQDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 10) & 7 | (uVar7 & 0x40000000) >> 0x1b);
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0xe8:
    uVar1 = *(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xb) & 3 | (uVar7 & 0x40000000) >> 0x1c);
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0xe9:
    uVar1 = *(undefined4 *)(QQQDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xb) & 3 | (uVar7 & 0x40000000) >> 0x1c);
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0xea:
    uVar1 = *(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xc) & 1 | (uVar7 & 0x40000000) >> 0x1d);
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0xeb:
    uVar1 = *(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,uVar14 >> 0x1e & 1);
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0xec:
    uVar1 = *(undefined4 *)(QQQDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xc) & 1 | (uVar7 & 0x40000000) >> 0x1d);
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0xed:
    uVar1 = *(undefined4 *)(QQQDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,uVar14 >> 0x1e & 1);
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0xee:
    uVar1 = *(undefined4 *)(QQDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 10) & 7 | (uVar7 & 0x40000000) >> 0x1b);
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0xef:
    uVar1 = *(undefined4 *)(QQQQDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 10) & 7 | (uVar7 & 0x40000000) >> 0x1b);
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0xf0:
    uVar1 = *(undefined4 *)(QQDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xb) & 3 | (uVar7 & 0x40000000) >> 0x1c);
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0xf1:
    uVar1 = *(undefined4 *)(QQQQDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xb) & 3 | (uVar7 & 0x40000000) >> 0x1c);
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0xf2:
    uVar1 = *(undefined4 *)(QQDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xc) & 1 | (uVar7 & 0x40000000) >> 0x1d);
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0xf3:
    uVar1 = *(undefined4 *)(QQDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,uVar14 >> 0x1e & 1);
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0xf4:
    uVar1 = *(undefined4 *)(QQQQDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xc) & 1 | (uVar7 & 0x40000000) >> 0x1d);
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0xf5:
    uVar1 = *(undefined4 *)(QQQQDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,uVar14 >> 0x1e & 1);
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0xf6:
    uVar15 = uVar14 >> 5 & 0x1f;
    iVar6 = *(int *)(GPR64DecoderTable + uVar15 * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 10) & 7 | (uVar7 & 0x40000000) >> 0x1b);
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar15);
    if (iVar6 == 0) {
      return 0;
    }
    goto LAB_001c3f40;
  case 0xf7:
    uVar15 = uVar14 >> 5 & 0x1f;
    iVar6 = *(int *)(GPR64DecoderTable + uVar15 * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(QQDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 10) & 7 | (uVar7 & 0x40000000) >> 0x1b);
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar15);
    if (iVar6 == 0) {
      return 0;
    }
    goto LAB_001c3f40;
  case 0xf8:
    uVar15 = uVar14 >> 5 & 0x1f;
    iVar6 = *(int *)(GPR64DecoderTable + uVar15 * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(QQQDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 10) & 7 | (uVar7 & 0x40000000) >> 0x1b);
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar15);
    if (iVar6 == 0) {
      return 0;
    }
    goto LAB_001c3f40;
  case 0xf9:
    uVar15 = uVar14 >> 5 & 0x1f;
    iVar6 = *(int *)(GPR64DecoderTable + uVar15 * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(QQQQDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 10) & 7 | (uVar7 & 0x40000000) >> 0x1b);
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar15);
    if (iVar6 == 0) {
      return 0;
    }
    goto LAB_001c3f40;
  case 0xfa:
    uVar15 = uVar14 >> 5 & 0x1f;
    iVar6 = *(int *)(GPR64DecoderTable + uVar15 * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xb) & 3 | (uVar7 & 0x40000000) >> 0x1c);
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar15);
    if (iVar6 == 0) {
      return 0;
    }
    goto LAB_001c3f40;
  case 0xfb:
    uVar15 = uVar14 >> 5 & 0x1f;
    iVar6 = *(int *)(GPR64DecoderTable + uVar15 * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(QQDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xb) & 3 | (uVar7 & 0x40000000) >> 0x1c);
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar15);
    if (iVar6 == 0) {
      return 0;
    }
    goto LAB_001c3f40;
  case 0xfc:
    uVar15 = uVar14 >> 5 & 0x1f;
    iVar6 = *(int *)(GPR64DecoderTable + uVar15 * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(QQQDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xb) & 3 | (uVar7 & 0x40000000) >> 0x1c);
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar15);
    if (iVar6 == 0) {
      return 0;
    }
    goto LAB_001c3f40;
  case 0xfd:
    uVar15 = uVar14 >> 5 & 0x1f;
    iVar6 = *(int *)(GPR64DecoderTable + uVar15 * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(QQQQDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xb) & 3 | (uVar7 & 0x40000000) >> 0x1c);
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar15);
    if (iVar6 == 0) {
      return 0;
    }
    goto LAB_001c3f40;
  case 0xfe:
    uVar15 = uVar14 >> 5 & 0x1f;
    iVar6 = *(int *)(GPR64DecoderTable + uVar15 * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xc) & 1 | (uVar7 & 0x40000000) >> 0x1d);
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar15);
    if (iVar6 == 0) {
      return 0;
    }
    goto LAB_001c3f40;
  case 0xff:
    uVar15 = uVar14 >> 5 & 0x1f;
    iVar6 = *(int *)(GPR64DecoderTable + uVar15 * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(QQDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xc) & 1 | (uVar7 & 0x40000000) >> 0x1d);
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar15);
    if (iVar6 == 0) {
      return 0;
    }
    goto LAB_001c3f40;
  case 0x100:
    uVar15 = uVar14 >> 5 & 0x1f;
    iVar6 = *(int *)(GPR64DecoderTable + uVar15 * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x1e & 1);
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar15);
    if (iVar6 == 0) {
      return 0;
    }
    goto LAB_001c3f40;
  case 0x101:
    uVar15 = uVar14 >> 5 & 0x1f;
    iVar6 = *(int *)(GPR64DecoderTable + uVar15 * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(QQDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x1e & 1);
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar15);
    if (iVar6 == 0) {
      return 0;
    }
    goto LAB_001c3f40;
  case 0x102:
    uVar15 = uVar14 >> 5 & 0x1f;
    iVar6 = *(int *)(GPR64DecoderTable + uVar15 * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(QQQDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xc) & 1 | (uVar7 & 0x40000000) >> 0x1d);
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar15);
    if (iVar6 == 0) {
      return 0;
    }
    goto LAB_001c3f40;
  case 0x103:
    uVar15 = uVar14 >> 5 & 0x1f;
    iVar6 = *(int *)(GPR64DecoderTable + uVar15 * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(QQQQDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xc) & 1 | (uVar7 & 0x40000000) >> 0x1d);
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar15);
    if (iVar6 == 0) {
      return 0;
    }
    goto LAB_001c3f40;
  case 0x104:
    uVar15 = uVar14 >> 5 & 0x1f;
    iVar6 = *(int *)(GPR64DecoderTable + uVar15 * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(QQQDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x1e & 1);
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar15);
    if (iVar6 == 0) {
      return 0;
    }
    goto LAB_001c3f40;
  case 0x105:
    uVar15 = uVar14 >> 5 & 0x1f;
    iVar6 = *(int *)(GPR64DecoderTable + uVar15 * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(QQQQDecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x1e & 1);
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar15);
    if (iVar6 == 0) {
      return 0;
    }
    goto LAB_001c3f40;
  case 0x106:
    uVar15 = uVar14 >> 5 & 0x1f;
    iVar6 = *(int *)(GPR64DecoderTable + uVar15 * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    uVar1 = *(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 10) & 7 | (uVar7 & 0x40000000) >> 0x1b);
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar15);
    if (iVar6 == 0) {
      return 0;
    }
    goto LAB_001c3f40;
  case 0x107:
    uVar15 = uVar14 >> 5 & 0x1f;
    iVar6 = *(int *)(GPR64DecoderTable + uVar15 * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    uVar1 = *(undefined4 *)(QQDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 10) & 7 | (uVar7 & 0x40000000) >> 0x1b);
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar15);
    if (iVar6 == 0) {
      return 0;
    }
    goto LAB_001c3f40;
  case 0x108:
    uVar15 = uVar14 >> 5 & 0x1f;
    iVar6 = *(int *)(GPR64DecoderTable + uVar15 * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    uVar1 = *(undefined4 *)(QQQDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 10) & 7 | (uVar7 & 0x40000000) >> 0x1b);
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar15);
    if (iVar6 == 0) {
      return 0;
    }
    goto LAB_001c3f40;
  case 0x109:
    uVar15 = uVar14 >> 5 & 0x1f;
    iVar6 = *(int *)(GPR64DecoderTable + uVar15 * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    uVar1 = *(undefined4 *)(QQQQDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 10) & 7 | (uVar7 & 0x40000000) >> 0x1b);
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar15);
    if (iVar6 == 0) {
      return 0;
    }
    goto LAB_001c3f40;
  case 0x10a:
    uVar15 = uVar14 >> 5 & 0x1f;
    iVar6 = *(int *)(GPR64DecoderTable + uVar15 * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    uVar1 = *(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xb) & 3 | (uVar7 & 0x40000000) >> 0x1c);
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar15);
    if (iVar6 == 0) {
      return 0;
    }
    goto LAB_001c3f40;
  case 0x10b:
    uVar15 = uVar14 >> 5 & 0x1f;
    iVar6 = *(int *)(GPR64DecoderTable + uVar15 * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    uVar1 = *(undefined4 *)(QQDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xb) & 3 | (uVar7 & 0x40000000) >> 0x1c);
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar15);
    if (iVar6 == 0) {
      return 0;
    }
    goto LAB_001c3f40;
  case 0x10c:
    uVar15 = uVar14 >> 5 & 0x1f;
    iVar6 = *(int *)(GPR64DecoderTable + uVar15 * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    uVar1 = *(undefined4 *)(QQQDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xb) & 3 | (uVar7 & 0x40000000) >> 0x1c);
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar15);
    if (iVar6 == 0) {
      return 0;
    }
    goto LAB_001c3f40;
  case 0x10d:
    uVar15 = uVar14 >> 5 & 0x1f;
    iVar6 = *(int *)(GPR64DecoderTable + uVar15 * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    uVar1 = *(undefined4 *)(QQQQDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xb) & 3 | (uVar7 & 0x40000000) >> 0x1c);
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar15);
    if (iVar6 == 0) {
      return 0;
    }
    goto LAB_001c3f40;
  case 0x10e:
    uVar15 = uVar14 >> 5 & 0x1f;
    iVar6 = *(int *)(GPR64DecoderTable + uVar15 * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    uVar1 = *(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xc) & 1 | (uVar7 & 0x40000000) >> 0x1d);
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar15);
    if (iVar6 == 0) {
      return 0;
    }
    goto LAB_001c3f40;
  case 0x10f:
    uVar15 = uVar14 >> 5 & 0x1f;
    iVar6 = *(int *)(GPR64DecoderTable + uVar15 * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    uVar1 = *(undefined4 *)(QQDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xc) & 1 | (uVar7 & 0x40000000) >> 0x1d);
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar15);
    if (iVar6 == 0) {
      return 0;
    }
    goto LAB_001c3f40;
  case 0x110:
    uVar15 = uVar14 >> 5 & 0x1f;
    iVar6 = *(int *)(GPR64DecoderTable + uVar15 * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    uVar1 = *(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,uVar14 >> 0x1e & 1);
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar15);
    if (iVar6 == 0) {
      return 0;
    }
    goto LAB_001c3f40;
  case 0x111:
    uVar15 = uVar14 >> 5 & 0x1f;
    iVar6 = *(int *)(GPR64DecoderTable + uVar15 * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    uVar1 = *(undefined4 *)(QQDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,uVar14 >> 0x1e & 1);
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar15);
    if (iVar6 == 0) {
      return 0;
    }
    goto LAB_001c3f40;
  case 0x112:
    uVar15 = uVar14 >> 5 & 0x1f;
    iVar6 = *(int *)(GPR64DecoderTable + uVar15 * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    uVar1 = *(undefined4 *)(QQQDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xc) & 1 | (uVar7 & 0x40000000) >> 0x1d);
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar15);
    if (iVar6 == 0) {
      return 0;
    }
    goto LAB_001c3f40;
  case 0x113:
    uVar15 = uVar14 >> 5 & 0x1f;
    iVar6 = *(int *)(GPR64DecoderTable + uVar15 * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    uVar1 = *(undefined4 *)(QQQQDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xc) & 1 | (uVar7 & 0x40000000) >> 0x1d);
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar15);
    if (iVar6 == 0) {
      return 0;
    }
    goto LAB_001c3f40;
  case 0x114:
    uVar15 = uVar14 >> 5 & 0x1f;
    iVar6 = *(int *)(GPR64DecoderTable + uVar15 * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    uVar1 = *(undefined4 *)(QQQDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,uVar14 >> 0x1e & 1);
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar15);
    if (iVar6 == 0) {
      return 0;
    }
    goto LAB_001c3f40;
  case 0x115:
    uVar15 = uVar14 >> 5 & 0x1f;
    iVar6 = *(int *)(GPR64DecoderTable + uVar15 * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    uVar1 = *(undefined4 *)(QQQQDecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,uVar14 >> 0x1e & 1);
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar15);
    if (iVar6 == 0) {
      return 0;
    }
LAB_001c3f40:
    uVar7 = 1;
    if (iVar6 != 1) {
      uVar7 = param_1;
    }
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    return (ulong)uVar7;
  case 0x116:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x117:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x118:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x13 & 3);
    break;
  case 0x119:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x12 & 7);
    break;
  case 0x11a:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x11 & 0xf);
    break;
  case 0x11b:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x11c:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x11d:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x11e:
    uVar1 = *(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x11f:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x120:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(QQDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x121:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x122:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x123:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x12 & 7);
    break;
  case 0x124:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x11 & 0xf);
    break;
  case 0x125:
    uVar1 = *(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(QQDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x126:
    uVar1 = *(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x127:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x128:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x13 & 3);
    break;
  case 0x129:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(QQQDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x12a:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 299:
    uVar1 = *(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(QQQDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 300:
    uVar1 = *(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x12d:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(QQQQDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x12e:
    uVar1 = *(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(QQQQDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x12f:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x130:
    uVar1 = *(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x131:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR8DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x132:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0xb & 7);
    break;
  case 0x133:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x134:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x14 & 1);
    break;
  case 0x135:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x13 & 3);
    break;
  case 0x136:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x12 & 7);
    break;
  case 0x137:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x11 & 0xf);
    break;
  case 0x138:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x139:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x13a:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x13b:
    uVar1 = *(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x13c:
    uVar1 = *(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,uVar14 >> 0x14 & 1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x13d:
    uVar1 = *(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,uVar14 >> 0x13 & 3);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x13e:
    uVar1 = *(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,uVar14 >> 0x12 & 7);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x13f:
    uVar1 = *(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,uVar14 >> 0x11 & 0xf);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x140:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(QQDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x141:
    uVar1 = *(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x142:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x143:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x13 & 3);
    break;
  case 0x144:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x12 & 7);
    break;
  case 0x145:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x11 & 0xf);
    break;
  case 0x146:
    uVar1 = *(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(QQDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x147:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x148:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x14 & 1);
    break;
  case 0x149:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(QQQDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x14a:
    uVar1 = *(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(QQQDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x14b:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(QQQQDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x14c:
    uVar1 = *(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(QQQQDecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x14d:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR8DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x14e:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0xb & 0xf);
    break;
  case 0x14f:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x150:
    uVar1 = *(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,uVar14 >> 0x14 & 1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0xe & 1);
    break;
  case 0x151:
    uVar1 = *(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,uVar14 >> 0x13 & 3);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0xd & 3);
    break;
  case 0x152:
    uVar1 = *(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,uVar14 >> 0x12 & 7);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0xc & 7);
    break;
  case 0x153:
    uVar1 = *(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,uVar14 >> 0x11 & 0xf);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0xb & 0xf);
    break;
  case 0x154:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 10 & 0x1f) * 4));
    break;
  case 0x155:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x156:
    uVar1 = *(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0xb & 3);
    break;
  case 0x157:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0xc & 1);
    break;
  case 0x158:
    uVar1 = *(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0xb & 3);
    break;
  case 0x159:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0xc & 1);
    break;
  case 0x15a:
    uVar1 = *(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0xc & 3);
    break;
  case 0x15b:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 10 & 0x3f);
    break;
  case 0x15c:
    uVar1 = *(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 0x10 & 0xf) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0x14) & 3 | (uVar7 & 0x800) >> 9);
    break;
  case 0x15d:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 0x10 & 0xf) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0x14) & 3 | (uVar7 & 0x800) >> 9);
    break;
  case 0x15e:
    uVar1 = *(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0x15) & 1 | (uVar7 & 0x800) >> 10);
    break;
  case 0x15f:
    iVar6 = MCInst_getOpcode(param_4);
    if (iVar6 == 0xe48) {
      MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (ulong)(uVar7 & 0x1f) * 4));
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (ulong)(uVar7 & 0x1f) * 4));
    }
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 5) & 0x1f | (uVar7 & 0x70000) >> 0xb);
    iVar6 = MCInst_getOpcode(param_4);
    if (iVar6 != 0xe4b) {
      if (0x3e < iVar6 - 0xe4cU) break;
      uVar14 = 1L << ((ulong)(iVar6 - 0xe4cU) & 0x3f);
      if ((uVar14 & 0x5a00000000000026) == 0) {
        if ((uVar14 & 0x2400000000000009) != 0) {
          uVar11 = 0x108;
          if ((uVar7 >> 0xc & 1) != 0) {
            uVar11 = 0x110;
          }
          MCOperand_CreateImm0(param_4,uVar11);
        }
        break;
      }
    }
    MCOperand_CreateImm0(param_4,(uVar7 >> 0xc & 6) << 2);
    break;
  case 0x160:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,8 - (uVar5 & 7));
    break;
  case 0x161:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,0x10 - (uVar5 & 0xf));
    break;
  case 0x162:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,0x20 - (uVar5 & 0x1f));
    break;
  case 0x163:
    uVar1 = *(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 5) & 0x1f | (uVar7 & 0x70000) >> 0xb);
    MCOperand_CreateImm0(param_4,uVar7 >> 10 & 0x18);
    break;
  case 0x164:
    uVar1 = *(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,8 - (uVar5 & 7));
    break;
  case 0x165:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x10 & 7);
    break;
  case 0x166:
    uVar1 = *(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,0x10 - (uVar5 & 0xf));
    break;
  case 0x167:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x10 & 0xf);
    break;
  case 0x168:
    uVar1 = *(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,0x20 - (uVar5 & 0x1f));
    break;
  case 0x169:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x10 & 0x1f);
    break;
  case 0x16a:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,0x10 - (uVar5 & 7 | 8));
    break;
  case 0x16b:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x10 & 7);
    break;
  case 0x16c:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,0x20 - (uVar5 & 0xf | 0x10));
    break;
  case 0x16d:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x10 & 0xf);
    break;
  case 0x16e:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,0x40 - (uVar5 & 0x1f | 0x20));
    break;
  case 0x16f:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x10 & 0x1f);
    break;
  case 0x170:
    uVar1 = *(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x10 & 7);
    break;
  case 0x171:
    uVar1 = *(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x10 & 0xf);
    break;
  case 0x172:
    uVar1 = *(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x10 & 0x1f);
    break;
  case 0x173:
    uVar1 = *(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 0x10 & 0xf) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0x14) & 3 | (uVar7 & 0x800) >> 9);
    break;
  case 0x174:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 0x10 & 0xf) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0x14) & 3 | (uVar7 & 0x800) >> 9);
    break;
  case 0x175:
    uVar1 = *(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0x15) & 1 | (uVar7 & 0x800) >> 10);
    break;
  case 0x176:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,8 - (uVar5 & 7));
    break;
  case 0x177:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,0x10 - (uVar5 & 0xf));
    break;
  case 0x178:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,0x20 - (uVar5 & 0x1f));
    break;
  case 0x179:
    uVar1 = *(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,8 - (uVar5 & 7));
    break;
  case 0x17a:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x10 & 7);
    break;
  case 0x17b:
    uVar1 = *(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,0x10 - (uVar5 & 0xf));
    break;
  case 0x17c:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x10 & 0xf);
    break;
  case 0x17d:
    uVar1 = *(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,0x20 - (uVar5 & 0x1f));
    break;
  case 0x17e:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x10 & 0x1f);
    break;
  case 0x17f:
    uVar1 = *(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,0x10 - (uVar5 & 7 | 8));
    break;
  case 0x180:
    uVar1 = *(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,0x20 - (uVar5 & 0xf | 0x10));
    break;
  case 0x181:
    uVar1 = *(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,0x40 - (uVar5 & 0x1f | 0x20));
    break;
  case 0x182:
    uVar1 = *(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x10 & 7);
    break;
  case 0x183:
    uVar1 = *(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x10 & 0xf);
    break;
  case 0x184:
    uVar1 = *(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x10 & 0x1f);
    break;
  case 0x185:
    uVar1 = *(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 0x10 & 0xf) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0x14) & 3 | (uVar7 & 0x800) >> 9);
    break;
  case 0x186:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 0x10 & 0xf) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0x14) & 3 | (uVar7 & 0x800) >> 9);
    break;
  case 0x187:
    uVar1 = *(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x15 & 1);
    MCOperand_CreateImm0(param_4,uVar14 >> 0xd & 3);
    break;
  case 0x188:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,0x40 - (uVar5 & 0x3f));
    break;
  case 0x189:
    uVar1 = *(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,0x40 - (uVar5 & 0x3f));
    break;
  case 0x18a:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x10 & 0x3f);
    break;
  case 0x18b:
    uVar1 = *(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0x15) & 1 | (uVar7 & 0x800) >> 10);
    MCOperand_CreateImm0(param_4,uVar14 >> 0xd & 3);
    break;
  case 0x18c:
    uVar1 = *(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x10 & 0x3f);
    break;
  case 0x18d:
    uVar1 = *(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 0x10 & 0xf) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0x14) & 3 | (uVar7 & 0x800) >> 9);
    break;
  case 0x18e:
    uVar1 = *(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0x15) & 1 | (uVar7 & 0x800) >> 10);
    break;
  case 399:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0x15) & 1 | (uVar7 & 0x800) >> 10);
    break;
  case 400:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0x15) & 1 | (uVar7 & 0x800) >> 10);
    break;
  case 0x191:
    uVar1 = *(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 0x10 & 0xf) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0x14) & 3 | (uVar7 & 0x800) >> 9);
    break;
  case 0x192:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0x15) & 1 | (uVar7 & 0x800) >> 10);
    break;
  case 0x193:
    uVar1 = *(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0xb & 1);
    MCOperand_CreateImm0(param_4,uVar14 >> 0xd & 3);
    break;
  case 0x194:
    uVar1 = *(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0xb & 1);
    break;
  case 0x195:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0xb & 1);
    break;
  case 0x196:
    uVar7 = (uVar7 & 0xffffe0) >> 3;
    uVar15 = (ulong)((uint)(uVar14 >> 0x1d) & 3 | uVar7);
    uVar14 = uVar15 | 0xffffffffffe00000;
    if ((uVar7 & 0x100000) == 0) {
      uVar14 = uVar15;
    }
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14);
    break;
  case 0x197:
    if ((uVar7 >> 0x17 & 1) != 0) {
      return 0;
    }
    uVar5 = uVar7 & 0x1f;
    uVar15 = uVar14 >> 5 & 0x1f;
    uVar7 = (uint)(uVar5 == 0x1f) & (uVar7 >> 0x1d ^ 0xffffffff);
    if ((param_3 & 0x80000000) == 0) {
      if (uVar7 == 0) {
        MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (ulong)uVar5 * 4));
      }
      else {
        MCOperand_CreateReg0(param_4,7);
      }
      iVar6 = *(int *)(GPR32DecoderTable + uVar15 * 4);
      if (iVar6 == 8) {
        iVar6 = 7;
      }
      MCOperand_CreateReg0(param_4,iVar6);
    }
    else {
      if (uVar7 == 0) {
        MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (ulong)uVar5 * 4));
      }
      else {
        DecodeGPR64spRegisterClass_part_0(param_4,0x1f);
      }
      iVar6 = *(int *)(GPR64DecoderTable + uVar15 * 4);
      if (iVar6 == 9) {
        iVar6 = 5;
      }
      MCOperand_CreateReg0(param_4,iVar6);
    }
    MCOperand_CreateImm0(param_4,uVar14 >> 10 & 0xfff);
    MCOperand_CreateImm0(param_4,-((uint)(uVar14 >> 0x16) & 3) & 0xc);
    break;
  case 0x198:
    iVar6 = *(int *)(GPR64DecoderTable + (param_3 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar14 >> 5 & 0x1f);
    if (iVar6 == 0) {
      return 0;
    }
    uVar7 = 1;
    if (iVar6 != 1) {
      uVar7 = param_1;
    }
    MCOperand_CreateImm0(param_4,uVar14 >> 0x10 & 0x3f);
    MCOperand_CreateImm0(param_4,uVar14 >> 10 & 0xf);
    return (ulong)uVar7;
  case 0x199:
    uVar15 = (ulong)(uVar7 & 0x1f);
    uVar12 = uVar14 >> 5 & 0x1f;
    if ((param_3 & 0x80000000) == 0) {
      iVar6 = MCInst_getOpcode(param_4);
      if (iVar6 == 0x427) {
        MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + uVar15 * 4));
      }
      else {
        iVar6 = *(int *)(GPR32DecoderTable + uVar15 * 4);
        if (iVar6 == 8) {
          iVar6 = 7;
        }
        MCOperand_CreateReg0(param_4,iVar6);
      }
      MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + uVar12 * 4));
      uVar5 = (uint)(uVar14 >> 10) & 0x3f;
      if (uVar5 == 0x3f) {
        return 0;
      }
      if (((1 << (ulong)(0x1fU - (int)LZCOUNT(uVar5 ^ 0x3f) & 0x1f)) - 1U & (uVar5 ^ 0xffffffff)) ==
          0) {
        return 0;
      }
      uVar15 = (ulong)(uVar7 >> 10) & 0xfff;
    }
    else {
      iVar6 = MCInst_getOpcode(param_4);
      if (iVar6 == 0x429) {
        MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + uVar15 * 4));
      }
      else {
        iVar6 = *(int *)(GPR64DecoderTable + uVar15 * 4);
        if (iVar6 == 9) {
          iVar6 = 5;
        }
        MCOperand_CreateReg0(param_4,iVar6);
      }
      MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + uVar12 * 4));
      uVar5 = (uint)(uVar14 >> 10) & 0x3f;
      uVar15 = uVar14 >> 10 & 0x1fff;
      uVar7 = uVar5 ^ 0x3f | ((uint)(uVar14 >> 0x16) & 1) << 6;
      if (uVar7 == 0) {
        return 0;
      }
      if (((1 << (ulong)(0x1fU - (int)LZCOUNT(uVar7) & 0x1f)) - 1U & (uVar5 ^ 0xffffffff)) == 0) {
        return 0;
      }
    }
    MCOperand_CreateImm0(param_4,uVar15);
    break;
  case 0x19a:
    iVar6 = MCInst_getOpcode(param_4);
    uVar5 = (uVar7 >> 0x15) << 4;
    if (0xe < iVar6 - 0xe52U) {
      return 0;
    }
    uVar15 = 1L << ((ulong)(iVar6 - 0xe52U) & 0x3f);
    if ((uVar15 & 0x400a) == 0) {
      if ((uVar15 & 0x2005) == 0) {
        return 0;
      }
      if ((uVar5 & 0x20) != 0) {
        return 0;
      }
      MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (ulong)(uVar7 & 0x1f) * 4));
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (ulong)(uVar7 & 0x1f) * 4));
    }
    iVar6 = MCInst_getOpcode(param_4);
    if ((iVar6 == 0xe52) || (iVar6 = MCInst_getOpcode(param_4), iVar6 == 0xe53)) {
      uVar11 = MCInst_getOperand(param_4,0);
      MCInst_addOperand2(param_4,uVar11);
    }
    MCOperand_CreateImm0(param_4,uVar14 >> 5 & 0xffff);
    MCOperand_CreateImm0(param_4,uVar5 & 0x30);
    break;
  case 0x19b:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x10 & 0x1f);
    MCOperand_CreateImm0(param_4,uVar14 >> 10 & 0x1f);
    break;
  case 0x19c:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 10 & 0x1f);
    break;
  case 0x19d:
    uVar1 = *(undefined4 *)(GPR32DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x10 & 0x1f);
    MCOperand_CreateImm0(param_4,uVar14 >> 10 & 0x1f);
    break;
  case 0x19e:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x10 & 0x3f);
    MCOperand_CreateImm0(param_4,uVar14 >> 10 & 0x3f);
    break;
  case 0x19f:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 10 & 0x3f);
    break;
  case 0x1a0:
    uVar1 = *(undefined4 *)(GPR64DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x10 & 0x3f);
    MCOperand_CreateImm0(param_4,uVar14 >> 10 & 0x3f);
    break;
  case 0x1a1:
    uVar14 = uVar14 | 0xfffffffffc000000;
    if ((param_3 & 0x2000000) == 0) {
      uVar14 = param_3 & 0x3ffffff;
    }
    MCOperand_CreateImm0(param_4,uVar14);
    break;
  case 0x1a2:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (param_3 & 0x1f) * 4));
    uVar15 = uVar14 >> 5 & 0x7ffff;
    uVar14 = uVar15 | 0xfffffffffff80000;
    if ((uVar7 >> 5 & 0x40000) == 0) {
      uVar14 = uVar15;
    }
    MCOperand_CreateImm0(param_4,uVar14);
    break;
  case 0x1a3:
    uVar12 = uVar14 >> 5 & 0x3fff;
    uVar15 = uVar12 | 0xffffffffffffc000;
    if ((uVar7 >> 5 & 0x2000) == 0) {
      uVar15 = uVar12;
    }
    if ((int)uVar7 < 0) {
      MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (ulong)(uVar7 & 0x1f) * 4));
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (ulong)(uVar7 & 0x1f) * 4));
    }
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0x13) & 0x1f | ((int)uVar7 >> 0x1f) * -0x20);
    MCOperand_CreateImm0(param_4,uVar15);
    break;
  case 0x1a4:
    MCOperand_CreateImm0(param_4,param_3 & 0xf);
    uVar15 = uVar14 >> 5 & 0x7ffff;
    uVar14 = uVar15 | 0xfffffffffff80000;
    if ((uVar7 >> 5 & 0x40000) == 0) {
      uVar14 = uVar15;
    }
    MCOperand_CreateImm0(param_4,uVar14);
    break;
  case 0x1a5:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (param_3 & 0x1f) * 4));
    uVar15 = uVar14 >> 5 & 0x7ffff;
    uVar14 = uVar15 | 0xfffffffffff80000;
    if ((uVar7 >> 5 & 0x40000) == 0) {
      uVar14 = uVar15;
    }
    MCOperand_CreateImm0(param_4,uVar14);
    break;
  case 0x1a6:
    MCOperand_CreateImm0(param_4,uVar14 >> 5 & 0xffff);
    break;
  case 0x1a7:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (param_3 & 0x1f) * 4));
    break;
  case 0x1a8:
    MCOperand_CreateImm0(param_4,uVar14 >> 5 & 0x7f);
    break;
  case 0x1a9:
    MCOperand_CreateImm0(param_4,((ulong)(uVar7 >> 10) & 3) << 2 | 3);
    break;
  case 0x1aa:
    MCOperand_CreateImm0(param_4,uVar14 >> 8 & 0xf);
    break;
  case 0x1ab:
    uVar15 = uVar14 >> 9 & 7;
    lVar10 = lookupSVCRByEncoding(uVar15);
    if (lVar10 == 0) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar15);
    MCOperand_CreateImm0(param_4,uVar14 >> 8 & 1);
    break;
  case 0x1ac:
    uVar7 = (uint)(uVar14 >> 5) & 7 | (uVar7 & 0x70000) >> 0xd;
    if ((uVar7 - 3 < 2) && ((param_3 & 0xe00) != 0)) {
      return 0;
    }
    MCOperand_CreateImm0(param_4,uVar7);
    MCOperand_CreateImm0(param_4,uVar14 >> 8 & 0xf);
    lVar10 = lookupPStateByEncoding(uVar7);
    if (lVar10 == 0) {
      return 0;
    }
    break;
  case 0x1ad:
    MCOperand_CreateImm0(param_4,uVar14 >> 0x10 & 7);
    MCOperand_CreateImm0(param_4,uVar14 >> 0xc & 0xf);
    MCOperand_CreateImm0(param_4,uVar14 >> 8 & 0xf);
    MCOperand_CreateImm0(param_4,uVar14 >> 5 & 7);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (param_3 & 0x1f) * 4));
    break;
  case 0x1ae:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x10 & 7);
    MCOperand_CreateImm0(param_4,uVar14 >> 0xc & 0xf);
    MCOperand_CreateImm0(param_4,uVar14 >> 8 & 0xf);
    MCOperand_CreateImm0(param_4,uVar14 >> 5 & 7);
    break;
  case 0x1af:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x1b0:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (param_3 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0x1b1:
    iVar6 = DecodeSignedLdStInstruction_isra_0(param_4,uVar14);
    if (iVar6 == 0) {
      return 0;
    }
    if (iVar6 == 1) {
      return 1;
    }
    break;
  case 0x1b2:
    uVar7 = uVar7 & 0x1f;
    uVar5 = (uint)(uVar14 >> 5) & 0x1f;
    uVar14 = uVar14 >> 0x10 & 0x1f;
    uVar13 = (uint)uVar14;
    if ((uVar7 == 0x1f || uVar7 == uVar5) || (uVar7 == uVar13 || uVar13 == uVar5)) {
      return 0;
    }
    uVar1 = *(undefined4 *)(GPR64DecoderTable + (ulong)uVar7 * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    if (uVar13 == 0x1f) {
      return 0;
    }
    uVar2 = *(undefined4 *)(GPR64DecoderTable + uVar14 * 4);
    MCOperand_CreateReg0(param_4,uVar2);
    uVar3 = *(undefined4 *)(GPR64DecoderTable + (ulong)uVar5 * 4);
    MCOperand_CreateReg0(param_4,uVar3);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar2);
    MCOperand_CreateReg0(param_4,uVar3);
    break;
  case 0x1b3:
    uVar7 = uVar7 & 0x1f;
    uVar5 = (uint)(uVar14 >> 5) & 0x1f;
    uVar14 = uVar14 >> 0x10 & 0x1f;
    uVar13 = (uint)uVar14;
    if ((uVar7 == 0x1f || uVar7 == uVar5) || (uVar7 == uVar13 || uVar13 == uVar5)) {
      return 0;
    }
    uVar1 = *(undefined4 *)(GPR64DecoderTable + (ulong)uVar7 * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    uVar2 = *(undefined4 *)(GPR64DecoderTable + (ulong)uVar5 * 4);
    MCOperand_CreateReg0(param_4,uVar2);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar2);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + uVar14 * 4));
    break;
  case 0x1b4:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x1b5:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0xc & 0xf);
    break;
  case 0x1b6:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (uVar14 >> 10 & 0x1f) * 4));
    break;
  case 0x1b7:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0x1b8:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (param_3 & 0x1f) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uVar7 & 0x8000) >> 0xf);
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xc) & 1);
    break;
  case 0x1b9:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (param_3 & 0x1f) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uVar7 & 0x8000) >> 0xf);
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xc) & 1);
    break;
  case 0x1ba:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (param_3 & 0x1f) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0x1bb:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (param_3 & 0x1f) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uVar7 & 0x8000) >> 0xf);
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xc) & 1);
    break;
  case 0x1bc:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (param_3 & 0x1f) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uVar7 & 0x8000) >> 0xf);
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xc) & 1);
    break;
  case 0x1bd:
    uVar15 = (ulong)(uVar7 & 0x1f);
    uVar7 = MCInst_getOpcode(param_4);
    if (uVar7 == 0xf00) {
      MCOperand_CreateImm0(param_4,uVar15);
    }
    else if (uVar7 < 0xf01) {
      if (uVar7 == 0xd4d) {
LAB_001caa00:
        MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + uVar15 * 4));
      }
      else if (uVar7 < 0xd4e) {
        if (uVar7 != 0xd3d) {
          if (uVar7 < 0xd3e) {
            if (uVar7 != 0xd32) {
              if (uVar7 != 0xd37) {
                return 0;
              }
LAB_001c0ba8:
              MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR8DecoderTable + uVar15 * 4));
              goto LAB_001c0bc0;
            }
          }
          else if (uVar7 != 0xd42) {
            if (uVar7 != 0xd47) {
              return 0;
            }
            goto LAB_001cb01c;
          }
          goto LAB_001caf88;
        }
LAB_001cafa4:
        MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + uVar15 * 4));
      }
      else {
        uVar7 = uVar7 - 0xd52;
        if (0x27 < uVar7) {
          return 0;
        }
        uVar12 = 1L << ((ulong)uVar7 & 0x3f);
        if ((uVar12 & 0x8000208020) == 0) {
          if ((uVar12 & 0x200000401) == 0) {
            if (uVar7 != 0x1b) {
              return 0;
            }
            goto LAB_001ca8a8;
          }
          goto LAB_001caf88;
        }
LAB_001caf28:
        MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + uVar15 * 4));
      }
    }
    else if (uVar7 == 0x14a1) {
LAB_001cb01c:
      MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + uVar15 * 4));
    }
    else {
      if (uVar7 < 0x14a2) {
        if (uVar7 == 0x1497) goto LAB_001cafa4;
        if (uVar7 < 0x1498) {
          if (uVar7 != 0x148d) {
            if (uVar7 != 0x1492) {
              return 0;
            }
            goto LAB_001c0ba8;
          }
        }
        else if (uVar7 != 0x149c) {
          return 0;
        }
      }
      else {
        if (uVar7 == 0x14ab) {
LAB_001ca8a8:
          MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + uVar15 * 4));
          goto LAB_001c0bc0;
        }
        if (uVar7 < 0x14ac) {
          if (uVar7 != 0x14a6) {
            return 0;
          }
          goto LAB_001caa00;
        }
        if (uVar7 != 0x14b0) {
          if (uVar7 != 0x14b5) {
            return 0;
          }
          goto LAB_001caf28;
        }
      }
LAB_001caf88:
      MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + uVar15 * 4));
    }
LAB_001c0bc0:
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    MCOperand_CreateImm0(param_4,uVar14 >> 10 & 0xfff);
    break;
  case 0x1be:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x1bf:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,param_3 & 0xf);
    MCOperand_CreateImm0(param_4,uVar14 >> 0xc & 0xf);
    break;
  case 0x1c0:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x10 & 0x1f);
    MCOperand_CreateImm0(param_4,param_3 & 0xf);
    MCOperand_CreateImm0(param_4,uVar14 >> 0xc & 0xf);
    break;
  case 0x1c1:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x1c2:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x1c3:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0xc & 0xf);
    break;
  case 0x1c4:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (param_3 & 0x1f) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar14 >> 0x10 & 0x1f);
    if (iVar6 == 0) {
      return 0;
    }
    if (iVar6 == 1) {
      return 1;
    }
    break;
  case 0x1c5:
    iVar6 = *(int *)(GPR64DecoderTable + (param_3 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar14 >> 5 & 0x1f);
    if (iVar6 == 0) {
      return 0;
    }
    uVar7 = 1;
    if (iVar6 != 1) {
      uVar7 = param_1;
    }
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    return (ulong)uVar7;
  case 0x1c6:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0x1c7:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (param_3 & 0x1f) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x1c8:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x1c9:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 10 & 0x1f) * 4));
    break;
  case 0x1ca:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 10 & 0x1f) * 4));
    break;
  case 0x1cb:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0xf & 0x3f);
    MCOperand_CreateImm0(param_4,param_3 & 0xf);
    break;
  case 0x1cc:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,param_3 & 0xf);
    MCOperand_CreateImm0(param_4,uVar14 >> 0xc & 0xf);
    break;
  case 0x1cd:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x10 & 0x1f);
    MCOperand_CreateImm0(param_4,param_3 & 0xf);
    MCOperand_CreateImm0(param_4,uVar14 >> 0xc & 0xf);
    break;
  case 0x1ce:
    MCOperand_CreateImm0(param_4,param_3 & 0x1f);
    uVar15 = uVar14 >> 5 & 0x7ffff;
    uVar14 = uVar15 | 0xfffffffffff80000;
    if ((uVar7 >> 5 & 0x40000) == 0) {
      uVar14 = uVar15;
    }
    MCOperand_CreateImm0(param_4,uVar14);
    break;
  case 0x1cf:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (param_3 & 0x1f) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0x1d0:
    uVar15 = uVar14 >> 5 & 0x1f;
    iVar6 = *(int *)(GPR64DecoderTable + uVar15 * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar7 & 0x1f);
    if (iVar6 == 0) {
      return 0;
    }
    uVar5 = 1;
    if (iVar6 != 1) {
      uVar5 = param_1;
    }
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar15);
    if (iVar6 == 0) {
      return 0;
    }
    uVar14 = uVar14 >> 0xc & 0x1ff;
    uVar13 = 1;
    if (iVar6 != 1) {
      uVar13 = uVar5;
    }
    if ((uVar7 >> 0x14 & 1) != 0) {
      uVar14 = uVar14 | 0xfffffffffffffe00;
    }
    MCOperand_CreateImm0(param_4,uVar14);
    return (ulong)uVar13;
  case 0x1d1:
    iVar6 = *(int *)(GPR64DecoderTable + (param_3 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar14 >> 5 & 0x1f);
    if (iVar6 == 0) {
      return 0;
    }
    uVar5 = 1;
    if (iVar6 != 1) {
      uVar5 = param_1;
    }
    uVar15 = uVar14 >> 0xc & 0x1ff;
    uVar14 = uVar15 | 0xfffffffffffffe00;
    if ((uVar7 >> 0xc & 0x100) == 0) {
      uVar14 = uVar15;
    }
    MCOperand_CreateImm0(param_4,uVar14);
    return (ulong)uVar5;
  case 0x1d2:
    uVar1 = *(undefined4 *)(GPR64DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    uVar15 = uVar14 >> 0xc & 0x1ff;
    uVar14 = uVar15 | 0xfffffffffffffe00;
    if ((uVar7 >> 0xc & 0x100) == 0) {
      uVar14 = uVar15;
    }
    MCOperand_CreateImm0(param_4,uVar14);
    break;
  case 0x1d3:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x1d4:
    uVar1 = *(undefined4 *)(GPR64DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0x1d5:
    uVar1 = *(undefined4 *)(GPR64DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    break;
  case 0x1d6:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    break;
  case 0x1d7:
    if (0x16 < (uVar7 & 0x1f)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    MCOperand_CreateReg0
              (param_4,*(undefined4 *)(GPR64x8DecoderTable + (ulong)((uVar7 & 0x1f) >> 1) * 4));
    iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar14 >> 5 & 0x1f);
    if (iVar6 == 0) {
      return 0;
    }
    if (iVar6 == 1) {
      return 1;
    }
    break;
  case 0x1d8:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    if (((uVar7 & 0x1f) < 0x17) && ((param_3 & 1) == 0)) {
      MCOperand_CreateReg0
                (param_4,*(undefined4 *)(GPR64x8DecoderTable + (ulong)((uVar7 & 0x1f) >> 1) * 4));
      iVar6 = DecodeGPR64spRegisterClass_part_0(param_4,uVar14 >> 5 & 0x1f);
      if (iVar6 != 0) {
        if (iVar6 == 1) {
          return 1;
        }
        break;
      }
    }
    return 0;
  case 0x1d9:
    uVar15 = uVar14 >> 5 & 0x1f;
    uVar5 = MCInst_getOpcode(param_4);
    if (uVar5 != 0xd2c) {
      if (uVar5 < 0xd2d) {
        if (uVar5 == 0xd2a) goto LAB_001ca5c0;
        if (uVar5 != 0xd2b) {
          return 0;
        }
      }
      else if (uVar5 != 0xd2d) {
        return 0;
      }
      iVar6 = *(int *)(GPR64DecoderTable + uVar15 * 4);
      if (iVar6 == 9) {
        iVar6 = 5;
      }
      MCOperand_CreateReg0(param_4,iVar6);
    }
LAB_001ca5c0:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (param_3 & 0x1f) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + uVar15 * 4);
    uVar5 = (uVar7 & 0x400000) >> 0xd;
    uVar14 = (ulong)((uint)(uVar14 >> 0xc) & 0x1ff | uVar5);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    uVar12 = uVar14 | 0xfffffffffffffc00;
    if (uVar5 == 0) {
      uVar12 = uVar14;
    }
    MCOperand_CreateImm0(param_4,uVar12);
    if (((uint)((uVar7 & 0x1f) == (uint)uVar15 && (uint)uVar15 != 0x1f) & uVar7 >> 0xb) != 0) {
      return 1;
    }
    break;
  case 0x1da:
    MCOperand_CreateImm0(param_4,param_3 & 0x1f);
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uVar7 & 0x8000) >> 0xf);
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xc) & 1);
    break;
  case 0x1db:
    MCOperand_CreateImm0(param_4,param_3 & 0x1f);
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uVar7 & 0x8000) >> 0xf);
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xc) & 1);
    break;
  case 0x1dc:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (param_3 & 0x1f) * 4));
    uVar15 = uVar14 >> 5 & 0x7ffff;
    uVar14 = uVar15 | 0xfffffffffff80000;
    if ((uVar7 >> 5 & 0x40000) == 0) {
      uVar14 = uVar15;
    }
    MCOperand_CreateImm0(param_4,uVar14);
    break;
  case 0x1dd:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,0x40 - ((uint)(uVar14 >> 10) & 0x1f | 0x20));
    break;
  case 0x1de:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,0x40 - ((uint)(uVar14 >> 10) & 0x1f | 0x20));
    break;
  case 0x1df:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x1e0:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x1e1:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x1e2:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x1e3:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x1e4:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x1e5:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x1e6:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0xd & 0xff);
    break;
  case 0x1e7:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,param_3 & 0xf);
    MCOperand_CreateImm0(param_4,uVar14 >> 0xc & 0xf);
    break;
  case 0x1e8:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x1e9:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0xc & 0xf);
    break;
  case 0x1ea:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,0x40 - ((uint)(uVar14 >> 10) & 0x1f | 0x20));
    break;
  case 0x1eb:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,0x40 - ((uint)(uVar14 >> 10) & 0x1f | 0x20));
    break;
  case 0x1ec:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x1ed:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x1ee:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x1ef:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0xd & 0xff);
    break;
  case 0x1f0:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,param_3 & 0xf);
    MCOperand_CreateImm0(param_4,uVar14 >> 0xc & 0xf);
    break;
  case 0x1f1:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0xc & 0xf);
    break;
  case 0x1f2:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,0x40 - ((uint)(uVar14 >> 10) & 0x1f | 0x20));
    break;
  case 499:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,0x40 - ((uint)(uVar14 >> 10) & 0x1f | 0x20));
    break;
  case 500:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x1f5:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x1f6:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x1f7:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x1f8:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x1f9:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x1fa:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x1fb:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0xd & 0xff);
    break;
  case 0x1fc:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,param_3 & 0xf);
    MCOperand_CreateImm0(param_4,uVar14 >> 0xc & 0xf);
    break;
  case 0x1fd:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x1fe:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0xc & 0xf);
    break;
  case 0x1ff:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (uVar14 >> 10 & 0x1f) * 4));
    break;
  case 0x200:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 10 & 0x1f) * 4));
    break;
  case 0x201:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (uVar14 >> 10 & 0x1f) * 4));
    break;
  case 0x202:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR8DecoderTable + (param_3 & 0x1f) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uVar7 & 0x8000) >> 0xf);
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xc) & 1);
    break;
  case 0x203:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR8DecoderTable + (param_3 & 0x1f) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uVar7 & 0x8000) >> 0xf);
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xc) & 1);
    break;
  case 0x204:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uVar7 & 0x8000) >> 0xf);
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xc) & 1);
    break;
  case 0x205:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uVar7 & 0x8000) >> 0xf);
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xc) & 1);
    break;
  case 0x206:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4));
    uVar15 = uVar14 >> 5 & 0x7ffff;
    uVar14 = uVar15 | 0xfffffffffff80000;
    if ((uVar7 >> 5 & 0x40000) == 0) {
      uVar14 = uVar15;
    }
    MCOperand_CreateImm0(param_4,uVar14);
    break;
  case 0x207:
    uVar1 = *(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x208:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x14 & 1);
    break;
  case 0x209:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x13 & 3);
    break;
  case 0x20a:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x12 & 7);
    break;
  case 0x20b:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR8DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x11 & 0xf);
    break;
  case 0x20c:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR8DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR8DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR8DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x20d:
    uVar1 = *(undefined4 *)(FPR8DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR8DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x20e:
    uVar1 = *(undefined4 *)(FPR16DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x20f:
    uVar1 = *(undefined4 *)(FPR32DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x210:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR8DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x211:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR8DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR8DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x212:
    uVar1 = *(undefined4 *)(FPR32DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x213:
    uVar1 = *(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x214:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x215:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x216:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,0x40 - (uVar5 & 0x3f));
    break;
  case 0x217:
    uVar1 = *(undefined4 *)(FPR16DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 0x10 & 0xf) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0x14) & 3 | (uVar7 & 0x800) >> 9);
    break;
  case 0x218:
    uVar1 = *(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,0x40 - (uVar5 & 0x3f));
    break;
  case 0x219:
    uVar1 = *(undefined4 *)(FPR32DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0x15) & 1 | (uVar7 & 0x800) >> 10);
    break;
  case 0x21a:
    uVar1 = *(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0xb & 1);
    break;
  case 0x21b:
    uVar1 = *(undefined4 *)(FPR32DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 0x10 & 0xf) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0x14) & 3 | (uVar7 & 0x800) >> 9);
    break;
  case 0x21c:
    uVar1 = *(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0x15) & 1 | (uVar7 & 0x800) >> 10);
    break;
  case 0x21d:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x10 & 0x3f);
    break;
  case 0x21e:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR8DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR8DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x10 & 7);
    break;
  case 0x21f:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x10 & 0xf);
    break;
  case 0x220:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x10 & 0x1f);
    break;
  case 0x221:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 0x10 & 0xf) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0x14) & 3 | (uVar7 & 0x800) >> 9);
    break;
  case 0x222:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR8DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,8 - (uVar5 & 7));
    break;
  case 0x223:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,0x10 - (uVar5 & 0xf));
    break;
  case 0x224:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,0x20 - (uVar5 & 0x1f));
    break;
  case 0x225:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0x15) & 1 | (uVar7 & 0x800) >> 10);
    break;
  case 0x226:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0xb & 1);
    break;
  case 0x227:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 0x10 & 0xf) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0x14) & 3 | (uVar7 & 0x800) >> 9);
    break;
  case 0x228:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0x15) & 1 | (uVar7 & 0x800) >> 10);
    break;
  case 0x229:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,0x10 - (uVar5 & 0xf));
    break;
  case 0x22a:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,0x20 - (uVar5 & 0x1f));
    break;
  case 0x22b:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (param_3 & 0x1f) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uVar7 & 0x8000) >> 0xf);
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xc) & 1);
    break;
  case 0x22c:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (param_3 & 0x1f) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uVar7 & 0x8000) >> 0xf);
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xc) & 1);
    break;
  case 0x22d:
    uVar1 = *(undefined4 *)(FPR16DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x22e:
    uVar1 = *(undefined4 *)(FPR32DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    break;
  case 0x22f:
    uVar1 = *(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,uVar1);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 0x10 & 0x3f);
    break;
  case 0x230:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (param_3 & 0x1f) * 4));
    uVar15 = uVar14 >> 5 & 0x7ffff;
    uVar14 = uVar15 | 0xfffffffffff80000;
    if ((uVar7 >> 5 & 0x40000) == 0) {
      uVar14 = uVar15;
    }
    MCOperand_CreateImm0(param_4,uVar14);
    break;
  case 0x231:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,0x40 - ((uint)(uVar14 >> 10) & 0x3f));
    break;
  case 0x232:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,0x40 - ((uint)(uVar14 >> 10) & 0x3f));
    break;
  case 0x233:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x234:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x235:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,0x40 - ((uint)(uVar14 >> 10) & 0x3f));
    break;
  case 0x236:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,0x40 - ((uint)(uVar14 >> 10) & 0x3f));
    break;
  case 0x237:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x238:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x239:
    uVar14 = uVar14 >> 5 & 0x1f;
    if ((param_3 & 0x10000) == 0) {
      MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (ulong)(uVar7 & 0x1f) * 4));
      MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + uVar14 * 4));
    }
    else {
      MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR128DecoderTable + (ulong)(uVar7 & 0x1f) * 4));
      MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + uVar14 * 4));
    }
    MCOperand_CreateImm0(param_4,1);
    break;
  case 0x23a:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,0x40 - ((uint)(uVar14 >> 10) & 0x3f));
    break;
  case 0x23b:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,0x40 - ((uint)(uVar14 >> 10) & 0x3f));
    break;
  case 0x23c:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x23d:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR16DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4));
    break;
  case 0x23e:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (param_3 & 0x1f) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uVar7 & 0x8000) >> 0xf);
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xc) & 1);
    break;
  case 0x23f:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR32DecoderTable + (param_3 & 0x1f) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uVar7 & 0x8000) >> 0xf);
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xc) & 1);
    break;
  case 0x240:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR32DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uVar7 & 0x8000) >> 0xf);
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xc) & 1);
    break;
  case 0x241:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(FPR64DecoderTable + (param_3 & 0x1f) * 4));
    iVar6 = *(int *)(GPR64DecoderTable + (uVar14 >> 5 & 0x1f) * 4);
    if (iVar6 == 9) {
      iVar6 = 5;
    }
    MCOperand_CreateReg0(param_4,iVar6);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (uVar14 >> 0x10 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,(uVar7 & 0x8000) >> 0xf);
    MCOperand_CreateImm0(param_4,(uint)(uVar14 >> 0xc) & 1);
    break;
  case 0x242:
    MCOperand_CreateImm0(param_4,uVar14 >> 5 & 0xffff);
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (param_3 & 0x1f) * 4));
    break;
  case 0x243:
    MCOperand_CreateReg0(param_4,*(undefined4 *)(GPR64DecoderTable + (param_3 & 0x1f) * 4));
    MCOperand_CreateImm0(param_4,uVar14 >> 5 & 0xffff);
    break;
  default:
    MCOperand_CreateImm0(param_4,param_3 & 0xffff);
  }
  return (ulong)param_1;
}

