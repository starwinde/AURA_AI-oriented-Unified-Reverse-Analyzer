
undefined8 FUN_001f7340(long param_1,char *param_2,long *param_3)

{
  int iVar1;
  size_t sVar2;
  void *__dest;
  undefined8 *puVar3;
  long *plVar4;
  long *plVar5;
  long *plVar6;
  long lVar7;
  
  if (param_3 == (long *)0x0 || param_2 == (char *)0x0) {
    return 0;
  }
  if (((*(uint *)(param_3 + 3) >> 9 & 1) == 0) && (param_3[7] != 0)) {
    (*(code *)PTR_free_006005a0)();
  }
  sVar2 = strlen(param_2);
  __dest = (void *)(*(code *)PTR_malloc_00600598)(sVar2 + 1);
  if (__dest == (void *)0x0) {
    param_3[7] = 0;
  }
  else {
    memcpy(__dest,param_2,sVar2 + 1);
    param_3[7] = (long)__dest;
    *(uint *)(param_3 + 3) = *(uint *)(param_3 + 3) & 0xfffffdff;
    if (param_1 != 0) {
      plVar6 = *(long **)(param_1 + 0x10);
      for (plVar5 = plVar6; (plVar5 != (long *)0x0 && ((char *)plVar5[7] != (char *)0x0));
          plVar5 = (long *)*plVar5) {
        iVar1 = strcmp(param_2,(char *)plVar5[7]);
        if (iVar1 == 0) {
          if (param_3 == plVar5) {
            return 1;
          }
          lVar7 = *plVar5;
          param_3[1] = plVar5[1];
          *param_3 = lVar7;
          if (lVar7 == 0) {
            if (plVar6 == plVar5) goto LAB_001f7480;
            puVar3 = (undefined8 *)param_3[1];
            if (puVar3 != (undefined8 *)0x0) goto LAB_001f742c;
          }
          else {
            *(long **)(lVar7 + 8) = param_3;
            if (plVar6 == plVar5) {
LAB_001f7480:
              plVar4 = param_3;
              if ((long *)plVar6[1] != plVar6) {
                plVar4 = (long *)param_3[1];
              }
              param_3[1] = (long)plVar4;
              *(long **)(param_1 + 0x10) = param_3;
              goto LAB_001f7438;
            }
            puVar3 = (undefined8 *)param_3[1];
            if (puVar3 == (undefined8 *)0x0) goto LAB_001f7438;
LAB_001f742c:
            *puVar3 = param_3;
            if (*param_3 != 0) goto LAB_001f7438;
          }
          plVar6[1] = (long)param_3;
LAB_001f7438:
          *plVar5 = 0;
          plVar5[1] = 0;
          FUN_001f43e0(plVar5);
          return 1;
        }
      }
    }
  }
  return 0;
}

