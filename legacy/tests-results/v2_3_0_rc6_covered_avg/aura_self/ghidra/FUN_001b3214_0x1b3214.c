
void FUN_001b3214(long param_1,undefined8 param_2)

{
  long lVar1;
  byte bVar2;
  uint uVar3;
  long lVar4;
  
  FUN_0018ffd0(param_1,3);
  uVar3 = FUN_001900a0();
  if (uVar3 < 10) {
    FUN_001903f0(param_2,&DAT_001fe0f8,uVar3);
  }
  else {
    FUN_001903f0(param_2,"{0x%x}",uVar3);
  }
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar4 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar2 = *(byte *)(lVar4 + 0x80);
    lVar1 = lVar4 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10;
    *(undefined4 *)(lVar1 + 0x94) = 2;
    *(uint *)(lVar1 + 0x98) = uVar3;
    *(byte *)(lVar4 + 0x80) = bVar2 + 1;
  }
  return;
}

