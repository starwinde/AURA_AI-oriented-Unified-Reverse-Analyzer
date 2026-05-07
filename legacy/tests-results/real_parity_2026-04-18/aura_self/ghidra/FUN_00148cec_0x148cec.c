
byte * FUN_00148cec(byte *param_1)

{
  ushort uVar1;
  ushort **ppuVar2;
  size_t sVar3;
  byte *pbVar4;
  ushort *puVar5;
  
  ppuVar2 = __ctype_b_loc();
  puVar5 = *ppuVar2;
  uVar1 = puVar5[*param_1];
  while ((uVar1 >> 0xd & 1) != 0) {
    param_1 = param_1 + 1;
    uVar1 = puVar5[*param_1];
  }
  sVar3 = strlen((char *)param_1);
  pbVar4 = param_1 + sVar3;
  if (param_1 < pbVar4) {
    do {
      if ((puVar5[pbVar4[-1]] >> 0xd & 1) == 0) break;
      pbVar4 = pbVar4 + -1;
    } while (pbVar4 != param_1);
  }
  *pbVar4 = 0;
  return param_1;
}

