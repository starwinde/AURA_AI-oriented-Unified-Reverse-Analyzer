
/* WARNING: Type propagation algorithm not settling */

void cf_emit_block_body_part_0_isra_0(long param_1,ulong param_2,FILE *param_3,int param_4)

{
  uint *puVar1;
  uint uVar2;
  char *pcVar3;
  int iVar4;
  long lVar5;
  uint uVar6;
  uint uVar7;
  long lVar8;
  
  param_1 = param_1 + (param_2 & 0xffffffff) * 0x50;
  uVar7 = *(uint *)(param_1 + 0x10);
  if (uVar7 != 0) {
    lVar5 = 0;
    uVar6 = 0;
    do {
      while( true ) {
        puVar1 = (uint *)(*(long *)(param_1 + 8) + lVar5);
        uVar2 = *(uint *)(*(long *)(param_1 + 8) + lVar5);
        if (1 < uVar2 - 0x17 && (uVar2 != 0x1a && uVar2 != 0x1b)) break;
LAB_0015b270:
        uVar6 = uVar6 + 1;
        lVar5 = lVar5 + 0x88;
        if (uVar7 <= uVar6) {
          return;
        }
      }
      if (0 < param_4) {
        iVar4 = 0;
        do {
          iVar4 = iVar4 + 1;
          fputc(0x20,param_3);
        } while (iVar4 < param_4 * 4);
        uVar2 = *puVar1;
      }
      if (uVar2 == 0x15) {
        if (puVar1[2] == 0xffffffff) {
          fwrite("__undef",1,7,param_3);
        }
        else {
          __fprintf_chk(param_3,2,&DAT_001fa488);
        }
        switch(puVar1[3]) {
        case 0:
          pcVar3 = "void";
          break;
        case 1:
          pcVar3 = "int8_t";
          break;
        case 2:
          pcVar3 = "int16_t";
          break;
        case 3:
          pcVar3 = "int32_t";
          break;
        default:
          pcVar3 = "int64_t";
          break;
        case 5:
          pcVar3 = "void*";
          break;
        case 6:
          pcVar3 = "int";
          break;
        case 7:
          pcVar3 = "float";
          break;
        case 8:
          pcVar3 = "double";
          break;
        case 9:
          pcVar3 = "long double";
          break;
        case 10:
          pcVar3 = "__m128";
          break;
        case 0xb:
          pcVar3 = "__m256";
          break;
        case 0xc:
          pcVar3 = "__m512";
          break;
        case 0xd:
          pcVar3 = "__m64";
        }
        __fprintf_chk(param_3,2," = *(%s*)addr;\n",pcVar3);
        uVar7 = *(uint *)(param_1 + 0x10);
        goto LAB_0015b270;
      }
      if (0x15 < uVar2) {
        if (uVar2 != 0x19) {
          if (uVar2 == 0x1c) {
            if (2 < puVar1[0x12]) {
              if (puVar1[2] == 0xffffffff) {
                fwrite("__undef",1,7,param_3);
              }
              else {
                __fprintf_chk(param_3,2,&DAT_001fa488);
              }
              fwrite(&DAT_001fa490,1,3,param_3);
              if (puVar1[6] == 0xffffffff) {
                fwrite("__undef",1,7,param_3);
              }
              else {
                __fprintf_chk(param_3,2,&DAT_001fa488);
              }
              fwrite(&DAT_001fa4b8,1,3,param_3);
              if (puVar1[10] == 0xffffffff) {
                fwrite("__undef",1,7,param_3);
              }
              else {
                __fprintf_chk(param_3,2,&DAT_001fa488);
              }
              fwrite(&DAT_001f9450,1,3,param_3);
              uVar7 = puVar1[0xe];
              goto joined_r0x0015b5a0;
            }
          }
          else if ((uVar2 == 0x16) && (1 < puVar1[0x12])) {
            switch(puVar1[0xb]) {
            case 0:
              pcVar3 = "void";
              break;
            case 1:
              pcVar3 = "int8_t";
              break;
            case 2:
              pcVar3 = "int16_t";
              break;
            case 3:
              pcVar3 = "int32_t";
              break;
            default:
              pcVar3 = "int64_t";
              break;
            case 5:
              pcVar3 = "void*";
              break;
            case 6:
              pcVar3 = "int";
              break;
            case 7:
              pcVar3 = "float";
              break;
            case 8:
              pcVar3 = "double";
              break;
            case 9:
              pcVar3 = "long double";
              break;
            case 10:
              pcVar3 = "__m128";
              break;
            case 0xb:
              pcVar3 = "__m256";
              break;
            case 0xc:
              pcVar3 = "__m512";
              break;
            case 0xd:
              pcVar3 = "__m64";
            }
            __fprintf_chk(param_3,2,"*(%s*)addr = ",pcVar3);
            uVar7 = puVar1[10];
            goto joined_r0x0015b5a0;
          }
          goto LAB_0015b2ec;
        }
        if (puVar1[2] == 0xffffffff) {
          fwrite("__undef",1,7,param_3);
        }
        else {
          __fprintf_chk(param_3,2,&DAT_001fa488);
        }
        if ((puVar1[0x12] == 0) || (*(long *)(puVar1 + 8) == 0)) {
          fwrite(" = call(",1,8,param_3);
        }
        else {
          __fprintf_chk(param_3,2," = sub_%lx(");
        }
        lVar8 = 0;
        if (puVar1[0x18] != 0) {
          do {
            uVar7 = (uint)lVar8;
            while( true ) {
              if (uVar7 != 0) {
                fwrite(", ",1,2,param_3);
              }
              if (*(int *)(*(long *)(puVar1 + 0x14) + lVar8 * 0x10) != -1) break;
              lVar8 = lVar8 + 1;
              fwrite("__undef",1,7,param_3);
              uVar7 = (uint)lVar8;
              if (puVar1[0x18] <= uVar7) goto LAB_0015b648;
            }
            __fprintf_chk(param_3,2,&DAT_001fa488);
            lVar8 = lVar8 + 1;
          } while ((uint)lVar8 < puVar1[0x18]);
        }
LAB_0015b648:
        fwrite(&DAT_001fa508,1,3,param_3);
        uVar7 = *(uint *)(param_1 + 0x10);
        goto LAB_0015b270;
      }
      if (uVar2 == 1) {
        if (puVar1[2] == 0xffffffff) {
          fwrite("__undef",1,7,param_3);
        }
        else {
          __fprintf_chk(param_3,2,&DAT_001fa488);
        }
        __fprintf_chk(param_3,2," = %ldLL;\n",*(undefined8 *)(puVar1 + 4));
        uVar7 = *(uint *)(param_1 + 0x10);
        goto LAB_0015b270;
      }
      if (uVar2 < 2) {
        if (puVar1[0x12] == 0) goto LAB_0015b2ec;
        if (puVar1[2] == 0xffffffff) {
          fwrite("__undef",1,7,param_3);
        }
        else {
          __fprintf_chk(param_3,2,&DAT_001fa488);
        }
        fwrite(&DAT_001fa490,1,3,param_3);
        uVar7 = puVar1[6];
joined_r0x0015b5a0:
        if (uVar7 == 0xffffffff) {
          fwrite("__undef",1,7,param_3);
        }
        else {
          __fprintf_chk(param_3,2,&DAT_001fa488);
        }
        fwrite(";\n",1,2,param_3);
        uVar7 = *(uint *)(param_1 + 0x10);
      }
      else {
        if (1 < puVar1[0x12]) {
          if (puVar1[2] == 0xffffffff) {
            fwrite("__undef",1,7,param_3);
          }
          else {
            __fprintf_chk(param_3,2,&DAT_001fa488);
          }
          fwrite(&DAT_001fa490,1,3,param_3);
          if (puVar1[6] == 0xffffffff) {
            fwrite("__undef",1,7,param_3);
          }
          else {
            __fprintf_chk(param_3,2,&DAT_001fa488);
          }
          cf_binop_str(*puVar1);
          __fprintf_chk(param_3,2);
          uVar7 = puVar1[10];
          goto joined_r0x0015b5a0;
        }
LAB_0015b2ec:
        uVar7 = *(uint *)(param_1 + 0x10);
      }
      uVar6 = uVar6 + 1;
      lVar5 = lVar5 + 0x88;
    } while (uVar6 < uVar7);
  }
  return;
}

