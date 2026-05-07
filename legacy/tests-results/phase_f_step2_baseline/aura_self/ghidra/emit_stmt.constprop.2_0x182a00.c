
size_t emit_stmt_constprop_2(int *param_1,FILE *param_2)

{
  long lVar1;
  undefined8 *puVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  long lVar6;
  int *piVar7;
  char *__ptr;
  size_t sVar8;
  long lVar9;
  
  if (param_1 == (int *)0x0) {
    return 0;
  }
  iVar4 = *param_1;
  switch(iVar4) {
  case 0:
    uVar5 = 0;
    if (param_1[0x28] != 0) {
      lVar9 = 0;
      do {
        emit_stmt(*(undefined8 *)(*(long *)(param_1 + 0x26) + lVar9 * 8),param_2,3);
        piVar7 = *(int **)(*(long *)(param_1 + 0x26) + lVar9 * 8);
        if (((piVar7 != (int *)0x0) && (*piVar7 == 0xc)) &&
           (sVar8 = call_fixup_lookup(piVar7 + 0x26), (int)sVar8 == 1)) {
          return sVar8;
        }
        uVar5 = param_1[0x28];
        lVar9 = lVar9 + 1;
      } while ((uint)lVar9 < uVar5);
    }
    return (ulong)uVar5;
  case 1:
    iVar4 = 3;
    do {
      fwrite(&DAT_001fa940,1,4,param_2);
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
    fwrite(&DAT_001f8ae0,1,4,param_2);
    emit_expr(*(undefined8 *)(param_1 + 0x26),param_2,0);
    fwrite(&DAT_001f8a40,1,4,param_2);
    emit_stmt(*(undefined8 *)(param_1 + 0x28),param_2,4);
    if (*(long *)(param_1 + 0x2a) != 0) {
      iVar4 = 3;
      do {
        fwrite(&DAT_001fa940,1,4,param_2);
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
      fwrite("} else {\n",1,9,param_2);
      emit_stmt(*(undefined8 *)(param_1 + 0x2a),param_2,4);
    }
    iVar4 = 3;
    do {
      fwrite(&DAT_001fa940,1,4,param_2);
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
    goto LAB_00182d38;
  case 2:
    iVar4 = 3;
    do {
      fwrite(&DAT_001fa940,1,4,param_2);
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
    fwrite("while (",1,7,param_2);
    emit_expr(*(undefined8 *)(param_1 + 0x26),param_2,0);
    fwrite(&DAT_001f8a40,1,4,param_2);
    iVar4 = 3;
    emit_stmt(*(undefined8 *)(param_1 + 0x28),param_2,4);
    do {
      fwrite(&DAT_001fa940,1,4,param_2);
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
    goto LAB_00182d38;
  case 3:
    iVar3 = iVar4;
    do {
      fwrite(&DAT_001fa940,1,4,param_2);
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    fwrite("do {\n",1,5,param_2);
    emit_stmt(*(undefined8 *)(param_1 + 0x28),param_2,4);
    do {
      fwrite(&DAT_001fa940,1,4,param_2);
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
    fwrite("} while (",1,9,param_2);
    emit_expr(*(undefined8 *)(param_1 + 0x26),param_2,0);
    sVar8 = fwrite(&DAT_001f89b0,1,3,param_2);
    return sVar8;
  case 4:
    iVar4 = 3;
    do {
      fwrite(&DAT_001fa940,1,4,param_2);
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
    fwrite("for (",1,5,param_2);
    piVar7 = *(int **)(param_1 + 0x26);
    if (piVar7 != (int *)0x0) {
      if (*piVar7 == 10) {
        emit_expr(*(undefined8 *)(piVar7 + 0x26),param_2,0);
        fwrite(&DAT_001f8938,1,3,param_2);
        emit_expr(*(undefined8 *)(*(long *)(param_1 + 0x26) + 0xa0),param_2,0);
      }
      else {
        emit_expr(piVar7,param_2,0);
      }
    }
    fwrite(&DAT_001fb4b0,1,2,param_2);
    if (*(long *)(param_1 + 0x28) != 0) {
      emit_expr(*(long *)(param_1 + 0x28),param_2,0);
    }
    fwrite(&DAT_001fb4b0,1,2,param_2);
    piVar7 = *(int **)(param_1 + 0x2a);
    if (piVar7 != (int *)0x0) {
      if (*piVar7 == 10) {
        emit_expr(*(undefined8 *)(piVar7 + 0x26),param_2,0);
        fwrite(&DAT_001f8938,1,3,param_2);
        emit_expr(*(undefined8 *)(*(long *)(param_1 + 0x2a) + 0xa0),param_2,0);
      }
      else {
        emit_expr(piVar7,param_2,0);
      }
    }
    fwrite(&DAT_001f8a40,1,4,param_2);
    iVar4 = 3;
    emit_stmt(*(undefined8 *)(param_1 + 0x2c),param_2,4);
    do {
      fwrite(&DAT_001fa940,1,4,param_2);
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
    goto LAB_00182d38;
  case 5:
    iVar4 = 3;
    do {
      fwrite(&DAT_001fa940,1,4,param_2);
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
    fwrite("switch (",1,8,param_2);
    emit_expr(*(undefined8 *)(param_1 + 0x26),param_2,0);
    fwrite(&DAT_001f8a40,1,4,param_2);
    if (param_1[0x2a] != 0) {
      lVar9 = 0;
      uVar5 = 0;
      do {
        iVar4 = 3;
        puVar2 = (undefined8 *)(*(long *)(param_1 + 0x28) + lVar9);
        do {
          fwrite(&DAT_001fa940,1,4,param_2);
          iVar4 = iVar4 + -1;
        } while (iVar4 != 0);
        if (*(char *)(puVar2 + 1) == '\0') {
          __fprintf_chk(param_2,2,"case %ld:\n",*puVar2);
        }
        else {
          fwrite("default:\n",1,9,param_2);
        }
        iVar4 = 4;
        emit_stmt(puVar2[2],param_2,4);
        do {
          fwrite(&DAT_001fa940,1,4,param_2);
          iVar4 = iVar4 + -1;
        } while (iVar4 != 0);
        fwrite("break;\n",1,7,param_2);
        uVar5 = uVar5 + 1;
        lVar9 = lVar9 + 0x18;
      } while (uVar5 < (uint)param_1[0x2a]);
    }
    iVar4 = 3;
    do {
      fwrite(&DAT_001fa940,1,4,param_2);
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
LAB_00182d38:
    sVar8 = fwrite(&DAT_001f7e88,1,2,param_2);
    return sVar8;
  case 6:
    iVar4 = 3;
    do {
      fwrite(&DAT_001fa940,1,4,param_2);
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
    sVar8 = __fprintf_chk(param_2,2,"goto L_%u;\n",param_1[0x26]);
    return sVar8;
  case 7:
    sVar8 = __fprintf_chk(param_2,2,"L_%u:\n",param_1[0x26]);
    return sVar8;
  case 8:
    iVar4 = 3;
    do {
      fwrite(&DAT_001fa940,1,4,param_2);
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
    __ptr = "break;\n";
    sVar8 = 7;
    break;
  case 9:
    iVar4 = 3;
    do {
      fwrite(&DAT_001fa940,1,4,param_2);
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
    __ptr = "continue;\n";
    sVar8 = 10;
    break;
  case 10:
    piVar7 = *(int **)(param_1 + 0x26);
    if (((((piVar7 == (int *)0x0) || (*piVar7 != 0x10)) || (piVar7[0x28] != 3)) ||
        ((piVar7 = *(int **)(piVar7 + 0x26), piVar7 == (int *)0x0 || (*piVar7 != 0xe)))) ||
       (*(ulong *)(piVar7 + 0x26) < 0xffffffffffffff00)) {
      iVar4 = 3;
      do {
        fwrite(&DAT_001fa940,1,4,param_2);
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
      emit_expr(*(undefined8 *)(param_1 + 0x26),param_2,0);
      fwrite(&DAT_001f8938,1,3,param_2);
      emit_expr(*(undefined8 *)(param_1 + 0x28),param_2,0);
      __ptr = ";\n";
      sVar8 = 2;
    }
    else {
      iVar4 = 3;
      do {
        fwrite(&DAT_001fa940,1,4,param_2);
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
      __ptr = "/* prologue: save to stack */\n";
      sVar8 = 0x1e;
    }
    break;
  case 0xb:
    iVar4 = 3;
    do {
      fwrite(&DAT_001fa940,1,4,param_2);
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
    if (*(long *)(param_1 + 0x26) == 0) {
      fwrite("return",1,6,param_2);
    }
    else {
      fwrite("return ",1,7,param_2);
      emit_expr(*(undefined8 *)(param_1 + 0x26),param_2,0);
    }
    __ptr = ";\n";
    sVar8 = 2;
    break;
  case 0xc:
    iVar4 = 3;
    do {
      fwrite(&DAT_001fa940,1,4,param_2);
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
    __fprintf_chk(param_2,2,&DAT_001fb420,param_1 + 0x26);
    if (param_1[0x4a] != 0) {
      lVar9 = 0;
      do {
        if ((int)lVar9 == 0) {
          lVar6 = *(long *)(param_1 + 0x48);
        }
        else {
          fwrite(", ",1,2,param_2);
          lVar6 = *(long *)(param_1 + 0x48);
        }
        lVar1 = lVar9 * 8;
        lVar9 = lVar9 + 1;
        emit_expr(*(undefined8 *)(lVar6 + lVar1),param_2,0);
      } while ((uint)lVar9 < (uint)param_1[0x4a]);
    }
    fwrite(&DAT_001fb660,1,2,param_2);
    iVar4 = call_fixup_lookup(param_1 + 0x26);
    if (iVar4 == 1) {
      fwrite(" /* NORETURN */",1,0xf,param_2);
    }
    else if (iVar4 == 2) {
      fwrite(" /* returns-twice */",1,0x14,param_2);
    }
    else if (iVar4 == 3) {
      fwrite(" /* LONGJMP */",1,0xe,param_2);
    }
    uVar5 = fputc(10,param_2);
    return (ulong)uVar5;
  default:
    iVar4 = 3;
    do {
      fwrite(&DAT_001fa940,1,4,param_2);
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
    emit_expr(param_1,param_2,0);
    __ptr = ";\n";
    sVar8 = 2;
  }
  sVar8 = fwrite(__ptr,1,sVar8,param_2);
  return sVar8;
}

