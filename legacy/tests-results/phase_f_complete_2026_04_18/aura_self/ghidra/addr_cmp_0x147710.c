
int addr_cmp(ulong *param_1,ulong *param_2)

{
  return (uint)(*param_2 < *param_1) - (uint)(*param_1 < *param_2);
}

