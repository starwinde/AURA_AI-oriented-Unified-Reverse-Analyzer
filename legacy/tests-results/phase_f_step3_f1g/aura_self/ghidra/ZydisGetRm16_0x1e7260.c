
long ZydisGetRm16(int param_1,int param_2)

{
  char local_1;
  
  local_1 = '\0';
  while( true ) {
    if ('\a' < local_1) {
      return 0xffffffff;
    }
    if ((param_1 == *(int *)(modrm16_lookup_52 + (long)(int)local_1 * 8)) &&
       (param_2 == *(int *)(modrm16_lookup_52 + (long)(int)local_1 * 8 + 4))) break;
    local_1 = local_1 + '\x01';
  }
  return (long)local_1;
}

