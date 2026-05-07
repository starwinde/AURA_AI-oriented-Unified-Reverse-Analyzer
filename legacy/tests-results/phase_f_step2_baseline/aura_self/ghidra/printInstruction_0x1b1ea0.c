
void printInstruction(long param_1,undefined8 param_2)

{
  byte bVar1;
  code *pcVar2;
  undefined1 uVar3;
  undefined4 uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  uint uVar10;
  uint uVar11;
  ulong uVar12;
  long lVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  undefined8 uVar16;
  long lVar17;
  undefined *puVar18;
  char *pcVar19;
  long lVar20;
  ulong uVar21;
  uint uVar22;
  char cVar23;
  uint uVar24;
  
  uVar12 = MCInst_getOpcode();
  uVar11 = *(uint *)(OpInfo0_2 + (uVar12 & 0xffffffff) * 4);
  uVar10 = *(uint *)(OpInfo1_1 + (uVar12 & 0xffffffff) * 4);
  SStream_concat0(param_2,(uVar11 & 0xfff) + 0x24282f);
  uVar12 = (((ulong)uVar11 & 0x1f000) >> 0xc) - 1;
  if (0x1e < uVar12) {
    return;
  }
  switch(uVar12 & 0xffffffff) {
  case 0:
    MCInst_getOperand(param_1,5);
    iVar7 = MCOperand_getReg();
    if ((iVar7 != 0) &&
       (SStream_concat0(param_2,"s"), *(int *)(*(long *)(param_1 + 800) + 0x60) != 0)) {
      *(undefined1 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x78) = 1;
    }
  case 6:
    printPredicateOperand(param_1,3,param_2);
    break;
  case 1:
    MCInst_getOperand(param_1,1);
    uVar5 = MCOperand_getImm();
    MCInst_getOperand(param_1,0);
    uVar6 = MCOperand_getImm();
    if ((uVar5 != 0) &&
       (uVar24 = (uVar5 & 0xaaaaaaaa) >> 1 | (uVar5 & 0x55555555) << 1,
       uVar24 = (uVar24 & 0xcccccccc) >> 2 | (uVar24 & 0x33333333) << 2,
       uVar24 = (uVar24 & 0xf0f0f0f0) >> 4 | (uVar24 & 0xf0f0f0f) << 4,
       uVar24 = (uVar24 & 0xff00ff00) >> 8 | (uVar24 & 0xff00ff) << 8,
       uVar24 = (uint)LZCOUNT(uVar24 >> 0x10 | uVar24 << 0x10), uVar24 < 3)) {
      uVar22 = 3;
      do {
        if (((uVar5 >> (ulong)(uVar22 & 0x1f) ^ uVar6) & 1) == 0) {
          SStream_concat0(param_2,&DAT_002003d8);
        }
        else {
          SStream_concat0(param_2,"e");
        }
        uVar22 = uVar22 - 1;
      } while (uVar24 != uVar22);
    }
    break;
  case 3:
    MCInst_getOperand(param_1,4);
    iVar7 = MCOperand_getReg();
    if ((iVar7 != 0) &&
       (SStream_concat0(param_2,"s"), *(int *)(*(long *)(param_1 + 800) + 0x60) != 0)) {
      *(undefined1 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x78) = 1;
    }
  case 2:
    printPredicateOperand(param_1,2,param_2);
    break;
  case 5:
    printPredicateOperand(param_1,5,param_2);
    break;
  case 7:
    MCInst_getOperand(param_1,6);
    iVar7 = MCOperand_getReg();
    if ((iVar7 != 0) &&
       (SStream_concat0(param_2,"s"), *(int *)(*(long *)(param_1 + 800) + 0x60) != 0)) {
      *(undefined1 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x78) = 1;
    }
  case 4:
    printPredicateOperand(param_1,4,param_2);
    break;
  case 8:
    MCInst_getOperand(param_1,7);
    iVar7 = MCOperand_getReg();
    if ((iVar7 != 0) &&
       (SStream_concat0(param_2,"s"), *(int *)(*(long *)(param_1 + 800) + 0x60) != 0)) {
      *(undefined1 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x78) = 1;
    }
    printPredicateOperand(param_1,5,param_2);
    SStream_concat0(param_2,&DAT_001fc128);
    printOperand(param_1,0,param_2);
    SStream_concat0(param_2,", ");
    printOperand(param_1,1,param_2);
    SStream_concat0(param_2,", ");
    printSORegRegOperand(param_1,2,param_2);
    return;
  case 9:
    printOperand(param_1,0,param_2);
    break;
  case 10:
    printPredicateOperand(param_1,1,param_2);
    break;
  case 0xb:
    printPredicateOperand(param_1,0,param_2);
    break;
  case 0xc:
    printPredicateOperand(param_1,6,param_2);
    break;
  case 0xd:
    MCInst_getOperand(param_1,0);
    uVar4 = MCOperand_getImm();
    SStream_concat(param_2,&DAT_001fc008,uVar4);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x94) = 0x41;
      *(undefined4 *)(lVar13 + 0x98) = uVar4;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    SStream_concat0(param_2,", ");
    break;
  case 0xe:
    MCInst_getOperand(param_1,0);
    iVar7 = MCOperand_getImm();
    if (iVar7 == 2) {
      puVar18 = &DAT_001fbff0;
    }
    else {
      puVar18 = &DAT_001fbff8;
      if (iVar7 != 3) {
        puVar18 = &DAT_001fc428;
      }
    }
    SStream_concat0(param_2,puVar18);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(int *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x6c) = iVar7;
    }
    break;
  case 0xf:
    goto switchD_001b1f34_caseD_f;
  case 0x10:
    goto switchD_001b1f34_caseD_10;
  case 0x11:
    MCInst_getOperand(param_1,1);
    uVar4 = MCOperand_getImm();
    SStream_concat(param_2,&DAT_001fc008,uVar4);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x94) = 0x41;
      *(undefined4 *)(lVar13 + 0x98) = uVar4;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    SStream_concat0(param_2,", ");
    printOperand(param_1,2,param_2);
    SStream_concat0(param_2,", ");
    printOperand(param_1,0,param_2);
    SStream_concat0(param_2,", ");
    MCInst_getOperand(param_1,3);
    uVar4 = MCOperand_getImm();
    SStream_concat(param_2,&DAT_001fbda8,uVar4);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x94) = 0x40;
      *(undefined4 *)(lVar13 + 0x98) = uVar4;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    SStream_concat0(param_2,", ");
    MCInst_getOperand(param_1,4);
    uVar4 = MCOperand_getImm();
    SStream_concat(param_2,&DAT_001fbda8,uVar4);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x94) = 0x40;
      *(undefined4 *)(lVar13 + 0x98) = uVar4;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    goto LAB_001b2610;
  case 0x12:
    MCInst_getOperand(param_1,2);
    uVar4 = MCOperand_getImm();
    SStream_concat(param_2,&DAT_001fc008,uVar4);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x94) = 0x41;
      *(undefined4 *)(lVar13 + 0x98) = uVar4;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    SStream_concat0(param_2,", ");
    printOperand(param_1,3,param_2);
    SStream_concat0(param_2,", ");
    printOperand(param_1,0,param_2);
    SStream_concat0(param_2,", ");
    printOperand(param_1,1,param_2);
    SStream_concat0(param_2,", ");
    MCInst_getOperand(param_1,4);
    uVar4 = MCOperand_getImm();
    SStream_concat(param_2,&DAT_001fbda8,uVar4);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
      return;
    }
    lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar17 + 0x80);
    lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
    *(undefined4 *)(lVar13 + 0x94) = 0x40;
    *(undefined4 *)(lVar13 + 0x98) = uVar4;
    *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    return;
  case 0x13:
    goto switchD_001b1f34_caseD_13;
  case 0x14:
    printAddrMode2Operand(param_1,0,param_2);
    return;
  case 0x15:
    MCInst_getOperand(param_1,0);
    lVar13 = MCOperand_getImm();
    if (lVar13 == 0) {
      SStream_concat0(param_2,"le");
      if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
        return;
      }
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar13 + 0x80);
      *(undefined8 *)(lVar13 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x94) = DAT_0020a420;
      *(byte *)(lVar13 + 0x80) = bVar1 + 1;
      return;
    }
    SStream_concat0(param_2,&DAT_001fc010);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
      return;
    }
    lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar13 + 0x80);
    *(undefined8 *)(lVar13 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x94) = DAT_0020a418;
    *(byte *)(lVar13 + 0x80) = bVar1 + 1;
    return;
  case 0x16:
    MCInst_getOperand(param_1,8);
    iVar7 = MCOperand_getReg();
    if ((iVar7 != 0) &&
       (SStream_concat0(param_2,"s"), *(int *)(*(long *)(param_1 + 800) + 0x60) != 0)) {
      *(undefined1 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x78) = 1;
    }
    printPredicateOperand(param_1,6,param_2);
    SStream_concat0(param_2,&DAT_001fc128);
    printOperand(param_1,0,param_2);
    SStream_concat0(param_2,", ");
    printOperand(param_1,1,param_2);
    SStream_concat0(param_2,", ");
    printOperand(param_1,2,param_2);
    SStream_concat0(param_2,", ");
    printOperand(param_1,3,param_2);
    return;
  case 0x17:
    MCInst_getOperand(param_1,0);
    iVar7 = MCOperand_getImm();
    uVar14 = 0x1fc000;
    if (iVar7 != 0) {
      uVar14 = 0;
    }
    SStream_concat0(param_2,uVar14);
    return;
  case 0x18:
    printPredicateOperand(param_1,7,param_2);
    break;
  case 0x19:
    printPredicateOperand(param_1,9,param_2);
    break;
  case 0x1a:
    printPredicateOperand(param_1,0xb,param_2);
    break;
  case 0x1b:
    printPredicateOperand(param_1,8,param_2);
    break;
  case 0x1c:
    printPredicateOperand(param_1,0xd,param_2);
    break;
  case 0x1d:
    printOperand(param_1,1,param_2);
    SStream_concat0(param_2,", ");
    printOperand(param_1,2,param_2);
    SStream_concat0(param_2,", ");
    printOperand(param_1,3,param_2);
    break;
  case 0x1e:
    MCInst_getOperand(param_1,1);
    iVar7 = MCOperand_getReg();
    if ((iVar7 != 0) &&
       (SStream_concat0(param_2,"s"), *(int *)(*(long *)(param_1 + 800) + 0x60) != 0)) {
      *(undefined1 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x78) = 1;
    }
    break;
  default:
    goto switchD_001b1f34_default;
  }
  uVar12 = (((ulong)uVar11 & 0xfe0000) >> 0x11) - 1;
  if (0x49 < uVar12) {
switchD_001b2168_default:
    SStream_concat0(param_2,&DAT_001fc348);
    goto LAB_001b1fb0;
  }
  switch(uVar12 & 0xffffffff) {
  case 0:
    SStream_concat0(param_2,&DAT_001fc018);
    iVar7 = *(int *)(*(long *)(param_1 + 800) + 0x60);
    goto joined_r0x001b3c00;
  case 1:
    SStream_concat0(param_2,&DAT_001fc020);
    iVar7 = *(int *)(*(long *)(param_1 + 800) + 0x60);
    goto joined_r0x001b3be0;
  case 2:
    SStream_concat0(param_2,&DAT_001fc028);
    iVar7 = *(int *)(*(long *)(param_1 + 800) + 0x60);
    goto joined_r0x001b3bc0;
  case 3:
    SStream_concat0(param_2,&DAT_001fc128);
    goto LAB_001b1fb0;
  case 4:
    goto switchD_001b2168_caseD_4;
  case 5:
    goto switchD_001b1f34_default;
  case 6:
    SStream_concat0(param_2,&DAT_001fc030);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
      return;
    }
    lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar13 + 0x80);
    *(undefined8 *)(lVar13 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x94) = 0xa00000001;
    *(byte *)(lVar13 + 0x80) = bVar1 + 1;
    return;
  case 7:
    printOperand(param_1,1,param_2);
    goto switchD_001b2168_caseD_4;
  case 8:
    SStream_concat0(param_2,".f64\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x10;
    }
    goto LAB_001b2c38;
  case 9:
    SStream_concat0(param_2,".f16\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0xe;
    }
    goto LAB_001b2c38;
  case 10:
    SStream_concat0(param_2,".f32\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0xf;
    }
