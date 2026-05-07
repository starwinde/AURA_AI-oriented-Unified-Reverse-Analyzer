
undefined8 cfg_print_text(long *param_1,FILE *param_2)

{
  long lVar1;
  long lVar2;
  int iVar3;
  bool bVar4;
  uint uVar5;
  undefined8 uVar6;
  char *pcVar7;
  ulong uVar8;
  long lVar9;
  uint uVar10;
  char *local_8;
  
  if (param_1 == (long *)0x0) {
    return 0;
  }
  if (param_2 == (FILE *)0x0) {
    param_2 = *(FILE **)PTR_stdout_005fff40;
  }
  __fprintf_chk(param_2,2,"CFG of function 0x%016llx  (%u blocks, %u edges)\n\n",param_1[4],
                (int)param_1[1],(int)param_1[3]);
  if ((int)param_1[1] != 0) {
    uVar8 = 0;
    do {
      lVar1 = *param_1 + uVar8 * 0x20;
      lVar9 = 0;
      uVar10 = 0;
      __fprintf_chk(param_2,2,"Block %u: 0x%llx .. 0x%llx  (%u insns)\n",uVar8 & 0xffffffff,
                    *(undefined8 *)(*param_1 + uVar8 * 0x20),*(undefined8 *)(lVar1 + 8),
                    *(undefined4 *)(lVar1 + 0x18));
      if (*(int *)(lVar1 + 0x18) != 0) {
        do {
          while( true ) {
            lVar2 = *(long *)(lVar1 + 0x10) + lVar9;
            uVar6 = *(undefined8 *)(*(long *)(lVar1 + 0x10) + lVar9);
            if (*(char *)(lVar2 + 0x60) != '\0') break;
            __fprintf_chk(param_2,2,"  0x%016llx:  %s\n",uVar6,lVar2 + 0x20,lVar2 + 0x60);
            uVar10 = uVar10 + 1;
            lVar9 = lVar9 + 0xe0;
            if (*(uint *)(lVar1 + 0x18) <= uVar10) goto LAB_001487ac;
          }
          __fprintf_chk(param_2,2,"  0x%016llx:  %-10s %s\n",uVar6,lVar2 + 0x20,lVar2 + 0x60);
          uVar10 = uVar10 + 1;
          lVar9 = lVar9 + 0xe0;
        } while (uVar10 < *(uint *)(lVar1 + 0x18));
      }
LAB_001487ac:
      fwrite("  successors:",1,0xd,param_2);
      uVar5 = *(uint *)(param_1 + 3);
      lVar9 = 0;
      uVar10 = 0;
      bVar4 = true;
      if (uVar5 == 0) {
LAB_0014898c:
        fwrite(" (none)",1,7,param_2);
      }
      else {
        local_8 = "BRANCH_TRUE";
LAB_00148850:
        do {
          lVar1 = param_1[2] + lVar9;
          if (*(int *)(param_1[2] + lVar9) == (int)uVar8) {
            if (bVar4) {
              fputc(0x20,param_2);
              iVar3 = *(int *)(lVar1 + 4);
              uVar5 = *(uint *)(lVar1 + 8);
            }
            else {
              fwrite(", ",1,2,param_2);
              iVar3 = *(int *)(lVar1 + 4);
              uVar5 = *(uint *)(lVar1 + 8);
            }
            if (iVar3 == -1) {
              if (uVar5 == 2) {
                pcVar7 = "BRANCH_FALSE";
              }
              else if (uVar5 < 3) {
                pcVar7 = "FALLTHROUGH";
                if (uVar5 != 0) {
                  pcVar7 = "BRANCH_TRUE";
                }
              }
              else if (uVar5 == 3) {
                pcVar7 = "CALL";
              }
              else {
                pcVar7 = "RET";
                if (uVar5 != 4) {
                  pcVar7 = "UNKNOWN";
                }
              }
              __fprintf_chk(param_2,2,"EXTERNAL [%s]",pcVar7);
              uVar10 = uVar10 + 1;
              uVar5 = *(uint *)(param_1 + 3);
              lVar9 = lVar9 + 0xc;
              bVar4 = false;
              if (uVar5 <= uVar10) break;
              goto LAB_00148850;
            }
            if (uVar5 == 2) {
              pcVar7 = "BRANCH_FALSE";
            }
            else if (uVar5 < 3) {
              pcVar7 = "FALLTHROUGH";
              if (uVar5 != 0) {
                pcVar7 = local_8;
              }
            }
            else if (uVar5 == 3) {
              pcVar7 = "CALL";
            }
            else {
              pcVar7 = "RET";
              if (uVar5 != 4) {
                pcVar7 = "UNKNOWN";
              }
            }
            __fprintf_chk(param_2,2,"Block %u [%s]",iVar3,pcVar7);
            uVar5 = *(uint *)(param_1 + 3);
            bVar4 = false;
          }
          uVar10 = uVar10 + 1;
          lVar9 = lVar9 + 0xc;
        } while (uVar10 < uVar5);
        if (bVar4) goto LAB_0014898c;
      }
      fwrite("\n\n",1,2,param_2);
      uVar8 = uVar8 + 1;
    } while ((uint)uVar8 < *(uint *)(param_1 + 1));
  }
  return 0;
}

