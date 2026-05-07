
long eh_frame_find_fde(long param_1,ulong param_2)

{
  long lVar1;
  long lVar2;
  
  if ((param_1 != 0) && (*(uint *)(param_1 + 0x18) != 0)) {
    lVar1 = *(long *)(param_1 + 0x10);
    lVar2 = lVar1 + (ulong)*(uint *)(param_1 + 0x18) * 0x28;
    do {
      if ((*(ulong *)(lVar1 + 0x10) <= param_2) &&
         (param_2 < *(ulong *)(lVar1 + 0x10) + *(long *)(lVar1 + 0x18))) {
        return lVar1;
      }
      lVar1 = lVar1 + 0x28;
    } while (lVar2 != lVar1);
  }
  return 0;
}

