
void entry_points_format_text(long *param_1,long param_2)

{
  long lVar1;
  uint uVar2;
  undefined8 uVar3;
  char *pcVar4;
  long lVar5;
  uint uVar6;
  
  if (param_1 == (long *)0x0 || param_2 == 0) {
    return;
  }
  __fprintf_chk(param_2,2,"Entry Points: %u entries\n",(int)param_1[1]);
  if ((int)param_1[1] != 0) {
    uVar6 = 0;
    lVar5 = 0;
    do {
      while( true ) {
        lVar1 = *param_1 + lVar5;
        uVar3 = *(undefined8 *)(*param_1 + lVar5);
        uVar2 = *(uint *)(lVar1 + 8);
        if (uVar2 == 3) break;
        if (uVar2 < 4) {
          if (uVar2 == 1) {
            pcVar4 = "INIT_ARRAY";
          }
          else {
            pcVar4 = "FINI_ARRAY";
            if (uVar2 != 2) {
              pcVar4 = "MAIN_ENTRY";
            }
          }
          goto LAB_00165b94;
        }
        pcVar4 = "DT_FINI";
        if (uVar2 == 4) goto LAB_00165b94;
        pcVar4 = "TLS_CALLBACK";
        if (uVar2 != 5) {
          pcVar4 = "UNKNOWN";
        }
        if (*(long *)(lVar1 + 0x10) != 0) goto LAB_00165ba0;
LAB_00165c08:
        __fprintf_chk(param_2,2,"  0x%lx  %-14s  %s\n",uVar3,pcVar4,"(unnamed)");
        uVar6 = uVar6 + 1;
        lVar5 = lVar5 + 0x18;
        if (*(uint *)(param_1 + 1) <= uVar6) {
          return;
        }
      }
      pcVar4 = "DT_INIT";
LAB_00165b94:
      if (*(long *)(lVar1 + 0x10) == 0) goto LAB_00165c08;
LAB_00165ba0:
      __fprintf_chk(param_2,2,"  0x%lx  %-14s  %s\n",uVar3,pcVar4);
      uVar6 = uVar6 + 1;
      lVar5 = lVar5 + 0x18;
    } while (uVar6 < *(uint *)(param_1 + 1));
  }
  return;
}

