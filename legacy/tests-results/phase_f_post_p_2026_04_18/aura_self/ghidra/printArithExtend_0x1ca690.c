
void printArithExtend(long param_1,undefined8 param_2,undefined8 param_3)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  long lVar6;
  undefined *puVar7;
  uint uVar8;
  
  MCInst_getOperand();
  uVar3 = MCOperand_getImm();
  uVar2 = uVar3 >> 3 & 7;
  if (uVar2 - 1 < 7) {
    uVar1 = uVar3 & 7;
    uVar8 = uVar2 + 5;
    if (uVar2 - 2 < 2) {
      MCInst_getOperand(param_1,0);
      iVar4 = MCOperand_getReg();
      MCInst_getOperand(param_1,1);
      iVar5 = MCOperand_getReg();
      if (iVar4 == 5 || iVar5 == 5) {
        if ((uVar8 == 8) || (iVar5 == 7 || iVar4 == 7)) {
LAB_001ca85c:
          if (uVar1 == 0) {
            return;
          }
          SStream_concat0(param_3,", lsl ");
          printInt32Bang(param_3,uVar1);
          if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
            return;
          }
          lVar6 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          uVar2 = *(byte *)(lVar6 + 0x67) - 1;
          lVar6 = lVar6 + ((-(ulong)(uVar2 >> 0x1f) & 0xfffffff800000000 | (ulong)uVar2 << 3) -
                          (long)(int)uVar2) * 8;
          *(undefined4 *)(lVar6 + 0x70) = 1;
          *(uint *)(lVar6 + 0x74) = uVar1;
          return;
        }
        uVar8 = 7;
        puVar7 = &DAT_001fe6c0;
      }
      else if (iVar4 == 7 || iVar5 == 7) {
        if (uVar8 == 7) goto LAB_001ca85c;
        uVar8 = 8;
        puVar7 = &DAT_001fe6b0;
      }
      else {
        puVar7 = &DAT_001fe6b0;
        if (uVar8 != 8) {
          puVar7 = &DAT_001fe6c0;
        }
      }
    }
    else if (uVar8 == 10) {
      puVar7 = &DAT_001fddc0;
    }
    else if (uVar8 < 0xb) {
      if (uVar8 == 9) {
        puVar7 = &DAT_001fddb0;
      }
      else {
        uVar8 = 6;
        puVar7 = &DAT_001fdf00;
      }
    }
    else if (uVar8 == 0xb) {
      puVar7 = &DAT_001fe6a8;
    }
    else {
      uVar8 = 0xc;
      puVar7 = &DAT_001fe6b8;
    }
    SStream_concat(param_3,&DAT_001fe6c8,puVar7);
    iVar4 = uVar8 - 4;
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) goto joined_r0x001ca720;
  }
  else {
    SStream_concat(param_3,&DAT_001fe6c8,&DAT_001fdef0);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) goto joined_r0x001ca720;
    iVar4 = 1;
  }
  lVar6 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
  uVar2 = *(byte *)(lVar6 + 0x67) - 1;
  *(int *)(lVar6 + ((-(ulong)(uVar2 >> 0x1f) & 0xfffffff800000000 | (ulong)uVar2 << 3) -
                   (long)(int)uVar2) * 8 + 0x78) = iVar4;
joined_r0x001ca720:
  if ((uVar3 & 7) != 0) {
    SStream_concat0(param_3,&DAT_001fd008);
    printInt32Bang(param_3,uVar3 & 7);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar6 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      uVar2 = *(byte *)(lVar6 + 0x67) - 1;
      lVar6 = lVar6 + ((-(ulong)(uVar2 >> 0x1f) & 0xfffffff800000000 | (ulong)uVar2 << 3) -
                      (long)(int)uVar2) * 8;
      *(undefined4 *)(lVar6 + 0x70) = 1;
      *(uint *)(lVar6 + 0x74) = uVar3 & 7;
      return;
    }
  }
  return;
}

