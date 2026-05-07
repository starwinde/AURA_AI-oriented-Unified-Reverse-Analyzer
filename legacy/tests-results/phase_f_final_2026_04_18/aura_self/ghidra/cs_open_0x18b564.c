
int cs_open(uint param_1,uint param_2,undefined8 *param_3)

{
  int iVar1;
  uint *puVar2;
  code *pcVar3;
  
  if ((((cs_mem_malloc == (undefined *)0x0) || (cs_mem_calloc == (undefined *)0x0)) ||
      (cs_mem_realloc == (undefined *)0x0)) ||
     ((cs_mem_free == (undefined *)0x0 || (cs_vsnprintf == (undefined *)0x0)))) {
    return 8;
  }
  if (param_1 < 0x12) {
    pcVar3 = (code *)(&arch_configs)[(ulong)param_1 * 3];
    if (pcVar3 != (code *)0x0) {
      if ((param_2 & *(uint *)(&DAT_005ff858 + (ulong)param_1 * 0x18)) != 0) {
        *param_3 = 0;
        return 5;
      }
      puVar2 = (uint *)(*(code *)cs_mem_calloc)(1,0xb8);
      if (puVar2 == (uint *)0x0) {
        return 1;
      }
      *puVar2 = param_1;
      puVar2[1] = param_2;
      puVar2[0x14] = 0;
      puVar2[0x18] = 0;
      *(char **)(puVar2 + 0x22) = ".byte";
      iVar1 = (*pcVar3)();
      if (iVar1 == 0) {
        *param_3 = puVar2;
        return 0;
      }
      (*(code *)cs_mem_free)(puVar2);
      *param_3 = 0;
      return iVar1;
    }
  }
  *param_3 = 0;
  return 2;
}

