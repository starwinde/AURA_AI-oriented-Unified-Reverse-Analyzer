
void indirect_print(long *param_1,FILE *param_2)

{
  long lVar1;
  int iVar2;
  char *pcVar3;
  long lVar4;
  uint uVar5;
  
  if (param_1 == (long *)0x0) {
    return;
  }
  if (param_2 == (FILE *)0x0) {
    param_2 = *(FILE **)PTR_stdout_005fff40;
  }
  __fprintf_chk(param_2,2,"=== Indirect Resolution (%u resolved) ===\n\n",(int)param_1[1]);
  if ((int)param_1[1] != 0) {
    lVar4 = 0;
    uVar5 = 0;
    do {
      lVar1 = *param_1 + lVar4;
      iVar2 = *(int *)(lVar1 + 0x10);
      pcVar3 = "VTABLE";
      if (((iVar2 != 1) && (pcVar3 = "JUMP_TABLE", iVar2 != 2)) && (pcVar3 = "FUNC_PTR", iVar2 != 0)
         ) {
        pcVar3 = "?";
      }
      __fprintf_chk(param_2,2,"  0x%lx -> 0x%lx  [%s]\n",*(undefined8 *)(*param_1 + lVar4),
                    *(undefined8 *)(lVar1 + 8),pcVar3);
      uVar5 = uVar5 + 1;
      lVar4 = lVar4 + 0x18;
    } while (uVar5 < *(uint *)(param_1 + 1));
    if (*(uint *)(param_1 + 1) != 0) {
      return;
    }
  }
  fwrite("  (no indirect references resolved)\n",1,0x24,param_2);
  return;
}

