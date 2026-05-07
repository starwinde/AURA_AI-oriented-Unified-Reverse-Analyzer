
void emit_cond(FILE *param_1,long param_2)

{
  if ((param_2 != 0) && (*(int *)(param_2 + 0x48) != 0)) {
    if (*(int *)(param_2 + 0x18) != -1) {
      __fprintf_chk(param_1,2,&DAT_001fa488,*(int *)(param_2 + 0x18));
      return;
    }
    fwrite("__undef",1,7,param_1);
    return;
  }
  fwrite(&DAT_001fa3e0,1,4,param_1);
  return;
}

