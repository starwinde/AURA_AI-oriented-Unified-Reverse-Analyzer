
/* WARNING: Removing unreachable block (ram,0x00155c28) */

int chase_copy_src(long *param_1,int param_2)

{
  undefined8 *puVar1;
  uint uVar2;
  int iVar3;
  undefined8 *puVar4;
  int *piVar5;
  int *piVar6;
  int iVar7;
  
  if ((int)param_1[1] != 0) {
    iVar7 = 0x40;
LAB_00155b78:
    uVar2 = *(uint *)(*param_1 + 0x10);
    puVar1 = (undefined8 *)(*param_1 + 8);
    puVar4 = puVar1;
    while( true ) {
      if (uVar2 != 0) {
        piVar5 = (int *)*puVar4;
        piVar6 = piVar5 + (ulong)uVar2 * 0x24;
        do {
          if ((((*piVar5 == 0) && (piVar5[2] == param_2)) && (piVar5[0x12] != 0)) &&
             (iVar3 = piVar5[6], iVar3 != param_2)) {
            iVar7 = iVar7 + -1;
            param_2 = iVar3;
            if (iVar7 == 0) {
              return iVar3;
            }
            goto LAB_00155b78;
          }
          piVar5 = piVar5 + 0x24;
        } while (piVar5 != piVar6);
      }
      if (puVar4 == puVar1 + (ulong)((int)param_1[1] - 1) * 10) break;
      uVar2 = *(uint *)(puVar4 + 0xb);
      puVar4 = puVar4 + 10;
    }
  }
  return param_2;
}

