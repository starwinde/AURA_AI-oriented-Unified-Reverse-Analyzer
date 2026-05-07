
int FUN_0017a040(long *param_1)

{
  undefined8 *puVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  bool bVar5;
  bool bVar6;
  int iVar7;
  int *piVar8;
  long lVar9;
  int *piVar10;
  undefined8 *puVar11;
  uint *puVar12;
  uint uVar13;
  uint uVar14;
  uint *puVar15;
  undefined8 *puVar16;
  long lVar17;
  
  uVar2 = *(uint *)(param_1 + 1);
  if (uVar2 == 0) {
    return 0;
  }
  iVar7 = 0;
  puVar1 = (undefined8 *)(*param_1 + 8);
  puVar16 = puVar1;
  do {
    if (*(uint *)(puVar16 + 1) != 0) {
      puVar12 = (uint *)*puVar16;
      puVar15 = puVar12 + (ulong)*(uint *)(puVar16 + 1) * 0x24;
      do {
        if (puVar12[0x12] != 2) goto LAB_0017a178;
        uVar3 = puVar12[6];
        uVar4 = puVar12[10];
        if (uVar3 == 0xffffffff) {
          uVar14 = *puVar12;
          if (uVar4 != 0xffffffff) {
            uVar13 = *(uint *)(param_1 + 1);
            if (uVar13 == 0) goto LAB_0017a3c4;
            lVar17 = 0;
            bVar6 = false;
            goto LAB_0017a0fc;
          }
LAB_0017a3b8:
          lVar17 = 0;
          bVar5 = false;
LAB_0017a240:
          if (uVar14 == 6) {
LAB_0017a1f8:
            if (lVar17 == 0 && bVar5) {
LAB_0017a36c:
              iVar7 = iVar7 + 1;
              *puVar12 = 1;
              puVar12[4] = 0;
              puVar12[5] = 0;
              puVar12[0x12] = 0;
              goto LAB_0017a178;
            }
            goto LAB_0017a204;
          }
          if (uVar14 < 7) {
            if (uVar14 != 3) {
              if (uVar14 != 4) {
                if (uVar14 != 2) goto LAB_0017a178;
                goto LAB_0017a168;
              }
              goto LAB_0017a384;
            }
LAB_0017a300:
            if (uVar3 == uVar4) {
              iVar7 = iVar7 + 1;
              *puVar12 = 1;
              puVar12[4] = 0;
              puVar12[5] = 0;
              puVar12[0x12] = 0;
            }
          }
          else {
            if (uVar14 != 8) {
              if (uVar14 < 9) {
LAB_0017a278:
                if (lVar17 != 0 || !bVar5) goto LAB_0017a204;
                iVar7 = iVar7 + 1;
                *puVar12 = 0;
                puVar12[6] = uVar4;
                puVar12[0x12] = 1;
              }
              goto LAB_0017a178;
            }
LAB_0017a3e8:
            if (uVar3 == uVar4) {
              iVar7 = iVar7 + 1;
              *puVar12 = 1;
              puVar12[4] = 0;
              puVar12[5] = 0;
              puVar12[0x12] = 0;
              goto LAB_0017a178;
            }
LAB_0017a168:
            if (lVar17 != 0 || !bVar5) goto LAB_0017a178;
LAB_0017a1dc:
            iVar7 = iVar7 + 1;
            *puVar12 = 0;
            puVar12[6] = uVar4;
            puVar12[0x12] = 1;
          }
        }
        else {
          uVar13 = *(uint *)(param_1 + 1);
          if (uVar13 == 0) {
            uVar14 = *puVar12;
            if (uVar4 == 0xffffffff) goto LAB_0017a3b8;
LAB_0017a3c4:
            if (uVar14 != 6) {
              if (uVar14 < 7) goto LAB_0017a2f8;
              if (uVar14 == 8) {
                lVar17 = 0;
                bVar5 = false;
                goto LAB_0017a3e8;
              }
              if (8 < uVar14) goto LAB_0017a178;
            }
LAB_0017a204:
            if (uVar3 == uVar4) {
              iVar7 = iVar7 + 1;
              *puVar12 = 0;
              puVar12[0x12] = 1;
            }
          }
          else {
            puVar11 = puVar1;
            do {
              if (*(uint *)(puVar11 + 1) != 0) {
                piVar8 = (int *)*puVar11;
                piVar10 = piVar8 + (ulong)*(uint *)(puVar11 + 1) * 0x24;
                do {
                  if ((*piVar8 == 1) && (uVar3 == piVar8[2])) {
                    lVar17 = *(long *)(piVar8 + 4);
                    uVar14 = *puVar12;
                    bVar5 = true;
                    bVar6 = true;
                    if (uVar4 != 0xffffffff) goto LAB_0017a0fc;
                    goto LAB_0017a240;
                  }
                  piVar8 = piVar8 + 0x24;
                } while (piVar10 != piVar8);
              }
              puVar11 = puVar11 + 10;
            } while (puVar1 + (ulong)uVar13 * 10 != puVar11);
            uVar14 = *puVar12;
            lVar17 = 0;
            bVar5 = false;
            bVar6 = bVar5;
            if (uVar4 == 0xffffffff) goto LAB_0017a240;
LAB_0017a0fc:
            bVar5 = bVar6;
            puVar11 = puVar1;
            do {
              if (*(uint *)(puVar11 + 1) != 0) {
                piVar8 = (int *)*puVar11;
                piVar10 = piVar8 + (ulong)*(uint *)(puVar11 + 1) * 0x24;
                do {
                  if ((*piVar8 == 1) && (uVar4 == piVar8[2])) {
                    lVar9 = *(long *)(piVar8 + 4);
                    if (uVar14 == 6) {
                      if (lVar9 != 0) goto LAB_0017a1f8;
                      iVar7 = iVar7 + 1;
                      *puVar12 = 1;
                      puVar12[4] = 0;
                      puVar12[5] = 0;
                      puVar12[0x12] = 0;
                      goto LAB_0017a178;
                    }
                    if (uVar14 < 7) {
                      if (uVar14 == 3) {
                        if (lVar9 != 0) goto LAB_0017a300;
                      }
                      else {
                        if (uVar14 == 4) {
                          if (lVar9 == 1) {
                            iVar7 = iVar7 + 1;
                            *puVar12 = 0;
                            puVar12[0x12] = 1;
                            goto LAB_0017a178;
                          }
                          if (!bVar5) {
                            if (lVar9 == 0) goto LAB_0017a36c;
                            goto LAB_0017a178;
                          }
                          if (lVar17 == 1) goto LAB_0017a1dc;
                          if (lVar9 != 0) goto LAB_0017a390;
                          iVar7 = iVar7 + 1;
                          *puVar12 = 1;
                          puVar12[4] = 0;
                          puVar12[5] = 0;
                          puVar12[0x12] = 0;
                          goto LAB_0017a178;
                        }
                        if (uVar14 != 2) goto LAB_0017a178;
LAB_0017a164:
                        if (lVar9 != 0) goto LAB_0017a168;
                      }
                    }
                    else {
                      if (uVar14 == 8) {
                        if (uVar3 != uVar4) goto LAB_0017a164;
                        iVar7 = iVar7 + 1;
                        *puVar12 = 1;
                        puVar12[4] = 0;
                        puVar12[5] = 0;
                        puVar12[0x12] = 0;
                        goto LAB_0017a178;
                      }
                      if (8 < uVar14) {
                        if ((uVar14 - 9 < 2) && (lVar9 == 0)) {
                          iVar7 = iVar7 + 1;
                          *puVar12 = 0;
                          puVar12[0x12] = 1;
                        }
                        goto LAB_0017a178;
                      }
                      if (lVar9 != 0) goto LAB_0017a278;
                    }
                    iVar7 = iVar7 + 1;
                    *puVar12 = 0;
                    puVar12[0x12] = 1;
                    goto LAB_0017a178;
                  }
                  piVar8 = piVar8 + 0x24;
                } while (piVar8 != piVar10);
              }
              puVar11 = puVar11 + 10;
            } while (puVar11 != puVar1 + (ulong)uVar13 * 10);
            if (uVar14 == 4) {
LAB_0017a384:
              if (bVar5) {
                if (lVar17 == 1) goto LAB_0017a1dc;
LAB_0017a390:
                if (lVar17 == 0) {
                  iVar7 = iVar7 + 1;
                  *puVar12 = 1;
                  puVar12[4] = 0;
                  puVar12[5] = 0;
                  puVar12[0x12] = 0;
                }
              }
            }
            else if (uVar14 < 5) {
              if (uVar14 == 2) goto LAB_0017a168;
LAB_0017a2f8:
              if (uVar14 == 3) goto LAB_0017a300;
            }
            else {
              if (uVar14 == 8) goto LAB_0017a3e8;
              if (uVar14 < 9) {
                if (uVar14 == 6) goto LAB_0017a1f8;
                if (uVar14 == 7) {
                  if (lVar17 != 0 || !bVar5) goto LAB_0017a204;
                  goto LAB_0017a1dc;
                }
              }
            }
          }
        }
LAB_0017a178:
        puVar12 = puVar12 + 0x24;
      } while (puVar12 != puVar15);
    }
    puVar16 = puVar16 + 10;
    if (puVar16 == puVar1 + (ulong)uVar2 * 10) {
      return iVar7;
    }
  } while( true );
}

