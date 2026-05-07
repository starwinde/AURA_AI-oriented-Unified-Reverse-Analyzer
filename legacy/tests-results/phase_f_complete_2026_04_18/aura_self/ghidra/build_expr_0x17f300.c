
undefined4 * build_expr(long *param_1,uint param_2)

{
  uint uVar1;
  undefined4 *puVar2;
  long *plVar3;
  uint *puVar4;
  undefined *puVar5;
  long lVar6;
  undefined8 *puVar7;
  undefined8 *puVar8;
  uint *puVar9;
  undefined8 local_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 local_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 local_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 local_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 local_50;
  long local_38;
  
  local_38 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (param_2 == 0xffffffff) {
    if (local_38 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_38 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    puVar2 = (undefined4 *)hir_const_create(0);
    return puVar2;
  }
  plVar3 = (long *)*param_1;
  if (param_2 < *(uint *)(plVar3 + 2)) {
    if (*(uint *)(plVar3 + 1) != 0) {
      puVar7 = (undefined8 *)(*plVar3 + 8);
      puVar8 = puVar7 + (ulong)*(uint *)(plVar3 + 1) * 10;
      do {
        if (*(uint *)(puVar7 + 1) != 0) {
          puVar9 = (uint *)*puVar7;
          puVar4 = puVar9 + (ulong)*(uint *)(puVar7 + 1) * 0x24;
          do {
            if (param_2 == puVar9[2]) {
              uVar1 = *puVar9;
              if (uVar1 - 0xb < 10) {
LAB_0017f39c:
                if ((0xa400000UL >> ((ulong)uVar1 & 0x3f) & 1) == 0) goto LAB_0017f500;
              }
              else if (uVar1 == 1) {
                if ((puVar9[3] != 5) || (*(int *)(param_1[5] + (ulong)param_2 * 4) == 1)) {
LAB_0017f500:
                  lVar6 = 0;
                  puVar5 = PTR___stack_chk_guard_005ffe88;
                  if (local_38 == *(long *)PTR___stack_chk_guard_005ffe88) {
                    puVar2 = (undefined4 *)build_expr_from_instr(param_1,puVar9,0,0);
                    return puVar2;
                  }
                  goto LAB_0017f550;
                }
              }
              else if (*(int *)(param_1[5] + (ulong)param_2 * 4) == 1) {
                if (uVar1 < 0x1c) goto LAB_0017f39c;
                goto LAB_0017f500;
              }
              puVar2 = calloc(1,0x130);
              if (puVar2 != (undefined4 *)0x0) {
                *puVar2 = 0xd;
                puVar2[0x26] = param_2;
                __snprintf_chk(puVar2 + 0x27,0x40,2,0x40,&DAT_001faae0,param_2);
                ir_type_to_hir_ex(&local_d0,puVar9[3],(char)puVar9[0x22]);
                *(undefined8 *)(puVar2 + 3) = uStack_c8;
                *(undefined8 *)(puVar2 + 1) = local_d0;
                *(undefined8 *)(puVar2 + 7) = uStack_b8;
                *(undefined8 *)(puVar2 + 5) = uStack_c0;
                *(undefined8 *)(puVar2 + 0xb) = uStack_a8;
                *(undefined8 *)(puVar2 + 9) = local_b0;
                *(undefined8 *)(puVar2 + 0xf) = uStack_98;
                *(undefined8 *)(puVar2 + 0xd) = uStack_a0;
                *(undefined8 *)(puVar2 + 0x13) = uStack_88;
                *(undefined8 *)(puVar2 + 0x11) = local_90;
                *(undefined8 *)(puVar2 + 0x17) = uStack_78;
                *(undefined8 *)(puVar2 + 0x15) = uStack_80;
                *(undefined8 *)(puVar2 + 0x1b) = uStack_68;
                *(undefined8 *)(puVar2 + 0x19) = local_70;
                *(undefined8 *)(puVar2 + 0x1f) = uStack_58;
                *(undefined8 *)(puVar2 + 0x1d) = uStack_60;
                *(undefined8 *)(puVar2 + 0x21) = local_50;
              }
              goto LAB_0017f428;
            }
            puVar9 = puVar9 + 0x24;
          } while (puVar9 != puVar4);
        }
        puVar7 = puVar7 + 10;
      } while (puVar8 != puVar7);
    }
  }
  puVar2 = calloc(1,0x130);
  if (puVar2 != (undefined4 *)0x0) {
    *puVar2 = 0xd;
    puVar2[0x26] = param_2;
    __snprintf_chk(puVar2 + 0x27,0x40,2,0x40,&DAT_001faae0,param_2);
  }
LAB_0017f428:
  lVar6 = local_38 - *(long *)PTR___stack_chk_guard_005ffe88;
  param_1 = (long *)PTR___stack_chk_guard_005ffe88;
  puVar5 = (undefined *)0x0;
  if (lVar6 == 0) {
    return puVar2;
  }
LAB_0017f550:
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(param_1,puVar5,lVar6);
}

