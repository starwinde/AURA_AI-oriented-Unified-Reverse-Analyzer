
/* WARNING: Type propagation algorithm not settling */

void FUN_0015b360(long param_1,ulong param_2,FILE *param_3)

{
  uint *puVar1;
  char *pcVar2;
  int iVar3;
  uint uVar4;
  long lVar5;
  long lVar6;
  uint uVar7;
  
  param_1 = param_1 + (param_2 & 0xffffffff) * 0x50;
  uVar4 = *(uint *)(param_1 + 0x10);
  if (uVar4 != 0) {
    lVar6 = 0;
    uVar7 = 0;
    do {
      while( true ) {
        puVar1 = (uint *)(*(long *)(param_1 + 8) + lVar6);
        iVar3 = *(int *)(*(long *)(param_1 + 8) + lVar6);
        if (1 < iVar3 - 0x17U && (iVar3 != 0x1a && iVar3 != 0x1b)) break;
LAB_0015b3a0:
        uVar7 = uVar7 + 1;
        lVar6 = lVar6 + 0x90;
        if (uVar4 <= uVar7) {
          return;
        }
      }
      iVar3 = 4;
      do {
        fputc(0x20,param_3);
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
      uVar4 = *puVar1;
      if (uVar4 == 0x15) {
        if (puVar1[2] == 0xffffffff) {
          fwrite("__undef",1,7,param_3);
        }
        else {
          __fprintf_chk(param_3,2,&DAT_001faad0);
        }
        switch(puVar1[3]) {
        case 0:
          pcVar2 = "void";
          break;
        case 1:
          pcVar2 = "int8_t";
          break;
        case 2:
          pcVar2 = "int16_t";
          break;
        case 3:
          pcVar2 = "int32_t";
          break;
        default:
          pcVar2 = "int64_t";
          break;
        case 5:
          pcVar2 = "void*";
          break;
        case 6:
          pcVar2 = "int";
          break;
        case 7:
          pcVar2 = "float";
          break;
        case 8:
          pcVar2 = "double";
          break;
        case 9:
          pcVar2 = "long double";
          break;
        case 10:
          pcVar2 = "__m128";
          break;
        case 0xb:
          pcVar2 = "__m256";
          break;
        case 0xc:
          pcVar2 = "__m512";
          break;
        case 0xd:
          pcVar2 = "__m64";
        }
        __fprintf_chk(param_3,2," = *(%s*)addr;\n",pcVar2);
        uVar4 = *(uint *)(param_1 + 0x10);
        goto LAB_0015b3a0;
      }
      if (0x15 < uVar4) {
        if (uVar4 != 0x19) {
          if (uVar4 == 0x1c) {
            if (2 < puVar1[0x12]) {
              if (puVar1[2] == 0xffffffff) {
                fwrite("__undef",1,7,param_3);
              }
              else {
                __fprintf_chk(param_3,2,&DAT_001faad0);
              }
              fwrite(&DAT_001faad8,1,3,param_3);
              if (puVar1[6] == 0xffffffff) {
                fwrite("__undef",1,7,param_3);
              }
              else {
                __fprintf_chk(param_3,2,&DAT_001faad0);
              }
              fwrite(&DAT_001fab00,1,3,param_3);
              if (puVar1[10] == 0xffffffff) {
                fwrite("__undef",1,7,param_3);
              }
              else {
                __fprintf_chk(param_3,2,&DAT_001faad0);
              }
              fwrite(&DAT_001f9a30,1,3,param_3);
              uVar4 = puVar1[0xe];
              goto joined_r0x0015b6c0;
            }
          }
          else if ((uVar4 == 0x16) && (1 < puVar1[0x12])) {
            switch(puVar1[0xb]) {
            case 0:
              pcVar2 = "void";
              break;
            case 1:
              pcVar2 = "int8_t";
              break;
            case 2:
              pcVar2 = "int16_t";
              break;
            case 3:
              pcVar2 = "int32_t";
              break;
            default:
              pcVar2 = "int64_t";
              break;
            case 5:
              pcVar2 = "void*";
              break;
            case 6:
              pcVar2 = "int";
              break;
            case 7:
              pcVar2 = "float";
              break;
            case 8:
              pcVar2 = "double";
              break;
            case 9:
              pcVar2 = "long double";
              break;
            case 10:
              pcVar2 = "__m128";
              break;
            case 0xb:
              pcVar2 = "__m256";
              break;
            case 0xc:
              pcVar2 = "__m512";
              break;
            case 0xd:
              pcVar2 = "__m64";
            }
            __fprintf_chk(param_3,2,"*(%s*)addr = ",pcVar2);
            uVar4 = puVar1[10];
            goto joined_r0x0015b6c0;
          }
          goto LAB_0015b410;
        }
        if (puVar1[2] == 0xffffffff) {
          fwrite("__undef",1,7,param_3);
        }
        else {
          __fprintf_chk(param_3,2,&DAT_001faad0);
        }
        if ((puVar1[0x12] == 0) || (*(long *)(puVar1 + 8) == 0)) {
          fwrite(" = call(",1,8,param_3);
        }
        else {
          __fprintf_chk(param_3,2," = sub_%lx(");
        }
        lVar5 = 0;
        if (puVar1[0x18] != 0) {
          do {
            uVar4 = (uint)lVar5;
            while( true ) {
              if (uVar4 != 0) {
                fwrite(", ",1,2,param_3);
              }
              if (*(int *)(*(long *)(puVar1 + 0x14) + lVar5 * 0x10) != -1) break;
              fwrite("__undef",1,7,param_3);
              lVar5 = lVar5 + 1;
              uVar4 = (uint)lVar5;
              if (puVar1[0x18] <= uVar4) goto LAB_0015b76c;
            }
            __fprintf_chk(param_3,2,&DAT_001faad0);
            lVar5 = lVar5 + 1;
          } while ((uint)lVar5 < puVar1[0x18]);
        }
LAB_0015b76c:
        fwrite(&DAT_001fab50,1,3,param_3);
        uVar4 = *(uint *)(param_1 + 0x10);
        goto LAB_0015b3a0;
      }
      if (uVar4 == 1) {
        if (puVar1[2] == 0xffffffff) {
          fwrite("__undef",1,7,param_3);
        }
        else {
          __fprintf_chk(param_3,2,&DAT_001faad0);
        }
        __fprintf_chk(param_3,2," = %ldLL;\n",*(undefined8 *)(puVar1 + 4));
        uVar4 = *(uint *)(param_1 + 0x10);
        goto LAB_0015b3a0;
      }
      if (uVar4 < 2) {
        if (puVar1[0x12] == 0) goto LAB_0015b410;
        if (puVar1[2] == 0xffffffff) {
          fwrite("__undef",1,7,param_3);
        }
        else {
          __fprintf_chk(param_3,2,&DAT_001faad0);
        }
        fwrite(&DAT_001faad8,1,3,param_3);
        uVar4 = puVar1[6];
joined_r0x0015b6c0:
        if (uVar4 == 0xffffffff) {
          fwrite("__undef",1,7,param_3);
        }
        else {
          __fprintf_chk(param_3,2,&DAT_001faad0);
        }
        fwrite(";\n",1,2,param_3);
        uVar4 = *(uint *)(param_1 + 0x10);
      }
      else {
        if (1 < puVar1[0x12]) {
          if (puVar1[2] == 0xffffffff) {
            fwrite("__undef",1,7,param_3);
          }
          else {
            __fprintf_chk(param_3,2,&DAT_001faad0);
          }
          fwrite(&DAT_001faad8,1,3,param_3);
          if (puVar1[6] == 0xffffffff) {
            fwrite("__undef",1,7,param_3);
          }
          else {
            __fprintf_chk(param_3,2,&DAT_001faad0);
          }
          FUN_0015a9d0(*puVar1);
          __fprintf_chk(param_3,2);
          uVar4 = puVar1[10];
          goto joined_r0x0015b6c0;
        }
LAB_0015b410:
        uVar4 = *(uint *)(param_1 + 0x10);
      }
      uVar7 = uVar7 + 1;
      lVar6 = lVar6 + 0x90;
    } while (uVar7 < uVar4);
  }
  return;
}

