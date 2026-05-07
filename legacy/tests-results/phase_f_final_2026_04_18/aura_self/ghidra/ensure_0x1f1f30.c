
long ensure(long *param_1,ulong param_2)

{
  ulong uVar1;
  long lVar2;
  void *__dest;
  long lVar3;
  ulong uVar4;
  
  if (param_1 == (long *)0x0) {
    return 0;
  }
  lVar2 = *param_1;
  if ((lVar2 == 0) ||
     (((uVar4 = param_1[1], uVar4 != 0 && (uVar4 <= (ulong)param_1[2])) ||
      (lVar3 = 0x7fffffff, 0x7fffffff < param_2)))) {
    return 0;
  }
  uVar1 = param_1[2] + param_2 + 1;
  if (uVar1 <= uVar4) {
    return lVar2 + param_1[2];
  }
  if ((int)param_1[4] != 0) {
    return 0;
  }
  if (uVar1 < 0x40000000) {
    lVar3 = uVar1 * 2;
  }
  else if (0x7fffffff < uVar1) {
    return 0;
  }
  if ((code *)param_1[7] == (code *)0x0) {
    __dest = (void *)(*(code *)param_1[5])(lVar3);
    if (__dest != (void *)0x0) {
      memcpy(__dest,(void *)*param_1,param_1[2] + 1);
      (*(code *)param_1[6])(*param_1);
      goto LAB_001f1fa8;
    }
  }
  else {
    __dest = (void *)(*(code *)param_1[7])(lVar2,lVar3);
    if (__dest != (void *)0x0) {
LAB_001f1fa8:
      *param_1 = (long)__dest;
      param_1[1] = lVar3;
      return (long)__dest + param_1[2];
    }
  }
  (*(code *)param_1[6])(*param_1);
  *param_1 = 0;
  param_1[1] = 0;
  return 0;
}