LAB_001b2c38:
    printOperand(param_1,0,param_2);
    goto LAB_001b1fb0;
  case 0xb:
    SStream_concat0(param_2,"\tapsr_nzcv, fpscr");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
      return;
    }
    lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar13 + 0x80);
    *(undefined8 *)(lVar13 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x94) = 0x200000001;
    *(undefined8 *)
     (lVar13 + ((ulong)(byte)(bVar1 + 1) * 2 + (ulong)(byte)(bVar1 + 1)) * 0x10 + 0x94) =
         0x600000001;
    *(byte *)(lVar13 + 0x80) = bVar1 + 2;
    return;
  case 0xc:
    MCInst_getOperand(param_1,1);
    uVar4 = MCOperand_getImm();
    SStream_concat(param_2,&DAT_001fbda8,uVar4);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x94) = 0x40;
      *(undefined4 *)(lVar13 + 0x98) = uVar4;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    SStream_concat0(param_2,", ");
    goto LAB_001b1fb0;
  case 0xd:
    SStream_concat0(param_2,"\tpc, lr");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
      return;
    }
    lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar13 + 0x80);
    *(undefined8 *)(lVar13 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x94) = 0xb00000001;
    *(undefined8 *)
     (lVar13 + ((ulong)(byte)(bVar1 + 1) * 2 + (ulong)(byte)(bVar1 + 1)) * 0x10 + 0x94) =
         0xa00000001;
    *(byte *)(lVar13 + 0x80) = bVar1 + 2;
    return;
  case 0xe:
    goto switchD_001b6bb0_caseD_1;
  case 0xf:
    SStream_concat0(param_2,".s32\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 7;
    }
    goto LAB_001b2198;
  case 0x10:
    SStream_concat0(param_2,".s16\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 6;
    }
    goto LAB_001b2198;
  case 0x11:
    SStream_concat0(param_2,&DAT_001fc080);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 5;
    }
    goto LAB_001b2198;
  case 0x12:
    SStream_concat0(param_2,".u32\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0xb;
    }
    goto LAB_001b2198;
  case 0x13:
    SStream_concat0(param_2,".u16\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 10;
    }
    goto LAB_001b2198;
  case 0x14:
    SStream_concat0(param_2,&DAT_001fc098);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 9;
    }
    goto LAB_001b2198;
  case 0x15:
    SStream_concat0(param_2,".i64\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 4;
    }
    goto LAB_001b2198;
  case 0x16:
    SStream_concat0(param_2,".i32\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 3;
    }
    goto LAB_001b2198;
  case 0x17:
    SStream_concat0(param_2,".i16\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 2;
    }
    goto LAB_001b2198;
  case 0x18:
    SStream_concat0(param_2,&DAT_001fc0b8);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 1;
    }
    goto LAB_001b2198;
  case 0x19:
    SStream_concat0(param_2,".f16.f64\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x11;
    }
    goto LAB_001b2e6c;
  case 0x1a:
    SStream_concat0(param_2,".f64.f16\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x12;
    }
    goto LAB_001b2e6c;
  case 0x1b:
    SStream_concat0(param_2,".f32.f16\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x13;
    }
    goto LAB_001b2e6c;
  case 0x1c:
    SStream_concat0(param_2,".f16.f32\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x14;
    }
    goto LAB_001b2e6c;
  case 0x1d:
    SStream_concat0(param_2,".f64.f32\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x15;
    }
    goto LAB_001b2e6c;
  case 0x1e:
    SStream_concat0(param_2,".f32.f64\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x16;
    }
LAB_001b2e6c:
    printOperand(param_1,0,param_2);
    SStream_concat0(param_2,", ");
    printOperand(param_1,1,param_2);
    return;
  case 0x1f:
    SStream_concat0(param_2,&DAT_001fc120);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x17;
    }
    break;
  case 0x20:
    SStream_concat0(param_2,".u32.f32\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x18;
    }
    break;
  case 0x21:
    pcVar19 = ".s16.f16\t";
    goto LAB_001b2d2c;
  case 0x22:
    SStream_concat0(param_2,".u16.f16\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x28;
    }
    break;
  case 0x23:
    SStream_concat0(param_2,".f32.s32\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x19;
    }
    break;
  case 0x24:
    pcVar19 = ".f16.s16\t";
    goto LAB_001b2d2c;
  case 0x25:
    SStream_concat0(param_2,".f32.u32\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x1a;
    }
    break;
  case 0x26:
    SStream_concat0(param_2,".f16.u16\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x27;
    }
    break;
  case 0x27:
    SStream_concat0(param_2,&DAT_001fc1a0);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 100) = 0x40;
    }
    goto LAB_001b1fb0;
  case 0x28:
    SStream_concat0(param_2,".s32.f64\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x20;
    }
    break;
  case 0x29:
    SStream_concat0(param_2,".16\t{");
    iVar7 = *(int *)(*(long *)(param_1 + 800) + 0x60);
joined_r0x001b3c00:
    if (iVar7 != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 100) = 0x10;
    }
    goto LAB_001b1fb0;
  case 0x2a:
    SStream_concat0(param_2,".32\t{");
    iVar7 = *(int *)(*(long *)(param_1 + 800) + 0x60);
joined_r0x001b3be0:
    if (iVar7 != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 100) = 0x20;
    }
    goto LAB_001b1fb0;
  case 0x2b:
    SStream_concat0(param_2,&DAT_001fc1c8);
    iVar7 = *(int *)(*(long *)(param_1 + 800) + 0x60);
joined_r0x001b3bc0:
    if (iVar7 != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 100) = 8;
    }
    goto LAB_001b1fb0;
  case 0x2c:
    SStream_concat0(param_2,"\tfpscr, ");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) goto LAB_001b31e4;
    lVar13 = *(long *)(param_1 + 0x310);
    uVar14 = 0x600000001;
    goto LAB_001b31c4;
  case 0x2d:
    SStream_concat0(param_2,"\tfpexc, ");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) goto LAB_001b31e4;
    lVar13 = *(long *)(param_1 + 0x310);
    uVar14 = 0x400000001;
    goto LAB_001b31c4;
  case 0x2e:
    SStream_concat0(param_2,"\tfpinst, ");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) goto LAB_001b31e4;
    lVar13 = *(long *)(param_1 + 0x310);
    uVar14 = 0x500000001;
    goto LAB_001b31c4;
  case 0x2f:
    SStream_concat0(param_2,"\tfpinst2, ");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) goto LAB_001b31e4;
    lVar13 = *(long *)(param_1 + 0x310);
    uVar14 = 0x2e00000001;
    goto LAB_001b31c4;
  case 0x30:
    SStream_concat0(param_2,"\tfpsid, ");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) goto LAB_001b31e4;
    lVar13 = *(long *)(param_1 + 0x310);
    uVar14 = 0x800000001;
    goto LAB_001b31c4;
  case 0x31:
    SStream_concat0(param_2,&DAT_001fc220);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0xd;
    }
    printOperand(param_1,0,param_2);
    SStream_concat0(param_2,", ");
    printOperand(param_1,1,param_2);
    SStream_concat0(param_2,", ");
    printOperand(param_1,2,param_2);
    return;
  case 0x32:
    SStream_concat0(param_2,".s64\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 8;
    }
    goto LAB_001b2198;
  case 0x33:
    SStream_concat0(param_2,".u64\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0xc;
    }
LAB_001b2198:
    printOperand(param_1,0,param_2);
switchD_001b2168_caseD_4:
    SStream_concat0(param_2,", ");
    goto LAB_001b1fb0;
  case 0x34:
    MCInst_getOperand(param_1,4);
    uVar11 = MCOperand_getImm();
    if (uVar11 < 10) {
      SStream_concat(param_2,&DAT_001fbda0,uVar11);
    }
    else {
      SStream_concat(param_2,"[0x%x]",uVar11);
    }
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
      return;
    }
    lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    uVar10 = *(byte *)(lVar13 + 0x80) - 1;
    *(uint *)(lVar13 + ((-(ulong)(uVar10 >> 0x1f) & 0xfffffffe00000000 | (ulong)uVar10 << 1) +
                       (long)(int)uVar10) * 0x10 + 0x88) = uVar11;
    return;
  case 0x35:
    SStream_concat0(param_2,".f64.s16\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x1b;
    }
    printOperand(param_1,0,param_2);
    SStream_concat0(param_2,", ");
    printOperand(param_1,1,param_2);
    SStream_concat0(param_2,", ");
    MCInst_getOperand(param_1,2);
    iVar7 = MCOperand_getImm();
    printUInt32Bang(param_2,0x10 - iVar7);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
      return;
    }
    lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar17 + 0x80);
    lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
    *(undefined4 *)(lVar13 + 0x94) = 2;
    *(int *)(lVar13 + 0x98) = 0x10 - iVar7;
    *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    return;
  case 0x36:
    SStream_concat0(param_2,".f32.s16\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x1c;
    }
    printOperand(param_1,0,param_2);
    SStream_concat0(param_2,", ");
    printOperand(param_1,1,param_2);
    SStream_concat0(param_2,", ");
    MCInst_getOperand(param_1,2);
    iVar7 = MCOperand_getImm();
    printUInt32Bang(param_2,0x10 - iVar7);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
      return;
    }
    lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar17 + 0x80);
    lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
    *(undefined4 *)(lVar13 + 0x94) = 2;
    *(int *)(lVar13 + 0x98) = 0x10 - iVar7;
    *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    return;
  case 0x37:
    SStream_concat0(param_2,".f64.s32\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x1d;
    }
    break;
  case 0x38:
    pcVar19 = ".f16.s32\t";
    goto LAB_001b2d2c;
  case 0x39:
    SStream_concat0(param_2,".s16.f64\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x1e;
    }
    printOperand(param_1,0,param_2);
    SStream_concat0(param_2,", ");
    printOperand(param_1,1,param_2);
    SStream_concat0(param_2,", ");
    MCInst_getOperand(param_1,2);
    iVar7 = MCOperand_getImm();
    printUInt32Bang(param_2,0x10 - iVar7);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
      return;
    }
    lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar17 + 0x80);
    lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
    *(undefined4 *)(lVar13 + 0x94) = 2;
    *(int *)(lVar13 + 0x98) = 0x10 - iVar7;
    *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    return;
  case 0x3a:
    SStream_concat0(param_2,".s16.f32\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x1f;
    }
    printOperand(param_1,0,param_2);
    SStream_concat0(param_2,", ");
    printOperand(param_1,1,param_2);
    SStream_concat0(param_2,", ");
    MCInst_getOperand(param_1,2);
    iVar7 = MCOperand_getImm();
    printUInt32Bang(param_2,0x10 - iVar7);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
      return;
    }
    lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar17 + 0x80);
    lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
    *(undefined4 *)(lVar13 + 0x94) = 2;
    *(int *)(lVar13 + 0x98) = 0x10 - iVar7;
    *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    return;
  case 0x3b:
    pcVar19 = ".s32.f16\t";
LAB_001b2d2c:
    SStream_concat0(param_2,pcVar19);
    break;
  case 0x3c:
    SStream_concat0(param_2,".u16.f64\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x21;
    }
    printOperand(param_1,0,param_2);
    SStream_concat0(param_2,", ");
    printOperand(param_1,1,param_2);
    SStream_concat0(param_2,", ");
    MCInst_getOperand(param_1,2);
    iVar7 = MCOperand_getImm();
    printUInt32Bang(param_2,0x10 - iVar7);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
      return;
    }
    lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar17 + 0x80);
    lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
    *(undefined4 *)(lVar13 + 0x94) = 2;
    *(int *)(lVar13 + 0x98) = 0x10 - iVar7;
    *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    return;
  case 0x3d:
    SStream_concat0(param_2,".u16.f32\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x22;
    }
    printOperand(param_1,0,param_2);
    SStream_concat0(param_2,", ");
    printOperand(param_1,1,param_2);
    SStream_concat0(param_2,", ");
    MCInst_getOperand(param_1,2);
    iVar7 = MCOperand_getImm();
    printUInt32Bang(param_2,0x10 - iVar7);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
      return;
    }
    lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar17 + 0x80);
    lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
    *(undefined4 *)(lVar13 + 0x94) = 2;
    *(int *)(lVar13 + 0x98) = 0x10 - iVar7;
    *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    return;
  case 0x3e:
    SStream_concat0(param_2,".u32.f64\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x23;
    }
    break;
  case 0x3f:
    SStream_concat0(param_2,".u32.f16\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x2a;
    }
    break;
  case 0x40:
    SStream_concat0(param_2,".f64.u16\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x24;
    }
    printOperand(param_1,0,param_2);
    SStream_concat0(param_2,", ");
    printOperand(param_1,1,param_2);
    SStream_concat0(param_2,", ");
    MCInst_getOperand(param_1,2);
    iVar7 = MCOperand_getImm();
    printUInt32Bang(param_2,0x10 - iVar7);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
      return;
    }
    lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar17 + 0x80);
    lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
    *(undefined4 *)(lVar13 + 0x94) = 2;
    *(int *)(lVar13 + 0x98) = 0x10 - iVar7;
    *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    return;
  case 0x41:
    SStream_concat0(param_2,".f32.u16\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x25;
    }
    printOperand(param_1,0,param_2);
    SStream_concat0(param_2,", ");
    printOperand(param_1,1,param_2);
    SStream_concat0(param_2,", ");
    MCInst_getOperand(param_1,2);
    iVar7 = MCOperand_getImm();
    printUInt32Bang(param_2,0x10 - iVar7);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
      return;
    }
    lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar17 + 0x80);
    lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
    *(undefined4 *)(lVar13 + 0x94) = 2;
    *(int *)(lVar13 + 0x98) = 0x10 - iVar7;
    *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    return;
  case 0x42:
    SStream_concat0(param_2,".f64.u32\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x26;
    }
    break;
  case 0x43:
    SStream_concat0(param_2,".f16.u32\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x29;
    }
    break;
  case 0x44:
    SStream_concat0(param_2,&DAT_001fc328);
    goto LAB_001b1fb0;
  case 0x45:
    SStream_concat0(param_2,"\tsp, ");
    iVar7 = *(int *)(*(long *)(param_1 + 800) + 0x60);
    goto joined_r0x001b31b4;
  case 0x46:
    SStream_concat0(param_2,"\tsp!, ");
    iVar7 = *(int *)(*(long *)(param_1 + 800) + 0x60);
joined_r0x001b31b4:
    if (iVar7 == 0) goto LAB_001b31e4;
    lVar13 = *(long *)(param_1 + 0x310);
    uVar14 = 0xc00000001;
