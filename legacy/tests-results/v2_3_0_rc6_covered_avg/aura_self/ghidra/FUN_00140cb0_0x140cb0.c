
undefined8 FUN_00140cb0(undefined8 param_1)

{
  int iVar1;
  long lVar2;
  undefined8 uVar3;
  
  lVar2 = FUN_00144c60();
  if (lVar2 != 0) {
    iVar1 = FUN_00144fd0(*(undefined8 *)(lVar2 + 8),*(undefined8 *)(lVar2 + 0x10));
    FUN_00144bf0(lVar2);
    if (iVar1 == 2) {
      uVar3 = FUN_00145ae0(param_1);
      return uVar3;
    }
    if (iVar1 == 3) {
      uVar3 = FUN_00147560(param_1);
      return uVar3;
    }
    if (iVar1 == 1) {
      uVar3 = FUN_001459e0(param_1);
      return uVar3;
    }
    __fprintf_chk(*(undefined8 *)PTR_stderr_005fffd8,2,
                  "aura: unsupported or unknown file format: \'%s\'\n",param_1);
  }
  return 0;
}

