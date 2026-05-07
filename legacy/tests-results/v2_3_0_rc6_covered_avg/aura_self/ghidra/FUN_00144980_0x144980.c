
undefined8 FUN_00144980(long *param_1,int param_2)

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
      FUN_0018c8d4(*param_1,1);
    }
    else {
      iVar1 = FUN_0018c8d4();
      *(int *)((long)param_1 + 0xc) = iVar1;
      if (iVar1 != 0) goto LAB_001449cc;
    }
    uVar2 = 0;
  }
  return uVar2;
}

