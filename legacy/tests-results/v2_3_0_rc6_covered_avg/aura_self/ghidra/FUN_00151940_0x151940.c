
void FUN_00151940(long param_1)

{
  void *__ptr;
  undefined8 *puVar1;
  size_t __size;
  uint uVar2;
  uint uVar3;
  
  uVar2 = *(uint *)(param_1 + 0x10);
  uVar3 = *(uint *)(param_1 + 0x14);
  __ptr = *(void **)(param_1 + 8);
  if (uVar3 <= uVar2) {
    if (uVar3 == 0) {
      __size = 0x900;
      uVar3 = 0x10;
    }
    else {
      uVar3 = uVar3 << 1;
      __size = (ulong)uVar3 * 0x90;
    }
    __ptr = realloc(__ptr,__size);
    if (__ptr == (void *)0x0) {
      return;
    }
    uVar2 = *(uint *)(param_1 + 0x10);
    *(void **)(param_1 + 8) = __ptr;
    *(uint *)(param_1 + 0x14) = uVar3;
  }
  *(uint *)(param_1 + 0x10) = uVar2 + 1;
  puVar1 = (undefined8 *)((long)__ptr + (ulong)uVar2 * 0x90);
  puVar1[1] = 0;
  *puVar1 = 0;
  puVar1[3] = 0;
  puVar1[2] = 0;
  puVar1[5] = 0;
  puVar1[4] = 0;
  puVar1[7] = 0;
  puVar1[6] = 0;
  puVar1[9] = 0;
  puVar1[8] = 0;
  puVar1[0xb] = 0;
  puVar1[10] = 0;
  puVar1[0xd] = 0;
  puVar1[0xc] = 0;
  puVar1[0xf] = 0;
  puVar1[0xe] = 0;
  puVar1[0x11] = 0;
  puVar1[0x10] = 0;
  return;
}

