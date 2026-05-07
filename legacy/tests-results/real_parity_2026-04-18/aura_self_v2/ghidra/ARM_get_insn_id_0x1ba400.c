
void ARM_get_insn_id(long param_1,uint *param_2,uint param_3)

{
  int iVar1;
  byte bVar2;
  undefined1 uVar3;
  undefined8 *puVar4;
  long lVar5;
  long lVar6;
  uint uVar7;
  int iVar8;
  ulong uVar9;
  uint uVar10;
  uint uVar11;
  long lVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  undefined1 auStack_f0 [96];
  int local_90;
  long local_38;
  
  local_38 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (param_3 < 0xc90) {
    uVar10 = 0xa79;
    uVar9 = 0xa79;
    uVar7 = 0x6e0;
    uVar11 = 0;
    while( true ) {
      uVar9 = uVar9 >> 1;
      iVar8 = (int)uVar9;
      if (param_3 == uVar7) break;
      if (param_3 < uVar7) {
        uVar10 = iVar8 - 1;
        if (uVar10 < uVar11) goto LAB_001ba494;
      }
      else {
        uVar11 = iVar8 + 1;
        if (uVar10 < uVar11) goto LAB_001ba494;
      }
      uVar9 = (ulong)(uVar10 + uVar11);
      uVar7 = (uint)*(ushort *)
                     (insns + (uVar9 & 0xfffffffe) * 0x20 + (ulong)(uVar10 + uVar11 >> 1) * 0x1e);
    }
    iVar1 = *(int *)(param_1 + 0x60);
    lVar5 = ((ulong)(uint)(iVar8 << 1) * 0x10 + uVar9 * 0xf) * 2;
    *param_2 = (uint)*(ushort *)(insns + lVar5 + 2);
    if (iVar1 != 0) {
      puVar4 = *(undefined8 **)(param_2 + 0x3c);
      lVar12 = uVar9 * 0x5e;
      uVar13 = *(undefined8 *)(insns + lVar12 + 4);
      uVar15 = *(undefined8 *)(insns + lVar12 + 0x1c);
      uVar14 = *(undefined8 *)(insns + lVar12 + 0x14);
      puVar4[1] = *(undefined8 *)(insns + lVar12 + 0xc);
      *puVar4 = uVar13;
      puVar4[3] = uVar15;
      puVar4[2] = uVar14;
      puVar4[4] = *(undefined8 *)(insns + lVar12 + 0x24);
      local_90 = iVar1;
      uVar3 = count_positive();
      lVar6 = *(long *)(param_2 + 0x3c);
      *(undefined1 *)(lVar6 + 0x28) = uVar3;
      uVar13 = *(undefined8 *)(insns + lVar12 + 0x2c);
      uVar15 = *(undefined8 *)(insns + lVar12 + 0x44);
      uVar14 = *(undefined8 *)(insns + lVar12 + 0x3c);
      *(undefined8 *)(lVar6 + 0x32) = *(undefined8 *)(insns + lVar12 + 0x34);
      *(undefined8 *)(lVar6 + 0x2a) = uVar13;
      *(undefined8 *)(lVar6 + 0x42) = uVar15;
      *(undefined8 *)(lVar6 + 0x3a) = uVar14;
      *(undefined8 *)(lVar6 + 0x4a) = *(undefined8 *)(insns + lVar12 + 0x4c);
      uVar3 = count_positive();
      lVar6 = *(long *)(param_2 + 0x3c);
      *(undefined1 *)(lVar6 + 0x52) = uVar3;
      *(undefined8 *)(lVar6 + 0x53) = *(undefined8 *)(insns + lVar12 + 0x54);
      uVar3 = count_positive8(lVar12 + 0x24ded4);
      lVar6 = *(long *)(param_2 + 0x3c);
      *(undefined1 *)(lVar6 + 0x5b) = uVar3;
      uVar3 = cs_reg_write(auStack_f0,param_2,3);
      *(undefined1 *)(lVar6 + 0x78) = uVar3;
      if (((insns[lVar5 + 0x5c] & 1) != 0) || ((insns[lVar5 + 0x5d] & 1) != 0)) {
        lVar5 = *(long *)(param_2 + 0x3c);
        bVar2 = *(byte *)(lVar5 + 0x5b);
        *(undefined1 *)(lVar5 + (ulong)bVar2 + 0x53) = 1;
        *(byte *)(lVar5 + 0x5b) = bVar2 + 1;
      }
    }
  }
LAB_001ba494:
  if (local_38 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                     local_38 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return;
}

