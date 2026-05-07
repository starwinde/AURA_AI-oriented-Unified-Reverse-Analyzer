
void FUN_00165e80(undefined8 *param_1,FILE *param_2)

{
  undefined8 *puVar1;
  int *piVar2;
  long *plVar3;
  int *piVar4;
  long *plVar5;
  undefined *puVar6;
  long lVar7;
  long lVar8;
  long lVar9;
  uint uVar10;
  uint uVar11;
  long *plVar12;
  long *plVar13;
  
  if (param_2 == (FILE *)0x0) {
    param_2 = *(FILE **)PTR_stdout_005fff40;
  }
  fwrite("digraph CallGraph {\n",1,0x14,param_2);
  fwrite("    node [shape=box fontname=\"monospace\"];\n",1,0x2b,param_2);
  if (((param_1 == (undefined8 *)0x0) || (plVar13 = (long *)*param_1, plVar13 == (long *)0x0)) ||
     ((int)plVar13[1] == 0)) {
    fwrite(&DAT_001fa010,1,2,param_2);
    return;
  }
  uVar10 = 0;
  plVar12 = (long *)param_1[1];
  lVar8 = 0;
  do {
    uVar10 = uVar10 + 1;
    puVar1 = (undefined8 *)(*plVar13 + lVar8);
    lVar7 = *plVar13 + lVar8 + 0x14;
    lVar8 = lVar8 + 0x98;
    __fprintf_chk(param_2,2,"    \"%s\" [label=\"%s\\n0x%lx\"];\n",lVar7,lVar7,*puVar1);
  } while (uVar10 < *(uint *)(plVar13 + 1));
  if ((plVar12 != (long *)0x0) && (uVar10 = *(uint *)(plVar12 + 1), uVar10 != 0)) {
    lVar8 = *plVar12;
    uVar11 = 0;
    lVar9 = 0;
    lVar7 = lVar8;
    if (*(int *)(lVar8 + 4) == -1) goto LAB_00165fc0;
LAB_00165f60:
    uVar11 = uVar11 + 1;
    if (uVar11 < uVar10) {
      while( true ) {
        lVar9 = lVar9 + 0x18;
        lVar8 = lVar7 + lVar9;
        if (*(int *)(lVar8 + 4) != -1) break;
        piVar4 = (int *)(lVar7 + 4);
        piVar2 = (int *)((long)piVar4 + lVar9);
        do {
          while (*piVar4 != -1) {
            piVar4 = piVar4 + 6;
            if (piVar2 == piVar4) goto LAB_00165fc0;
          }
          if (*(long *)(piVar4 + 1) == *(long *)(lVar8 + 8)) goto LAB_00165f60;
          piVar4 = piVar4 + 6;
        } while (piVar2 != piVar4);
LAB_00165fc0:
        __fprintf_chk(param_2,2,"    \"ext_0x%lx\" [label=\"<external>\\n0x%lx\" style=dashed];\n",
                      *(undefined8 *)(lVar8 + 8));
        uVar11 = uVar11 + 1;
        uVar10 = *(uint *)(plVar12 + 1);
        if (uVar10 <= uVar11) {
          if (uVar10 == 0) goto LAB_00166020;
          lVar7 = *plVar12;
          goto LAB_00166060;
        }
        lVar7 = *plVar12;
      }
      goto LAB_00165f60;
    }
LAB_00166060:
    lVar8 = 0;
    uVar10 = 0;
    do {
      lVar9 = lVar7 + lVar8;
      puVar6 = &DAT_001fe648;
      if (*(uint *)(lVar7 + lVar8) < *(uint *)(plVar13 + 1)) {
        puVar6 = (undefined *)(*plVar13 + (ulong)*(uint *)(lVar7 + lVar8) * 0x98 + 0x14);
      }
      __fprintf_chk(param_2,2,"    \"%s\" -> ",puVar6);
      uVar11 = *(uint *)(lVar9 + 4);
      if (uVar11 == 0xffffffff) {
        if (*(uint *)(plVar13 + 1) != 0) {
          plVar3 = (long *)*plVar13;
          plVar5 = plVar3 + (ulong)*(uint *)(plVar13 + 1) * 0x13;
          do {
            if (*(long *)(lVar9 + 8) == *plVar3) {
              __fprintf_chk(param_2,2,&DAT_001f9918,(long)plVar3 + 0x14);
              goto LAB_00166154;
            }
            plVar3 = plVar3 + 0x13;
          } while (plVar5 != plVar3);
        }
        __fprintf_chk(param_2,2,"\"ext_0x%lx\"");
LAB_00166154:
        __fprintf_chk(param_2,2," [label=\"0x%lx\" style=dashed];\n",*(undefined8 *)(lVar9 + 0x10));
      }
      else {
        puVar6 = &DAT_001fe648;
        if (uVar11 < *(uint *)(plVar13 + 1)) {
          puVar6 = (undefined *)(*plVar13 + (ulong)uVar11 * 0x98 + 0x14);
        }
        __fprintf_chk(param_2,2,"\"%s\" [label=\"0x%lx\"];\n",puVar6,*(undefined8 *)(lVar9 + 0x10));
      }
      uVar10 = uVar10 + 1;
      lVar8 = lVar8 + 0x18;
      if (*(uint *)(plVar12 + 1) <= uVar10) break;
      lVar7 = *plVar12;
    } while( true );
  }
LAB_00166020:
  fwrite(&DAT_001fa010,1,2,param_2);
  return;
}

