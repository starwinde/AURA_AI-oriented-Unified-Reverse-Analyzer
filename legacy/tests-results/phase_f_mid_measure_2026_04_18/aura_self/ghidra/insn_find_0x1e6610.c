
undefined2 insn_find(long param_1,uint param_2,uint param_3,long *param_4)

{
  long lVar1;
  uint uVar2;
  ulong uVar3;
  
  uVar2 = (uint)*(ushort *)(param_1 + (ulong)(param_2 - 1) * 0x5e);
  if (param_3 <= uVar2) {
    lVar1 = *param_4;
    if (lVar1 == 0) {
      lVar1 = (**(code **)PTR_cs_mem_calloc_005fff30)(uVar2 + 1,2);
      uVar3 = 1;
      if (1 < param_2) {
        do {
          uVar2 = (int)uVar3 + 1;
          *(short *)(lVar1 + (ulong)*(ushort *)(param_1 + uVar3 * 0x5e) * 2) = (short)uVar3;
          uVar3 = (ulong)(uVar2 & 0xffff);
        } while ((uVar2 & 0xffff) < param_2);
      }
      *param_4 = lVar1;
    }
    return *(undefined2 *)(lVar1 + (ulong)param_3 * 2);
  }
  return 0;
}

