
void aura_headless_run(long param_1,int param_2,FILE *param_3)

{
  long lVar1;
  uint uVar2;
  uint uVar3;
  bool bVar4;
  long *plVar5;
  bool bVar6;
  int iVar7;
  uint uVar8;
  long lVar9;
  long *plVar10;
  undefined8 uVar11;
  char *pcVar12;
  undefined1 *puVar13;
  undefined1 *puVar14;
  undefined *puVar15;
  undefined4 uVar16;
  undefined8 *puVar17;
  long lVar18;
  undefined8 *puVar19;
  long lVar20;
  long *plVar21;
  uint uVar22;
  undefined1 *local_c0;
  undefined1 *local_a8;
  void *local_a0;
  int local_8c;
  long *local_80;
  undefined8 local_78;
  undefined8 uStack_70;
  long local_68;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (param_1 == 0) {
    uVar11 = 0xfffffffc;
    goto LAB_0017283c;
  }
  if (param_3 == (FILE *)0x0) {
    param_3 = *(FILE **)PTR_stdout_005fff40;
  }
  pcVar12 = "markdown";
  if (param_2 != 0) {
    pcVar12 = "json";
  }
  aura_log(1,0,0,"headless: analyzing %s (format=%s)",param_1,pcVar12);
  lVar9 = elf_parser_load(param_1);
  if (((lVar9 == 0) && (lVar9 = pe_parser_load(param_1), lVar9 == 0)) &&
     (lVar9 = macho_parser_load(param_1), lVar9 == 0)) {
    aura_log(3,0,0,"headless: failed to load file: %s",param_1);
    uVar11 = 0xfffffff9;
    goto LAB_0017283c;
  }
  uVar22 = *(uint *)(lVar9 + 0x20);
  if (uVar22 == 0) {
LAB_00171868:
    local_a0 = (void *)0x0;
LAB_00171878:
    local_80 = (long *)0x0;
    local_8c = 0;
    if (param_2 != 0) goto LAB_0017187c;
LAB_001723b8:
    plVar5 = local_80;
    fwrite("# AURA Headless Analysis Report\n\n",1,0x21,param_3);
    __fprintf_chk(param_3,2,"**AURA Version:** %s\n\n","2.0.0");
    fwrite("## File Information\n\n",1,0x15,param_3);
    fwrite("| Field | Value |\n",1,0x12,param_3);
    fwrite("|-------|-------|\n",1,0x12,param_3);
    __fprintf_chk(param_3,2,"| File | `%s` |\n",param_1);
    uVar22 = *(uint *)(lVar9 + 8);
    if (uVar22 == 3) {
      pcVar12 = "Mach-O";
    }
    else if (uVar22 < 4) {
      if (uVar22 == 1) {
        pcVar12 = "ELF";
      }
      else {
        pcVar12 = "Unknown";
        if (uVar22 == 2) {
          pcVar12 = "PE";
        }
      }
    }
    else {
      pcVar12 = "Unknown";
      if (uVar22 == 4) {
        pcVar12 = "RAW";
      }
    }
    __fprintf_chk(param_3,2,"| Format | %s |\n",pcVar12);
    uVar22 = *(uint *)(lVar9 + 0xc);
    if (uVar22 == 3) {
      pcVar12 = "ARM";
    }
    else if (uVar22 < 4) {
      if (uVar22 == 1) {
        pcVar12 = "x86";
      }
      else {
        pcVar12 = "Unknown";
        if (uVar22 == 2) {
          pcVar12 = "x86_64";
        }
      }
    }
    else {
      pcVar12 = "Unknown";
      if (uVar22 == 4) {
        pcVar12 = "AArch64";
      }
    }
    __fprintf_chk(param_3,2,"| Architecture | %s |\n",pcVar12);
    __fprintf_chk(param_3,2,"| Entry Point | `0x%lx` |\n",*(undefined8 *)(lVar9 + 0x10));
    __fprintf_chk(param_3,2,"| Sections | %u |\n",*(undefined4 *)(lVar9 + 0x20));
    __fprintf_chk(param_3,2,"| Symbols | %u |\n",*(undefined4 *)(lVar9 + 0x30));
    __fprintf_chk(param_3,2,"| Instructions | %d |\n",local_8c);
    uVar16 = 0;
    if ((plVar5 != (long *)0x0) && (*plVar5 != 0)) {
      uVar16 = *(undefined4 *)(*plVar5 + 8);
    }
    __fprintf_chk(param_3,2,"| Functions | %u |\n\n",uVar16);
    fwrite("## Sections\n\n",1,0xd,param_3);
    fwrite("| # | Name | VAddr | Size | Flags |\n",1,0x24,param_3);
    fwrite("|---|------|-------|------|-------|\n",1,0x24,param_3);
    if (*(int *)(lVar9 + 0x20) != 0) {
      lVar20 = 0;
      uVar22 = 0;
LAB_001725d8:
      plVar21 = (long *)(*(long *)(lVar9 + 0x18) + lVar20);
      uVar8 = *(uint *)(plVar21 + 6);
      if ((uVar8 & 1) != 0) goto LAB_0017297c;
LAB_001725ec:
      local_78 = 0;
      if ((uVar8 >> 1 & 1) != 0) goto LAB_00172900;
LAB_001725f0:
      uStack_70 = 0;
      if ((uVar8 >> 2 & 1) != 0) goto LAB_00172918;
      do {
        lVar1 = *plVar21;
        lVar18 = plVar21[1];
        while( true ) {
          if (lVar1 != 0) {
            __fprintf_chk(param_3,2,"| %u | `%s` | `0x%lx` | %lu | %s |\n",uVar22,lVar1,lVar18,
                          plVar21[3],&local_78);
            uVar22 = uVar22 + 1;
            lVar20 = lVar20 + 0x38;
            if (*(uint *)(lVar9 + 0x20) <= uVar22) goto LAB_0017262c;
            goto LAB_001725d8;
          }
          __fprintf_chk(param_3,2,"| %u | `%s` | `0x%lx` | %lu | %s |\n",uVar22,&DAT_001fca88,lVar18
                        ,plVar21[3],&local_78);
          uVar22 = uVar22 + 1;
          lVar20 = lVar20 + 0x38;
          if (*(uint *)(lVar9 + 0x20) <= uVar22) goto LAB_0017262c;
          plVar21 = (long *)(*(long *)(lVar9 + 0x18) + lVar20);
          uVar8 = *(uint *)(plVar21 + 6);
          if ((uVar8 & 1) == 0) goto LAB_001725ec;
LAB_0017297c:
          local_78 = 0x52;
          if ((uVar8 >> 1 & 1) == 0) goto LAB_001725f0;
LAB_00172900:
          uStack_70 = 0;
          __strcat_chk(&local_78,&DAT_001fb1c8,0x10);
          if ((*(uint *)(plVar21 + 6) >> 2 & 1) == 0) break;
LAB_00172918:
          __strcat_chk(&local_78,&DAT_001fb1d0,0x10);
          lVar1 = *plVar21;
          lVar18 = plVar21[1];
        }
      } while( true );
    }
LAB_0017262c:
    fputc(10,param_3);
    fwrite("## Symbols",1,10,param_3);
    if (0x32 < *(uint *)(lVar9 + 0x30)) {
      __fprintf_chk(param_3,2," (first 50 of %u)");
    }
    fwrite("\n\n",1,2,param_3);
    fwrite("| # | Name | Address | Size | Type |\n",1,0x25,param_3);
    fwrite("|---|------|---------|------|------|\n",1,0x25,param_3);
    uVar2 = *(uint *)(lVar9 + 0x30);
    lVar20 = 0;
    uVar22 = 0;
    uVar8 = uVar2;
    if (0x32 < uVar2) {
      uVar8 = 0x32;
    }
    if (uVar2 != 0) {
      do {
        puVar17 = (undefined8 *)(*(long *)(lVar9 + 0x28) + lVar20);
        uVar2 = *(uint *)(puVar17 + 4);
        bVar6 = uVar2 == 3;
        uVar3 = uVar22;
        bVar4 = false;
        while( true ) {
          puVar15 = &DAT_001fae00;
          if (!bVar6) {
            if (uVar2 < 3 || bVar4) {
              if (uVar2 == 1) {
                puVar15 = &DAT_001f7a00;
              }
              else {
                puVar15 = &DAT_001f8ef8;
                if (uVar2 == 2) {
                  puVar15 = &DAT_001fadf8;
                }
              }
            }
            else {
              puVar15 = &DAT_001f8ef8;
              if (uVar2 == 4) {
                puVar15 = &DAT_001fae08;
              }
            }
          }
          if (puVar17[1] != 0) break;
          lVar20 = lVar20 + 0x28;
          __fprintf_chk(param_3,2,"| %u | `%s` | `0x%lx` | %lu | %s |\n",uVar3,*puVar17,puVar17[2],
                        puVar17[3],puVar15);
          if (uVar8 <= uVar3 + 1) goto LAB_0017273c;
          puVar17 = (undefined8 *)(*(long *)(lVar9 + 0x28) + lVar20);
          uVar2 = *(uint *)(puVar17 + 4);
          bVar6 = uVar2 == 3;
          uVar3 = uVar3 + 1;
          bVar4 = bVar6;
        }
        uVar22 = uVar3 + 1;
        lVar20 = lVar20 + 0x28;
        __fprintf_chk(param_3,2,"| %u | `%s` | `0x%lx` | %lu | %s |\n",uVar3,puVar17[1],puVar17[2],
                      puVar17[3],puVar15);
      } while (uVar22 < uVar8);
    }
LAB_0017273c:
    fputc(10,param_3);
    fwrite("## Functions\n\n",1,0xe,param_3);
    if (((plVar5 == (long *)0x0) || (plVar21 = (long *)*plVar5, plVar21 == (long *)0x0)) ||
       ((int)plVar21[1] == 0)) {
      fwrite("_No functions detected._\n",1,0x19,param_3);
      fputc(10,param_3);
      fwrite("## Call Graph\n\n",1,0xf,param_3);
      if (plVar5 != (long *)0x0) goto LAB_001727bc;
LAB_001727d0:
      fwrite("_No call edges detected._\n",1,0x1a,param_3);
    }
    else {
      fwrite("| # | Name | Start | End | Size |\n",1,0x22,param_3);
      fwrite("|---|------|-------|-----|------|\n",1,0x22,param_3);
      if ((int)plVar21[1] != 0) {
        lVar20 = 0;
        uVar22 = 0;
        do {
          lVar1 = *plVar21 + lVar20;
          puVar17 = (undefined8 *)(*plVar21 + lVar20);
          uVar8 = uVar22 + 1;
          lVar20 = lVar20 + 0x98;
          __fprintf_chk(param_3,2,"| %u | `%s` | `0x%lx` | `0x%lx` | %u |\n",uVar22,lVar1 + 0x14,
                        *puVar17,*(undefined8 *)(lVar1 + 8),*(undefined4 *)(lVar1 + 0x10));
          uVar22 = uVar8;
        } while (uVar8 < *(uint *)(plVar21 + 1));
      }
      fputc(10,param_3);
      fwrite("## Call Graph\n\n",1,0xf,param_3);
LAB_001727bc:
      plVar21 = (long *)plVar5[1];
      if ((plVar21 == (long *)0x0) || ((int)plVar21[1] == 0)) goto LAB_001727d0;
      fwrite("| Caller | Callee | Site |\n",1,0x1b,param_3);
      fwrite("|--------|--------|------|\n",1,0x1b,param_3);
      lVar20 = 0;
      uVar22 = 0;
      if ((int)plVar21[1] != 0) {
        do {
          plVar10 = (long *)*plVar5;
          lVar1 = *plVar21 + lVar20;
          puVar13 = &DAT_001f8ef8;
          pcVar12 = "external";
          if (plVar10 != (long *)0x0) {
            uVar8 = *(uint *)(*plVar21 + lVar20);
            if (uVar8 < *(uint *)(plVar10 + 1)) {
              puVar13 = (undefined1 *)(*plVar10 + (ulong)uVar8 * 0x98 + 0x14);
            }
            uVar8 = *(uint *)(lVar1 + 4);
            pcVar12 = "external";
            if ((uVar8 != 0xffffffff) && (uVar8 < *(uint *)(plVar10 + 1))) {
              pcVar12 = (char *)(*plVar10 + (ulong)uVar8 * 0x98 + 0x14);
            }
          }
          uVar22 = uVar22 + 1;
          lVar20 = lVar20 + 0x18;
          __fprintf_chk(param_3,2,"| `%s` | `%s` | `0x%lx` |\n",puVar13,pcVar12,
                        *(undefined8 *)(lVar1 + 0x10));
        } while (uVar22 < *(uint *)(plVar21 + 1));
      }
    }
    fputc(10,param_3);
  }
  else {
    puVar19 = *(undefined8 **)(lVar9 + 0x18);
    puVar17 = puVar19;
    do {
      if (((char *)*puVar17 != (char *)0x0) &&
         (iVar7 = strcmp((char *)*puVar17,".text"), iVar7 == 0)) goto LAB_00171858;
      puVar17 = puVar17 + 7;
    } while (puVar19 + (ulong)uVar22 * 7 != puVar17);
    uVar8 = *(uint *)(puVar19 + 6);
    puVar17 = puVar19;
    while ((uVar8 >> 2 & 1) == 0) {
      if (puVar19 + (ulong)uVar22 * 7 == puVar17 + 7) goto LAB_00171868;
      uVar8 = *(uint *)(puVar17 + 0xd);
      puVar17 = puVar17 + 7;
    }
LAB_00171858:
    if (((puVar17[5] == 0) || (puVar17[4] == 0)) ||
       (lVar20 = disasm_init(*(undefined4 *)(lVar9 + 0xc)), lVar20 == 0)) goto LAB_00171868;
    local_a0 = calloc(200000,0xe0);
    if (local_a0 == (void *)0x0) {
      disasm_destroy(lVar20);
      goto LAB_00171868;
    }
    iVar7 = disasm_run(lVar20,puVar17[5],puVar17[4],puVar17[1],local_a0,200000);
    local_8c = iVar7;
    if (iVar7 < 0) {
      local_8c = 0;
    }
    disasm_destroy(lVar20);
    local_80 = (long *)0x0;
    if (iVar7 < 1) goto LAB_00171878;
    local_80 = (long *)func_detect(local_a0,(long)local_8c,lVar9,0);
    if (param_2 == 0) goto LAB_001723b8;
LAB_0017187c:
    plVar5 = local_80;
    fwrite(&DAT_001fae60,1,2,param_3);
    fwrite(&DAT_001f8a00,1,2,param_3);
    __fprintf_chk(param_3,2,"\"%s\": \"%s\"",&DAT_001fae68,param_1);
    fwrite(&DAT_001fae80,1,2,param_3);
    fwrite(&DAT_001f8a00,1,2,param_3);
    uVar22 = *(uint *)(lVar9 + 8);
    if (uVar22 == 3) {
      pcVar12 = "Mach-O";
    }
    else if (uVar22 < 4) {
      if (uVar22 == 1) {
        pcVar12 = "ELF";
      }
      else {
        pcVar12 = "Unknown";
        if (uVar22 == 2) {
          pcVar12 = "PE";
        }
      }
    }
    else {
      pcVar12 = "Unknown";
      if (uVar22 == 4) {
        pcVar12 = "RAW";
      }
    }
    __fprintf_chk(param_3,2,"\"%s\": \"%s\"","format",pcVar12);
    fwrite(&DAT_001fae80,1,2,param_3);
    fwrite(&DAT_001f8a00,1,2,param_3);
    uVar22 = *(uint *)(lVar9 + 0xc);
    if (uVar22 == 3) {
      pcVar12 = "ARM";
    }
    else if (uVar22 < 4) {
      if (uVar22 == 1) {
        pcVar12 = "x86";
      }
      else {
        pcVar12 = "Unknown";
        if (uVar22 == 2) {
          pcVar12 = "x86_64";
        }
      }
    }
    else {
      pcVar12 = "Unknown";
      if (uVar22 == 4) {
        pcVar12 = "AArch64";
      }
    }
    __fprintf_chk(param_3,2,"\"%s\": \"%s\"",&DAT_001fae90,pcVar12);
    fwrite(&DAT_001fae80,1,2,param_3);
    fwrite(&DAT_001f8a00,1,2,param_3);
    __fprintf_chk(param_3,2,"\"%s\": \"0x%lx\"","entry_point",*(undefined8 *)(lVar9 + 0x10));
    fwrite(&DAT_001fae80,1,2,param_3);
    fwrite(&DAT_001f8a00,1,2,param_3);
    __fprintf_chk(param_3,2,"\"%s\": \"%s\"","aura_version","2.0.0");
    fwrite(&DAT_001fae80,1,2,param_3);
    fwrite("  \"sections\": [\n",1,0x10,param_3);
    if (*(int *)(lVar9 + 0x20) != 0) {
      lVar20 = 0;
      uVar22 = 0;
      do {
        while( true ) {
          lVar18 = *(long *)(lVar9 + 0x18);
          fwrite("    {",1,5,param_3);
          lVar1 = lVar18 + lVar20;
          puVar14 = *(undefined1 **)(lVar18 + lVar20);
          puVar13 = &DAT_001fca88;
          if (puVar14 != (undefined1 *)0x0) {
            puVar13 = puVar14;
          }
          uVar22 = uVar22 + 1;
          __fprintf_chk(param_3,2,"\"%s\": \"%s\"",&DAT_001fa610,puVar13);
          fwrite(", ",1,2,param_3);
          __fprintf_chk(param_3,2,"\"%s\": \"0x%lx\"","vaddr",*(undefined8 *)(lVar1 + 8));
          fwrite(", ",1,2,param_3);
          __fprintf_chk(param_3,2,"\"%s\": %lu",&DAT_001fa628,*(undefined8 *)(lVar1 + 0x18));
          fwrite(", ",1,2,param_3);
          __fprintf_chk(param_3,2,"\"flags\": %u",*(undefined4 *)(lVar1 + 0x30));
          if (*(uint *)(lVar9 + 0x20) <= uVar22) break;
          __fprintf_chk(param_3,2,&DAT_001faf28,&DAT_001f7a78);
          lVar20 = lVar20 + 0x38;
          if (*(uint *)(lVar9 + 0x20) <= uVar22) goto LAB_00171bd8;
        }
        lVar20 = lVar20 + 0x38;
        __fprintf_chk(param_3,2,&DAT_001faf28,&DAT_001fca88);
      } while (uVar22 < *(uint *)(lVar9 + 0x20));
    }
LAB_00171bd8:
    fwrite("  ],\n",1,5,param_3);
    fwrite("  \"symbols\": [\n",1,0xf,param_3);
    if (*(int *)(lVar9 + 0x30) != 0) {
      local_a8 = &DAT_001fca88;
      lVar20 = 0;
      uVar22 = 0;
      do {
        while( true ) {
          lVar18 = *(long *)(lVar9 + 0x28);
          lVar1 = lVar18 + lVar20;
          fwrite("    {",1,5,param_3);
          puVar13 = *(undefined1 **)(lVar1 + 8);
          if ((*(undefined1 **)(lVar1 + 8) == (undefined1 *)0x0) &&
             (puVar14 = *(undefined1 **)(lVar18 + lVar20), puVar13 = local_a8,
             puVar14 != (undefined1 *)0x0)) {
            puVar13 = puVar14;
          }
          __fprintf_chk(param_3,2,"\"%s\": \"%s\"",&DAT_001fa610,puVar13);
          fwrite(", ",1,2,param_3);
          uVar22 = uVar22 + 1;
          __fprintf_chk(param_3,2,"\"%s\": \"0x%lx\"","address",*(undefined8 *)(lVar1 + 0x10));
          fwrite(", ",1,2,param_3);
          __fprintf_chk(param_3,2,"\"%s\": %lu",&DAT_001fa628,*(undefined8 *)(lVar1 + 0x18));
          fwrite(", ",1,2,param_3);
          __fprintf_chk(param_3,2,"\"type\": %d",*(undefined4 *)(lVar1 + 0x20));
          if (uVar22 < *(uint *)(lVar9 + 0x30)) break;
          lVar20 = lVar20 + 0x28;
          __fprintf_chk(param_3,2,&DAT_001faf28,&DAT_001fca88);
          if (*(uint *)(lVar9 + 0x30) <= uVar22) goto LAB_00171d80;
        }
        __fprintf_chk(param_3,2,&DAT_001faf28,&DAT_001f7a78);
        lVar20 = lVar20 + 0x28;
      } while (uVar22 < *(uint *)(lVar9 + 0x30));
    }
LAB_00171d80:
    fwrite("  ],\n",1,5,param_3);
    fwrite("  \"functions\": [\n",1,0x11,param_3);
    if (plVar5 == (long *)0x0) {
      fwrite("  ],\n",1,5,param_3);
      fwrite("  \"call_graph\": [\n",1,0x12,param_3);
    }
    else {
      plVar21 = (long *)*plVar5;
      if ((plVar21 != (long *)0x0) && ((int)plVar21[1] != 0)) {
        lVar20 = 0;
        uVar22 = 0;
        do {
          while( true ) {
            lVar18 = *plVar21;
            lVar1 = lVar18 + lVar20;
            fwrite("    {",1,5,param_3);
            __fprintf_chk(param_3,2,"\"%s\": \"%s\"",&DAT_001fa610,lVar1 + 0x14);
            fwrite(", ",1,2,param_3);
            uVar22 = uVar22 + 1;
            __fprintf_chk(param_3,2,"\"%s\": \"0x%lx\"","start",*(undefined8 *)(lVar18 + lVar20));
            fwrite(", ",1,2,param_3);
            __fprintf_chk(param_3,2,"\"%s\": \"0x%lx\"",&DAT_001faf68,*(undefined8 *)(lVar1 + 8));
            fwrite(", ",1,2,param_3);
            __fprintf_chk(param_3,2,"\"%s\": %lu",&DAT_001fa628,*(undefined4 *)(lVar1 + 0x10));
            if (uVar22 < *(uint *)(plVar21 + 1)) break;
            lVar20 = lVar20 + 0x98;
            __fprintf_chk(param_3,2,&DAT_001faf28,&DAT_001fca88);
            if (*(uint *)(plVar21 + 1) <= uVar22) goto LAB_00171f54;
          }
          __fprintf_chk(param_3,2,&DAT_001faf28,&DAT_001f7a78);
          lVar20 = lVar20 + 0x98;
        } while (uVar22 < *(uint *)(plVar21 + 1));
      }
LAB_00171f54:
      fwrite("  ],\n",1,5,param_3);
      fwrite("  \"call_graph\": [\n",1,0x12,param_3);
      plVar21 = (long *)plVar5[1];
      if ((plVar21 != (long *)0x0) && ((int)plVar21[1] != 0)) {
        local_c0 = &DAT_001f8ef8;
        lVar20 = 0;
        uVar22 = 0;
        do {
          while( true ) {
            plVar10 = (long *)*plVar5;
            lVar1 = *plVar21 + lVar20;
            puVar13 = local_c0;
            if (plVar10 == (long *)0x0) {
              pcVar12 = "external";
            }
            else {
              uVar8 = *(uint *)(*plVar21 + lVar20);
              if (uVar8 < *(uint *)(plVar10 + 1)) {
                puVar13 = (undefined1 *)(*plVar10 + (ulong)uVar8 * 0x98 + 0x14);
              }
              uVar8 = *(uint *)(lVar1 + 4);
              if ((uVar8 == 0xffffffff) || (*(uint *)(plVar10 + 1) <= uVar8)) {
                pcVar12 = "external";
              }
              else {
                pcVar12 = (char *)(*plVar10 + (ulong)uVar8 * 0x98 + 0x14);
              }
            }
            fwrite("    {",1,5,param_3);
            __fprintf_chk(param_3,2,"\"%s\": \"%s\"","caller",puVar13);
            uVar22 = uVar22 + 1;
            fwrite(", ",1,2,param_3);
            __fprintf_chk(param_3,2,"\"%s\": \"%s\"","callee",pcVar12);
            fwrite(", ",1,2,param_3);
            __fprintf_chk(param_3,2,"\"%s\": \"0x%lx\"",&DAT_001faf98,*(undefined8 *)(lVar1 + 0x10))
            ;
            if (uVar22 < *(uint *)(plVar21 + 1)) break;
            __fprintf_chk(param_3,2,&DAT_001faf28,&DAT_001fca88);
            lVar20 = lVar20 + 0x18;
            if (*(uint *)(plVar21 + 1) <= uVar22) goto LAB_00172130;
          }
          __fprintf_chk(param_3,2,&DAT_001faf28,&DAT_001f7a78);
          lVar20 = lVar20 + 0x18;
        } while (uVar22 < *(uint *)(plVar21 + 1));
      }
    }
LAB_00172130:
    fwrite("  ],\n",1,5,param_3);
    fwrite("  \"stats\": {\n",1,0xd,param_3);
    fwrite(&DAT_001fafb0,1,4,param_3);
    __fprintf_chk(param_3,2,"\"%s\": %lu","section_count",*(undefined4 *)(lVar9 + 0x20));
    fwrite(&DAT_001fae80,1,2,param_3);
    fwrite(&DAT_001fafb0,1,4,param_3);
    __fprintf_chk(param_3,2,"\"%s\": %lu","symbol_count",*(undefined4 *)(lVar9 + 0x30));
    fwrite(&DAT_001fae80,1,2,param_3);
    fwrite(&DAT_001fafb0,1,4,param_3);
    __fprintf_chk(param_3,2,"\"%s\": %lu","instruction_count",(long)local_8c);
    fwrite(&DAT_001fae80,1,2,param_3);
    if (plVar5 == (long *)0x0) {
      fwrite(&DAT_001fafb0,1,4,param_3);
      __fprintf_chk(param_3,2,"\"%s\": %lu","function_count",0);
      fwrite(&DAT_001fae80,1,2,param_3);
LAB_00172a64:
      uVar16 = 0;
    }
    else {
      uVar16 = 0;
      if (*plVar5 != 0) {
        uVar16 = *(undefined4 *)(*plVar5 + 8);
      }
      fwrite(&DAT_001fafb0,1,4,param_3);
      __fprintf_chk(param_3,2,"\"%s\": %lu","function_count",uVar16);
      fwrite(&DAT_001fae80,1,2,param_3);
      if (plVar5[1] == 0) goto LAB_00172a64;
      uVar16 = *(undefined4 *)(plVar5[1] + 8);
    }
    fwrite(&DAT_001fafb0,1,4,param_3);
    __fprintf_chk(param_3,2,"\"%s\": %lu","call_edge_count",uVar16);
    fputc(10,param_3);
    fwrite(&DAT_001fb000,1,4,param_3);
    fwrite(&DAT_001f8448,1,2,param_3);
  }
  func_detect_destroy(&local_80);
  free(local_a0);
  file_info_destroy(lVar9);
  aura_log(1,0,0,"headless: analysis complete");
  uVar11 = 0;
LAB_0017283c:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(uVar11,PTR___stack_chk_guard_005ffe88,0,
                     local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return;
}

