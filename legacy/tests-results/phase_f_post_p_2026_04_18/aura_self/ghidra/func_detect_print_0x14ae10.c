
void func_detect_print(undefined8 *param_1,FILE *param_2)

{
  undefined8 *puVar1;
  uint uVar2;
  long lVar3;
  char *pcVar4;
  long lVar5;
  long lVar6;
  long *plVar7;
  uint uVar8;
  long *plVar9;
  
  if (param_1 == (undefined8 *)0x0) {
    return;
  }
  if (param_2 == (FILE *)0x0) {
    param_2 = *(FILE **)PTR_stdout_005fff40;
  }
  plVar7 = (long *)*param_1;
  if (plVar7 == (long *)0x0) {
    __fprintf_chk(param_2,2,"Functions (%u detected):\n",0);
  }
  else {
    __fprintf_chk(param_2,2,"Functions (%u detected):\n",(int)plVar7[1]);
    if ((int)plVar7[1] != 0) {
      lVar6 = 0;
      uVar8 = 0;
      do {
        lVar5 = *plVar7 + lVar6;
        uVar2 = uVar8 + 1;
        puVar1 = (undefined8 *)(*plVar7 + lVar6);
        lVar6 = lVar6 + 0x98;
        __fprintf_chk(param_2,2,&DAT_001f8d50,uVar8,*puVar1,*(undefined8 *)(lVar5 + 8),
                      *(undefined4 *)(lVar5 + 0x10),lVar5 + 0x14);
        uVar8 = uVar2;
      } while (uVar2 < *(uint *)(plVar7 + 1));
      plVar9 = (long *)param_1[1];
      if ((plVar9 != (long *)0x0) && ((int)plVar9[1] != 0)) {
        __fprintf_chk(param_2,2,"\nCall Graph (%u edges):\n");
        if ((int)plVar9[1] != 0) {
          lVar6 = 0;
          uVar8 = 0;
          do {
            lVar3 = *plVar9 + lVar6;
            lVar5 = *plVar7 + (ulong)*(uint *)(lVar3 + 4) * 0x98 + 0x14;
            pcVar4 = "  %s  -->  %s  (at 0x%lx)\n";
            if (*(uint *)(lVar3 + 4) == 0xffffffff) {
              lVar5 = *(long *)(lVar3 + 8);
              pcVar4 = "  %s  -->  extern@0x%lx  (at 0x%lx)\n";
            }
            __fprintf_chk(param_2,2,pcVar4,*plVar7 + (ulong)*(uint *)(*plVar9 + lVar6) * 0x98 + 0x14
                          ,lVar5,*(undefined8 *)(lVar3 + 0x10));
            uVar8 = uVar8 + 1;
            lVar6 = lVar6 + 0x18;
          } while (uVar8 < *(uint *)(plVar9 + 1));
        }
        return;
      }
      fwrite("\nCall Graph: (no direct calls found)\n",1,0x25,param_2);
      return;
    }
  }
  fwrite("  (none)\n",1,9,param_2);
  return;
}

