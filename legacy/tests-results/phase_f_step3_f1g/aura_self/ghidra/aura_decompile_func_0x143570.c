
undefined4 aura_decompile_func(long param_1,ulong param_2)

{
  int iVar1;
  int iVar2;
  long lVar3;
  long lVar4;
  ulong *__ptr;
  void *__ptr_00;
  long lVar5;
  ulong *puVar6;
  ulong *puVar7;
  undefined8 *puVar8;
  undefined4 uVar9;
  undefined8 *puVar10;
  ulong uVar11;
  long local_b8;
  long local_b0;
  long local_a8;
  long local_a0;
  long local_98;
  long local_90;
  long local_88;
  long *local_80 [3];
  long local_68;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (param_1 == 0) {
    uVar9 = 0xfffffffc;
  }
  else {
    lVar3 = load_any_format(param_1,0);
    if (lVar3 == 0) {
      uVar9 = 0xfffffff9;
      __fprintf_chk(*(undefined8 *)PTR_stderr_005fffd8,2,"aura: failed to parse \'%s\'\n",param_1);
    }
    else {
      puVar8 = *(undefined8 **)(lVar3 + 0x18);
      if (*(uint *)(lVar3 + 0x20) != 0) {
        puVar10 = puVar8 + (ulong)*(uint *)(lVar3 + 0x20) * 7;
        do {
          if (((char *)*puVar8 != (char *)0x0) &&
             (iVar1 = strcmp((char *)*puVar8,".text"), iVar1 == 0)) {
            if (puVar8[5] != 0) {
              uVar11 = puVar8[1];
              if (param_2 < uVar11 || uVar11 + puVar8[3] <= param_2) {
                __fprintf_chk(*(undefined8 *)PTR_stderr_005fffd8,2,
                              "aura: func_addr 0x%016lx is outside .text [0x%lx..0x%lx]\n",param_2,
                              uVar11);
                file_info_destroy(lVar3);
                goto LAB_0014362c;
              }
              lVar4 = disasm_init(*(undefined4 *)(lVar3 + 0xc));
              if (lVar4 == 0) {
                fwrite("aura: disassembler init failed\n",1,0x1f,*(FILE **)PTR_stderr_005fffd8);
                file_info_destroy(lVar3);
              }
              else {
                lVar5 = puVar8[3];
                __ptr = malloc(0x1c000);
                if (__ptr == (ulong *)0x0) {
                  disasm_destroy(lVar4);
                  file_info_destroy(lVar3);
                  goto LAB_00143a88;
                }
                iVar2 = disasm_run(lVar4,puVar8[5] + (param_2 - uVar11),(uVar11 + lVar5) - param_2,
                                   param_2,__ptr,0x200);
                lVar5 = (long)iVar2;
                disasm_destroy(lVar4);
                iVar1 = *(int *)(lVar3 + 0xc);
                if (0 < iVar2) {
                  local_80[0] = (long *)func_detect(__ptr,lVar5,lVar3,0);
                  if ((((local_80[0] == (long *)0x0) ||
                       (puVar8 = (undefined8 *)*local_80[0], puVar8 == (undefined8 *)0x0)) ||
                      (puVar7 = (ulong *)*puVar8, puVar7 == (ulong *)0x0)) ||
                     (*(uint *)(puVar8 + 1) == 0)) goto LAB_00143788;
                  puVar6 = puVar7 + (ulong)*(uint *)(puVar8 + 1) * 0x13;
                  goto LAB_00143740;
                }
                __fprintf_chk(*(undefined8 *)PTR_stderr_005fffd8,2,
                              "aura: disasm_run failed at 0x%016lx\n",param_2);
                free(__ptr);
              }
              uVar9 = 0xfffffff8;
              goto LAB_00143638;
            }
            break;
          }
          puVar8 = puVar8 + 7;
        } while (puVar8 != puVar10);
      }
      __fprintf_chk(*(undefined8 *)PTR_stderr_005fffd8,2,"aura: .text section not found in \'%s\'\n"
                    ,param_1);
      file_info_destroy(lVar3);
LAB_0014362c:
      uVar9 = 0xfffffffa;
    }
  }
  goto LAB_00143638;
  while (puVar7 = puVar7 + 0x13, puVar7 != puVar6) {
LAB_00143740:
    if ((*puVar7 == param_2) && (param_2 < puVar7[1])) {
      lVar4 = 0;
      puVar6 = __ptr;
      goto LAB_00143774;
    }
  }
  goto LAB_00143788;
  while( true ) {
    lVar4 = lVar4 + 1;
    puVar6 = puVar6 + 0x1c;
    if (lVar5 == lVar4) break;
LAB_00143774:
    if (puVar7[1] <= *puVar6) {
      if (lVar4 != 0) {
        lVar5 = lVar4;
      }
      break;
    }
  }
LAB_00143788:
  func_detect_destroy(local_80);
  __ptr_00 = (void *)param_id_analyze(lVar3,__ptr,lVar5,param_2);
  local_b8 = 0;
  cc_detect(local_80,__ptr,lVar5,*(undefined4 *)(lVar3 + 0xc));
  local_b8 = stack_analyze(__ptr,lVar5,param_2,*(undefined4 *)(lVar3 + 0xc),local_80,0);
  lVar4 = cfg_build(__ptr,lVar5,param_2);
  local_b0 = lVar4;
  free(__ptr);
  if (lVar4 == 0) {
    fwrite("aura: cfg_build failed\n",1,0x17,*(FILE **)PTR_stderr_005fffd8);
  }
  else {
    local_a8 = dfg_analyze(lVar4);
    if (local_a8 == 0) {
      cfg_destroy(&local_b0,0);
      fwrite("aura: dfg_analyze failed\n",1,0x19,*(FILE **)PTR_stderr_005fffd8);
    }
    else {
      if (iVar1 == 4) {
        local_a0 = ir_lift_arm64(local_b0,local_a8,&DAT_001f7f08,param_2);
      }
      else {
        local_a0 = ir_lift();
      }
      dfg_destroy(&local_a8);
      cfg_destroy(&local_b0);
      if (local_a0 != 0) {
        ir_build_ssa();
        ir_optimize(local_a0,7);
        ir_infer_types(local_a0);
        local_98 = sa_compute_postdom(local_a0);
        local_90 = loop_detect(local_a0);
        local_88 = hir_build(local_a0,local_98,local_90,lVar3,__ptr_00);
        puVar8 = (undefined8 *)PTR_stdout_005fff40;
        if (local_88 == 0) {
LAB_001439a8:
          __fprintf_chk(*puVar8,2,&DAT_001f7f80,param_1,param_2);
          ir_emit_pseudoc(local_a0,*puVar8);
        }
        else {
          local_80[0] = (long *)sr_analyze(local_a0);
          if (local_80[0] != (long *)0x0) {
            hir_apply_aggregate_types(local_88,local_a0,local_80[0]);
          }
          puVar8 = (undefined8 *)PTR_stdout_005fff40;
          __fprintf_chk(*(undefined8 *)PTR_stdout_005fff40,2,
                        "// AURA decompile (HIR pipeline)\n// file:    %s\n// func:    0x%016lx\n\n"
                        ,param_1,param_2);
          if (local_80[0] != (long *)0x0) {
            sr_emit_typedefs(local_80[0],*puVar8);
            sr_result_destroy(local_80);
          }
          hir_emit_set_stack_frame(local_b8);
          iVar1 = hir_emit_pseudoc(local_88,*puVar8,lVar3);
          if (iVar1 != 0) {
            hir_emit_set_stack_frame(0);
            hir_func_destroy(&local_88);
            goto LAB_001439a8;
          }
          hir_emit_set_stack_frame(0);
          hir_func_destroy(&local_88);
        }
        if (local_90 != 0) {
          loop_info_destroy(&local_90);
        }
        if (local_98 != 0) {
          sa_postdom_destroy(&local_98);
        }
        if (__ptr_00 != (void *)0x0) {
          param_id_result_destroy(__ptr_00);
          free(__ptr_00);
        }
        if (local_b8 != 0) {
          stack_frame_destroy(&local_b8);
        }
        ir_func_destroy(&local_a0);
        file_info_destroy(lVar3);
        uVar9 = 0;
        goto LAB_00143638;
      }
      __fprintf_chk(*(undefined8 *)PTR_stderr_005fffd8,2,"aura: ir_lift failed at 0x%016lx\n",
                    param_2);
    }
  }
LAB_00143a88:
  uVar9 = 0xfffffffe;
LAB_00143638:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return uVar9;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                   local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
}

