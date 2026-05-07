
undefined4 * build_expr_from_instr(undefined *param_1,uint *param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined8 uVar5;
  void *pvVar6;
  undefined4 *puVar7;
  undefined8 *puVar8;
  undefined *puVar9;
  undefined1 uVar10;
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
  
  uVar2 = *param_2;
  local_58 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (uVar2 == 0x15) {
    puVar4 = calloc(1,0x130);
    if (puVar4 == (undefined4 *)0x0) {
LAB_0017f2f0:
      puVar4 = (undefined4 *)0x0;
    }
    else {
      uVar2 = param_2[0x12];
      *puVar4 = 0x10;
      puVar4[0x28] = 3;
      if (uVar2 == 0) {
        uVar2 = param_2[2];
        puVar7 = calloc(1,0x130);
        if (puVar7 != (undefined4 *)0x0) {
          *puVar7 = 0xd;
          puVar7[0x26] = uVar2;
          __snprintf_chk(puVar7 + 0x27,0x40,2,0x40,&DAT_001faae0,uVar2);
        }
      }
      else {
        puVar7 = (undefined4 *)build_expr(param_1,param_2[6]);
      }
      uVar10 = (undefined1)param_2[0x22];
      uVar2 = param_2[3];
      *(undefined4 **)(puVar4 + 0x26) = puVar7;
LAB_0017edb0:
      ir_type_to_hir_ex(uVar2,uVar10);
      *(undefined8 *)(puVar4 + 3) = uStack_e8;
      *(undefined8 *)(puVar4 + 1) = local_f0;
      *(undefined8 *)(puVar4 + 7) = uStack_d8;
      *(undefined8 *)(puVar4 + 5) = uStack_e0;
      *(undefined8 *)(puVar4 + 0xb) = uStack_c8;
      *(undefined8 *)(puVar4 + 9) = local_d0;
      *(undefined8 *)(puVar4 + 0xf) = uStack_b8;
      *(undefined8 *)(puVar4 + 0xd) = uStack_c0;
      *(undefined8 *)(puVar4 + 0x13) = uStack_a8;
      *(undefined8 *)(puVar4 + 0x11) = local_b0;
      *(undefined8 *)(puVar4 + 0x17) = uStack_98;
      *(undefined8 *)(puVar4 + 0x15) = uStack_a0;
      *(undefined8 *)(puVar4 + 0x1b) = uStack_88;
      *(undefined8 *)(puVar4 + 0x19) = local_90;
      *(undefined8 *)(puVar4 + 0x1f) = uStack_78;
      *(undefined8 *)(puVar4 + 0x1d) = uStack_80;
      *(undefined8 *)(puVar4 + 0x21) = local_70;
    }
  }
  else {
    if (uVar2 < 0x16) {
      if (uVar2 == 1) {
        lVar13 = local_58 - *(long *)PTR___stack_chk_guard_005ffe88;
        puVar11 = (undefined *)0x0;
        puVar9 = PTR___stack_chk_guard_005ffe88;
        if (lVar13 == 0) {
          puVar4 = (undefined4 *)hir_const_create(*(undefined8 *)(param_2 + 4),0,0);
          return puVar4;
        }
        goto LAB_0017f2e4;
      }
      if (uVar2 < 2) {
        if (param_2[0x12] != 0) {
          lVar13 = 0;
          puVar9 = param_1;
          puVar11 = PTR___stack_chk_guard_005ffe88;
          if (local_58 == *(long *)PTR___stack_chk_guard_005ffe88) {
            puVar4 = (undefined4 *)build_expr(param_1,param_2[6],0,0);
            return puVar4;
          }
          goto LAB_0017f2e4;
        }
      }
      else if (1 < param_2[0x12]) {
        puVar4 = calloc(1,0x130);
        if (puVar4 == (undefined4 *)0x0) goto LAB_0017eeb8;
        uVar1 = param_2[6];
        *puVar4 = 0xf;
        puVar4[0x2a] = uVar2;
        uVar5 = build_expr(param_1,uVar1);
        uVar2 = param_2[10];
        *(undefined8 *)(puVar4 + 0x26) = uVar5;
        uVar5 = build_expr(param_1,uVar2);
        uVar10 = (undefined1)param_2[0x22];
        uVar2 = param_2[3];
        *(undefined8 *)(puVar4 + 0x28) = uVar5;
        goto LAB_0017edb0;
      }
    }
    else {
      if (uVar2 == 0x19) {
        puVar4 = calloc(1,0x130);
        if (puVar4 == (undefined4 *)0x0) goto LAB_0017f2f0;
        uVar2 = param_2[0x12];
        *puVar4 = 0x11;
        uVar10 = DAT_001f9a7c;
        if ((uVar2 != 0) && (uVar17 = *(ulong *)(param_2 + 8), uVar17 != 0)) {
          plVar18 = *(long **)(param_1 + 0x18);
          if (plVar18 != (long *)0x0) {
            if (*(uint *)(plVar18 + 6) != 0) {
              puVar8 = (undefined8 *)plVar18[5];
              puVar12 = puVar8 + (ulong)*(uint *)(plVar18 + 6) * 5;
              do {
                if (((puVar8[2] == uVar17) && (pcVar16 = (char *)*puVar8, pcVar16 != (char *)0x0))
                   && (*pcVar16 != '\0')) {
                  pcVar15 = (char *)puVar8[1];
                  if ((char *)puVar8[1] == (char *)0x0) {
                    pcVar15 = pcVar16;
                  }
                  goto LAB_0017f108;
                }
                puVar8 = puVar8 + 5;
              } while (puVar8 != puVar12);
            }
            if (*(uint *)(plVar18 + 4) != 0) {
              puVar8 = (undefined8 *)plVar18[3];
              puVar12 = puVar8 + (ulong)*(uint *)(plVar18 + 4) * 7;
              do {
                if (((char *)*puVar8 != (char *)0x0) &&
                   (iVar3 = strcmp((char *)*puVar8,".plt"), iVar3 == 0)) {
                  if ((((ulong)puVar8[1] <= uVar17) &&
                      ((uVar17 < (ulong)(puVar8[1] + puVar8[3]) && (*plVar18 != 0)))) &&
                     (local_60 = (long *)reloc_parse(plVar18), local_60 != (long *)0x0)) {
                    if (*(uint *)(local_60 + 1) == 0) goto LAB_0017f2d4;
                    iVar3 = 0;
                    plVar18 = (long *)(*local_60 + 8);
                    plVar14 = plVar18 + (ulong)*(uint *)(local_60 + 1) * 4;
                    goto LAB_0017f270;
                  }
                  break;
                }
                puVar8 = puVar8 + 7;
              } while (puVar12 != puVar8);
            }
          }
          goto LAB_0017f1e4;
        }
        puVar4[0x26] = DAT_001f9a78;
        *(undefined1 *)(puVar4 + 0x27) = uVar10;
        goto LAB_0017ef64;
      }
      if ((uVar2 == 0x1c) && (2 < param_2[0x12])) {
        puVar4 = calloc(1,0x130);
        if (puVar4 != (undefined4 *)0x0) {
          uVar2 = param_2[6];
          *puVar4 = 0x15;
          uVar5 = build_expr(param_1,uVar2);
          uVar2 = param_2[10];
          *(undefined8 *)(puVar4 + 0x26) = uVar5;
          uVar5 = build_expr(param_1,uVar2);
          uVar2 = param_2[0xe];
          *(undefined8 *)(puVar4 + 0x28) = uVar5;
          uVar5 = build_expr(param_1,uVar2);
          uVar10 = (undefined1)param_2[0x22];
          uVar2 = param_2[3];
          *(undefined8 *)(puVar4 + 0x2a) = uVar5;
          goto LAB_0017edb0;
        }
        goto LAB_0017eeb8;
      }
    }
    uVar2 = param_2[2];
    puVar4 = calloc(1,0x130);
    if (puVar4 != (undefined4 *)0x0) {
      *puVar4 = 0xd;
      puVar4[0x26] = uVar2;
      __snprintf_chk(puVar4 + 0x27,0x40,2,0x40,&DAT_001faae0,uVar2);
    }
  }
  goto LAB_0017eeb8;
LAB_0017f270:
  if ((int)plVar18[2] != 4) goto LAB_0017f264;
  if ((uVar17 != puVar8[1] + 0x20 + (ulong)(uint)(iVar3 << 4)) || (*plVar18 == 0)) {
    iVar3 = iVar3 + 1;
    goto LAB_0017f264;
  }
  snprintf(&plt_sym_buf_0,0x80,"%s");
  reloc_table_destroy(&local_60);
  pcVar15 = &plt_sym_buf_0;
LAB_0017f108:
  snprintf((char *)(puVar4 + 0x26),0x80,"%s",pcVar15);
  uVar2 = param_2[0x12];
  goto LAB_0017ef64;
LAB_0017f264:
  plVar18 = plVar18 + 4;
  if (plVar18 == plVar14) goto LAB_0017f2d4;
  goto LAB_0017f270;
LAB_0017f2d4:
  reloc_table_destroy(&local_60);
LAB_0017f1e4:
  __snprintf_chk(puVar4 + 0x26,0x80,2,0x80,"sub_%lx",uVar17);
  uVar2 = param_2[0x12];
LAB_0017ef64:
  if (uVar2 != 0) {
    *(undefined8 *)(puVar4 + 0x46) = *(undefined8 *)(param_2 + 8);
  }
  uVar2 = param_2[0x18];
  if (uVar2 != 0) {
    pcVar16 = *(char **)(param_1 + 0x20);
    if ((((pcVar16 != (char *)0x0) && (*pcVar16 != '\0')) && (*(char *)(puVar4 + 0x26) != '\0')) &&
       (iVar3 = strcmp((char *)(puVar4 + 0x26),pcVar16), iVar3 == 0)) {
      if (*(uint *)(pcVar16 + 0xdd0) < uVar2) {
        uVar2 = *(uint *)(pcVar16 + 0xdd0);
      }
      if (uVar2 == 0) goto LAB_0017f00c;
    }
    pvVar6 = calloc((ulong)uVar2,8);
    lVar13 = 0;
    *(void **)(puVar4 + 0x48) = pvVar6;
    puVar4[0x4a] = uVar2;
    puVar4[0x4b] = uVar2;
    while( true ) {
      uVar5 = build_expr(param_1,*(undefined4 *)(*(long *)(param_2 + 0x14) + lVar13 * 2));
      *(undefined8 *)((long)pvVar6 + lVar13) = uVar5;
      lVar13 = lVar13 + 8;
      if (lVar13 == (ulong)uVar2 * 8) break;
      pvVar6 = *(void **)(puVar4 + 0x48);
    }
  }
LAB_0017f00c:
  ir_type_to_hir_ex(param_2[3],(char)param_2[0x22]);
  *(undefined8 *)(puVar4 + 3) = uStack_e8;
  *(undefined8 *)(puVar4 + 1) = local_f0;
  *(undefined8 *)(puVar4 + 7) = uStack_d8;
  *(undefined8 *)(puVar4 + 5) = uStack_e0;
  *(undefined8 *)(puVar4 + 0xb) = uStack_c8;
  *(undefined8 *)(puVar4 + 9) = local_d0;
  *(undefined8 *)(puVar4 + 0xf) = uStack_b8;
  *(undefined8 *)(puVar4 + 0xd) = uStack_c0;
  *(undefined8 *)(puVar4 + 0x13) = uStack_a8;
  *(undefined8 *)(puVar4 + 0x11) = local_b0;
  *(undefined8 *)(puVar4 + 0x17) = uStack_98;
  *(undefined8 *)(puVar4 + 0x15) = uStack_a0;
  *(undefined8 *)(puVar4 + 0x1b) = uStack_88;
  *(undefined8 *)(puVar4 + 0x19) = local_90;
  *(undefined8 *)(puVar4 + 0x1f) = uStack_78;
  *(undefined8 *)(puVar4 + 0x1d) = uStack_80;
  *(undefined8 *)(puVar4 + 0x21) = local_70;
LAB_0017eeb8:
  lVar13 = local_58 - *(long *)PTR___stack_chk_guard_005ffe88;
  puVar9 = PTR___stack_chk_guard_005ffe88;
  puVar11 = (undefined *)0x0;
  if (lVar13 == 0) {
    return puVar4;
  }
LAB_0017f2e4:
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(puVar9,puVar11,lVar13);
}

