
long * get_object_item(long param_1,char *param_2,int param_3)

{
  byte *pbVar1;
  byte *pbVar2;
  int iVar3;
  __int32_t **pp_Var4;
  long lVar5;
  long *plVar6;
  char *pcVar7;
  
  if (param_1 == 0 || param_2 == (char *)0x0) {
    return (long *)0x0;
  }
  plVar6 = *(long **)(param_1 + 0x10);
  if (param_3 == 0) {
    for (; plVar6 != (long *)0x0; plVar6 = (long *)*plVar6) {
      pcVar7 = (char *)plVar6[7];
      if (pcVar7 != (char *)0x0) {
        if (pcVar7 == param_2) {
LAB_001f1934:
          if (plVar6[7] == 0) {
            plVar6 = (long *)0x0;
          }
          return plVar6;
        }
        pp_Var4 = __ctype_tolower_loc();
        lVar5 = 0;
        while( true ) {
          pbVar1 = (byte *)(param_2 + lVar5);
          pbVar2 = (byte *)(pcVar7 + lVar5);
          lVar5 = lVar5 + 1;
          if ((*pp_Var4)[*pbVar1] != (*pp_Var4)[*pbVar2]) break;
          if (*pbVar1 == 0) goto LAB_001f1934;
        }
      }
    }
  }
  else {
    for (; plVar6 != (long *)0x0; plVar6 = (long *)*plVar6) {
      if (((char *)plVar6[7] == (char *)0x0) ||
         (iVar3 = strcmp(param_2,(char *)plVar6[7]), iVar3 == 0)) goto LAB_001f1934;
    }
  }
  return (long *)0x0;
}

