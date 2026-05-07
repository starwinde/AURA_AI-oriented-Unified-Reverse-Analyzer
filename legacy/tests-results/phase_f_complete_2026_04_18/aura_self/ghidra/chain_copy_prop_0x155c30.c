
ulong chain_copy_prop(long *param_1)

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
  ulong uVar5;
  ulong extraout_x13;
  ulong extraout_x13_00;
  ulong extraout_x13_01;
  ulong extraout_x13_02;
  long *extraout_x14;
  long *extraout_x14_00;
  long *extraout_x14_01;
  long *extraout_x14_02;
  int *extraout_x15;
  int *piVar6;
  int *extraout_x18;
  int *extraout_x18_00;
  int *extraout_x18_01;
  int *piVar7;
  int *extraout_x18_02;
  undefined8 *puVar8;
  undefined8 *puVar9;
  
  if (*(uint *)(param_1 + 1) == 0) {
    return 0;
  }
  uVar5 = 0;
  puVar8 = (undefined8 *)(*param_1 + 8);
  puVar9 = puVar8 + (ulong)*(uint *)(param_1 + 1) * 10;
  do {
    if (*(uint *)(puVar8 + 1) != 0) {
      piVar3 = (int *)*puVar8;
      piVar7 = piVar3 + (ulong)*(uint *)(puVar8 + 1) * 0x24;
      do {
        while( true ) {
          iVar2 = piVar3[0x12];
          if (iVar2 != 0) {
            if ((piVar3[6] != -1) &&
               (iVar1 = chase_copy_src(param_1,piVar3[6]), piVar3 = extraout_x10,
               uVar5 = extraout_x13, param_1 = extraout_x14, piVar7 = extraout_x18,
               iVar2 = extraout_w11, extraout_w12 != iVar1)) {
              uVar5 = (ulong)((int)extraout_x13 + 1);
              extraout_x10[6] = iVar1;
            }
            if (iVar2 != 1) {
              if ((piVar3[10] != -1) &&
                 (iVar1 = chase_copy_src(param_1,piVar3[10]), piVar3 = extraout_x10_00,
                 uVar5 = extraout_x13_00, param_1 = extraout_x14_00, piVar7 = extraout_x18_00,
                 iVar2 = extraout_w11_00, iVar1 != extraout_w12_00)) {
                uVar5 = (ulong)((int)extraout_x13_00 + 1);
                extraout_x10_00[10] = iVar1;
              }
              if (((iVar2 != 2) && (piVar3[0xe] != -1)) &&
                 (iVar2 = chase_copy_src(param_1,piVar3[0xe]), piVar3 = extraout_x10_01,
                 uVar5 = extraout_x13_01, param_1 = extraout_x14_01, piVar7 = extraout_x18_01,
                 extraout_w11_01 != iVar2)) {
                uVar5 = (ulong)((int)extraout_x13_01 + 1);
                extraout_x10_01[0xe] = iVar2;
              }
            }
          }
          if ((*piVar3 != 0x1b) || (piVar3[0x18] == 0)) break;
          piVar4 = *(int **)(piVar3 + 0x14);
          piVar6 = piVar4 + (ulong)(uint)piVar3[0x18] * 4;
          do {
            if ((*piVar4 != -1) &&
               (iVar2 = chase_copy_src(param_1,*piVar4), piVar3 = extraout_x10_02,
               piVar4 = extraout_x11, uVar5 = extraout_x13_02, param_1 = extraout_x14_02,
               piVar6 = extraout_x15, piVar7 = extraout_x18_02, extraout_w12_01 != iVar2)) {
              uVar5 = (ulong)((int)extraout_x13_02 + 1);
              *extraout_x11 = iVar2;
            }
            piVar4 = piVar4 + 4;
          } while (piVar4 != piVar6);
          piVar3 = piVar3 + 0x24;
          if (piVar3 == piVar7) goto LAB_00155d78;
        }
        piVar3 = piVar3 + 0x24;
      } while (piVar3 != piVar7);
    }
LAB_00155d78:
    puVar8 = puVar8 + 10;
    if (puVar8 == puVar9) {
      return uVar5 & 0xffffffff;
    }
  } while( true );
}

