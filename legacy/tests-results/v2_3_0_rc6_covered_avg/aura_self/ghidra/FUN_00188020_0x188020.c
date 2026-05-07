
int FUN_00188020(undefined8 param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = FUN_001582e4();
  if (iVar1 != 0) {
    iVar3 = 0;
    do {
      iVar2 = FUN_00158494(param_1,iVar3);
      if (iVar2 == param_2) {
        return iVar3;
      }
      iVar3 = iVar3 + 1;
    } while (iVar1 != iVar3);
  }
  return -1;
}

