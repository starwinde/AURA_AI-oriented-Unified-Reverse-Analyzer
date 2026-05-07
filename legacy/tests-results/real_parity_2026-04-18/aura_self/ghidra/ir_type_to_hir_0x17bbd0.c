
void ir_type_to_hir(ulong *param_1,undefined4 param_2)

{
  undefined *puVar1;
  char *pcVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  long lVar5;
  undefined8 local_a0;
  ulong uStack_98;
  ulong local_20;
  
  lVar5 = *(long *)PTR___stack_chk_guard_005ffe88;
  uVar4 = 0;
  uStack_98 = 0;
  switch(param_2) {
  case 0:
    local_20 = 0x10000000000;
    local_a0 = (ulong)CONCAT14(DAT_001f7ca4,DAT_001f7ca0);
    break;
  case 1:
    pcVar2 = "int8_t";
    uVar3 = 1;
    goto LAB_0017bcf0;
  case 2:
    local_20 = 0x10000000002;
    local_a0 = 0x745f3631746e69;
    break;
  case 3:
    local_20 = 0x10000000004;
    local_a0 = 0x745f3233746e69;
    break;
  default:
    local_20 = 0x10000000008;
    local_a0 = 0x745f3436746e69;
    break;
  case 5:
    local_20 = 0x100000008;
    local_a0 = (ulong)CONCAT24(DAT_001f7c9c,DAT_001f7c98);
    uVar4 = DAT_001f7c98;
    break;
  case 6:
    local_a0 = 0x746e69;
    local_20 = 0x10000000004;
    break;
  case 7:
    uVar3 = 4;
    pcVar2 = "float";
    goto LAB_0017bcac;
  case 8:
    uVar3 = 8;
    pcVar2 = "double";
    goto LAB_0017bcf0;
  case 9:
    local_20 = 0x10000000010;
    local_a0 = s_long_double_001f7cb8._0_8_;
    uStack_98 = (ulong)(uint)s_long_double_001f7cb8._8_4_;
    break;
  case 10:
    uVar3 = 0x10;
    pcVar2 = "__m128";
    goto LAB_0017bcf0;
  case 0xb:
    uVar3 = 0x20;
    pcVar2 = "__m256";
    goto LAB_0017bcf0;
  case 0xc:
    uVar3 = 0x40;
    pcVar2 = "__m512";
LAB_0017bcf0:
    local_20 = (ulong)CONCAT24(0x100,uVar3);
    local_a0 = (ulong)CONCAT43(*(undefined4 *)(pcVar2 + 3),(int3)*(undefined4 *)pcVar2);
    break;
  case 0xd:
    pcVar2 = (char *)&DAT_001f7ce0;
    uVar3 = 8;
LAB_0017bcac:
    local_20 = (ulong)CONCAT24(0x100,uVar3);
    local_a0 = (ulong)*(uint6 *)pcVar2;
  }
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
  __stack_chk_fail(puVar1,0,lVar5,uVar4);
}

