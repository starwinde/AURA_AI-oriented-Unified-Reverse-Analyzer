
char * indirect_type_name(int param_1)

{
  char *pcVar1;
  
  if (param_1 == 1) {
    return "VTABLE";
  }
  if (param_1 != 2) {
    pcVar1 = "FUNC_PTR";
    if (param_1 != 0) {
      pcVar1 = "?";
    }
    return pcVar1;
  }
  return "JUMP_TABLE";
}

