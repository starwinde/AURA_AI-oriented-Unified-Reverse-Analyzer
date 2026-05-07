
undefined4 DecodeSignedLdStInstruction_isra_0(undefined8 param_1,ulong param_2)

{
  ulong uVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  ulong uVar5;
  uint uVar6;
  ulong uVar7;
  ulong uVar8;
  
  uVar7 = (param_2 & 0xffffffff) >> 0xc & 0x1ff;
  uVar6 = (uint)param_2;
  uVar8 = (ulong)(uVar6 & 0x1f);
  uVar1 = uVar7 | 0xfffffffffffffe00;
  if ((param_2 >> 0xc & 0x100) == 0) {
    uVar1 = uVar7;
  }
  uVar7 = (param_2 & 0xffffffff) >> 5 & 0x1f;
  uVar3 = MCInst_getOpcode();
  if (uVar3 < 0xd77) {
    if (0xd38 < uVar3) {
      uVar5 = 0x30c30c318c630c63 >> ((ulong)(uVar3 - 0xd39) & 0x3f);
      goto joined_r0x001bab28;
    }
    if (uVar3 < 0xd30) {
      if (uVar3 < 0xd2e) goto LAB_001ba9a0;
      goto LAB_001baa54;
    }
    if (uVar3 - 0xd33 < 2) goto LAB_001baa54;
LAB_001ba9a0:
    uVar3 = MCInst_getOpcode(param_1);
    if (uVar3 != 0xf02) goto LAB_001ba9b0;
LAB_001baa8c:
    MCOperand_CreateImm0(param_1,uVar8);
    goto LAB_001bac18;
  }
  if (0x29 < uVar3 - 0x1489) goto LAB_001ba9a0;
  uVar5 = 0x318c6318c63 >> ((ulong)(uVar3 - 0x1489) & 0x3f);
joined_r0x001bab28:
  if ((uVar5 & 1) == 0) goto LAB_001ba9a0;
LAB_001baa54:
  iVar2 = *(int *)(GPR64DecoderTable + uVar7 * 4);
  if (iVar2 == 9) {
    iVar2 = 5;
  }
  MCOperand_CreateReg0(param_1,iVar2);
  uVar3 = MCInst_getOpcode(param_1);
  if (uVar3 == 0xf02) goto LAB_001baa8c;
LAB_001ba9b0:
  if (uVar3 < 0xf02) {
    if (uVar3 < 0xdb6) {
      if (uVar3 < 0xdad) {
        if (uVar3 < 0xd45) {
          if (0xd42 < uVar3) goto switchD_001baac4_caseD_149d;
          if (uVar3 < 0xd35) {
            if (0xd32 < uVar3) goto switchD_001baac4_caseD_148e;
            if (0xcae < uVar3) {
              uVar3 = uVar3 - 0xd2e;
              goto joined_r0x001bad50;
            }
            if (0xca5 < uVar3) {
              uVar5 = 1L << ((ulong)(uVar3 - 0xca6) & 0x3f);
              if ((uVar5 & 0x117) == 0) {
                uVar5 = uVar5 & 0xe8;
                goto joined_r0x001baae8;
              }
              goto switchD_001baac4_caseD_145c;
            }
          }
          else {
            if (0xd3a < uVar3) {
              uVar3 = uVar3 - 0xd3e;
joined_r0x001bad50:
              if (1 < uVar3) {
                return 0;
              }
              goto switchD_001baac4_caseD_145c;
            }
            if (0xd38 < uVar3) goto switchD_001baac4_caseD_1493;
          }
        }
        else if (uVar3 < 0xd4b) {
          if (0xd48 < uVar3) goto switchD_001baac4_caseD_14a2;
        }
        else if (uVar3 - 0xd4e < 0x29) {
          uVar5 = 1L << ((ulong)(uVar3 - 0xd4e) & 0x3f);
          if ((uVar5 & 0x18000618060) != 0) goto switchD_001baac4_caseD_145f;
          if ((uVar5 & 0x600000c03) != 0) goto switchD_001baac4_caseD_145c;
          if ((uVar5 & 0x18000000) != 0) goto switchD_001baac4_caseD_14a7;
        }
      }
      else {
        uVar5 = 1L << ((ulong)(uVar3 - 0xdad) & 0x3f);
        if ((uVar5 & 0x97) != 0) goto switchD_001baac4_caseD_145c;
        uVar5 = uVar5 & 0x168;
joined_r0x001baae8:
        if (uVar5 != 0) goto switchD_001baac4_caseD_145f;
      }
    }
    else {
      if (uVar3 == 0xdda) goto switchD_001baac4_caseD_149d;
      if (uVar3 < 0xddb) {
        if (uVar3 == 0xdd8) goto switchD_001baac4_caseD_1493;
        if ((uVar3 == 0xdd9) || (uVar3 == 0xdd6)) goto switchD_001baac4_caseD_145c;
        if (uVar3 == 0xdd7) goto switchD_001baac4_caseD_148e;
      }
      else {
        if (uVar3 == 0xddb) goto switchD_001baac4_caseD_14a2;
        if (uVar3 - 0xddc < 8) {
          uVar5 = 1L << ((ulong)(uVar3 - 0xddc) & 0x3f);
          if ((uVar5 & 0x9a) != 0) goto switchD_001baac4_caseD_145f;
          if ((uVar5 & 0x45) == 0) goto switchD_001baac4_caseD_14a7;
          goto switchD_001baac4_caseD_145c;
        }
      }
    }
switchD_001baac4_caseD_1460:
    uVar4 = 0;
  }
  else {
    switch(uVar3) {
    case 0x145c:
    case 0x145d:
    case 0x145e:
    case 0x1489:
    case 0x148a:
    case 0x1498:
    case 0x1499:
    case 0x14ac:
    case 0x14ad:
    case 0x14b9:
    case 0x14ba:
    case 0x14bb:
    case 0x14bd:
    case 0x14c0:
    case 0x14c4:
switchD_001baac4_caseD_145c:
      MCOperand_CreateReg0(param_1,*(undefined4 *)(GPR32DecoderTable + uVar8 * 4));
      break;
    case 0x145f:
    case 0x14b1:
    case 0x14b2:
    case 0x14bc:
    case 0x14c5:
switchD_001baac4_caseD_145f:
      MCOperand_CreateReg0(param_1,*(undefined4 *)(GPR64DecoderTable + uVar8 * 4));
      break;
    default:
      goto switchD_001baac4_caseD_1460;
    case 0x148e:
    case 0x148f:
    case 0x14be:
switchD_001baac4_caseD_148e:
      MCOperand_CreateReg0(param_1,*(undefined4 *)(FPR8DecoderTable + uVar8 * 4));
      break;
    case 0x1493:
    case 0x1494:
    case 0x14bf:
switchD_001baac4_caseD_1493:
      MCOperand_CreateReg0(param_1,*(undefined4 *)(FPR64DecoderTable + uVar8 * 4));
      break;
    case 0x149d:
    case 0x149e:
    case 0x14c1:
switchD_001baac4_caseD_149d:
      MCOperand_CreateReg0(param_1,*(undefined4 *)(FPR16DecoderTable + uVar8 * 4));
      break;
    case 0x14a2:
    case 0x14a3:
    case 0x14c2:
switchD_001baac4_caseD_14a2:
      MCOperand_CreateReg0(param_1,*(undefined4 *)(FPR128DecoderTable + uVar8 * 4));
      break;
    case 0x14a7:
    case 0x14a8:
    case 0x14c3:
switchD_001baac4_caseD_14a7:
      MCOperand_CreateReg0(param_1,*(undefined4 *)(FPR32DecoderTable + uVar8 * 4));
    }
LAB_001bac18:
    iVar2 = *(int *)(GPR64DecoderTable + uVar7 * 4);
    if (iVar2 == 9) {
      iVar2 = 5;
    }
    MCOperand_CreateReg0(param_1,iVar2);
    MCOperand_CreateImm0(param_1,uVar1);
    uVar4 = 3;
    if (((uint)((param_2 & 0xc00) != 0) & uVar6 >> 0x16) != 0) {
      uVar4 = 3;
      if (((uint)((uVar6 & 0x1f) == (uint)uVar7) &
          (uint)((uint)uVar7 != 0x1f) & (uVar6 >> 0x1a ^ 0xffffffff)) != 0) {
        uVar4 = 1;
      }
      return uVar4;
    }
  }
  return uVar4;
}

