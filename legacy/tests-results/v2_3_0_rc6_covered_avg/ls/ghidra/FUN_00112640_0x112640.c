
undefined * FUN_00112640(uint param_1,undefined8 param_2,undefined4 *param_3)

{
  size_t __size;
  uint uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined *puVar6;
  int *piVar7;
  undefined8 *puVar8;
  ulong uVar9;
  long lVar10;
  undefined *puVar11;
  long lVar12;
  ulong uVar13;
  ulong uVar14;
  long local_70;
  long local_68;
  
  local_68 = *(long *)PTR___stack_chk_guard_0013ffd0;
  piVar7 = __errno_location();
  iVar4 = *piVar7;
  puVar8 = (undefined8 *)PTR_DAT_00140280;
  if (DAT_00140278 <= (int)param_1) {
    lVar12 = (long)DAT_00140278;
    lVar10 = (long)(int)((param_1 - DAT_00140278) + 1);
    local_70 = lVar12;
    if ((undefined8 *)PTR_DAT_00140280 == &DAT_00140288) {
      puVar8 = (undefined8 *)FUN_0010f680(0,&local_70,lVar10,0x7fffffff);
      puVar11 = PTR_DAT_00140290;
      PTR_DAT_00140280 = (undefined *)puVar8;
      *puVar8 = DAT_00140288;
      puVar8[1] = puVar11;
    }
    else {
      puVar8 = (undefined8 *)FUN_0010f680(PTR_DAT_00140280,&local_70,lVar10,0x7fffffff);
      PTR_DAT_00140280 = (undefined *)puVar8;
    }
    memset(puVar8 + lVar12 * 2,0,(local_70 - lVar12) * 0x10);
    DAT_00140278 = (int)local_70;
  }
  uVar13 = -(ulong)(param_1 >> 0x1f) & 0xfffffff000000000 | (ulong)param_1 << 4;
  uVar1 = param_3[1];
  uVar14 = *(ulong *)((long)puVar8 + uVar13);
  puVar11 = *(undefined **)((long)puVar8 + uVar13 + 8);
  uVar9 = FUN_00111270(puVar11,uVar14,param_2,*param_3,uVar1 | 1,param_3 + 2,
                       *(undefined8 *)(param_3 + 10),*(undefined8 *)(param_3 + 0xc));
  if (uVar14 <= uVar9) {
    __size = uVar9 + 1;
    *(size_t *)((long)puVar8 + uVar13) = __size;
    if (puVar11 != &DAT_00141450) {
      free(puVar11);
    }
    puVar11 = malloc(__size);
    if (puVar11 == (undefined *)0x0) {
                    /* WARNING: Subroutine does not return */
      FUN_0010d454();
    }
    uVar2 = *(undefined8 *)(param_3 + 10);
    uVar3 = *(undefined8 *)(param_3 + 0xc);
    uVar5 = *param_3;
    *(undefined **)((long)puVar8 + uVar13 + 8) = puVar11;
    FUN_00111270(puVar11,__size,param_2,uVar5,uVar1 | 1,param_3 + 2,uVar2,uVar3);
  }
  puVar6 = PTR___stack_chk_guard_0013ffd0;
  *piVar7 = iVar4;
  lVar10 = local_68 - *(long *)puVar6;
  if (lVar10 == 0) {
    return puVar11;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(puVar6,0,lVar10);
}

