
void FUN_001cd830(long param_1,undefined4 param_2,undefined8 param_3)

{
  uint uVar1;
  undefined4 uVar2;
  long lVar3;
  
  FUN_00190370(param_3,&DAT_001fdf80);
  FUN_0018ffd0(param_1,param_2);
  uVar2 = FUN_001900a0();
  FUN_00190670(param_3,uVar2);
  FUN_00190370(param_3,&DAT_001fe598);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
    return;
  }
  FUN_0018ffd0(param_1,param_2);
  uVar2 = FUN_001900a0();
  lVar3 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
  uVar1 = *(byte *)(lVar3 + 0x67) - 1;
  *(undefined4 *)
   (lVar3 + ((-(ulong)(uVar1 >> 0x1f) & 0xfffffff800000000 | (ulong)uVar1 << 3) - (long)(int)uVar1)
            * 8 + 0x68) = uVar2;
  return;
}

