
size_t emit_stmt(undefined4 *param_1,FILE *param_2,int param_3)

{
  long lVar1;
  undefined8 *puVar2;
  undefined4 uVar3;
  bool bVar4;
  int iVar5;
  uint uVar6;
  int *piVar7;
  long lVar8;
  ulong uVar9;
  char *pcVar10;
  int *piVar11;
  size_t sVar12;
  long lVar13;
  int iVar14;
  int iVar15;
  
  if (param_1 == (undefined4 *)0x0) {
    return 0;
  }
  switch(*param_1) {
  case 0:
    lVar13 = 0;
    if (param_1[0x28] == 0) {
      uVar9 = 0;
    }
    else {
      do {
        emit_stmt(*(undefined8 *)(*(long *)(param_1 + 0x26) + lVar13 * 8),param_2,param_3);
        piVar7 = *(int **)(*(long *)(param_1 + 0x26) + lVar13 * 8);
        if (((piVar7 != (int *)0x0) && (*piVar7 == 0xc)) &&
           (sVar12 = call_fixup_lookup(piVar7 + 0x26), (int)sVar12 == 1)) {
          return sVar12;
        }
        uVar9 = (ulong)(uint)param_1[0x28];
        lVar13 = lVar13 + 1;
      } while ((uint)lVar13 < (uint)param_1[0x28]);
    }
    return uVar9;
  case 1:
    iVar5 = param_3 + 1;
    iVar14 = 0;
    if (param_3 < 1) {
      fwrite(&DAT_001f9ad8,1,4,param_2);
      emit_expr(*(undefined8 *)(param_1 + 0x26),param_2,0);
      fwrite(&DAT_001f9a38,1,4,param_2);
      emit_stmt(*(undefined8 *)(param_1 + 0x28),param_2,iVar5);
      if (*(long *)(param_1 + 0x2a) != 0) goto LAB_001833a8;
    }
    else {
      do {
        iVar15 = iVar14;
        iVar14 = iVar15 + 1;
        fwrite(&DAT_001fb9d0,1,4,param_2);
      } while (param_3 != iVar14);
      fwrite(&DAT_001f9ad8,1,4,param_2);
      emit_expr(*(undefined8 *)(param_1 + 0x26),param_2,0);
      fwrite(&DAT_001f9a38,1,4,param_2);
      emit_stmt(*(undefined8 *)(param_1 + 0x28),param_2,iVar5);
      if (*(long *)(param_1 + 0x2a) != 0) {
        iVar14 = 0;
        do {
          fwrite(&DAT_001fb9d0,1,4,param_2);
          bVar4 = iVar15 != iVar14;
          iVar14 = iVar14 + 1;
        } while (bVar4);
LAB_001833a8:
        fwrite("} else {\n",1,9,param_2);
        emit_stmt(*(undefined8 *)(param_1 + 0x2a),param_2,iVar5);
        if (param_3 < 1) goto LAB_0018340c;
      }
      iVar5 = 0;
      do {
        iVar5 = iVar5 + 1;
        fwrite(&DAT_001fb9d0,1,4,param_2);
      } while (param_3 != iVar5);
    }
    goto LAB_0018340c;
  case 2:
    iVar5 = 0;
    if (param_3 < 1) {
      fwrite("while (",1,7,param_2);
      emit_expr(*(undefined8 *)(param_1 + 0x26),param_2,0);
      fwrite(&DAT_001f9a38,1,4,param_2);
      emit_stmt(*(undefined8 *)(param_1 + 0x28),param_2,param_3 + 1);
    }
    else {
      do {
        iVar14 = iVar5;
        iVar5 = iVar14 + 1;
        fwrite(&DAT_001fb9d0,1,4,param_2);
      } while (param_3 != iVar5);
      fwrite("while (",1,7,param_2);
      iVar5 = 0;
      emit_expr(*(undefined8 *)(param_1 + 0x26),param_2,0);
      fwrite(&DAT_001f9a38,1,4,param_2);
      emit_stmt(*(undefined8 *)(param_1 + 0x28),param_2,param_3 + 1);
      do {
        fwrite(&DAT_001fb9d0,1,4,param_2);
        bVar4 = iVar14 != iVar5;
        iVar5 = iVar5 + 1;
      } while (bVar4);
    }
    goto LAB_0018340c;
  case 3:
    iVar5 = 0;
    if (param_3 < 1) {
      fwrite("do {\n",1,5,param_2);
      emit_stmt(*(undefined8 *)(param_1 + 0x28),param_2,param_3 + 1);
    }
    else {
      do {
        iVar14 = iVar5;
        iVar5 = iVar14 + 1;
        fwrite(&DAT_001fb9d0,1,4,param_2);
      } while (param_3 != iVar5);
      fwrite("do {\n",1,5,param_2);
      iVar5 = 0;
      emit_stmt(*(undefined8 *)(param_1 + 0x28),param_2,param_3 + 1);
      do {
        fwrite(&DAT_001fb9d0,1,4,param_2);
        bVar4 = iVar14 != iVar5;
        iVar5 = iVar5 + 1;
      } while (bVar4);
    }
    fwrite("} while (",1,9,param_2);
    emit_expr(*(undefined8 *)(param_1 + 0x26),param_2,0);
    pcVar10 = ");\n";
    sVar12 = 3;
    break;
  case 4:
    iVar5 = 0;
    if (0 < param_3) {
      do {
        iVar5 = iVar5 + 1;
        fwrite(&DAT_001fb9d0,1,4,param_2);
      } while (param_3 != iVar5);
    }
    fwrite("for (",1,5,param_2);
    piVar7 = *(int **)(param_1 + 0x26);
    if (piVar7 != (int *)0x0) {
      if (*piVar7 == 10) {
        emit_expr(*(undefined8 *)(piVar7 + 0x26),param_2,0);
        fwrite(&DAT_001f9930,1,3,param_2);
        emit_expr(*(undefined8 *)(*(long *)(param_1 + 0x26) + 0xa0),param_2,0);
      }
      else {
        emit_expr(piVar7,param_2,0);
      }
    }
    fwrite(&DAT_001fc530,1,2,param_2);
    if (*(long *)(param_1 + 0x28) != 0) {
      emit_expr(*(long *)(param_1 + 0x28),param_2,0);
    }
    fwrite(&DAT_001fc530,1,2,param_2);
    piVar7 = *(int **)(param_1 + 0x2a);
    if (piVar7 != (int *)0x0) {
      if (*piVar7 == 10) {
        emit_expr(*(undefined8 *)(piVar7 + 0x26),param_2,0);
        fwrite(&DAT_001f9930,1,3,param_2);
        emit_expr(*(undefined8 *)(*(long *)(param_1 + 0x2a) + 0xa0),param_2,0);
      }
      else {
        emit_expr(piVar7,param_2,0);
      }
    }
    fwrite(&DAT_001f9a38,1,4,param_2);
    emit_stmt(*(undefined8 *)(param_1 + 0x2c),param_2,param_3 + 1);
    if (0 < param_3) {
      iVar5 = 0;
      do {
        iVar5 = iVar5 + 1;
        fwrite(&DAT_001fb9d0,1,4,param_2);
      } while (param_3 != iVar5);
    }
    goto LAB_0018340c;
  case 5:
    iVar5 = 0;
    if (param_3 < 1) {
      fwrite("switch (",1,8,param_2);
      emit_expr(*(undefined8 *)(param_1 + 0x26),param_2,0);
      fwrite(&DAT_001f9a38,1,4,param_2);
      if (param_1[0x2a] != 0) goto LAB_00183098;
    }
    else {
      do {
        iVar5 = iVar5 + 1;
        fwrite(&DAT_001fb9d0,1,4,param_2);
      } while (param_3 != iVar5);
      fwrite("switch (",1,8,param_2);
      emit_expr(*(undefined8 *)(param_1 + 0x26),param_2,0);
      fwrite(&DAT_001f9a38,1,4,param_2);
      if (param_1[0x2a] != 0) {
LAB_00183098:
        uVar6 = 0;
        lVar13 = 0;
        do {
          iVar5 = 0;
          puVar2 = (undefined8 *)(*(long *)(param_1 + 0x28) + lVar13);
          if (0 < param_3) {
            do {
              iVar5 = iVar5 + 1;
              fwrite(&DAT_001fb9d0,1,4,param_2);
            } while (param_3 != iVar5);
          }
          if (*(char *)(puVar2 + 1) == '\0') {
            __fprintf_chk(param_2,2,"case %ld:\n",*puVar2);
          }
          else {
            fwrite("default:\n",1,9,param_2);
          }
          iVar5 = 0;
          emit_stmt(puVar2[2],param_2,param_3 + 1);
          if (-1 < param_3) {
            do {
              iVar5 = iVar5 + 1;
              fwrite(&DAT_001fb9d0,1,4,param_2);
            } while (iVar5 <= param_3);
          }
          fwrite("break;\n",1,7,param_2);
          uVar6 = uVar6 + 1;
          lVar13 = lVar13 + 0x18;
        } while (uVar6 < (uint)param_1[0x2a]);
        if (param_3 < 1) goto LAB_0018340c;
      }
      iVar5 = 0;
      do {
        iVar5 = iVar5 + 1;
        fwrite(&DAT_001fb9d0,1,4,param_2);
      } while (param_3 != iVar5);
    }
LAB_0018340c:
    pcVar10 = "}\n";
    sVar12 = 2;
    break;
  case 6:
    iVar5 = 0;
    if (0 < param_3) {
      do {
        iVar5 = iVar5 + 1;
        fwrite(&DAT_001fb9d0,1,4,param_2);
      } while (param_3 != iVar5);
    }
    uVar3 = param_1[0x26];
    pcVar10 = "goto L_%u;\n";
    goto LAB_00182f70;
  case 7:
    uVar3 = param_1[0x26];
    pcVar10 = "L_%u:\n";
LAB_00182f70:
    sVar12 = __fprintf_chk(param_2,2,pcVar10,uVar3);
    return sVar12;
  case 8:
    iVar5 = 0;
    if (0 < param_3) {
      do {
        iVar5 = iVar5 + 1;
        fwrite(&DAT_001fb9d0,1,4,param_2);
      } while (param_3 != iVar5);
    }
    pcVar10 = "break;\n";
    sVar12 = 7;
    break;
  case 9:
    iVar5 = 0;
    if (0 < param_3) {
      do {
        iVar5 = iVar5 + 1;
        fwrite(&DAT_001fb9d0,1,4,param_2);
      } while (param_3 != iVar5);
    }
    pcVar10 = "continue;\n";
    sVar12 = 10;
    break;
  case 10:
    piVar7 = *(int **)(param_1 + 0x26);
    if (((((piVar7 == (int *)0x0) || (*piVar7 != 0x10)) || (piVar7[0x28] != 3)) ||
        ((piVar11 = *(int **)(piVar7 + 0x26), piVar11 == (int *)0x0 || (*piVar11 != 0xe)))) ||
       (0xff < *(long *)(piVar11 + 0x26) + 0x100U)) {
      iVar5 = 0;
      if (0 < param_3) {
        do {
          iVar5 = iVar5 + 1;
          fwrite(&DAT_001fb9d0,1,4,param_2);
        } while (param_3 != iVar5);
        piVar7 = *(int **)(param_1 + 0x26);
      }
      emit_expr(piVar7,param_2,0);
      fwrite(&DAT_001f9930,1,3,param_2);
      emit_expr(*(undefined8 *)(param_1 + 0x28),param_2,0);
      pcVar10 = ";\n";
      sVar12 = 2;
    }
    else {
      if (0 < param_3) {
        iVar5 = 0;
        do {
          iVar5 = iVar5 + 1;
          fwrite(&DAT_001fb9d0,1,4,param_2);
        } while (param_3 != iVar5);
      }
      pcVar10 = "/* prologue: save to stack */\n";
      sVar12 = 0x1e;
    }
    break;
  case 0xb:
    iVar5 = 0;
    if (0 < param_3) {
      do {
        iVar5 = iVar5 + 1;
        fwrite(&DAT_001fb9d0,1,4,param_2);
      } while (param_3 != iVar5);
    }
    if (*(long *)(param_1 + 0x26) == 0) {
      fwrite("return",1,6,param_2);
    }
    else {
      fwrite("return ",1,7,param_2);
      emit_expr(*(undefined8 *)(param_1 + 0x26),param_2,0);
    }
    pcVar10 = ";\n";
    sVar12 = 2;
    break;
  case 0xc:
    iVar5 = 0;
    if (0 < param_3) {
      do {
        iVar5 = iVar5 + 1;
        fwrite(&DAT_001fb9d0,1,4,param_2);
      } while (param_3 != iVar5);
    }
    __fprintf_chk(param_2,2,&DAT_001fc4a0,param_1 + 0x26);
    lVar13 = 0;
    if (param_1[0x4a] != 0) {
      do {
        if ((int)lVar13 == 0) {
          lVar8 = *(long *)(param_1 + 0x48);
        }
        else {
          fwrite(", ",1,2,param_2);
          lVar8 = *(long *)(param_1 + 0x48);
        }
        lVar1 = lVar13 * 8;
        lVar13 = lVar13 + 1;
        emit_expr(*(undefined8 *)(lVar8 + lVar1),param_2,0);
      } while ((uint)lVar13 < (uint)param_1[0x4a]);
    }
    fwrite(&DAT_001fc6e0,1,2,param_2);
    iVar5 = call_fixup_lookup(param_1 + 0x26);
    if (iVar5 == 1) {
      fwrite(" /* NORETURN */",1,0xf,param_2);
    }
    else if (iVar5 == 2) {
      fwrite(" /* returns-twice */",1,0x14,param_2);
    }
    else if (iVar5 == 3) {
      fwrite(" /* LONGJMP */",1,0xe,param_2);
    }
    uVar6 = fputc(10,param_2);
    return (ulong)uVar6;
  default:
    iVar5 = 0;
    if (0 < param_3) {
      do {
        iVar5 = iVar5 + 1;
        fwrite(&DAT_001fb9d0,1,4,param_2);
      } while (param_3 != iVar5);
    }
    emit_expr(param_1,param_2,0);
    pcVar10 = ";\n";
    sVar12 = 2;
  }
  sVar12 = fwrite(pcVar10,1,sVar12,param_2);
  return sVar12;
}

