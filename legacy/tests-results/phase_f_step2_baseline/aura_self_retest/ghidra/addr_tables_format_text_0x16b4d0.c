
void addr_tables_format_text(long *param_1,long param_2)

{
  uint uVar1;
  undefined8 *puVar2;
  char *pcVar3;
  uint uVar4;
  long lVar5;
  
  if (param_1 == (long *)0x0 || param_2 == 0) {
    return;
  }
  __fprintf_chk(param_2,2,"Address Tables: %u entries\n",(int)param_1[1]);
  if ((int)param_1[1] != 0) {
    lVar5 = 0;
    uVar4 = 0;
    do {
      puVar2 = (undefined8 *)(*param_1 + lVar5);
      pcVar3 = "jump_table";
      if ((*(int *)(puVar2 + 2) != 0) && (pcVar3 = "fptr", *(int *)(puVar2 + 2) == 1)) {
        pcVar3 = "vtable";
      }
      uVar1 = uVar4 + 1;
      lVar5 = lVar5 + 0x18;
      __fprintf_chk(param_2,2,"  [%u] 0x%lx (%s) ref=0x%lx\n",uVar4,*puVar2,pcVar3,puVar2[1]);
      uVar4 = uVar1;
    } while (uVar1 < *(uint *)(param_1 + 1));
  }
  return;
}

