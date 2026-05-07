
void emit_region(long *param_1,uint param_2,uint param_3,int *param_4)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined1 uVar6;
  long *plVar7;
  int *piVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  void *pvVar11;
  void *pvVar12;
  undefined8 uVar13;
  undefined4 *puVar14;
  undefined4 *puVar15;
  uint uVar16;
  long lVar17;
  void *pvVar18;
  long lVar19;
  long lVar20;
  long lVar21;
  uint uVar22;
  ulong uVar23;
  long lVar24;
  ulong uVar25;
  uint uVar26;
  size_t sVar27;
  long *local_190;
  
  plVar7 = (long *)*param_1;
  lVar20 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (param_2 < *(uint *)(plVar7 + 1) && param_3 != param_2) {
    lVar17 = param_1[6];
    uVar25 = (ulong)param_2;
LAB_0017e9b4:
    do {
      if ((*(byte *)(lVar17 + uVar25) & 1) != 0) break;
      lVar21 = *plVar7;
      *(undefined1 *)(lVar17 + uVar25) = 1;
      lVar21 = lVar21 + uVar25 * 0x50;
      uVar16 = *(uint *)(lVar21 + 0x10) - 1;
      if (-1 < (int)uVar16) {
        piVar8 = (int *)(*(long *)(lVar21 + 8) + (long)(int)uVar16 * 0x88);
        do {
          if (*piVar8 - 0x17U < 2 || *piVar8 == 0x1a) goto LAB_0017ea20;
          piVar8 = piVar8 + -0x22;
        } while (piVar8 != (int *)(*(long *)(lVar21 + 8) + -0x110 +
                                  ((ulong)*(uint *)(lVar21 + 0x10) - (ulong)uVar16) * 0x88));
      }
      piVar8 = (int *)0x0;
LAB_0017ea20:
      plVar7 = (long *)param_1[2];
      if ((((plVar7 != (long *)0x0) &&
           (uVar16 = *(uint *)(plVar7[2] + uVar25 * 4), uVar16 != 0xffffffff)) &&
          (uVar16 < *(uint *)(plVar7 + 1))) &&
         (lVar17 = *plVar7 + (ulong)uVar16 * 0x60,
         *(int *)(*plVar7 + (ulong)uVar16 * 0x60) == (int)uVar25)) {
        if (piVar8 == (int *)0x0) {
          emit_block_stmts(param_1,uVar25,param_4);
          if ((2 < *(uint *)(lVar21 + 0x30)) &&
             (puVar9 = calloc(1,0x130), puVar9 != (undefined4 *)0x0)) {
            *puVar9 = 5;
LAB_0017ed78:
            puVar10 = calloc(1,0x130);
            if (puVar10 != (undefined4 *)0x0) {
              *puVar10 = 0xe;
              *(undefined8 *)(puVar10 + 0x26) = 0;
              *(undefined8 *)(puVar10 + 3) = 0;
              *(undefined8 *)(puVar10 + 1) = 0x745f3233746e69;
              *(undefined8 *)(puVar10 + 7) = 0;
              *(undefined8 *)(puVar10 + 5) = 0;
              *(undefined8 *)(puVar10 + 0x21) = 0x10000000004;
              *(undefined8 *)(puVar10 + 0xb) = 0;
              *(undefined8 *)(puVar10 + 9) = 0;
              *(undefined8 *)(puVar10 + 0xf) = 0;
              *(undefined8 *)(puVar10 + 0xd) = 0;
              *(undefined8 *)(puVar10 + 0x13) = 0;
              *(undefined8 *)(puVar10 + 0x11) = 0;
              *(undefined8 *)(puVar10 + 0x17) = 0;
              *(undefined8 *)(puVar10 + 0x15) = 0;
              *(undefined8 *)(puVar10 + 0x1b) = 0;
              *(undefined8 *)(puVar10 + 0x19) = 0;
              *(undefined8 *)(puVar10 + 0x1f) = 0;
              *(undefined8 *)(puVar10 + 0x1d) = 0;
            }
            goto LAB_0017ee1c;
          }
          break;
        }
        iVar1 = *(int *)(lVar17 + 0x18);
        if (iVar1 == 3) {
          if ((*(byte *)(lVar17 + 0x44) & 1) == 0) {
            iVar3 = *piVar8;
            goto joined_r0x0017f074;
          }
          emit_block_stmts(param_1,uVar25,param_4);
          puVar9 = calloc(1,0x130);
          if (puVar9 == (undefined4 *)0x0) break;
          *puVar9 = 4;
          puVar10 = calloc(1,0x130);
          if (puVar10 != (undefined4 *)0x0) {
            uVar4 = *(undefined4 *)(lVar17 + 0x20);
            *puVar10 = 10;
            puVar14 = calloc(1,0x130);
            if (puVar14 != (undefined4 *)0x0) {
              *puVar14 = 0xd;
              puVar14[0x26] = uVar4;
              __snprintf_chk(puVar14 + 0x27,0x40,2,0x40,&DAT_001f9928);
            }
            uVar4 = *(undefined4 *)(lVar17 + 0x24);
            *(undefined4 **)(puVar10 + 0x26) = puVar14;
            uVar13 = build_expr(param_1,uVar4);
            *(undefined8 *)(puVar10 + 0x28) = uVar13;
          }
          iVar1 = *piVar8;
          *(undefined4 **)(puVar9 + 0x26) = puVar10;
          if ((iVar1 == 0x17) && (piVar8[0x12] != 0)) {
            puVar10 = (undefined4 *)build_expr(param_1,piVar8[6]);
          }
          else {
            puVar10 = calloc(1,0x130);
            if (puVar10 != (undefined4 *)0x0) {
              *(undefined8 *)(puVar10 + 0x26) = 1;
              *puVar10 = 0xe;
              *(undefined8 *)(puVar10 + 3) = 0;
              *(undefined8 *)(puVar10 + 1) = 0x745f3233746e69;
              *(undefined8 *)(puVar10 + 7) = 0;
              *(undefined8 *)(puVar10 + 5) = 0;
              *(undefined8 *)(puVar10 + 0x21) = 0x10000000004;
              *(undefined8 *)(puVar10 + 0xb) = 0;
              *(undefined8 *)(puVar10 + 9) = 0;
              *(undefined8 *)(puVar10 + 0xf) = 0;
              *(undefined8 *)(puVar10 + 0xd) = 0;
              *(undefined8 *)(puVar10 + 0x13) = 0;
              *(undefined8 *)(puVar10 + 0x11) = 0;
              *(undefined8 *)(puVar10 + 0x17) = 0;
              *(undefined8 *)(puVar10 + 0x15) = 0;
              *(undefined8 *)(puVar10 + 0x1b) = 0;
              *(undefined8 *)(puVar10 + 0x19) = 0;
              *(undefined8 *)(puVar10 + 0x1f) = 0;
              *(undefined8 *)(puVar10 + 0x1d) = 0;
            }
          }
          *(undefined4 **)(puVar9 + 0x28) = puVar10;
          puVar10 = calloc(1,0x130);
          if (puVar10 != (undefined4 *)0x0) {
            uVar4 = *(undefined4 *)(lVar17 + 0x20);
            *puVar10 = 10;
            puVar14 = calloc(1,0x130);
            if (puVar14 != (undefined4 *)0x0) {
              *puVar14 = 0xd;
              puVar14[0x26] = uVar4;
              __snprintf_chk(puVar14 + 0x27,0x40,2,0x40,&DAT_001f9928);
            }
            *(undefined4 **)(puVar10 + 0x26) = puVar14;
            puVar14 = calloc(1,0x130);
            if (puVar14 != (undefined4 *)0x0) {
              uVar4 = *(undefined4 *)(lVar17 + 0x20);
              uVar5 = *(undefined4 *)(lVar17 + 0x38);
              *puVar14 = 0xf;
              puVar14[0x2a] = uVar5;
              puVar15 = calloc(1,0x130);
              if (puVar15 != (undefined4 *)0x0) {
                *puVar15 = 0xd;
                puVar15[0x26] = uVar4;
                __snprintf_chk(puVar15 + 0x27,0x40,2,0x40,&DAT_001f9928);
              }
              uVar13 = *(undefined8 *)(lVar17 + 0x30);
              *(undefined4 **)(puVar14 + 0x26) = puVar15;
              uVar13 = hir_const_create(uVar13);
              *(undefined8 *)(puVar14 + 0x28) = uVar13;
            }
            *(undefined4 **)(puVar10 + 0x28) = puVar14;
          }
          *(undefined4 **)(puVar9 + 0x2a) = puVar10;
          pvVar11 = calloc(1,0x130);
          if (pvVar11 != (void *)0x0) {
            pvVar12 = calloc(8,8);
            iVar1 = *piVar8;
            *(void **)((long)pvVar11 + 0x98) = pvVar12;
            *(undefined4 *)((long)pvVar11 + 0xa4) = 8;
            if (iVar1 == 0x17) {
              uVar26 = piVar8[0x19];
              uVar16 = *(uint *)(*param_1 + 8);
              if ((*(uint *)(lVar17 + 0x14) != 0xffffffff) && (*(uint *)(lVar17 + 0x14) == uVar26))
              {
                uVar26 = piVar8[0x1a];
              }
            }
            else {
              uVar16 = *(uint *)(*param_1 + 8);
              uVar26 = uVar16;
              if (*(int *)(lVar21 + 0x30) != 0) {
                uVar26 = **(uint **)(lVar21 + 0x28);
              }
            }
            pvVar12 = calloc((ulong)uVar16,1);
            if (pvVar12 != (void *)0x0) {
              lVar21 = param_1[6];
              __memcpy_chk(pvVar12,lVar21,(ulong)uVar16);
              *(undefined1 *)(lVar21 + uVar25) = 1;
              emit_region(param_1,uVar26,uVar25,pvVar11);
              uVar6 = *(undefined1 *)(param_1[6] + uVar25);
              memcpy((void *)param_1[6],pvVar12,(ulong)*(uint *)(*param_1 + 8));
              *(undefined1 *)(param_1[6] + uVar25) = uVar6;
              free(pvVar12);
            }
          }
          *(void **)(puVar9 + 0x2c) = pvVar11;
          if ((param_4 != (int *)0x0) && (*param_4 == 0)) {
            uVar16 = param_4[0x28];
            uVar26 = param_4[0x29];
            pvVar11 = *(void **)(param_4 + 0x26);
            if (uVar26 <= uVar16) {
              pvVar11 = realloc(pvVar11,((ulong)uVar26 & 0x7fffffff) << 4);
              if (pvVar11 == (void *)0x0) goto LAB_0017f3c4;
              uVar16 = param_4[0x28];
              *(void **)(param_4 + 0x26) = pvVar11;
              param_4[0x29] = uVar26 << 1;
            }
            param_4[0x28] = uVar16 + 1;
            *(undefined4 **)((long)pvVar11 + (ulong)uVar16 * 8) = puVar9;
          }
        }
        else {
          if ((iVar1 != 2) && ((iVar3 = *piVar8, iVar1 != 0 || (iVar3 != 0x18)))) {
joined_r0x0017f074:
            if (iVar3 != 0x17) {
              emit_block_stmts(param_1,uVar25,param_4);
              if (*(uint *)(lVar21 + 0x30) < 3) goto LAB_0017ea80;
              puVar9 = calloc(1,0x130);
              if (puVar9 != (undefined4 *)0x0) {
                *puVar9 = 5;
                goto LAB_0017ed70;
              }
              break;
            }
            emit_block_stmts(param_1,uVar25,param_4);
            puVar9 = calloc(1,0x130);
            if (puVar9 == (undefined4 *)0x0) break;
            iVar1 = piVar8[0x12];
            *puVar9 = 2;
            if (iVar1 == 0) {
              puVar10 = calloc(1,0x130);
              if (puVar10 != (undefined4 *)0x0) {
                *puVar10 = 0xe;
                *(undefined8 *)(puVar10 + 0x26) = 1;
                *(undefined8 *)(puVar10 + 3) = 0;
                *(undefined8 *)(puVar10 + 1) = 0x745f3233746e69;
                *(undefined8 *)(puVar10 + 7) = 0;
                *(undefined8 *)(puVar10 + 5) = 0;
                *(undefined8 *)(puVar10 + 0xb) = 0;
                *(undefined8 *)(puVar10 + 9) = 0;
                *(undefined8 *)(puVar10 + 0xf) = 0;
                *(undefined8 *)(puVar10 + 0xd) = 0;
                *(undefined8 *)(puVar10 + 0x13) = 0;
                *(undefined8 *)(puVar10 + 0x11) = 0;
                *(undefined8 *)(puVar10 + 0x17) = 0;
                *(undefined8 *)(puVar10 + 0x15) = 0;
                *(undefined8 *)(puVar10 + 0x1b) = 0;
                *(undefined8 *)(puVar10 + 0x19) = 0;
                *(undefined8 *)(puVar10 + 0x1f) = 0;
                *(undefined8 *)(puVar10 + 0x1d) = 0;
                *(undefined8 *)(puVar10 + 0x21) = 0x10000000004;
              }
            }
            else {
              puVar10 = (undefined4 *)build_expr(param_1,piVar8[6]);
            }
            uVar16 = piVar8[0x19];
            uVar26 = *(uint *)(lVar17 + 0x14);
            *(undefined4 **)(puVar9 + 0x26) = puVar10;
            if ((uVar26 == 0xffffffff) || (*(uint *)(*param_1 + 8) <= uVar26)) {
              uVar26 = piVar8[0x1a];
            }
            else if (uVar26 == uVar16) {
              uVar16 = piVar8[0x1a];
            }
            pvVar11 = calloc(1,0x130);
            if (pvVar11 != (void *)0x0) {
              pvVar12 = calloc(8,8);
              *(void **)((long)pvVar11 + 0x98) = pvVar12;
              lVar17 = *param_1;
              *(undefined4 *)((long)pvVar11 + 0xa4) = 8;
              uVar22 = *(uint *)(lVar17 + 8);
              pvVar12 = calloc((ulong)uVar22,1);
              if (pvVar12 != (void *)0x0) {
                lVar17 = param_1[6];
                __memcpy_chk(pvVar12,lVar17,(ulong)uVar22);
                *(undefined1 *)(lVar17 + uVar25) = 1;
                emit_region(param_1,uVar16,uVar25,pvVar11);
                memcpy((void *)param_1[6],pvVar12,(ulong)*(uint *)(*param_1 + 8));
                *(undefined1 *)(param_1[6] + uVar25) = 1;
                free(pvVar12);
              }
            }
            *(void **)(puVar9 + 0x28) = pvVar11;
            if ((param_4 != (int *)0x0) && (*param_4 == 0)) {
              uVar16 = param_4[0x28];
              uVar22 = param_4[0x29];
              pvVar11 = *(void **)(param_4 + 0x26);
              if (uVar22 <= uVar16) {
                pvVar11 = realloc(pvVar11,((ulong)uVar22 & 0x7fffffff) << 4);
                if (pvVar11 == (void *)0x0) goto LAB_0017f1b4;
                uVar16 = param_4[0x28];
                *(void **)(param_4 + 0x26) = pvVar11;
                param_4[0x29] = uVar22 << 1;
              }
              param_4[0x28] = uVar16 + 1;
              *(undefined4 **)((long)pvVar11 + (ulong)uVar16 * 8) = puVar9;
            }
LAB_0017f1b4:
            plVar7 = (long *)*param_1;
            if (*(uint *)(plVar7 + 1) <= uVar26 || uVar26 == param_3) break;
            uVar25 = (ulong)uVar26;
            lVar17 = param_1[6];
            goto LAB_0017e9b4;
          }
          puVar9 = calloc(1,0x130);
          if (puVar9 == (undefined4 *)0x0) break;
          *puVar9 = 3;
          pvVar11 = calloc(1,0x130);
          if (pvVar11 == (void *)0x0) {
            local_190 = (long *)*param_1;
            uVar26 = *(uint *)(lVar17 + 4);
            uVar16 = *(uint *)(local_190 + 1);
LAB_0017fcbc:
            *(void **)(puVar9 + 0x28) = pvVar11;
            if (uVar26 < uVar16) goto LAB_0017f850;
LAB_0017f2f0:
            puVar10 = calloc(1,0x130);
            if (puVar10 != (undefined4 *)0x0) {
              *puVar10 = 0xe;
              *(undefined8 *)(puVar10 + 0x26) = 1;
              *(undefined8 *)(puVar10 + 3) = 0;
              *(undefined8 *)(puVar10 + 1) = 0x745f3233746e69;
              *(undefined8 *)(puVar10 + 7) = 0;
              *(undefined8 *)(puVar10 + 5) = 0;
              *(undefined8 *)(puVar10 + 0x21) = 0x10000000004;
              *(undefined8 *)(puVar10 + 0xb) = 0;
              *(undefined8 *)(puVar10 + 9) = 0;
              *(undefined8 *)(puVar10 + 0xf) = 0;
              *(undefined8 *)(puVar10 + 0xd) = 0;
              *(undefined8 *)(puVar10 + 0x13) = 0;
              *(undefined8 *)(puVar10 + 0x11) = 0;
              *(undefined8 *)(puVar10 + 0x17) = 0;
              *(undefined8 *)(puVar10 + 0x15) = 0;
              *(undefined8 *)(puVar10 + 0x1b) = 0;
              *(undefined8 *)(puVar10 + 0x19) = 0;
              *(undefined8 *)(puVar10 + 0x1f) = 0;
              *(undefined8 *)(puVar10 + 0x1d) = 0;
            }
          }
          else {
            pvVar12 = calloc(8,8);
            *(void **)((long)pvVar11 + 0x98) = pvVar12;
            *(undefined4 *)((long)pvVar11 + 0xa4) = 8;
            emit_block_stmts(param_1,uVar25,pvVar11);
            if (*piVar8 == 0x18) {
              uVar26 = piVar8[0x19];
LAB_0017f254:
              local_190 = (long *)*param_1;
              uVar16 = *(uint *)(local_190 + 1);
              pvVar12 = calloc((ulong)uVar16,1);
              if (pvVar12 == (void *)0x0) {
LAB_0017fcb8:
                uVar26 = *(uint *)(lVar17 + 4);
                goto LAB_0017fcbc;
              }
              lVar21 = param_1[6];
              __memcpy_chk(pvVar12,lVar21,(ulong)uVar16);
              uVar22 = *(uint *)(lVar17 + 4);
              *(undefined1 *)(lVar21 + uVar25) = 1;
              if ((uVar22 != uVar26 && uVar26 <= uVar16) && (uVar22 == uVar26 || uVar16 != uVar26))
              {
                emit_region(param_1,uVar26,uVar22,pvVar11);
                uVar22 = *(uint *)(lVar17 + 4);
                uVar16 = *(uint *)(*param_1 + 8);
              }
            }
            else {
              if (*(int *)(lVar21 + 0x30) != 0) {
                uVar26 = **(uint **)(lVar21 + 0x28);
                goto LAB_0017f254;
              }
              local_190 = (long *)*param_1;
              uVar16 = *(uint *)(local_190 + 1);
              pvVar12 = calloc((ulong)uVar16,1);
              if (pvVar12 == (void *)0x0) goto LAB_0017fcb8;
              lVar21 = param_1[6];
              __memcpy_chk(pvVar12,lVar21,(ulong)uVar16);
              uVar22 = *(uint *)(lVar17 + 4);
              *(undefined1 *)(lVar21 + uVar25) = 1;
            }
            if (uVar22 < uVar16) {
              emit_block_stmts(param_1,uVar22,pvVar11);
              pvVar18 = (void *)param_1[6];
              uVar16 = *(uint *)(*param_1 + 8);
              *(undefined1 *)((long)pvVar18 + (ulong)*(uint *)(lVar17 + 4)) = 1;
            }
            else {
              pvVar18 = (void *)param_1[6];
            }
            memcpy(pvVar18,pvVar12,(ulong)uVar16);
            local_190 = (long *)*param_1;
            lVar21 = param_1[6];
            uVar26 = *(uint *)(lVar17 + 4);
            uVar16 = *(uint *)(local_190 + 1);
            *(undefined1 *)(lVar21 + uVar25) = 1;
            if (uVar16 <= uVar26) {
              free(pvVar12);
              *(void **)(puVar9 + 0x28) = pvVar11;
              goto LAB_0017f2f0;
            }
            *(undefined1 *)(lVar21 + (ulong)uVar26) = 1;
            free(pvVar12);
            *(void **)(puVar9 + 0x28) = pvVar11;
LAB_0017f850:
            lVar21 = *local_190 + (ulong)uVar26 * 0x50;
            uVar16 = *(uint *)(lVar21 + 0x10);
            uVar26 = uVar16 - 1;
            if (-1 < (int)uVar26) {
              lVar21 = *(long *)(lVar21 + 8);
              piVar8 = (int *)(lVar21 + (long)(int)uVar26 * 0x88);
              do {
                iVar1 = *piVar8;
                if (iVar1 - 0x17U < 2 || iVar1 == 0x1a) {
                  if ((iVar1 == 0x17) && (piVar8[0x12] != 0)) {
                    puVar10 = (undefined4 *)build_expr(param_1,piVar8[6]);
                    goto LAB_0017f390;
                  }
                  break;
                }
                piVar8 = piVar8 + -0x22;
              } while (piVar8 != (int *)(lVar21 + -0x110 + ((ulong)uVar16 - (ulong)uVar26) * 0x88));
            }
            puVar10 = calloc(1,0x130);
            if (puVar10 != (undefined4 *)0x0) {
              *puVar10 = 0xe;
              *(undefined8 *)(puVar10 + 0x26) = 1;
              *(undefined8 *)(puVar10 + 3) = 0;
              *(undefined8 *)(puVar10 + 1) = 0x745f3233746e69;
              *(undefined8 *)(puVar10 + 7) = 0;
              *(undefined8 *)(puVar10 + 5) = 0;
              *(undefined8 *)(puVar10 + 0xb) = 0;
              *(undefined8 *)(puVar10 + 9) = 0;
              *(undefined8 *)(puVar10 + 0xf) = 0;
              *(undefined8 *)(puVar10 + 0xd) = 0;
              *(undefined8 *)(puVar10 + 0x13) = 0;
              *(undefined8 *)(puVar10 + 0x11) = 0;
              *(undefined8 *)(puVar10 + 0x17) = 0;
              *(undefined8 *)(puVar10 + 0x15) = 0;
              *(undefined8 *)(puVar10 + 0x1b) = 0;
              *(undefined8 *)(puVar10 + 0x19) = 0;
              *(undefined8 *)(puVar10 + 0x1f) = 0;
              *(undefined8 *)(puVar10 + 0x1d) = 0;
              *(undefined8 *)(puVar10 + 0x21) = 0x10000000004;
            }
          }
LAB_0017f390:
          *(undefined4 **)(puVar9 + 0x26) = puVar10;
          if ((param_4 != (int *)0x0) && (*param_4 == 0)) {
            uVar16 = param_4[0x28];
            uVar26 = param_4[0x29];
            pvVar11 = *(void **)(param_4 + 0x26);
            if (uVar26 <= uVar16) {
              pvVar11 = realloc(pvVar11,((ulong)uVar26 & 0x7fffffff) << 4);
              if (pvVar11 == (void *)0x0) goto LAB_0017f3c4;
              uVar16 = param_4[0x28];
              *(void **)(param_4 + 0x26) = pvVar11;
              param_4[0x29] = uVar26 << 1;
            }
            param_4[0x28] = uVar16 + 1;
            *(undefined4 **)((long)pvVar11 + (ulong)uVar16 * 8) = puVar9;
          }
        }
LAB_0017f3c4:
        plVar7 = (long *)*param_1;
        uVar16 = *(uint *)(lVar17 + 0x14);
        uVar25 = (ulong)uVar16;
        if (*(uint *)(plVar7 + 1) <= uVar16 || uVar16 == param_3) break;
        lVar17 = param_1[6];
        goto LAB_0017e9b4;
      }
      emit_block_stmts(param_1,uVar25,param_4);
      if (2 < *(uint *)(lVar21 + 0x30)) {
        puVar9 = calloc(1,0x130);
        if (puVar9 != (undefined4 *)0x0) {
          *puVar9 = 5;
          if (piVar8 == (int *)0x0) goto LAB_0017ed78;
LAB_0017ed70:
          if (piVar8[0x12] == 0) goto LAB_0017ed78;
          puVar10 = (undefined4 *)build_expr(param_1,piVar8[6]);
LAB_0017ee1c:
          uVar16 = *(uint *)(lVar21 + 0x30);
          *(undefined4 **)(puVar9 + 0x26) = puVar10;
          lVar17 = 0;
          pvVar11 = calloc((ulong)uVar16,0x18);
          *(void **)(puVar9 + 0x28) = pvVar11;
          puVar9[0x2a] = uVar16;
          puVar9[0x2b] = uVar16;
          if (uVar16 != 0) goto LAB_0017ee40;
          goto LAB_0017ef74;
        }
        break;
      }
      if (piVar8 == (int *)0x0) break;
LAB_0017ea80:
      iVar1 = *piVar8;
      if (iVar1 != 0x18) {
        if (iVar1 == 0x1a) {
          puVar9 = calloc(1,0x130);
          if (puVar9 == (undefined4 *)0x0) break;
          iVar1 = piVar8[0x12];
          *puVar9 = 0xb;
          if ((iVar1 != 0) && (piVar8[6] != -1)) {
            uVar13 = build_expr(param_1);
            *(undefined8 *)(puVar9 + 0x26) = uVar13;
          }
          if ((param_4 == (int *)0x0) || (*param_4 != 0)) break;
          uVar16 = param_4[0x28];
          uVar26 = param_4[0x29];
          pvVar11 = *(void **)(param_4 + 0x26);
          if (uVar26 <= uVar16) {
            pvVar11 = realloc(pvVar11,((ulong)uVar26 & 0x7fffffff) << 4);
            if (pvVar11 == (void *)0x0) break;
            uVar16 = param_4[0x28];
            *(void **)(param_4 + 0x26) = pvVar11;
            param_4[0x29] = uVar26 << 1;
          }
          param_4[0x28] = uVar16 + 1;
          *(undefined4 **)((long)pvVar11 + (ulong)uVar16 * 8) = puVar9;
          break;
        }
        if (iVar1 != 0x17) break;
        uVar23 = 0xffffffff;
        uVar16 = piVar8[0x19];
        uVar26 = piVar8[0x1a];
        if (param_1[1] != 0) {
          uVar23 = sa_find_join(param_1[1],*param_1,uVar25);
          uVar23 = uVar23 & 0xffffffff;
        }
        puVar9 = calloc(1,0x130);
        if (puVar9 == (undefined4 *)0x0) break;
        iVar1 = piVar8[0x12];
        *puVar9 = 1;
        if (iVar1 == 0) {
          puVar10 = calloc(1,0x130);
          if (puVar10 != (undefined4 *)0x0) {
            *puVar10 = 0xe;
            *(undefined8 *)(puVar10 + 0x26) = 1;
            *(undefined8 *)(puVar10 + 3) = 0;
            *(undefined8 *)(puVar10 + 1) = 0x745f3233746e69;
            *(undefined8 *)(puVar10 + 7) = 0;
            *(undefined8 *)(puVar10 + 5) = 0;
            *(undefined8 *)(puVar10 + 0xb) = 0;
            *(undefined8 *)(puVar10 + 9) = 0;
            *(undefined8 *)(puVar10 + 0xf) = 0;
            *(undefined8 *)(puVar10 + 0xd) = 0;
            *(undefined8 *)(puVar10 + 0x13) = 0;
            *(undefined8 *)(puVar10 + 0x11) = 0;
            *(undefined8 *)(puVar10 + 0x17) = 0;
            *(undefined8 *)(puVar10 + 0x15) = 0;
            *(undefined8 *)(puVar10 + 0x1b) = 0;
            *(undefined8 *)(puVar10 + 0x19) = 0;
            *(undefined8 *)(puVar10 + 0x1f) = 0;
            *(undefined8 *)(puVar10 + 0x1d) = 0;
            *(undefined8 *)(puVar10 + 0x21) = 0x10000000004;
          }
        }
        else {
          puVar10 = (undefined4 *)build_expr(param_1,piVar8[6]);
        }
        *(undefined4 **)(puVar9 + 0x26) = puVar10;
        pvVar11 = calloc(1,0x130);
        uVar22 = (uint)uVar23;
        if (pvVar11 != (void *)0x0) {
          pvVar12 = calloc(8,8);
          *(void **)((long)pvVar11 + 0x98) = pvVar12;
          *(undefined4 *)((long)pvVar11 + 0xa4) = 8;
          emit_phi_assigns(param_1,uVar23,uVar25,pvVar11);
          uVar2 = *(uint *)(*param_1 + 8);
          sVar27 = (size_t)uVar2;
          pvVar12 = calloc(sVar27,1);
          if (pvVar12 != (void *)0x0) {
            pvVar18 = (void *)param_1[6];
            __memcpy_chk(pvVar12,pvVar18,sVar27,sVar27);
            if (uVar16 < uVar2 && uVar22 != uVar16) {
              uVar2 = param_3;
              if (uVar22 != 0xffffffff) {
                uVar2 = uVar22;
              }
              emit_region(param_1,uVar16,uVar2,pvVar11);
              pvVar18 = (void *)param_1[6];
              sVar27 = (size_t)*(uint *)(*param_1 + 8);
            }
            memcpy(pvVar18,pvVar12,sVar27);
            free(pvVar12);
          }
        }
        plVar7 = (long *)*param_1;
        uVar16 = *(uint *)(plVar7 + 1);
        *(void **)(puVar9 + 0x28) = pvVar11;
        if (uVar26 < uVar16) {
          if (uVar22 != uVar26) {
            pvVar11 = calloc(1,0x130);
            if (pvVar11 != (void *)0x0) {
              pvVar12 = calloc(8,8);
              *(void **)((long)pvVar11 + 0x98) = pvVar12;
              *(undefined4 *)((long)pvVar11 + 0xa4) = 8;
              emit_phi_assigns(param_1,uVar23,uVar25,pvVar11);
              uVar25 = (ulong)*(uint *)(*param_1 + 8);
              pvVar12 = calloc(uVar25,1);
              if (pvVar12 != (void *)0x0) {
                __memcpy_chk(pvVar12,param_1[6],uVar25,uVar25);
                uVar16 = param_3;
                if (uVar22 != 0xffffffff) {
                  uVar16 = uVar22;
                }
                emit_region(param_1,uVar26,uVar16,pvVar11);
                memcpy((void *)param_1[6],pvVar12,(ulong)*(uint *)(*param_1 + 8));
                free(pvVar12);
              }
            }
            *(void **)(puVar9 + 0x2a) = pvVar11;
            goto LAB_0017f490;
          }
          if ((param_4 != (int *)0x0) && (*param_4 == 0)) goto LAB_0017ec1c;
        }
        else {
LAB_0017f490:
          if ((param_4 != (int *)0x0) && (*param_4 == 0)) {
LAB_0017ec1c:
            uVar16 = param_4[0x28];
            uVar26 = param_4[0x29];
            pvVar11 = *(void **)(param_4 + 0x26);
            if (uVar26 <= uVar16) {
              pvVar11 = realloc(pvVar11,((ulong)uVar26 & 0x7fffffff) << 4);
              if (pvVar11 == (void *)0x0) goto LAB_0017ec38;
              uVar16 = param_4[0x28];
              *(void **)(param_4 + 0x26) = pvVar11;
              param_4[0x29] = uVar26 << 1;
            }
            param_4[0x28] = uVar16 + 1;
            *(undefined4 **)((long)pvVar11 + (ulong)uVar16 * 8) = puVar9;
          }
LAB_0017ec38:
          if (uVar22 == 0xffffffff) break;
          plVar7 = (long *)*param_1;
          uVar16 = *(uint *)(plVar7 + 1);
        }
        if (uVar22 == param_3 || uVar16 <= uVar22) break;
        lVar17 = param_1[6];
        uVar25 = uVar23;
        goto LAB_0017e9b4;
      }
      plVar7 = (long *)*param_1;
      uVar16 = piVar8[0x19];
      if (*(uint *)(plVar7 + 1) <= uVar16 || param_3 == uVar16) break;
      lVar17 = param_1[6];
      uVar25 = (ulong)uVar16;
    } while ((*(byte *)(lVar17 + (ulong)uVar16) & 1) == 0);
  }
  goto LAB_0017eaac;
