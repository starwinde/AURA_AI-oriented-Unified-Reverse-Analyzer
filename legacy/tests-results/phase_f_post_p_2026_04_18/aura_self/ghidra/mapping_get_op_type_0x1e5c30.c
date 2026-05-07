
undefined1 mapping_get_op_type(long param_1,ulong param_2,long param_3)

{
  return *(undefined1 *)
          (param_3 + ((param_2 & 0xffffffff) * 2 + (param_2 & 0xffffffff)) * 4 +
          (ulong)*(uint *)(param_1 + 8) * 0xc0);
}

