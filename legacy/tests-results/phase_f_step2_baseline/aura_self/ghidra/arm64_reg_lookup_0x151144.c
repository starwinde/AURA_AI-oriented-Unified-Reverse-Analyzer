
undefined8 arm64_reg_lookup(char *param_1,uint *param_2,undefined4 *param_3)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  ushort **ppuVar4;
  long lVar5;
  undefined4 uVar6;
  
  cVar1 = *param_1;
  while (cVar1 == ' ') {
    param_1 = param_1 + 1;
    cVar1 = *param_1;
  }
  iVar2 = strcmp(param_1,"xzr");
  if (iVar2 == 0) {
    uVar3 = 0xffffffff;
LAB_001511f8:
    uVar6 = 4;
LAB_001511fc:
    *param_2 = uVar3;
    *param_3 = uVar6;
    return 1;
  }
  iVar2 = strcmp(param_1,"wzr");
  if (iVar2 == 0) {
    uVar3 = 0xffffffff;
    uVar6 = 3;
    goto LAB_001511fc;
  }
  if ((*param_1 == 's') && (param_1[1] == 'p')) {
    uVar3 = 0x1f;
    uVar6 = 4;
    if (param_1[2] == '\0') goto LAB_001511fc;
  }
  if (cVar1 == 'x') {
    ppuVar4 = __ctype_b_loc();
    if (((*ppuVar4)[(byte)param_1[1]] >> 0xb & 1) == 0) {
      return 0;
    }
    lVar5 = strtol(param_1 + 1,(char **)0x0,10);
    uVar3 = (uint)lVar5;
    if (uVar3 < 0x1f) goto LAB_001511f8;
    cVar1 = *param_1;
  }
  if ((cVar1 == 'w') && (ppuVar4 = __ctype_b_loc(), ((*ppuVar4)[(byte)param_1[1]] >> 0xb & 1) != 0))
  {
    lVar5 = strtol(param_1 + 1,(char **)0x0,10);
    uVar6 = 3;
    uVar3 = (uint)lVar5;
    if (uVar3 < 0x1f) goto LAB_001511fc;
  }
  return 0;
}