LAB_0017ee40:
  do {
    lVar24 = lVar17 * 0x18;
    *(long *)((long)pvVar11 + lVar17 * 0x18) = lVar17;
    *(bool *)((long)pvVar11 + lVar24 + 8) = uVar16 - 1 == (int)lVar17;
    piVar8 = calloc(1,0x130);
    if (piVar8 == (int *)0x0) {
      puVar10 = calloc(1,0x130);
      if (puVar10 != (undefined4 *)0x0) {
        *puVar10 = 8;
      }
    }
    else {
      pvVar11 = calloc(8,8);
      *(void **)(piVar8 + 0x26) = pvVar11;
      lVar19 = *param_1;
      piVar8[0x29] = 8;
      uVar16 = *(uint *)(lVar19 + 8);
      sVar27 = (size_t)uVar16;
      pvVar11 = calloc(sVar27,1);
      if (pvVar11 != (void *)0x0) {
        pvVar12 = (void *)param_1[6];
        __memcpy_chk();
        uVar26 = *(uint *)(*(long *)(lVar21 + 0x28) + lVar17 * 4);
        *(undefined1 *)((long)pvVar12 + uVar25) = 1;
        if ((uVar26 < uVar16) && ((*(byte *)((long)pvVar12 + (ulong)uVar26) & 1) == 0)) {
          emit_region(param_1,uVar26,param_3,piVar8);
          pvVar12 = (void *)param_1[6];
          sVar27 = (size_t)*(uint *)(*param_1 + 8);
        }
        memcpy(pvVar12,pvVar11,sVar27);
        *(undefined1 *)(param_1[6] + uVar25) = 1;
        free(pvVar11);
      }
      puVar10 = calloc(1,0x130);
      if ((puVar10 != (undefined4 *)0x0) && (*puVar10 = 8, *piVar8 == 0)) {
        uVar16 = piVar8[0x28];
        uVar26 = piVar8[0x29];
        pvVar11 = *(void **)(piVar8 + 0x26);
        if (uVar26 <= uVar16) {
          pvVar11 = realloc(pvVar11,((ulong)uVar26 & 0x7fffffff) << 4);
          if (pvVar11 == (void *)0x0) goto LAB_0017ef58;
          uVar16 = piVar8[0x28];
          *(void **)(piVar8 + 0x26) = pvVar11;
          piVar8[0x29] = uVar26 << 1;
        }
        piVar8[0x28] = uVar16 + 1;
        *(undefined4 **)((long)pvVar11 + (ulong)uVar16 * 8) = puVar10;
      }
    }
LAB_0017ef58:
    pvVar11 = *(void **)(puVar9 + 0x28);
    lVar17 = lVar17 + 1;
    uVar16 = *(uint *)(lVar21 + 0x30);
    *(int **)((long)pvVar11 + lVar24 + 0x10) = piVar8;
  } while ((uint)lVar17 < uVar16);
LAB_0017ef74:
  if ((param_4 != (int *)0x0) && (*param_4 == 0)) {
    uVar16 = param_4[0x28];
    uVar26 = param_4[0x29];
    pvVar11 = *(void **)(param_4 + 0x26);
    if (uVar26 <= uVar16) {
      pvVar11 = realloc(pvVar11,((ulong)uVar26 & 0x7fffffff) << 4);
      if (pvVar11 == (void *)0x0) goto LAB_0017eaac;
      uVar16 = param_4[0x28];
      *(void **)(param_4 + 0x26) = pvVar11;
      param_4[0x29] = uVar26 << 1;
    }
    param_4[0x28] = uVar16 + 1;
    *(undefined4 **)((long)pvVar11 + (ulong)uVar16 * 8) = puVar9;
  }
LAB_0017eaac:
  if (lVar20 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,lVar20 - *(long *)PTR___stack_chk_guard_005ffe88
                  );
}