LAB_001b31c4:
    lVar13 = *(long *)(lVar13 + 0xf0);
    bVar1 = *(byte *)(lVar13 + 0x80);
    *(undefined8 *)(lVar13 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x94) = uVar14;
    *(byte *)(lVar13 + 0x80) = bVar1 + 1;
LAB_001b31e4:
    printOperand(param_1,0,param_2);
    return;
  case 0x47:
    SStream_concat0(param_2,&DAT_001fc340);
    printOperand(param_1,0,param_2);
    return;
  case 0x48:
    printPredicateOperand(param_1,4,param_2);
    SStream_concat0(param_2,&DAT_001fc128);
    printOperand(param_1,0,param_2);
    goto switchD_001b2168_caseD_4;
  case 0x49:
    printPredicateOperand(param_1,3,param_2);
    SStream_concat0(param_2,&DAT_001fc128);
    printOperand(param_1,0,param_2);
    SStream_concat0(param_2,", ");
    printOperand(param_1,2,param_2);
    goto LAB_001b1fb0;
  default:
    goto switchD_001b2168_default;
  }
  printOperand(param_1,0,param_2);
  SStream_concat0(param_2,", ");
  printOperand(param_1,1,param_2);
LAB_001b1fb0:
  uVar12 = (((ulong)uVar11 & 0x3f000000) >> 0x18) - 1;
  if (0x3a < uVar12) {
switchD_001b21d0_default:
    printOperand(param_1,0,param_2);
    goto LAB_001b1fd8;
  }
  switch(uVar12 & 0xffffffff) {
  case 0:
    MCInst_getOperand(param_1,0);
    iVar7 = MCOperand_getImm();
    switch(iVar7) {
    case 0:
      pcVar19 = "eq";
      break;
    case 1:
      pcVar19 = "ne";
      break;
    case 2:
      pcVar19 = "hs";
      break;
    case 3:
      pcVar19 = "lo";
      break;
    case 4:
      pcVar19 = "mi";
      break;
    case 5:
      pcVar19 = "pl";
      break;
    case 6:
      pcVar19 = "vs";
      break;
    case 7:
      pcVar19 = "vc";
      break;
    case 8:
      pcVar19 = "hi";
      break;
    case 9:
      pcVar19 = "ls";
      break;
    case 10:
      pcVar19 = "ge";
      break;
    case 0xb:
      pcVar19 = "lt";
      break;
    case 0xc:
      pcVar19 = "gt";
      break;
    case 0xd:
      pcVar19 = "le";
      break;
    case 0xe:
      pcVar19 = "al";
      break;
    default:
      pcVar19 = "";
    }
    SStream_concat0(param_2,pcVar19);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
      return;
    }
    *(int *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x74) = iVar7 + 1;
    return;
  case 1:
    uVar14 = *(undefined8 *)(param_1 + 800);
    uVar4 = MCInst_getOpcode(param_1);
    bVar1 = *(byte *)(param_1 + 0x366);
    lVar13 = ARM_get_op_access(uVar14,uVar4);
    if (lVar13 == 0) {
      cVar23 = '\0';
    }
    else {
      cVar23 = *(char *)(lVar13 + (ulong)bVar1);
      if (cVar23 == -0x80) {
        cVar23 = '\0';
      }
    }
    SStream_concat0(param_2,&DAT_001f74a0);
    lVar13 = *(long *)(param_1 + 800);
    MCInst_getOperand(param_1,0);
    MCOperand_getReg();
    uVar14 = (**(code **)(lVar13 + 0x78))();
    SStream_concat0(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 1;
      MCInst_getOperand(param_1,0);
      uVar4 = MCOperand_getReg();
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x98) = uVar4;
      *(char *)(lVar13 + 0xb1) = cVar23;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    SStream_concat0(param_2,&DAT_001fc350);
    lVar13 = *(long *)(param_1 + 800);
    MCInst_getOperand(param_1,0);
    iVar7 = MCOperand_getReg();
    uVar14 = (**(code **)(lVar13 + 0x78))(iVar7 + 1);
    SStream_concat0(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 1;
      MCInst_getOperand(param_1,0);
      iVar7 = MCOperand_getReg();
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(int *)(lVar13 + 0x98) = iVar7 + 1;
      *(char *)(lVar13 + 0xb1) = cVar23;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    SStream_concat0(param_2,&DAT_001fc350);
    lVar13 = *(long *)(param_1 + 800);
    MCInst_getOperand(param_1,0);
    iVar7 = MCOperand_getReg();
    uVar14 = (**(code **)(lVar13 + 0x78))(iVar7 + 2);
    SStream_concat0(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 1;
      MCInst_getOperand(param_1,0);
      iVar7 = MCOperand_getReg();
      iVar7 = iVar7 + 2;
      lVar13 = *(long *)(param_1 + 0x310);
LAB_001b47f0:
      lVar17 = *(long *)(lVar13 + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(int *)(lVar13 + 0x98) = iVar7;
      *(char *)(lVar13 + 0xb1) = cVar23;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    goto LAB_001b4678;
  case 2:
    uVar14 = *(undefined8 *)(param_1 + 800);
    uVar4 = MCInst_getOpcode(param_1);
    bVar1 = *(byte *)(param_1 + 0x366);
    lVar13 = ARM_get_op_access(uVar14,uVar4);
    if (lVar13 == 0) {
      cVar23 = '\0';
    }
    else {
      cVar23 = *(char *)(lVar13 + (ulong)bVar1);
      if (cVar23 == -0x80) {
        cVar23 = '\0';
      }
    }
    SStream_concat0(param_2,&DAT_001f74a0);
    lVar13 = *(long *)(param_1 + 800);
    MCInst_getOperand(param_1,0);
    MCOperand_getReg();
    uVar14 = (**(code **)(lVar13 + 0x78))();
    SStream_concat0(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 1;
      MCInst_getOperand(param_1,0);
      uVar4 = MCOperand_getReg();
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x98) = uVar4;
      *(char *)(lVar13 + 0xb1) = cVar23;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    SStream_concat0(param_2,&DAT_001fc350);
    lVar13 = *(long *)(param_1 + 800);
    MCInst_getOperand(param_1,0);
    iVar7 = MCOperand_getReg();
    uVar14 = (**(code **)(lVar13 + 0x78))(iVar7 + 2);
    SStream_concat0(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 1;
      MCInst_getOperand(param_1,0);
      iVar7 = MCOperand_getReg();
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(int *)(lVar13 + 0x98) = iVar7 + 2;
      *(char *)(lVar13 + 0xb1) = cVar23;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    SStream_concat0(param_2,&DAT_001fc350);
    lVar13 = *(long *)(param_1 + 800);
    MCInst_getOperand(param_1,0);
    iVar7 = MCOperand_getReg();
    uVar14 = (**(code **)(lVar13 + 0x78))(iVar7 + 4);
    SStream_concat0(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 1;
      MCInst_getOperand(param_1,0);
      iVar7 = MCOperand_getReg();
      iVar7 = iVar7 + 4;
      lVar13 = *(long *)(param_1 + 0x310);
      goto LAB_001b47f0;
    }
    goto LAB_001b4678;
  case 3:
    printVectorListThree(param_1,0,param_2);
    SStream_concat0(param_2,", ");
    break;
  case 4:
    uVar14 = *(undefined8 *)(param_1 + 800);
    uVar4 = MCInst_getOpcode(param_1);
    bVar1 = *(byte *)(param_1 + 0x366);
    lVar13 = ARM_get_op_access(uVar14,uVar4);
    if (lVar13 == 0) {
      cVar23 = '\0';
    }
    else {
      cVar23 = *(char *)(lVar13 + (ulong)bVar1);
      if (cVar23 == -0x80) {
        cVar23 = '\0';
      }
    }
    SStream_concat0(param_2,&DAT_001f74a0);
    lVar13 = *(long *)(param_1 + 800);
    MCInst_getOperand(param_1,0);
    MCOperand_getReg();
    uVar14 = (**(code **)(lVar13 + 0x78))();
    SStream_concat0(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 1;
      MCInst_getOperand(param_1,0);
      uVar4 = MCOperand_getReg();
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x98) = uVar4;
      *(char *)(lVar13 + 0xb1) = cVar23;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    SStream_concat0(param_2,", ");
    lVar13 = *(long *)(param_1 + 800);
    MCInst_getOperand(param_1,0);
    iVar7 = MCOperand_getReg();
    uVar14 = (**(code **)(lVar13 + 0x78))(iVar7 + 2);
    SStream_concat0(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 1;
      MCInst_getOperand(param_1,0);
      iVar7 = MCOperand_getReg();
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(int *)(lVar13 + 0x98) = iVar7 + 2;
      *(char *)(lVar13 + 0xb1) = cVar23;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    SStream_concat0(param_2,", ");
    lVar13 = *(long *)(param_1 + 800);
    MCInst_getOperand(param_1,0);
    iVar7 = MCOperand_getReg();
    uVar14 = (**(code **)(lVar13 + 0x78))(iVar7 + 4);
    SStream_concat0(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 1;
      MCInst_getOperand(param_1,0);
      iVar7 = MCOperand_getReg();
      iVar7 = iVar7 + 4;
      lVar13 = *(long *)(param_1 + 0x310);
LAB_001b4e60:
      lVar17 = *(long *)(lVar13 + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(int *)(lVar13 + 0x98) = iVar7;
      *(char *)(lVar13 + 0xb1) = cVar23;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    goto LAB_001b49f0;
  case 5:
    uVar14 = *(undefined8 *)(param_1 + 800);
    uVar4 = MCInst_getOpcode(param_1);
    bVar1 = *(byte *)(param_1 + 0x366);
    lVar13 = ARM_get_op_access(uVar14,uVar4);
    if (lVar13 == 0) {
      cVar23 = '\0';
    }
    else {
      cVar23 = *(char *)(lVar13 + (ulong)bVar1);
      if (cVar23 == -0x80) {
        cVar23 = '\0';
      }
    }
    SStream_concat0(param_2,&DAT_001f74a0);
    lVar13 = *(long *)(param_1 + 800);
    MCInst_getOperand(param_1,0);
    MCOperand_getReg();
    uVar14 = (**(code **)(lVar13 + 0x78))();
    SStream_concat0(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 1;
      MCInst_getOperand(param_1,0);
      uVar4 = MCOperand_getReg();
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x98) = uVar4;
      *(char *)(lVar13 + 0xb1) = cVar23;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    SStream_concat0(param_2,&DAT_001fc350);
    lVar13 = *(long *)(param_1 + 800);
    MCInst_getOperand(param_1,0);
    iVar7 = MCOperand_getReg();
    uVar14 = (**(code **)(lVar13 + 0x78))(iVar7 + 1);
    SStream_concat0(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 1;
      MCInst_getOperand(param_1,0);
      iVar7 = MCOperand_getReg();
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(int *)(lVar13 + 0x98) = iVar7 + 1;
      *(char *)(lVar13 + 0xb1) = cVar23;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    SStream_concat0(param_2,&DAT_001fc350);
    lVar13 = *(long *)(param_1 + 800);
    MCInst_getOperand(param_1,0);
    iVar7 = MCOperand_getReg();
    uVar14 = (**(code **)(lVar13 + 0x78))(iVar7 + 2);
    SStream_concat0(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 1;
      MCInst_getOperand(param_1,0);
      iVar7 = MCOperand_getReg();
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(int *)(lVar13 + 0x98) = iVar7 + 2;
      *(char *)(lVar13 + 0xb1) = cVar23;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    SStream_concat0(param_2,&DAT_001fc350);
    lVar13 = *(long *)(param_1 + 800);
    MCInst_getOperand(param_1,0);
    iVar7 = MCOperand_getReg();
    uVar14 = (**(code **)(lVar13 + 0x78))(iVar7 + 3);
    SStream_concat0(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 1;
      MCInst_getOperand(param_1,0);
      iVar7 = MCOperand_getReg();
      iVar7 = iVar7 + 3;
      lVar13 = *(long *)(param_1 + 0x310);
      goto LAB_001b47f0;
    }
    goto LAB_001b4678;
  case 6:
    uVar14 = *(undefined8 *)(param_1 + 800);
    uVar4 = MCInst_getOpcode(param_1);
    bVar1 = *(byte *)(param_1 + 0x366);
    lVar13 = ARM_get_op_access(uVar14,uVar4);
    if (lVar13 == 0) {
      cVar23 = '\0';
    }
    else {
      cVar23 = *(char *)(lVar13 + (ulong)bVar1);
      if (cVar23 == -0x80) {
        cVar23 = '\0';
      }
    }
    SStream_concat0(param_2,&DAT_001f74a0);
    lVar13 = *(long *)(param_1 + 800);
    MCInst_getOperand(param_1,0);
    MCOperand_getReg();
    uVar14 = (**(code **)(lVar13 + 0x78))();
    SStream_concat0(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 1;
      MCInst_getOperand(param_1,0);
      uVar4 = MCOperand_getReg();
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x98) = uVar4;
      *(char *)(lVar13 + 0xb1) = cVar23;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    SStream_concat0(param_2,&DAT_001fc350);
    lVar13 = *(long *)(param_1 + 800);
    MCInst_getOperand(param_1,0);
    iVar7 = MCOperand_getReg();
    uVar14 = (**(code **)(lVar13 + 0x78))(iVar7 + 2);
    SStream_concat0(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 1;
      MCInst_getOperand(param_1,0);
      iVar7 = MCOperand_getReg();
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(int *)(lVar13 + 0x98) = iVar7 + 2;
      *(char *)(lVar13 + 0xb1) = cVar23;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    SStream_concat0(param_2,&DAT_001fc350);
    lVar13 = *(long *)(param_1 + 800);
    MCInst_getOperand(param_1,0);
    iVar7 = MCOperand_getReg();
    uVar14 = (**(code **)(lVar13 + 0x78))(iVar7 + 4);
    SStream_concat0(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 1;
      MCInst_getOperand(param_1,0);
      iVar7 = MCOperand_getReg();
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(int *)(lVar13 + 0x98) = iVar7 + 4;
      *(char *)(lVar13 + 0xb1) = cVar23;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    SStream_concat0(param_2,&DAT_001fc350);
    lVar13 = *(long *)(param_1 + 800);
    MCInst_getOperand(param_1,0);
    iVar7 = MCOperand_getReg();
    uVar14 = (**(code **)(lVar13 + 0x78))(iVar7 + 6);
    SStream_concat0(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 1;
      MCInst_getOperand(param_1,0);
      iVar7 = MCOperand_getReg();
      iVar7 = iVar7 + 6;
      lVar13 = *(long *)(param_1 + 0x310);
      goto LAB_001b47f0;
    }
LAB_001b4678:
    SStream_concat0(param_2,&DAT_001fc358);
    cVar23 = *(char *)(param_1 + 0x366);
LAB_001b4698:
    *(char *)(param_1 + 0x366) = cVar23 + '\x01';
    SStream_concat0(param_2,", ");
    printAddrMode6Operand(param_1,1,param_2);
    break;
  case 7:
    printVectorListFour(param_1,0,param_2);
    SStream_concat0(param_2,", ");
    break;
  case 8:
    uVar14 = *(undefined8 *)(param_1 + 800);
    uVar4 = MCInst_getOpcode(param_1);
    bVar1 = *(byte *)(param_1 + 0x366);
    lVar13 = ARM_get_op_access(uVar14,uVar4);
    if (lVar13 == 0) {
      cVar23 = '\0';
    }
    else {
      cVar23 = *(char *)(lVar13 + (ulong)bVar1);
      if (cVar23 == -0x80) {
        cVar23 = '\0';
      }
    }
    SStream_concat0(param_2,&DAT_001f74a0);
    lVar13 = *(long *)(param_1 + 800);
    MCInst_getOperand(param_1,0);
    MCOperand_getReg();
    uVar14 = (**(code **)(lVar13 + 0x78))();
    SStream_concat0(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 1;
      MCInst_getOperand(param_1,0);
      uVar4 = MCOperand_getReg();
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x98) = uVar4;
      *(char *)(lVar13 + 0xb1) = cVar23;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    SStream_concat0(param_2,", ");
    lVar13 = *(long *)(param_1 + 800);
    MCInst_getOperand(param_1,0);
    iVar7 = MCOperand_getReg();
    uVar14 = (**(code **)(lVar13 + 0x78))(iVar7 + 2);
    SStream_concat0(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 1;
      MCInst_getOperand(param_1,0);
      iVar7 = MCOperand_getReg();
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(int *)(lVar13 + 0x98) = iVar7 + 2;
      *(char *)(lVar13 + 0xb1) = cVar23;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    SStream_concat0(param_2,", ");
    lVar13 = *(long *)(param_1 + 800);
    MCInst_getOperand(param_1,0);
    iVar7 = MCOperand_getReg();
    uVar14 = (**(code **)(lVar13 + 0x78))(iVar7 + 4);
    SStream_concat0(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 1;
      MCInst_getOperand(param_1,0);
      iVar7 = MCOperand_getReg();
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(int *)(lVar13 + 0x98) = iVar7 + 4;
      *(char *)(lVar13 + 0xb1) = cVar23;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    SStream_concat0(param_2,", ");
    lVar13 = *(long *)(param_1 + 800);
    MCInst_getOperand(param_1,0);
    iVar7 = MCOperand_getReg();
    uVar14 = (**(code **)(lVar13 + 0x78))(iVar7 + 6);
    SStream_concat0(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 1;
      MCInst_getOperand(param_1,0);
      iVar7 = MCOperand_getReg();
      iVar7 = iVar7 + 6;
      lVar13 = *(long *)(param_1 + 0x310);
      goto LAB_001b4e60;
    }
LAB_001b49f0:
    SStream_concat0(param_2,&DAT_001f75a0);
    cVar23 = *(char *)(param_1 + 0x366);
    goto LAB_001b4698;
  case 9:
    printOperand(param_1,2,param_2);
    break;
  case 10:
    printOperand(param_1,1,param_2);
    break;
  case 0xb:
    MCInst_getOperand(param_1,0);
    uVar4 = MCOperand_getImm();
    SStream_concat(param_2,&DAT_001fc008,uVar4);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x94) = 0x41;
      *(undefined4 *)(lVar13 + 0x98) = uVar4;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    goto switchD_001b21d0_caseD_e;
  case 0xc:
    MCInst_getOperand(param_1,2);
    uVar4 = MCOperand_getImm();
    SStream_concat(param_2,&DAT_001fbda8,uVar4);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x94) = 0x40;
      *(undefined4 *)(lVar13 + 0x98) = uVar4;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    SStream_concat0(param_2,", ");
    MCInst_getOperand(param_1,3);
    uVar4 = MCOperand_getImm();
    SStream_concat(param_2,&DAT_001fbda8,uVar4);
    iVar7 = *(int *)(*(long *)(param_1 + 800) + 0x60);
    goto joined_r0x001b456c;
  case 0xd:
    MCInst_getOperand(param_1,1);
    uVar5 = MCOperand_getImm();
    if ((uVar5 >> 2 & 1) == 0) {
      if ((uVar5 >> 1 & 1) != 0) goto LAB_001b7008;
      if ((uVar5 & 1) != 0) goto LAB_001b3dd4;
      if (uVar5 == 0) {
        uVar5 = 0x10;
        SStream_concat0(param_2,&DAT_001fc360);
      }
    }
    else {
      SStream_concat0(param_2,&DAT_00204510);
      if ((uVar5 >> 1 & 1) != 0) {
LAB_001b7008:
        SStream_concat0(param_2,"i");
      }
      if ((uVar5 & 1) != 0) {
LAB_001b3dd4:
        SStream_concat0(param_2,&DAT_001fbfe8);
      }
    }
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(uint *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x70) = uVar5;
    }
    break;
  case 0xe:
    goto switchD_001b21d0_caseD_e;
  case 0xf:
    printGPRPairOperand(param_1,0,param_2);
    SStream_concat0(param_2,", ");
    printAddrMode7Operand(param_1,1,param_2);
    return;
  case 0x10:
    goto switchD_001b5e20_caseD_e;
  case 0x11:
    printAddrMode7Operand(param_1,2,param_2);
    SStream_concat0(param_2,", ");
    break;
  case 0x12:
    goto switchD_001b5e20_caseD_10;
  case 0x13:
    MCInst_getOperand(param_1,1);
    uVar4 = MCOperand_getImm();
    SStream_concat(param_2,&DAT_001fc008,uVar4);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x94) = 0x41;
      *(undefined4 *)(lVar13 + 0x98) = uVar4;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    SStream_concat0(param_2,", ");
    printOperand(param_1,2,param_2);
    SStream_concat0(param_2,", ");
    printOperand(param_1,0,param_2);
    SStream_concat0(param_2,", ");
    MCInst_getOperand(param_1,3);
    uVar4 = MCOperand_getImm();
    SStream_concat(param_2,&DAT_001fbda8,uVar4);
    iVar7 = *(int *)(*(long *)(param_1 + 800) + 0x60);
joined_r0x001b456c:
    if (iVar7 != 0) {
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x94) = 0x40;
      *(undefined4 *)(lVar13 + 0x98) = uVar4;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    SStream_concat0(param_2,", ");
    MCInst_getOperand(param_1,4);
    uVar4 = MCOperand_getImm();
    SStream_concat(param_2,&DAT_001fbda8,uVar4);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x94) = 0x40;
      *(undefined4 *)(lVar13 + 0x98) = uVar4;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
LAB_001b2610:
    SStream_concat0(param_2,", ");
    printOperand(param_1,5,param_2);
    return;
  case 0x14:
    MCInst_getOperand(param_1,2);
    uVar4 = MCOperand_getImm();
    SStream_concat(param_2,&DAT_001fc008,uVar4);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x94) = 0x41;
      *(undefined4 *)(lVar13 + 0x98) = uVar4;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    SStream_concat0(param_2,", ");
    printOperand(param_1,3,param_2);
    SStream_concat0(param_2,", ");
    printOperand(param_1,0,param_2);
    SStream_concat0(param_2,", ");
    printOperand(param_1,1,param_2);
    SStream_concat0(param_2,", ");
    MCInst_getOperand(param_1,4);
    uVar4 = MCOperand_getImm();
    SStream_concat(param_2,&DAT_001fbda8,uVar4);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
      return;
    }
    lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar17 + 0x80);
    lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
    *(undefined4 *)(lVar13 + 0x94) = 0x40;
    *(undefined4 *)(lVar13 + 0x98) = uVar4;
    *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    return;
  case 0x15:
    printMSRMaskOperand(param_1,0,param_2);
    SStream_concat0(param_2,", ");
    break;
  case 0x16:
    MCInst_getOperand(param_1,0);
    uVar3 = MCOperand_getImm();
    uVar11 = binsearch_IndexTypeEncoding(Index_7,0x21,uVar3);
    if (uVar11 != 0xffffffff) {
      uVar11 = *(uint *)(Index_7 + (ulong)uVar11 * 8 + 4);
      SStream_concat0(param_2,(&BankedRegsList)[(ulong)uVar11 * 2]);
      if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
        uVar4 = *(undefined4 *)(&DAT_005ed488 + (ulong)uVar11 * 0x10);
        lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        bVar1 = *(byte *)(lVar17 + 0x80);
        lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
        *(undefined4 *)(lVar13 + 0x94) = 0x43;
        *(undefined4 *)(lVar13 + 0x98) = uVar4;
        *(byte *)(lVar17 + 0x80) = bVar1 + 1;
      }
      SStream_concat0(param_2,", ");
      printOperand(param_1,1,param_2);
      return;
    }
                    /* WARNING: Does not return */
    pcVar2 = (code *)SoftwareBreakpoint(1000,0x1b87dc);
    (*pcVar2)();
  case 0x17:
    MCInst_getOperand(param_1,1);
    uVar6 = MCOperand_getImm();
    uVar11 = uVar6 & 0xff;
    uVar5 = uVar6 >> 8 & 0x1f;
    uVar10 = uVar6 >> 8;
    uVar12 = (ulong)uVar11;
    if (uVar5 == 0xe) {
LAB_001b6fb0:
      if (9 < uVar12) {
LAB_001b6fb8:
        SStream_concat(param_2,"#0x%lx",uVar12);
        goto LAB_001b4258;
      }
    }
    else {
      if (((uVar10 & 0xc) == 8) || ((uVar6 >> 0xb & 1) == 0)) {
        uVar12 = (ulong)uVar11 << ((uVar5 >> 1 & 3) << 3);
        goto LAB_001b6fb0;
      }
      if ((uVar10 & 0xe) == 0xc) {
        iVar7 = (uVar10 & 1) + 1;
        uVar12 = (ulong)(0xffff >> ((2 - iVar7) * 8 & 0x1fU) | uVar11 << (ulong)(uint)(iVar7 * 8));
        goto LAB_001b6fb8;
      }
      if (uVar5 == 0x1e) {
        uVar21 = 0;
        if ((uVar6 & 1) != 0) {
          uVar21 = 0xff;
        }
        if ((uVar6 >> 1 & 1) != 0) {
          uVar21 = uVar21 | 0xff00;
        }
        if ((uVar6 >> 2 & 1) != 0) {
          uVar21 = uVar21 | 0xff0000;
        }
        if ((uVar6 >> 3 & 1) != 0) {
          uVar21 = uVar21 | 0xff000000;
        }
        if ((uVar6 >> 4 & 1) != 0) {
          uVar21 = uVar21 | 0xff00000000;
        }
        if ((uVar6 >> 5 & 1) != 0) {
          uVar21 = uVar21 | 0xff0000000000;
        }
        if ((uVar6 >> 6 & 1) == 0) {
          uVar12 = uVar21;
          if ((uVar6 >> 7 & 1) == 0) goto LAB_001b6fb0;
          uVar12 = uVar21 | 0xff00000000000000;
        }
        else {
          uVar12 = uVar21 | 0xff000000000000;
          if ((uVar6 >> 7 & 1) != 0) {
            uVar12 = uVar21 | 0xffff000000000000;
          }
        }
        goto LAB_001b6fb8;
      }
      uVar12 = 0;
    }
    SStream_concat(param_2,&DAT_001fbb30,uVar12);
LAB_001b4258:
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
      return;
    }
    lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar17 + 0x80);
    lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
    *(undefined4 *)(lVar13 + 0x94) = 2;
    *(int *)(lVar13 + 0x98) = (int)uVar12;
    *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    return;
  case 0x18:
    SStream_concat0(param_2,&DAT_001fc368);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
      return;
    }
    lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar13 + 0x80);
    *(undefined8 *)(lVar13 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x94) = 2;
    *(byte *)(lVar13 + 0x80) = bVar1 + 1;
    return;
  case 0x19:
    goto switchD_001b1f34_default;
  case 0x1a:
    uVar14 = *(undefined8 *)(param_1 + 800);
    uVar4 = MCInst_getOpcode(param_1);
    bVar1 = *(byte *)(param_1 + 0x366);
    lVar13 = ARM_get_op_access(uVar14,uVar4);
    if (lVar13 == 0) {
      cVar23 = '\0';
    }
    else {
      cVar23 = *(char *)(lVar13 + (ulong)bVar1);
      if (cVar23 == -0x80) {
        cVar23 = '\0';
      }
    }
    SStream_concat0(param_2,&DAT_001f74a0);
    lVar13 = *(long *)(param_1 + 800);
    MCInst_getOperand(param_1,0);
    MCOperand_getReg();
    uVar14 = (**(code **)(lVar13 + 0x78))();
    SStream_concat0(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 1;
      MCInst_getOperand(param_1,0);
      uVar4 = MCOperand_getReg();
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x98) = uVar4;
      *(char *)(lVar13 + 0xb1) = cVar23;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    SStream_concat0(param_2,&DAT_001fc358);
    *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
    SStream_concat0(param_2,", ");
    break;
  case 0x1b:
    MCInst_getOperand(param_1,0);
    uVar4 = MCOperand_getReg();
    uVar9 = MCRegisterInfo_getSubReg(*(undefined8 *)(param_1 + 0x3b0),uVar4,1);
    uVar14 = *(undefined8 *)(param_1 + 0x3b0);
    uVar15 = 2;
    goto LAB_001b3fd0;
  case 0x1c:
    printVectorListOne(param_1,0,param_2);
    SStream_concat0(param_2,", ");
    break;
  case 0x1d:
    printVectorListTwo(param_1,0,param_2);
    SStream_concat0(param_2,", ");
    break;
  case 0x1e:
    MCInst_getOperand(param_1,0);
    uVar4 = MCOperand_getReg();
    uVar9 = MCRegisterInfo_getSubReg(*(undefined8 *)(param_1 + 0x3b0),uVar4,1);
    uVar14 = *(undefined8 *)(param_1 + 0x3b0);
    uVar15 = 3;
