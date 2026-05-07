
void file_info_destroy(undefined8 *param_1)

{
  long lVar1;
  void *pvVar2;
  uint uVar3;
  long lVar4;
  void *pvVar5;
  
  if (param_1 == (undefined8 *)0x0) {
    return;
  }
  pvVar5 = (void *)param_1[5];
  if (pvVar5 != (void *)0x0) {
    uVar3 = *(uint *)(param_1 + 6);
    if (uVar3 != 0) {
      lVar4 = 0;
      do {
        while (pvVar2 = (void *)((long)pvVar5 + lVar4 * 0x28), pvVar2 == (void *)0x0) {
          lVar4 = lVar4 + 1;
          if (uVar3 <= (uint)lVar4) goto LAB_00144e54;
        }
        lVar1 = lVar4 + 1;
        free(*(void **)((long)pvVar5 + lVar4 * 0x28));
        *(undefined8 *)((long)pvVar5 + lVar4 * 0x28) = 0;
        free(*(void **)((long)pvVar2 + 8));
        uVar3 = *(uint *)(param_1 + 6);
        pvVar5 = (void *)param_1[5];
        *(undefined8 *)((long)pvVar2 + 8) = 0;
        lVar4 = lVar1;
      } while ((uint)lVar1 < uVar3);
    }
LAB_00144e54:
    free(pvVar5);
    param_1[5] = 0;
  }
  pvVar5 = (void *)param_1[3];
  if (pvVar5 != (void *)0x0) {
    uVar3 = *(uint *)(param_1 + 4);
    if (uVar3 != 0) {
      lVar4 = 0;
      do {
        while ((void *)((long)pvVar5 + lVar4 * 0x38) == (void *)0x0) {
          lVar4 = lVar4 + 1;
          if (uVar3 <= (uint)lVar4) goto LAB_00144ea8;
        }
        lVar1 = lVar4 + 1;
        free(*(void **)((long)pvVar5 + lVar4 * 0x38));
        uVar3 = *(uint *)(param_1 + 4);
        *(undefined8 *)((long)pvVar5 + lVar4 * 0x38) = 0;
        pvVar5 = (void *)param_1[3];
        lVar4 = lVar1;
      } while ((uint)lVar1 < uVar3);
    }
LAB_00144ea8:
    free(pvVar5);
    param_1[3] = 0;
  }
  mapped_file_destroy(*param_1);
  free(param_1);
  return;
}

