
void FUN_00107c20(undefined8 *param_1,ulong param_2,undefined8 *param_3,code *param_4)

{
  ulong uVar1;
  int iVar2;
  ulong uVar3;
  long lVar4;
  long lVar5;
  undefined8 *puVar6;
  undefined8 *puVar7;
  ulong uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  ulong uVar11;
  ulong uVar12;
  ulong local_8;
  
  uVar12 = param_2 >> 1;
  puVar6 = param_1 + uVar12;
  if (param_2 - uVar12 < 3) {
    if (param_2 - uVar12 == 2) {
      uVar10 = param_1[uVar12];
      uVar9 = puVar6[1];
      iVar2 = (*param_4)(uVar10,uVar9);
      if (0 < iVar2) {
        param_1[uVar12] = uVar9;
        puVar6[1] = uVar10;
      }
    }
  }
  else {
    FUN_00107c20(puVar6);
  }
  if (param_2 == 3) {
    uVar10 = *param_1;
    *param_3 = uVar10;
    goto LAB_00107c78;
  }
  uVar3 = param_2 >> 2;
  uVar11 = uVar12 - uVar3;
  puVar6 = param_1 + uVar3;
  if (uVar11 < 3) {
    if (uVar11 == 2) {
      uVar10 = param_1[uVar3];
      uVar9 = puVar6[1];
      iVar2 = (*param_4)(uVar10,uVar9);
      if (0 < iVar2) {
        param_1[uVar3] = uVar9;
        puVar6[1] = uVar10;
      }
    }
  }
  else {
    FUN_00107c20(puVar6,uVar11,param_3,param_4);
  }
  if (uVar3 < 3) {
    uVar9 = *param_1;
    uVar10 = uVar9;
    if (uVar3 == 2) {
      uVar10 = param_1[1];
      iVar2 = (*param_4)(uVar9,uVar10);
      if (iVar2 < 1) goto LAB_00107e58;
      *param_1 = uVar10;
      param_1[1] = uVar9;
    }
  }
  else {
    FUN_00107c20(param_1,uVar3,param_3,param_4);
LAB_00107e58:
    uVar10 = *param_1;
  }
  uVar11 = 0;
  uVar9 = param_1[uVar3];
  puVar6 = param_3;
  uVar8 = uVar3;
  while( true ) {
    iVar2 = (*param_4)(uVar10,uVar9);
    puVar7 = puVar6;
    while (puVar6 = puVar7 + 1, 0 < iVar2) {
      uVar1 = uVar8 + 1;
      *puVar7 = uVar9;
      uVar8 = uVar11;
      local_8 = uVar3;
      if (uVar12 == uVar1) goto LAB_00107df8;
      uVar9 = param_1[uVar1];
      iVar2 = (*param_4)(uVar10,uVar9);
      uVar8 = uVar1;
      puVar7 = puVar6;
    }
    uVar11 = uVar11 + 1;
    *puVar7 = uVar10;
    local_8 = uVar12;
    if (uVar3 == uVar11) break;
    uVar10 = param_1[uVar11];
  }
LAB_00107df8:
  memcpy(puVar6,param_1 + uVar8,(local_8 - uVar8) * 8);
  uVar10 = *param_3;
LAB_00107c78:
  uVar9 = param_1[uVar12];
  lVar5 = 0;
  iVar2 = (*param_4)(uVar10,uVar9);
  lVar4 = 1;
  uVar11 = 0;
  uVar3 = uVar12;
  if (iVar2 < 1) goto LAB_00107cd0;
  do {
    uVar3 = uVar3 + 1;
    param_1[lVar5] = uVar9;
    if (param_2 == uVar3) {
      memcpy(param_1 + lVar4,param_3 + uVar11,(uVar12 - uVar11) * 8);
      return;
    }
    uVar9 = param_1[uVar3];
    lVar5 = lVar4;
    while( true ) {
      iVar2 = (*param_4)(uVar10,uVar9);
      lVar4 = lVar5 + 1;
      if (0 < iVar2) break;
LAB_00107cd0:
      uVar11 = uVar11 + 1;
      param_1[lVar5] = uVar10;
      if (uVar12 == uVar11) {
        return;
      }
      uVar10 = param_3[uVar11];
      lVar5 = lVar4;
    }
  } while( true );
}

