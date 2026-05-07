
ulong FUN_00166dc0(ulong *param_1,int param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  ulong uVar3;
  ulong uVar4;
  
  if (param_2 != 8) {
    uVar1 = (uint)*param_1;
    uVar2 = (uVar1 & 0xff00ff00) >> 8 | (uVar1 & 0xff00ff) << 8;
    uVar2 = uVar2 >> 0x10 | uVar2 << 0x10;
    if (param_3 != 0) {
      uVar2 = uVar1;
    }
    return (ulong)uVar2;
  }
  uVar4 = *param_1;
  uVar3 = (uVar4 & 0xff00ff00ff00ff00) >> 8 | (uVar4 & 0xff00ff00ff00ff) << 8;
  uVar3 = (uVar3 & 0xffff0000ffff0000) >> 0x10 | (uVar3 & 0xffff0000ffff) << 0x10;
  uVar3 = uVar3 >> 0x20 | uVar3 << 0x20;
  if (param_3 != 0) {
    uVar3 = uVar4;
  }
  return uVar3;
}

