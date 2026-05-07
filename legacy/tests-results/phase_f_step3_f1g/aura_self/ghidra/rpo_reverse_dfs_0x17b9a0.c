
void rpo_reverse_dfs(long *param_1,uint param_2,long param_3,long param_4,uint *param_5)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  byte bVar7;
  uint uVar8;
  long lVar9;
  long lVar10;
  long lVar11;
  uint *puVar12;
  long lVar13;
  uint *puVar14;
  uint *puVar15;
  long lVar16;
  long lVar17;
  long lVar18;
  long lVar19;
  long lVar20;
  long lVar21;
  uint *puVar22;
  long lVar23;
  long lVar24;
  
  lVar18 = *param_1;
  lVar23 = lVar18 + (ulong)param_2 * 0x50;
  *(undefined1 *)(param_3 + (ulong)param_2) = 1;
  uVar8 = *(uint *)(lVar23 + 0x20);
  if (uVar8 != 0) {
    lVar16 = 0;
    lVar24 = *(long *)(lVar23 + 0x18);
    do {
      uVar2 = *(uint *)(lVar24 + lVar16 * 4);
      uVar1 = *(uint *)(param_1 + 1);
      if ((uVar2 < uVar1) && ((*(byte *)(param_3 + (ulong)uVar2) & 1) == 0)) {
        *(undefined1 *)(param_3 + (ulong)uVar2) = 1;
        lVar11 = lVar18 + (ulong)uVar2 * 0x50;
        uVar8 = *(uint *)(lVar11 + 0x20);
        if (uVar8 != 0) {
          puVar12 = *(uint **)(lVar11 + 0x18);
          lVar21 = 0;
          uVar3 = *puVar12;
          if (uVar3 < uVar1) {
            bVar7 = *(byte *)(param_3 + (ulong)uVar3);
            goto joined_r0x0017ba6c;
          }
          while (lVar21 = lVar21 + 1, (uint)lVar21 < uVar8) {
            uVar1 = *(uint *)(param_1 + 1);
            uVar3 = puVar12[lVar21];
            if (uVar3 < uVar1) {
              bVar7 = *(byte *)(param_3 + (ulong)uVar3);
joined_r0x0017ba6c:
              if ((bVar7 & 1) == 0) {
                *(undefined1 *)(param_3 + (ulong)uVar3) = 1;
                lVar13 = lVar18 + (ulong)uVar3 * 0x50;
                uVar8 = *(uint *)(lVar13 + 0x20);
                if (uVar8 != 0) {
                  puVar14 = *(uint **)(lVar13 + 0x18);
                  lVar10 = 0;
                  uVar4 = *puVar14;
                  if (uVar4 < uVar1) {
                    bVar7 = *(byte *)(param_3 + (ulong)uVar4);
                    goto joined_r0x0017bae0;
                  }
                  while (lVar10 = lVar10 + 1, (uint)lVar10 < uVar8) {
                    uVar1 = *(uint *)(param_1 + 1);
                    uVar4 = puVar14[lVar10];
                    if (uVar4 < uVar1) {
                      bVar7 = *(byte *)(param_3 + (ulong)uVar4);
joined_r0x0017bae0:
                      if ((bVar7 & 1) == 0) {
                        *(undefined1 *)(param_3 + (ulong)uVar4) = 1;
                        lVar19 = lVar18 + (ulong)uVar4 * 0x50;
                        uVar8 = *(uint *)(lVar19 + 0x20);
                        if (uVar8 != 0) {
                          puVar22 = *(uint **)(lVar19 + 0x18);
                          lVar17 = 0;
                          uVar5 = *puVar22;
                          if (uVar5 < uVar1) {
                            bVar7 = *(byte *)(param_3 + (ulong)uVar5);
                            goto joined_r0x0017bb54;
                          }
                          while (lVar17 = lVar17 + 1, (uint)lVar17 < uVar8) {
                            uVar1 = *(uint *)(param_1 + 1);
                            uVar5 = puVar22[lVar17];
                            if (uVar5 < uVar1) {
                              bVar7 = *(byte *)(param_3 + (ulong)uVar5);
joined_r0x0017bb54:
                              if ((bVar7 & 1) == 0) {
                                *(undefined1 *)(param_3 + (ulong)uVar5) = 1;
                                lVar9 = lVar18 + (ulong)uVar5 * 0x50;
                                uVar8 = *(uint *)(lVar9 + 0x20);
                                if (uVar8 != 0) {
                                  puVar15 = *(uint **)(lVar9 + 0x18);
                                  lVar20 = 0;
                                  uVar6 = *puVar15;
                                  if (uVar1 <= uVar6) goto LAB_0017bbdc;
                                  do {
                                    if ((*(byte *)(param_3 + (ulong)uVar6) & 1) == 0) {
                                      rpo_reverse_dfs(param_1,(ulong)uVar6,param_3,param_4);
                                      uVar8 = *(uint *)(lVar9 + 0x20);
                                    }
LAB_0017bbdc:
                                    do {
                                      lVar20 = lVar20 + 1;
                                      if (uVar8 <= (uint)lVar20) goto LAB_0017bc8c;
                                      uVar6 = puVar15[lVar20];
                                    } while (*(uint *)(param_1 + 1) <= uVar6);
                                  } while( true );
                                }
LAB_0017bc8c:
                                uVar8 = *param_5;
                                *param_5 = uVar8 + 1;
                                *(uint *)(param_4 + (ulong)uVar8 * 4) = uVar5;
                                uVar8 = *(uint *)(lVar19 + 0x20);
                              }
                            }
                          }
                        }
                        uVar8 = *param_5;
                        *param_5 = uVar8 + 1;
                        *(uint *)(param_4 + (ulong)uVar8 * 4) = uVar4;
                        uVar8 = *(uint *)(lVar13 + 0x20);
                      }
                    }
                  }
                }
                uVar8 = *param_5;
                *param_5 = uVar8 + 1;
                *(uint *)(param_4 + (ulong)uVar8 * 4) = uVar3;
                uVar8 = *(uint *)(lVar11 + 0x20);
              }
            }
          }
        }
        uVar8 = *param_5;
        *param_5 = uVar8 + 1;
        *(uint *)(param_4 + (ulong)uVar8 * 4) = uVar2;
        uVar8 = *(uint *)(lVar23 + 0x20);
      }
      lVar16 = lVar16 + 1;
    } while ((uint)lVar16 < uVar8);
  }
  uVar8 = *param_5;
  *param_5 = uVar8 + 1;
  *(uint *)(param_4 + (ulong)uVar8 * 4) = param_2;
  return;
}

