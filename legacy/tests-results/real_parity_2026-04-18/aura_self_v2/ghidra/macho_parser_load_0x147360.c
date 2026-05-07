
long * macho_parser_load(long param_1)

{
  bool bVar1;
  uint *puVar2;
  ulong uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  long *plVar9;
  uint *puVar10;
  uint uVar11;
  ulong uVar12;
  ulong uVar13;
  long local_30;
  long local_28;
  
  local_28 = *(long *)PTR___stack_chk_guard_005ffe88;
  if ((param_1 != 0) &&
     (local_30 = mapped_file_open(param_1,PTR___stack_chk_guard_005ffe88,0), local_30 != 0)) {
    plVar9 = (long *)file_info_create(&local_30);
    if (plVar9 == (long *)0x0) {
      plVar9 = (long *)0x0;
      mapped_file_destroy(local_30);
      goto LAB_001473f8;
    }
    puVar2 = *(uint **)(*plVar9 + 8);
    uVar3 = *(ulong *)(*plVar9 + 0x10);
    if (7 < uVar3) {
      uVar11 = *puVar2;
      if (uVar11 == 0xbebafeca) {
        uVar11 = puVar2[1];
        if (((uVar11 != 0) && (0x13 < uVar3)) && (7 < uVar3 - 0x14)) {
          uVar5 = (uVar11 & 0xff00ff00) >> 8 | (uVar11 & 0xff00ff) << 8;
          puVar10 = puVar2 + 4;
          uVar11 = 0;
          do {
            uVar4 = puVar10[1];
            uVar6 = (uVar4 & 0xff00ff00) >> 8 | (uVar4 & 0xff00ff) << 8;
            uVar12 = (ulong)(uVar6 >> 0x10 | uVar6 << 0x10);
            uVar4 = (uVar4 & 0xff00ff00) >> 8 | (uVar4 & 0xff00ff) << 8;
            uVar4 = uVar4 >> 0x10 | uVar4 << 0x10;
            if (uVar12 <= uVar3) {
              uVar6 = *puVar10;
              uVar7 = (uVar6 & 0xff00ff00) >> 8 | (uVar6 & 0xff00ff) << 8;
              uVar13 = (ulong)(uVar7 >> 0x10 | uVar7 << 0x10);
              uVar6 = (uVar6 & 0xff00ff00) >> 8 | (uVar6 & 0xff00ff) << 8;
              bVar1 = uVar3 - uVar12 < uVar13;
              if (((!bVar1 && 6 < uVar4) && (bVar1 || uVar4 != 7)) &&
                 (uVar4 = *(uint *)((long)puVar2 + (ulong)(uVar6 >> 0x10 | uVar6 << 0x10)),
                 uVar4 + 0x1120532 < 2 || (uVar4 & 0xfeffffff) == 0xcefaedfe)) {
                iVar8 = macho_parse_inner(plVar9,puVar2,uVar3,uVar13);
                goto LAB_001473f4;
              }
            }
            uVar11 = uVar11 + 1;
          } while ((uVar11 < (uVar5 >> 0x10 | uVar5 << 0x10)) &&
                  (puVar10 = puVar10 + 5,
                  (ulong)((-8 - (long)puVar2) + (long)puVar10) <= uVar3 - 0x14));
        }
      }
      else if (uVar11 + 0x1120532 < 2 || (uVar11 & 0xfeffffff) == 0xcefaedfe) {
        iVar8 = macho_parse_inner();
LAB_001473f4:
        if (iVar8 == 0) goto LAB_001473f8;
      }
    }
    file_info_destroy(plVar9);
  }
  plVar9 = (long *)0x0;
LAB_001473f8:
  if (local_28 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return plVar9;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                   local_28 - *(long *)PTR___stack_chk_guard_005ffe88);
}

