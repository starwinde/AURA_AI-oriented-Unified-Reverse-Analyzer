
void op_addImm(long param_1,int param_2)

{
  long lVar1;
  int iVar2;
  byte bVar3;
  long lVar4;
  
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    iVar2 = *(int *)(*(long *)(param_1 + 800) + 0x68);
    lVar4 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar3 = *(byte *)(lVar4 + 0xa0);
    lVar1 = lVar4 + ((ulong)bVar3 * 2 + (ulong)bVar3) * 0x10;
    *(undefined4 *)(lVar1 + 0xa8) = 2;
    *(long *)(lVar1 + 0xb0) = (long)param_2;
    if (iVar2 == 2) {
      *(undefined1 *)(param_1 + 5) = 1;
    }
    else {
      if (bVar3 != 0) {
        *(undefined1 *)(lVar1 + 200) = *(undefined1 *)(lVar4 + 200);
        *(byte *)(lVar4 + 0xa0) = bVar3 + 1;
        goto LAB_001e6798;
      }
      *(undefined1 *)(lVar4 + 200) = *(undefined1 *)(param_1 + 0x334);
    }
    *(byte *)(lVar4 + 0xa0) = bVar3 + 1;
  }
LAB_001e6798:
  if (*(char *)(param_1 + 6) == '\0') {
    *(undefined1 *)(param_1 + 6) = *(undefined1 *)(param_1 + 0x334);
  }
  return;
}