LAB_001b3fd0:
    uVar4 = MCRegisterInfo_getSubReg(uVar14,uVar4,uVar15);
    uVar14 = *(undefined8 *)(param_1 + 800);
    uVar8 = MCInst_getOpcode(param_1);
    bVar1 = *(byte *)(param_1 + 0x366);
    lVar13 = ARM_get_op_access(uVar14,uVar8);
    if (lVar13 == 0) {
      cVar23 = '\0';
    }
    else {
      cVar23 = *(char *)(lVar13 + (ulong)bVar1);
      if (cVar23 == -0x80) {
        cVar23 = '\0';
      }
    }
    SStream_concat0(param_2,&DAT_001f74a0);
    uVar14 = (**(code **)(*(long *)(param_1 + 800) + 0x78))(uVar9);
    SStream_concat0(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x94) = 1;
      *(undefined4 *)(lVar13 + 0x98) = uVar9;
      *(char *)(lVar13 + 0xb1) = cVar23;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    SStream_concat0(param_2,&DAT_001fc350);
    uVar14 = (**(code **)(*(long *)(param_1 + 800) + 0x78))(uVar4);
    SStream_concat0(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x94) = 1;
      *(undefined4 *)(lVar13 + 0x98) = uVar4;
      *(char *)(lVar13 + 0xb1) = cVar23;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    SStream_concat0(param_2,&DAT_001fc358);
    *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
    SStream_concat0(param_2,", ");
    break;
  case 0x1f:
    printVectorListTwoSpaced(param_1,0,param_2);
    goto switchD_001b21d0_caseD_e;
  case 0x20:
    printOperand(param_1,4,param_2);
    break;
  case 0x21:
    printVectorListOne(param_1,2,param_2);
    SStream_concat0(param_2,", ");
    printAddrMode6Operand(param_1,0,param_2);
    return;
  case 0x22:
    printVectorListFour(param_1,2,param_2);
    SStream_concat0(param_2,", ");
    printAddrMode6Operand(param_1,0,param_2);
    return;
  case 0x23:
    printVectorListFour(param_1,3,param_2);
    SStream_concat0(param_2,", ");
    printAddrMode6Operand(param_1,1,param_2);
    SStream_concat0(param_2,&DAT_001fb3f0);
    return;
  case 0x24:
    printVectorListFour(param_1,4,param_2);
    SStream_concat0(param_2,", ");
    printAddrMode6Operand(param_1,1,param_2);
    SStream_concat0(param_2,", ");
    printOperand(param_1,3,param_2);
    return;
  case 0x25:
    printVectorListThree(param_1,2,param_2);
    SStream_concat0(param_2,", ");
    printAddrMode6Operand(param_1,0,param_2);
    return;
  case 0x26:
    printVectorListThree(param_1,3,param_2);
    SStream_concat0(param_2,", ");
    printAddrMode6Operand(param_1,1,param_2);
    SStream_concat0(param_2,&DAT_001fb3f0);
    return;
  case 0x27:
    printVectorListThree(param_1,4,param_2);
    SStream_concat0(param_2,", ");
    printAddrMode6Operand(param_1,1,param_2);
    SStream_concat0(param_2,", ");
    printOperand(param_1,3,param_2);
    return;
  case 0x28:
    printVectorListOne(param_1,3,param_2);
    SStream_concat0(param_2,", ");
    printAddrMode6Operand(param_1,1,param_2);
    SStream_concat0(param_2,&DAT_001fb3f0);
    return;
  case 0x29:
    printVectorListOne(param_1,4,param_2);
    SStream_concat0(param_2,", ");
    printAddrMode6Operand(param_1,1,param_2);
    SStream_concat0(param_2,", ");
    printOperand(param_1,3,param_2);
    return;
  case 0x2a:
    printVectorListTwo(param_1,2,param_2);
    SStream_concat0(param_2,", ");
    printAddrMode6Operand(param_1,0,param_2);
    return;
  case 0x2b:
    printVectorListTwo(param_1,3,param_2);
    SStream_concat0(param_2,", ");
    printAddrMode6Operand(param_1,1,param_2);
    SStream_concat0(param_2,&DAT_001fb3f0);
    return;
  case 0x2c:
    printVectorListTwo(param_1,4,param_2);
    SStream_concat0(param_2,", ");
    printAddrMode6Operand(param_1,1,param_2);
    SStream_concat0(param_2,", ");
    printOperand(param_1,3,param_2);
    return;
  case 0x2d:
    printVectorListTwoSpaced(param_1,2,param_2);
    SStream_concat0(param_2,", ");
    printAddrMode6Operand(param_1,0,param_2);
    return;
  case 0x2e:
    printVectorListTwoSpaced(param_1,3,param_2);
    SStream_concat0(param_2,", ");
    printAddrMode6Operand(param_1,1,param_2);
    SStream_concat0(param_2,&DAT_001fb3f0);
    return;
  case 0x2f:
    printVectorListTwoSpaced(param_1,4,param_2);
    SStream_concat0(param_2,", ");
    printAddrMode6Operand(param_1,1,param_2);
    SStream_concat0(param_2,", ");
    printOperand(param_1,3,param_2);
    return;
  case 0x30:
