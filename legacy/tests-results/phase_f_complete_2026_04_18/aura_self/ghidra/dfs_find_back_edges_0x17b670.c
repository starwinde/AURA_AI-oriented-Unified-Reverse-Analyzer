
void dfs_find_back_edges(long *param_1,uint param_2,long param_3,undefined8 *param_4,uint *param_5,
                        uint *param_6)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  void *__ptr;
  size_t __size;
  uint uVar5;
  uint uVar6;
  long lVar7;
  long lVar8;
  ulong uVar9;
  
  uVar9 = (ulong)param_2;
  lVar8 = *param_1 + uVar9 * 0x50;
  *(undefined4 *)(param_3 + uVar9 * 4) = 1;
  uVar6 = *(uint *)(lVar8 + 0x30);
  if (uVar6 != 0) {
    lVar7 = 0;
    do {
      uVar2 = *(uint *)(*(long *)(lVar8 + 0x28) + lVar7 * 4);
      if (uVar2 < *(uint *)(param_1 + 1)) {
        iVar3 = *(int *)(param_3 + (ulong)uVar2 * 4);
        if (iVar3 == 1) {
          if (param_2 != uVar2) {
            uVar5 = 0;
            uVar4 = param_2;
            do {
              uVar5 = uVar5 + 1;
              uVar1 = *(uint *)(*param_1 + (ulong)uVar4 * 0x50 + 0x34);
              if ((uVar1 == uVar4) || (*(uint *)(param_1 + 1) < uVar5)) goto LAB_0017b70c;
              uVar4 = uVar1;
            } while (uVar2 != uVar1);
          }
          uVar5 = *param_5;
          uVar6 = *param_6;
          __ptr = (void *)*param_4;
          if (uVar6 <= uVar5) {
            if (uVar6 == 0) {
              __size = 0x40;
              uVar5 = 8;
            }
            else {
              uVar5 = uVar6 << 1;
              __size = ((ulong)uVar6 & 0x7fffffff) << 4;
            }
            *param_6 = uVar5;
            __ptr = realloc(__ptr,__size);
            uVar5 = *param_5;
            *param_4 = __ptr;
          }
          *(uint *)((long)__ptr + (ulong)uVar5 * 8) = param_2;
          *(uint *)((long)__ptr + (ulong)*param_5 * 8 + 4) = uVar2;
          *param_5 = *param_5 + 1;
          uVar6 = *(uint *)(lVar8 + 0x30);
        }
        else if (iVar3 == 0) {
          dfs_find_back_edges(param_1,uVar2,param_3,param_4,param_5,param_6);
          uVar6 = *(uint *)(lVar8 + 0x30);
        }
      }
LAB_0017b70c:
      lVar7 = lVar7 + 1;
    } while ((uint)lVar7 < uVar6);
  }
  *(undefined4 *)(param_3 + uVar9 * 4) = 2;
  return;
}

