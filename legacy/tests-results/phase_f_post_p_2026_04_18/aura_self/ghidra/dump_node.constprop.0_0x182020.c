
void dump_node_constprop_0(undefined4 *param_1,FILE *param_2)

{
  long lVar1;
  char *__ptr;
  undefined8 uVar2;
  size_t __n;
  int iVar3;
  long lVar4;
  uint uVar5;
  
  if (param_1 == (undefined4 *)0x0) {
    return;
  }
  switch(*param_1) {
  case 0:
    lVar4 = 0;
    if (param_1[0x28] != 0) {
      do {
        lVar1 = lVar4 * 8;
        lVar4 = lVar4 + 1;
        dump_node_constprop_0(*(undefined8 *)(*(long *)(param_1 + 0x26) + lVar1),param_2);
      } while ((uint)lVar4 < (uint)param_1[0x28]);
    }
    return;
  case 1:
    fputc(0x20,param_2);
    fputc(0x20,param_2);
    fwrite(&DAT_001fc138,1,4,param_2);
    dump_expr(*(undefined8 *)(param_1 + 0x26),param_2);
    fwrite(&DAT_001f9680,1,4,param_2);
    dump_node(*(undefined8 *)(param_1 + 0x28),param_2,2);
    if (*(long *)(param_1 + 0x2a) != 0) {
      fputc(0x20,param_2);
      fputc(0x20,param_2);
      fwrite("} ELSE {\n",1,9,param_2);
      dump_node(*(undefined8 *)(param_1 + 0x2a),param_2,2);
    }
    goto LAB_001822cc;
  case 2:
    fputc(0x20,param_2);
    fputc(0x20,param_2);
    fwrite("WHILE (",1,7,param_2);
    dump_expr(*(undefined8 *)(param_1 + 0x26),param_2);
    fwrite(&DAT_001f9680,1,4,param_2);
    uVar2 = *(undefined8 *)(param_1 + 0x28);
    goto LAB_001824a4;
  case 3:
    fputc(0x20,param_2);
    fputc(0x20,param_2);
    fwrite("DO {\n",1,5,param_2);
    dump_node(*(undefined8 *)(param_1 + 0x28),param_2,2);
    fputc(0x20,param_2);
    fputc(0x20,param_2);
    fwrite("} WHILE (",1,9,param_2);
    dump_expr(*(undefined8 *)(param_1 + 0x26),param_2);
    __ptr = ")\n";
    __n = 2;
    break;
  case 4:
    fputc(0x20,param_2);
    fputc(0x20,param_2);
    fwrite("FOR (",1,5,param_2);
    if (*(long *)(param_1 + 0x26) != 0) {
      dump_expr(*(long *)(param_1 + 0x26),param_2);
    }
    fwrite(&DAT_001fc170,1,2,param_2);
    dump_expr(*(undefined8 *)(param_1 + 0x28),param_2);
    fwrite(&DAT_001fc170,1,2,param_2);
    if (*(long *)(param_1 + 0x2a) != 0) {
      dump_expr(*(long *)(param_1 + 0x2a),param_2);
    }
    fwrite(&DAT_001f9680,1,4,param_2);
    uVar2 = *(undefined8 *)(param_1 + 0x2c);
LAB_001824a4:
    dump_node(uVar2,param_2,2);
    fputc(0x20,param_2);
    fputc(0x20,param_2);
    fwrite(&DAT_001f8ab0,1,2,param_2);
    return;
  case 5:
    fputc(0x20,param_2);
    fputc(0x20,param_2);
    fwrite("SWITCH (",1,8,param_2);
    lVar4 = 0;
    uVar5 = 0;
    dump_expr(*(undefined8 *)(param_1 + 0x26),param_2);
    fwrite(&DAT_001f9680,1,4,param_2);
    if (param_1[0x2a] != 0) {
      do {
        iVar3 = 4;
        do {
          fputc(0x20,param_2);
          iVar3 = iVar3 + -1;
        } while (iVar3 != 0);
        if (*(char *)(*(long *)(param_1 + 0x28) + lVar4 + 8) == '\0') {
          __fprintf_chk(param_2,2,"CASE %ld:\n",*(undefined8 *)(*(long *)(param_1 + 0x28) + lVar4));
        }
        else {
          fwrite("DEFAULT:\n",1,9,param_2);
        }
        uVar5 = uVar5 + 1;
        lVar1 = *(long *)(param_1 + 0x28) + lVar4;
        lVar4 = lVar4 + 0x18;
        dump_node(*(undefined8 *)(lVar1 + 0x10),param_2,3);
      } while (uVar5 < (uint)param_1[0x2a]);
    }
LAB_001822cc:
    fputc(0x20,param_2);
    fputc(0x20,param_2);
    fwrite(&DAT_001f8ab0,1,2,param_2);
    return;
  case 6:
    fputc(0x20,param_2);
    fputc(0x20,param_2);
    __fprintf_chk(param_2,2,"GOTO L_%u;\n",param_1[0x26]);
    return;
  case 7:
    fputc(0x20,param_2);
    fputc(0x20,param_2);
    __fprintf_chk(param_2,2,"L_%u:\n",param_1[0x26]);
    return;
  case 8:
    fputc(0x20,param_2);
    fputc(0x20,param_2);
    __ptr = "BREAK;\n";
    __n = 7;
    break;
  case 9:
    fputc(0x20,param_2);
    fputc(0x20,param_2);
    __ptr = "CONTINUE;\n";
    __n = 10;
    break;
  case 10:
    fputc(0x20,param_2);
    fputc(0x20,param_2);
    dump_expr(*(undefined8 *)(param_1 + 0x26),param_2);
    fwrite(&DAT_001f9578,1,3,param_2);
    uVar2 = *(undefined8 *)(param_1 + 0x28);
    goto LAB_001820e8;
  case 0xb:
    fputc(0x20,param_2);
    fputc(0x20,param_2);
    fwrite("RETURN",1,6,param_2);
    if (*(long *)(param_1 + 0x26) == 0) goto LAB_001820ec;
    fputc(0x20,param_2);
    uVar2 = *(undefined8 *)(param_1 + 0x26);
LAB_001820e8:
    dump_expr(uVar2,param_2);
LAB_001820ec:
    fwrite(";\n",1,2,param_2);
    return;
  default:
    fputc(0x20,param_2);
    fputc(0x20,param_2);
    dump_expr(param_1,param_2);
    __ptr = ";\n";
    __n = 2;
  }
  fwrite(__ptr,1,__n,param_2);
  return;
}

