
void hir_emit_pseudoc(long param_1,FILE *param_2,undefined8 param_3)

{
  long lVar1;
  uint uVar2;
  uint uVar3;
  FILE *__stream;
  undefined8 uVar4;
  long *plVar5;
  char *pcVar6;
  void *__ptr;
  char *pcVar7;
  ulong uVar8;
  void *__ptr_00;
  int *piVar9;
  long lVar10;
  long *plVar11;
  int *piVar12;
  undefined1 *puVar13;
  char *pcVar14;
  int iVar15;
  ulong uVar16;
  long lVar17;
  ulong uVar18;
  long lVar19;
  char *local_b0;
  char *local_a0;
  size_t local_98;
  char *local_90;
  char acStack_88 [32];
  long local_68;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (param_1 == 0) {
    uVar4 = 0xfffffffc;
    goto LAB_0018689c;
  }
  if (param_2 == (FILE *)0x0) {
    param_2 = *(FILE **)PTR_stdout_005fff40;
  }
  s_emit_func = param_1;
  s_emit_fi = param_3;
  if (*(char *)(param_1 + 0xdf0) != '\0') {
    __fprintf_chk(param_2,2,
                  "/* UNSUPPORTED: lifter could not lower the following mnemonic(s), output is incomplete: %s */\n"
                  ,param_1 + 0xdf0,0);
  }
  __fprintf_chk(param_2,2,"%s %s(",param_1 + 0x88,param_1);
  pcVar14 = (char *)(param_1 + 0x110);
  iVar15 = 0;
  if (*(int *)(param_1 + 0xdd0) != 0) {
    do {
      if (*pcVar14 == '\0') {
        fputs(pcVar14 + 0x40,param_2);
        uVar3 = *(uint *)(param_1 + 0xdd0);
        if (uVar3 <= iVar15 + 1U) goto LAB_00186500;
      }
      else {
        __fprintf_chk(param_2,2,"%s %s",pcVar14 + 0x40,pcVar14);
        uVar3 = *(uint *)(param_1 + 0xdd0);
        if (uVar3 <= iVar15 + 1U) goto LAB_00186500;
      }
      iVar15 = iVar15 + 1;
      pcVar14 = pcVar14 + 0xcc;
      fwrite(", ",1,2,param_2);
    } while( true );
  }
LAB_00186990:
  fwrite(&DAT_001f8ee0,1,4,param_2);
  goto LAB_00186504;
LAB_00186628:
  iVar15 = (int)plVar5[1];
  pcVar14 = local_b0;
  if ((iVar15 != 2) && (pcVar14 = "int32_t", iVar15 != 4)) {
    pcVar14 = "int64_t";
    if (iVar15 == 1) {
      pcVar14 = "int8_t";
    }
  }
LAB_0018665c:
  __snprintf_chk(acStack_88,0x20,2,0x20,"*%s%ld",uVar4,lVar19);
  if ((local_a0 == (char *)0x0) || (pcVar6 = strstr(local_a0,acStack_88), pcVar6 == (char *)0x0)) {
    fwrite(&DAT_001fb610,1,4,param_2);
    __fprintf_chk(param_2,2,"%s %s%ld;\n",pcVar14,uVar4,lVar19);
  }
  else {
    fwrite(&DAT_001fb610,1,4,param_2);
    __fprintf_chk(param_2,2,"%s *%s%ld;\n",pcVar14,uVar4,lVar19);
  }
  lVar17 = lVar17 + 1;
  if (s_stack_var_count <= (uint)lVar17) goto code_r0x001866d4;
  goto LAB_001865b8;
code_r0x001866d4:
  if (s_stack_var_count == 0) goto LAB_001866d8;
  goto LAB_00186974;
LAB_00186500:
  if (uVar3 == 0) goto LAB_00186990;
LAB_00186504:
  fwrite(&DAT_001fc3c0,1,4,param_2);
  free(s_stack_var_offsets);
  s_stack_var_count = 0;
  s_stack_var_offsets = (void *)0x0;
  s_stack_var_cap = 0;
  local_a0 = (char *)0x0;
  local_98 = 0;
  __stream = open_memstream(&local_a0,&local_98);
  if (__stream == (FILE *)0x0) {
    if ((*(long *)(param_1 + 0xdd8) != 0) && (*(int *)(param_1 + 0xde0) != 0)) {
      emit_local_decls_part_0(param_1,param_2,0);
    }
    emit_stmt_constprop_0(*(undefined8 *)(param_1 + 0xde8),param_2);
  }
  else {
    emit_stmt_constprop_0(*(undefined8 *)(param_1 + 0xde8),__stream);
    fclose(__stream);
    if ((*(long *)(param_1 + 0xdd8) == 0) || (*(int *)(param_1 + 0xde0) == 0)) {
      if (s_stack_var_count != 0) goto LAB_0018658c;
    }
    else {
      emit_local_decls_part_0(param_1,param_2,local_a0);
      if (s_stack_var_count != 0) {
LAB_0018658c:
        lVar17 = 0;
        local_b0 = "int16_t";
LAB_001865b8:
        lVar19 = *(long *)((long)s_stack_var_offsets + lVar17 * 8);
        uVar4 = stack_var_name_prefix(lVar19);
        if (s_emit_stack_frame != 0) {
          if (*(uint *)(s_emit_stack_frame + 0x20) != 0) {
            plVar5 = *(long **)(s_emit_stack_frame + 0x18);
            plVar11 = plVar5 + (ulong)*(uint *)(s_emit_stack_frame + 0x20) * 6;
            if (*(long *)(s_emit_stack_frame + 8) < 1) {
              do {
                lVar10 = *plVar5;
                lVar1 = -lVar10;
                if (-1 < lVar10) {
                  lVar1 = lVar10;
                }
                if (lVar19 == lVar1) goto LAB_00186628;
                plVar5 = plVar5 + 6;
              } while (plVar5 != plVar11);
            }
            else {
              do {
                lVar10 = *plVar5;
                lVar1 = -lVar10;
                if (-1 < lVar10) {
                  lVar1 = lVar10;
                }
                if ((lVar19 == lVar1) || (lVar19 == *(long *)(s_emit_stack_frame + 8) - lVar1))
                goto LAB_00186628;
                plVar5 = plVar5 + 6;
              } while (plVar5 != plVar11);
            }
          }
        }
        pcVar14 = "int64_t";
        goto LAB_0018665c;
      }
LAB_001866d8:
      if ((*(long *)(param_1 + 0xdd8) != 0) && (*(int *)(param_1 + 0xde0) != 0)) {
LAB_00186974:
        fputc(10,param_2);
      }
    }
    pcVar14 = local_a0;
    if (local_a0 != (char *)0x0) {
      __ptr = malloc(0x80);
      uVar16 = 0;
      uVar18 = 0x10;
      pcVar6 = pcVar14;
LAB_00186718:
      do {
        do {
          do {
            pcVar7 = strchr(pcVar6,0x76);
            __ptr_00 = __ptr;
            if (pcVar7 == (char *)0x0) goto LAB_00186848;
            pcVar6 = pcVar7 + 1;
          } while ((pcVar14 < pcVar7) && (pcVar7[-1] == '_' || (byte)(pcVar7[-1] + 0x9fU) < 0x1a));
          local_90 = (char *)0x0;
          uVar8 = strtoul(pcVar6,&local_90,10);
          pcVar14 = local_a0;
        } while ((local_90 == pcVar6) || ((byte)(*local_90 + 0x9fU) < 0x1a));
        piVar9 = *(int **)(param_1 + 0xdd8);
        pcVar6 = local_90;
        if ((piVar9 != (int *)0x0) && (*(uint *)(param_1 + 0xde0) != 0)) {
          piVar12 = piVar9 + (ulong)*(uint *)(param_1 + 0xde0) * 0x33;
          do {
            if (*piVar9 == (int)uVar8) goto LAB_00186718;
            piVar9 = piVar9 + 0x33;
          } while (piVar9 != piVar12);
        }
        if (*(uint *)(param_1 + 0xdd0) != 0) {
          lVar17 = param_1;
          do {
            if ((*(int *)(lVar17 + 0x1d8) != -1) && (*(int *)(lVar17 + 0x1d8) == (int)uVar8))
            goto LAB_00186718;
            lVar17 = lVar17 + 0xcc;
          } while (lVar17 != param_1 + (ulong)*(uint *)(param_1 + 0xdd0) * 0xcc);
        }
        uVar3 = (uint)uVar16;
        if ((__ptr != (void *)0x0) && (lVar17 = 0, uVar3 != 0)) {
          do {
            if (*(ulong *)((long)__ptr + lVar17 * 8) == uVar8) goto LAB_00186718;
            lVar17 = lVar17 + 1;
          } while ((uint)lVar17 < uVar3);
        }
        __snprintf_chk(acStack_88,0x20,2,0x20,"*v%lu",uVar8);
        pcVar14 = strstr(local_a0,acStack_88);
        if (pcVar14 == (char *)0x0) {
          fwrite(&DAT_001fb610,1,4,param_2);
          puVar13 = &DAT_001fd0e8;
        }
        else {
          fwrite(&DAT_001fb610,1,4,param_2);
          puVar13 = &DAT_001f9508;
        }
        __fprintf_chk(param_2,2,"int64_t %sv%lu;\n",puVar13,uVar8);
        if (__ptr != (void *)0x0) {
          if ((uint)uVar18 <= uVar3) {
            uVar2 = (uint)uVar18 << 1;
            uVar18 = (ulong)uVar2;
            __ptr_00 = realloc(__ptr,uVar18 << 3);
            if (__ptr_00 == (void *)0x0) {
              __ptr_00 = __ptr;
            }
            if (uVar2 <= uVar3) goto LAB_0018683c;
          }
          *(ulong *)((long)__ptr_00 + uVar16 * 8) = uVar8;
          uVar16 = (ulong)(uVar3 + 1);
        }
LAB_0018683c:
        __ptr = __ptr_00;
        pcVar14 = local_a0;
        pcVar6 = local_90;
      } while (local_90 != (char *)0x0);
LAB_00186848:
      free(__ptr_00);
    }
    fwrite(pcVar14,1,local_98,param_2);
    free(local_a0);
  }
  fwrite(&DAT_001f8ab0,1,2,param_2);
  uVar4 = 0;
LAB_0018689c:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(uVar4,PTR___stack_chk_guard_005ffe88,0,
                   local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
}

