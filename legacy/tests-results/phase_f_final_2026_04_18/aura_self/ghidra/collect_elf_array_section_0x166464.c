
void collect_elf_array_section
               (long param_1,char *param_2,undefined4 param_3,undefined8 param_4,int param_5,
               int param_6,undefined8 param_7)

{
  ulong uVar1;
  uint uVar2;
  ulong uVar3;
  int iVar4;
  ulong uVar5;
  ulong uVar6;
  undefined8 *puVar7;
  undefined8 *puVar8;
  ulong uVar9;
  ulong uVar10;
  ulong uVar11;
  long lVar12;
  undefined1 auStack_a8 [64];
  long local_68;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (param_1 != 0) {
    puVar7 = *(undefined8 **)(param_1 + 0x18);
    if (*(uint *)(param_1 + 0x20) != 0) {
      puVar8 = puVar7 + (ulong)*(uint *)(param_1 + 0x20) * 7;
      do {
        if (((char *)*puVar7 != (char *)0x0) &&
           (iVar4 = strcmp((char *)*puVar7,param_2), iVar4 == 0)) {
          if ((puVar7[5] != 0) && (uVar5 = puVar7[3], uVar5 != 0)) {
            uVar6 = (ulong)param_5;
            uVar3 = 0;
            if (uVar6 != 0) {
              uVar3 = uVar5 / uVar6;
            }
            if (0x400 < uVar3) {
              uVar3 = 0x400;
            }
            if (uVar6 <= uVar5) {
              if (param_5 == 8) {
                uVar6 = 0;
                uVar10 = 0;
                goto LAB_001666c8;
              }
              if (param_6 != 0) {
                uVar10 = 0;
                uVar9 = 0;
                goto LAB_00166628;
              }
              lVar12 = 0;
              uVar10 = 0;
              goto LAB_00166570;
            }
          }
          break;
        }
        puVar7 = puVar7 + 7;
      } while (puVar7 != puVar8);
    }
  }
  goto LAB_001664f8;
  while (uVar6 = uVar6 + 1, uVar6 < uVar3) {
LAB_001666c8:
    uVar9 = uVar10 + 8;
    if (uVar5 < uVar9) break;
    uVar11 = *(ulong *)(puVar7[5] + uVar10);
    uVar10 = (uVar11 & 0xff00ff00ff00ff00) >> 8 | (uVar11 & 0xff00ff00ff00ff) << 8;
    uVar10 = (uVar10 & 0xffff0000ffff0000) >> 0x10 | (uVar10 & 0xffff0000ffff) << 0x10;
    uVar1 = uVar10 >> 0x20 | uVar10 << 0x20;
    if (param_6 != 0) {
      uVar1 = uVar11;
    }
    uVar10 = uVar9;
    if (uVar1 - 1 < 0xfffffffffffffffe) {
      __snprintf_chk(auStack_a8,0x40,2,0x40,"%s[%zu]",param_4,uVar6);
      uVar6 = uVar6 + 1;
      elist_add_isra_0(param_7,uVar1,param_3,auStack_a8);
      if (uVar3 <= uVar6) break;
      uVar5 = puVar7[3];
      goto LAB_001666c8;
    }
  }
  goto LAB_001664f8;
LAB_00166570:
  if (uVar5 < uVar6 + uVar10) goto LAB_001664f8;
  uVar2 = (*(uint *)(puVar7[5] + uVar10) & 0xff00ff00) >> 8 |
          (*(uint *)(puVar7[5] + uVar10) & 0xff00ff) << 8;
  uVar9 = (ulong)(uVar2 >> 0x10 | uVar2 << 0x10);
  if (uVar9 - 1 < 0xfffffffffffffffe) {
    __snprintf_chk(auStack_a8,0x40,2,0x40,"%s[%zu]",param_4,lVar12);
    elist_add_isra_0(param_7,uVar9,param_3,auStack_a8);
    if (uVar3 <= lVar12 + 1U) goto LAB_001664f8;
    uVar5 = puVar7[3];
  }
  else if (uVar3 <= lVar12 + 1U) goto LAB_001664f8;
  lVar12 = lVar12 + 1;
  uVar10 = uVar6 + uVar10;
  goto LAB_00166570;
  while (uVar10 = uVar10 + 1, uVar10 < uVar3) {
LAB_00166628:
    uVar1 = uVar6 + uVar9;
    if (uVar5 < uVar1) break;
    uVar2 = *(uint *)(puVar7[5] + uVar9);
    uVar9 = uVar1;
    if ((ulong)uVar2 - 1 < 0xfffffffffffffffe) {
      __snprintf_chk(auStack_a8,0x40,2,0x40,"%s[%zu]",param_4,uVar10);
      uVar10 = uVar10 + 1;
      elist_add_isra_0(param_7,(ulong)uVar2,param_3,auStack_a8);
      if (uVar3 <= uVar10) break;
      uVar5 = puVar7[3];
      goto LAB_00166628;
    }
  }
LAB_001664f8:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                     local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return;
}