switchD_001b1f34_caseD_f:
    printMemBOption_constprop_0(param_1,param_2);
    return;
  case 0x31:
switchD_001b1f34_caseD_10:
    printInstSyncBOption_constprop_0(param_1,param_2);
    return;
  case 0x32:
switchD_001b1f34_caseD_13:
    printAddrModeImm12Operand(param_1,0,param_2,0);
    return;
  case 0x33:
    printT2AddrModeImm8Operand(param_1,0,param_2,0);
    return;
  case 0x34:
    printT2AddrModeSoRegOperand(param_1,0,param_2);
    return;
  case 0x35:
    printThumbLdrLabelOperand(param_1,0,param_2);
    return;
  case 0x36:
    uVar14 = MCInst_getOperand(param_1,0);
    uVar15 = MCInst_getOperand(param_1,1);
    SStream_concat0(param_2,&DAT_001fbd60);
    set_mem_access(param_1,1);
    lVar13 = *(long *)(param_1 + 800);
    MCOperand_getReg(uVar14);
    uVar16 = (**(code **)(lVar13 + 0x78))();
    SStream_concat0(param_2,uVar16);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar13 + 0x80);
      uVar4 = MCOperand_getReg(uVar14);
      *(undefined4 *)(lVar13 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x98) = uVar4;
    }
    SStream_concat0(param_2,", ");
    lVar13 = *(long *)(param_1 + 800);
    MCOperand_getReg(uVar15);
    uVar14 = (**(code **)(lVar13 + 0x78))();
    SStream_concat0(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar13 + 0x80);
      uVar4 = MCOperand_getReg(uVar15);
      *(undefined4 *)(lVar13 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x9c) = uVar4;
    }
    SStream_concat0(param_2,&DAT_001fc378);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 3) {
      return;
    }
    lVar13 = *(long *)(param_1 + 0x310);
    *(undefined1 *)(*(long *)(param_1 + 800) + 0x6c) = 0;
    lVar13 = *(long *)(lVar13 + 0xf0);
    *(char *)(lVar13 + 0x80) = *(char *)(lVar13 + 0x80) + '\x01';
    return;
  case 0x37:
    uVar14 = MCInst_getOperand(param_1,0);
    uVar15 = MCInst_getOperand(param_1,1);
    SStream_concat0(param_2,&DAT_001fbd60);
    set_mem_access(param_1,1);
    lVar13 = *(long *)(param_1 + 800);
    MCOperand_getReg(uVar14);
    uVar16 = (**(code **)(lVar13 + 0x78))();
    SStream_concat0(param_2,uVar16);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar13 + 0x80);
      uVar4 = MCOperand_getReg(uVar14);
      *(undefined4 *)(lVar13 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x98) = uVar4;
    }
    SStream_concat0(param_2,", ");
    lVar13 = *(long *)(param_1 + 800);
    MCOperand_getReg(uVar15);
    uVar14 = (**(code **)(lVar13 + 0x78))();
    SStream_concat0(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar13 + 0x80);
      uVar4 = MCOperand_getReg(uVar15);
      *(undefined4 *)(lVar13 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x9c) = uVar4;
    }
    SStream_concat0(param_2,&DAT_001fc370);
    lVar13 = *(long *)(param_1 + 800);
    iVar7 = *(int *)(lVar13 + 0x60);
    if (iVar7 == 0) {
      return;
    }
    lVar20 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar20 + 0x80);
    lVar17 = lVar20 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
    *(undefined8 *)(lVar17 + 0x8c) = DAT_0020a428;
    *(undefined4 *)(lVar17 + 0xa8) = 1;
    if (iVar7 != 3) {
      return;
    }
    *(undefined1 *)(lVar13 + 0x6c) = 0;
    *(byte *)(lVar20 + 0x80) = bVar1 + 1;
    return;
  case 0x38:
    MCInst_getOperand(param_1,0);
    iVar7 = MCOperand_getImm();
    uVar14 = 0x1fc000;
    if (iVar7 != 0) {
      uVar14 = 0;
    }
    SStream_concat0(param_2,uVar14);
    return;
  case 0x39:
    printOperand(param_1,3,param_2);
    return;
  case 0x3a:
    printRegisterList(param_1,2,param_2);
    return;
  default:
    goto switchD_001b21d0_default;
  }
LAB_001b1fd8:
  uVar12 = (CONCAT44(uVar10,uVar11) >> 0x1e & 0x1f) - 1;
  if (0x1c < uVar12) goto switchD_001b21e8_default;
  switch(uVar12 & 0xffffffff) {
  case 0:
    break;
  case 1:
    goto switchD_001b6bb0_caseD_1;
  case 2:
    printAddrMode6Operand(param_1,1,param_2);
    goto LAB_001b2000;
  case 3:
    printOperand(param_1,1,param_2);
    goto LAB_001b2000;
  case 4:
    uVar14 = MCInst_getOperand(param_1,1);
    uVar10 = MCOperand_getImm();
    uVar11 = (uVar10 >> 7) << 0x1f;
    uVar5 = 0x3e000000;
    if ((uVar10 >> 6 & 1) == 0) {
      uVar11 = uVar11 | 0x40000000;
      uVar5 = 0;
    }
    SStream_concat((double)(float)((uVar10 >> 4 & 3) << 0x17 | (uVar10 & 0xf) << 0x13 |
                                  uVar5 | uVar11),param_2,&DAT_001fc380);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 4;
      uVar10 = MCOperand_getImm(uVar14);
      uVar5 = 0x3e000000;
      uVar11 = (uVar10 >> 7) << 0x1f;
      if ((uVar10 >> 6 & 1) == 0) {
        uVar11 = uVar11 | 0x40000000;
        uVar5 = 0;
      }
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar13 + 0x80);
      *(double *)(lVar13 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x98) =
           (double)(float)((uVar10 >> 4 & 3) << 0x17 | (uVar10 & 0xf) << 0x13 | uVar11 | uVar5);
      *(byte *)(lVar13 + 0x80) = bVar1 + 1;
    }
    break;
  case 5:
    SStream_concat0(param_2,&DAT_001fc388);
    printRegisterList(param_1,4,param_2);
    goto LAB_001b2000;
  case 6:
    MCInst_getOperand(param_1,3);
    uVar11 = MCOperand_getImm();
    if (uVar11 < 10) {
      SStream_concat(param_2,&DAT_001fbed8,uVar11);
    }
    else {
      SStream_concat(param_2,"{0x%x}",uVar11);
    }
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x94) = 2;
      *(uint *)(lVar13 + 0x98) = uVar11;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    break;
  case 7:
    goto switchD_001b7814_caseD_6;
  case 8:
    MCInst_getOperand(param_1,1);
    uVar4 = MCOperand_getImm();
    SStream_concat(param_2,&DAT_001fbda8,uVar4);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x94) = 0x40;
      *(undefined4 *)(lVar13 + 0x98) = uVar4;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
  default:
