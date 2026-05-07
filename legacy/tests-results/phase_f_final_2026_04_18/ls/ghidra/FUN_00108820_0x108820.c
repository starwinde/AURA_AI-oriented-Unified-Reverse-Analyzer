
long FUN_00108820(long *param_1,long param_2,long *param_3,ulong param_4)

{
  undefined8 uVar1;
  ulong uVar2;
  undefined8 *puVar3;
  long *plVar4;
  undefined8 *puVar5;
  long lVar6;
  long lVar7;
  
  uVar2 = (*(code *)param_1[6])(param_2,param_1[2]);
  if ((ulong)param_1[2] <= uVar2) {
                    /* WARNING: Subroutine does not return */
    abort();
  }
  lVar7 = *param_1;
  lVar6 = uVar2 * 0x10;
  puVar5 = (undefined8 *)(lVar7 + lVar6);
  *param_3 = (long)puVar5;
  if (*(long *)(lVar7 + lVar6) == 0) {
    return 0;
  }
  if (*(long *)(lVar7 + lVar6) != param_2) {
    uVar2 = (*(code *)param_1[7])(param_2);
    if ((uVar2 & 1) == 0) {
      while( true ) {
        if ((long *)puVar5[1] == (long *)0x0) {
          return 0;
        }
        if ((*(long *)puVar5[1] == param_2) ||
           (uVar2 = (*(code *)param_1[7])(param_2), (uVar2 & 1) != 0)) break;
        puVar5 = (undefined8 *)puVar5[1];
      }
      plVar4 = (long *)puVar5[1];
      lVar6 = *plVar4;
      if ((param_4 & 1) != 0) {
        puVar5[1] = plVar4[1];
        lVar7 = param_1[9];
        *plVar4 = 0;
        plVar4[1] = lVar7;
        param_1[9] = (long)plVar4;
        return lVar6;
      }
      return lVar6;
    }
    param_2 = *(long *)(lVar7 + lVar6);
  }
  if ((param_4 & 1) != 0) {
    puVar3 = (undefined8 *)puVar5[1];
    if (puVar3 == (undefined8 *)0x0) {
      *(undefined8 *)(lVar7 + lVar6) = 0;
    }
    else {
      uVar1 = puVar3[1];
      *puVar5 = *puVar3;
      puVar5[1] = uVar1;
      lVar6 = param_1[9];
      *puVar3 = 0;
      puVar3[1] = lVar6;
      param_1[9] = (long)puVar3;
    }
  }
  return param_2;
}

