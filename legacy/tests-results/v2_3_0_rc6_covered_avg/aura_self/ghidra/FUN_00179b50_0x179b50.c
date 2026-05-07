
void FUN_00179b50(undefined8 *param_1,FILE *param_2)

{
  void *__ptr;
  long lVar1;
  uint uVar2;
  long lVar3;
  uint *puVar4;
  uint uVar5;
  uint *puVar6;
  uint uVar7;
  uint *puVar8;
  ulong uVar9;
  
  if (param_1 == (undefined8 *)0x0) {
    return;
  }
  if (param_2 == (FILE *)0x0) {
    param_2 = *(FILE **)PTR_stdout_005fff40;
  }
  __fprintf_chk(param_2,2,"=== Alias Analysis: 0x%016lx ===\n",param_1[3]);
  __fprintf_chk(param_2,2,"  Values:     %u\n",*(undefined4 *)(param_1 + 2));
  __fprintf_chk(param_2,2,"  Partitions: %u\n\n",*(undefined4 *)((long)param_1 + 0x14));
  uVar7 = *(uint *)(param_1 + 2);
  puVar6 = (uint *)*param_1;
  __ptr = calloc((ulong)uVar7,4);
  if (__ptr == (void *)0x0) {
    return;
  }
  lVar1 = 0;
  uVar5 = 0;
  if (uVar7 != 0) {
    do {
      uVar2 = *(uint *)((long)puVar6 + lVar1);
      lVar3 = lVar1;
      if (uVar2 != uVar5) {
        do {
          uVar7 = puVar6[uVar2];
          *(uint *)((long)puVar6 + lVar3) = uVar7;
          lVar3 = (ulong)uVar7 << 2;
          uVar2 = puVar6[uVar7];
        } while (uVar2 != uVar7);
        uVar7 = *(uint *)(param_1 + 2);
      }
      uVar5 = uVar5 + 1;
      lVar1 = lVar1 + 4;
      *(int *)((long)__ptr + lVar3) = *(int *)((long)__ptr + lVar3) + 1;
    } while (uVar5 < uVar7);
    if (uVar7 != 0) {
      uVar9 = 0;
      do {
        while (*(uint *)((long)__ptr + uVar9 * 4) < 2) {
          uVar9 = uVar9 + 1;
          if (uVar7 <= (uint)uVar9) goto LAB_00179d0c;
        }
        __fprintf_chk(param_2,2,"  Partition %u (%u members):",uVar9 & 0xffffffff);
        uVar7 = 0;
        puVar8 = puVar6;
        if (*(int *)(param_1 + 2) == 0) {
LAB_00179cec:
          fputc(10,param_2);
          uVar7 = *(uint *)(param_1 + 2);
        }
        else {
          do {
            while( true ) {
              uVar5 = *puVar8;
              puVar4 = puVar8;
              uVar2 = uVar7;
              if (uVar5 != uVar7) {
                do {
                  uVar2 = puVar6[uVar5];
                  *puVar4 = uVar2;
                  puVar4 = puVar6 + uVar2;
                  uVar5 = puVar6[uVar2];
                } while (uVar5 != uVar2);
              }
              if (uVar2 == (uint)uVar9) break;
              uVar7 = uVar7 + 1;
              puVar8 = puVar8 + 1;
              if (*(uint *)(param_1 + 2) <= uVar7) goto LAB_00179cec;
            }
            __fprintf_chk(param_2,2,&DAT_001fa610,uVar7);
            uVar7 = uVar7 + 1;
            puVar8 = puVar8 + 1;
          } while (uVar7 < *(uint *)(param_1 + 2));
          fputc(10,param_2);
          uVar7 = *(uint *)(param_1 + 2);
        }
        uVar9 = uVar9 + 1;
      } while ((uint)uVar9 < uVar7);
    }
  }
LAB_00179d0c:
  free(__ptr);
  return;
}

