
void FUN_001e68a4(long param_1,undefined4 param_2)

{
  uint uVar1;
  long lVar2;
  
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar2 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    uVar1 = *(byte *)(lVar2 + 0xa0) - 1;
    *(undefined4 *)
     (lVar2 + ((-(ulong)(uVar1 >> 0x1f) & 0xfffffffe00000000 | (ulong)uVar1 << 1) + (long)(int)uVar1
              ) * 0x10 + 0xcc) = param_2;
  }
  return;
}

