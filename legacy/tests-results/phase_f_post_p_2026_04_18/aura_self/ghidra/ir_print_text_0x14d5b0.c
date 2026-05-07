
undefined8 ir_print_text(long *param_1,FILE *param_2)

{
  long lVar1;
  long lVar2;
  int *piVar3;
  int iVar4;
  undefined8 uVar5;
  char *__s;
  long lVar6;
  long lVar7;
  uint uVar8;
  long lVar9;
  uint uVar10;
  int *piVar11;
  long local_28;
  uint local_4;
  
  if (param_1 == (long *)0x0) {
    uVar5 = 0xfffffffc;
  }
  else {
    if (param_2 == (FILE *)0x0) {
      param_2 = *(FILE **)PTR_stdout_005fff40;
    }
    __fprintf_chk(param_2,2,"IR Function: %s @ 0x%lx\n",param_1 + 4,param_1[3]);
    __fprintf_chk(param_2,2,"  blocks=%u  next_val_id=%u\n",(int)param_1[1],(int)param_1[2]);
    if ((int)param_1[1] != 0) {
      local_28 = 0;
      local_4 = 0;
      do {
        lVar7 = 0;
        lVar2 = *param_1 + local_28;
        __fprintf_chk(param_2,2,"\nbb%u: (preds:",*(undefined4 *)(*param_1 + local_28));
        if (*(int *)(lVar2 + 0x20) != 0) {
          do {
            lVar9 = lVar7 * 4;
            lVar7 = lVar7 + 1;
            __fprintf_chk(param_2,2," %u",*(undefined4 *)(*(long *)(lVar2 + 0x18) + lVar9));
          } while ((uint)lVar7 < *(uint *)(lVar2 + 0x20));
        }
        fwrite("  succs:",1,8,param_2);
        lVar7 = 0;
        if (*(int *)(lVar2 + 0x30) != 0) {
          do {
            lVar9 = lVar7 * 4;
            lVar7 = lVar7 + 1;
            __fprintf_chk(param_2,2," %u",*(undefined4 *)(*(long *)(lVar2 + 0x28) + lVar9));
          } while ((uint)lVar7 < *(uint *)(lVar2 + 0x30));
        }
        lVar7 = 0;
        __fprintf_chk(param_2,2,"  idom=%u)\n",*(undefined4 *)(lVar2 + 0x34));
        uVar8 = 0;
        if (*(int *)(lVar2 + 0x10) != 0) {
          do {
            lVar9 = *(long *)(lVar2 + 8);
            piVar3 = (int *)(lVar9 + lVar7);
            fwrite(&DAT_001f9068,1,2,param_2);
            iVar4 = *(int *)(lVar9 + lVar7);
            if (iVar4 == 0x1b) {
              if (piVar3[2] == -1) {
                fwrite(&DAT_001f9080,1,3,param_2);
              }
              else {
                __fprintf_chk(param_2,2,"v%u = phi");
              }
              lVar9 = 0;
              if (piVar3[0x18] != 0) {
                do {
                  lVar6 = lVar9 * 0x10;
                  lVar1 = lVar9 * 4;
                  lVar9 = lVar9 + 1;
                  __fprintf_chk(param_2,2," [bb%u: v%u]",
                                *(undefined4 *)(*(long *)(piVar3 + 0x16) + lVar1),
                                *(undefined4 *)(*(long *)(piVar3 + 0x14) + lVar6));
                } while ((uint)lVar9 < (uint)piVar3[0x18]);
              }
            }
            else {
              if (piVar3[2] != -1) {
                __fprintf_chk(param_2,2,"v%u = ");
                iVar4 = *piVar3;
              }
              switch(iVar4) {
              case 0:
                __s = "COPY";
                break;
              case 1:
                __s = "CONST";
                break;
              case 2:
                __s = "ADD";
                break;
              case 3:
                __s = "SUB";
                break;
              case 4:
                __s = "MUL";
                break;
              case 5:
                __s = "DIV";
                break;
              case 6:
                __s = "AND";
                break;
              case 7:
                __s = "OR";
                break;
              case 8:
                __s = "XOR";
                break;
              case 9:
                __s = "SHL";
                break;
              case 10:
                __s = "SHR";
                break;
              case 0xb:
                __s = "CMP_EQ";
                break;
              case 0xc:
                __s = "CMP_NE";
                break;
              case 0xd:
                __s = "CMP_LT";
                break;
              case 0xe:
                __s = "CMP_LE";
                break;
              case 0xf:
                __s = "CMP_ULT";
                break;
              case 0x10:
                __s = "CMP_ULE";
                break;
              default:
                __s = "???";
                break;
              case 0x15:
                __s = "LOAD";
                break;
              case 0x16:
                __s = "STORE";
                break;
              case 0x17:
                __s = "BRANCH";
                break;
              case 0x18:
                __s = "JUMP";
                break;
              case 0x19:
                __s = "CALL";
                break;
              case 0x1a:
                __s = "RET";
                break;
              case 0x1b:
                __s = "PHI";
                break;
              case 0x1c:
                fputs("SELECT",param_2);
                iVar4 = *piVar3;
                goto joined_r0x0014d88c;
              }
              fputs(__s,param_2);
              iVar4 = *piVar3;
joined_r0x0014d88c:
              if (iVar4 == 1) {
                __fprintf_chk(param_2,2,&DAT_001f90a0,*(undefined8 *)(piVar3 + 4));
                iVar4 = *piVar3;
                if (iVar4 != 0x17) goto LAB_0014d7e4;
LAB_0014d8b4:
                __fprintf_chk(param_2,2," -> bb%u / bb%u",piVar3[0x19],piVar3[0x1a]);
                lVar9 = *(long *)(piVar3 + 0x1c);
              }
              else {
                if (piVar3[0x12] != 0) {
                  uVar10 = 0;
                  piVar11 = piVar3 + 6;
                  do {
                    uVar10 = uVar10 + 1;
                    __fprintf_chk(param_2,2,&DAT_001f90a8,*piVar11);
                    piVar11 = piVar11 + 4;
                  } while (uVar10 < (uint)piVar3[0x12]);
                  iVar4 = *piVar3;
                }
                if (iVar4 == 0x17) goto LAB_0014d8b4;
LAB_0014d7e4:
                if (iVar4 == 0x18) {
                  __fprintf_chk(param_2,2," -> bb%u",piVar3[0x19]);
                }
                lVar9 = *(long *)(piVar3 + 0x1c);
              }
              if (lVar9 != 0) {
                __fprintf_chk(param_2,2,"  ; 0x%lx");
              }
            }
            fputc(10,param_2);
            uVar8 = uVar8 + 1;
            lVar7 = lVar7 + 0x88;
          } while (uVar8 < *(uint *)(lVar2 + 0x10));
        }
        local_28 = local_28 + 0x50;
        local_4 = local_4 + 1;
      } while (local_4 < *(uint *)(param_1 + 1));
    }
    uVar5 = 0;
  }
  return uVar5;
}

