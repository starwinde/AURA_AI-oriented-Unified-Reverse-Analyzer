
void FUN_001cc25c(long param_1)

{
  long lVar1;
  undefined4 uVar2;
  ulong uVar3;
  
  uVar3 = (ulong)(*(byte *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x67) - 1);
  MCInst_getOperand((int)param_1,uVar3);
  uVar2 = MCOperand_getReg();
  lVar1 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0) + uVar3 * 0x38;
  *(undefined4 *)(lVar1 + 0x7c) = 0x48;
  *(undefined4 *)(lVar1 + 0x88) = uVar2;
  *(undefined8 *)(lVar1 + 0x8c) = 0;
  return;
}

