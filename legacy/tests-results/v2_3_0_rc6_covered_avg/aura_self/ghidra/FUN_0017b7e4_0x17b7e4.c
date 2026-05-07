
void FUN_0017b7e4(long param_1,uint param_2,uint param_3,uint param_4,undefined8 *param_5,
                 uint *param_6)

{
  uint *puVar1;
  byte *__ptr;
  uint *__ptr_00;
  byte *pbVar2;
  void *pvVar4;
  long lVar5;
  uint *puVar6;
  ulong uVar7;
  int iVar8;
  ulong uVar9;
  uint uVar10;
  ulong __nmemb;
  byte *pbVar3;
  
  __nmemb = (ulong)param_2;
  __ptr = calloc(__nmemb,1);
  __ptr_00 = malloc(__nmemb << 2);
  if (__ptr == (byte *)0x0 || __ptr_00 == (uint *)0x0) {
    free(__ptr);
    free(__ptr_00);
    *param_5 = 0;
    *param_6 = 0;
    return;
  }
  __ptr[param_3] = 1;
  if (param_3 != param_4) {
    uVar9 = 0;
    __ptr[param_4] = 1;
    *__ptr_00 = param_4;
    while( true ) {
      iVar8 = (int)uVar9;
      lVar5 = param_1 + (ulong)param_4 * 0x50;
      uVar10 = *(uint *)(lVar5 + 0x20);
      if (uVar10 != 0) {
        puVar6 = *(uint **)(lVar5 + 0x18);
        puVar1 = puVar6 + uVar10;
        do {
          uVar10 = *puVar6;
          puVar6 = puVar6 + 1;
          if ((uVar10 < param_2) && ((__ptr[uVar10] & 1) == 0)) {
            __ptr_00[uVar9] = uVar10;
            uVar9 = (ulong)((int)uVar9 + 1);
            __ptr[uVar10] = 1;
          }
          iVar8 = (int)uVar9;
        } while (puVar1 != puVar6);
      }
      if (iVar8 == 0) break;
      uVar9 = (ulong)(iVar8 - 1);
      param_4 = __ptr_00[iVar8 - 1];
    }
  }
  if (param_2 == 0) {
    pvVar4 = malloc(0);
    uVar10 = 0;
    if (pvVar4 != (void *)0x0) goto LAB_0017b914;
  }
  else {
    uVar9 = 0;
    pbVar3 = __ptr;
    do {
      pbVar2 = pbVar3 + 1;
      uVar10 = (int)uVar9 + (*pbVar3 & 1);
      uVar9 = (ulong)uVar10;
      pbVar3 = pbVar2;
    } while (__ptr + __nmemb != pbVar2);
    pvVar4 = malloc(uVar9 << 2);
    if (pvVar4 != (void *)0x0) {
      uVar9 = 0;
      uVar7 = 0;
      do {
        if ((__ptr[uVar9] & 1) != 0) {
          *(int *)((long)pvVar4 + uVar7 * 4) = (int)uVar9;
          uVar7 = (ulong)((int)uVar7 + 1);
        }
        uVar9 = uVar9 + 1;
      } while (__nmemb != uVar9);
      goto LAB_0017b914;
    }
  }
  pvVar4 = (void *)0x0;
  uVar10 = 0;
LAB_0017b914:
  *param_5 = pvVar4;
  *param_6 = uVar10;
  free(__ptr);
  free(__ptr_00);
  return;
}

