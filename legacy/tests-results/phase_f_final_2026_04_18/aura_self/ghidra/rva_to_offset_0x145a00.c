
ulong rva_to_offset(long param_1,uint param_2,uint param_3,ulong param_4)

{
  ulong uVar1;
  uint uVar2;
  uint uVar3;
  long lVar4;
  
  if (param_2 != 0) {
    lVar4 = param_1 + (ulong)param_2 * 0x28;
    do {
      uVar3 = *(uint *)(param_1 + 8);
      uVar2 = param_3 - *(uint *)(param_1 + 0xc);
      if (uVar3 == 0) {
        uVar3 = *(uint *)(param_1 + 0x10);
      }
      if ((*(uint *)(param_1 + 0xc) <= param_3) && (uVar2 < uVar3)) {
        uVar1 = (ulong)*(uint *)(param_1 + 0x14) + (ulong)uVar2;
        if (param_4 <= uVar1) {
          uVar1 = 0;
        }
        return uVar1;
      }
      param_1 = param_1 + 0x28;
    } while (param_1 != lVar4);
  }
  return 0;
}

