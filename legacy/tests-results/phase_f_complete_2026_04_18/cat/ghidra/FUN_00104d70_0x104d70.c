
undefined * FUN_00104d70(long param_1,undefined4 *param_2)

{
  undefined *__ptr;
  ulong uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  int iVar4;
  undefined4 uVar5;
  int *piVar6;
  ulong uVar7;
  undefined *puVar8;
  long lVar9;
  size_t __size;
  long lVar10;
  ulong uVar11;
  undefined **ppuVar12;
  size_t *psVar13;
  size_t *unaff_x28;
  
  ppuVar12 = (undefined **)&DAT_00120000;
  piVar6 = __errno_location();
  puVar8 = PTR_DAT_001200b0;
  iVar4 = *piVar6;
  psVar13 = (size_t *)PTR_DAT_001200b0;
  if (0 < (int)DAT_00120028) goto LAB_00104e78;
  lVar10 = (long)(int)DAT_00120028;
  uVar11 = ((long)((ulong)DAT_00120028 << 0x20) >> 0x21) + lVar10;
  __size = uVar11 * 0x10;
  __ptr = PTR_DAT_001200b0;
  if ((undefined8 *)PTR_DAT_001200b0 == &DAT_001200b8) {
    __ptr = (undefined *)0x0;
  }
  if ((long)__size < 0x80) {
    uVar11 = 8;
  }
  lVar9 = uVar11 - lVar10;
  if ((long)__size < 0x80) {
    __size = 0x80;
  }
  if (lVar9 < (int)(1 - DAT_00120028)) {
    uVar11 = (int)(1 - DAT_00120028) + lVar10;
    __size = uVar11 * 0x10;
    unaff_x28 = realloc(__ptr,__size);
    if (unaff_x28 == (size_t *)0x0) {
      if (__ptr == (undefined *)0x0 || __size != 0) goto LAB_00104f44;
      lVar9 = uVar11 - lVar10;
      __size = 0;
    }
    else {
      lVar9 = uVar11 - lVar10;
    }
  }
  else {
    unaff_x28 = realloc(__ptr,__size);
    if (unaff_x28 == (size_t *)0x0) goto LAB_00104f44;
  }
  ppuVar12 = &PTR_DAT_001200a0;
  psVar13 = unaff_x28;
  PTR_DAT_001200b0 = (undefined *)unaff_x28;
  if ((undefined8 *)puVar8 == &DAT_001200b8) goto LAB_00104f48;
  while( true ) {
    uVar1 = lVar10 * 0x10;
    if ((ulong)(lVar10 * 0x10) < __size) {
      uVar1 = __size;
    }
    __memset_chk(psVar13 + lVar10 * 2,0,lVar9 << 4,uVar1 + lVar10 * -0x10);
    DAT_00120028 = (uint)uVar11;
    unaff_x28 = psVar13;
LAB_00104e78:
    uVar1 = *psVar13;
    puVar8 = (undefined *)psVar13[1];
    ppuVar12 = (undefined **)(param_2 + 2);
    uVar11 = (ulong)(param_2[1] | 1);
    lVar9 = param_1;
    uVar7 = FUN_001038f0(puVar8,uVar1,param_1,*param_2,uVar11,ppuVar12,*(undefined8 *)(param_2 + 10)
                         ,*(undefined8 *)(param_2 + 0xc));
    if (uVar7 < uVar1) goto LAB_00104efc;
    __size = uVar7 + 1;
    *psVar13 = __size;
    if (puVar8 != &DAT_001200e0) {
      free(puVar8);
    }
    puVar8 = malloc(__size);
    lVar10 = 0;
    if (puVar8 != (undefined *)0x0) break;
LAB_00104f44:
    FUN_001031c4();
    psVar13 = unaff_x28;
LAB_00104f48:
    puVar8 = ppuVar12[4];
    *psVar13 = (size_t)ppuVar12[3];
    psVar13[1] = (size_t)puVar8;
  }
  uVar2 = *(undefined8 *)(param_2 + 10);
  uVar3 = *(undefined8 *)(param_2 + 0xc);
  uVar5 = *param_2;
  psVar13[1] = (size_t)puVar8;
  FUN_001038f0(puVar8,__size,param_1,uVar5,uVar11,ppuVar12,uVar2,uVar3);
LAB_00104efc:
  *piVar6 = iVar4;
  return puVar8;
}

