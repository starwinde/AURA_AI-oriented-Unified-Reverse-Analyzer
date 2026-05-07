
ssize_t FUN_00103144(int param_1,void *param_2,ulong param_3)

{
  int iVar1;
  bool bVar2;
  bool bVar3;
  ssize_t sVar4;
  int *piVar5;
  
  do {
    sVar4 = read(param_1,param_2,param_3);
    if (-1 < sVar4) {
      return sVar4;
    }
    piVar5 = __errno_location();
    iVar1 = *piVar5;
  } while ((iVar1 == 4) ||
          (bVar2 = 0x7fefffff < param_3, bVar3 = param_3 != 0x7ff00000, param_3 = 0x7ff00000,
          (iVar1 == 0x16 && bVar2) && (iVar1 != 0x16 || bVar3)));
  return sVar4;
}

