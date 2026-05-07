
void dfs_mark(long *param_1,ulong param_2,long param_3,long param_4)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  long lVar4;
  long lVar5;
  long lVar6;
  ulong uVar7;
  long lVar8;
  ulong uVar9;
  long lVar10;
  long lVar11;
  long lVar12;
  long lVar13;
  long lVar14;
  long lVar15;
  long lVar16;
  ulong uVar17;
  long lVar18;
  long lVar19;
  
  lVar5 = *param_1;
  *(undefined4 *)(param_3 + (param_2 & 0xffffffff) * 4) = 1;
  lVar14 = lVar5 + (param_2 & 0xffffffff) * 0x50;
  uVar3 = *(uint *)(lVar14 + 0x30);
  if (uVar3 != 0) {
    lVar19 = *(long *)(lVar14 + 0x28);
    lVar12 = 0;
    do {
      uVar1 = *(uint *)(lVar19 + lVar12 * 4);
      if (uVar1 < *(uint *)(param_1 + 1)) {
        uVar17 = (ulong)uVar1;
        iVar2 = *(int *)(param_3 + uVar17 * 4);
        if (iVar2 == 1) {
          *(undefined1 *)(param_4 + (ulong)uVar1) = 1;
        }
        else if (iVar2 == 0) {
          *(undefined4 *)(param_3 + uVar17 * 4) = 1;
          lVar13 = lVar5 + (ulong)uVar1 * 0x50;
          uVar3 = *(uint *)(lVar13 + 0x30);
          if (uVar3 != 0) {
            lVar18 = *(long *)(lVar13 + 0x28);
            lVar15 = 0;
            do {
              uVar1 = *(uint *)(lVar18 + lVar15 * 4);
              if (uVar1 < *(uint *)(param_1 + 1)) {
                uVar7 = (ulong)uVar1;
                iVar2 = *(int *)(param_3 + uVar7 * 4);
                if (iVar2 == 1) {
                  *(undefined1 *)(param_4 + (ulong)uVar1) = 1;
                }
                else if (iVar2 == 0) {
                  *(undefined4 *)(param_3 + uVar7 * 4) = 1;
                  lVar16 = lVar5 + (ulong)uVar1 * 0x50;
                  uVar3 = *(uint *)(lVar16 + 0x30);
                  if (uVar3 != 0) {
                    lVar10 = *(long *)(lVar16 + 0x28);
                    lVar4 = 0;
                    do {
                      uVar1 = *(uint *)(lVar10 + lVar4 * 4);
                      if (uVar1 < *(uint *)(param_1 + 1)) {
                        uVar9 = (ulong)uVar1;
                        iVar2 = *(int *)(param_3 + uVar9 * 4);
                        if (iVar2 == 1) {
                          *(undefined1 *)(param_4 + (ulong)uVar1) = 1;
                        }
                        else if (iVar2 == 0) {
                          *(undefined4 *)(param_3 + uVar9 * 4) = 1;
                          lVar6 = lVar5 + (ulong)uVar1 * 0x50;
                          uVar3 = *(uint *)(lVar6 + 0x30);
                          if (uVar3 != 0) {
                            lVar11 = *(long *)(lVar6 + 0x28);
                            lVar8 = 0;
                            do {
                              uVar1 = *(uint *)(lVar11 + lVar8 * 4);
                              if (uVar1 < *(uint *)(param_1 + 1)) {
                                iVar2 = *(int *)(param_3 + (ulong)uVar1 * 4);
                                if (iVar2 == 1) {
                                  *(undefined1 *)(param_4 + (ulong)uVar1) = 1;
                                }
                                else if (iVar2 == 0) {
                                  dfs_mark(param_1,(ulong)uVar1,param_3);
                                  uVar3 = *(uint *)(lVar6 + 0x30);
                                }
                              }
                              lVar8 = lVar8 + 1;
                            } while ((uint)lVar8 < uVar3);
                          }
                          *(undefined4 *)(param_3 + uVar9 * 4) = 2;
                          uVar3 = *(uint *)(lVar16 + 0x30);
                        }
                      }
                      lVar4 = lVar4 + 1;
                    } while ((uint)lVar4 < uVar3);
                  }
                  *(undefined4 *)(param_3 + uVar7 * 4) = 2;
                  uVar3 = *(uint *)(lVar13 + 0x30);
                }
              }
              lVar15 = lVar15 + 1;
            } while ((uint)lVar15 < uVar3);
          }
          *(undefined4 *)(param_3 + uVar17 * 4) = 2;
          uVar3 = *(uint *)(lVar14 + 0x30);
        }
      }
      lVar12 = lVar12 + 1;
    } while ((uint)lVar12 < uVar3);
  }
  *(undefined4 *)(param_3 + (param_2 & 0xffffffff) * 4) = 2;
  return;
}

