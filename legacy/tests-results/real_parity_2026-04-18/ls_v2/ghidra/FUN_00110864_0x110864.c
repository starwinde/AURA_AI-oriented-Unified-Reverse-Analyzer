
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00110864(void)

{
  int iVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  int *piVar9;
  undefined8 *puVar10;
  
  piVar9 = __errno_location();
  iVar1 = *piVar9;
  puVar10 = malloc(0x38);
  uVar8 = DAT_00140f78;
  uVar7 = uRam0000000000140f70;
  uVar6 = _DAT_00140f68;
  uVar5 = uRam0000000000140f60;
  uVar4 = _DAT_00140f58;
  uVar3 = uRam0000000000140f50;
  uVar2 = _DAT_00140f48;
  if (puVar10 != (undefined8 *)0x0) {
    *piVar9 = iVar1;
    puVar10[6] = uVar8;
    puVar10[1] = uVar3;
    *puVar10 = uVar2;
    puVar10[3] = uVar5;
    puVar10[2] = uVar4;
    puVar10[5] = uVar7;
    puVar10[4] = uVar6;
    return;
  }
                    /* WARNING: Subroutine does not return */
  FUN_0010d454();
}

