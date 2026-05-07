
undefined8 FUN_00157f94(long *param_1,FILE *param_2)

{
  long lVar1;
  long *plVar2;
  bool bVar3;
  uint uVar4;
  long lVar5;
  uint uVar6;
  char *pcVar7;
  long lVar8;
  long lVar9;
  uint uVar10;
  long lVar11;
  long lVar12;
  char *local_10;
  
  if (param_1 == (long *)0x0) {
    return 0;
  }
  if (param_2 == (FILE *)0x0) {
    param_2 = *(FILE **)PTR_stdout_005fff40;
  }
  uVar6 = *(uint *)(param_1 + 1);
  lVar11 = 0;
  uVar10 = 0;
  if (uVar6 != 0) {
    local_10 = "void*";
    do {
      while (lVar1 = *param_1 + lVar11, *(int *)(lVar1 + 0x10) == 0) {
        uVar10 = uVar10 + 1;
        lVar11 = lVar11 + 0x60;
        if (uVar6 <= uVar10) goto LAB_001581ac;
      }
      fwrite("typedef struct {\n",1,0x11,param_2);
      if (*(int *)(lVar1 + 0x10) != 0) {
        uVar6 = 0;
        lVar12 = 0;
        lVar5 = 0;
        do {
          lVar9 = *(long *)(lVar1 + 8);
          plVar2 = (long *)(lVar9 + lVar12);
          lVar8 = *(long *)(lVar9 + lVar12);
          pcVar7 = local_10;
          if (lVar5 < lVar8) {
            __fprintf_chk(param_2,2,"    char _pad%u[%ld];\n",uVar6,lVar8 - lVar5);
            uVar4 = *(uint *)((long)plVar2 + 0xc);
            lVar8 = *(long *)(lVar9 + lVar12);
            bVar3 = false;
            if (uVar4 != 5) goto LAB_001580e0;
          }
          else {
            uVar4 = *(uint *)((long)plVar2 + 0xc);
            bVar3 = uVar4 == 5;
            if (!bVar3) {
LAB_001580e0:
              if (uVar4 < 5 || bVar3) {
                if (uVar4 == 2) {
                  pcVar7 = "int16_t";
                }
                else if (uVar4 == 3) {
                  pcVar7 = "int32_t";
                }
                else {
                  pcVar7 = "int64_t";
                  if (uVar4 == 1) {
                    pcVar7 = "int8_t";
                  }
                }
              }
              else if (uVar4 == 7) {
                pcVar7 = "float";
              }
              else if (uVar4 == 8) {
                pcVar7 = "double";
              }
              else {
                pcVar7 = "int64_t";
                if (uVar4 == 6) {
                  pcVar7 = "int";
                }
              }
            }
          }
          __fprintf_chk(param_2,2,"    %s field_%ld;",pcVar7,lVar8);
          uVar6 = uVar6 + 1;
          lVar12 = lVar12 + 0x18;
          __fprintf_chk(param_2,2,"    /* offset 0x%lx, size %u */\n",*plVar2,(int)plVar2[1]);
          lVar5 = (ulong)*(uint *)(plVar2 + 1) + *plVar2;
        } while (uVar6 < *(uint *)(lVar1 + 0x10));
      }
      uVar10 = uVar10 + 1;
      lVar11 = lVar11 + 0x60;
      __fprintf_chk(param_2,2,"} %s;    /* total size: %u bytes */\n\n",lVar1 + 0x1c,
                    *(undefined4 *)(lVar1 + 0x18));
      uVar6 = *(uint *)(param_1 + 1);
    } while (uVar10 < uVar6);
  }
LAB_001581ac:
  lVar11 = 0;
  if ((int)param_1[3] != 0) {
    do {
      lVar12 = lVar11 * 0x10;
      lVar1 = param_1[2] + lVar12;
      uVar10 = *(uint *)(lVar1 + 8);
      if (uVar10 == 5) {
        pcVar7 = "void*";
      }
      else if (uVar10 < 6) {
        if (uVar10 == 2) {
          pcVar7 = "int16_t";
        }
        else if (uVar10 == 3) {
          pcVar7 = "int32_t";
        }
        else {
          pcVar7 = "int64_t";
          if (uVar10 == 1) {
            pcVar7 = "int8_t";
          }
        }
      }
      else {
        pcVar7 = "float";
        if ((uVar10 != 7) && (pcVar7 = "double", uVar10 != 8)) {
          pcVar7 = "int64_t";
          if (uVar10 == 6) {
            pcVar7 = "int";
          }
        }
      }
      lVar11 = lVar11 + 1;
      __fprintf_chk(param_2,2,"/* array v%u: %s[] (elem size=%u, %u accesses) */\n",
                    *(undefined4 *)(param_1[2] + lVar12),pcVar7,*(undefined4 *)(lVar1 + 4),
                    *(undefined4 *)(lVar1 + 0xc));
    } while ((uint)lVar11 < *(uint *)(param_1 + 3));
  }
  return 0;
}

