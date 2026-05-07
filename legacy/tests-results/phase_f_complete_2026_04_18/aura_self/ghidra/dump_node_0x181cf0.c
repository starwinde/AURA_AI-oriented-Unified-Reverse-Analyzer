
void dump_node(undefined4 *param_1,FILE *param_2,int param_3)

{
  undefined4 uVar1;
  bool bVar2;
  char *pcVar3;
  size_t __n;
  int iVar4;
  int iVar5;
  long lVar6;
  long lVar7;
  
  if (param_1 == (undefined4 *)0x0) {
    return;
  }
  switch(*param_1) {
  case 0:
    lVar7 = 0;
    if (param_1[0x28] != 0) {
      do {
        lVar6 = lVar7 * 8;
        lVar7 = lVar7 + 1;
        dump_node(*(undefined8 *)(*(long *)(param_1 + 0x26) + lVar6),param_2,param_3);
      } while ((uint)lVar7 < (uint)param_1[0x28]);
    }
    return;
  case 1:
    iVar5 = param_3 * 2;
    param_3 = param_3 + 1;
    iVar4 = 0;
    if (iVar5 < 1) {
      fwrite(&DAT_001fd6b8,1,4,param_2);
      dump_expr(*(undefined8 *)(param_1 + 0x26),param_2);
      fwrite(&DAT_001fabf0,1,4,param_2);
      dump_node(*(undefined8 *)(param_1 + 0x28),param_2,param_3);
      if (*(long *)(param_1 + 0x2a) == 0) break;
LAB_00182390:
      fwrite("} ELSE {\n",1,9,param_2);
      dump_node(*(undefined8 *)(param_1 + 0x2a),param_2,param_3);
      if (iVar5 < 1) break;
    }
    else {
      do {
        iVar4 = iVar4 + 1;
        fputc(0x20,param_2);
      } while (iVar4 != iVar5);
      fwrite(&DAT_001fd6b8,1,4,param_2);
      dump_expr(*(undefined8 *)(param_1 + 0x26),param_2);
      fwrite(&DAT_001fabf0,1,4,param_2);
      dump_node(*(undefined8 *)(param_1 + 0x28),param_2,param_3);
      if (*(long *)(param_1 + 0x2a) != 0) {
        iVar4 = 0;
        do {
          iVar4 = iVar4 + 1;
          fputc(0x20,param_2);
        } while (iVar4 != iVar5);
        goto LAB_00182390;
      }
    }
    iVar4 = 0;
    do {
      iVar4 = iVar4 + 1;
      fputc(0x20,param_2);
    } while (iVar4 != iVar5);
    break;
  case 2:
    iVar4 = 0;
    if (param_3 < 1) {
      fwrite("WHILE (",1,7,param_2);
      dump_expr(*(undefined8 *)(param_1 + 0x26),param_2);
      fwrite(&DAT_001fabf0,1,4,param_2);
      dump_node(*(undefined8 *)(param_1 + 0x28),param_2,param_3 + 1);
    }
    else {
      do {
        iVar4 = iVar4 + 1;
        fputc(0x20,param_2);
      } while (iVar4 != param_3 * 2);
      fwrite("WHILE (",1,7,param_2);
      dump_expr(*(undefined8 *)(param_1 + 0x26),param_2);
      fwrite(&DAT_001fabf0,1,4,param_2);
      iVar4 = 0;
      dump_node(*(undefined8 *)(param_1 + 0x28),param_2,param_3 + 1);
      do {
        iVar4 = iVar4 + 1;
        fputc(0x20,param_2);
      } while (iVar4 != param_3 * 2);
    }
    break;
  case 3:
    iVar4 = 0;
    if (param_3 < 1) {
      fwrite("DO {\n",1,5,param_2);
      dump_node(*(undefined8 *)(param_1 + 0x28),param_2,param_3 + 1);
    }
    else {
      do {
        iVar5 = iVar4;
        iVar4 = iVar5 + 1;
        fputc(0x20,param_2);
      } while (param_3 << 1 != iVar4);
      fwrite("DO {\n",1,5,param_2);
      iVar4 = 0;
      dump_node(*(undefined8 *)(param_1 + 0x28),param_2,param_3 + 1);
      do {
        fputc(0x20,param_2);
        bVar2 = iVar5 != iVar4;
        iVar4 = iVar4 + 1;
      } while (bVar2);
    }
    fwrite("} WHILE (",1,9,param_2);
    dump_expr(*(undefined8 *)(param_1 + 0x26),param_2);
    pcVar3 = ")\n";
    __n = 2;
    goto LAB_00181d64;
  case 4:
    iVar5 = param_3 * 2;
    iVar4 = 0;
    if (0 < iVar5) {
      do {
        iVar4 = iVar4 + 1;
        fputc(0x20,param_2);
      } while (iVar4 != iVar5);
    }
    fwrite("FOR (",1,5,param_2);
    if (*(long *)(param_1 + 0x26) != 0) {
      dump_expr(*(long *)(param_1 + 0x26),param_2);
    }
    fwrite(&DAT_001fd6f0,1,2,param_2);
    dump_expr(*(undefined8 *)(param_1 + 0x28),param_2);
    fwrite(&DAT_001fd6f0,1,2,param_2);
    if (*(long *)(param_1 + 0x2a) != 0) {
      dump_expr(*(long *)(param_1 + 0x2a),param_2);
    }
    fwrite(&DAT_001fabf0,1,4,param_2);
    dump_node(*(undefined8 *)(param_1 + 0x2c),param_2,param_3 + 1);
    if (0 < iVar5) {
      iVar4 = 0;
      do {
        iVar4 = iVar4 + 1;
        fputc(0x20,param_2);
      } while (iVar4 != iVar5);
    }
    break;
  case 5:
    iVar5 = param_3 * 2;
    iVar4 = 0;
    if (iVar5 < 1) {
      fwrite("SWITCH (",1,8,param_2);
      dump_expr(*(undefined8 *)(param_1 + 0x26),param_2);
      fwrite(&DAT_001fabf0,1,4,param_2);
      if (param_1[0x2a] == 0) break;
LAB_00181fcc:
      lVar7 = 0;
      do {
        iVar4 = 0;
        if (-1 < param_3) {
          do {
            iVar4 = iVar4 + 1;
            fputc(0x20,param_2);
          } while ((param_3 + 1) * 2 != iVar4);
        }
        lVar6 = lVar7 * 0x18;
        if (*(char *)(*(long *)(param_1 + 0x28) + lVar6 + 8) == '\0') {
          __fprintf_chk(param_2,2,"CASE %ld:\n",
                        *(undefined8 *)(*(long *)(param_1 + 0x28) + lVar7 * 0x18));
        }
        else {
          fwrite("DEFAULT:\n",1,9,param_2);
        }
        lVar7 = lVar7 + 1;
        dump_node(*(undefined8 *)(*(long *)(param_1 + 0x28) + lVar6 + 0x10),param_2,param_3 + 2);
      } while ((uint)lVar7 < (uint)param_1[0x2a]);
      if (iVar5 < 1) break;
    }
    else {
      do {
        iVar4 = iVar4 + 1;
        fputc(0x20,param_2);
      } while (iVar4 != iVar5);
      fwrite("SWITCH (",1,8,param_2);
      dump_expr(*(undefined8 *)(param_1 + 0x26),param_2);
      fwrite(&DAT_001fabf0,1,4,param_2);
      if (param_1[0x2a] != 0) goto LAB_00181fcc;
    }
    iVar4 = 0;
    do {
      iVar4 = iVar4 + 1;
      fputc(0x20,param_2);
    } while (iVar5 != iVar4);
    break;
  case 6:
    iVar4 = 0;
    if (0 < param_3) {
      do {
        iVar4 = iVar4 + 1;
        fputc(0x20,param_2);
      } while (param_3 << 1 != iVar4);
    }
    uVar1 = param_1[0x26];
    pcVar3 = "GOTO L_%u;\n";
    goto LAB_00181f0c;
  case 7:
    iVar4 = 0;
    if (0 < param_3) {
      do {
        iVar4 = iVar4 + 1;
        fputc(0x20,param_2);
      } while (iVar4 != param_3 * 2);
    }
    uVar1 = param_1[0x26];
    pcVar3 = "L_%u:\n";
LAB_00181f0c:
    __fprintf_chk(param_2,2,pcVar3,uVar1);
    return;
  case 8:
    iVar4 = 0;
    if (0 < param_3) {
      do {
        iVar4 = iVar4 + 1;
        fputc(0x20,param_2);
      } while (iVar4 != param_3 * 2);
    }
    pcVar3 = "BREAK;\n";
    __n = 7;
    goto LAB_00181d64;
  case 9:
    iVar4 = 0;
    if (0 < param_3) {
      do {
        iVar4 = iVar4 + 1;
        fputc(0x20,param_2);
      } while (iVar4 != param_3 * 2);
    }
    pcVar3 = "CONTINUE;\n";
    __n = 10;
    goto LAB_00181d64;
  case 10:
    iVar4 = 0;
    if (0 < param_3) {
      do {
        iVar4 = iVar4 + 1;
        fputc(0x20,param_2);
      } while (iVar4 != param_3 * 2);
    }
    dump_expr(*(undefined8 *)(param_1 + 0x26),param_2);
    fwrite(&DAT_001faae8,1,3,param_2);
    param_1 = *(undefined4 **)(param_1 + 0x28);
    goto LAB_00181d50;
  case 0xb:
    iVar4 = 0;
    if (0 < param_3) {
      do {
        iVar4 = iVar4 + 1;
        fputc(0x20,param_2);
      } while (iVar4 != param_3 * 2);
    }
    fwrite("RETURN",1,6,param_2);
    if (*(long *)(param_1 + 0x26) != 0) {
      fputc(0x20,param_2);
      param_1 = *(undefined4 **)(param_1 + 0x26);
      goto LAB_00181d50;
    }
    goto LAB_00181d54;
  case 0xc:
    iVar4 = 0;
    if (0 < param_3) {
      do {
        iVar4 = iVar4 + 1;
        fputc(0x20,param_2);
      } while (param_3 << 1 != iVar4);
    }
    goto LAB_00181d50;
  default:
    iVar4 = 0;
    if (0 < param_3) {
      do {
        iVar4 = iVar4 + 1;
        fputc(0x20,param_2);
      } while (iVar4 != param_3 * 2);
    }
LAB_00181d50:
    dump_expr(param_1,param_2);
LAB_00181d54:
    pcVar3 = ";\n";
    __n = 2;
LAB_00181d64:
    fwrite(pcVar3,1,__n,param_2);
    return;
  }
  fwrite(&DAT_001fa020,1,2,param_2);
  return;
}

