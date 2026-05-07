
void FUN_001b1fac(long param_1,undefined8 param_2,uint param_3)

{
  byte bVar1;
  int iVar2;
  long lVar3;
  long lVar4;
  
  MCInst_getOperand(param_1,1);
  iVar2 = MCOperand_getImm();
  iVar2 = iVar2 << (ulong)(param_3 & 0x1f);
  if (iVar2 == -0x80000000) {
    SStream_concat0(param_2,&DAT_001fcdd8);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar4 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar4 + 0x80);
      *(undefined8 *)(lVar4 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x94) = 2;
      *(byte *)(lVar4 + 0x80) = bVar1 + 1;
      return;
    }
  }
  else {
    if (iVar2 < 0) {
      SStream_concat(param_2,"#-0x%x",-iVar2);
    }
    else if (iVar2 < 10) {
      SStream_concat(param_2,&DAT_001fcbd8,iVar2);
    }
    else {
      SStream_concat(param_2,"#0x%x",iVar2);
    }
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar3 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar3 + 0x80);
      lVar4 = lVar3 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar4 + 0x94) = 2;
      *(int *)(lVar4 + 0x98) = iVar2;
      *(byte *)(lVar3 + 0x80) = bVar1 + 1;
    }
  }
  return;
}

