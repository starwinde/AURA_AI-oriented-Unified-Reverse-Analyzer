
void shared_return_format_text(long *param_1,FILE *param_2)

{
  long lVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  uint uVar5;
  
  if (param_1 == (long *)0x0 || param_2 == (FILE *)0x0) {
    return;
  }
  __fprintf_chk(param_2,2,"Shared Return Thunks: %u found (%u ret insns, %u candidates)\n",
                (int)param_1[1],*(undefined4 *)((long)param_1 + 0xc),(int)param_1[2]);
  if ((int)param_1[1] != 0) {
    lVar4 = 0;
    uVar5 = 0;
    do {
      lVar2 = *param_1 + lVar4;
      __fprintf_chk(param_2,2,"  thunk @ 0x%lx (%u insns, %u callers):",
                    *(undefined8 *)(*param_1 + lVar4),*(undefined4 *)(lVar2 + 8),
                    *(undefined4 *)(lVar2 + 0x210));
      if (*(int *)(lVar2 + 0x210) != 0) {
        lVar3 = 0;
        do {
          lVar1 = lVar3 * 8;
          lVar3 = lVar3 + 1;
          __fprintf_chk(param_2,2," 0x%lx",*(undefined8 *)(lVar2 + 0x10 + lVar1));
        } while ((uint)lVar3 < *(uint *)(lVar2 + 0x210));
      }
      fputc(10,param_2);
      uVar5 = uVar5 + 1;
      lVar4 = lVar4 + 0x218;
    } while (uVar5 < *(uint *)(param_1 + 1));
  }
  return;
}

