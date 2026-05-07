
undefined8 FUN_00195e10(undefined8 param_1,uint param_2)

{
  undefined2 uVar1;
  int iVar2;
  
  iVar2 = FUN_0018ffb0();
  if (iVar2 == 0xc3d) {
    uVar1 = *(undefined2 *)
             (&DAT_0022f720 + (ulong)(param_2 & 7 | ((param_2 & 0xffff) >> 7 & 1) << 3) * 2);
    FUN_00190100(param_1,uVar1);
    FUN_00190100(param_1,0xc);
    FUN_00190100(param_1,uVar1);
    return 3;
  }
  iVar2 = FUN_0018ffb0(param_1);
  if (iVar2 != 0xc41) {
    return 3;
  }
  FUN_00190100(param_1,0xc);
  FUN_00190100(param_1,0xc);
  FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + ((ulong)((param_2 & 0xffff) >> 3) & 0xf) * 2)
              );
  return 3;
}

