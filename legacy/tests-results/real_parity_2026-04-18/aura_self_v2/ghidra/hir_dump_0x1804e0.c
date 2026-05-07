
undefined8 hir_dump(long param_1,FILE *param_2)

{
  undefined4 *puVar1;
  long lVar2;
  long lVar3;
  uint uVar4;
  
  if (param_1 == 0) {
    return 0xfffffffc;
  }
  if (param_2 == (FILE *)0x0) {
    param_2 = *(FILE **)PTR_stdout_005fff40;
  }
  __fprintf_chk(param_2,2,"=== HIR: %s (0x%lx) ===\n",param_1,*(undefined8 *)(param_1 + 0x80));
  __fprintf_chk(param_2,2,"%s %s(",param_1 + 0x88,param_1);
  if (*(int *)(param_1 + 0xdd0) != 0) {
    __fprintf_chk(param_2,2,"%s %s",param_1 + 0x150,param_1 + 0x110);
    lVar3 = param_1 + 0x21c;
    if (1 < *(uint *)(param_1 + 0xdd0)) {
      uVar4 = 1;
      do {
        fwrite(", ",1,2,param_2);
        uVar4 = uVar4 + 1;
        __fprintf_chk(param_2,2,"%s %s",lVar3,lVar3 + -0x40);
        lVar3 = lVar3 + 0xcc;
      } while (uVar4 < *(uint *)(param_1 + 0xdd0));
    }
  }
  fwrite(")\n",1,2,param_2);
  if ((*(int *)(param_1 + 0xde0) != 0) &&
     (fwrite("Locals:\n",1,8,param_2), *(int *)(param_1 + 0xde0) != 0)) {
    lVar3 = 0;
    uVar4 = 0;
    do {
      lVar2 = *(long *)(param_1 + 0xdd8) + lVar3;
      uVar4 = uVar4 + 1;
      puVar1 = (undefined4 *)(*(long *)(param_1 + 0xdd8) + lVar3);
      lVar3 = lVar3 + 0xcc;
      __fprintf_chk(param_2,2,"  %s %s (ssa_id=%u)\n",lVar2 + 0x44,lVar2 + 4,*puVar1);
    } while (uVar4 < *(uint *)(param_1 + 0xde0));
  }
  fwrite("Body:\n",1,6,param_2);
  dump_node_constprop_0(*(undefined8 *)(param_1 + 0xde8),param_2);
  return 0;
}

