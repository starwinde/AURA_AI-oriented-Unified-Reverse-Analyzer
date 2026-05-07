
undefined8 FUN_0018d6b0(long param_1,int *param_2)

{
  undefined8 uVar1;
  long lVar2;
  
  if (param_1 != 0) {
    if (*(int *)(param_1 + 0x60) != 0) {
      if (*param_2 == 0) {
        *(undefined4 *)(param_1 + 0x50) = 0xb;
        return 0;
      }
      lVar2 = *(long *)(param_2 + 0x3c);
      if (lVar2 != 0) {
        uVar1 = FUN_00190890(lVar2 + 0x53,*(undefined1 *)(lVar2 + 0x5b));
        return uVar1;
      }
    }
    *(undefined4 *)(param_1 + 0x50) = 7;
  }
  return 0;
}

