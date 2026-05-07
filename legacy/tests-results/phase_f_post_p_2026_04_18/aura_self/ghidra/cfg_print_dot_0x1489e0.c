
undefined8 cfg_print_dot(long *param_1,FILE *param_2)

{
  long lVar1;
  long lVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  char *pcVar6;
  long lVar7;
  uint uVar8;
  ulong uVar9;
  
  if (param_1 == (long *)0x0) {
    return 0;
  }
  if (param_2 == (FILE *)0x0) {
    param_2 = *(FILE **)PTR_stdout_005fff40;
  }
  __fprintf_chk(param_2,2,
                "digraph cfg_0x%llx {\n    node [shape=box fontname=\"Courier New\" fontsize=10];\n"
                ,param_1[4]);
  uVar9 = 0;
  if ((int)param_1[1] != 0) {
    do {
      lVar1 = *param_1 + uVar9 * 0x20;
      lVar7 = 0;
      uVar8 = 0;
      __fprintf_chk(param_2,2,"    B%u [label=\"Block %u\\n0x%llx..0x%llx",uVar9 & 0xffffffff,
                    uVar9 & 0xffffffff,*(undefined8 *)(*param_1 + uVar9 * 0x20),
                    *(undefined8 *)(lVar1 + 8));
      if (*(int *)(lVar1 + 0x18) != 0) {
        do {
          while( true ) {
            lVar2 = *(long *)(lVar1 + 0x10) + lVar7;
            fwrite(&DAT_001f8908,1,2,param_2);
            dot_escape(param_2,lVar2 + 0x20);
            if (*(char *)(lVar2 + 0x60) == '\0') break;
            fputc(0x20,param_2);
            uVar8 = uVar8 + 1;
            dot_escape(param_2,lVar2 + 0x60);
            lVar7 = lVar7 + 0xe0;
            if (*(uint *)(lVar1 + 0x18) <= uVar8) goto LAB_00148af8;
          }
          uVar8 = uVar8 + 1;
          lVar7 = lVar7 + 0xe0;
        } while (uVar8 < *(uint *)(lVar1 + 0x18));
      }
LAB_00148af8:
      fwrite(&DAT_001f8aa8,1,4,param_2);
      uVar9 = uVar9 + 1;
    } while ((uint)uVar9 < *(uint *)(param_1 + 1));
  }
  lVar7 = 0;
  uVar8 = 0;
  if ((int)param_1[3] != 0) {
    do {
      while( true ) {
        lVar1 = param_1[2] + lVar7;
        uVar5 = *(undefined4 *)(param_1[2] + lVar7);
        iVar3 = *(int *)(lVar1 + 4);
        uVar4 = *(uint *)(lVar1 + 8);
        if (iVar3 != -1) break;
        if (uVar4 == 2) {
          pcVar6 = "BRANCH_FALSE";
        }
        else if (uVar4 < 3) {
          pcVar6 = "FALLTHROUGH";
          if (uVar4 != 0) {
            pcVar6 = "BRANCH_TRUE";
          }
        }
        else if (uVar4 == 3) {
          pcVar6 = "CALL";
        }
        else {
          pcVar6 = "RET";
          if (uVar4 != 4) {
            pcVar6 = "UNKNOWN";
          }
        }
        __fprintf_chk(param_2,2,"    B%u -> EXT_%u [label=\"%s\" style=dashed];\n",uVar5,uVar8,
                      pcVar6);
        uVar8 = uVar8 + 1;
        lVar7 = lVar7 + 0xc;
        if (*(uint *)(param_1 + 3) <= uVar8) goto LAB_00148bf0;
      }
      if (uVar4 == 2) {
        pcVar6 = "BRANCH_FALSE";
      }
      else if (uVar4 < 3) {
        pcVar6 = "FALLTHROUGH";
        if (uVar4 != 0) {
          pcVar6 = "BRANCH_TRUE";
        }
      }
      else if (uVar4 == 3) {
        pcVar6 = "CALL";
      }
      else {
        pcVar6 = "RET";
        if (uVar4 != 4) {
          pcVar6 = "UNKNOWN";
        }
      }
      __fprintf_chk(param_2,2,"    B%u -> B%u [label=\"%s\"];\n",uVar5,iVar3,pcVar6);
      uVar8 = uVar8 + 1;
      lVar7 = lVar7 + 0xc;
    } while (uVar8 < *(uint *)(param_1 + 3));
  }
LAB_00148bf0:
  fwrite(&DAT_001f8ab0,1,2,param_2);
  return 0;
}

