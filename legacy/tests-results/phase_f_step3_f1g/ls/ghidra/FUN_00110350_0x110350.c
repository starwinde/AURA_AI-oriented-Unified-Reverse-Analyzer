
ulong FUN_00110350(uint *param_1,byte *param_2,long param_3)

{
  bool bVar1;
  ulong uVar2;
  ulong uVar3;
  long lVar4;
  
  bVar1 = param_2 == (byte *)0x0;
  lVar4 = param_3;
  if (bVar1) {
    param_1 = (uint *)0x0;
    param_2 = (byte *)0x119c60;
    lVar4 = 1;
  }
  uVar2 = mbrtoc32(param_1,param_2,lVar4);
  bVar1 = !bVar1;
  if ((((!bVar1 || param_3 != 0) && 0xfffffffffffffffc < uVar2) &&
       (bVar1 && param_3 == 0 || uVar2 != 0xfffffffffffffffd)) &&
     (uVar3 = FUN_0010ba30(0), (uVar3 & 1) == 0)) {
    if (param_1 != (uint *)0x0) {
      *param_1 = (uint)*param_2;
    }
    uVar2 = 1;
  }
  return uVar2;
}

