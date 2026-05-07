
int FUN_00107090(long param_1,long param_2,long param_3)

{
  long lVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  lVar1 = 0;
  do {
    uVar3 = (uint)*(byte *)(param_1 + lVar1);
    uVar4 = uVar3;
    if (uVar3 - 0x41 < 0x1a) {
      uVar4 = *(byte *)(param_1 + lVar1) + 0x20;
      uVar3 = uVar4 & 0xff;
    }
    uVar2 = (uint)*(byte *)(param_2 + lVar1);
    uVar5 = uVar2;
    if (uVar2 - 0x41 < 0x1a) {
      uVar5 = *(byte *)(param_2 + lVar1) + 0x20;
      uVar2 = uVar5 & 0xff;
    }
  } while (((lVar1 != param_3 + -1) && (uVar4 != 0)) && (lVar1 = lVar1 + 1, uVar3 == uVar2));
  return uVar4 - uVar5;
}

