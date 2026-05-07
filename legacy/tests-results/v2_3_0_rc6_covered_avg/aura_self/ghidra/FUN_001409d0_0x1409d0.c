
undefined8 FUN_001409d0(long *param_1)

{
  long lVar1;
  ulong uVar2;
  long lVar3;
  bool bVar4;
  int iVar5;
  long *plVar6;
  undefined8 uVar7;
  char *__s2;
  ulong uVar8;
  long lVar9;
  long *plVar10;
  ulong uVar11;
  
  plVar10 = DAT_006005c8;
  lVar3 = DAT_006005c0;
  if (param_1 == (long *)0x0) {
    return 0xfffffffc;
  }
  if (*param_1 == 0) {
    uVar7 = 0xfffffffc;
  }
  else {
    __s2 = (char *)param_1[1];
    if (((__s2 == (char *)0x0) || (param_1[5] == 0)) || (param_1[6] == 0)) {
      return 0xfffffffc;
    }
    if (DAT_006005c0 == 0) {
      uVar11 = 1;
      uVar8 = 8;
      if (DAT_006005d0 != 0) goto LAB_00140ac4;
    }
    else {
      lVar1 = 0;
      do {
        lVar9 = lVar1;
        lVar1 = lVar9 + 1;
        iVar5 = strcmp(*(char **)(plVar10[lVar9] + 8),__s2);
        if (iVar5 == 0) {
          return 0xffffffff;
        }
      } while (lVar1 != lVar3);
      uVar11 = lVar9 + 2;
      if (uVar11 <= DAT_006005d0) {
        plVar10 = plVar10 + lVar1;
        goto LAB_00140ac4;
      }
      uVar8 = DAT_006005d0;
      if (DAT_006005d0 == 0) {
        uVar8 = 8;
      }
    }
    while( true ) {
      uVar2 = uVar8 + (uVar8 >> 1);
      if (uVar11 <= uVar8) break;
      bVar4 = uVar8 < uVar2;
      uVar8 = uVar8 + 1;
      if (bVar4) {
        uVar8 = uVar2;
      }
    }
    plVar6 = realloc(plVar10,uVar8 << 3);
    if (plVar6 != (long *)0x0) {
      plVar10 = plVar6 + lVar3;
      DAT_006005c8 = plVar6;
      DAT_006005d0 = uVar8;
LAB_00140ac4:
      DAT_006005c0 = uVar11;
      *plVar10 = (long)param_1;
      return 0;
    }
    uVar7 = 0xfffffffe;
  }
  return uVar7;
}

