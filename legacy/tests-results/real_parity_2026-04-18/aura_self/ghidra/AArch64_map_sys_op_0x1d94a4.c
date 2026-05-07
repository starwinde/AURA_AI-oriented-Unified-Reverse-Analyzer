
int AArch64_map_sys_op(undefined8 param_1)

{
  int iVar1;
  
  iVar1 = name2id(sys_op_name_map,0xd1,param_1);
  if (iVar1 == -1) {
    iVar1 = 0;
  }
  return iVar1;
}

