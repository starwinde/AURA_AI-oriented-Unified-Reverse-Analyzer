
void FUN_0010bbf0(ulong *param_1)

{
  int iVar1;
  void *pvVar2;
  int *piVar3;
  long lVar4;
  long *plVar5;
  void *pvVar6;
  long *plVar7;
  
  piVar3 = __errno_location();
  iVar1 = *piVar3;
  plVar7 = (long *)*param_1;
  plVar5 = (long *)param_1[1];
  if ((param_1[8] != 0) && (param_1[4] != 0)) {
    if (plVar5 <= plVar7) goto LAB_0010bcb8;
    do {
      while (lVar4 = *plVar7, plVar5 = plVar7, lVar4 != 0) {
        while( true ) {
          (*(code *)param_1[8])(lVar4);
          plVar5 = (long *)plVar5[1];
          if (plVar5 == (long *)0x0) break;
          lVar4 = *plVar5;
        }
        plVar5 = (long *)param_1[1];
        plVar7 = plVar7 + 2;
        if (plVar5 <= plVar7) goto LAB_0010bc80;
      }
      plVar5 = (long *)param_1[1];
      plVar7 = plVar7 + 2;
    } while (plVar7 < plVar5);
  }
LAB_0010bc80:
  plVar7 = (long *)*param_1;
  if (plVar7 < plVar5) {
    do {
      pvVar2 = (void *)plVar7[1];
      while (pvVar2 != (void *)0x0) {
        pvVar6 = *(void **)((long)pvVar2 + 8);
        free(pvVar2);
        pvVar2 = pvVar6;
      }
      plVar7 = plVar7 + 2;
    } while (plVar7 < (long *)param_1[1]);
  }
LAB_0010bcb8:
  pvVar2 = (void *)param_1[9];
  while (pvVar2 != (void *)0x0) {
    pvVar6 = *(void **)((long)pvVar2 + 8);
    free(pvVar2);
    pvVar2 = pvVar6;
  }
  free((void *)*param_1);
  free(param_1);
  *piVar3 = iVar1;
  return;
}

