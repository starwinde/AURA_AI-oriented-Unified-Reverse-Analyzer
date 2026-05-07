
long FUN_001e8dd0(int param_1,int param_2)

{
  char local_1;
  
  local_1 = '\0';
  while( true ) {
    if ('\a' < local_1) {
      return 0xffffffff;
    }
    if ((param_1 == *(int *)(&DAT_005710c0 + (long)(int)local_1 * 8)) &&
       (param_2 == *(int *)(&DAT_005710c4 + (long)(int)local_1 * 8))) break;
    local_1 = local_1 + '\x01';
  }
  return (long)local_1;
}

