
void arm64_op_addVectorArrSpecifier(long param_1,undefined4 param_2)

{
  uint uVar1;
  long lVar2;
  
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar2 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    uVar1 = *(byte *)(lVar2 + 0x67) - 1;
    *(undefined4 *)
     (lVar2 + ((-(ulong)(uVar1 >> 0x1f) & 0xfffffff800000000 | (ulong)uVar1 << 3) - (long)(int)uVar1
              ) * 8 + 0x6c) = param_2;
  }
  return;
}

