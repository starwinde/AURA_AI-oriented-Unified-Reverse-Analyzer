
undefined8 disasm_set_option(long *param_1,int param_2)

{
  int iVar1;
  undefined8 uVar2;
  
  if (param_1 == (long *)0x0) {
    return 0xfffffffc;
  }
  if (*param_1 == 0) {
LAB_001449cc:
    uVar2 = 0xfffffffc;
  }
  else {
    if (param_2 == 0) {
      cs_option(*param_1,1);
    }
    else {
      iVar1 = cs_option();
      *(int *)((long)param_1 + 0xc) = iVar1;
      if (iVar1 != 0) goto LAB_001449cc;
    }
    uVar2 = 0;
  }
  return uVar2;
}

