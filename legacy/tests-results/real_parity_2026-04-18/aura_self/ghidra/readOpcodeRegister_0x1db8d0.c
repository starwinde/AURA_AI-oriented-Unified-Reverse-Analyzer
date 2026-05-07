
undefined8 readOpcodeRegister(long param_1,byte param_2)

{
  uint uVar1;
  uint uVar2;
  
  if (param_2 == 0) {
    param_2 = *(byte *)(param_1 + 0x7c);
  }
  if (param_2 == 4) {
    *(uint *)(param_1 + 0xb8) =
         ((*(byte *)(param_1 + 5) & 1) << 3 | *(byte *)(param_1 + 0x81) & 7) + 0x24;
    return 0;
  }
  if (param_2 < 5) {
    if (param_2 == 1) {
      uVar2 = (*(byte *)(param_1 + 5) & 1) << 3 | *(byte *)(param_1 + 0x81) & 7;
      uVar1 = uVar2 + 0xc;
      if (*(byte *)(param_1 + 5) == 0 || 3 < uVar2 - 4) {
        uVar1 = uVar2;
      }
      *(uint *)(param_1 + 0xb8) = uVar1;
      return 0;
    }
    if (param_2 == 2) {
      *(uint *)(param_1 + 0xb8) =
           ((*(byte *)(param_1 + 5) & 1) << 3 | *(byte *)(param_1 + 0x81) & 7) + 0x14;
      return 0;
    }
  }
  else if (param_2 == 8) {
    *(uint *)(param_1 + 0xb8) =
         ((*(byte *)(param_1 + 5) & 1) << 3 | *(byte *)(param_1 + 0x81) & 7) + 0x34;
  }
  return 0;
}

