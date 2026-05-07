
undefined8 FUN_00197970(undefined8 param_1,uint param_2)

{
  if ((param_2 >> 0xc & 1) != 0) {
    return 0;
  }
  FUN_00190100(param_1,L"23456789:;<=>?@A"
                       [(param_2 >> 0xc & 0xf | (param_2 & 0x400000) >> 0x12) >> 1]);
  FUN_00190100(param_1,*(undefined2 *)
                        (&DAT_0022f4e0 + (ulong)(param_2 & 0xf | (param_2 & 0x20) >> 1) * 2));
  FUN_00190140(param_1,(long)(8 << ((ulong)(param_2 >> 0x12) & 3)));
  return 3;
}

