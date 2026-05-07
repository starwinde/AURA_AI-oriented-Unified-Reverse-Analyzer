
int chase_copy(long *param_1,int param_2)

{
  undefined8 *puVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  undefined8 *puVar5;
  int iVar6;
  
  if ((int)param_1[1] != 0) {
    iVar6 = 0x40;
LAB_0014b688:
    puVar5 = (undefined8 *)(*param_1 + 8);
    puVar1 = puVar5 + (ulong)((int)param_1[1] - 1) * 9;
    while( true ) {
      if (*(uint *)(puVar5 + 1) != 0) {
        piVar3 = (int *)*puVar5;
        piVar4 = piVar3 + (ulong)*(uint *)(puVar5 + 1) * 0x22;
        do {
          if ((((*piVar3 == 0) && (piVar3[2] == param_2)) && (piVar3[0x12] != 0)) &&
             (iVar2 = piVar3[6], iVar2 != param_2)) {
            iVar6 = iVar6 + -1;
            param_2 = iVar2;
            if (iVar6 == 0) {
              return iVar2;
            }
            goto LAB_0014b688;
          }
          piVar3 = piVar3 + 0x22;
        } while (piVar3 != piVar4);
      }
      if (puVar5 == puVar1) break;
      puVar5 = puVar5 + 9;
    }
  }
  return param_2;
}

