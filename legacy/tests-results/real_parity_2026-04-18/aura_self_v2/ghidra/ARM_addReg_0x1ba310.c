
void ARM_addReg(long param_1,undefined4 param_2)

{
  long lVar1;
  byte bVar2;
  long lVar3;
  
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar3 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar2 = *(byte *)(lVar3 + 0x80);
    lVar1 = lVar3 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10;
    *(undefined4 *)(lVar1 + 0x94) = 1;
    *(undefined4 *)(lVar1 + 0x98) = param_2;
    *(byte *)(lVar3 + 0x80) = bVar2 + 1;
  }
  return;
}

