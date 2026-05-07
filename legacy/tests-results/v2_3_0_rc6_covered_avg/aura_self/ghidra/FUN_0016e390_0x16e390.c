
void FUN_0016e390(long *param_1,long param_2)

{
  long lVar1;
  long lVar2;
  
  if (param_1 == (long *)0x0 || param_2 == 0) {
    return;
  }
  __fprintf_chk(param_2,2,"Function start candidates: %u\n",(int)param_1[1]);
  if ((int)param_1[1] != 0) {
    lVar2 = 0;
    do {
      lVar1 = lVar2 * 8;
      lVar2 = lVar2 + 1;
      __fprintf_chk(param_2,2,"  0x%lx\n",*(undefined8 *)(*param_1 + lVar1));
    } while ((uint)lVar2 < *(uint *)(param_1 + 1));
  }
  return;
}

