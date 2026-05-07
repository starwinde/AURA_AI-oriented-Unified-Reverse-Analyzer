
void const_refs_format_text(long *param_1,long param_2)

{
  long lVar1;
  undefined8 uVar2;
  char *pcVar3;
  long lVar4;
  
  if (param_1 == (long *)0x0 || param_2 == 0) {
    return;
  }
  __fprintf_chk(param_2,2,"Constant References: %u entries\n",(int)param_1[1]);
  if ((int)param_1[1] != 0) {
    lVar4 = 0;
    do {
      while( true ) {
        lVar1 = *param_1 + lVar4 * 0x20;
        pcVar3 = "CODE";
        if ((*(int *)(lVar1 + 0x10) != 0) && (pcVar3 = "DATA", *(int *)(lVar1 + 0x10) != 1)) {
          pcVar3 = "UNKNOWN";
        }
        uVar2 = *(undefined8 *)(*param_1 + lVar4 * 0x20);
        if (*(long *)(lVar1 + 0x18) != 0) break;
        __fprintf_chk(param_2,2,"  0x%lx -> 0x%lx [%s] (%s)\n",uVar2,*(undefined8 *)(lVar1 + 8),
                      pcVar3,&DAT_001f9918);
        lVar4 = lVar4 + 1;
        if (*(uint *)(param_1 + 1) <= (uint)lVar4) {
          return;
        }
      }
      __fprintf_chk(param_2,2,"  0x%lx -> 0x%lx [%s] (%s)\n",uVar2,*(undefined8 *)(lVar1 + 8),pcVar3
                   );
      lVar4 = lVar4 + 1;
    } while ((uint)lVar4 < *(uint *)(param_1 + 1));
  }
  return;
}

