
undefined8 DecodeDPRRegListOperand_isra_0(undefined8 param_1,ulong param_2)

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
    if (iVar2 + uVar5 < 0x21) goto LAB_0019607c;
LAB_00196118:
    uVar5 = 0x20 - iVar2;
  }
  else if (0x20 < iVar2 + uVar5) goto LAB_00196118;
  uVar6 = 1;
  if (uVar5 == 0) {
    uVar5 = 1;
  }
  if (0x10 < uVar5) {
    uVar5 = 0x10;
  }
  uVar4 = uVar5 - 1;
LAB_0019607c:
  MCOperand_CreateReg0(param_1,*(undefined2 *)(DPR + uVar3 * 2));
  if (uVar5 != 1) {
    if (iVar2 != 0x1f) {
      uVar3 = (ulong)(iVar2 + 2);
      do {
        MCOperand_CreateReg0(param_1,*(undefined2 *)(&DAT_0022df7e + uVar3 * 2));
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

