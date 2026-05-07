
long FUN_001050b4(void *param_1,ulong param_2)

{
  bool bVar1;
  ssize_t sVar2;
  int *piVar3;
  ulong __n;
  long lVar4;
  
  lVar4 = 0;
  do {
    __n = param_2;
    if (param_2 == 0) {
      return lVar4;
    }
    do {
      sVar2 = write(1,param_1,__n);
      if (-1 < sVar2) {
        if (sVar2 == 0) {
          piVar3 = __errno_location();
          *piVar3 = 0x1c;
          return lVar4;
        }
        goto LAB_0010512c;
      }
      piVar3 = __errno_location();
    } while ((*piVar3 == 4) ||
            (bVar1 = 0x7ff00000 < __n, __n = 0x7ff00000, bVar1 && *piVar3 == 0x16));
    if (sVar2 == -1) {
      return lVar4;
    }
LAB_0010512c:
    lVar4 = lVar4 + sVar2;
    param_1 = (void *)((long)param_1 + sVar2);
    param_2 = param_2 - sVar2;
  } while( true );
}

