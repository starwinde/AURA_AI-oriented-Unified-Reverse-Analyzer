
void FUN_001b30fc(long param_1,undefined8 param_2,uint param_3)

{
  byte bVar1;
  int iVar2;
  long lVar3;
  long lVar4;
  
  FUN_0018ffd0(param_1,1);
  iVar2 = FUN_001900a0();
  iVar2 = iVar2 << (ulong)(param_3 & 0x1f);
  if (iVar2 == -0x80000000) {
    FUN_00190370(param_2,&DAT_001fdf78);
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
      FUN_001903f0(param_2,"#-0x%x",-iVar2);
    }
    else if (iVar2 < 10) {
      FUN_001903f0(param_2,&DAT_001fdd78,iVar2);
    }
    else {
      FUN_001903f0(param_2,"#0x%x",iVar2);
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

