
void func_id_result_print(long *param_1,long param_2)

{
  long lVar1;
  undefined8 uVar2;
  long lVar3;
  uint uVar4;
  
  if (param_1 == (long *)0x0) {
    return;
  }
  if (param_2 == 0) {
    param_2 = *(long *)PTR_stdout_005fff40;
  }
  __fprintf_chk(param_2,2,"=== Function ID Results (%u) ===\n",(int)param_1[1]);
  if ((int)param_1[1] != 0) {
    lVar3 = 0;
    uVar4 = 0;
    do {
      while( true ) {
        lVar1 = *param_1 + lVar3;
        uVar2 = *(undefined8 *)(*param_1 + lVar3);
        if (*(char *)(lVar1 + 0x10) == '\0') break;
        uVar4 = uVar4 + 1;
        lVar3 = lVar3 + 0x98;
        __fprintf_chk((double)(*(float *)(lVar1 + 0x90) * 100.0),param_2,2,
                      "  0x%lx  hash=0x%016lx  -> %-24s  (%.0f%%)\n",uVar2,
                      *(undefined8 *)(lVar1 + 8),lVar1 + 0x10);
        if (*(uint *)(param_1 + 1) <= uVar4) {
          return;
        }
      }
      __fprintf_chk(param_2,2,"  0x%lx  hash=0x%016lx  (no match)\n",uVar2,
                    *(undefined8 *)(lVar1 + 8),lVar1 + 0x10);
      uVar4 = uVar4 + 1;
      lVar3 = lVar3 + 0x98;
    } while (uVar4 < *(uint *)(param_1 + 1));
  }
  return;
}

