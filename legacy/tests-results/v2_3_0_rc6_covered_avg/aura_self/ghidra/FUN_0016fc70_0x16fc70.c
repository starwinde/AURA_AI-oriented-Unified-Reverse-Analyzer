
ulong FUN_0016fc70(long param_1,ulong param_2)

{
  byte *pbVar1;
  ulong uVar2;
  ulong uVar3;
  
  uVar2 = 0xcbf29ce484222325;
  if (param_1 != 0 && param_2 != 0) {
    uVar3 = 0;
    do {
      pbVar1 = (byte *)(param_1 + uVar3);
      uVar3 = uVar3 + 1;
      uVar2 = (*pbVar1 ^ uVar2) * 0x100000001b3;
    } while (uVar3 < param_2);
  }
  return uVar2;
}

