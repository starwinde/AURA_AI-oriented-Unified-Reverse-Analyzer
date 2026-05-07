
void printPCRelImm_constprop_0(long param_1,undefined8 param_2)

{
  byte bVar1;
  undefined8 uVar2;
  ulong uVar3;
  long lVar4;
  long lVar5;
  
  uVar2 = MCInst_getOperand(param_1,0);
  uVar3 = MCOperand_isImm();
  if ((uVar3 & 1) == 0) {
    return;
  }
  lVar4 = MCOperand_getImm(uVar2);
  uVar3 = (ulong)*(ushort *)(*(long *)(param_1 + 0x310) + 0x10) + lVar4 + *(long *)(param_1 + 0x318)
  ;
  if (*(int *)(*(long *)(param_1 + 800) + 4) == 8) {
    if ((long)uVar3 < 0) {
      SStream_concat(param_2,"0x%lx",uVar3);
      goto LAB_0018fcc8;
    }
  }
  else {
    uVar3 = uVar3 & 0xffffffff;
  }
  if ((long)uVar3 < 10) {
    SStream_concat(param_2,&DAT_001f9ea0,uVar3);
  }
  else {
    SStream_concat(param_2,"0x%lx",uVar3);
  }
LAB_0018fcc8:
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
    return;
  }
  lVar5 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
  bVar1 = *(byte *)(lVar5 + 0xa0);
  lVar4 = lVar5 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
  *(undefined4 *)(lVar4 + 0xa8) = 2;
  *(undefined1 *)(param_1 + 5) = 1;
  *(ulong *)(lVar4 + 0xb0) = uVar3;
  *(byte *)(lVar5 + 0xa0) = bVar1 + 1;
  return;
}

