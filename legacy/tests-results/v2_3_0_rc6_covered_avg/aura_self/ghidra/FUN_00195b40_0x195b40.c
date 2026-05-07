
void FUN_00195b40(undefined8 param_1,uint param_2)

{
  uint uVar1;
  
  uVar1 = -(param_2 & 0xff);
  if ((param_2 & 0x100) != 0) {
    uVar1 = param_2 & 0xff;
  }
  FUN_00190140(param_1,(long)(int)(uVar1 << 2));
  return;
}

