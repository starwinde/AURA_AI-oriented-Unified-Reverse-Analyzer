
void MCInst_addOperand2(long param_1,undefined8 *param_2)

{
  long lVar1;
  undefined8 uVar2;
  byte bVar3;
  
  uVar2 = param_2[1];
  bVar3 = *(byte *)(param_1 + 4);
  lVar1 = param_1 + (ulong)bVar3 * 0x10;
  *(undefined8 *)(lVar1 + 0x10) = *param_2;
  *(undefined8 *)(lVar1 + 0x18) = uVar2;
  *(byte *)(param_1 + 4) = bVar3 + 1;
  return;
}

