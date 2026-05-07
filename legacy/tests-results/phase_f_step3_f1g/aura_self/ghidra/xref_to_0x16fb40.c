
uint xref_to(undefined8 *param_1,long param_2,undefined8 *param_3)

{
  long *plVar1;
  undefined8 uVar2;
  uint uVar3;
  uint uVar4;
  long *plVar5;
  void *pvVar6;
  undefined8 *puVar7;
  ulong uVar8;
  undefined8 *puVar9;
  int iVar10;
  uint uVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  
  if (param_3 != (undefined8 *)0x0) {
    *param_3 = 0;
    *(undefined4 *)(param_3 + 1) = 0;
    param_3[2] = 0;
    if ((param_1 != (undefined8 *)0x0) && (uVar3 = *(uint *)(param_1 + 1), uVar3 != 0)) {
      uVar4 = uVar3 - 1;
      param_1 = (undefined8 *)*param_1;
      if (uVar4 < 5) {
        uVar4 = 0;
        uVar11 = 0;
      }
      else {
        iVar10 = 0;
        iVar12 = 0;
        iVar13 = 0;
        iVar14 = 0;
        plVar5 = param_1 + 1;
        do {
          plVar1 = plVar5 + 0xc;
          iVar10 = iVar10 + (uint)(*plVar5 == param_2);
          iVar12 = iVar12 + (uint)(plVar5[3] == param_2);
          iVar13 = iVar13 + (uint)(plVar5[6] == param_2);
          iVar14 = iVar14 + (uint)(plVar5[9] == param_2);
          plVar5 = plVar1;
        } while (plVar1 != param_1 + 1 + (ulong)(uVar4 >> 2) * 0xc);
        uVar11 = iVar10 + iVar12 + iVar13 + iVar14;
        uVar4 = uVar4 & 0xfffffffc;
      }
      if (param_1[(ulong)uVar4 * 3 + 1] == param_2) {
        uVar11 = uVar11 + 1;
      }
      if (uVar4 + 1 < uVar3) {
        if (param_2 == param_1[(ulong)(uVar4 + 1) * 3 + 1]) {
          uVar11 = uVar11 + 1;
        }
        if (uVar4 + 2 < uVar3) {
          if (param_1[(ulong)(uVar4 + 2) * 3 + 1] == param_2) {
            uVar11 = uVar11 + 1;
          }
          if (uVar4 + 3 < uVar3) {
            if (param_1[(ulong)(uVar4 + 3) * 3 + 1] == param_2) {
              uVar11 = uVar11 + 1;
            }
            if ((uVar4 + 4 < uVar3) && (param_2 == param_1[(ulong)(uVar4 + 4) * 3 + 1])) {
              uVar11 = uVar11 + 1;
            }
          }
        }
      }
      if ((uVar11 != 0) && (pvVar6 = calloc((ulong)uVar11,0x18), pvVar6 != (void *)0x0)) {
        uVar8 = 0;
        puVar9 = param_1 + (ulong)uVar3 * 3;
        do {
          if (param_1[1] == param_2) {
            puVar7 = (undefined8 *)((long)pvVar6 + uVar8 * 0x18);
            uVar8 = (ulong)((int)uVar8 + 1);
            uVar2 = param_1[1];
            *puVar7 = *param_1;
            puVar7[1] = uVar2;
            puVar7[2] = param_1[2];
          }
          param_1 = param_1 + 3;
        } while (param_1 != puVar9);
        *param_3 = pvVar6;
        *(uint *)(param_3 + 1) = uVar11;
        param_3[2] = pvVar6;
        return uVar11;
      }
    }
  }
  return 0;
}

