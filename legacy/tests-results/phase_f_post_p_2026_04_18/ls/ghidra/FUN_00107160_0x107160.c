
long FUN_00107160(undefined8 *param_1,ulong param_2)

{
  ulong uVar1;
  ulong uVar2;
  byte bVar3;
  byte *pbVar4;
  
  uVar2 = 0;
  pbVar4 = (byte *)*param_1;
  bVar3 = *pbVar4;
  if (bVar3 != 0) {
    do {
      uVar2 = (uVar2 >> 0x37 | uVar2 << 9) + (ulong)bVar3;
      pbVar4 = pbVar4 + 1;
      bVar3 = *pbVar4;
    } while (bVar3 != 0);
    uVar1 = 0;
    if (param_2 != 0) {
      uVar1 = uVar2 / param_2;
    }
    uVar2 = uVar2 - uVar1 * param_2;
  }
  uVar1 = 0;
  if (param_2 != 0) {
    uVar1 = (uVar2 ^ param_1[1]) / param_2;
  }
  return (uVar2 ^ param_1[1]) - uVar1 * param_2;
}

