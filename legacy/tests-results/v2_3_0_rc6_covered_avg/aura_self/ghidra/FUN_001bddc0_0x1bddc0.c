
undefined * FUN_001bddc0(long param_1,undefined4 param_2)

{
  undefined *puVar1;
  ushort uVar2;
  
  uVar2 = FUN_001e6c00(&DAT_00250680,0xa7a,param_2,param_1 + 0x70);
  puVar1 = &UNK_0024bd28 + ((ulong)uVar2 * 8 - (ulong)uVar2);
  if (uVar2 == 0) {
    puVar1 = (undefined *)0x0;
  }
  return puVar1;
}

