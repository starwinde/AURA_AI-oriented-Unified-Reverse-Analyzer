
void DecodeT2Imm8S4_part_0(undefined8 param_1,uint param_2)

{
  uint uVar1;
  
  uVar1 = -(param_2 & 0xff);
  if ((param_2 & 0x100) != 0) {
    uVar1 = param_2 & 0xff;
  }
  MCOperand_CreateImm0(param_1,(long)(int)(uVar1 << 2));
  return;
}

