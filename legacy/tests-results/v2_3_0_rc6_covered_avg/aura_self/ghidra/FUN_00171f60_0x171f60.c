
void FUN_00171f60(long *param_1,FILE *param_2)

{
  undefined8 *puVar1;
  long lVar2;
  long lVar3;
  uint uVar4;
  uint uVar5;
  long lVar6;
  uint uVar7;
  uint uVar8;
  long lVar9;
  
  if (param_1 == (long *)0x0) {
    return;
  }
  if (param_2 == (FILE *)0x0) {
    param_2 = *(FILE **)PTR_stdout_005fff40;
  }
  fwrite("=== Recursive Disassembly ===\n",1,0x1e,param_2);
  __fprintf_chk(param_2,2,"  Functions discovered: %u\n",(int)param_1[1]);
  __fprintf_chk(param_2,2,"  Total instructions: %u\n",*(undefined4 *)((long)param_1 + 0xc));
  if ((int)param_1[1] != 0) {
    lVar9 = 0;
    uVar8 = 0;
    do {
      uVar8 = uVar8 + 1;
      lVar2 = *param_1 + lVar9;
      lVar6 = 0;
      uVar7 = 0;
      __fprintf_chk(param_2,2,"\n  [%u] func_0x%lx (%u insns, src=%u, conf=%u)\n",uVar8,
                    *(undefined8 *)(*param_1 + lVar9),*(undefined4 *)(lVar2 + 0x10),
                    *(undefined1 *)(lVar2 + 0x14),*(undefined1 *)(lVar2 + 0x15));
      uVar5 = *(uint *)(lVar2 + 0x10);
      uVar4 = uVar5;
      if (10 < uVar5) {
        uVar4 = 10;
      }
      if (uVar5 != 0) {
        do {
          lVar3 = *(long *)(lVar2 + 8) + lVar6;
          uVar7 = uVar7 + 1;
          puVar1 = (undefined8 *)(*(long *)(lVar2 + 8) + lVar6);
          lVar6 = lVar6 + 0xe0;
          __fprintf_chk(param_2,2,"    0x%lx: %s %s\n",*puVar1,lVar3 + 0x20,lVar3 + 0x60);
        } while (uVar7 < uVar4);
        if (10 < *(uint *)(lVar2 + 0x10)) {
          __fprintf_chk(param_2,2,"    ... (%u more)\n",*(uint *)(lVar2 + 0x10) - 10);
        }
      }
      lVar9 = lVar9 + 0x18;
    } while (uVar8 < *(uint *)(param_1 + 1));
  }
  return;
}

