
ulong main(uint param_1,long param_2)

{
  uint uVar1;
  undefined8 uVar2;
  ulong uVar3;
  undefined *puVar4;
  bool bVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  long lVar9;
  long lVar10;
  undefined8 uVar11;
  ulong uVar12;
  long lVar13;
  char *pcVar14;
  char *__s1;
  ulong uVar15;
  ulonglong uVar16;
  long lVar17;
  undefined4 uVar18;
  ulonglong local_a0;
  undefined8 local_90;
  char *local_88;
  undefined1 local_80 [16];
  ulong local_70;
  long local_68;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (1 < (int)param_1) {
    uVar12 = 1;
    iVar7 = 1;
    do {
      while( true ) {
        pcVar14 = *(char **)(param_2 + uVar12 * 8);
        iVar6 = strcmp(pcVar14,"--verbose");
        if (iVar6 != 0) break;
        aura_log_set_level();
        uVar12 = uVar12 + 1;
        aura_log(0,"/home/str_dgx_spark/Desktop/AURA/src/core/aura.c",0x50,"verbose logging enabled"
                );
        if (param_1 == uVar12) goto LAB_0013fa70;
      }
      uVar12 = uVar12 + 1;
      *(char **)(param_2 + (long)iVar7 * 8) = pcVar14;
      iVar7 = iVar7 + 1;
    } while (param_1 != uVar12);
LAB_0013fa70:
    if (1 < iVar7) {
      pcVar14 = *(char **)(param_2 + 8);
      iVar6 = strcmp(pcVar14,"--version");
      if (iVar6 == 0) {
        uVar12 = 0;
        puts("AURA v2.0.0");
        goto LAB_0013fd14;
      }
      if (iVar7 != 2) {
        iVar6 = strcmp(pcVar14,"--disasm");
        if (iVar6 == 0) {
          iVar7 = aura_disasm_file(*(undefined8 *)(param_2 + 0x10));
        }
        else {
          iVar6 = strcmp(pcVar14,"--info");
          if (iVar6 == 0) {
            pcVar14 = *(char **)(param_2 + 0x10);
            uVar18 = 0;
            if ((iVar7 != 3) && (iVar7 = strcmp(pcVar14,"--json"), iVar7 == 0)) {
              pcVar14 = *(char **)(param_2 + 0x18);
              uVar18 = 1;
            }
            iVar7 = aura_info_file(pcVar14,uVar18);
          }
          else {
            if ((5 < iVar7) && (iVar6 = strcmp(pcVar14,"--patch"), iVar6 == 0)) {
              uVar12 = 3;
              lVar17 = 0;
              uVar16 = 0;
              do {
                uVar15 = -(uVar12 >> 0x1f) & 0xfffffff800000000 | uVar12 << 3;
                iVar8 = (int)uVar12;
                uVar1 = iVar8 + 1;
                uVar12 = (ulong)uVar1;
                pcVar14 = *(char **)(param_2 + uVar15);
                iVar6 = strcmp(pcVar14,"--addr");
                if (iVar6 == 0) {
                  if ((int)uVar1 < iVar7) {
                    uVar12 = (ulong)(iVar8 + 2);
                    uVar16 = strtoull(*(char **)(param_2 + uVar15 + 8),(char **)0x0,0);
                  }
                  else {
                    iVar6 = strcmp(pcVar14,"--asm");
                    if (iVar6 == 0) break;
                  }
                }
                else {
                  iVar6 = strcmp(pcVar14,"--asm");
                  if (iVar6 == 0) {
                    if (iVar7 <= (int)uVar1) break;
                    uVar12 = (ulong)(iVar8 + 2);
                    lVar17 = *(long *)(param_2 + uVar15 + 8);
                  }
                }
              } while ((int)uVar12 < iVar7);
              if (uVar16 == 0 || lVar17 == 0) {
                fwrite("usage: aura --patch <file> --addr <hex_addr> --asm \"<instr>\"\n",1,0x3d,
                       *(FILE **)PTR_stderr_005fffd8);
              }
              else {
                uVar15 = patch_encode(lVar17,uVar16,local_80);
                uVar12 = uVar15 & 0xffffffff;
                if ((int)uVar15 == 0) {
                  __printf_chk(2,"patch: %s @ 0x%lx =>",lVar17,uVar16);
                  for (uVar15 = 0; uVar15 < local_70; uVar15 = uVar15 + 1) {
                    __printf_chk(2," %02x",local_80[uVar15]);
                  }
                  putchar(10);
                  goto LAB_0013fd14;
                }
                uVar11 = *(undefined8 *)PTR_stderr_005fffd8;
                aura_error_str(uVar15,PTR_stderr_005fffd8,"aura: patch encode failed: %s\n");
                __fprintf_chk(uVar11,2);
              }
              uVar12 = 1;
              goto LAB_0013fd14;
            }
            iVar6 = strcmp(pcVar14,"--recursive");
            if (iVar6 == 0) {
              iVar7 = aura_recursive_disasm_file(*(undefined8 *)(param_2 + 0x10));
            }
            else {
              iVar6 = strcmp(pcVar14,"--strings");
              if (iVar6 == 0) {
                iVar7 = aura_strings_file(*(undefined8 *)(param_2 + 0x10));
              }
              else {
                iVar6 = strcmp(pcVar14,"--xref");
                if (iVar6 == 0) {
                  uVar11 = *(undefined8 *)(param_2 + 0x10);
                  if (iVar7 != 3) {
                    uVar12 = 3;
                    uVar16 = 0;
                    do {
                      uVar15 = uVar12 << 3;
                      uVar3 = uVar12 >> 0x1f;
                      iVar6 = strcmp(*(char **)(param_2 + (long)(int)uVar12 * 8),"--addr");
                      if (iVar6 == 0) {
                        uVar1 = (int)uVar12 + 1;
                        uVar12 = (ulong)uVar1;
                        if (iVar7 <= (int)uVar1) break;
                        uVar16 = strtoull(*(char **)(param_2 + (-uVar3 & 0xfffffff800000000 | uVar15
                                                               ) + 8),(char **)0x0,0);
                      }
                      uVar1 = (int)uVar12 + 1;
                      uVar12 = (ulong)uVar1;
                    } while ((int)uVar1 < iVar7);
                    if (uVar16 != 0) {
                      iVar7 = aura_xref_file(uVar11,uVar16);
                      goto LAB_0013fd00;
                    }
                  }
                  fwrite("usage: aura --xref <file> --addr <hex_addr>\n",1,0x2c,
                         *(FILE **)PTR_stderr_005fffd8);
LAB_0013ff08:
                  uVar12 = 1;
                  goto LAB_0013fd14;
                }
                iVar6 = strcmp(pcVar14,"--callgraph");
                if (iVar6 == 0) {
                  bVar5 = false;
                  if (iVar7 != 3) {
                    iVar7 = strcmp(*(char **)(param_2 + 0x18),"--dot");
                    bVar5 = iVar7 == 0;
                  }
                  iVar7 = aura_callgraph_file(*(undefined8 *)(param_2 + 0x10),bVar5);
                }
                else {
                  iVar6 = strcmp(pcVar14,"--functions");
                  if (iVar6 != 0) {
                    if (iVar7 == 3) {
LAB_0013fc0c:
                      iVar6 = strcmp(pcVar14,"--headless");
                      if (iVar6 == 0) {
                        lVar17 = 2;
                        pcVar14 = (char *)0x0;
                        uVar18 = 0;
                        do {
                          __s1 = *(char **)(param_2 + lVar17 * 8);
                          iVar6 = strcmp(__s1,"--json");
                          if (iVar6 == 0) {
                            uVar18 = 1;
                          }
                          else if (pcVar14 == (char *)0x0) {
                            pcVar14 = __s1;
                          }
                          lVar17 = lVar17 + 1;
                        } while ((int)lVar17 < iVar7);
                        if (pcVar14 != (char *)0x0) {
                          iVar7 = aura_headless_run(pcVar14,uVar18,
                                                    *(undefined8 *)PTR_stdout_005fff40);
                          goto LAB_0013fd00;
                        }
                        fwrite("usage: aura --headless <file> [--json]\n",1,0x27,
                               *(FILE **)PTR_stderr_005fffd8);
                      }
                      else {
                        iVar6 = strcmp(pcVar14,"--list-analyzers");
                        if (iVar6 == 0) goto LAB_0013fdb0;
                        if ((iVar7 == 3) || (iVar6 = strcmp(pcVar14,"--run-analyzer"), iVar6 != 0))
                        {
                          iVar7 = strcmp(pcVar14,"--run-all-analyzers");
                          if (iVar7 != 0) goto LAB_0013fc74;
                          uVar11 = *(undefined8 *)(param_2 + 0x10);
                          analyzer_registry_init_all();
                          lVar17 = elf_parser_load(uVar11);
                          puVar4 = PTR_stdout_005fff40;
                          if (lVar17 != 0) {
                            lVar9 = analyzer_registry_count();
                            for (lVar13 = 0; lVar13 != lVar9; lVar13 = lVar13 + 1) {
                              lVar10 = analyzer_registry_at(lVar13);
                              if (lVar10 != 0) {
                                local_90 = 0;
                                local_88 = (char *)0x0;
                                iVar7 = (**(code **)(lVar10 + 0x28))
                                                  (lVar17,0,0,0,&local_90,&local_88);
                                if (iVar7 == 0) {
                                  __printf_chk(2,"[%s] %s\n",*(undefined8 *)(lVar10 + 8),
                                               &DAT_001f7348);
                                  if (*(code **)(lVar10 + 0x38) != (code *)0x0) {
                                    (**(code **)(lVar10 + 0x38))(local_90,*(undefined8 *)puVar4);
                                  }
                                }
                                else {
                                  pcVar14 = "SKIPPED";
                                  if (iVar7 != 1) {
                                    pcVar14 = "ERROR";
                                  }
                                  __printf_chk(2,"[%s] %s\n",*(undefined8 *)(lVar10 + 8),pcVar14);
                                }
                                free(local_88);
                                (**(code **)(lVar10 + 0x30))(local_90);
                              }
                            }
                            uVar12 = 0;
                            file_info_destroy(lVar17);
                            goto LAB_0013fd14;
                          }
                        }
                        else {
                          uVar2 = *(undefined8 *)(param_2 + 0x10);
                          uVar11 = *(undefined8 *)(param_2 + 0x18);
                          uVar12 = 4;
                          uVar16 = 0;
                          while (iVar6 = (int)uVar12, iVar6 < iVar7) {
                            uVar15 = -(uVar12 >> 0x1f) & 0xfffffff800000000 | uVar12 << 3;
                            uVar12 = (ulong)(iVar6 + 1U);
                            iVar8 = strcmp(*(char **)(param_2 + uVar15),"--func");
                            if ((iVar8 == 0) && ((int)(iVar6 + 1U) < iVar7)) {
                              uVar12 = (ulong)(iVar6 + 2);
                              uVar16 = strtoull(*(char **)(param_2 + uVar15 + 8),(char **)0x0,0);
                            }
                          }
                          analyzer_registry_init_all();
                          lVar17 = analyzer_registry_get(uVar2);
                          if (lVar17 == 0) {
                            __fprintf_chk(*(undefined8 *)PTR_stderr_005fffd8,2,
                                          "aura: unknown analyzer \'%s\'\n",uVar2);
                            goto LAB_0013ff08;
                          }
                          lVar13 = elf_parser_load(uVar11);
                          if (lVar13 != 0) {
                            local_90 = 0;
                            local_88 = (char *)0x0;
                            iVar7 = (**(code **)(lVar17 + 0x28))
                                              (lVar13,0,0,uVar16,&local_90,&local_88);
                            if (iVar7 == 0) {
                              if (*(code **)(lVar17 + 0x38) == (code *)0x0) {
                                puts("OK (no text formatter)");
                              }
                              else {
                                (**(code **)(lVar17 + 0x38))
                                          (local_90,*(undefined8 *)PTR_stdout_005fff40);
                              }
                            }
                            else if (iVar7 == 1) {
                              puts("SKIPPED: not applicable to this binary");
                            }
                            else {
                              pcVar14 = local_88;
                              if (local_88 == (char *)0x0) {
                                pcVar14 = "unknown";
                              }
                              __fprintf_chk(*(undefined8 *)PTR_stderr_005fffd8,2,"ERROR: %s\n",
                                            pcVar14);
                            }
                            free(local_88);
                            (**(code **)(lVar17 + 0x30))(local_90);
                            file_info_destroy(lVar13);
                            uVar12 = (ulong)(iVar7 != 0);
                            goto LAB_0013fd14;
                          }
                        }
                        __fprintf_chk(*(undefined8 *)PTR_stderr_005fffd8,2,
                                      "aura: failed to load \'%s\'\n",uVar11);
                      }
                    }
                    else {
                      iVar6 = strcmp(pcVar14,"--cfg");
                      if (iVar6 == 0) {
                        uVar11 = *(undefined8 *)(param_2 + 0x10);
                        uVar18 = 0;
                        uVar12 = 3;
                        local_a0 = 0;
                        bVar5 = false;
                        do {
                          uVar15 = -(uVar12 >> 0x1f) & 0xfffffff800000000 | uVar12 << 3;
                          pcVar14 = *(char **)(param_2 + uVar15);
                          iVar6 = strcmp(pcVar14,"--func");
                          if (iVar6 == 0) {
                            uVar1 = (int)uVar12 + 1;
                            uVar12 = (ulong)uVar1;
                            if (iVar7 <= (int)uVar1) {
                              iVar7 = strcmp(pcVar14,"--dot");
                              if (iVar7 == 0) {
                                uVar18 = 1;
                              }
                              break;
                            }
                            bVar5 = true;
                            local_a0 = strtoull(*(char **)(param_2 + uVar15 + 8),(char **)0x0,0);
                          }
                          else {
                            iVar6 = strcmp(pcVar14,"--dot");
                            if (iVar6 == 0) {
                              uVar18 = 1;
                            }
                          }
                          uVar1 = (int)uVar12 + 1;
                          uVar12 = (ulong)uVar1;
                        } while ((int)uVar1 < iVar7);
                        if (bVar5) {
                          iVar7 = aura_cfg_func(uVar11,local_a0,uVar18);
LAB_00140068:
                          uVar12 = (ulong)(iVar7 != 0);
                          goto LAB_0013fd14;
                        }
                        fwrite("usage: aura --cfg <file> --func <addr> [--dot]\n",1,0x2f,
                               *(FILE **)PTR_stderr_005fffd8);
                      }
                      else {
                        iVar6 = strcmp(pcVar14,"--dfg");
                        if (iVar6 == 0) {
                          uVar11 = *(undefined8 *)(param_2 + 0x10);
                          uVar18 = 0;
                          uVar12 = 3;
                          local_a0 = 0;
                          bVar5 = false;
                          do {
                            uVar15 = -(uVar12 >> 0x1f) & 0xfffffff800000000 | uVar12 << 3;
                            pcVar14 = *(char **)(param_2 + uVar15);
                            iVar6 = strcmp(pcVar14,"--func");
                            if (iVar6 == 0) {
                              uVar1 = (int)uVar12 + 1;
                              uVar12 = (ulong)uVar1;
                              if (iVar7 <= (int)uVar1) {
                                iVar7 = strcmp(pcVar14,"--json");
                                if (iVar7 == 0) {
                                  uVar18 = 1;
                                }
                                break;
                              }
                              bVar5 = true;
                              local_a0 = strtoull(*(char **)(param_2 + uVar15 + 8),(char **)0x0,0);
                            }
                            else {
                              iVar6 = strcmp(pcVar14,"--json");
                              if (iVar6 == 0) {
                                uVar18 = 1;
                              }
                            }
                            uVar1 = (int)uVar12 + 1;
                            uVar12 = (ulong)uVar1;
                          } while ((int)uVar1 < iVar7);
                          if (bVar5) {
                            iVar7 = aura_dfg_func(uVar11,local_a0,uVar18);
                            goto LAB_00140068;
                          }
                          fwrite("usage: aura --dfg <file> --func <addr> [--json]\n",1,0x30,
                                 *(FILE **)PTR_stderr_005fffd8);
                        }
                        else {
                          iVar6 = strcmp(pcVar14,"--decompile");
                          if (iVar6 != 0) goto LAB_0013fc0c;
                          uVar11 = *(undefined8 *)(param_2 + 0x10);
                          uVar12 = 3;
                          uVar16 = 0;
                          bVar5 = false;
                          do {
                            uVar15 = -(uVar12 >> 0x1f) & 0xfffffff800000000 | uVar12 << 3;
                            iVar6 = strcmp(*(char **)(param_2 + uVar15),"--func");
                            if (iVar6 == 0) {
                              uVar1 = (int)uVar12 + 1;
                              uVar12 = (ulong)uVar1;
                              if (iVar7 <= (int)uVar1) break;
                              bVar5 = true;
                              uVar16 = strtoull(*(char **)(param_2 + uVar15 + 8),(char **)0x0,0);
                            }
                            uVar1 = (int)uVar12 + 1;
                            uVar12 = (ulong)uVar1;
                          } while ((int)uVar1 < iVar7);
                          if (bVar5) {
                            iVar7 = aura_decompile_func(uVar11,uVar16);
                            goto LAB_0013fd00;
                          }
                          fwrite("usage: aura --decompile <file> --func <addr>\n",1,0x2d,
                                 *(FILE **)PTR_stderr_005fffd8);
                        }
                      }
                    }
                    goto LAB_0013ff08;
                  }
                  iVar7 = aura_functions_file(*(undefined8 *)(param_2 + 0x10));
                }
              }
            }
          }
        }
LAB_0013fd00:
        uVar12 = (ulong)(iVar7 != 0);
        goto LAB_0013fd14;
      }
      iVar7 = strcmp(pcVar14,"--list-analyzers");
      if (iVar7 == 0) {
LAB_0013fdb0:
        analyzer_registry_init_all();
        lVar13 = analyzer_registry_count();
        __printf_chk(2,"Registered analyzers: %zu\n",lVar13);
        for (lVar17 = 0; lVar17 != lVar13; lVar17 = lVar17 + 1) {
          lVar9 = analyzer_registry_at(lVar17);
          if (lVar9 != 0) {
            __printf_chk(2,&DAT_001f7718,*(undefined8 *)(lVar9 + 8),*(undefined8 *)(lVar9 + 0x10));
          }
        }
        uVar12 = 0;
        goto LAB_0013fd14;
      }
    }
  }
LAB_0013fc74:
  puts("AURA: AI-powered Unified Reverse Analyzer");
  uVar12 = 0;
  puts(&DAT_001f7810);
LAB_0013fd14:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return uVar12;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                   local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
}

