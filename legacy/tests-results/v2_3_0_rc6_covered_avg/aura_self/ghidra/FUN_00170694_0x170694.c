
uint FUN_00170694(undefined8 *param_1,long param_2,undefined8 *param_3)

{
  long lVar1;
  uint uVar2;
  uint uVar3;
  long *plVar4;
  void *pvVar5;
  long *plVar6;
  ulong uVar7;
  long *plVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  
  if (param_3 != (undefined8 *)0x0) {
    *param_3 = 0;
    *(undefined4 *)(param_3 + 1) = 0;
    param_3[2] = 0;
    if ((param_1 != (undefined8 *)0x0) && (uVar2 = *(uint *)(param_1 + 1), uVar2 != 0)) {
      uVar3 = uVar2 - 1;
      plVar8 = (long *)*param_1;
      if (uVar3 < 5) {
        uVar3 = 0;
        uVar10 = 0;
      }
      else {
        iVar9 = 0;
        iVar11 = 0;
        iVar12 = 0;
        iVar13 = 0;
        plVar4 = plVar8;
        do {
          plVar6 = plVar4 + 0xc;
          iVar9 = iVar9 + (uint)(*plVar4 == param_2);
          iVar11 = iVar11 + (uint)(plVar4[3] == param_2);
          iVar12 = iVar12 + (uint)(plVar4[6] == param_2);
          iVar13 = iVar13 + (uint)(plVar4[9] == param_2);
          plVar4 = plVar6;
        } while (plVar6 != plVar8 + (ulong)(uVar3 >> 2) * 0xc);
        uVar10 = iVar9 + iVar11 + iVar12 + iVar13;
        uVar3 = uVar3 & 0xfffffffc;
      }
      if (plVar8[(ulong)uVar3 * 3] == param_2) {
        uVar10 = uVar10 + 1;
      }
      if (uVar3 + 1 < uVar2) {
        if (param_2 == plVar8[(ulong)(uVar3 + 1) * 3]) {
          uVar10 = uVar10 + 1;
        }
        if (uVar3 + 2 < uVar2) {
          if (plVar8[(ulong)(uVar3 + 2) * 3] == param_2) {
            uVar10 = uVar10 + 1;
          }
          if (uVar3 + 3 < uVar2) {
            if (plVar8[(ulong)(uVar3 + 3) * 3] == param_2) {
              uVar10 = uVar10 + 1;
            }
            if ((uVar3 + 4 < uVar2) && (param_2 == plVar8[(ulong)(uVar3 + 4) * 3])) {
              uVar10 = uVar10 + 1;
            }
          }
        }
      }
      if ((uVar10 != 0) && (pvVar5 = calloc((ulong)uVar10,0x18), pvVar5 != (void *)0x0)) {
        uVar7 = 0;
        plVar4 = plVar8 + (ulong)uVar2 * 3;
        do {
          if (*plVar8 == param_2) {
            plVar6 = (long *)((long)pvVar5 + uVar7 * 0x18);
            uVar7 = (ulong)((int)uVar7 + 1);
            lVar1 = plVar8[1];
            *plVar6 = *plVar8;
            plVar6[1] = lVar1;
            plVar6[2] = plVar8[2];
          }
          plVar8 = plVar8 + 3;
        } while (plVar8 != plVar4);
        *param_3 = pvVar5;
        *(uint *)(param_3 + 1) = uVar10;
        param_3[2] = pvVar5;
        return uVar10;
      }
    }
  }
  return 0;
}

