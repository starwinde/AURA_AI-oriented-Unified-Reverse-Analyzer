
void AArch64SysReg_genericRegisterString(uint param_1,undefined8 param_2)

{
  char *pcVar1;
  ulong uVar2;
  ulong uVar3;
  char local_10d;
  char local_10c [4];
  char acStack_108 [32];
  char acStack_e8 [32];
  char acStack_c8 [32];
  char acStack_a8 [19];
  char local_95;
  char local_94 [12];
  char acStack_88 [20];
  char local_74 [12];
  long local_68;
  
  local_74[0] = ((byte)(param_1 >> 0xe) & 3) + 0x30;
  uVar2 = (ulong)(param_1 >> 3) & 0xf;
  uVar3 = (ulong)(param_1 >> 7) & 0xf;
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  local_74[1] = 0;
  strncpy(acStack_108,local_74,0x16);
  local_74[0] = ((byte)(param_1 >> 0xb) & 7) + 0x30;
  pcVar1 = local_94;
  local_74[1] = 0;
  strncpy(acStack_e8,local_74,0x16);
  local_94[0] = ((byte)param_1 & 7) + 0x30;
  local_94[1] = 0;
  strncpy(acStack_88,pcVar1,0x16);
  local_94[1] = 0;
  if ((uint)uVar3 == 0) {
    local_94[0] = '0';
  }
  else {
    local_94[0] = (char)uVar3 + (char)(uVar3 / 10) * -10 + '0';
    if (9 < (uint)uVar3) {
      pcVar1 = &local_95;
      local_95 = '1';
    }
  }
  strncpy(acStack_c8,pcVar1,0x16);
  local_10c[1] = 0;
  if ((uint)uVar2 == 0) {
    local_10c[0] = '0';
  }
  else {
    local_10c[0] = (char)uVar2 + (char)(uVar2 / 10) * -10 + '0';
    if (9 < (uint)uVar2) {
      pcVar1 = &local_10d;
      local_10d = '1';
      goto LAB_001e7c74;
    }
  }
  pcVar1 = local_10c;
LAB_001e7c74:
  strncpy(acStack_a8,pcVar1,0x16);
  cs_snprintf(param_2,0x80,"s%s_%s_c%s_c%s_%s",acStack_108,acStack_e8,acStack_c8,acStack_a8,
              acStack_88);
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                     local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return;
}

