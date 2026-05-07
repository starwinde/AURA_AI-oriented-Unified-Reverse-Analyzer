
undefined1 * FUN_0010d770(byte *param_1,char param_2)

{
  ulong uVar1;
  ulong uVar2;
  size_t sVar3;
  undefined1 *puVar4;
  ulong uVar5;
  uint uVar6;
  long lVar7;
  ulong uVar8;
  undefined1 *puVar9;
  
  sVar3 = strlen((char *)param_1);
  puVar4 = (undefined1 *)reallocarray(0,3,sVar3 + 1);
  if (puVar4 == (undefined1 *)0x0) {
                    /* WARNING: Subroutine does not return */
    FUN_0010d454();
  }
  uVar6 = (uint)*param_1;
  puVar9 = puVar4;
  if (*param_1 != 0) {
    uVar2 = (sVar3 + 1) * 3;
    uVar8 = uVar2;
    do {
      while( true ) {
        param_1 = param_1 + 1;
        uVar1 = uVar2;
        if (uVar2 < uVar8) {
          uVar1 = uVar8;
        }
        if (uVar6 != 0x2f || param_2 == '\0') break;
        uVar5 = (uVar1 - uVar8) + 1;
        *puVar9 = 0x2f;
        if (uVar5 < uVar1) {
          uVar5 = uVar1;
        }
        lVar7 = uVar5 - uVar1;
LAB_0010d800:
        uVar8 = lVar7 + (uVar8 - 1);
        puVar9 = puVar9 + 1;
        uVar6 = (uint)*param_1;
        if (*param_1 == 0) goto LAB_0010d868;
      }
      if ((&DAT_00141180)[(int)uVar6] != '\0') {
        *puVar9 = (char)uVar6;
        uVar5 = (uVar1 - uVar8) + 1;
        if (uVar5 < uVar1) {
          uVar5 = uVar1;
        }
        lVar7 = uVar5 - uVar1;
        goto LAB_0010d800;
      }
      __sprintf_chk(puVar9,2,uVar8,"%%%02x");
      puVar9 = puVar9 + 3;
      uVar6 = (uint)*param_1;
      uVar5 = (uVar1 + 3) - uVar8;
      if (uVar5 < uVar1) {
        uVar5 = uVar1;
      }
      uVar8 = uVar5 + (uVar8 - (uVar1 + 3));
    } while (*param_1 != 0);
  }
LAB_0010d868:
  *puVar9 = 0;
  return puVar4;
}

