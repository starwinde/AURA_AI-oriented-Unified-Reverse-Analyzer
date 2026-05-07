
undefined8 * FUN_001446dc(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  undefined8 *__ptr;
  
  uVar3 = param_1 - 1;
  if (uVar3 < 4) {
    uVar2 = *(undefined4 *)(&DAT_0020c530 + (ulong)uVar3 * 4);
    uVar1 = *(undefined4 *)(&DAT_0020c540 + (ulong)uVar3 * 4);
    __ptr = calloc(1,0x10);
    if (__ptr != (undefined8 *)0x0) {
      *(int *)(__ptr + 1) = param_1;
      iVar4 = FUN_0018c6b4(uVar2,uVar1,__ptr);
      if (iVar4 == 0) {
        FUN_0018c8d4(*__ptr,1);
        FUN_0018c8d4(*__ptr,2,0);
        return __ptr;
      }
      free(__ptr);
    }
  }
  return (undefined8 *)0x0;
}

