
ulong type_wider(ulong param_1,uint param_2)

{
  uint uVar1;
  ulong uVar2;
  int iVar3;
  int iVar4;
  
  uVar1 = (uint)param_1;
  if (uVar1 == 0 || uVar1 == 6) {
LAB_001575a4:
    return (ulong)param_2;
  }
  uVar2 = param_1;
  if ((param_2 == 0 || param_2 == 6) || (uVar2 = 5, uVar1 == 5 || param_2 == 5)) {
    return uVar2;
  }
  if (uVar1 - 10 < 4) {
    if (3 < param_2 - 10) {
      return param_1 & 0xffffffff;
    }
LAB_001575b8:
    if (uVar1 < 0xd) {
      iVar4 = 8;
      iVar3 = *(int *)(&CSWTCH_2 + (param_1 & 0xffffffff) * 4);
      if (0xc < param_2) goto LAB_001575d8;
    }
    else {
      if (0xc < param_2) {
LAB_00157618:
        return param_1 & 0xffffffff;
      }
      iVar3 = 8;
    }
  }
  else {
    if (param_2 - 10 < 4) goto LAB_001575a4;
    if (2 < uVar1 - 7) {
      if (param_2 - 7 < 3) {
        return (ulong)param_2;
      }
      goto LAB_001575b8;
    }
    if (2 < param_2 - 7) goto LAB_00157618;
    iVar3 = *(int *)(&CSWTCH_2 + (param_1 & 0xffffffff) * 4);
  }
  iVar4 = *(int *)(&CSWTCH_2 + (ulong)param_2 * 4);
LAB_001575d8:
  if (iVar3 < iVar4) {
    uVar1 = param_2;
  }
  return (ulong)uVar1;
}

