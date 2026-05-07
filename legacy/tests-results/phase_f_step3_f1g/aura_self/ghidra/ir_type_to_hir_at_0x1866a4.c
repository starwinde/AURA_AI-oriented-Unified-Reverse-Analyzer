
void ir_type_to_hir_at(ulong *param_1,uint param_2)

{
  undefined *puVar1;
  char *pcVar2;
  undefined4 uVar3;
  long lVar4;
  undefined8 local_a0;
  ulong local_20;
  
  lVar4 = *(long *)PTR___stack_chk_guard_005ffe88;
  uVar3 = 0;
  if (param_2 == 3) {
    local_20 = 0x10000000004;
    local_a0 = 0x745f3233746e69;
    goto LAB_00186720;
  }
  if (param_2 < 4) {
    if (param_2 != 1) {
      if (param_2 == 2) {
        local_20 = 0x10000000002;
        local_a0 = 0x745f3631746e69;
      }
      else {
        local_20 = 0x10000000000;
        local_a0 = (ulong)CONCAT14(DAT_001f887c,DAT_001f8878);
      }
      goto LAB_00186720;
    }
    pcVar2 = "int8_t";
  }
  else {
    if (param_2 == 7) {
      local_20 = 0x10000000004;
      local_a0._0_6_ = CONCAT24(s_float_001f8880._4_2_,s_float_001f8880._0_4_);
      local_a0 = (ulong)(uint6)local_a0;
      goto LAB_00186720;
    }
    if (param_2 != 8) {
      if (param_2 == 5) {
        local_20 = 0x100000008;
        local_a0._0_6_ = CONCAT24(DAT_001f8874,DAT_001f8870);
        local_a0 = (ulong)(uint6)local_a0;
        uVar3 = DAT_001f8870;
      }
      else {
        local_20 = 0x10000000008;
        local_a0 = 0x745f3436746e69;
      }
      goto LAB_00186720;
    }
    pcVar2 = "double";
  }
  local_20 = (ulong)CONCAT24(0x100,param_2);
  local_a0 = (ulong)CONCAT43(*(undefined4 *)(pcVar2 + 3),(int3)*(undefined4 *)pcVar2);
  uVar3 = *(undefined4 *)pcVar2;
LAB_00186720:
  param_1[1] = 0;
  *param_1 = local_a0;
  param_1[3] = 0;
  param_1[2] = 0;
  param_1[5] = 0;
  param_1[4] = 0;
  param_1[7] = 0;
  param_1[6] = 0;
  param_1[0x10] = local_20;
  puVar1 = PTR___stack_chk_guard_005ffe88;
  param_1[9] = 0;
  param_1[8] = 0;
  param_1[0xb] = 0;
  param_1[10] = 0;
  param_1[0xd] = 0;
  param_1[0xc] = 0;
  param_1[0xf] = 0;
  param_1[0xe] = 0;
  lVar4 = lVar4 - *(long *)puVar1;
  if (lVar4 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(puVar1,0,lVar4,uVar3);
}

