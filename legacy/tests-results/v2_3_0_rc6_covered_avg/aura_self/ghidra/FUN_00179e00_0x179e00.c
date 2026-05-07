
void FUN_00179e00(undefined8 *param_1,undefined8 *param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  uint uVar3;
  void *__ptr;
  uint uVar4;
  undefined8 *puVar5;
  
  if (param_1 == (undefined8 *)0x0 || param_2 == (undefined8 *)0x0) {
    return;
  }
  uVar4 = *(uint *)(param_1 + 1);
  __ptr = (void *)*param_1;
  if (*(uint *)((long)param_1 + 0xc) <= uVar4) {
    uVar3 = *(uint *)((long)param_1 + 0xc) << 1;
    __ptr = realloc(__ptr,(ulong)uVar3 * 0x18);
    if (__ptr == (void *)0x0) {
      return;
    }
    uVar4 = *(uint *)(param_1 + 1);
    *param_1 = __ptr;
    *(uint *)((long)param_1 + 0xc) = uVar3;
  }
  uVar1 = *param_2;
  uVar2 = param_2[1];
  puVar5 = (undefined8 *)((long)__ptr + (ulong)uVar4 * 0x18);
  *(uint *)(param_1 + 1) = uVar4 + 1;
  *puVar5 = uVar1;
  puVar5[1] = uVar2;
  puVar5[2] = param_2[2];
  return;
}

