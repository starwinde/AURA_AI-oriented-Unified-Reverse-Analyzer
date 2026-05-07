
undefined4
FUN_0014b514(long param_1,long param_2,ulong param_3,ulong param_4,long param_5,undefined4 param_6)

{
  undefined4 uVar1;
  long lVar2;
  
  if (((param_5 != 0 && param_3 < param_4) && (param_1 != 0 && param_2 != 0)) &&
     (lVar2 = FUN_00189670(), lVar2 != 0)) {
    uVar1 = FUN_0014b280(*(undefined8 *)(lVar2 + 0x10),*(undefined4 *)(lVar2 + 0x18),param_2,param_3
                         ,param_4,param_5,param_6);
    FUN_0018b5e0(lVar2);
    return uVar1;
  }
  return 0;
}

