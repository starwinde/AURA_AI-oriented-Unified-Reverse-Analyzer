
void FUN_0010f680(void *param_1,ulong *param_2,long param_3,ulong param_4,ulong param_5)

{
  long lVar1;
  void *pvVar2;
  size_t sVar3;
  ulong uVar4;
  ulong uVar5;
  ulong uVar6;
  
  uVar5 = *param_2;
  uVar6 = ((long)uVar5 >> 1) + uVar5;
  if (SCARRY8((long)uVar5 >> 1,uVar5)) {
    uVar6 = 0x7fffffffffffffff;
  }
  if ((param_4 != 0xffffffffffffffff) && ((long)param_4 < (long)uVar6)) {
    uVar6 = param_4;
  }
  sVar3 = uVar6 * param_5;
  if (SUB168(SEXT816((long)uVar6) * SEXT816((long)param_5),8) == (long)sVar3 >> 0x3f) {
    if ((long)sVar3 < 0x80) {
      uVar4 = 0x80;
      goto LAB_0010f734;
    }
    if (param_1 == (void *)0x0) goto LAB_0010f744;
LAB_0010f6d8:
    lVar1 = uVar6 - uVar5;
  }
  else {
    uVar4 = 0x7fffffffffffffff;
LAB_0010f734:
    uVar6 = 0;
    if (param_5 != 0) {
      uVar6 = uVar4 / param_5;
    }
    sVar3 = uVar6 * param_5;
    if (param_1 != (void *)0x0) goto LAB_0010f6d8;
LAB_0010f744:
    lVar1 = uVar6 - uVar5;
    *param_2 = 0;
  }
  if (lVar1 < param_3) {
    uVar6 = uVar5 + param_3;
    if ((((!SCARRY8(uVar5,param_3)) &&
         ((long)uVar6 <= (long)param_4 || param_4 == 0xffffffffffffffff)) &&
        (sVar3 = uVar6 * param_5,
        SUB168(SEXT816((long)uVar6) * SEXT816((long)param_5),8) == (long)sVar3 >> 0x3f)) &&
       ((pvVar2 = realloc(param_1,sVar3), pvVar2 != (void *)0x0 ||
        (param_1 != (void *)0x0 && sVar3 == 0)))) {
LAB_0010f718:
      *param_2 = uVar6;
      return;
    }
  }
  else {
    pvVar2 = realloc(param_1,sVar3);
    if (pvVar2 != (void *)0x0) goto LAB_0010f718;
  }
                    /* WARNING: Subroutine does not return */
  FUN_0010d454();
}

