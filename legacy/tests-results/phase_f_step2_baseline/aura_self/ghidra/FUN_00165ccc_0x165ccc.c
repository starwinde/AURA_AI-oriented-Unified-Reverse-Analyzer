
void FUN_00165ccc(undefined8 *param_1,long param_2,undefined4 param_3,char *param_4)

{
  uint uVar1;
  long *__ptr;
  char *pcVar2;
  void *pvVar3;
  long lVar4;
  long *plVar5;
  uint uVar6;
  
  uVar6 = *(uint *)(param_1 + 1);
  if (0x3ff < uVar6 || param_2 == 0) {
    return;
  }
  __ptr = (long *)*param_1;
  if (uVar6 != 0) {
    plVar5 = __ptr;
    do {
      lVar4 = *plVar5;
      plVar5 = plVar5 + 3;
      if (param_2 == lVar4) {
        return;
      }
    } while (__ptr + (ulong)uVar6 * 3 != plVar5);
  }
  if (uVar6 < *(uint *)((long)param_1 + 0xc)) {
    plVar5 = __ptr + (ulong)uVar6 * 3;
    __ptr[(ulong)uVar6 * 3] = param_2;
    *(undefined4 *)(plVar5 + 1) = param_3;
  }
  else {
    uVar1 = *(uint *)((long)param_1 + 0xc) << 1;
    if (0x400 < uVar1) {
      uVar1 = 0x400;
    }
    pvVar3 = realloc(__ptr,(ulong)uVar1 * 0x18);
    if (pvVar3 == (void *)0x0) {
      return;
    }
    uVar6 = *(uint *)(param_1 + 1);
    *(uint *)((long)param_1 + 0xc) = uVar1;
    *param_1 = pvVar3;
    plVar5 = (long *)((long)pvVar3 + (ulong)uVar6 * 0x18);
    *(long *)((long)pvVar3 + (ulong)uVar6 * 0x18) = param_2;
    *(undefined4 *)(plVar5 + 1) = param_3;
  }
  pcVar2 = strdup(param_4);
  plVar5[2] = (long)pcVar2;
  *(uint *)(param_1 + 1) = uVar6 + 1;
  return;
}

