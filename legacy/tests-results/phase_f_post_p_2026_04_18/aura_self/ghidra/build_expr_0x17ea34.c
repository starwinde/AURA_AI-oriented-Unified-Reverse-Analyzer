
undefined4 * build_expr(long *param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  long *plVar4;
  uint *puVar5;
  undefined *puVar6;
  long lVar7;
  undefined8 *puVar8;
  undefined8 *puVar9;
  uint *puVar10;
  undefined8 local_1e0;
  undefined8 uStack_1d8;
  undefined8 uStack_1d0;
  undefined8 uStack_1c8;
  undefined8 local_1c0;
  undefined8 uStack_1b8;
  undefined8 uStack_1b0;
  undefined8 uStack_1a8;
  undefined8 local_1a0;
  undefined8 uStack_198;
  undefined8 uStack_190;
  undefined8 uStack_188;
  undefined8 local_180;
  undefined8 uStack_178;
  undefined8 uStack_170;
  undefined8 uStack_168;
  undefined8 local_160;
  undefined8 local_148;
  undefined8 uStack_140;
  undefined8 uStack_138;
  undefined8 uStack_130;
  undefined8 uStack_128;
  undefined8 local_120;
  undefined8 uStack_118;
  undefined8 uStack_110;
  undefined8 uStack_108;
  undefined8 local_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined8 uStack_e8;
  undefined8 local_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined8 local_c8;
  undefined8 local_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 local_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 local_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 local_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 local_40;
  long local_38;
  
  local_38 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (param_2 == 0xffffffff) {
    puVar3 = calloc(1,0x130);
    if (puVar3 != (undefined4 *)0x0) {
      uStack_d8 = 0;
      local_e0 = 0;
      uStack_d0 = 0;
      local_148 = 0x745f3233746e69;
      local_c8 = 0x10000000004;
      *puVar3 = 0xe;
      uStack_138 = 0;
      uStack_140 = 0;
      uStack_128 = 0;
      uStack_130 = 0;
      uStack_b8 = 0;
      local_c0 = 0x745f3233746e69;
      uStack_a8 = 0;
      uStack_b0 = 0;
      uStack_118 = 0;
      local_120 = 0;
      uStack_108 = 0;
      uStack_110 = 0;
      uStack_98 = 0;
      local_a0 = 0;
      uStack_88 = 0;
      uStack_90 = 0;
      uStack_f8 = 0;
      local_100 = 0;
      uStack_e8 = 0;
      uStack_f0 = 0;
      uStack_78 = 0;
      local_80 = 0;
      uStack_68 = 0;
      uStack_70 = 0;
      *(undefined8 *)(puVar3 + 0x26) = 0;
      uStack_58 = 0;
      local_60 = 0;
      uStack_48 = 0;
      uStack_50 = 0;
      local_40 = 0x10000000004;
      *(undefined8 *)(puVar3 + 3) = 0;
      *(undefined8 *)(puVar3 + 1) = 0x745f3233746e69;
      *(undefined8 *)(puVar3 + 7) = 0;
      *(undefined8 *)(puVar3 + 5) = 0;
      *(undefined8 *)(puVar3 + 0xb) = 0;
      *(undefined8 *)(puVar3 + 9) = 0;
      *(undefined8 *)(puVar3 + 0xf) = 0;
      *(undefined8 *)(puVar3 + 0xd) = 0;
      *(undefined8 *)(puVar3 + 0x13) = 0;
      *(undefined8 *)(puVar3 + 0x11) = 0;
      *(undefined8 *)(puVar3 + 0x17) = 0;
      *(undefined8 *)(puVar3 + 0x15) = 0;
      *(undefined8 *)(puVar3 + 0x1b) = 0;
      *(undefined8 *)(puVar3 + 0x19) = 0;
      *(undefined8 *)(puVar3 + 0x1f) = 0;
      *(undefined8 *)(puVar3 + 0x1d) = 0;
      *(undefined8 *)(puVar3 + 0x21) = 0x10000000004;
    }
  }
  else {
    plVar4 = (long *)*param_1;
    if (param_2 < *(uint *)(plVar4 + 2)) {
      if (*(uint *)(plVar4 + 1) != 0) {
        puVar8 = (undefined8 *)(*plVar4 + 8);
        puVar9 = puVar8 + (ulong)*(uint *)(plVar4 + 1) * 10;
        do {
          if (*(uint *)(puVar8 + 1) != 0) {
            puVar10 = (uint *)*puVar8;
            puVar5 = puVar10 + (ulong)*(uint *)(puVar8 + 1) * 0x22;
            do {
              if (param_2 == puVar10[2]) {
                uVar1 = *puVar10;
                iVar2 = *(int *)(param_1[5] + (ulong)param_2 * 4);
                if (uVar1 - 0xb < 10) {
                  if (iVar2 != 1) {
LAB_0017eae0:
                    if ((0xa400000UL >> ((ulong)uVar1 & 0x3f) & 1) != 0) goto LAB_0017eaec;
                  }
                }
                else {
                  if (iVar2 != 1) {
LAB_0017eaec:
                    puVar3 = calloc(1,0x130);
                    if (puVar3 != (undefined4 *)0x0) {
                      *puVar3 = 0xd;
                      puVar3[0x26] = param_2;
                      __snprintf_chk(puVar3 + 0x27,0x40,2,0x40,&DAT_001f9570,param_2);
                      ir_type_to_hir(&local_1e0,puVar10[3]);
                      *(undefined8 *)(puVar3 + 3) = uStack_1d8;
                      *(undefined8 *)(puVar3 + 1) = local_1e0;
                      *(undefined8 *)(puVar3 + 7) = uStack_1c8;
                      *(undefined8 *)(puVar3 + 5) = uStack_1d0;
                      *(undefined8 *)(puVar3 + 0xb) = uStack_1b8;
                      *(undefined8 *)(puVar3 + 9) = local_1c0;
                      *(undefined8 *)(puVar3 + 0xf) = uStack_1a8;
                      *(undefined8 *)(puVar3 + 0xd) = uStack_1b0;
                      *(undefined8 *)(puVar3 + 0x13) = uStack_198;
                      *(undefined8 *)(puVar3 + 0x11) = local_1a0;
                      *(undefined8 *)(puVar3 + 0x17) = uStack_188;
                      *(undefined8 *)(puVar3 + 0x15) = uStack_190;
                      *(undefined8 *)(puVar3 + 0x1b) = uStack_178;
                      *(undefined8 *)(puVar3 + 0x19) = local_180;
                      *(undefined8 *)(puVar3 + 0x1f) = uStack_168;
                      *(undefined8 *)(puVar3 + 0x1d) = uStack_170;
                      *(undefined8 *)(puVar3 + 0x21) = local_160;
                    }
                    goto LAB_0017eb68;
                  }
                  if (uVar1 < 0x1c) goto LAB_0017eae0;
                }
                lVar7 = 0;
                puVar6 = PTR___stack_chk_guard_005ffe88;
                if (local_38 == *(long *)PTR___stack_chk_guard_005ffe88) {
                  puVar3 = (undefined4 *)build_expr_from_instr(param_1,puVar10,0,0);
                  return puVar3;
                }
                goto LAB_0017ecdc;
              }
              puVar10 = puVar10 + 0x22;
            } while (puVar10 != puVar5);
          }
          puVar8 = puVar8 + 10;
        } while (puVar9 != puVar8);
      }
    }
    puVar3 = calloc(1,0x130);
    if (puVar3 != (undefined4 *)0x0) {
      *puVar3 = 0xd;
      puVar3[0x26] = param_2;
      __snprintf_chk(puVar3 + 0x27,0x40,2,0x40,&DAT_001f9570,param_2);
    }
  }
LAB_0017eb68:
  lVar7 = local_38 - *(long *)PTR___stack_chk_guard_005ffe88;
  param_1 = (long *)PTR___stack_chk_guard_005ffe88;
  puVar6 = (undefined *)0x0;
  if (lVar7 == 0) {
    return puVar3;
  }
LAB_0017ecdc:
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(param_1,puVar6,lVar7);
}

