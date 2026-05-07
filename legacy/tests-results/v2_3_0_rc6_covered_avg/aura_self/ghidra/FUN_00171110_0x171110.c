
void FUN_00171110(long *param_1,undefined8 param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  undefined8 *puVar5;
  void *__ptr;
  uint uVar6;
  uint uVar7;
  undefined8 *puVar8;
  
  uVar2 = *(uint *)(param_1 + 2);
  uVar7 = *(uint *)(param_1 + 1);
  uVar1 = *(uint *)((long)param_1 + 0xc);
  uVar4 = 0;
  if (uVar2 != 0) {
    uVar4 = (uVar1 + 1) / uVar2;
  }
  uVar4 = (uVar1 + 1) - uVar4 * uVar2;
  if (uVar4 == uVar7) {
    puVar5 = calloc((ulong)(uVar2 << 1),8);
    uVar3 = uVar2 * 2;
    if (puVar5 == (undefined8 *)0x0) {
      return;
    }
    __ptr = (void *)*param_1;
    if (uVar1 == uVar7) {
      uVar4 = 1;
      puVar8 = puVar5;
    }
    else {
      uVar4 = 0;
      do {
        uVar6 = uVar4;
        uVar4 = 0;
        if (uVar2 != 0) {
          uVar4 = (uVar7 + 1) / uVar2;
        }
        puVar5[uVar6] = *(undefined8 *)((long)__ptr + (ulong)uVar7 * 8);
        uVar7 = (uVar7 + 1) - uVar4 * uVar2;
        uVar4 = uVar6 + 1;
      } while (uVar1 != uVar7);
      uVar4 = uVar6 + 2;
      puVar8 = puVar5 + (uVar6 + 1);
    }
    free(__ptr);
    *param_1 = (long)puVar5;
    uVar7 = 0;
    if (uVar3 != 0) {
      uVar7 = uVar4 / uVar3;
    }
    *(undefined4 *)(param_1 + 1) = 0;
    *(uint *)(param_1 + 2) = uVar3;
    uVar4 = uVar4 - uVar7 * uVar3;
  }
  else {
    puVar8 = (undefined8 *)(*param_1 + (ulong)uVar1 * 8);
  }
  *puVar8 = param_2;
  *(uint *)((long)param_1 + 0xc) = uVar4;
  return;
}

