
int FUN_00155db0(long *param_1)

{
  long lVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 *extraout_x10;
  int extraout_w11;
  undefined4 *extraout_x11;
  int extraout_w12;
  ulong uVar8;
  ulong extraout_x13;
  ulong extraout_x13_00;
  void *extraout_x14;
  void *extraout_x14_00;
  void *__ptr;
  long lVar9;
  uint uVar10;
  long lVar11;
  int iVar12;
  
  uVar5 = *(uint *)(param_1 + 1);
  if (uVar5 == 0) {
    return 0;
  }
  lVar11 = 0;
  iVar12 = 0;
  uVar10 = 0;
  do {
    lVar1 = *param_1 + lVar11;
    uVar8 = (ulong)*(uint *)(lVar1 + 0x10);
    if (*(uint *)(lVar1 + 0x10) != 0) {
      lVar9 = 0;
      uVar5 = 0;
LAB_00155e00:
      do {
        puVar2 = (undefined4 *)(*(long *)(lVar1 + 8) + lVar9);
        if (((*(int *)(*(long *)(lVar1 + 8) + lVar9) == 0x1b) && (puVar2[0x18] != 0)) &&
           (iVar6 = FUN_00155b50(param_1,**(undefined4 **)(puVar2 + 0x14)), uVar8 = extraout_x13,
           iVar6 != -1)) {
          __ptr = extraout_x14;
          if (extraout_w11 != 1) {
            puVar7 = (undefined4 *)((long)extraout_x14 + 0x10);
            do {
              iVar6 = FUN_00155b50(param_1,*puVar7);
              uVar8 = extraout_x13_00;
              if (extraout_w12 != iVar6) goto LAB_00155e78;
              puVar7 = extraout_x10;
              __ptr = extraout_x14_00;
              iVar6 = extraout_w12;
            } while (extraout_x11 != extraout_x10);
          }
          if (puVar2[2] != iVar6) {
            uVar3 = *(undefined4 *)((long)__ptr + 4);
            *puVar2 = 0;
            uVar5 = uVar5 + 1;
            puVar2[6] = iVar6;
            puVar2[7] = uVar3;
            iVar12 = iVar12 + 1;
            *(undefined8 *)(puVar2 + 8) = 0;
            lVar9 = lVar9 + 0x90;
            puVar2[0x12] = 1;
            free(__ptr);
            free(*(void **)(puVar2 + 0x16));
            *(undefined8 *)(puVar2 + 0x14) = 0;
            *(undefined8 *)(puVar2 + 0x16) = 0;
            uVar4 = *(uint *)(lVar1 + 0x10);
            uVar8 = (ulong)uVar4;
            puVar2[0x18] = 0;
            if (uVar4 <= uVar5) break;
            goto LAB_00155e00;
          }
        }
LAB_00155e78:
        uVar5 = uVar5 + 1;
        lVar9 = lVar9 + 0x90;
      } while (uVar5 < (uint)uVar8);
      uVar5 = *(uint *)(param_1 + 1);
    }
    uVar10 = uVar10 + 1;
    lVar11 = lVar11 + 0x50;
    if (uVar5 <= uVar10) {
      return iVar12;
    }
  } while( true );
}

