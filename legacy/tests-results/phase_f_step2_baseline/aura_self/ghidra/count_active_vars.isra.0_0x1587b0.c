
uint count_active_vars_isra_0(long param_1,uint param_2,uint param_3)

{
  uint uVar1;
  void *__ptr;
  uint *puVar2;
  uint *puVar3;
  long *plVar4;
  long *plVar5;
  uint uVar6;
  
  if ((param_3 != 0) && (__ptr = calloc((ulong)param_3,1), __ptr != (void *)0x0)) {
    uVar6 = 0;
    if (param_2 != 0) {
      plVar4 = (long *)(param_1 + 8);
      plVar5 = plVar4 + (ulong)param_2 * 9;
      uVar6 = 0;
      do {
        if (*(uint *)(plVar4 + 1) != 0) {
          puVar2 = (uint *)(*plVar4 + 8);
          puVar3 = puVar2 + (ulong)*(uint *)(plVar4 + 1) * 0x22;
          do {
            uVar1 = *puVar2;
            puVar2 = puVar2 + 0x22;
            if ((uVar1 < param_3) && (*(char *)((long)__ptr + (ulong)uVar1) == '\0')) {
              uVar6 = uVar6 + 1;
              *(undefined1 *)((long)__ptr + (ulong)uVar1) = 1;
            }
          } while (puVar2 != puVar3);
        }
        plVar4 = plVar4 + 9;
      } while (plVar4 != plVar5);
    }
    free(__ptr);
    return uVar6;
  }
  return param_3;
}