switchD_001b21e8_default:
    SStream_concat0(param_2,", ");
LAB_001b2000:
    uVar12 = ((ulong)(uVar10 >> 3) & 0x7f) - 1;
    if (uVar12 < 0x40) {
      switch(uVar12 & 0xffffffff) {
      case 0:
        printAddrMode7Operand(param_1,1,param_2);
        return;
      case 1:
        printAddrMode6Operand(param_1,2,param_2);
        break;
      case 2:
        printOperand(param_1,3,param_2);
        break;
      case 3:
        goto switchD_001b1f34_default;
      case 4:
        goto switchD_001b6bb0_caseD_1;
      case 5:
        SStream_concat0(param_2,", ");
        break;
      case 6:
        printT2SOOperand(param_1,1,param_2);
        return;
      case 7:
        printSORegRegOperand(param_1,1,param_2);
        return;
      case 8:
        printAdrLabelOperand_constprop_0(param_1,param_2,0);
        return;
      case 9:
        printBitfieldInvMaskImmOperand(param_1,2,param_2);
        return;
      case 10:
        printOperand(param_1,2,param_2);
        break;
      case 0xb:
switchD_001b5e20_caseD_b:
        printModImmOperand(param_1,1,param_2);
        return;
      case 0xc:
        printSORegImmOperand(param_1,1,param_2);
        return;
      case 0xd:
        printRegisterList(param_1,3,param_2);
        break;
      case 0xe:
switchD_001b5e20_caseD_e:
        printAddrMode5Operand(param_1,2,param_2,0);
        return;
      case 0xf:
        printAddrMode7Operand(param_1,2,param_2);
        break;
      case 0x10:
switchD_001b5e20_caseD_10:
        printAddrMode5Operand(param_1,2,param_2,1);
        SStream_concat0(param_2,&DAT_001fb3f0);
        return;
      case 0x11:
        printAddrModeImm12Operand(param_1,2,param_2,1);
        SStream_concat0(param_2,&DAT_001fb3f0);
        return;
      case 0x12:
        printAddrMode2Operand(param_1,2,param_2);
        SStream_concat0(param_2,&DAT_001fb3f0);
        return;
      case 0x13:
        printAddrModeImm12Operand(param_1,1,param_2,0);
        return;
      case 0x14:
        printAddrMode2Operand(param_1,1,param_2);
        return;
      case 0x15:
        printAddrMode3Operand(param_1,1,param_2,0);
        return;
      case 0x16:
        printAddrMode3Operand(param_1,2,param_2,1);
        SStream_concat0(param_2,&DAT_001fb3f0);
        return;
      case 0x17:
        goto switchD_001b20a4_caseD_1;
      case 0x18:
        printBankedRegOperand(param_1,1,param_2);
        return;
      case 0x19:
        printImmPlusOneOperand(param_1,1,param_2);
        SStream_concat0(param_2,", ");
        printOperand(param_1,2,param_2);
        break;
      case 0x1a:
        printGPRPairOperand(param_1,1,param_2);
        SStream_concat0(param_2,", ");
        printAddrMode7Operand(param_1,2,param_2);
        return;
      case 0x1b:
        SStream_concat0(param_2,&DAT_001fc368);
        if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
          return;
        }
        op_addImm_part_0_isra_0(*(undefined8 *)(param_1 + 0x310),0);
        return;
      case 0x1c:
        printNoHashImmediate(param_1,4,param_2);
        break;
      case 0x1d:
        printNoHashImmediate(param_1,6,param_2);
        break;
      case 0x1e:
        printNoHashImmediate(param_1,8,param_2);
        SStream_concat0(param_2,&DAT_001fc3f0);
        set_mem_access_constprop_0(param_1);
        break;
      case 0x20:
        printNoHashImmediate(param_1,10,param_2);
        SStream_concat0(param_2,&DAT_001fc3f0);
        set_mem_access_constprop_0(param_1);
        printOperand(param_1,1,param_2);
        SStream_concat0(param_2,&DAT_001fbd60);
        set_mem_access(param_1,1);
        printNoHashImmediate(param_1,10,param_2);
        SStream_concat0(param_2,&DAT_001fc3f0);
        set_mem_access_constprop_0(param_1);
        printOperand(param_1,2,param_2);
        SStream_concat0(param_2,&DAT_001fbd60);
        set_mem_access(param_1,1);
        printNoHashImmediate(param_1,10,param_2);
        break;
      case 0x21:
        SStream_concat0(param_2,&DAT_001fc350);
        printOperand(param_1,3,param_2);
      case 0x1f:
        SStream_concat0(param_2,"[]}, ");
        break;
      case 0x22:
        printNoHashImmediate(param_1,0xc,param_2);
        SStream_concat0(param_2,&DAT_001fc3f0);
        set_mem_access_constprop_0(param_1);
        printOperand(param_1,1,param_2);
        SStream_concat0(param_2,&DAT_001fbd60);
        set_mem_access(param_1,1);
        printNoHashImmediate(param_1,0xc,param_2);
        SStream_concat0(param_2,&DAT_001fc3f0);
        set_mem_access_constprop_0(param_1);
        printOperand(param_1,2,param_2);
        SStream_concat0(param_2,&DAT_001fbd60);
        set_mem_access(param_1,1);
        printNoHashImmediate(param_1,0xc,param_2);
        SStream_concat0(param_2,&DAT_001fc3f0);
        set_mem_access_constprop_0(param_1);
        printOperand(param_1,3,param_2);
        SStream_concat0(param_2,&DAT_001fbd60);
        set_mem_access(param_1,1);
        printNoHashImmediate(param_1,0xc,param_2);
        SStream_concat0(param_2,&DAT_001fc400);
        set_mem_access_constprop_0(param_1);
        printAddrMode6Operand(param_1,5,param_2);
        printAddrMode6OffsetOperand(param_1,7,param_2);
        return;
      case 0x23:
        printAddrMode5Operand(param_1,1,param_2,0);
        return;
      case 0x24:
        uVar14 = MCInst_getOperand(param_1,1);
        uVar15 = MCInst_getOperand(param_1,2);
        uVar11 = MCOperand_getImm();
        uVar10 = MCOperand_getImm(uVar15);
        uVar12 = MCOperand_isReg(uVar14);
        if ((uVar12 & 1) == 0) goto LAB_001b7f5c;
        SStream_concat0(param_2,&DAT_001fbd60);
        lVar13 = *(long *)(param_1 + 800);
        MCOperand_getReg(uVar14);
        uVar15 = (**(code **)(lVar13 + 0x78))();
        SStream_concat0(param_2,uVar15);
        if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
          lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          lVar13 = lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30;
          *(undefined4 *)(lVar13 + 0x94) = 3;
          uVar4 = MCOperand_getReg(uVar14);
          lVar17 = *(long *)(param_1 + 0x310);
          *(undefined4 *)(lVar13 + 0x98) = uVar4;
          uVar14 = DAT_0020a3f8;
          lVar13 = *(long *)(lVar17 + 0xf0);
          lVar13 = lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30;
          *(undefined4 *)(lVar13 + 0x9c) = 0;
          *(undefined8 *)(lVar13 + 0xa0) = uVar14;
          *(undefined1 *)(lVar13 + 0xb1) = 1;
        }
        uVar11 = uVar11 & 0xff;
        uVar10 = uVar10 & 0x100;
        if (uVar11 == 0) {
          if (uVar10 == 0) goto LAB_001b6640;
          uVar5 = 0;
          puVar18 = &DAT_001f88c0;
LAB_001b6604:
          SStream_concat(param_2,", #%s%u",puVar18,uVar5);
        }
        else {
          uVar5 = uVar11 << 1;
          if (uVar5 < 10) {
            puVar18 = &DAT_001fc428;
            if (uVar10 != 0) {
              puVar18 = &DAT_001f88c0;
            }
            goto LAB_001b6604;
          }
          puVar18 = &DAT_001fc428;
          if (uVar10 != 0) {
            puVar18 = &DAT_001f88c0;
          }
          SStream_concat(param_2,&DAT_001fbd68,puVar18,uVar5);
        }
        if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
          lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          if (uVar10 == 0) {
            *(uint *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0xa4) = uVar5;
          }
          else {
            *(uint *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0xa4) = uVar11 * -2;
          }
        }
LAB_001b6640:
        SStream_concat0(param_2,&DAT_001fc378);
        if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
          return;
        }
        lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        *(char *)(lVar13 + 0x80) = *(char *)(lVar13 + 0x80) + '\x01';
        return;
      case 0x25:
        printNoHashImmediate(param_1,3,param_2);
        SStream_concat0(param_2,&DAT_001fc400);
        set_mem_access_constprop_0(param_1);
        printAddrMode6Operand(param_1,0,param_2);
        return;
      case 0x26:
        printNoHashImmediate(param_1,5,param_2);
        break;
      case 0x27:
        printNoHashImmediate(param_1,7,param_2);
        SStream_concat0(param_2,&DAT_001fc3f0);
        set_mem_access_constprop_0(param_1);
        printOperand(param_1,5,param_2);
        SStream_concat0(param_2,&DAT_001fbd60);
        set_mem_access(param_1,1);
        printNoHashImmediate(param_1,7,param_2);
        SStream_concat0(param_2,&DAT_001fc3f0);
        set_mem_access_constprop_0(param_1);
        printOperand(param_1,6,param_2);
        SStream_concat0(param_2,&DAT_001fbd60);
        set_mem_access(param_1,1);
        printNoHashImmediate(param_1,7,param_2);
        SStream_concat0(param_2,&DAT_001fc400);
        set_mem_access_constprop_0(param_1);
        printAddrMode6Operand(param_1,1,param_2);
        printAddrMode6OffsetOperand(param_1,3,param_2);
        return;
      case 0x28:
        printOperand(param_1,5,param_2);
        SStream_concat0(param_2,", ");
        printOperand(param_1,6,param_2);
        break;
      case 0x29:
        printVectorListOne(param_1,1,param_2);
        SStream_concat0(param_2,", ");
        printOperand(param_1,2,param_2);
        return;
      case 0x2a:
        printVectorListTwo(param_1,1,param_2);
        SStream_concat0(param_2,", ");
        printOperand(param_1,2,param_2);
        return;
      case 0x2b:
        printVectorListThree(param_1,1,param_2);
        SStream_concat0(param_2,", ");
        printOperand(param_1,2,param_2);
        return;
      case 0x2c:
        printVectorListFour(param_1,1,param_2);
        SStream_concat0(param_2,", ");
        printOperand(param_1,2,param_2);
        return;
      case 0x2d:
        printVectorListOne(param_1,2,param_2);
        SStream_concat0(param_2,", ");
        printOperand(param_1,3,param_2);
        return;
      case 0x2e:
        printVectorListTwo(param_1,2,param_2);
        SStream_concat0(param_2,", ");
        printOperand(param_1,3,param_2);
        return;
      case 0x2f:
        printVectorListThree(param_1,2,param_2);
        SStream_concat0(param_2,", ");
        printOperand(param_1,3,param_2);
        return;
      case 0x30:
        printVectorListFour(param_1,2,param_2);
        SStream_concat0(param_2,", ");
        printOperand(param_1,3,param_2);
        return;
      case 0x31:
        SStream_concat0(param_2,&DAT_001fc408);
        if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
          return;
        }
        ARM_addUserMode_part_0_isra_0(*(undefined8 *)(param_1 + 0x310));
        return;
      case 0x32:
        printT2AddrModeImm8Operand(param_1,1,param_2,0);
        return;
      case 0x33:
        printT2AddrModeImm8Operand(param_1,2,param_2,1);
        SStream_concat0(param_2,&DAT_001fb3f0);
        return;
      case 0x34:
        printThumbLdrLabelOperand(param_1,1,param_2);
        return;
      case 0x35:
        printT2AddrModeSoRegOperand(param_1,1,param_2);
        return;
      case 0x36:
        printT2AddrModeImm0_1020s4Operand(param_1,1,param_2);
        return;
      case 0x37:
        printMSRMaskOperand(param_1,1,param_2);
        return;
      case 0x38:
        goto switchD_001b7814_caseD_24;
      case 0x39:
        printAdrLabelOperand_constprop_0(param_1,param_2,2);
        return;
      case 0x3a:
        printThumbSRImm(param_1,3,param_2);
        return;
      case 0x3b:
        printThumbAddrModeImm5SOperand_constprop_0(param_1,param_2,1);
        return;
      case 0x3c:
        uVar14 = MCInst_getOperand(param_1,1);
        uVar15 = MCInst_getOperand(param_1,2);
        uVar12 = MCOperand_isReg(uVar14);
        if ((uVar12 & 1) != 0) {
          SStream_concat0(param_2,&DAT_001fbd60);
          set_mem_access(param_1,1);
          lVar13 = *(long *)(param_1 + 800);
          MCOperand_getReg(uVar14);
          uVar16 = (**(code **)(lVar13 + 0x78))();
          SStream_concat0(param_2,uVar16);
          if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
            lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
            bVar1 = *(byte *)(lVar13 + 0x80);
            uVar4 = MCOperand_getReg(uVar14);
            *(undefined4 *)(lVar13 + (long)(int)(uint)bVar1 * 0x30 + 0x98) = uVar4;
          }
          iVar7 = MCOperand_getReg(uVar15);
          if (iVar7 != 0) {
            SStream_concat0(param_2,", ");
            uVar14 = (**(code **)(*(long *)(param_1 + 800) + 0x78))(iVar7);
            SStream_concat0(param_2,uVar14);
            if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
              lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
              *(int *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x9c) = iVar7;
            }
          }
          SStream_concat0(param_2,&DAT_001fc378);
          if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 3) {
            return;
          }
          lVar13 = *(long *)(param_1 + 0x310);
          *(undefined1 *)(*(long *)(param_1 + 800) + 0x6c) = 0;
          lVar13 = *(long *)(lVar13 + 0xf0);
          *(char *)(lVar13 + 0x80) = *(char *)(lVar13 + 0x80) + '\x01';
          return;
        }
