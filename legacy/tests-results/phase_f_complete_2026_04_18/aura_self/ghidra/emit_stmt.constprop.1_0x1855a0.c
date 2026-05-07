
size_t emit_stmt_constprop_1(undefined4 *param_1,FILE *param_2)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  long lVar4;
  ulong uVar5;
  char *__ptr;
  size_t sVar6;
  long lVar7;
  long lVar8;
  
  if (param_1 == (undefined4 *)0x0) {
    return 0;
  }
  switch(*param_1) {
  case 0:
    lVar7 = 0;
    if (param_1[0x28] == 0) {
      uVar5 = 0;
    }
    else {
      do {
        emit_stmt(*(undefined8 *)(*(long *)(param_1 + 0x26) + lVar7 * 8),param_2,2);
        piVar3 = *(int **)(*(long *)(param_1 + 0x26) + lVar7 * 8);
        if (((piVar3 != (int *)0x0) && (*piVar3 == 0xc)) &&
           (sVar6 = call_fixup_lookup(piVar3 + 0x26), (int)sVar6 == 1)) {
          return sVar6;
        }
        uVar5 = (ulong)(uint)param_1[0x28];
        lVar7 = lVar7 + 1;
      } while ((uint)lVar7 < (uint)param_1[0x28]);
    }
    return uVar5;
  case 1:
    fwrite(&DAT_001fcb80,1,4,param_2);
    fwrite(&DAT_001fcb80,1,4,param_2);
    fwrite(&DAT_001fac90,1,4,param_2);
    emit_expr(*(undefined8 *)(param_1 + 0x26),param_2,0);
    fwrite(&DAT_001fabf0,1,4,param_2);
    emit_stmt_constprop_2(*(undefined8 *)(param_1 + 0x28),param_2);
    if (*(long *)(param_1 + 0x2a) != 0) {
      fwrite(&DAT_001fcb80,1,4,param_2);
      fwrite(&DAT_001fcb80,1,4,param_2);
      fwrite("} else {\n",1,9,param_2);
      emit_stmt_constprop_2(*(undefined8 *)(param_1 + 0x2a),param_2);
    }
    goto LAB_00185984;
  case 2:
    fwrite(&DAT_001fcb80,1,4,param_2);
    fwrite(&DAT_001fcb80,1,4,param_2);
    fwrite("while (",1,7,param_2);
    emit_expr(*(undefined8 *)(param_1 + 0x26),param_2,0);
    fwrite(&DAT_001fabf0,1,4,param_2);
    emit_stmt_constprop_2(*(undefined8 *)(param_1 + 0x28),param_2);
    fwrite(&DAT_001fcb80,1,4,param_2);
    fwrite(&DAT_001fcb80,1,4,param_2);
    __ptr = "}\n";
    sVar6 = 2;
    break;
  case 3:
    fwrite(&DAT_001fcb80,1,4,param_2);
    fwrite(&DAT_001fcb80,1,4,param_2);
    fwrite("do {\n",1,5,param_2);
    emit_stmt_constprop_2(*(undefined8 *)(param_1 + 0x28),param_2);
    fwrite(&DAT_001fcb80,1,4,param_2);
    fwrite(&DAT_001fcb80,1,4,param_2);
    fwrite("} while (",1,9,param_2);
    emit_expr(*(undefined8 *)(param_1 + 0x26),param_2,0);
    __ptr = ");\n";
    sVar6 = 3;
    break;
  case 4:
    fwrite(&DAT_001fcb80,1,4,param_2);
    fwrite(&DAT_001fcb80,1,4,param_2);
    fwrite("for (",1,5,param_2);
    piVar3 = *(int **)(param_1 + 0x26);
    if (piVar3 != (int *)0x0) {
      if (*piVar3 == 10) {
        emit_expr(*(undefined8 *)(piVar3 + 0x26),param_2,0);
        fwrite(&DAT_001faae8,1,3,param_2);
        emit_expr(*(undefined8 *)(*(long *)(param_1 + 0x26) + 0xa0),param_2,0);
      }
      else {
        emit_expr(piVar3,param_2,0);
      }
    }
    fwrite(&DAT_001fd6f0,1,2,param_2);
    if (*(long *)(param_1 + 0x28) != 0) {
      emit_expr(*(long *)(param_1 + 0x28),param_2,0);
    }
    fwrite(&DAT_001fd6f0,1,2,param_2);
    piVar3 = *(int **)(param_1 + 0x2a);
    if (piVar3 != (int *)0x0) {
      if (*piVar3 == 10) {
        emit_expr(*(undefined8 *)(piVar3 + 0x26),param_2,0);
        fwrite(&DAT_001faae8,1,3,param_2);
        emit_expr(*(undefined8 *)(*(long *)(param_1 + 0x2a) + 0xa0),param_2,0);
      }
      else {
        emit_expr(piVar3,param_2,0);
      }
    }
    fwrite(&DAT_001fabf0,1,4,param_2);
    emit_stmt_constprop_2(*(undefined8 *)(param_1 + 0x2c),param_2);
    fwrite(&DAT_001fcb80,1,4,param_2);
    fwrite(&DAT_001fcb80,1,4,param_2);
    goto LAB_001859c0;
  case 5:
    fwrite(&DAT_001fcb80,1,4,param_2);
    fwrite(&DAT_001fcb80,1,4,param_2);
    fwrite("switch (",1,8,param_2);
    emit_expr(*(undefined8 *)(param_1 + 0x26),param_2,0);
    fwrite(&DAT_001fabf0,1,4,param_2);
    if (param_1[0x2a] != 0) {
      lVar7 = 0;
      uVar2 = 0;
      do {
        lVar8 = *(long *)(param_1 + 0x28);
        lVar4 = lVar8 + lVar7;
        fwrite(&DAT_001fcb80,1,4,param_2);
        fwrite(&DAT_001fcb80,1,4,param_2);
        if (*(char *)(lVar4 + 8) == '\0') {
          __fprintf_chk(param_2,2,"case %ld:\n",*(undefined8 *)(lVar8 + lVar7));
        }
        else {
          fwrite("default:\n",1,9,param_2);
        }
        iVar1 = 3;
        emit_stmt_constprop_2(*(undefined8 *)(lVar4 + 0x10),param_2);
        do {
          fwrite(&DAT_001fcb80,1,4,param_2);
          iVar1 = iVar1 + -1;
        } while (iVar1 != 0);
        fwrite("break;\n",1,7,param_2);
        uVar2 = uVar2 + 1;
        lVar7 = lVar7 + 0x18;
      } while (uVar2 < (uint)param_1[0x2a]);
    }
LAB_00185984:
    fwrite(&DAT_001fcb80,1,4,param_2);
    fwrite(&DAT_001fcb80,1,4,param_2);
LAB_001859c0:
    sVar6 = fwrite(&DAT_001fa020,1,2,param_2);
    return sVar6;
  case 6:
    fwrite(&DAT_001fcb80,1,4,param_2);
    fwrite(&DAT_001fcb80,1,4,param_2);
    sVar6 = __fprintf_chk(param_2,2,"goto L_%u;\n",param_1[0x26]);
    return sVar6;
  case 7:
    sVar6 = __fprintf_chk(param_2,2,"L_%u:\n",param_1[0x26]);
    return sVar6;
  case 8:
    fwrite(&DAT_001fcb80,1,4,param_2);
    fwrite(&DAT_001fcb80,1,4,param_2);
    __ptr = "break;\n";
    sVar6 = 7;
    break;
  case 9:
    fwrite(&DAT_001fcb80,1,4,param_2);
    fwrite(&DAT_001fcb80,1,4,param_2);
    __ptr = "continue;\n";
    sVar6 = 10;
    break;
  case 10:
    piVar3 = *(int **)(param_1 + 0x26);
    if (((((piVar3 == (int *)0x0) || (*piVar3 != 0x10)) || (piVar3[0x28] != 3)) ||
        ((piVar3 = *(int **)(piVar3 + 0x26), piVar3 == (int *)0x0 || (*piVar3 != 0xe)))) ||
       (*(ulong *)(piVar3 + 0x26) < 0xffffffffffffff00)) {
      fwrite(&DAT_001fcb80,1,4,param_2);
      fwrite(&DAT_001fcb80,1,4,param_2);
      emit_expr(*(undefined8 *)(param_1 + 0x26),param_2,0);
      fwrite(&DAT_001faae8,1,3,param_2);
      emit_expr(*(undefined8 *)(param_1 + 0x28),param_2,0);
      __ptr = ";\n";
      sVar6 = 2;
    }
    else {
      fwrite(&DAT_001fcb80,1,4,param_2);
      fwrite(&DAT_001fcb80,1,4,param_2);
      __ptr = "/* prologue: save to stack */\n";
      sVar6 = 0x1e;
    }
    break;
  case 0xb:
    fwrite(&DAT_001fcb80,1,4,param_2);
    fwrite(&DAT_001fcb80,1,4,param_2);
    if (*(long *)(param_1 + 0x26) == 0) {
      fwrite("return",1,6,param_2);
    }
    else {
      fwrite("return ",1,7,param_2);
      emit_expr(*(undefined8 *)(param_1 + 0x26),param_2,0);
    }
    __ptr = ";\n";
    sVar6 = 2;
    break;
  case 0xc:
    fwrite(&DAT_001fcb80,1,4,param_2);
    fwrite(&DAT_001fcb80,1,4,param_2);
    __fprintf_chk(param_2,2,&DAT_001fd660,param_1 + 0x26);
    lVar7 = 0;
    if (param_1[0x4a] != 0) {
      do {
        if ((int)lVar7 == 0) {
          lVar4 = *(long *)(param_1 + 0x48);
        }
        else {
          fwrite(", ",1,2,param_2);
          lVar4 = *(long *)(param_1 + 0x48);
        }
        lVar8 = lVar7 * 8;
        lVar7 = lVar7 + 1;
        emit_expr(*(undefined8 *)(lVar4 + lVar8),param_2,0);
      } while ((uint)lVar7 < (uint)param_1[0x4a]);
    }
    fwrite(&DAT_001fd8a0,1,2,param_2);
    iVar1 = call_fixup_lookup(param_1 + 0x26);
    if (iVar1 == 1) {
      fwrite(" /* NORETURN */",1,0xf,param_2);
    }
    else if (iVar1 == 2) {
      fwrite(" /* returns-twice */",1,0x14,param_2);
    }
    else if (iVar1 == 3) {
      fwrite(" /* LONGJMP */",1,0xe,param_2);
    }
    uVar2 = fputc(10,param_2);
    return (ulong)uVar2;
  default:
    fwrite(&DAT_001fcb80,1,4,param_2);
    fwrite(&DAT_001fcb80,1,4,param_2);
    emit_expr(param_1,param_2,0);
    __ptr = ";\n";
    sVar6 = 2;
  }
  sVar6 = fwrite(__ptr,1,sVar6,param_2);
  return sVar6;
}

