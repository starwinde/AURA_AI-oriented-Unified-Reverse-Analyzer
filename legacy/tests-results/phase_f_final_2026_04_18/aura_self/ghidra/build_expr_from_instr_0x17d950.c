
undefined4 * build_expr_from_instr(undefined *param_1,uint *param_2)

{
  uint uVar1;
  undefined1 uVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined8 uVar6;
  void *pvVar7;
  undefined4 *puVar8;
  undefined8 *puVar9;
  undefined *puVar10;
  undefined *puVar11;
  undefined8 *puVar12;
  long lVar13;
  long *plVar14;
  char *pcVar15;
  char *pcVar16;
  ulong uVar17;
  long *plVar18;
  undefined8 local_f0;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 local_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 local_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 local_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 local_70;
  long *local_60;
  long local_58;
  
  uVar3 = *param_2;
  local_58 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (uVar3 == 0x15) {
    puVar5 = calloc(1,0x130);
    if (puVar5 == (undefined4 *)0x0) {
LAB_0017df2c:
      puVar5 = (undefined4 *)0x0;
    }
    else {
      uVar3 = param_2[0x12];
      *puVar5 = 0x10;
      puVar5[0x28] = 3;
      if (uVar3 == 0) {
        uVar3 = param_2[2];
        puVar8 = calloc(1,0x130);
        if (puVar8 != (undefined4 *)0x0) {
          *puVar8 = 0xd;
          puVar8[0x26] = uVar3;
          __snprintf_chk(puVar8 + 0x27,0x40,2,0x40,&DAT_001f9928,uVar3);
        }
      }
      else {
        puVar8 = (undefined4 *)build_expr(param_1,param_2[6]);
      }
      uVar3 = param_2[3];
      *(undefined4 **)(puVar5 + 0x26) = puVar8;
LAB_0017d9f8:
      ir_type_to_hir(&local_f0,uVar3);
      *(undefined8 *)(puVar5 + 3) = uStack_e8;
      *(undefined8 *)(puVar5 + 1) = local_f0;
      *(undefined8 *)(puVar5 + 7) = uStack_d8;
      *(undefined8 *)(puVar5 + 5) = uStack_e0;
      *(undefined8 *)(puVar5 + 0xb) = uStack_c8;
      *(undefined8 *)(puVar5 + 9) = local_d0;
      *(undefined8 *)(puVar5 + 0xf) = uStack_b8;
      *(undefined8 *)(puVar5 + 0xd) = uStack_c0;
      *(undefined8 *)(puVar5 + 0x13) = uStack_a8;
      *(undefined8 *)(puVar5 + 0x11) = local_b0;
      *(undefined8 *)(puVar5 + 0x17) = uStack_98;
      *(undefined8 *)(puVar5 + 0x15) = uStack_a0;
      *(undefined8 *)(puVar5 + 0x1b) = uStack_88;
      *(undefined8 *)(puVar5 + 0x19) = local_90;
      *(undefined8 *)(puVar5 + 0x1f) = uStack_78;
      *(undefined8 *)(puVar5 + 0x1d) = uStack_80;
      *(undefined8 *)(puVar5 + 0x21) = local_70;
    }
  }
  else {
    if (uVar3 < 0x16) {
      if (uVar3 == 1) {
        lVar13 = local_58 - *(long *)PTR___stack_chk_guard_005ffe88;
        puVar11 = (undefined *)0x0;
        puVar10 = PTR___stack_chk_guard_005ffe88;
        if (lVar13 == 0) {
          puVar5 = (undefined4 *)hir_const_create(*(undefined8 *)(param_2 + 4),0,0);
          return puVar5;
        }
        goto LAB_0017df20;
      }
      if (uVar3 < 2) {
        if (param_2[0x12] != 0) {
          lVar13 = 0;
          puVar10 = param_1;
          puVar11 = PTR___stack_chk_guard_005ffe88;
          if (local_58 == *(long *)PTR___stack_chk_guard_005ffe88) {
            puVar5 = (undefined4 *)build_expr(param_1,param_2[6],0,0);
            return puVar5;
          }
          goto LAB_0017df20;
        }
      }
      else if (1 < param_2[0x12]) {
        puVar5 = calloc(1,0x130);
        if (puVar5 == (undefined4 *)0x0) goto LAB_0017dafc;
        uVar1 = param_2[6];
        *puVar5 = 0xf;
        puVar5[0x2a] = uVar3;
        uVar6 = build_expr(param_1,uVar1);
        uVar3 = param_2[10];
        *(undefined8 *)(puVar5 + 0x26) = uVar6;
        uVar6 = build_expr(param_1,uVar3);
        uVar3 = param_2[3];
        *(undefined8 *)(puVar5 + 0x28) = uVar6;
        goto LAB_0017d9f8;
      }
    }
    else {
      if (uVar3 == 0x19) {
        puVar5 = calloc(1,0x130);
        if (puVar5 == (undefined4 *)0x0) goto LAB_0017df2c;
        uVar3 = param_2[0x12];
        *puVar5 = 0x11;
        uVar2 = DAT_001f892c;
        if ((uVar3 != 0) && (uVar17 = *(ulong *)(param_2 + 8), uVar17 != 0)) {
          plVar18 = *(long **)(param_1 + 0x18);
          if (plVar18 != (long *)0x0) {
            if (*(uint *)(plVar18 + 6) != 0) {
              puVar9 = (undefined8 *)plVar18[5];
              puVar12 = puVar9 + (ulong)*(uint *)(plVar18 + 6) * 5;
              do {
                if (((puVar9[2] == uVar17) && (pcVar16 = (char *)*puVar9, pcVar16 != (char *)0x0))
                   && (*pcVar16 != '\0')) {
                  pcVar15 = (char *)puVar9[1];
                  if ((char *)puVar9[1] == (char *)0x0) {
                    pcVar15 = pcVar16;
                  }
                  goto LAB_0017dd44;
                }
                puVar9 = puVar9 + 5;
              } while (puVar9 != puVar12);
            }
            if (*(uint *)(plVar18 + 4) != 0) {
              puVar9 = (undefined8 *)plVar18[3];
              puVar12 = puVar9 + (ulong)*(uint *)(plVar18 + 4) * 7;
              do {
                if (((char *)*puVar9 != (char *)0x0) &&
                   (iVar4 = strcmp((char *)*puVar9,".plt"), iVar4 == 0)) {
                  if ((((ulong)puVar9[1] <= uVar17) &&
                      ((uVar17 < (ulong)(puVar9[1] + puVar9[3]) && (*plVar18 != 0)))) &&
                     (local_60 = (long *)reloc_parse(plVar18), local_60 != (long *)0x0)) {
                    if (*(uint *)(local_60 + 1) == 0) goto LAB_0017df10;
                    iVar4 = 0;
                    plVar18 = (long *)(*local_60 + 8);
                    plVar14 = plVar18 + (ulong)*(uint *)(local_60 + 1) * 4;
                    goto LAB_0017deac;
                  }
                  break;
                }
                puVar9 = puVar9 + 7;
              } while (puVar12 != puVar9);
            }
          }
          goto LAB_0017de20;
        }
        puVar5[0x26] = DAT_001f8928;
        *(undefined1 *)(puVar5 + 0x27) = uVar2;
        goto LAB_0017dba8;
      }
      if ((uVar3 == 0x1c) && (2 < param_2[0x12])) {
        puVar5 = calloc(1,0x130);
        if (puVar5 != (undefined4 *)0x0) {
          uVar3 = param_2[6];
          *puVar5 = 0x15;
          uVar6 = build_expr(param_1,uVar3);
          uVar3 = param_2[10];
          *(undefined8 *)(puVar5 + 0x26) = uVar6;
          uVar6 = build_expr(param_1,uVar3);
          uVar3 = param_2[0xe];
          *(undefined8 *)(puVar5 + 0x28) = uVar6;
          uVar6 = build_expr(param_1,uVar3);
          uVar3 = param_2[3];
          *(undefined8 *)(puVar5 + 0x2a) = uVar6;
          goto LAB_0017d9f8;
        }
        goto LAB_0017dafc;
      }
    }
    uVar3 = param_2[2];
    puVar5 = calloc(1,0x130);
    if (puVar5 != (undefined4 *)0x0) {
      *puVar5 = 0xd;
      puVar5[0x26] = uVar3;
      __snprintf_chk(puVar5 + 0x27,0x40,2,0x40,&DAT_001f9928,uVar3);
    }
  }
  goto LAB_0017dafc;
LAB_0017deac:
  if ((int)plVar18[2] != 4) goto LAB_0017dea0;
  if ((uVar17 != puVar9[1] + 0x20 + (ulong)(uint)(iVar4 << 4)) || (*plVar18 == 0)) {
    iVar4 = iVar4 + 1;
    goto LAB_0017dea0;
  }
  snprintf(&plt_sym_buf_0,0x80,"%s");
  reloc_table_destroy(&local_60);
  pcVar15 = &plt_sym_buf_0;
LAB_0017dd44:
  snprintf((char *)(puVar5 + 0x26),0x80,"%s",pcVar15);
  uVar3 = param_2[0x12];
  goto LAB_0017dba8;
LAB_0017dea0:
  plVar18 = plVar18 + 4;
  if (plVar18 == plVar14) goto LAB_0017df10;
  goto LAB_0017deac;
LAB_0017df10:
  reloc_table_destroy(&local_60);
LAB_0017de20:
  __snprintf_chk(puVar5 + 0x26,0x80,2,0x80,"sub_%lx",uVar17);
  uVar3 = param_2[0x12];
LAB_0017dba8:
  if (uVar3 != 0) {
    *(undefined8 *)(puVar5 + 0x46) = *(undefined8 *)(param_2 + 8);
  }
  uVar3 = param_2[0x18];
  if (uVar3 != 0) {
    pcVar16 = *(char **)(param_1 + 0x20);
    if ((((pcVar16 != (char *)0x0) && (*pcVar16 != '\0')) && (*(char *)(puVar5 + 0x26) != '\0')) &&
       (iVar4 = strcmp((char *)(puVar5 + 0x26),pcVar16), iVar4 == 0)) {
      if (*(uint *)(pcVar16 + 0xdd0) < uVar3) {
        uVar3 = *(uint *)(pcVar16 + 0xdd0);
      }
      if (uVar3 == 0) goto LAB_0017dc54;
    }
    pvVar7 = calloc((ulong)uVar3,8);
    lVar13 = 0;
    *(void **)(puVar5 + 0x48) = pvVar7;
    puVar5[0x4a] = uVar3;
    puVar5[0x4b] = uVar3;
    while( true ) {
      uVar6 = build_expr(param_1,*(undefined4 *)(*(long *)(param_2 + 0x14) + lVar13 * 2));
      *(undefined8 *)((long)pvVar7 + lVar13) = uVar6;
      lVar13 = lVar13 + 8;
      if (lVar13 == (ulong)uVar3 * 8) break;
      pvVar7 = *(void **)(puVar5 + 0x48);
    }
  }
LAB_0017dc54:
  ir_type_to_hir(&local_f0,param_2[3]);
  *(undefined8 *)(puVar5 + 3) = uStack_e8;
  *(undefined8 *)(puVar5 + 1) = local_f0;
  *(undefined8 *)(puVar5 + 7) = uStack_d8;
  *(undefined8 *)(puVar5 + 5) = uStack_e0;
  *(undefined8 *)(puVar5 + 0xb) = uStack_c8;
  *(undefined8 *)(puVar5 + 9) = local_d0;
  *(undefined8 *)(puVar5 + 0xf) = uStack_b8;
  *(undefined8 *)(puVar5 + 0xd) = uStack_c0;
  *(undefined8 *)(puVar5 + 0x13) = uStack_a8;
  *(undefined8 *)(puVar5 + 0x11) = local_b0;
  *(undefined8 *)(puVar5 + 0x17) = uStack_98;
  *(undefined8 *)(puVar5 + 0x15) = uStack_a0;
  *(undefined8 *)(puVar5 + 0x1b) = uStack_88;
  *(undefined8 *)(puVar5 + 0x19) = local_90;
  *(undefined8 *)(puVar5 + 0x1f) = uStack_78;
  *(undefined8 *)(puVar5 + 0x1d) = uStack_80;
  *(undefined8 *)(puVar5 + 0x21) = local_70;
LAB_0017dafc:
  lVar13 = local_58 - *(long *)PTR___stack_chk_guard_005ffe88;
  puVar10 = PTR___stack_chk_guard_005ffe88;
  puVar11 = (undefined *)0x0;
  if (lVar13 == 0) {
    return puVar5;
  }
LAB_0017df20:
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(puVar10,puVar11,lVar13);
}

