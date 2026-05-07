
ulong FUN_00114b40(float param_1,ulong param_2,ulong param_3)

{
  ulong uVar1;
  undefined1 auVar2 [16];
  int *piVar3;
  ulong uVar4;
  ulong uVar5;
  long lVar6;
  
  if ((param_3 & 1) == 0) {
    if (1.8446744e+19 <= (float)param_2 / param_1) goto code_r0x00114bfc;
    param_2 = (ulong)((float)param_2 / param_1);
  }
  if (param_2 < 10) {
    param_2 = 10;
  }
  for (param_2 = param_2 | 1; param_2 != 0xffffffffffffffff; param_2 = param_2 + 2) {
    for (; auVar2._8_8_ = 0, auVar2._0_8_ = param_2,
        uVar4 = (SUB168(auVar2 * ZEXT816(0xaaaaaaaaaaaaaaab),8) & 0xfffffffffffffffe) + param_2 / 3,
        param_2 < 10; param_2 = param_2 + 2) {
      if (param_2 != uVar4) goto LAB_00114be4;
    }
    if (param_2 != uVar4) {
      lVar6 = 0x10;
      uVar5 = 9;
      uVar4 = 3;
      do {
        uVar4 = uVar4 + 2;
        uVar5 = uVar5 + lVar6;
        lVar6 = lVar6 + 8;
        uVar1 = 0;
        if (uVar4 != 0) {
          uVar1 = param_2 / uVar4;
        }
        if (param_2 <= uVar5) {
          if (param_2 != uVar1 * uVar4) goto LAB_00114be4;
          break;
        }
      } while (param_2 != uVar1 * uVar4);
    }
  }
LAB_00114be4:
  if (((param_2 >> 0x3c & 1) == 0) && (param_2 >> 0x3d == 0)) {
    return param_2;
  }
code_r0x00114bfc:
  piVar3 = __errno_location();
  *piVar3 = 0xc;
  return 0;
}

