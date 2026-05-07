
void ir_type_to_hir_ex(ulong *param_1,uint param_2,byte param_3)

{
  undefined *puVar1;
  char *pcVar2;
  undefined4 uVar3;
  long lVar4;
  long lVar5;
  undefined8 local_a0;
  ulong uStack_98;
  ulong local_20;
  
  lVar5 = *(long *)PTR___stack_chk_guard_005ffe88;
  lVar4 = 1;
  uStack_98 = 0;
  if (0xd < param_2) {
switchD_0017e56c_caseD_4:
    local_20 = 0x10000000008;
    local_a0 = 0x745f3436746e69;
    goto LAB_0017e508;
  }
  lVar4 = (long)(char)(&switchD_0017e56c::switchdataD_0020c920)[param_2] * 4 + 0x17e570;
  switch(param_2) {
  case 0:
    local_20 = 0x10000000000;
    local_a0 = (ulong)CONCAT14(DAT_001fa45c,DAT_001fa458);
    break;
  case 1:
    pcVar2 = "int8_t";
    uVar3 = 1;
    goto LAB_0017e5c0;
  case 2:
    local_20 = 0x10000000002;
    local_a0 = 0x745f3631746e69;
    break;
  case 3:
    local_20 = 0x10000000004;
    local_a0 = 0x745f3233746e69;
    break;
  case 4:
    goto switchD_0017e56c_caseD_4;
  case 5:
    if (param_3 == 4) {
      local_a0 = DAT_001fb3b0;
      uStack_98 = (ulong)DAT_001fb3b8;
    }
    else if (param_3 < 5) {
      if (param_3 == 1) {
        local_a0 = 0x2a745f38746e69;
      }
      else {
        if (param_3 != 2) goto LAB_0017e730;
        local_a0 = DAT_001fb3a0;
        uStack_98 = (ulong)DAT_001fb3a8;
      }
    }
    else if (param_3 == 8) {
      local_a0 = DAT_001fb3c0;
      uStack_98 = (ulong)DAT_001fb3c8;
    }
    else {
LAB_0017e730:
      local_a0 = (ulong)CONCAT24(DAT_001fa454,DAT_001fa450);
    }
    local_20 = 0x100000008;
    break;
  case 6:
    local_a0 = 0x746e69;
    local_20 = 0x10000000004;
    break;
  case 7:
    uVar3 = 4;
    pcVar2 = "float";
    goto LAB_0017e57c;
  case 8:
    uVar3 = 8;
    pcVar2 = "double";
    goto LAB_0017e5c0;
  case 9:
    local_20 = 0x10000000010;
    local_a0 = s_long_double_001fa470._0_8_;
    uStack_98 = (ulong)(uint)s_long_double_001fa470._8_4_;
    break;
  case 10:
    uVar3 = 0x10;
    pcVar2 = "__m128";
    goto LAB_0017e5c0;
  case 0xb:
    uVar3 = 0x20;
    pcVar2 = "__m256";
    goto LAB_0017e5c0;
  case 0xc:
    uVar3 = 0x40;
    pcVar2 = "__m512";
LAB_0017e5c0:
    local_20 = (ulong)CONCAT24(0x100,uVar3);
    local_a0 = (ulong)CONCAT43(*(undefined4 *)(pcVar2 + 3),(int3)*(undefined4 *)pcVar2);
    break;
  case 0xd:
    pcVar2 = (char *)&DAT_001fa498;
    uVar3 = 8;
LAB_0017e57c:
    local_20 = (ulong)CONCAT24(0x100,uVar3);
    local_a0 = (ulong)*(uint6 *)pcVar2;
  }
LAB_0017e508:
  param_1[1] = uStack_98;
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
  lVar5 = lVar5 - *(long *)puVar1;
  if (lVar5 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(puVar1,0,lVar5,lVar4,0);
}

