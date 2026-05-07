
void FUN_0017f55c(long *param_1,uint param_2,int param_3,int *param_4)

{
  long lVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined8 uVar5;
  void *__ptr;
  uint uVar6;
  ulong uVar7;
  long lVar8;
  uint uVar9;
  uint uVar10;
  long lVar11;
  
  if (param_2 < *(uint *)((long *)*param_1 + 1)) {
    lVar11 = *(long *)*param_1 + (ulong)param_2 * 0x50;
    uVar9 = *(uint *)(lVar11 + 0x10);
    if (uVar9 != 0) {
      uVar10 = 0;
      lVar8 = 0;
LAB_0017f5d4:
      do {
        lVar1 = *(long *)(lVar11 + 8) + lVar8;
        if ((*(int *)(*(long *)(lVar11 + 8) + lVar8) == 0x1b) && (*(uint *)(lVar1 + 0x60) != 0)) {
          uVar7 = 0;
          do {
            if (*(int *)(*(long *)(lVar1 + 0x58) + uVar7 * 4) == param_3) {
              puVar3 = calloc(1,0x130);
              if (puVar3 != (undefined4 *)0x0) {
                uVar2 = *(undefined4 *)(lVar1 + 8);
                *puVar3 = 10;
                puVar4 = calloc(1,0x130);
                if (puVar4 != (undefined4 *)0x0) {
                  *puVar4 = 0xd;
                  puVar4[0x26] = uVar2;
                  __snprintf_chk(puVar4 + 0x27,0x40,2,0x40,&DAT_001faae0);
                }
                uVar2 = *(undefined4 *)(*(long *)(lVar1 + 0x50) + uVar7 * 0x10);
                *(undefined4 **)(puVar3 + 0x26) = puVar4;
                uVar5 = build_expr(param_1,uVar2);
                *(undefined8 *)(puVar3 + 0x28) = uVar5;
                if ((param_4 != (int *)0x0) && (*param_4 == 0)) {
                  uVar6 = param_4[0x28];
                  uVar9 = param_4[0x29];
                  __ptr = *(void **)(param_4 + 0x26);
                  if (uVar9 <= uVar6) {
                    __ptr = realloc(__ptr,((ulong)uVar9 & 0x7fffffff) << 4);
                    if (__ptr == (void *)0x0) goto LAB_0017f6ec;
                    uVar6 = param_4[0x28];
                    *(void **)(param_4 + 0x26) = __ptr;
                    param_4[0x29] = uVar9 << 1;
                  }
                  uVar9 = *(uint *)(lVar11 + 0x10);
                  param_4[0x28] = uVar6 + 1;
                  uVar10 = uVar10 + 1;
                  *(undefined4 **)((long)__ptr + (ulong)uVar6 * 8) = puVar3;
                  lVar8 = lVar8 + 0x90;
                  if (uVar9 <= uVar10) {
                    return;
                  }
                  goto LAB_0017f5d4;
                }
LAB_0017f6ec:
                uVar9 = *(uint *)(lVar11 + 0x10);
              }
              break;
            }
            uVar7 = uVar7 + 1;
          } while (*(uint *)(lVar1 + 0x60) != uVar7);
        }
        uVar10 = uVar10 + 1;
        lVar8 = lVar8 + 0x90;
      } while (uVar10 < uVar9);
    }
  }
  return;
}

