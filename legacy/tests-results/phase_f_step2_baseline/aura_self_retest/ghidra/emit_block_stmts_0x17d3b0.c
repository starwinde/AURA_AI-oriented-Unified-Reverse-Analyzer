
void emit_block_stmts(long *param_1,uint param_2,int *param_3)

{
  long lVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined8 uVar7;
  void *pvVar8;
  undefined4 *puVar9;
  uint uVar10;
  long lVar11;
  long lVar12;
  uint uVar13;
  
  if (param_2 < *(uint *)((long *)*param_1 + 1)) {
    lVar12 = *(long *)*param_1 + (ulong)param_2 * 0x48;
    uVar13 = *(uint *)(lVar12 + 0x10);
    if (uVar13 != 0) {
      if (param_3 == (int *)0x0) {
        lVar11 = 0;
        uVar10 = 0;
        do {
          lVar1 = *(long *)(lVar12 + 8) + lVar11;
          iVar4 = *(int *)(*(long *)(lVar12 + 8) + lVar11);
          if (1 < iVar4 - 0x17U && (iVar4 != 0x1a && iVar4 != 0x1b)) {
            uVar3 = *(uint *)(lVar1 + 8);
            if ((uVar3 == 0xffffffff) ||
               ((uVar3 < *(uint *)(*param_1 + 0x10) &&
                (*(int *)(param_1[5] + (ulong)uVar3 * 4) == 1)))) {
              if (iVar4 == 0x16) goto LAB_0017d8d4;
              if (iVar4 == 0x19) goto LAB_0017d7ac;
            }
            else if (iVar4 == 0x16) {
LAB_0017d8d4:
              if ((1 < *(uint *)(lVar1 + 0x48)) &&
                 (puVar6 = calloc(1,0x130), puVar6 != (undefined4 *)0x0)) {
                *puVar6 = 10;
                puVar5 = calloc(1,0x130);
                if (puVar5 != (undefined4 *)0x0) {
                  uVar2 = *(undefined4 *)(lVar1 + 0x18);
                  *puVar5 = 0x10;
                  puVar5[0x28] = 3;
                  uVar7 = build_expr(param_1,uVar2);
                  *(undefined8 *)(puVar5 + 0x26) = uVar7;
                }
                uVar2 = *(undefined4 *)(lVar1 + 0x28);
                *(undefined4 **)(puVar6 + 0x26) = puVar5;
                uVar7 = build_expr(param_1,uVar2);
                uVar13 = *(uint *)(lVar12 + 0x10);
                *(undefined8 *)(puVar6 + 0x24) = *(undefined8 *)(lVar1 + 0x70);
                *(undefined8 *)(puVar6 + 0x28) = uVar7;
              }
            }
            else if (iVar4 == 0x19) {
LAB_0017d7ac:
              puVar6 = (undefined4 *)build_expr_from_instr(param_1,lVar1);
              uVar13 = *(uint *)(lVar1 + 8);
              if (((uVar13 == 0xffffffff) || (*(uint *)(*param_1 + 0x10) <= uVar13)) ||
                 (*(int *)(param_1[5] + (ulong)uVar13 * 4) == 0)) {
                uVar13 = *(uint *)(lVar12 + 0x10);
                if (puVar6 != (undefined4 *)0x0) {
                  *puVar6 = 0xc;
                }
              }
              else {
                puVar5 = calloc(1,0x130);
                if (puVar5 == (undefined4 *)0x0) {
                  uVar13 = *(uint *)(lVar12 + 0x10);
                }
                else {
                  *puVar5 = 10;
                  puVar9 = calloc(1,0x130);
                  if (puVar9 != (undefined4 *)0x0) {
                    *puVar9 = 0xd;
                    puVar9[0x26] = uVar13;
                    __snprintf_chk(puVar9 + 0x27,0x40,2,0x40,&DAT_001f8930,uVar13);
                  }
                  uVar13 = *(uint *)(lVar12 + 0x10);
                  *(undefined8 *)(puVar5 + 0x24) = *(undefined8 *)(lVar1 + 0x70);
                  *(undefined4 **)(puVar5 + 0x26) = puVar9;
                  *(undefined4 **)(puVar5 + 0x28) = puVar6;
                }
              }
            }
            else {
              puVar6 = calloc(1,0x130);
              if (puVar6 != (undefined4 *)0x0) {
                *puVar6 = 10;
                puVar5 = calloc(1,0x130);
                if (puVar5 != (undefined4 *)0x0) {
                  *puVar5 = 0xd;
                  puVar5[0x26] = uVar3;
                  __snprintf_chk(puVar5 + 0x27,0x40,2,0x40,&DAT_001f8930,uVar3);
                }
                *(undefined4 **)(puVar6 + 0x26) = puVar5;
                uVar7 = build_expr_from_instr(param_1,lVar1);
                uVar13 = *(uint *)(lVar12 + 0x10);
                *(undefined8 *)(puVar6 + 0x24) = *(undefined8 *)(lVar1 + 0x70);
                *(undefined8 *)(puVar6 + 0x28) = uVar7;
              }
            }
          }
          uVar10 = uVar10 + 1;
          lVar11 = lVar11 + 0x88;
        } while (uVar10 < uVar13);
      }
      else {
        lVar11 = 0;
        do {
          lVar1 = *(long *)(lVar12 + 8) + lVar11 * 0x88;
          iVar4 = *(int *)(*(long *)(lVar12 + 8) + lVar11 * 0x88);
          if (1 < iVar4 - 0x1aU && (iVar4 != 0x17 && iVar4 != 0x18)) {
            uVar10 = *(uint *)(lVar1 + 8);
            if ((uVar10 == 0xffffffff) ||
               ((uVar10 < *(uint *)(*param_1 + 0x10) &&
                (*(int *)(param_1[5] + (ulong)uVar10 * 4) == 1)))) {
              if (iVar4 == 0x16) goto LAB_0017d600;
              if (iVar4 == 0x19) goto LAB_0017d548;
            }
            else if (iVar4 == 0x16) {
LAB_0017d600:
              if ((1 < *(uint *)(lVar1 + 0x48)) &&
                 (puVar6 = calloc(1,0x130), puVar6 != (undefined4 *)0x0)) {
                *puVar6 = 10;
                puVar5 = calloc(1,0x130);
                if (puVar5 != (undefined4 *)0x0) {
                  uVar2 = *(undefined4 *)(lVar1 + 0x18);
                  *puVar5 = 0x10;
                  puVar5[0x28] = 3;
                  uVar7 = build_expr(param_1,uVar2);
                  *(undefined8 *)(puVar5 + 0x26) = uVar7;
                }
                uVar2 = *(undefined4 *)(lVar1 + 0x28);
                *(undefined4 **)(puVar6 + 0x26) = puVar5;
                uVar7 = build_expr(param_1,uVar2);
                iVar4 = *param_3;
                *(undefined8 *)(puVar6 + 0x24) = *(undefined8 *)(lVar1 + 0x70);
                *(undefined8 *)(puVar6 + 0x28) = uVar7;
                if (iVar4 != 0) goto LAB_0017d5f8;
                uVar10 = param_3[0x28];
                uVar13 = param_3[0x29];
                pvVar8 = *(void **)(param_3 + 0x26);
                if (uVar13 <= uVar10) {
LAB_0017d8a0:
                  pvVar8 = realloc(pvVar8,((ulong)uVar13 & 0x7fffffff) << 4);
                  if (pvVar8 == (void *)0x0) goto LAB_0017d5f8;
                  uVar10 = param_3[0x28];
                  *(void **)(param_3 + 0x26) = pvVar8;
                  param_3[0x29] = uVar13 << 1;
                }
LAB_0017d690:
                uVar13 = *(uint *)(lVar12 + 0x10);
                param_3[0x28] = uVar10 + 1;
                *(undefined4 **)((long)pvVar8 + (ulong)uVar10 * 8) = puVar6;
              }
            }
            else {
              if (iVar4 == 0x19) {
LAB_0017d548:
                puVar6 = (undefined4 *)build_expr_from_instr(param_1,lVar1);
                uVar13 = *(uint *)(lVar1 + 8);
                if (((uVar13 == 0xffffffff) || (*(uint *)(*param_1 + 0x10) <= uVar13)) ||
                   (*(int *)(param_1[5] + (ulong)uVar13 * 4) == 0)) {
                  if ((puVar6 != (undefined4 *)0x0) && (*puVar6 = 0xc, *param_3 == 0)) {
                    uVar10 = param_3[0x28];
                    uVar13 = param_3[0x29];
                    pvVar8 = *(void **)(param_3 + 0x26);
                    if (uVar13 <= uVar10) goto LAB_0017d8a0;
                    goto LAB_0017d690;
                  }
                }
                else {
                  puVar5 = calloc(1,0x130);
                  if (puVar5 != (undefined4 *)0x0) {
                    *puVar5 = 10;
                    puVar9 = calloc(1,0x130);
                    if (puVar9 != (undefined4 *)0x0) {
                      *puVar9 = 0xd;
                      puVar9[0x26] = uVar13;
                      __snprintf_chk(puVar9 + 0x27,0x40,2,0x40,&DAT_001f8930,uVar13);
                    }
                    iVar4 = *param_3;
                    *(undefined8 *)(puVar5 + 0x24) = *(undefined8 *)(lVar1 + 0x70);
                    *(undefined4 **)(puVar5 + 0x26) = puVar9;
                    *(undefined4 **)(puVar5 + 0x28) = puVar6;
                    goto joined_r0x0017d5f4;
                  }
                }
              }
              else {
                puVar5 = calloc(1,0x130);
                if (puVar5 == (undefined4 *)0x0) goto LAB_0017d510;
                *puVar5 = 10;
                puVar6 = calloc(1,0x130);
                if (puVar6 != (undefined4 *)0x0) {
                  *puVar6 = 0xd;
                  puVar6[0x26] = uVar10;
                  __snprintf_chk(puVar6 + 0x27,0x40,2,0x40,&DAT_001f8930,uVar10);
                }
                *(undefined4 **)(puVar5 + 0x26) = puVar6;
                uVar7 = build_expr_from_instr(param_1,lVar1);
                iVar4 = *param_3;
                *(undefined8 *)(puVar5 + 0x24) = *(undefined8 *)(lVar1 + 0x70);
                *(undefined8 *)(puVar5 + 0x28) = uVar7;
joined_r0x0017d5f4:
                if (iVar4 == 0) {
                  uVar10 = param_3[0x28];
                  uVar13 = param_3[0x29];
                  pvVar8 = *(void **)(param_3 + 0x26);
                  if (uVar13 <= uVar10) {
                    pvVar8 = realloc(pvVar8,((ulong)uVar13 & 0x7fffffff) << 4);
                    if (pvVar8 == (void *)0x0) goto LAB_0017d5f8;
                    uVar10 = param_3[0x28];
                    *(void **)(param_3 + 0x26) = pvVar8;
                    param_3[0x29] = uVar13 << 1;
                  }
                  uVar13 = *(uint *)(lVar12 + 0x10);
                  param_3[0x28] = uVar10 + 1;
                  *(undefined4 **)((long)pvVar8 + (ulong)uVar10 * 8) = puVar5;
                  goto LAB_0017d510;
                }
              }
LAB_0017d5f8:
              uVar13 = *(uint *)(lVar12 + 0x10);
            }
          }
LAB_0017d510:
          lVar11 = lVar11 + 1;
        } while ((uint)lVar11 < uVar13);
      }
    }
  }
  return;
}

