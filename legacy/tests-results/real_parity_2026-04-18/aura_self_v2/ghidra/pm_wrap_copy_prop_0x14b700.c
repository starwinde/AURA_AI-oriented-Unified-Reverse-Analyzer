
ulong pm_wrap_copy_prop(long *param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int *extraout_x10;
  int *extraout_x10_00;
  int *extraout_x10_01;
  int *extraout_x10_02;
  int extraout_w11;
  int extraout_w11_00;
  int extraout_w11_01;
  int *piVar4;
  int *extraout_x11;
  int extraout_w12;
  int extraout_w12_00;
  int extraout_w12_01;
  long *extraout_x13;
  long *extraout_x13_00;
  long *extraout_x13_01;
  long *extraout_x13_02;
  int *extraout_x14;
  int *piVar5;
  int *extraout_x15;
  int *extraout_x15_00;
  int *extraout_x15_01;
  int *piVar6;
  int *extraout_x15_02;
  ulong uVar7;
  ulong extraout_x18;
  ulong extraout_x18_00;
  ulong extraout_x18_01;
  ulong extraout_x18_02;
  undefined8 *puVar8;
  undefined8 *puVar9;
  
  if (*(uint *)(param_1 + 1) == 0) {
    return 0;
  }
  uVar7 = 0;
  puVar8 = (undefined8 *)(*param_1 + 8);
  puVar9 = puVar8 + (ulong)*(uint *)(param_1 + 1) * 9;
  do {
    if (*(uint *)(puVar8 + 1) != 0) {
      piVar3 = (int *)*puVar8;
      piVar6 = piVar3 + (ulong)*(uint *)(puVar8 + 1) * 0x22;
      do {
        iVar2 = piVar3[0x12];
        if (iVar2 != 0) {
          if ((piVar3[6] != -1) &&
             (iVar1 = chase_copy(param_1,piVar3[6]), piVar3 = extraout_x10, param_1 = extraout_x13,
             piVar6 = extraout_x15, uVar7 = extraout_x18, iVar2 = extraout_w11,
             extraout_w12 != iVar1)) {
            uVar7 = 1;
            extraout_x10[6] = iVar1;
          }
          if (iVar2 != 1) {
            if ((piVar3[10] != -1) &&
               (iVar1 = chase_copy(param_1,piVar3[10]), piVar3 = extraout_x10_00,
               param_1 = extraout_x13_00, piVar6 = extraout_x15_00, uVar7 = extraout_x18_00,
               iVar2 = extraout_w11_00, iVar1 != extraout_w12_00)) {
              uVar7 = 1;
              extraout_x10_00[10] = iVar1;
            }
            if (((iVar2 != 2) && (piVar3[0xe] != -1)) &&
               (iVar2 = chase_copy(param_1,piVar3[0xe]), piVar3 = extraout_x10_01,
               param_1 = extraout_x13_01, piVar6 = extraout_x15_01, uVar7 = extraout_x18_01,
               extraout_w11_01 != iVar2)) {
              uVar7 = 1;
              extraout_x10_01[0xe] = iVar2;
            }
          }
        }
        if ((*piVar3 == 0x1b) && (piVar3[0x18] != 0)) {
          piVar4 = *(int **)(piVar3 + 0x14);
          piVar5 = piVar4 + (ulong)(uint)piVar3[0x18] * 4;
          do {
            if ((*piVar4 != -1) &&
               (iVar2 = chase_copy(param_1,*piVar4), piVar3 = extraout_x10_02, piVar4 = extraout_x11
               , param_1 = extraout_x13_02, piVar5 = extraout_x14, piVar6 = extraout_x15_02,
               uVar7 = extraout_x18_02, extraout_w12_01 != iVar2)) {
              uVar7 = 1;
              *extraout_x11 = iVar2;
            }
            piVar4 = piVar4 + 4;
          } while (piVar4 != piVar5);
        }
        piVar3 = piVar3 + 0x22;
      } while (piVar3 != piVar6);
    }
    puVar8 = puVar8 + 9;
  } while (puVar8 != puVar9);
  return uVar7 & 0xffffffff;
}

