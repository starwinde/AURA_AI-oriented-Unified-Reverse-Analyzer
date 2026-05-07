
void aura_info_file(long param_1,int param_2)

{
  long *plVar1;
  undefined1 *puVar2;
  char *pcVar3;
  undefined *puVar4;
  uint uVar5;
  long lVar6;
  char *pcVar7;
  undefined1 *puVar8;
  undefined8 uVar9;
  long lVar10;
  long lVar11;
  uint uVar12;
  long lVar13;
  undefined1 local_70;
  undefined1 local_6f;
  undefined1 local_6e;
  undefined1 local_6d;
  long local_68;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (param_1 == 0) {
    uVar9 = 0xfffffffc;
  }
  else {
    lVar6 = load_any_format(param_1,0);
    if (lVar6 == 0) {
      __fprintf_chk(*(undefined8 *)PTR_stderr_005fffd8,2,"aura: failed to parse \'%s\'\n",param_1);
      uVar9 = 0xfffffff9;
    }
    else {
      if (param_2 == 0) {
        __printf_chk(2,"File:   %s\n",param_1);
        uVar12 = *(uint *)(lVar6 + 8);
        if (uVar12 == 3) {
          pcVar7 = "Mach-O";
        }
        else if (uVar12 < 4) {
          if (uVar12 == 1) {
            pcVar7 = "ELF";
          }
          else {
            pcVar7 = "Unknown";
            if (uVar12 == 2) {
              pcVar7 = "PE";
            }
          }
        }
        else {
          pcVar7 = "Unknown";
          if (uVar12 == 4) {
            pcVar7 = "Raw";
          }
        }
        __printf_chk(2,"Format: %s\n",pcVar7);
        uVar9 = aura_arch_name(*(undefined4 *)(lVar6 + 0xc));
        __printf_chk(2,"Arch:   %s\n",uVar9);
        __printf_chk(2,"Entry:  0x%016lx\n",*(undefined8 *)(lVar6 + 0x10));
        __printf_chk(2,"\nSections (%u):\n",*(undefined4 *)(lVar6 + 0x20));
        if (*(int *)(lVar6 + 0x20) != 0) {
          lVar11 = 0;
          uVar12 = 0;
          do {
            while( true ) {
              lVar10 = *(long *)(lVar6 + 0x18) + lVar11;
              uVar5 = *(uint *)(lVar10 + 0x30);
              local_6d = 0;
              local_6f = 0x2d;
              local_70 = local_6f;
              if ((uVar5 & 1) != 0) {
                local_70 = 0x72;
              }
              if ((uVar5 & 2) != 0) {
                local_6f = 0x77;
              }
              local_6e = 0x2d;
              if ((uVar5 & 4) != 0) {
                local_6e = 0x78;
              }
              lVar13 = *(long *)(*(long *)(lVar6 + 0x18) + lVar11);
              if (lVar13 == 0) break;
              uVar5 = uVar12 + 1;
              __printf_chk(2,"  [%u] %-20s vaddr=0x%016lx  size=0x%08lx  %s\n",uVar12,lVar13,
                           *(undefined8 *)(lVar10 + 8),*(undefined8 *)(lVar10 + 0x18),&local_70);
              lVar11 = lVar11 + 0x38;
              uVar12 = uVar5;
              if (*(uint *)(lVar6 + 0x20) <= uVar5) goto LAB_001416f4;
            }
            __printf_chk(2,"  [%u] %-20s vaddr=0x%016lx  size=0x%08lx  %s\n",uVar12,"(null)",
                         *(undefined8 *)(lVar10 + 8),*(undefined8 *)(lVar10 + 0x18),&local_70);
            uVar12 = uVar12 + 1;
            lVar11 = lVar11 + 0x38;
          } while (uVar12 < *(uint *)(lVar6 + 0x20));
        }
LAB_001416f4:
        __printf_chk(2,"\nSymbols (%u):\n",*(undefined4 *)(lVar6 + 0x30));
        if (*(int *)(lVar6 + 0x30) != 0) {
          lVar11 = 0;
          uVar12 = 0;
          do {
            plVar1 = (long *)(*(long *)(lVar6 + 0x28) + lVar11);
            uVar5 = *(uint *)(plVar1 + 4);
            if (uVar5 == 3) {
              pcVar7 = "IMPORT";
            }
            else if (uVar5 < 4) {
              if (uVar5 == 1) {
                pcVar7 = "FUNC";
              }
              else {
                pcVar7 = "UNKNOWN";
                if (uVar5 == 2) {
                  pcVar7 = "OBJECT";
                }
              }
            }
            else {
              pcVar7 = "UNKNOWN";
              if (uVar5 == 4) {
                pcVar7 = "EXPORT";
              }
            }
            if (*(int *)((long)plVar1 + 0x24) == 1) {
              lVar10 = plVar1[1];
              pcVar3 = "GLOBAL";
            }
            else {
              lVar10 = plVar1[1];
              pcVar3 = "WEAK";
              if (*(int *)((long)plVar1 + 0x24) != 2) {
                pcVar3 = "LOCAL";
              }
            }
            if (lVar10 == 0) {
              lVar10 = *plVar1;
            }
            __printf_chk(2,"  [%u] 0x%016lx  %-7s %-7s %s\n",uVar12,plVar1[2],pcVar7,pcVar3,lVar10);
            uVar12 = uVar12 + 1;
            lVar11 = lVar11 + 0x28;
          } while (uVar12 < *(uint *)(lVar6 + 0x30));
        }
      }
      else {
        puts("{");
        __printf_chk(2,"  \"file\": ");
        print_json_str(param_1);
        puts(",");
        __printf_chk(2,"  \"format\": ");
        uVar12 = *(uint *)(lVar6 + 8);
        if (uVar12 == 3) {
          pcVar7 = "Mach-O";
        }
        else if (uVar12 < 4) {
          if (uVar12 == 1) {
            pcVar7 = "ELF";
          }
          else {
            pcVar7 = "Unknown";
            if (uVar12 == 2) {
              pcVar7 = "PE";
            }
          }
        }
        else {
          pcVar7 = "Unknown";
          if (uVar12 == 4) {
            pcVar7 = "Raw";
          }
        }
        print_json_str(pcVar7);
        puts(",");
        __printf_chk(2,"  \"arch\": ");
        aura_arch_name(*(undefined4 *)(lVar6 + 0xc));
        print_json_str();
        puts(",");
        __printf_chk(2,"  \"entry_point\": %lu,\n",*(undefined8 *)(lVar6 + 0x10));
        puts("  \"sections\": [");
        puVar4 = PTR_stdout_005fff40;
        if (*(int *)(lVar6 + 0x20) != 0) {
          lVar11 = 0;
          uVar12 = 0;
          do {
            while( true ) {
              lVar13 = *(long *)(lVar6 + 0x18);
              lVar10 = lVar13 + lVar11;
              uVar12 = uVar12 + 1;
              uVar5 = *(uint *)(lVar10 + 0x30);
              local_6d = 0;
              local_6f = 0x2d;
              local_70 = local_6f;
              if ((uVar5 & 1) != 0) {
                local_70 = 0x72;
              }
              if ((uVar5 & 2) != 0) {
                local_6f = 0x77;
              }
              local_6e = 0x2d;
              if ((uVar5 & 4) != 0) {
                local_6e = 0x78;
              }
              __printf_chk(2,"    {\"name\": ");
              puVar8 = *(undefined1 **)(lVar13 + lVar11);
              puVar2 = &DAT_001fd0e8;
              if (puVar8 != (undefined1 *)0x0) {
                puVar2 = puVar8;
              }
              print_json_str(puVar2);
              __printf_chk(2,", \"vaddr\": %lu, \"size\": %lu, \"flags\": \"%s\"}",
                           *(undefined8 *)(lVar10 + 8),*(undefined8 *)(lVar10 + 0x18),&local_70);
              if (*(uint *)(lVar6 + 0x20) <= uVar12) break;
              lVar11 = lVar11 + 0x38;
              putc(0x2c,*(FILE **)puVar4);
              putc(10,*(FILE **)puVar4);
              if (*(uint *)(lVar6 + 0x20) <= uVar12) goto LAB_00141410;
            }
            lVar11 = lVar11 + 0x38;
            putc(10,*(FILE **)puVar4);
          } while (uVar12 < *(uint *)(lVar6 + 0x20));
        }
LAB_00141410:
        puts("  ],");
        puts("  \"symbols\": [");
        puVar4 = PTR_stdout_005fff40;
        if (*(int *)(lVar6 + 0x30) != 0) {
          lVar11 = 0;
          uVar12 = 0;
LAB_001414ac:
          do {
            lVar13 = *(long *)(lVar6 + 0x28);
            __printf_chk(2,"    {\"name\": ");
            lVar10 = lVar13 + lVar11;
            if (*(long *)(lVar10 + 8) == 0) {
              print_json_str(*(undefined8 *)(lVar13 + lVar11));
              uVar5 = *(uint *)(lVar10 + 0x20);
              uVar9 = *(undefined8 *)(lVar10 + 0x10);
              if (uVar5 == 3) goto LAB_00141870;
LAB_001414dc:
              if (uVar5 < 3) {
                if (uVar5 == 1) {
                  pcVar7 = "FUNC";
                }
                else {
                  pcVar7 = "UNKNOWN";
                  if (uVar5 == 2) {
                    pcVar7 = "OBJECT";
                  }
                }
              }
              else {
                pcVar7 = "UNKNOWN";
                if (uVar5 == 4) {
                  pcVar7 = "EXPORT";
                }
              }
            }
            else {
              print_json_str();
              uVar5 = *(uint *)(lVar10 + 0x20);
              uVar9 = *(undefined8 *)(lVar10 + 0x10);
              if (uVar5 != 3) goto LAB_001414dc;
LAB_00141870:
              pcVar7 = "IMPORT";
            }
            if (*(int *)(lVar10 + 0x24) != 1) {
              pcVar3 = "WEAK";
              if (*(int *)(lVar10 + 0x24) != 2) {
                pcVar3 = "LOCAL";
              }
              __printf_chk(2,", \"address\": %lu, \"type\": \"%s\", \"binding\": \"%s\"}",uVar9,
                           pcVar7,pcVar3);
              if (*(uint *)(lVar6 + 0x30) <= uVar12 + 1) goto LAB_00141490;
LAB_00141530:
              uVar12 = uVar12 + 1;
              lVar11 = lVar11 + 0x28;
              putc(0x2c,*(FILE **)puVar4);
              putc(10,*(FILE **)puVar4);
              if (*(uint *)(lVar6 + 0x30) <= uVar12) break;
              goto LAB_001414ac;
            }
            __printf_chk(2,", \"address\": %lu, \"type\": \"%s\", \"binding\": \"%s\"}",uVar9,pcVar7
                         ,"GLOBAL");
            if (uVar12 + 1 < *(uint *)(lVar6 + 0x30)) goto LAB_00141530;
LAB_00141490:
            uVar12 = uVar12 + 1;
            lVar11 = lVar11 + 0x28;
            putc(10,*(FILE **)puVar4);
          } while (uVar12 < *(uint *)(lVar6 + 0x30));
        }
        puts("  ]");
        puts("}");
      }
      file_info_destroy(lVar6);
      uVar9 = 0;
    }
  }
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(uVar9,PTR___stack_chk_guard_005ffe88,0,
                   local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
}

