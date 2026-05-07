
void FUN_00182d90(long param_1)

{
  uint uVar1;
  long *plVar2;
  long *plVar3;
  size_t __size;
  long lVar4;
  uint uVar5;
  
  uVar1 = DAT_00600870;
  plVar2 = DAT_00600878;
  if (DAT_00600870 == 0) {
    if (DAT_00600880 != 0) {
      DAT_00600870 = 1;
      goto LAB_00182e04;
    }
LAB_00182e54:
    __size = 0x80;
    uVar5 = 0x10;
  }
  else {
    do {
      lVar4 = *plVar2;
      plVar2 = plVar2 + 1;
      if (lVar4 == param_1) {
        return;
      }
    } while (plVar2 != DAT_00600878 + DAT_00600870);
    if (DAT_00600870 < DAT_00600880) {
      DAT_00600870 = DAT_00600870 + 1;
      goto LAB_00182e04;
    }
    if (DAT_00600880 == 0) goto LAB_00182e54;
    uVar5 = DAT_00600880 << 1;
    __size = ((ulong)DAT_00600880 & 0x7fffffff) << 4;
  }
  plVar3 = realloc(DAT_00600878,__size);
  if (plVar3 == (long *)0x0) {
    return;
  }
  DAT_00600870 = uVar1 + 1;
  plVar2 = plVar3 + uVar1;
  DAT_00600878 = plVar3;
  DAT_00600880 = uVar5;
LAB_00182e04:
  *plVar2 = param_1;
  return;
}

