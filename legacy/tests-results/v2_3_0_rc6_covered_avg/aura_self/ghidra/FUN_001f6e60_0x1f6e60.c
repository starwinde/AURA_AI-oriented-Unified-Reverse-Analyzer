
void FUN_001f6e60(long param_1,char *param_2)

{
  int iVar1;
  long *plVar2;
  long lVar3;
  long *plVar4;
  long *plVar5;
  
  if (param_1 == 0 || param_2 == (char *)0x0) {
    FUN_001f43e0(0);
    return;
  }
  plVar4 = *(long **)(param_1 + 0x10);
  plVar5 = plVar4;
  while( true ) {
    if (plVar5 == (long *)0x0) {
      FUN_001f43e0(0);
      return;
    }
    if ((char *)plVar5[7] == (char *)0x0) break;
    iVar1 = strcmp(param_2,(char *)plVar5[7]);
    if (iVar1 == 0) {
      if (plVar5 == plVar4) {
        lVar3 = *plVar5;
        if (lVar3 != 0) {
          *(long *)(lVar3 + 8) = plVar5[1];
        }
        *(long *)(param_1 + 0x10) = lVar3;
      }
      else {
        plVar2 = (long *)plVar5[1];
        if (plVar2 == (long *)0x0) break;
        lVar3 = *plVar5;
        *plVar2 = lVar3;
        if (lVar3 == 0) {
          plVar4[1] = (long)plVar2;
        }
        else {
          *(long **)(lVar3 + 8) = plVar2;
        }
      }
      *plVar5 = 0;
      plVar5[1] = 0;
      FUN_001f43e0(plVar5);
      return;
    }
    plVar5 = (long *)*plVar5;
  }
  FUN_001f43e0(0);
  return;
}

