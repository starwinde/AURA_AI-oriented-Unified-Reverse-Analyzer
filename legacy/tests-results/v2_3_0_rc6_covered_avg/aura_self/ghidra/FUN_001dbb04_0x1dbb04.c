
undefined8 FUN_001dbb04(undefined8 param_1,uint param_2)

{
  undefined8 uVar1;
  
  uVar1 = 0;
  if (param_2 < 0x509) {
    uVar1 = *(undefined8 *)(&DAT_005f28f0 + (ulong)param_2 * 8);
  }
  return uVar1;
}

