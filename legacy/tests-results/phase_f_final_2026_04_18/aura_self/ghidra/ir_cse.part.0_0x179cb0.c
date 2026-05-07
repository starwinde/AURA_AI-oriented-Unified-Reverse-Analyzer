
int ir_cse_part_0(long *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  void *__ptr;
  int *piVar4;
  void *pvVar5;
  long *__s;
  int *piVar6;
  ulong uVar7;
  int *piVar8;
  undefined8 *puVar9;
  undefined8 *puVar10;
  int *piVar11;
  int local_874;
  long local_868 [256];
  long local_68;
  
  local_868[0x7d] = 0;
  __s = local_868;
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  memset(__s,0,0x800);
  if (*(uint *)(param_1 + 1) == 0) {
    local_874 = 0;
  }
  else {
    local_874 = 0;
    puVar10 = (undefined8 *)(*param_1 + 8);
    puVar9 = puVar10 + (ulong)*(uint *)(param_1 + 1) * 10;
    do {
      if (*(uint *)(puVar10 + 1) != 0) {
        piVar6 = (int *)*puVar10;
        piVar11 = piVar6 + (ulong)*(uint *)(puVar10 + 1) * 0x22;
        do {
          if ((piVar6[0x12] == 2) && (iVar1 = *piVar6, iVar1 - 2U < 0x13)) {
            iVar2 = piVar6[10];
            iVar3 = piVar6[6];
            uVar7 = (ulong)(uint)(iVar1 * 0x1f + iVar3 * 0x11 + iVar2 * 7) & 0xff;
            piVar8 = (int *)__s[uVar7];
            for (piVar4 = piVar8; piVar4 != (int *)0x0; piVar4 = *(int **)(piVar4 + 4)) {
              if (((iVar1 == *piVar4) && (iVar3 == piVar4[1])) && (iVar2 == piVar4[2])) {
                *piVar6 = 0;
                local_874 = local_874 + 1;
                piVar6[6] = piVar4[3];
                piVar6[0x12] = 1;
                goto LAB_00179dd8;
              }
            }
            piVar4 = malloc(0x18);
            if (piVar4 != (int *)0x0) {
              *piVar4 = iVar1;
              piVar4[1] = iVar3;
              piVar4[2] = iVar2;
              __s[uVar7] = (long)piVar4;
              piVar4[3] = piVar6[2];
              *(int **)(piVar4 + 4) = piVar8;
            }
          }
LAB_00179dd8:
          piVar6 = piVar6 + 0x22;
        } while (piVar6 != piVar11);
      }
      puVar10 = puVar10 + 10;
    } while (puVar10 != puVar9);
  }
  do {
    __ptr = (void *)*__s;
    while (__ptr != (void *)0x0) {
      pvVar5 = *(void **)((long)__ptr + 0x10);
      free(__ptr);
      __ptr = pvVar5;
    }
    __s = __s + 1;
  } while (__s != &local_68);
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                     local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return local_874;
}

