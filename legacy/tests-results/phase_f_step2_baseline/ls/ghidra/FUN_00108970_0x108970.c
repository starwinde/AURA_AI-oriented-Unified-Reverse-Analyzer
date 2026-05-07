
byte FUN_00108970(long *param_1,undefined8 *param_2,byte param_3)

{
  ulong uVar1;
  long *plVar2;
  ulong uVar3;
  long lVar4;
  long lVar5;
  long lVar6;
  undefined8 *puVar7;
  undefined8 *puVar8;
  long *plVar9;
  long lVar10;
  undefined8 uVar11;
  
  plVar9 = (long *)*param_2;
  plVar2 = (long *)param_2[1];
  if (plVar2 <= plVar9) {
    return 1;
  }
  do {
    while (lVar10 = *plVar9, lVar10 == 0) {
LAB_001089ac:
      plVar9 = plVar9 + 2;
      if (plVar2 <= plVar9) {
        return 1;
      }
    }
    if ((undefined8 *)plVar9[1] != (undefined8 *)0x0) {
      uVar3 = param_1[2];
      puVar8 = (undefined8 *)plVar9[1];
      do {
        uVar11 = *puVar8;
        uVar1 = (*(code *)param_1[6])(uVar11,uVar3);
        uVar3 = param_1[2];
        if (uVar3 <= uVar1) goto LAB_00108b08;
        lVar6 = *param_1;
        lVar10 = uVar1 * 0x10;
        puVar7 = (undefined8 *)puVar8[1];
        if (*(long *)(lVar6 + lVar10) == 0) {
          lVar4 = param_1[3];
          *(undefined8 *)(lVar6 + lVar10) = uVar11;
          lVar10 = param_1[9];
          param_1[3] = lVar4 + 1;
          *puVar8 = 0;
          puVar8[1] = lVar10;
          param_1[9] = (long)puVar8;
        }
        else {
          puVar8[1] = *(undefined8 *)(lVar6 + lVar10 + 8);
          *(undefined8 **)(lVar6 + lVar10 + 8) = puVar8;
        }
        puVar8 = puVar7;
      } while (puVar7 != (undefined8 *)0x0);
      lVar10 = *plVar9;
    }
    plVar9[1] = 0;
    if ((param_3 & 1) == 0) {
      uVar3 = (*(code *)param_1[6])(lVar10,param_1[2]);
      if ((ulong)param_1[2] <= uVar3) {
LAB_00108b08:
                    /* WARNING: Subroutine does not return */
        abort();
      }
      lVar4 = *param_1;
      lVar6 = uVar3 * 0x10;
      if (*(long *)(lVar4 + lVar6) == 0) {
        lVar5 = param_1[3];
        *(long *)(lVar4 + lVar6) = lVar10;
        param_1[3] = lVar5 + 1;
      }
      else {
        plVar2 = (long *)param_1[9];
        if (plVar2 == (long *)0x0) {
          plVar2 = malloc(0x10);
          if (plVar2 == (long *)0x0) {
            return param_3;
          }
        }
        else {
          param_1[9] = plVar2[1];
        }
        lVar5 = *(long *)(lVar4 + lVar6 + 8);
        *plVar2 = lVar10;
        plVar2[1] = lVar5;
        *(long **)(lVar4 + lVar6 + 8) = plVar2;
      }
      lVar10 = param_2[3];
      *plVar9 = 0;
      plVar2 = (long *)param_2[1];
      param_2[3] = lVar10 + -1;
      goto LAB_001089ac;
    }
    plVar2 = (long *)param_2[1];
    plVar9 = plVar9 + 2;
    if (plVar2 <= plVar9) {
      return 1;
    }
  } while( true );
}

