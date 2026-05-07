
int simplify_identities(long *param_1)

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
      puVar15 = puVar12 + (ulong)*(uint *)(puVar16 + 1) * 0x22;
      do {
        if (puVar12[0x12] != 2) goto LAB_00179988;
        uVar3 = puVar12[6];
        uVar4 = puVar12[10];
        if (uVar3 == 0xffffffff) {
          uVar14 = *puVar12;
          if (uVar4 != 0xffffffff) {
            uVar13 = *(uint *)(param_1 + 1);
            if (uVar13 == 0) goto LAB_00179bd4;
            lVar17 = 0;
            bVar6 = false;
            goto LAB_0017990c;
          }
LAB_00179bc8:
          lVar17 = 0;
          bVar5 = false;
LAB_00179a50:
          if (uVar14 == 6) {
LAB_00179a08:
            if (lVar17 == 0 && bVar5) {
LAB_00179b7c:
              iVar7 = iVar7 + 1;
              *puVar12 = 1;
              puVar12[4] = 0;
              puVar12[5] = 0;
              puVar12[0x12] = 0;
              goto LAB_00179988;
            }
            goto LAB_00179a14;
          }
          if (uVar14 < 7) {
            if (uVar14 != 3) {
              if (uVar14 != 4) {
                if (uVar14 != 2) goto LAB_00179988;
                goto LAB_00179978;
              }
              goto LAB_00179b94;
            }
LAB_00179b10:
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
LAB_00179a88:
                if (lVar17 != 0 || !bVar5) goto LAB_00179a14;
                iVar7 = iVar7 + 1;
                *puVar12 = 0;
                puVar12[6] = uVar4;
                puVar12[0x12] = 1;
              }
              goto LAB_00179988;
            }
LAB_00179bf8:
            if (uVar3 == uVar4) {
              iVar7 = iVar7 + 1;
              *puVar12 = 1;
              puVar12[4] = 0;
              puVar12[5] = 0;
              puVar12[0x12] = 0;
              goto LAB_00179988;
            }
LAB_00179978:
            if (lVar17 != 0 || !bVar5) goto LAB_00179988;
LAB_001799ec:
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
            if (uVar4 == 0xffffffff) goto LAB_00179bc8;
LAB_00179bd4:
            if (uVar14 != 6) {
              if (uVar14 < 7) goto LAB_00179b08;
              if (uVar14 == 8) {
                lVar17 = 0;
                bVar5 = false;
                goto LAB_00179bf8;
              }
              if (8 < uVar14) goto LAB_00179988;
            }
LAB_00179a14:
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
                piVar10 = piVar8 + (ulong)*(uint *)(puVar11 + 1) * 0x22;
                do {
                  if ((*piVar8 == 1) && (uVar3 == piVar8[2])) {
                    lVar17 = *(long *)(piVar8 + 4);
                    uVar14 = *puVar12;
                    bVar5 = true;
                    bVar6 = true;
                    if (uVar4 != 0xffffffff) goto LAB_0017990c;
                    goto LAB_00179a50;
                  }
                  piVar8 = piVar8 + 0x22;
                } while (piVar10 != piVar8);
              }
              puVar11 = puVar11 + 10;
            } while (puVar1 + (ulong)uVar13 * 10 != puVar11);
            uVar14 = *puVar12;
            lVar17 = 0;
            bVar5 = false;
            bVar6 = bVar5;
            if (uVar4 == 0xffffffff) goto LAB_00179a50;
LAB_0017990c:
            bVar5 = bVar6;
            puVar11 = puVar1;
            do {
              if (*(uint *)(puVar11 + 1) != 0) {
                piVar8 = (int *)*puVar11;
                piVar10 = piVar8 + (ulong)*(uint *)(puVar11 + 1) * 0x22;
                do {
                  if ((*piVar8 == 1) && (uVar4 == piVar8[2])) {
                    lVar9 = *(long *)(piVar8 + 4);
                    if (uVar14 == 6) {
                      if (lVar9 != 0) goto LAB_00179a08;
                      iVar7 = iVar7 + 1;
                      *puVar12 = 1;
                      puVar12[4] = 0;
                      puVar12[5] = 0;
                      puVar12[0x12] = 0;
                      goto LAB_00179988;
                    }
                    if (uVar14 < 7) {
                      if (uVar14 == 3) {
                        if (lVar9 != 0) goto LAB_00179b10;
                      }
                      else {
                        if (uVar14 == 4) {
                          if (lVar9 == 1) {
                            iVar7 = iVar7 + 1;
                            *puVar12 = 0;
                            puVar12[0x12] = 1;
                            goto LAB_00179988;
                          }
                          if (!bVar5) {
                            if (lVar9 == 0) goto LAB_00179b7c;
                            goto LAB_00179988;
                          }
                          if (lVar17 == 1) goto LAB_001799ec;
                          if (lVar9 != 0) goto LAB_00179ba0;
                          iVar7 = iVar7 + 1;
                          *puVar12 = 1;
                          puVar12[4] = 0;
                          puVar12[5] = 0;
                          puVar12[0x12] = 0;
                          goto LAB_00179988;
                        }
                        if (uVar14 != 2) goto LAB_00179988;
LAB_00179974:
                        if (lVar9 != 0) goto LAB_00179978;
                      }
                    }
                    else {
                      if (uVar14 == 8) {
                        if (uVar3 != uVar4) goto LAB_00179974;
                        iVar7 = iVar7 + 1;
                        *puVar12 = 1;
                        puVar12[4] = 0;
                        puVar12[5] = 0;
                        puVar12[0x12] = 0;
                        goto LAB_00179988;
                      }
                      if (8 < uVar14) {
                        if ((uVar14 - 9 < 2) && (lVar9 == 0)) {
                          iVar7 = iVar7 + 1;
                          *puVar12 = 0;
                          puVar12[0x12] = 1;
                        }
                        goto LAB_00179988;
                      }
                      if (lVar9 != 0) goto LAB_00179a88;
                    }
                    iVar7 = iVar7 + 1;
                    *puVar12 = 0;
                    puVar12[0x12] = 1;
                    goto LAB_00179988;
                  }
                  piVar8 = piVar8 + 0x22;
                } while (piVar8 != piVar10);
              }
              puVar11 = puVar11 + 10;
            } while (puVar11 != puVar1 + (ulong)uVar13 * 10);
            if (uVar14 == 4) {
LAB_00179b94:
              if (bVar5) {
                if (lVar17 == 1) goto LAB_001799ec;
LAB_00179ba0:
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
              if (uVar14 == 2) goto LAB_00179978;
LAB_00179b08:
              if (uVar14 == 3) goto LAB_00179b10;
            }
            else {
              if (uVar14 == 8) goto LAB_00179bf8;
              if (uVar14 < 9) {
                if (uVar14 == 6) goto LAB_00179a08;
                if (uVar14 == 7) {
                  if (lVar17 != 0 || !bVar5) goto LAB_00179a14;
                  goto LAB_001799ec;
                }
              }
            }
          }
        }
LAB_00179988:
        puVar12 = puVar12 + 0x22;
      } while (puVar12 != puVar15);
    }
    puVar16 = puVar16 + 10;
    if (puVar16 == puVar1 + (ulong)uVar2 * 10) {
      return iVar7;
    }
  } while( true );
}

