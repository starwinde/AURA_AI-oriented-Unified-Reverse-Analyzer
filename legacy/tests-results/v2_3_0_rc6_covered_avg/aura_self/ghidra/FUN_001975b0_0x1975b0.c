
undefined8 FUN_001975b0(undefined8 param_1,ulong param_2)

{
  int iVar1;
  int iVar2;
  ulong uVar3;
  uint uVar4;
  uint uVar5;
  undefined8 uVar6;
  
  uVar5 = (uint)(param_2 >> 1) & 0x7f;
  uVar3 = param_2 >> 8 & 0xffffff;
  uVar4 = uVar5 - 1;
  iVar2 = (int)uVar3;
  if (uVar4 < 0x10) {
    uVar6 = 3;
    if (iVar2 + uVar5 < 0x21) goto LAB_001975ec;
LAB_00197688:
    uVar5 = 0x20 - iVar2;
  }
  else if (0x20 < iVar2 + uVar5) goto LAB_00197688;
  uVar6 = 1;
  if (uVar5 == 0) {
    uVar5 = 1;
  }
  if (0x10 < uVar5) {
    uVar5 = 0x10;
  }
  uVar4 = uVar5 - 1;
LAB_001975ec:
  FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f4e0 + uVar3 * 2));
  if (uVar5 != 1) {
    if (iVar2 != 0x1f) {
      uVar3 = (ulong)(iVar2 + 2);
      do {
        FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f4de + uVar3 * 2));
        iVar1 = (int)uVar3;
        uVar3 = uVar3 + 1;
        if (uVar4 <= (iVar1 - iVar2) - 1U) {
          return uVar6;
        }
      } while (uVar3 != (ulong)(0x1e - iVar2) + (ulong)(iVar2 + 3));
    }
    uVar6 = 0;
  }
  return uVar6;
}