LAB_001b7f5c:
        printOperand(param_1,1,param_2);
        return;
      case 0x3d:
        printThumbAddrModeImm5SOperand_constprop_0(param_1,param_2,2);
        return;
      case 0x3e:
      case 0x3f:
        printThumbAddrModeImm5SOperand_constprop_0(param_1,param_2,4);
        return;
      default:
        goto switchD_001b5e20_default;
      }
    }
    else {
switchD_001b5e20_default:
      printOperand(param_1,1,param_2);
    }
    uVar12 = ((ulong)(uVar10 >> 10) & 0x1f) - 1;
    if (uVar12 < 0x16) {
      switch(uVar12 & 0xffffffff) {
      case 0:
        return;
      case 1:
switchD_001b6bb0_caseD_1:
        SStream_concat0(param_2,&DAT_001fb3f0);
        return;
      case 2:
        printOperand(param_1,3,param_2);
        break;
      case 3:
        printCImmediate(param_1,2,param_2);
        SStream_concat0(param_2,", ");
        printCImmediate(param_1,3,param_2);
        SStream_concat0(param_2,", ");
        printCImmediate(param_1,4,param_2);
        SStream_concat0(param_2,", ");
        printOperand(param_1,5,param_2);
        return;
      case 4:
        printOperand(param_1,2,param_2);
        break;
      case 5:
        goto switchD_001b20a4_caseD_6;
      case 6:
        printRotImmOperand(param_1,2,param_2);
        return;
      case 7:
        printVectorIndex(param_1,4,param_2);
        break;
      case 8:
        printVectorIndex(param_1,2,param_2);
        return;
      case 9:
        printOperand(param_1,4,param_2);
        return;
      case 10:
        SStream_concat0(param_2,&DAT_001fc400);
        set_mem_access_constprop_0(param_1);
        break;
      case 0xb:
        SStream_concat0(param_2,&DAT_001fc3f0);
        set_mem_access_constprop_0(param_1);
        break;
      case 0xc:
        printOperand(param_1,1,param_2);
        SStream_concat0(param_2,&DAT_001fbd60);
        set_mem_access(param_1,1);
        printNoHashImmediate(param_1,8,param_2);
        break;
      case 0xd:
        goto switchD_001b6bb0_caseD_d;
      case 0xe:
        printAddrMode6Operand(param_1,4,param_2);
        break;
      case 0xf:
        printAddrMode6Operand(param_1,5,param_2);
        printAddrMode6OffsetOperand(param_1,7,param_2);
        return;
      case 0x10:
        goto switchD_001b7814_caseD_1c;
      case 0x11:
        SStream_concat0(param_2,&DAT_001fc410);
        printAddrMode6Operand(param_1,1,param_2);
        printAddrMode6OffsetOperand(param_1,3,param_2);
        return;
      case 0x12:
        printOperand(param_1,5,param_2);
        SStream_concat0(param_2,&DAT_001fbd60);
        set_mem_access(param_1,1);
        printNoHashImmediate(param_1,8,param_2);
        SStream_concat0(param_2,&DAT_001fc3f0);
        set_mem_access_constprop_0(param_1);
        printOperand(param_1,6,param_2);
        SStream_concat0(param_2,&DAT_001fbd60);
        set_mem_access(param_1,1);
        printNoHashImmediate(param_1,8,param_2);
        SStream_concat0(param_2,&DAT_001fc3f0);
        set_mem_access_constprop_0(param_1);
        printOperand(param_1,7,param_2);
        SStream_concat0(param_2,&DAT_001fbd60);
        set_mem_access(param_1,1);
        printNoHashImmediate(param_1,8,param_2);
        SStream_concat0(param_2,&DAT_001fc400);
        set_mem_access_constprop_0(param_1);
        printAddrMode6Operand(param_1,1,param_2);
        printAddrMode6OffsetOperand(param_1,3,param_2);
        return;
      case 0x13:
        SStream_concat0(param_2,&DAT_001fc408);
        if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
          return;
        }
        *(undefined1 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x60) = 1;
        return;
      case 0x14:
        printT2AddrModeImm8s4OffsetOperand(param_1,3,param_2);
        return;
      case 0x15:
        SStream_concat0(param_2,&DAT_001fc418);
        if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
          return;
        }
        op_addImm_part_0_isra_0(*(undefined8 *)(param_1 + 0x310),1);
        return;
      default:
        goto switchD_001b6bb0_default;
      }
    }
    else {
switchD_001b6bb0_default:
      SStream_concat0(param_2,", ");
    }
    uVar12 = ((ulong)(uVar10 >> 0xf) & 0x3f) - 1;
    if (uVar12 < 0x25) {
      switch(uVar12 & 0xffffffff) {
      case 0:
        printOperand(param_1,4,param_2);
        break;
      case 1:
        return;
      case 2:
        printModImmOperand(param_1,2,param_2);
        return;
      case 3:
        printSORegImmOperand(param_1,2,param_2);
        return;
      case 4:
        printBitfieldInvMaskImmOperand(param_1,3,param_2);
        return;
      case 5:
        printCoprocOptionImm_constprop_0(param_1,param_2);
        return;
      case 6:
switchD_001b7814_caseD_6:
        printPostIdxImm8s4Operand_constprop_0(param_1,param_2);
        return;
      case 7:
        uVar14 = MCInst_getOperand(param_1,3);
        uVar15 = MCInst_getOperand(param_1,4);
        uVar11 = MCOperand_getImm();
        uVar11 = uVar11 & 0x1000;
        iVar7 = MCOperand_getReg(uVar14);
        if (iVar7 != 0) {
          puVar18 = &DAT_001fc428;
          if (uVar11 != 0) {
            puVar18 = &DAT_001f88c0;
          }
          SStream_concat0(param_2,puVar18);
          lVar13 = *(long *)(param_1 + 800);
          MCOperand_getReg(uVar14);
          uVar16 = (**(code **)(lVar13 + 0x78))();
          SStream_concat0(param_2,uVar16);
          if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
            lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
            *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 1;
            uVar4 = MCOperand_getReg(uVar14);
            lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
            cVar23 = *(char *)(lVar17 + 0x80);
            lVar13 = lVar17 + (ulong)*(byte *)(lVar17 + 0x80) * 0x30;
            *(undefined4 *)(lVar13 + 0x98) = uVar4;
            *(bool *)(lVar13 + 0xb0) = uVar11 != 0;
            *(undefined1 *)(lVar13 + 0xb1) = 1;
            *(char *)(lVar17 + 0x80) = cVar23 + '\x01';
          }
          uVar11 = MCOperand_getImm(uVar15);
          uVar11 = uVar11 >> 0xd & 7;
          uVar10 = MCOperand_getImm(uVar15);
          if (uVar11 == 0) {
            return;
          }
          if ((uVar10 & 0xfff) == 0 && uVar11 == 2) {
            return;
          }
          printRegImmShift_part_0(param_1,param_2,uVar11,uVar10 & 0xfff);
          return;
        }
        uVar10 = MCOperand_getImm(uVar15);
        uVar10 = uVar10 & 0xfff;
        puVar18 = &DAT_001fc428;
        if (uVar11 != 0) {
          puVar18 = &DAT_001f88c0;
        }
        if (uVar10 < 10) {
          SStream_concat(param_2,"#%s%u",puVar18,uVar10);
        }
        else {
          SStream_concat(param_2,"#%s0x%x",puVar18,uVar10);
        }
        if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
          return;
        }
        lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        cVar23 = *(char *)(lVar17 + 0x80);
        lVar13 = lVar17 + (ulong)*(byte *)(lVar17 + 0x80) * 0x30;
        *(undefined4 *)(lVar13 + 0x94) = 2;
        *(uint *)(lVar13 + 0x98) = uVar10;
        *(bool *)(lVar13 + 0xb0) = uVar11 != 0;
        *(char *)(lVar17 + 0x80) = cVar23 + '\x01';
        return;
      case 8:
        printAddrMode3Operand(param_1,2,param_2,0);
        return;
      case 9:
        printAddrMode7Operand(param_1,3,param_2);
        break;
      case 10:
        printAddrMode3Operand(param_1,3,param_2,1);
        SStream_concat0(param_2,&DAT_001fb3f0);
        return;
      case 0xb:
        MCInst_getOperand(param_1,3);
        uVar10 = MCOperand_getImm();
        uVar11 = uVar10 & 0xff;
        puVar18 = &DAT_001f88c0;
        if ((uVar10 & 0x100) != 0) {
          puVar18 = &DAT_001fc428;
        }
        if (uVar11 < 10) {
          SStream_concat(param_2,"#%s%u",puVar18,uVar11);
        }
        else {
          SStream_concat(param_2,"#%s0x%x",puVar18,uVar11);
        }
        if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
          return;
        }
        lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        cVar23 = *(char *)(lVar13 + 0x80);
        lVar17 = lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30;
        *(undefined4 *)(lVar17 + 0x94) = 2;
        *(uint *)(lVar17 + 0x98) = uVar11;
        *(char *)(lVar13 + 0x80) = cVar23 + '\x01';
        return;
      case 0xc:
        uVar14 = MCInst_getOperand(param_1,3);
        MCInst_getOperand(param_1,4);
        lVar13 = MCOperand_getImm();
        puVar18 = &DAT_001f88c0;
        if (lVar13 != 0) {
          puVar18 = &DAT_001fc428;
        }
        SStream_concat0(param_2,puVar18);
        lVar13 = *(long *)(param_1 + 800);
        MCOperand_getReg(uVar14);
        uVar15 = (**(code **)(lVar13 + 0x78))();
        SStream_concat0(param_2,uVar15);
        if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
          return;
        }
        lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 1;
        uVar4 = MCOperand_getReg(uVar14);
        lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        cVar23 = *(char *)(lVar13 + 0x80);
        lVar17 = lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30;
        *(undefined4 *)(lVar17 + 0x98) = uVar4;
        *(undefined1 *)(lVar17 + 0xb1) = 1;
        *(char *)(lVar13 + 0x80) = cVar23 + '\x01';
        return;
      case 0xd:
        printAddrMode3OffsetOperand(param_1,3,param_2);
        return;
      case 0xe:
        SStream_concat0(param_2,", ");
        break;
      case 0xf:
        printCImmediate(param_1,4,param_2);
        return;
      case 0x10:
        printAddrMode7Operand(param_1,2,param_2);
        return;
      case 0x11:
        printOperand(param_1,3,param_2);
        break;
      case 0x12:
        printComplexRotationOp(param_1,3,param_2,0xb4,0x5a);
        return;
      case 0x13:
        printComplexRotationOp(param_1,4,param_2,0x5a,0);
        return;
      case 0x14:
        printAddrMode6Operand(param_1,1,param_2);
        break;
      case 0x15:
        printAddrMode6Operand(param_1,2,param_2);
        printAddrMode6OffsetOperand(param_1,4,param_2);
        return;
      case 0x16:
        printOperand(param_1,1,param_2);
        SStream_concat0(param_2,&DAT_001fbd60);
        set_mem_access(param_1,1);
        printNoHashImmediate(param_1,6,param_2);
        SStream_concat0(param_2,&DAT_001fc400);
        set_mem_access_constprop_0(param_1);
        printAddrMode6Operand(param_1,2,param_2);
        return;
      case 0x17:
        SStream_concat0(param_2,&DAT_001fc400);
        set_mem_access_constprop_0(param_1);
        printAddrMode6Operand(param_1,3,param_2);
        printAddrMode6OffsetOperand(param_1,5,param_2);
        return;
      case 0x18:
        printAddrMode6OffsetOperand(param_1,6,param_2);
        return;
      case 0x19:
        SStream_concat0(param_2,&DAT_001fc3f0);
        set_mem_access_constprop_0(param_1);
        printOperand(param_1,2,param_2);
        SStream_concat0(param_2,&DAT_001fbd60);
        set_mem_access(param_1,1);
        printNoHashImmediate(param_1,8,param_2);
        SStream_concat0(param_2,&DAT_001fc400);
        set_mem_access_constprop_0(param_1);
        printAddrMode6Operand(param_1,3,param_2);
        return;
      case 0x1a:
        goto switchD_001b7814_caseD_1a;
      case 0x1b:
        printVectorIndex(param_1,4,param_2);
        return;
      case 0x1c:
