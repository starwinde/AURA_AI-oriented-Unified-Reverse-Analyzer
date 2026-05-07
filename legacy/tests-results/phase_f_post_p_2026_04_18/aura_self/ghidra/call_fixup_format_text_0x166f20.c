
void call_fixup_format_text(long *param_1,long param_2)

{
  int iVar1;
  char *pcVar2;
  long lVar3;
  long lVar4;
  
  if (param_1 == (long *)0x0 || param_2 == 0) {
    return;
  }
  __fprintf_chk(param_2,2,"Call-Fixup: %u/%u rules matched\n",(int)param_1[1],
                *(undefined4 *)((long)param_1 + 0xc));
  if ((int)param_1[1] != 0) {
    lVar4 = 0;
    do {
      lVar3 = lVar4 * 0x10;
      iVar1 = *(int *)(*param_1 + lVar3 + 8);
      pcVar2 = "RETURNS_TWICE";
      if (((iVar1 != 2) && (pcVar2 = "LONGJMP", iVar1 != 3)) && (pcVar2 = "NORETURN", iVar1 != 1)) {
        pcVar2 = "?";
      }
      lVar4 = lVar4 + 1;
      __fprintf_chk(param_2,2,&DAT_001f9c00,*(undefined8 *)(*param_1 + lVar3),pcVar2);
    } while ((uint)lVar4 < *(uint *)(param_1 + 1));
  }
  return;
}

