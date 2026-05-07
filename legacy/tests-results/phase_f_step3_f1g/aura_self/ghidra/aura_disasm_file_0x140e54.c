
undefined4 aura_disasm_file(long param_1)

{
  long *plVar1;
  undefined1 *puVar2;
  int iVar3;
  long lVar4;
  long lVar5;
  long lVar6;
  undefined8 uVar7;
  ulong uVar8;
  undefined8 *puVar9;
  undefined1 *puVar10;
  undefined8 uVar11;
  ulong uVar12;
  ulong uVar13;
  undefined1 *puVar14;
  ulong uVar15;
  undefined8 *puVar16;
  ulong uVar17;
  undefined4 local_e094;
  undefined1 local_e068 [8];
  undefined1 local_e060 [944];
  undefined8 local_dcb0;
  undefined1 auStack_2070 [8200];
  long local_68;
  
  local_dcb0 = 0;
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (param_1 == 0) {
    local_e094 = 0xfffffffc;
  }
  else {
    lVar4 = elf_parser_load();
    if (lVar4 == 0) {
      __fprintf_chk(*(undefined8 *)PTR_stderr_005fffd8,2,"aura: failed to load ELF: \'%s\'\n",
                    param_1);
      local_e094 = 0xfffffffd;
    }
    else {
      puVar16 = *(undefined8 **)(lVar4 + 0x18);
      if (*(uint *)(lVar4 + 0x20) != 0) {
        puVar9 = puVar16 + (ulong)*(uint *)(lVar4 + 0x20) * 7;
        do {
          if (((char *)*puVar16 != (char *)0x0) &&
             (iVar3 = strcmp((char *)*puVar16,".text"), iVar3 == 0)) {
            lVar5 = puVar16[5];
            if (lVar5 == 0) {
              __fprintf_chk(*(undefined8 *)PTR_stderr_005fffd8,2,
                            "aura: cannot map .text data from \'%s\'\n",param_1);
              file_info_destroy(lVar4);
              local_e094 = 0xfffffff9;
              goto LAB_001410b0;
            }
            lVar6 = disasm_init(*(undefined4 *)(lVar4 + 0xc));
            if (lVar6 != 0) {
              uVar13 = 0;
              uVar7 = aura_arch_name(*(undefined4 *)(lVar4 + 0xc));
              __printf_chk(2,"Disassembly of .text from \'%s\' [%s]:\n",param_1,uVar7);
              __printf_chk(2,"  0x%016lx .. 0x%016lx  (%lu bytes)\n\n",puVar16[1],
                           puVar16[1] + puVar16[3]);
              uVar8 = puVar16[3];
              if (uVar8 != 0) goto LAB_00140fa8;
              goto LAB_001410a0;
            }
            uVar11 = *(undefined8 *)PTR_stderr_005fffd8;
            uVar7 = aura_arch_name(*(undefined4 *)(lVar4 + 0xc));
            __fprintf_chk(uVar11,2,"aura: disassembler init failed (arch: %s)\n",uVar7);
            file_info_destroy(lVar4);
            local_e094 = 0xfffffff8;
            goto LAB_001410b0;
          }
          puVar16 = puVar16 + 7;
        } while (puVar16 != puVar9);
      }
      __fprintf_chk(*(undefined8 *)PTR_stderr_005fffd8,2,"aura: .text section not found in \'%s\'\n"
                    ,param_1);
      file_info_destroy(lVar4);
      local_e094 = 0xfffffffa;
    }
  }
  goto LAB_001410b0;
LAB_00140fa8:
  do {
    iVar3 = disasm_run(lVar6,lVar5 + uVar13,uVar8 - uVar13,uVar13 + puVar16[1],local_e068,0x100);
    if (iVar3 < 1) break;
    puVar10 = local_e060;
    puVar14 = puVar10 + (long)iVar3 * 0xe0;
    do {
      uVar15 = 0;
      __printf_chk(2,"  0x%016lx:  ",*(undefined8 *)(puVar10 + -8));
      uVar12 = *(ulong *)(puVar10 + 0x10);
      uVar17 = uVar12;
      if (8 < uVar12) {
        uVar17 = 8;
      }
      if (uVar12 == 0) {
LAB_00141048:
        do {
          uVar17 = uVar17 + 1;
          __printf_chk(2,&DAT_001f79d0);
        } while (uVar17 != 8);
      }
      else {
        do {
          puVar2 = puVar10 + uVar15;
          uVar15 = uVar15 + 1;
          __printf_chk(2,"%02x ",*puVar2);
        } while (uVar15 < uVar17);
        if (uVar12 < 8) goto LAB_00141048;
      }
      if (puVar10[0x58] == '\0') {
        __printf_chk(2,&DAT_001f7720,puVar10 + 0x18);
      }
      else {
        __printf_chk(2," %-10s %s\n",puVar10 + 0x18,puVar10 + 0x58);
      }
      plVar1 = (long *)(puVar10 + 0x10);
      puVar10 = puVar10 + 0xe0;
      uVar13 = uVar13 + *plVar1;
    } while (puVar14 != puVar10);
  } while (uVar13 < uVar8);
LAB_001410a0:
  disasm_destroy(lVar6);
  file_info_destroy(lVar4);
  local_e094 = 0;
LAB_001410b0:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,auStack_2070,
                     local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return local_e094;
}

