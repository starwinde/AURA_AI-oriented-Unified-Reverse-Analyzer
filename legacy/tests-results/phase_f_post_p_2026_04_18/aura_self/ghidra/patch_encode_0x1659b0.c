
void patch_encode(char *param_1,undefined8 param_2,void *param_3)

{
  char cVar1;
  int iVar2;
  ulonglong uVar3;
  void *pvVar4;
  undefined8 uVar5;
  undefined4 uVar6;
  char *pcVar7;
  char *local_200;
  undefined8 local_1f8;
  ulonglong uStack_1f0;
  undefined1 auStack_1e8 [8];
  undefined4 local_1e0;
  undefined4 local_1d0;
  undefined1 local_1c0;
  undefined4 local_1b8;
  ulonglong local_180;
  undefined1 auStack_58 [16];
  long local_48;
  
  local_48 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (param_1 == (char *)0x0 || param_3 == (void *)0x0) {
    uVar5 = 0xfffffffc;
    goto LAB_00165b58;
  }
  cVar1 = *param_1;
  while (cVar1 == ' ') {
    param_1 = param_1 + 1;
    cVar1 = *param_1;
  }
  local_1f8 = 0;
  uStack_1f0 = 0;
  iVar2 = strcasecmp(param_1,"nop");
  if (iVar2 == 0) {
    uVar6 = 0x22c;
LAB_00165b8c:
    local_1f8 = CONCAT44(local_1f8._4_4_,uVar6);
    pvVar4 = memset(auStack_1e8,0,400);
    local_200 = (char *)0xf;
    local_1e0 = uVar6;
    iVar2 = ZydisEncoderEncodeInstruction(pvVar4,auStack_58,&local_200);
LAB_00165b2c:
    pcVar7 = local_200;
    if ((-1 < iVar2) && (local_200 < (char *)0x10)) {
      memcpy(param_3,auStack_58,(size_t)local_200);
      uVar5 = 0;
      *(char **)((long)param_3 + 0x10) = pcVar7;
      goto LAB_00165b58;
    }
  }
  else {
    iVar2 = strcasecmp(param_1,"ret");
    if ((iVar2 == 0) || (iVar2 = strcasecmp(param_1,"retn"), iVar2 == 0)) {
      uVar6 = 0x2fe;
      goto LAB_00165b8c;
    }
    iVar2 = strcasecmp(param_1,"int3");
    if (iVar2 == 0) {
      uVar6 = 0x166;
      goto LAB_00165b8c;
    }
    iVar2 = strncasecmp(param_1,"jmp ",4);
    if (iVar2 == 0) {
      pcVar7 = param_1 + 4;
      cVar1 = param_1[4];
      while (cVar1 == ' ') {
        pcVar7 = pcVar7 + 1;
        cVar1 = *pcVar7;
      }
      uVar3 = strtoull(pcVar7,&local_200,0);
      if (local_200 == pcVar7) goto LAB_00165c60;
      local_1f8 = 0x10000017a;
      uStack_1f0 = uVar3;
      pvVar4 = memset(auStack_1e8,0,400);
      local_1e0 = 0x17a;
LAB_00165ae8:
      local_200 = (char *)0xf;
      local_1d0 = 2;
      local_1c0 = 1;
      local_1b8 = 4;
      local_180 = uVar3;
      iVar2 = ZydisEncoderEncodeInstructionAbsolute(pvVar4,auStack_58,&local_200,param_2);
      goto LAB_00165b2c;
    }
    iVar2 = strncasecmp(param_1,"call ",5);
    if (iVar2 == 0) {
      pcVar7 = param_1 + 5;
      cVar1 = param_1[5];
      while (cVar1 == ' ') {
        pcVar7 = pcVar7 + 1;
        cVar1 = *pcVar7;
      }
      uVar3 = strtoull(pcVar7,&local_200,0);
      if (local_200 != pcVar7) {
        local_1f8 = 0x100000047;
        uStack_1f0 = uVar3;
        pvVar4 = memset(auStack_1e8,0,400);
        local_1e0 = 0x47;
        goto LAB_00165ae8;
      }
    }
  }
LAB_00165c60:
  uVar5 = 0xfffffff6;
LAB_00165b58:
  if (local_48 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(uVar5,PTR___stack_chk_guard_005ffe88,0,
                     local_48 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return;
}