switchD_001b7814_caseD_1c:
        printVectorIndex(param_1,3,param_2);
        return;
      case 0x1d:
        printOperand(param_1,5,param_2);
        SStream_concat0(param_2,&DAT_001fbd60);
        set_mem_access(param_1,1);
        printNoHashImmediate(param_1,6,param_2);
        SStream_concat0(param_2,&DAT_001fc400);
        set_mem_access_constprop_0(param_1);
        printAddrMode6Operand(param_1,1,param_2);
        printAddrMode6OffsetOperand(param_1,3,param_2);
        return;
      case 0x1e:
        printOperand(param_1,7,param_2);
        SStream_concat0(param_2,&DAT_001fc410);
        printAddrMode6Operand(param_1,1,param_2);
        printAddrMode6OffsetOperand(param_1,3,param_2);
        return;
      case 0x1f:
        printT2SOOperand(param_1,2,param_2);
        return;
      case 0x20:
        printThumbSRImm(param_1,2,param_2);
        return;
      case 0x21:
        printT2AddrModeImm8s4Operand(param_1,3,param_2,1);
        SStream_concat0(param_2,&DAT_001fb3f0);
        return;
      case 0x22:
        printT2AddrModeImm8s4Operand(param_1,2,param_2,0);
        return;
      case 0x23:
        printT2AddrModeImm0_1020s4Operand(param_1,2,param_2);
        return;
      case 0x24:
switchD_001b7814_caseD_24:
        printThumbS4ImmOperand_constprop_0(param_1,param_2);
        return;
      default:
        goto switchD_001b7814_default;
      }
    }
    else {
switchD_001b7814_default:
      printOperand(param_1,2,param_2);
    }
    uVar12 = ((ulong)(uVar10 >> 0x15) & 0xf) - 1;
    if (0xb < uVar12) {
      return;
    }
    switch(uVar12 & 0xffffffff) {
    case 0:
      SStream_concat0(param_2,", ");
      break;
    case 1:
switchD_001b20a4_caseD_1:
      printCImmediate(param_1,3,param_2);
      SStream_concat0(param_2,", ");
      printCImmediate(param_1,4,param_2);
      SStream_concat0(param_2,", ");
      printOperand(param_1,5,param_2);
      return;
    case 2:
      printOperand(param_1,3,param_2);
      SStream_concat0(param_2,", ");
      printCImmediate(param_1,4,param_2);
      return;
    case 3:
      MCInst_getOperand(param_1,3);
      uVar11 = MCOperand_getImm();
      if (uVar11 == 0) {
        return;
      }
      if (uVar11 < 10) {
        SStream_concat(param_2,", lsl #%u",uVar11);
      }
      else {
        SStream_concat(param_2,", lsl #0x%x",uVar11);
      }
      if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
        return;
      }
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      lVar13 = lVar13 + (long)(int)(*(byte *)(lVar13 + 0x80) - 1) * 0x30;
      *(undefined4 *)(lVar13 + 0x8c) = 2;
      *(uint *)(lVar13 + 0x90) = uVar11;
      return;
    case 4:
      MCInst_getOperand(param_1,3);
      uVar12 = MCOperand_getImm();
      uVar21 = uVar12 & 0xffffffff;
      uVar11 = (uint)uVar12;
      if (uVar11 == 0) {
        uVar21 = 0x20;
      }
      else if (uVar11 < 10) {
        SStream_concat(param_2,", asr #%u",uVar12);
        goto LAB_001b81b4;
      }
      uVar11 = (uint)uVar21;
      SStream_concat(param_2,", asr #0x%x",uVar21);
LAB_001b81b4:
      if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
        return;
      }
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      lVar13 = lVar13 + (long)(int)(*(byte *)(lVar13 + 0x80) - 1) * 0x30;
      *(undefined4 *)(lVar13 + 0x8c) = 1;
      *(uint *)(lVar13 + 0x90) = uVar11;
      return;
    case 5:
      printRotImmOperand(param_1,3,param_2);
      return;
    case 6:
switchD_001b20a4_caseD_6:
      printShiftImmOperand_constprop_0(param_1,param_2);
      return;
    case 7:
      printComplexRotationOp(param_1,5,param_2,0x5a,0);
      return;
    case 8:
      SStream_concat0(param_2,&DAT_001fc410);
      break;
    case 9:
      SStream_concat0(param_2,&DAT_001fbd60);
      set_mem_access(param_1,1);
      break;
    case 10:
      printAddrMode6OffsetOperand(param_1,3,param_2);
      return;
    case 0xb:
      printT2AddrModeImm8s4OffsetOperand(param_1,4,param_2);
      return;
    default:
      goto switchD_001b1f34_default;
    }
    uVar12 = ((ulong)(uVar10 >> 0x19) & 0xf) - 1;
    if (uVar12 < 0xb) {
      switch(uVar12 & 0xffffffff) {
      case 0:
        printOperand(param_1,3,param_2);
        if ((uVar10 >> 0x1d & 1) == 0) {
          return;
        }
        SStream_concat0(param_2,&DAT_001fc410);
        if ((uVar10 >> 0x1e & 1) != 0) {
          printAddrMode6Operand(param_1,5,param_2);
          printAddrMode6OffsetOperand(param_1,7,param_2);
          return;
        }
        printAddrMode6Operand(param_1,4,param_2);
        return;
      case 1:
        printImmPlusOneOperand(param_1,3,param_2);
        return;
      case 2:
switchD_001b6bb0_caseD_d:
        printAddrMode6Operand(param_1,3,param_2);
        return;
      case 3:
switchD_001b7814_caseD_1a:
        printAddrMode6Operand(param_1,4,param_2);
        printAddrMode6OffsetOperand(param_1,6,param_2);
        return;
      case 4:
        printNoHashImmediate(param_1,10,param_2);
        SStream_concat0(param_2,&DAT_001fc400);
        set_mem_access_constprop_0(param_1);
        printAddrMode6Operand(param_1,4,param_2);
        return;
      case 5:
        printNoHashImmediate(param_1,4,param_2);
        SStream_concat0(param_2,&DAT_001fc400);
        set_mem_access_constprop_0(param_1);
        printAddrMode6Operand(param_1,0,param_2);
        return;
      case 6:
        printNoHashImmediate(param_1,5,param_2);
        SStream_concat0(param_2,&DAT_001fc3f0);
        set_mem_access_constprop_0(param_1);
        printOperand(param_1,4,param_2);
        SStream_concat0(param_2,&DAT_001fbd60);
        set_mem_access(param_1,1);
        printNoHashImmediate(param_1,5,param_2);
        SStream_concat0(param_2,&DAT_001fc400);
        set_mem_access_constprop_0(param_1);
        printAddrMode6Operand(param_1,0,param_2);
        return;
      case 7:
        printAddrMode6Operand(param_1,0,param_2);
        return;
      case 8:
        printNoHashImmediate(param_1,6,param_2);
        SStream_concat0(param_2,&DAT_001fc3f0);
        set_mem_access_constprop_0(param_1);
        printOperand(param_1,4,param_2);
        SStream_concat0(param_2,&DAT_001fbd60);
        set_mem_access(param_1,1);
        printNoHashImmediate(param_1,6,param_2);
        SStream_concat0(param_2,&DAT_001fc3f0);
        set_mem_access_constprop_0(param_1);
        printOperand(param_1,5,param_2);
        SStream_concat0(param_2,&DAT_001fbd60);
        set_mem_access(param_1,1);
        printNoHashImmediate(param_1,6,param_2);
        SStream_concat0(param_2,&DAT_001fc400);
        set_mem_access_constprop_0(param_1);
        printAddrMode6Operand(param_1,0,param_2);
        return;
      case 9:
        printOperand(param_1,5,param_2);
        SStream_concat0(param_2,&DAT_001fc410);
        printAddrMode6Operand(param_1,0,param_2);
        return;
      case 10:
        printAddrMode7Operand(param_1,3,param_2);
        return;
      }
    }
    printAddrMode3OffsetOperand(param_1,4,param_2);
    return;
  case 9:
    SStream_concat0(param_2,", apsr");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar13 + 0x80);
      *(undefined8 *)(lVar13 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x94) = 0x100000001;
      *(byte *)(lVar13 + 0x80) = bVar1 + 1;
    }
    break;
  case 10:
    SStream_concat0(param_2,", spsr");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar13 + 0x80);
      *(undefined8 *)(lVar13 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x94) = 0xd00000001;
      *(byte *)(lVar13 + 0x80) = bVar1 + 1;
    }
    break;
  case 0xb:
    goto switchD_001b5e20_caseD_b;
  case 0xc:
    SStream_concat0(param_2,&DAT_001fc368);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar13 + 0x80);
      *(undefined8 *)(lVar13 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x94) = 2;
      *(byte *)(lVar13 + 0x80) = bVar1 + 1;
    }
    break;
  case 0xd:
    printOperand(param_1,2,param_2);
    goto LAB_001b2000;
  case 0xe:
    MCInst_getOperand(param_1,2);
    uVar11 = MCOperand_getImm();
    if (uVar11 < 10) {
      SStream_concat(param_2,&DAT_001fbda0,uVar11);
    }
    else {
      SStream_concat(param_2,"[0x%x]",uVar11);
    }
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      uVar10 = *(byte *)(lVar13 + 0x80) - 1;
      *(uint *)(lVar13 + ((-(ulong)(uVar10 >> 0x1f) & 0xfffffffe00000000 | (ulong)uVar10 << 1) +
                         (long)(int)uVar10) * 0x10 + 0x88) = uVar11;
    }
    break;
  case 0xf:
    printAddrMode6Operand(param_1,2,param_2);
    goto LAB_001b2000;
  case 0x10:
    SStream_concat0(param_2,&DAT_001fbd60);
    set_mem_access(param_1,1);
    goto LAB_001b2000;
  case 0x11:
    SStream_concat0(param_2,&DAT_001fc350);
    printOperand(param_1,1,param_2);
    SStream_concat0(param_2,&DAT_001fc350);
    printOperand(param_1,2,param_2);
    goto LAB_001b2000;
  case 0x12:
    SStream_concat0(param_2,", fpscr");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar13 + 0x80);
      *(undefined8 *)(lVar13 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x94) = 0x600000001;
      *(byte *)(lVar13 + 0x80) = bVar1 + 1;
    }
    break;
  case 0x13:
    SStream_concat0(param_2,", fpexc");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar13 + 0x80);
      *(undefined8 *)(lVar13 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x94) = 0x400000001;
      *(byte *)(lVar13 + 0x80) = bVar1 + 1;
    }
    break;
  case 0x14:
    SStream_concat0(param_2,", fpinst");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar13 + 0x80);
      *(undefined8 *)(lVar13 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x94) = 0x500000001;
      *(byte *)(lVar13 + 0x80) = bVar1 + 1;
    }
    break;
  case 0x15:
    SStream_concat0(param_2,", fpinst2");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar13 + 0x80);
      *(undefined8 *)(lVar13 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x94) = 0x2e00000001;
      *(byte *)(lVar13 + 0x80) = bVar1 + 1;
    }
    break;
  case 0x16:
    SStream_concat0(param_2,", fpsid");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar13 + 0x80);
      *(undefined8 *)(lVar13 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x94) = 0x800000001;
      *(byte *)(lVar13 + 0x80) = bVar1 + 1;
    }
    break;
  case 0x17:
    SStream_concat0(param_2,", mvfr0");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar13 + 0x80);
      *(undefined8 *)(lVar13 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x94) = 0x2f00000001;
      *(byte *)(lVar13 + 0x80) = bVar1 + 1;
    }
    break;
  case 0x18:
    SStream_concat0(param_2,", mvfr1");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar13 + 0x80);
      *(undefined8 *)(lVar13 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x94) = 0x3000000001;
      *(byte *)(lVar13 + 0x80) = bVar1 + 1;
    }
    break;
  case 0x19:
    SStream_concat0(param_2,", mvfr2");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar13 + 0x80);
      *(undefined8 *)(lVar13 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x94) = 0x3100000001;
      *(byte *)(lVar13 + 0x80) = bVar1 + 1;
    }
    break;
  case 0x1a:
    MCInst_getOperand(param_1,3);
    uVar11 = MCOperand_getImm();
    if (uVar11 < 10) {
      SStream_concat(param_2,&DAT_001fbda0,uVar11);
    }
    else {
      SStream_concat(param_2,"[0x%x]",uVar11);
    }
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      uVar10 = *(byte *)(lVar13 + 0x80) - 1;
      *(uint *)(lVar13 + ((-(ulong)(uVar10 >> 0x1f) & 0xfffffffe00000000 | (ulong)uVar10 << 1) +
                         (long)(int)uVar10) * 0x10 + 0x88) = uVar11;
    }
    SStream_concat0(param_2,", ");
    printOperand(param_1,2,param_2);
    return;
  case 0x1b:
    MCInst_getOperand(param_1,2);
    iVar7 = MCOperand_getImm();
    printUInt32Bang(param_2,0x10 - iVar7);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x94) = 2;
      *(int *)(lVar13 + 0x98) = 0x10 - iVar7;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    break;
  case 0x1c:
    MCInst_getOperand(param_1,2);
    iVar7 = MCOperand_getImm();
    printUInt32Bang(param_2,0x20 - iVar7);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x94) = 2;
      *(int *)(lVar13 + 0x98) = 0x20 - iVar7;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
  }
switchD_001b1f34_default:
  return;
switchD_001b21d0_caseD_e:
  SStream_concat0(param_2,", ");
  goto LAB_001b1fd8;
}

