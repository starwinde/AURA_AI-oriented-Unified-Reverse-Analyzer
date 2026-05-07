
uint compare_xref_by_to(ulong *param_1,ulong *param_2)

{
  uint uVar1;
  
  if (param_1[1] < param_2[1]) {
    return 0xffffffff;
  }
  uVar1 = 1;
  if ((param_1[1] <= param_2[1]) && (uVar1 = (uint)(*param_2 < *param_1), *param_1 < *param_2)) {
    uVar1 = 0xffffffff;
  }
  return uVar1;
}

