
void ir_optimize(long param_1,uint param_2)

{
  undefined4 uVar1;
  ulong uVar2;
  long local_88;
  undefined *local_80;
  undefined *puStack_78;
  undefined8 local_70;
  undefined *local_68;
  undefined *puStack_60;
  undefined8 local_58;
  undefined *local_50;
  undefined *puStack_48;
  undefined8 local_40;
  long local_38;
  
  local_38 = *(long *)PTR___stack_chk_guard_005ffe88;
  uVar2 = 0;
  if (param_1 != 0 && param_2 != 0) {
    local_88 = pass_manager_create(0);
    if (local_88 == 0) {
      uVar2 = 0xfffffffe;
    }
    else {
      pass_manager_set_max_iters(local_88,10);
      if ((param_2 & 1) != 0) {
        local_68 = PTR_DAT_00600038;
        puStack_60 = PTR_pm_wrap_const_propagate_00600040;
        local_58 = DAT_00600048;
        pass_manager_add(local_88);
        local_50 = PTR_s_const_fold_00600050;
        puStack_48 = PTR_pm_wrap_const_fold_00600058;
        local_40 = DAT_00600060;
        pass_manager_add(local_88);
      }
      if ((param_2 >> 1 & 1) != 0) {
        local_50 = PTR_s_copy_prop_00600068;
        puStack_48 = PTR_pm_wrap_copy_prop_00600070;
        local_40 = DAT_00600078;
        pass_manager_add(local_88);
        pass_manager_add(local_88,PTR_ir_pass_copy_prop_enhanced_005fff80);
      }
      if ((param_2 & 7) != 0) {
        pass_manager_add(local_88,PTR_ir_pass_expr_simplify_005fff00);
        pass_manager_add(local_88,PTR_ir_pass_expr_reassoc_005ffe48);
        pass_manager_add(local_88,PTR_ir_pass_cse_005ffef8);
        pass_manager_add(local_88,PTR_ir_pass_cond_simplify_005fff70);
        if ((param_2 >> 2 & 1) != 0) {
          local_80 = PTR_s_dead_code_00600080;
          puStack_78 = PTR_pm_wrap_dead_code_eliminate_00600088;
          local_70 = DAT_00600090;
          pass_manager_add(local_88);
          local_68 = PTR_DAT_00600098;
          puStack_60 = PTR_pm_wrap_dce_006000a0;
          local_58 = DAT_006000a8;
          pass_manager_add(local_88);
          local_50 = PTR_s_dead_store_006000b0;
          puStack_48 = PTR_dead_store_pass_run_006000b8;
          local_40 = DAT_006000c0;
          pass_manager_add(local_88);
        }
        pass_manager_add(local_88,PTR_ir_pass_licm_005ffff0);
        pass_manager_add(local_88,PTR_ir_pass_strength_reduce_005ffe58);
      }
      uVar1 = pass_manager_run(local_88,param_1);
      local_50 = (undefined *)CONCAT44(local_50._4_4_,uVar1);
      pass_manager_destroy(&local_88);
      uVar2 = (ulong)local_50 & 0xffffffff;
      if ((int)local_50 == 0) {
        (**(code **)(PTR_ir_pass_reg_coalesce_005ffe70 + 8))(param_1,&local_50);
        uVar2 = (ulong)local_50 & 0xffffffff;
        if ((int)local_50 == 0) {
          (**(code **)(PTR_ir_pass_phi_elimination_005fffa0 + 8))(param_1,&local_50);
          uVar2 = (ulong)local_50 & 0xffffffff;
          if ((int)local_50 == 0) {
            tail_call_pass_run(param_1,&local_50);
            uVar2 = (ulong)local_50 & 0xffffffff;
          }
        }
      }
    }
  }
  if (local_38 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(uVar2,PTR___stack_chk_guard_005ffe88,0,
                     local_38 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return;
}

