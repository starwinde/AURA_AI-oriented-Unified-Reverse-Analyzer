
int FUN_0014b280(long param_1,uint param_2,long param_3,ulong param_4,ulong param_5,long param_6,
                undefined4 param_7)

{
  ulong uVar1;
  int iVar2;
  void *__base;
  ulong *puVar3;
  ulong uVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  uint uVar8;
  ulong *puVar10;
  uint uVar11;
  int iVar12;
  undefined8 local_148;
  undefined8 uStack_140;
  undefined8 uStack_138;
  undefined8 uStack_130;
  undefined8 local_128;
  undefined8 uStack_120;
  undefined8 uStack_118;
  undefined8 uStack_110;
  undefined8 local_108;
  undefined8 uStack_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined8 local_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined8 local_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 local_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 local_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  long local_68;
  ulong uVar9;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if ((param_1 != 0 && param_2 != 0) &&
     (((param_3 != 0 && param_6 != 0) && param_4 <= param_5) &&
      ((param_3 == 0 || param_6 == 0) || param_5 != param_4))) {
    __base = malloc((ulong)param_2 << 3);
    if (__base != (void *)0x0) {
      puVar10 = (ulong *)(param_1 + 0x10);
      lVar6 = 0;
      puVar3 = puVar10;
      do {
        *(ulong *)((long)__base + lVar6 * 8) = *puVar3;
        lVar6 = lVar6 + 1;
        puVar3 = puVar3 + 5;
      } while ((uint)lVar6 < param_2);
      qsort(__base,(ulong)param_2,8,FUN_0014b070);
      iVar12 = 0;
      lVar6 = FUN_001446e0(param_7);
      uVar11 = 0;
      if (lVar6 == 0) {
        iVar12 = 0;
        free(__base);
      }
      else {
        do {
          while( true ) {
            uVar1 = *puVar10;
            if (param_4 <= uVar1 && uVar1 < param_5) break;
LAB_0014b390:
            uVar11 = uVar11 + 1;
            puVar10 = puVar10 + 5;
            if (param_2 <= uVar11) goto LAB_0014b3d8;
          }
          uVar1 = puVar10[1] + uVar1;
          uVar7 = 0;
          uVar4 = (ulong)param_2;
          if (param_4 <= uVar1 && uVar1 < param_5) {
            while( true ) {
              uVar9 = uVar4;
              uVar5 = (uint)uVar7;
              uVar8 = (uint)uVar9;
              if (uVar8 <= uVar5) break;
              uVar5 = uVar5 + (uVar8 - uVar5 >> 1);
              uVar4 = (ulong)uVar5;
              if (*(ulong *)((long)__base + (ulong)uVar5 * 8) <= uVar1) {
                uVar7 = (ulong)(uVar5 + 1);
                uVar4 = uVar9;
              }
            }
            uVar4 = param_5;
            if (((param_2 <= uVar5) || (uVar4 = *(ulong *)((long)__base + uVar7 * 8), uVar1 < uVar4)
                ) && (uVar4 = uVar4 - uVar1, 7 < uVar4)) {
              if (0x10 < uVar4) {
                uVar4 = 0x10;
              }
              uStack_140 = 0;
              local_148 = 0;
              uStack_130 = 0;
              uStack_138 = 0;
              uStack_120 = 0;
              local_128 = 0;
              uStack_110 = 0;
              uStack_118 = 0;
              uStack_100 = 0;
              local_108 = 0;
              uStack_f0 = 0;
              uStack_f8 = 0;
              uStack_e0 = 0;
              local_e8 = 0;
              uStack_d0 = 0;
              uStack_d8 = 0;
              uStack_c0 = 0;
              local_c8 = 0;
              uStack_b0 = 0;
              uStack_b8 = 0;
              uStack_a0 = 0;
              local_a8 = 0;
              uStack_90 = 0;
              uStack_98 = 0;
              uStack_80 = 0;
              local_88 = 0;
              uStack_70 = 0;
              uStack_78 = 0;
              iVar2 = FUN_001447f0(lVar6,param_6 + (uVar1 - param_4),uVar4,uVar1,&local_148,1);
              if (((0 < iVar2) && ((int)local_128 != 0x706f6e)) &&
                 (iVar2 = FUN_0014bbf0(param_3,uVar1,4,0xffffffe6,0), iVar2 != 0)) {
                iVar12 = iVar12 + 1;
              }
            }
            goto LAB_0014b390;
          }
          uVar11 = uVar11 + 1;
          puVar10 = puVar10 + 5;
        } while (uVar11 < param_2);
LAB_0014b3d8:
        FUN_001447a4(lVar6);
        free(__base);
      }
      goto LAB_0014b3f4;
    }
  }
  iVar12 = 0;
LAB_0014b3f4:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return iVar12;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                   local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
}

