
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
  undefined4 uVar15;
  undefined8 *puVar16;
  long lVar17;
  undefined8 *puVar18;
  long lVar19;
  long *plVar20;
  uint uVar21;
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
    goto LAB_001729dc;
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
    goto LAB_001729dc;
  }
  uVar21 = *(uint *)(lVar9 + 0x20);
  if (uVar21 == 0) {
LAB_00171a08:
    local_a0 = (void *)0x0;
LAB_00171a18:
    local_80 = (long *)0x0;
    local_8c = 0;
    if (param_2 != 0) goto LAB_00171a1c;
LAB_00172558:
    plVar5 = local_80;
    fwrite("# AURA Headless Analysis Report\n\n",1,0x21,param_3);
    __fprintf_chk(param_3,2,"**AURA Version:** %s\n\n","2.0.0");
    fwrite("## File Information\n\n",1,0x15,param_3);
    fwrite("| Field | Value |\n",1,0x12,param_3);
    fwrite("|-------|-------|\n",1,0x12,param_3);
    __fprintf_chk(param_3,2,"| File | `%s` |\n",param_1);
    uVar21 = *(uint *)(lVar9 + 8);
    if (uVar21 == 3) {
      pcVar12 = "Mach-O";
    }
    else if (uVar21 < 4) {
      if (uVar21 == 1) {
        pcVar12 = "ELF";
      }
      else {
        pcVar12 = "Unknown";
        if (uVar21 == 2) {
          pcVar12 = "PE";
        }
      }
    }
    else {
      pcVar12 = "Unknown";
      if (uVar21 == 4) {
        pcVar12 = "RAW";
      }
    }
    __fprintf_chk(param_3,2,"| Format | %s |\n",pcVar12);
    uVar21 = *(uint *)(lVar9 + 0xc);
    if (uVar21 == 3) {
      pcVar12 = "ARM";
    }
    else if (uVar21 < 4) {
      if (uVar21 == 1) {
        pcVar12 = "x86";
      }
      else {
        pcVar12 = "Unknown";
        if (uVar21 == 2) {
          pcVar12 = "x86_64";
        }
      }
    }
    else {
      pcVar12 = "Unknown";
      if (uVar21 == 4) {
        pcVar12 = "AArch64";
      }
    }
    __fprintf_chk(param_3,2,"| Architecture | %s |\n",pcVar12);
    __fprintf_chk(param_3,2,"| Entry Point | `0x%lx` |\n",*(undefined8 *)(lVar9 + 0x10));
    __fprintf_chk(param_3,2,"| Sections | %u |\n",*(undefined4 *)(lVar9 + 0x20));
    __fprintf_chk(param_3,2,"| Symbols | %u |\n",*(undefined4 *)(lVar9 + 0x30));
    __fprintf_chk(param_3,2,"| Instructions | %d |\n",local_8c);
    uVar15 = 0;
    if ((plVar5 != (long *)0x0) && (*plVar5 != 0)) {
      uVar15 = *(undefined4 *)(*plVar5 + 8);
    }
    __fprintf_chk(param_3,2,"| Functions | %u |\n\n",uVar15);
    fwrite("## Sections\n\n",1,0xd,param_3);
    fwrite("| # | Name | VAddr | Size | Flags |\n",1,0x24,param_3);
    fwrite("|---|------|-------|------|-------|\n",1,0x24,param_3);
    if (*(int *)(lVar9 + 0x20) != 0) {
      lVar19 = 0;
      uVar21 = 0;
LAB_00172778:
      plVar20 = (long *)(*(long *)(lVar9 + 0x18) + lVar19);
      uVar8 = *(uint *)(plVar20 + 6);
      if ((uVar8 & 1) != 0) goto LAB_00172b1c;
LAB_0017278c:
      local_78 = 0;
      if ((uVar8 >> 1 & 1) != 0) goto LAB_00172aa0;
LAB_00172790:
      uStack_70 = 0;
      if ((uVar8 >> 2 & 1) != 0) goto LAB_00172ab8;
      do {
        lVar1 = *plVar20;
        lVar17 = plVar20[1];
        while( true ) {
          if (lVar1 != 0) {
            __fprintf_chk(param_3,2,"| %u | `%s` | `0x%lx` | %lu | %s |\n",uVar21,lVar1,lVar17,
                          plVar20[3],&local_78);
            uVar21 = uVar21 + 1;
            lVar19 = lVar19 + 0x38;
            if (*(uint *)(lVar9 + 0x20) <= uVar21) goto LAB_001727cc;
            goto LAB_00172778;
          }
          __fprintf_chk(param_3,2,"| %u | `%s` | `0x%lx` | %lu | %s |\n",uVar21,&DAT_001fd0e8,lVar17
                        ,plVar20[3],&local_78);
          uVar21 = uVar21 + 1;
          lVar19 = lVar19 + 0x38;
          if (*(uint *)(lVar9 + 0x20) <= uVar21) goto LAB_001727cc;
          plVar20 = (long *)(*(long *)(lVar9 + 0x18) + lVar19);
          uVar8 = *(uint *)(plVar20 + 6);
          if ((uVar8 & 1) == 0) goto LAB_0017278c;
LAB_00172b1c:
          local_78 = 0x52;
          if ((uVar8 >> 1 & 1) == 0) goto LAB_00172790;
LAB_00172aa0:
          uStack_70 = 0;
          __strcat_chk(&local_78,&DAT_001fb828,0x10);
          if ((*(uint *)(plVar20 + 6) >> 2 & 1) == 0) break;
LAB_00172ab8:
          __strcat_chk(&local_78,&DAT_001fb830,0x10);
          lVar1 = *plVar20;
          lVar17 = plVar20[1];
        }
      } while( true );
    }
LAB_001727cc:
    fputc(10,param_3);
    fwrite("## Symbols",1,10,param_3);
    if (0x32 < *(uint *)(lVar9 + 0x30)) {
      __fprintf_chk(param_3,2," (first 50 of %u)");
    }
    fwrite("\n\n",1,2,param_3);
    fwrite("| # | Name | Address | Size | Type |\n",1,0x25,param_3);
    fwrite("|---|------|---------|------|------|\n",1,0x25,param_3);
    uVar2 = *(uint *)(lVar9 + 0x30);
    lVar19 = 0;
    uVar21 = 0;
    uVar8 = uVar2;
    if (0x32 < uVar2) {
      uVar8 = 0x32;
    }
    if (uVar2 != 0) {
      do {
        puVar16 = (undefined8 *)(*(long *)(lVar9 + 0x28) + lVar19);
        uVar2 = *(uint *)(puVar16 + 4);
        bVar6 = uVar2 == 3;
        uVar3 = uVar21;
        bVar4 = false;
        while( true ) {
          puVar13 = &DAT_001fb460;
          if (!bVar6) {
            if (uVar2 < 3 || bVar4) {
              if (uVar2 == 1) {
                puVar13 = (undefined1 *)0x1f8000;
              }
              else {
                puVar13 = &DAT_001f9560;
                if (uVar2 == 2) {
                  puVar13 = &DAT_001fb458;
                }
              }
            }
            else {
              puVar13 = &DAT_001f9560;
              if (uVar2 == 4) {
                puVar13 = &DAT_001fb468;
              }
            }
          }
          if (puVar16[1] != 0) break;
          lVar19 = lVar19 + 0x28;
          __fprintf_chk(param_3,2,"| %u | `%s` | `0x%lx` | %lu | %s |\n",uVar3,*puVar16,puVar16[2],
                        puVar16[3],puVar13);
          if (uVar8 <= uVar3 + 1) goto LAB_001728dc;
          puVar16 = (undefined8 *)(*(long *)(lVar9 + 0x28) + lVar19);
          uVar2 = *(uint *)(puVar16 + 4);
          bVar6 = uVar2 == 3;
          uVar3 = uVar3 + 1;
          bVar4 = bVar6;
        }
        uVar21 = uVar3 + 1;
        lVar19 = lVar19 + 0x28;
        __fprintf_chk(param_3,2,"| %u | `%s` | `0x%lx` | %lu | %s |\n",uVar3,puVar16[1],puVar16[2],
                      puVar16[3],puVar13);
      } while (uVar21 < uVar8);
    }
LAB_001728dc:
    fputc(10,param_3);
    fwrite("## Functions\n\n",1,0xe,param_3);
    if (((plVar5 == (long *)0x0) || (plVar20 = (long *)*plVar5, plVar20 == (long *)0x0)) ||
       ((int)plVar20[1] == 0)) {
      fwrite("_No functions detected._\n",1,0x19,param_3);
      fputc(10,param_3);
      fwrite("## Call Graph\n\n",1,0xf,param_3);
      if (plVar5 != (long *)0x0) goto LAB_0017295c;
LAB_00172970:
      fwrite("_No call edges detected._\n",1,0x1a,param_3);
    }
    else {
      fwrite("| # | Name | Start | End | Size |\n",1,0x22,param_3);
      fwrite("|---|------|-------|-----|------|\n",1,0x22,param_3);
      if ((int)plVar20[1] != 0) {
        lVar19 = 0;
        uVar21 = 0;
        do {
          lVar1 = *plVar20 + lVar19;
          puVar16 = (undefined8 *)(*plVar20 + lVar19);
          uVar8 = uVar21 + 1;
          lVar19 = lVar19 + 0x98;
          __fprintf_chk(param_3,2,"| %u | `%s` | `0x%lx` | `0x%lx` | %u |\n",uVar21,lVar1 + 0x14,
                        *puVar16,*(undefined8 *)(lVar1 + 8),*(undefined4 *)(lVar1 + 0x10));
          uVar21 = uVar8;
        } while (uVar8 < *(uint *)(plVar20 + 1));
      }
      fputc(10,param_3);
      fwrite("## Call Graph\n\n",1,0xf,param_3);
LAB_0017295c:
      plVar20 = (long *)plVar5[1];
      if ((plVar20 == (long *)0x0) || ((int)plVar20[1] == 0)) goto LAB_00172970;
      fwrite("| Caller | Callee | Site |\n",1,0x1b,param_3);
      fwrite("|--------|--------|------|\n",1,0x1b,param_3);
      lVar19 = 0;
      uVar21 = 0;
      if ((int)plVar20[1] != 0) {
        do {
          plVar10 = (long *)*plVar5;
          lVar1 = *plVar20 + lVar19;
          puVar13 = &DAT_001f9560;
          pcVar12 = "external";
          if (plVar10 != (long *)0x0) {
            uVar8 = *(uint *)(*plVar20 + lVar19);
            if (uVar8 < *(uint *)(plVar10 + 1)) {
              puVar13 = (undefined1 *)(*plVar10 + (ulong)uVar8 * 0x98 + 0x14);
            }
            uVar8 = *(uint *)(lVar1 + 4);
            pcVar12 = "external";
            if ((uVar8 != 0xffffffff) && (uVar8 < *(uint *)(plVar10 + 1))) {
              pcVar12 = (char *)(*plVar10 + (ulong)uVar8 * 0x98 + 0x14);
            }
          }
          uVar21 = uVar21 + 1;
          lVar19 = lVar19 + 0x18;
          __fprintf_chk(param_3,2,"| `%s` | `%s` | `0x%lx` |\n",puVar13,pcVar12,
                        *(undefined8 *)(lVar1 + 0x10));
        } while (uVar21 < *(uint *)(plVar20 + 1));
      }
    }
    fputc(10,param_3);
  }
  else {
    puVar18 = *(undefined8 **)(lVar9 + 0x18);
    puVar16 = puVar18;
    do {
      if (((char *)*puVar16 != (char *)0x0) &&
         (iVar7 = strcmp((char *)*puVar16,".text"), iVar7 == 0)) goto LAB_001719f8;
      puVar16 = puVar16 + 7;
    } while (puVar18 + (ulong)uVar21 * 7 != puVar16);
    uVar8 = *(uint *)(puVar18 + 6);
    puVar16 = puVar18;
    while ((uVar8 >> 2 & 1) == 0) {
      if (puVar18 + (ulong)uVar21 * 7 == puVar16 + 7) goto LAB_00171a08;
      uVar8 = *(uint *)(puVar16 + 0xd);
      puVar16 = puVar16 + 7;
    }
LAB_001719f8:
    if (((puVar16[5] == 0) || (puVar16[4] == 0)) ||
       (lVar19 = disasm_init(*(undefined4 *)(lVar9 + 0xc)), lVar19 == 0)) goto LAB_00171a08;
    local_a0 = calloc(200000,0xe0);
    if (local_a0 == (void *)0x0) {
      disasm_destroy(lVar19);
      goto LAB_00171a08;
    }
    iVar7 = disasm_run(lVar19,puVar16[5],puVar16[4],puVar16[1],local_a0,200000);
    local_8c = iVar7;
    if (iVar7 < 0) {
      local_8c = 0;
    }
    disasm_destroy(lVar19);
    local_80 = (long *)0x0;
    if (iVar7 < 1) goto LAB_00171a18;
    local_80 = (long *)func_detect(local_a0,(long)local_8c,lVar9,0);
    if (param_2 == 0) goto LAB_00172558;
LAB_00171a1c:
    plVar5 = local_80;
    fwrite(&DAT_001fb4c0,1,2,param_3);
    fwrite(&DAT_001f9068,1,2,param_3);
    __fprintf_chk(param_3,2,"\"%s\": \"%s\"",&DAT_001fb4c8,param_1);
    fwrite(&DAT_001fb4e0,1,2,param_3);
    fwrite(&DAT_001f9068,1,2,param_3);
    uVar21 = *(uint *)(lVar9 + 8);
    if (uVar21 == 3) {
      pcVar12 = "Mach-O";
    }
    else if (uVar21 < 4) {
      if (uVar21 == 1) {
        pcVar12 = "ELF";
      }
      else {
        pcVar12 = "Unknown";
        if (uVar21 == 2) {
          pcVar12 = "PE";
        }
      }
    }
    else {
      pcVar12 = "Unknown";
      if (uVar21 == 4) {
        pcVar12 = "RAW";
      }
    }
    __fprintf_chk(param_3,2,"\"%s\": \"%s\"","format",pcVar12);
    fwrite(&DAT_001fb4e0,1,2,param_3);
    fwrite(&DAT_001f9068,1,2,param_3);
    uVar21 = *(uint *)(lVar9 + 0xc);
    if (uVar21 == 3) {
      pcVar12 = "ARM";
    }
    else if (uVar21 < 4) {
      if (uVar21 == 1) {
        pcVar12 = "x86";
      }
      else {
        pcVar12 = "Unknown";
        if (uVar21 == 2) {
          pcVar12 = "x86_64";
        }
      }
    }
    else {
      pcVar12 = "Unknown";
      if (uVar21 == 4) {
        pcVar12 = "AArch64";
      }
    }
    __fprintf_chk(param_3,2,"\"%s\": \"%s\"",&DAT_001fb4f0,pcVar12);
    fwrite(&DAT_001fb4e0,1,2,param_3);
    fwrite(&DAT_001f9068,1,2,param_3);
    __fprintf_chk(param_3,2,"\"%s\": \"0x%lx\"","entry_point",*(undefined8 *)(lVar9 + 0x10));
    fwrite(&DAT_001fb4e0,1,2,param_3);
    fwrite(&DAT_001f9068,1,2,param_3);
    __fprintf_chk(param_3,2,"\"%s\": \"%s\"","aura_version","2.0.0");
    fwrite(&DAT_001fb4e0,1,2,param_3);
    fwrite("  \"sections\": [\n",1,0x10,param_3);
    if (*(int *)(lVar9 + 0x20) != 0) {
      lVar19 = 0;
      uVar21 = 0;
      do {
        while( true ) {
          lVar17 = *(long *)(lVar9 + 0x18);
          fwrite("    {",1,5,param_3);
          lVar1 = lVar17 + lVar19;
          puVar14 = *(undefined1 **)(lVar17 + lVar19);
          puVar13 = &DAT_001fd0e8;
          if (puVar14 != (undefined1 *)0x0) {
            puVar13 = puVar14;
          }
          uVar21 = uVar21 + 1;
          __fprintf_chk(param_3,2,"\"%s\": \"%s\"",&DAT_001fac70,puVar13);
          fwrite(", ",1,2,param_3);
          __fprintf_chk(param_3,2,"\"%s\": \"0x%lx\"","vaddr",*(undefined8 *)(lVar1 + 8));
          fwrite(", ",1,2,param_3);
          __fprintf_chk(param_3,2,"\"%s\": %lu",&DAT_001fac88,*(undefined8 *)(lVar1 + 0x18));
          fwrite(", ",1,2,param_3);
          __fprintf_chk(param_3,2,"\"flags\": %u",*(undefined4 *)(lVar1 + 0x30));
          if (*(uint *)(lVar9 + 0x20) <= uVar21) break;
          __fprintf_chk(param_3,2,&DAT_001fb588,&DAT_001f8078);
          lVar19 = lVar19 + 0x38;
          if (*(uint *)(lVar9 + 0x20) <= uVar21) goto LAB_00171d78;
        }
        lVar19 = lVar19 + 0x38;
        __fprintf_chk(param_3,2,&DAT_001fb588,&DAT_001fd0e8);
      } while (uVar21 < *(uint *)(lVar9 + 0x20));
    }
LAB_00171d78:
    fwrite("  ],\n",1,5,param_3);
    fwrite("  \"symbols\": [\n",1,0xf,param_3);
    if (*(int *)(lVar9 + 0x30) != 0) {
      local_a8 = &DAT_001fd0e8;
      lVar19 = 0;
      uVar21 = 0;
      do {
        while( true ) {
          lVar17 = *(long *)(lVar9 + 0x28);
          lVar1 = lVar17 + lVar19;
          fwrite("    {",1,5,param_3);
          puVar13 = *(undefined1 **)(lVar1 + 8);
          if ((*(undefined1 **)(lVar1 + 8) == (undefined1 *)0x0) &&
             (puVar14 = *(undefined1 **)(lVar17 + lVar19), puVar13 = local_a8,
             puVar14 != (undefined1 *)0x0)) {
            puVar13 = puVar14;
          }
          __fprintf_chk(param_3,2,"\"%s\": \"%s\"",&DAT_001fac70,puVar13);
          fwrite(", ",1,2,param_3);
          uVar21 = uVar21 + 1;
          __fprintf_chk(param_3,2,"\"%s\": \"0x%lx\"","address",*(undefined8 *)(lVar1 + 0x10));
          fwrite(", ",1,2,param_3);
          __fprintf_chk(param_3,2,"\"%s\": %lu",&DAT_001fac88,*(undefined8 *)(lVar1 + 0x18));
          fwrite(", ",1,2,param_3);
          __fprintf_chk(param_3,2,"\"type\": %d",*(undefined4 *)(lVar1 + 0x20));
          if (uVar21 < *(uint *)(lVar9 + 0x30)) break;
          lVar19 = lVar19 + 0x28;
          __fprintf_chk(param_3,2,&DAT_001fb588,&DAT_001fd0e8);
          if (*(uint *)(lVar9 + 0x30) <= uVar21) goto LAB_00171f20;
        }
        __fprintf_chk(param_3,2,&DAT_001fb588,&DAT_001f8078);
        lVar19 = lVar19 + 0x28;
      } while (uVar21 < *(uint *)(lVar9 + 0x30));
    }
LAB_00171f20:
    fwrite("  ],\n",1,5,param_3);
    fwrite("  \"functions\": [\n",1,0x11,param_3);
    if (plVar5 == (long *)0x0) {
      fwrite("  ],\n",1,5,param_3);
      fwrite("  \"call_graph\": [\n",1,0x12,param_3);
    }
    else {
      plVar20 = (long *)*plVar5;
      if ((plVar20 != (long *)0x0) && ((int)plVar20[1] != 0)) {
        lVar19 = 0;
        uVar21 = 0;
        do {
          while( true ) {
            lVar17 = *plVar20;
            lVar1 = lVar17 + lVar19;
            fwrite("    {",1,5,param_3);
            __fprintf_chk(param_3,2,"\"%s\": \"%s\"",&DAT_001fac70,lVar1 + 0x14);
            fwrite(", ",1,2,param_3);
            uVar21 = uVar21 + 1;
            __fprintf_chk(param_3,2,"\"%s\": \"0x%lx\"","start",*(undefined8 *)(lVar17 + lVar19));
            fwrite(", ",1,2,param_3);
            __fprintf_chk(param_3,2,"\"%s\": \"0x%lx\"",&DAT_001fb5c8,*(undefined8 *)(lVar1 + 8));
            fwrite(", ",1,2,param_3);
            __fprintf_chk(param_3,2,"\"%s\": %lu",&DAT_001fac88,*(undefined4 *)(lVar1 + 0x10));
            if (uVar21 < *(uint *)(plVar20 + 1)) break;
            lVar19 = lVar19 + 0x98;
            __fprintf_chk(param_3,2,&DAT_001fb588,&DAT_001fd0e8);
            if (*(uint *)(plVar20 + 1) <= uVar21) goto LAB_001720f4;
          }
          __fprintf_chk(param_3,2,&DAT_001fb588,&DAT_001f8078);
          lVar19 = lVar19 + 0x98;
        } while (uVar21 < *(uint *)(plVar20 + 1));
      }
LAB_001720f4:
      fwrite("  ],\n",1,5,param_3);
      fwrite("  \"call_graph\": [\n",1,0x12,param_3);
      plVar20 = (long *)plVar5[1];
      if ((plVar20 != (long *)0x0) && ((int)plVar20[1] != 0)) {
        local_c0 = &DAT_001f9560;
        lVar19 = 0;
        uVar21 = 0;
        do {
          while( true ) {
            plVar10 = (long *)*plVar5;
            lVar1 = *plVar20 + lVar19;
            puVar13 = local_c0;
            if (plVar10 == (long *)0x0) {
              pcVar12 = "external";
            }
            else {
              uVar8 = *(uint *)(*plVar20 + lVar19);
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
            uVar21 = uVar21 + 1;
            fwrite(", ",1,2,param_3);
            __fprintf_chk(param_3,2,"\"%s\": \"%s\"","callee",pcVar12);
            fwrite(", ",1,2,param_3);
            __fprintf_chk(param_3,2,"\"%s\": \"0x%lx\"",&DAT_001fb5f8,*(undefined8 *)(lVar1 + 0x10))
            ;
            if (uVar21 < *(uint *)(plVar20 + 1)) break;
            __fprintf_chk(param_3,2,&DAT_001fb588,&DAT_001fd0e8);
            lVar19 = lVar19 + 0x18;
            if (*(uint *)(plVar20 + 1) <= uVar21) goto LAB_001722d0;
          }
          __fprintf_chk(param_3,2,&DAT_001fb588,&DAT_001f8078);
          lVar19 = lVar19 + 0x18;
        } while (uVar21 < *(uint *)(plVar20 + 1));
      }
    }
LAB_001722d0:
    fwrite("  ],\n",1,5,param_3);
    fwrite("  \"stats\": {\n",1,0xd,param_3);
    fwrite(&DAT_001fb610,1,4,param_3);
    __fprintf_chk(param_3,2,"\"%s\": %lu","section_count",*(undefined4 *)(lVar9 + 0x20));
    fwrite(&DAT_001fb4e0,1,2,param_3);
    fwrite(&DAT_001fb610,1,4,param_3);
    __fprintf_chk(param_3,2,"\"%s\": %lu","symbol_count",*(undefined4 *)(lVar9 + 0x30));
    fwrite(&DAT_001fb4e0,1,2,param_3);
    fwrite(&DAT_001fb610,1,4,param_3);
    __fprintf_chk(param_3,2,"\"%s\": %lu","instruction_count",(long)local_8c);
    fwrite(&DAT_001fb4e0,1,2,param_3);
    if (plVar5 == (long *)0x0) {
      fwrite(&DAT_001fb610,1,4,param_3);
      __fprintf_chk(param_3,2,"\"%s\": %lu","function_count",0);
      fwrite(&DAT_001fb4e0,1,2,param_3);
LAB_00172c04:
      uVar15 = 0;
    }
    else {
      uVar15 = 0;
      if (*plVar5 != 0) {
        uVar15 = *(undefined4 *)(*plVar5 + 8);
      }
      fwrite(&DAT_001fb610,1,4,param_3);
      __fprintf_chk(param_3,2,"\"%s\": %lu","function_count",uVar15);
      fwrite(&DAT_001fb4e0,1,2,param_3);
      if (plVar5[1] == 0) goto LAB_00172c04;
      uVar15 = *(undefined4 *)(plVar5[1] + 8);
    }
    fwrite(&DAT_001fb610,1,4,param_3);
    __fprintf_chk(param_3,2,"\"%s\": %lu","call_edge_count",uVar15);
    fputc(10,param_3);
    fwrite(&DAT_001fb660,1,4,param_3);
    fwrite(&DAT_001f8ab0,1,2,param_3);
  }
  func_detect_destroy(&local_80);
  free(local_a0);
  file_info_destroy(lVar9);
  aura_log(1,0,0,"headless: analysis complete");
  uVar11 = 0;
LAB_001729dc:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(uVar11,PTR___stack_chk_guard_005ffe88,0,
                     local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return;
}

