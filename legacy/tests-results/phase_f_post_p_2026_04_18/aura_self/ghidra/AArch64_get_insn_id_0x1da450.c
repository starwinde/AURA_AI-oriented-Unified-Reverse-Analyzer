
void AArch64_get_insn_id(long param_1,uint *param_2,undefined8 param_3)

{
  int iVar1;
  undefined1 uVar2;
  ushort uVar3;
  undefined8 *puVar4;
  long lVar5;
  long lVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined1 auStack_f0 [96];
  int local_90;
  long local_38;
  
  local_38 = *(long *)PTR___stack_chk_guard_005ffe88;
  uVar3 = insn_find(insns,0x1517,param_3,param_1 + 0x70);
  if (uVar3 != 0) {
    iVar1 = *(int *)(param_1 + 0x60);
    *param_2 = (uint)*(ushort *)
                      (insns + (((ulong)uVar3 * 2 + (ulong)uVar3) * 0x10 - (ulong)uVar3) * 2 + 2);
    if (iVar1 != 0) {
      puVar4 = *(undefined8 **)(param_2 + 0x3c);
      lVar6 = (ulong)uVar3 * 0x5e;
      uVar7 = *(undefined8 *)(insns + lVar6 + 4);
      uVar9 = *(undefined8 *)(insns + lVar6 + 0x1c);
      uVar8 = *(undefined8 *)(insns + lVar6 + 0x14);
      puVar4[1] = *(undefined8 *)(insns + lVar6 + 0xc);
      *puVar4 = uVar7;
      puVar4[3] = uVar9;
      puVar4[2] = uVar8;
      puVar4[4] = *(undefined8 *)(insns + lVar6 + 0x24);
      local_90 = iVar1;
      uVar2 = count_positive();
      lVar5 = *(long *)(param_2 + 0x3c);
      *(undefined1 *)(lVar5 + 0x28) = uVar2;
      uVar7 = *(undefined8 *)(insns + lVar6 + 0x2c);
      uVar9 = *(undefined8 *)(insns + lVar6 + 0x44);
      uVar8 = *(undefined8 *)(insns + lVar6 + 0x3c);
      *(undefined8 *)(lVar5 + 0x32) = *(undefined8 *)(insns + lVar6 + 0x34);
      *(undefined8 *)(lVar5 + 0x2a) = uVar7;
      *(undefined8 *)(lVar5 + 0x42) = uVar9;
      *(undefined8 *)(lVar5 + 0x3a) = uVar8;
      *(undefined8 *)(lVar5 + 0x4a) = *(undefined8 *)(insns + lVar6 + 0x4c);
      uVar2 = count_positive();
      lVar5 = *(long *)(param_2 + 0x3c);
      *(undefined1 *)(lVar5 + 0x52) = uVar2;
      *(undefined8 *)(lVar5 + 0x53) = *(undefined8 *)(insns + lVar6 + 0x54);
      uVar2 = count_positive8(lVar6 + 0x2e40fc);
      lVar5 = *(long *)(param_2 + 0x3c);
      *(undefined1 *)(lVar5 + 0x5b) = uVar2;
      uVar2 = cs_reg_write(auStack_f0,param_2,4);
      *(undefined1 *)(lVar5 + 100) = uVar2;
    }
  }
  if (local_38 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                   local_38 - *(long *)PTR___stack_chk_guard_005ffe88);
}

