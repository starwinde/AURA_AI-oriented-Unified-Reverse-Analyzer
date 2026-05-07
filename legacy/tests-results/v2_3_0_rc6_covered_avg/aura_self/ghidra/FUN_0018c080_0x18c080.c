
void FUN_0018c080(long *param_1,undefined8 *param_2)

{
  uint uVar1;
  ulong uVar2;
  undefined8 *puVar3;
  void *__ptr;
  uint uVar4;
  uint uVar5;
  long lVar6;
  int iVar7;
  uint uVar8;
  long lVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  
  if (param_1 == (long *)0x0 || param_2 == (undefined8 *)0x0) {
    return;
  }
  uVar5 = *(uint *)(param_1 + 1);
  if (uVar5 != 0) {
    __ptr = (void *)*param_2;
    lVar6 = 0;
    uVar4 = *(uint *)(param_2 + 1);
    uVar8 = *(uint *)((long)param_2 + 0xc);
    do {
      lVar9 = *param_1;
      iVar7 = 0;
      uVar1 = *(uint *)(lVar9 + lVar6 * 0x18 + 0x10);
      if (1 < uVar1) {
        iVar7 = (uVar1 != 2) + 1;
      }
      if (uVar8 <= uVar4) {
        uVar8 = uVar8 << 1;
        if (uVar8 < 0x40) {
          uVar8 = 0x40;
        }
        __ptr = realloc(__ptr,(ulong)uVar8 * 0x18);
        if (__ptr == (void *)0x0) {
          return;
        }
        uVar5 = *(uint *)(param_1 + 1);
        uVar4 = *(uint *)(param_2 + 1);
        *param_2 = __ptr;
        *(uint *)((long)param_2 + 0xc) = uVar8;
      }
      puVar3 = (undefined8 *)(lVar9 + lVar6 * 0x18);
      uVar11 = puVar3[1];
      uVar10 = *puVar3;
      uVar2 = (ulong)uVar4;
      uVar4 = uVar4 + 1;
      *(uint *)(param_2 + 1) = uVar4;
      lVar6 = lVar6 + 1;
      puVar3 = (undefined8 *)((long)__ptr + uVar2 * 0x18);
      puVar3[1] = uVar11;
      *puVar3 = uVar10;
      *(int *)((long)__ptr + uVar2 * 0x18 + 0x10) = iVar7;
    } while ((uint)lVar6 < uVar5);
  }
  return;
}

