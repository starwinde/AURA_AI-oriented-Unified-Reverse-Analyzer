
int eh_frame_count_regions_at(long param_1,ulong param_2)

{
  int iVar1;
  ulong *puVar2;
  ulong *puVar3;
  
  if (param_1 == 0) {
    return 0;
  }
  iVar1 = 0;
  if (*(uint *)(param_1 + 0x28) != 0) {
    puVar2 = *(ulong **)(param_1 + 0x20);
    puVar3 = puVar2 + (ulong)*(uint *)(param_1 + 0x28) * 5;
    iVar1 = 0;
    do {
      if ((*puVar2 <= param_2) && (param_2 < *puVar2 + puVar2[1])) {
        iVar1 = iVar1 + 1;
      }
      puVar2 = puVar2 + 5;
    } while (puVar3 != puVar2);
  }
  return iVar1;
}

