
void FUN_001ce5a4(long param_1,undefined8 param_2,char param_3,ulong param_4)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  long lVar4;
  
  FUN_0018ffd0(param_1,3);
  iVar2 = FUN_001900a0();
  FUN_0018ffd0(param_1,4);
  iVar3 = FUN_001900a0();
  if (param_3 == 'x' && iVar2 == 0) {
    FUN_00190370(param_2,&DAT_001fa820);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar4 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar4 + (ulong)*(byte *)(lVar4 + 0x67) * 0x38 + 0x70) = 1;
    }
  }
  else {
    if (iVar2 == 0) {
      FUN_001903f0(param_2,"%cxt%c",0x75,param_3);
      if ((*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) && (param_3 == 'w')) {
        lVar4 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        *(undefined4 *)(lVar4 + (ulong)*(byte *)(lVar4 + 0x67) * 0x38 + 0x78) = 3;
      }
    }
    else {
      FUN_001903f0(param_2,"%cxt%c",0x73,param_3);
      if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
        lVar4 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        bVar1 = *(byte *)(lVar4 + 0x67);
        if (param_3 == 'x') {
          *(undefined4 *)(lVar4 + ((ulong)bVar1 * 8 - (ulong)bVar1) * 8 + 0x78) = 8;
        }
        else {
          *(undefined4 *)(lVar4 + ((ulong)bVar1 * 8 - (ulong)bVar1) * 8 + 0x78) = 7;
        }
      }
    }
    if (iVar3 == 0) {
      return;
    }
  }
  iVar2 = 0x1f - (int)LZCOUNT((int)((param_4 & 0xffffffff) >> 3));
  FUN_001903f0(param_2,&DAT_001ffc50,iVar2);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
    return;
  }
  lVar4 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
  lVar4 = lVar4 + (ulong)*(byte *)(lVar4 + 0x67) * 0x38;
  *(undefined4 *)(lVar4 + 0x70) = 1;
  *(int *)(lVar4 + 0x74) = iVar2;
  return;
}

