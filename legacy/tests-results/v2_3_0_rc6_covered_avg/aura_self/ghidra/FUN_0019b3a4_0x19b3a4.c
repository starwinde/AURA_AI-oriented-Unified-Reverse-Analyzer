
undefined8 FUN_0019b3a4(undefined8 param_1,uint param_2)

{
  wchar16 wVar1;
  undefined2 uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar3 = param_2 >> 0xc & 0xf | (param_2 & 0x400000) >> 0x12;
  uVar4 = param_2 >> 0x10 & 0xf | (param_2 & 0x80) >> 3;
  if ((param_2 >> 6 & 1) == 0) {
    uVar2 = *(undefined2 *)(&DAT_0022f4e0 + (ulong)uVar3 * 2);
    FUN_00190100(param_1,uVar2);
    FUN_00190100(param_1,uVar2);
    FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f4e0 + (ulong)uVar4 * 2));
LAB_0019b458:
    FUN_00190100(param_1,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(param_2 & 0xf | (param_2 & 0x20) >> 1) * 2));
    FUN_00190140(param_1,0);
    FUN_00190140(param_1,param_2 >> 0x14 & 3);
    return 3;
  }
  if ((param_2 >> 0xc & 1) == 0) {
    wVar1 = L"23456789:;<=>?@A"[uVar3 >> 1];
    FUN_00190100(param_1,wVar1);
    FUN_00190100(param_1,wVar1);
    if ((param_2 >> 0x10 & 1) == 0) {
      FUN_00190100(param_1,L"23456789:;<=>?@A"[uVar4 >> 1]);
      goto LAB_0019b458;
    }
  }
  return 0;
}

