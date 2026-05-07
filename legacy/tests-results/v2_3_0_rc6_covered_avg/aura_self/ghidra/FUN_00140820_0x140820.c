
void FUN_00140820(uint param_1,char *param_2,undefined4 param_3,undefined8 param_4)

{
  char *pcVar1;
  long lVar2;
  FILE *__stream;
  
  lVar2 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (param_1 < DAT_00600010) goto LAB_00140960;
  if (DAT_006005b8 == (FILE *)0x0) {
    __stream = *(FILE **)PTR_stderr_005fffd8;
    if (param_1 != 2) goto LAB_001408a0;
LAB_001409a0:
    pcVar1 = "WARN ";
  }
  else {
    __stream = DAT_006005b8;
    if (param_1 == 2) goto LAB_001409a0;
LAB_001408a0:
    if (param_1 < 3) {
      pcVar1 = "DEBUG";
      if (param_1 != 0) {
        pcVar1 = "INFO ";
      }
    }
    else {
      pcVar1 = "ERROR";
      if (param_1 != 3) {
        pcVar1 = "?????";
      }
    }
  }
  __fprintf_chk(__stream,2,"[%s] ",pcVar1);
  if (param_2 != (char *)0x0) {
    pcVar1 = strrchr(param_2,0x2f);
    if (pcVar1 != (char *)0x0) {
      param_2 = pcVar1 + 1;
    }
    __fprintf_chk(__stream,2,"%s:%d: ",param_2,param_3);
  }
  __vfprintf_chk(__stream,2,param_4);
  fputc(10,__stream);
  fflush(__stream);
LAB_00140960:
  if (lVar2 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                     lVar2 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return;
}

