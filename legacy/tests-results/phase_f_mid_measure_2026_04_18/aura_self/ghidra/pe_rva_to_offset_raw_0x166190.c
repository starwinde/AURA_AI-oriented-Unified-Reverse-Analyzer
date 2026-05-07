
ulong pe_rva_to_offset_raw(long param_1,ulong param_2,uint param_3)

{
  ushort uVar1;
  uint uVar2;
  long lVar3;
  uint uVar4;
  ulong uVar5;
  ulong uVar6;
  
  if ((((0x3f < param_2) && (uVar4 = *(uint *)(param_1 + 0x3c), (ulong)uVar4 <= param_2 - 4)) &&
      (*(int *)(param_1 + (ulong)uVar4) == 0x4550)) &&
     (uVar5 = (ulong)(uVar4 + 4), uVar5 <= param_2 - 0x14)) {
    uVar1 = *(ushort *)(param_1 + uVar5 + 2);
    uVar6 = (ulong)uVar1 * 0x28;
    if (((uVar6 < param_2 || uVar6 - param_2 == 0) &&
        (uVar5 = (ulong)*(ushort *)(param_1 + uVar5 + 0x10) + uVar5 + 0x14,
        uVar5 <= param_2 + (ulong)uVar1 * -0x28)) && (uVar1 != 0)) {
      lVar3 = param_1 + uVar5;
      do {
        uVar4 = *(uint *)(lVar3 + 8);
        uVar2 = param_3 - *(uint *)(lVar3 + 0xc);
        if (uVar4 == 0) {
          uVar4 = *(uint *)(lVar3 + 0x10);
        }
        if ((*(uint *)(lVar3 + 0xc) <= param_3) && (uVar2 < uVar4)) {
          uVar5 = (ulong)*(uint *)(lVar3 + 0x14) + (ulong)uVar2;
          if (param_2 <= uVar5) {
            uVar5 = 0;
          }
          return uVar5;
        }
        lVar3 = lVar3 + 0x28;
      } while (param_1 + uVar6 + uVar5 != lVar3);
    }
  }
  return 0;
}

