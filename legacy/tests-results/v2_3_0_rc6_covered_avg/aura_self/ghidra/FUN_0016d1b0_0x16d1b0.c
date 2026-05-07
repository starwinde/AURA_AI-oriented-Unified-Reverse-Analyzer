
undefined8 FUN_0016d1b0(long *param_1,char *param_2)

{
  long lVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  undefined8 uVar5;
  char *__s;
  FILE *__s_00;
  size_t __n;
  size_t sVar6;
  long lVar7;
  long lVar8;
  
  if (param_1 == (long *)0x0 || param_2 == (char *)0x0) {
    uVar5 = 0xfffffffc;
  }
  else {
    lVar1 = FUN_001f78d0();
    if (lVar1 != 0) {
      FUN_001f63a4((double)*(uint *)((long)param_1 + 0xc),lVar1,"version");
      if (param_1[2] != 0) {
        FUN_001f6520(lVar1,"description");
      }
      lVar2 = FUN_001f6980(lVar1,"types");
      if (lVar2 == 0) {
        FUN_001f43e0(lVar1);
      }
      else {
        lVar7 = 0;
        if ((int)param_1[1] != 0) {
          do {
            lVar8 = *param_1;
            lVar4 = FUN_001f78d0();
            lVar3 = lVar8 + lVar7 * 0x20;
            if (lVar4 == 0) {
              FUN_001f43e0(lVar1);
              goto LAB_0016d314;
            }
            if (*(long *)(lVar8 + lVar7 * 0x20) != 0) {
              FUN_001f6520(lVar4,&DAT_001fc1d0);
            }
            if (*(long *)(lVar3 + 8) != 0) {
              FUN_001f6520(lVar4,"category");
            }
            FUN_001f63a4((double)*(uint *)(lVar3 + 0x18),lVar4,&DAT_001fc1e8);
            FUN_001f63a4((double)*(uint *)(lVar3 + 0x1c),lVar4,"alignment");
            if ((*(long *)(lVar3 + 0x10) != 0) && (lVar3 = FUN_001f5230(), lVar3 != 0)) {
              FUN_001f5b60(lVar4,"fields",lVar3);
            }
            FUN_001f5b10(lVar2,lVar4);
            lVar7 = lVar7 + 1;
          } while ((uint)lVar7 < *(uint *)(param_1 + 1));
        }
        __s = (char *)FUN_001f55b0(lVar1);
        FUN_001f43e0(lVar1);
        if (__s != (char *)0x0) {
          __s_00 = fopen(param_2,"w");
          if (__s_00 == (FILE *)0x0) {
            free(__s);
          }
          else {
            __n = strlen(__s);
            sVar6 = fwrite(__s,1,__n,__s_00);
            fclose(__s_00);
            free(__s);
            if (__n == sVar6) {
              return 0;
            }
          }
          return 0xfffffffd;
        }
      }
    }
LAB_0016d314:
    uVar5 = 0xfffffffe;
  }
  return uVar5;
}

