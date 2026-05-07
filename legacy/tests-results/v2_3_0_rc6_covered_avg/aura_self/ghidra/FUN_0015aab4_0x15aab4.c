
uint FUN_0015aab4(long param_1,uint param_2,uint param_3,uint param_4)

{
  uint *puVar1;
  uint uVar2;
  long lVar3;
  void *__ptr;
  void *__ptr_00;
  uint *__ptr_01;
  uint *puVar4;
  long lVar5;
  ulong uVar6;
  ulong uVar7;
  uint uVar8;
  ulong __nmemb;
  
  uVar8 = param_3;
  if (param_3 < param_4) {
    uVar8 = param_4;
  }
  uVar2 = param_2;
  if (uVar8 < param_2) {
    lVar3 = param_1 + (ulong)param_3 * 0x50;
    uVar8 = *(uint *)(lVar3 + 0x30);
    if ((uVar8 != 1) ||
       ((uVar2 = **(uint **)(lVar3 + 0x28), param_4 != uVar2 &&
        ((lVar3 = param_1 + (ulong)param_4 * 0x50, *(int *)(lVar3 + 0x30) != 1 ||
         (uVar2 != **(uint **)(lVar3 + 0x28))))))) {
      __nmemb = (ulong)param_2;
      __ptr = calloc(__nmemb,1);
      __ptr_00 = calloc(__nmemb,1);
      __ptr_01 = malloc(__nmemb << 2);
      if ((__ptr != (void *)0x0 && __ptr_00 != (void *)0x0) && __ptr_01 != (uint *)0x0) {
        uVar6 = 1;
        uVar7 = 0;
        *(undefined1 *)((long)__ptr + (ulong)param_3) = 1;
        *__ptr_01 = param_3;
        while( true ) {
          if (uVar8 != 0) {
            puVar4 = *(uint **)(param_1 + (ulong)__ptr_01[uVar7] * 0x50 + 0x28);
            puVar1 = puVar4 + uVar8;
            do {
              uVar8 = *puVar4;
              puVar4 = puVar4 + 1;
              if ((uVar8 < param_2) && ((*(byte *)((long)__ptr + (ulong)uVar8) & 1) == 0)) {
                __ptr_01[uVar6] = uVar8;
                uVar6 = (ulong)((int)uVar6 + 1);
                *(undefined1 *)((long)__ptr + (ulong)uVar8) = 1;
              }
            } while (puVar4 != puVar1);
          }
          uVar7 = uVar7 + 1;
          if ((uint)uVar6 <= (uint)uVar7) break;
          uVar8 = *(uint *)(param_1 + (ulong)__ptr_01[uVar7 & 0xffffffff] * 0x50 + 0x30);
        }
        uVar7 = 1;
        lVar3 = 0;
        *(undefined1 *)((long)__ptr_00 + (ulong)param_4) = 1;
        *__ptr_01 = param_4;
        do {
          lVar5 = param_1 + (ulong)__ptr_01[lVar3] * 0x50;
          uVar8 = *(uint *)(lVar5 + 0x30);
          if (uVar8 != 0) {
            puVar4 = *(uint **)(lVar5 + 0x28);
            puVar1 = puVar4 + uVar8;
            do {
              uVar8 = *puVar4;
              puVar4 = puVar4 + 1;
              if ((uVar8 < param_2) && ((*(byte *)((long)__ptr_00 + (ulong)uVar8) & 1) == 0)) {
                __ptr_01[uVar7] = uVar8;
                uVar7 = (ulong)((int)uVar7 + 1);
                *(undefined1 *)((long)__ptr_00 + (ulong)uVar8) = 1;
              }
            } while (puVar4 != puVar1);
          }
          lVar3 = lVar3 + 1;
        } while ((uint)lVar3 < (uint)uVar7);
        uVar7 = 0;
        while (((*(byte *)((long)__ptr + uVar7) & 1) == 0 ||
               ((*(byte *)((long)__ptr_00 + uVar7) & 1) == 0))) {
          uVar7 = uVar7 + 1;
          if (__nmemb == uVar7) {
LAB_0015ac64:
            free(__ptr);
            free(__ptr_00);
            free(__ptr_01);
            return param_2;
          }
        }
        param_2 = (uint)uVar7;
        goto LAB_0015ac64;
      }
      free(__ptr);
      free(__ptr_00);
      free(__ptr_01);
      uVar2 = param_2;
    }
  }
  return uVar2;
}

