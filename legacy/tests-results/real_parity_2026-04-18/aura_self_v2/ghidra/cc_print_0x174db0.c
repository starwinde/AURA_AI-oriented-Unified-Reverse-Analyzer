
void cc_print(uint *param_1,FILE *param_2)

{
  undefined *puVar1;
  uint uVar2;
  char *pcVar3;
  
  if (param_1 == (uint *)0x0) {
    return;
  }
  if (param_2 == (FILE *)0x0) {
    param_2 = *(FILE **)PTR_stdout_005fff40;
    uVar2 = *param_1;
  }
  else {
    uVar2 = *param_1;
  }
  if (uVar2 == 4) {
    pcVar3 = "SysV AMD64";
  }
  else if (uVar2 < 4) {
    if (uVar2 == 2) {
      pcVar3 = "stdcall";
    }
    else if (uVar2 == 3) {
      pcVar3 = "fastcall";
    }
    else {
      pcVar3 = "unknown";
      if (uVar2 == 1) {
        pcVar3 = "cdecl";
      }
    }
  }
  else if (uVar2 == 6) {
    pcVar3 = "ARM EABI";
  }
  else if (uVar2 == 7) {
    pcVar3 = "AArch64";
  }
  else {
    pcVar3 = "unknown";
    if (uVar2 == 5) {
      pcVar3 = "MS x64";
    }
  }
  __fprintf_chk(param_2,2,"Calling Convention: %s\n",pcVar3);
  __fprintf_chk(param_2,2,"  Estimated args:   %u\n",param_1[1]);
  puVar1 = &DAT_001f8cd0;
  if (param_1[2] != 0) {
    puVar1 = &DAT_001f8cc8;
  }
  __fprintf_chk(param_2,2,"  Returns value:    %s\n",puVar1);
  puVar1 = &DAT_001f8cd0;
  if (param_1[4] != 0) {
    puVar1 = &DAT_001f8cc8;
  }
  __fprintf_chk(param_2,2,"  Callee cleanup:   %s",puVar1);
  if (param_1[4] != 0) {
    __fprintf_chk(param_2,2," (%u bytes)",(short)param_1[5]);
  }
  fputc(10,param_2);
  __fprintf_chk(param_2,2,"  Arg regs used:    0x%04x\n",(short)param_1[3]);
  return;
}

