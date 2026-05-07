
void FUN_001572d0(long param_1,long param_2,uint param_3,undefined4 param_4)

{
  ulong uVar1;
  long *__ptr;
  size_t __size;
  uint uVar2;
  long *plVar3;
  uint uVar4;
  
  uVar4 = *(uint *)(param_1 + 0x10);
  __ptr = *(long **)(param_1 + 8);
  if (uVar4 == 0) {
    if (*(int *)(param_1 + 0x14) != 0) goto LAB_0015737c;
LAB_001573b8:
    __size = 0xc0;
    uVar2 = 8;
  }
  else {
    plVar3 = __ptr;
    do {
      if (*plVar3 == param_2) {
        *(int *)(plVar3 + 2) = (int)plVar3[2] + 1;
        if (*(uint *)(plVar3 + 1) < param_3) {
          *(uint *)(plVar3 + 1) = param_3;
          *(undefined4 *)((long)plVar3 + 0xc) = param_4;
        }
        return;
      }
      plVar3 = plVar3 + 3;
    } while (__ptr + (ulong)uVar4 * 3 != plVar3);
    uVar2 = *(uint *)(param_1 + 0x14);
    if (uVar4 < uVar2) goto LAB_0015737c;
    if (uVar2 == 0) goto LAB_001573b8;
    uVar2 = uVar2 << 1;
    __size = (ulong)uVar2 * 0x18;
  }
  *(uint *)(param_1 + 0x14) = uVar2;
  __ptr = realloc(__ptr,__size);
  *(long **)(param_1 + 8) = __ptr;
  uVar4 = *(uint *)(param_1 + 0x10);
LAB_0015737c:
  *(uint *)(param_1 + 0x10) = uVar4 + 1;
  uVar1 = (ulong)uVar4;
  __ptr[uVar1 * 3] = param_2;
  *(uint *)(__ptr + uVar1 * 3 + 1) = param_3;
  *(undefined4 *)((long)__ptr + uVar1 * 0x18 + 0xc) = param_4;
  *(undefined4 *)(__ptr + uVar1 * 3 + 2) = 1;
  return;
}

