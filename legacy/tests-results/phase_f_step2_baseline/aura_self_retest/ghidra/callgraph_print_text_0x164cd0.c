
void callgraph_print_text(long *param_1,FILE *param_2)

{
  long lVar1;
  long *plVar2;
  long *plVar3;
  bool bVar4;
  uint uVar5;
  long lVar6;
  long lVar7;
  uint uVar8;
  uint uVar9;
  long lVar10;
  
  if (param_2 == (FILE *)0x0) {
    param_2 = *(FILE **)PTR_stdout_005fff40;
  }
  if (param_1 == (long *)0x0) {
    fwrite("Call Graph: (null)\n",1,0x13,param_2);
    return;
  }
  plVar2 = (long *)*param_1;
  plVar3 = (long *)param_1[1];
  fwrite("Call Graph:\n",1,0xc,param_2);
  if ((plVar2 == (long *)0x0) || ((int)plVar2[1] == 0)) {
    fwrite("  (no functions detected)\n",1,0x1a,param_2);
    return;
  }
  lVar10 = 0;
  uVar9 = 0;
  do {
    __fprintf_chk(param_2,2,"  %s (0x%lx)\n",*plVar2 + lVar10 + 0x14,
                  *(undefined8 *)(*plVar2 + lVar10));
    if ((plVar3 == (long *)0x0) || (uVar5 = *(uint *)(plVar3 + 1), uVar5 == 0)) {
LAB_00164e60:
      fwrite("    (no outgoing calls)\n",1,0x18,param_2);
    }
    else {
      lVar7 = 0;
      uVar8 = 0;
      bVar4 = false;
      do {
        lVar1 = *plVar3 + lVar7;
        if (*(uint *)(*plVar3 + lVar7) == uVar9) {
          if (*(uint *)(lVar1 + 4) == 0xffffffff) {
            __fprintf_chk(param_2,2,"    -> <external:0x%lx>",*(undefined8 *)(lVar1 + 8));
          }
          else {
            lVar6 = (ulong)*(uint *)(lVar1 + 4) * 0x98;
            __fprintf_chk(param_2,2,"    -> %s (0x%lx)",*plVar2 + lVar6 + 0x14,
                          *(undefined8 *)(*plVar2 + lVar6));
          }
          __fprintf_chk(param_2,2," [call site: 0x%lx]\n",*(undefined8 *)(lVar1 + 0x10));
          uVar5 = *(uint *)(plVar3 + 1);
          bVar4 = true;
        }
        uVar8 = uVar8 + 1;
        lVar7 = lVar7 + 0x18;
      } while (uVar8 < uVar5);
      if (!bVar4) goto LAB_00164e60;
    }
    uVar9 = uVar9 + 1;
    lVar10 = lVar10 + 0x98;
    if (*(uint *)(plVar2 + 1) <= uVar9) {
      return;
    }
  } while( true );
}

