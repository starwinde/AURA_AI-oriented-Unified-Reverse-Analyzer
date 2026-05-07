
bool FUN_00155f30(long param_1)

{
  int iVar1;
  int iVar2;
  
  if (param_1 != 0) {
    iVar1 = FUN_00155db0();
    iVar2 = FUN_00155c30(param_1);
    return 0 < iVar1 + iVar2;
  }
  return false;
}

