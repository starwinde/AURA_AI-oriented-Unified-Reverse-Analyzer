
void FUN_001e498c(long param_1,ushort *param_2,int param_3)

{
  ushort uVar1;
  uint uVar2;
  ulong uVar3;
  uint uVar4;
  undefined4 uVar5;
  uint uVar6;
  uint uVar7;
  
  uVar4 = MCInst_getOpcode();
  if ((*param_2 <= uVar4) && (uVar6 = param_3 - 1, uVar4 <= param_2[(ulong)uVar6 * 0x2f])) {
    uVar7 = 0;
    do {
      uVar2 = uVar7 + uVar6 >> 1;
      uVar3 = (ulong)uVar2;
      uVar1 = param_2[uVar3 * 0x2f];
      while( true ) {
        if (uVar4 == uVar1) {
          **(uint **)(param_1 + 0x310) = (uint)param_2[uVar3 * 0x2f + 1];
          return;
        }
        if (uVar4 < uVar1) break;
        uVar7 = uVar2 + 1;
        if (uVar6 < uVar7) goto LAB_001e4a00;
        uVar2 = uVar7 + uVar6 >> 1;
        uVar3 = (ulong)uVar2;
        uVar1 = param_2[uVar3 * 0x2f];
      }
      uVar6 = uVar2 - 1;
    } while (uVar7 <= uVar6);
  }
LAB_001e4a00:
  uVar5 = MCInst_getOpcode(param_1);
  __printf_chk(2,"ERROR: Could not find CS id for MCInst opcode: %d\n",uVar5);
  return;
}

