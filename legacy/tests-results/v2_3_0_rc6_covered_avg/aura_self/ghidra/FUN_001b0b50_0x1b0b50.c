
void FUN_001b0b50(long param_1,undefined8 param_2,undefined8 param_3)

{
  uint uVar1;
  int iVar2;
  long lVar3;
  
  FUN_0018ffd0();
  iVar2 = FUN_001900a0();
  if (iVar2 != 0) {
    FUN_00190370(param_3,", ror #");
    if (iVar2 == 2) {
      FUN_00190370(param_3,&DAT_001fd520);
    }
    else if (iVar2 == 3) {
      FUN_00190370(param_3,&DAT_001fdf68);
    }
    else {
      FUN_00190370(param_3,"8");
    }
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar3 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      uVar1 = *(byte *)(lVar3 + 0x80) - 1;
      lVar3 = lVar3 + ((-(ulong)(uVar1 >> 0x1f) & 0xfffffffe00000000 | (ulong)uVar1 << 1) +
                      (long)(int)uVar1) * 0x10;
      *(undefined4 *)(lVar3 + 0x8c) = 4;
      *(int *)(lVar3 + 0x90) = iVar2 << 3;
      return;
    }
  }
  return;
}

