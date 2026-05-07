
/* WARNING: Type propagation algorithm not settling */

undefined4 aura_dfg_func(long param_1,ulong param_2,int param_3)

{
  uint uVar1;
  uint *puVar2;
  bool bVar3;
  long *plVar4;
  int iVar5;
  long lVar6;
  long lVar7;
  void *__ptr;
  uint uVar8;
  uint uVar9;
  long lVar10;
  uint uVar11;
  undefined8 *puVar12;
  undefined8 *puVar13;
  ulong uVar14;
  ulong uVar15;
  long lVar16;
  long local_c0;
  undefined4 local_b4;
  long local_b0;
  undefined8 local_a8;
  undefined8 local_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined1 local_88;
  undefined1 uStack_87;
  undefined1 uStack_86;
  undefined1 uStack_85;
  undefined1 uStack_84;
  undefined1 uStack_83;
  undefined1 uStack_82;
  undefined1 uStack_81;
  undefined1 uStack_80;
  undefined1 uStack_7f;
  undefined1 uStack_7e;
  undefined1 uStack_7d;
  undefined1 uStack_7c;
  undefined1 uStack_7b;
  undefined1 uStack_7a;
  undefined1 uStack_79;
  undefined1 uStack_78;
  undefined1 uStack_77;
  undefined1 uStack_76;
  undefined1 uStack_75;
  undefined1 uStack_74;
  undefined1 uStack_73;
  undefined1 uStack_72;
  undefined1 uStack_71;
  undefined1 uStack_70;
  undefined1 uStack_6f;
  undefined1 uStack_6e;
  undefined1 uStack_6d;
  undefined1 uStack_6c;
  undefined1 uStack_6b;
  undefined1 uStack_6a;
  undefined1 uStack_69;
  long local_68;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (param_1 == 0) {
    local_b4 = 0xfffffffc;
  }
  else {
    lVar6 = load_any_format();
    if (lVar6 == 0) {
      __fprintf_chk(*(undefined8 *)PTR_stderr_005fffd8,2,"aura: failed to parse \'%s\'\n",param_1);
LAB_0014349c:
      local_b4 = 0xfffffff9;
    }
    else {
      puVar12 = *(undefined8 **)(lVar6 + 0x18);
      if (*(uint *)(lVar6 + 0x20) != 0) {
        puVar13 = puVar12 + (ulong)*(uint *)(lVar6 + 0x20) * 7;
        do {
          if (((char *)*puVar12 != (char *)0x0) &&
             (iVar5 = strcmp((char *)*puVar12,".text"), iVar5 == 0)) {
            lVar16 = puVar12[5];
            if (lVar16 == 0) {
              __fprintf_chk(*(undefined8 *)PTR_stderr_005fffd8,2,
                            "aura: cannot map .text data from \'%s\'\n",param_1);
              file_info_destroy(lVar6);
              goto LAB_0014349c;
            }
            uVar14 = puVar12[1];
            if (param_2 < uVar14 || uVar14 + puVar12[3] <= param_2) {
              __fprintf_chk(*(undefined8 *)PTR_stderr_005fffd8,2,
                            "aura: func_addr 0x%016lx is outside .text [0x%lx..0x%lx]\n",param_2,
                            uVar14);
              file_info_destroy(lVar6);
              goto LAB_00141ff4;
            }
            lVar7 = disasm_init(*(undefined4 *)(lVar6 + 0xc));
            if (lVar7 == 0) {
              fwrite("aura: disassembler init failed\n",1,0x1f,*(FILE **)PTR_stderr_005fffd8);
              file_info_destroy(lVar6);
LAB_001432c4:
              local_b4 = 0xfffffff8;
            }
            else {
              lVar10 = puVar12[3];
              __ptr = malloc(0x1c000);
              if (__ptr == (void *)0x0) {
                disasm_destroy(lVar7);
                file_info_destroy(lVar6);
              }
              else {
                iVar5 = disasm_run(lVar7,lVar16 + (param_2 - uVar14),(uVar14 + lVar10) - param_2,
                                   param_2,__ptr,0x200);
                disasm_destroy(lVar7);
                file_info_destroy(lVar6);
                if (iVar5 < 1) {
                  __fprintf_chk(*(undefined8 *)PTR_stderr_005fffd8,2,
                                "aura: disasm_run failed at 0x%016lx\n",param_2);
                  free(__ptr);
                  goto LAB_001432c4;
                }
                lVar6 = cfg_build(__ptr,(long)iVar5,param_2);
                local_b0 = lVar6;
                free(__ptr);
                if (lVar6 == 0) {
                  fwrite("aura: cfg_build failed\n",1,0x17,*(FILE **)PTR_stderr_005fffd8);
                }
                else {
                  local_a8 = (long *)dfg_analyze(lVar6);
                  cfg_destroy(&local_b0);
                  plVar4 = local_a8;
                  if (local_a8 != (long *)0x0) {
                    if (param_3 == 0) {
                      __printf_chk(2,"DFG: %s @ 0x%016lx\n",param_1,param_2);
                      __printf_chk(2,"  blocks: %u\n\n",(int)plVar4[1]);
                      if ((int)plVar4[1] != 0) {
                        uVar14 = 0;
                        do {
                          lVar7 = *plVar4;
                          lVar16 = uVar14 * 0x20;
                          __printf_chk(2,"  Block %u:\n",uVar14 & 0xffffffff);
                          lVar6 = lVar7 + lVar16;
                          __printf_chk(2,"    gen : ");
                          uVar8 = *(uint *)(lVar7 + lVar16);
                          if ((uVar8 & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,&DAT_001f7e70);
                            uVar8 = *(uint *)(lVar7 + lVar16);
                          }
                          if ((uVar8 >> 1 & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,&DAT_001f7e80);
                            uVar8 = *(uint *)(lVar7 + lVar16);
                          }
                          if ((uVar8 >> 2 & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,&DAT_001f7e88);
                            uVar8 = *(uint *)(lVar7 + lVar16);
                          }
                          if ((uVar8 >> 3 & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,&DAT_001f7e90);
                            uVar8 = *(uint *)(lVar7 + lVar16);
                          }
                          if ((uVar8 >> 4 & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,&DAT_001f7e98);
                            uVar8 = *(uint *)(lVar7 + lVar16);
                          }
                          if ((uVar8 >> 5 & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,&DAT_001f7ea0);
                            uVar8 = *(uint *)(lVar7 + lVar16);
                          }
                          if ((uVar8 >> 6 & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,&DAT_001f7ea8);
                            uVar8 = *(uint *)(lVar7 + lVar16);
                          }
                          if ((uVar8 >> 7 & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,&DAT_001f7eb0);
                            uVar8 = *(uint *)(lVar7 + lVar16);
                          }
                          if ((uVar8 >> 8 & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,&DAT_0020a320);
                            uVar8 = *(uint *)(lVar7 + lVar16);
                          }
                          if ((uVar8 >> 9 & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,&DAT_0020a330);
                            uVar8 = *(uint *)(lVar7 + lVar16);
                          }
                          if ((uVar8 >> 10 & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,"r10");
                            uVar8 = *(uint *)(lVar7 + lVar16);
                          }
                          if ((uVar8 >> 0xb & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,"r11");
                            uVar8 = *(uint *)(lVar7 + lVar16);
                          }
                          if ((uVar8 >> 0xc & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,"r12");
                            uVar8 = *(uint *)(lVar7 + lVar16);
                          }
                          if ((uVar8 >> 0xd & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,"r13");
                            uVar8 = *(uint *)(lVar7 + lVar16);
                          }
                          if ((uVar8 >> 0xe & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,"r14");
                            uVar8 = *(uint *)(lVar7 + lVar16);
                          }
                          if ((uVar8 >> 0xf & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,"r15");
                          }
                          __printf_chk(2,"\n    kill: ");
                          uVar8 = *(uint *)(lVar6 + 4);
                          if ((uVar8 & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,&DAT_001f7e70);
                            uVar8 = *(uint *)(lVar6 + 4);
                          }
                          if ((uVar8 >> 1 & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,&DAT_001f7e80);
                            uVar8 = *(uint *)(lVar6 + 4);
                          }
                          if ((uVar8 >> 2 & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,&DAT_001f7e88);
                            uVar8 = *(uint *)(lVar6 + 4);
                          }
                          if ((uVar8 >> 3 & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,&DAT_001f7e90);
                            uVar8 = *(uint *)(lVar6 + 4);
                          }
                          if ((uVar8 >> 4 & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,&DAT_001f7e98);
                            uVar8 = *(uint *)(lVar6 + 4);
                          }
                          if ((uVar8 >> 5 & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,&DAT_001f7ea0);
                            uVar8 = *(uint *)(lVar6 + 4);
                          }
                          if ((uVar8 >> 6 & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,&DAT_001f7ea8);
                            uVar8 = *(uint *)(lVar6 + 4);
                          }
                          if ((uVar8 >> 7 & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,&DAT_001f7eb0);
                            uVar8 = *(uint *)(lVar6 + 4);
                          }
                          if ((uVar8 >> 8 & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,&DAT_0020a320);
                            uVar8 = *(uint *)(lVar6 + 4);
                          }
                          if ((uVar8 >> 9 & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,&DAT_0020a330);
                            uVar8 = *(uint *)(lVar6 + 4);
                          }
                          if ((uVar8 >> 10 & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,"r10");
                            uVar8 = *(uint *)(lVar6 + 4);
                          }
                          if ((uVar8 >> 0xb & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,"r11");
                            uVar8 = *(uint *)(lVar6 + 4);
                          }
                          if ((uVar8 >> 0xc & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,"r12");
                            uVar8 = *(uint *)(lVar6 + 4);
                          }
                          if ((uVar8 >> 0xd & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,"r13");
                            uVar8 = *(uint *)(lVar6 + 4);
                          }
                          if ((uVar8 >> 0xe & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,"r14");
                            uVar8 = *(uint *)(lVar6 + 4);
                          }
                          if ((uVar8 >> 0xf & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,"r15");
                          }
                          __printf_chk(2,&DAT_001f7ec8);
                          uVar8 = *(uint *)(lVar6 + 8);
                          if ((uVar8 & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,&DAT_001f7e70);
                            uVar8 = *(uint *)(lVar6 + 8);
                          }
                          if ((uVar8 >> 1 & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,&DAT_001f7e80);
                            uVar8 = *(uint *)(lVar6 + 8);
                          }
                          if ((uVar8 >> 2 & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,&DAT_001f7e88);
                            uVar8 = *(uint *)(lVar6 + 8);
                          }
                          if ((uVar8 >> 3 & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,&DAT_001f7e90);
                            uVar8 = *(uint *)(lVar6 + 8);
                          }
                          if ((uVar8 >> 4 & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,&DAT_001f7e98);
                            uVar8 = *(uint *)(lVar6 + 8);
                          }
                          if ((uVar8 >> 5 & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,&DAT_001f7ea0);
                            uVar8 = *(uint *)(lVar6 + 8);
                          }
                          if ((uVar8 >> 6 & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,&DAT_001f7ea8);
                            uVar8 = *(uint *)(lVar6 + 8);
                          }
                          if ((uVar8 >> 7 & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,&DAT_001f7eb0);
                            uVar8 = *(uint *)(lVar6 + 8);
                          }
                          if ((uVar8 >> 8 & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,&DAT_0020a320);
                            uVar8 = *(uint *)(lVar6 + 8);
                          }
                          if ((uVar8 >> 9 & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,&DAT_0020a330);
                            uVar8 = *(uint *)(lVar6 + 8);
                          }
                          if ((uVar8 >> 10 & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,"r10");
                            uVar8 = *(uint *)(lVar6 + 8);
                          }
                          if ((uVar8 >> 0xb & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,"r11");
                            uVar8 = *(uint *)(lVar6 + 8);
                          }
                          if ((uVar8 >> 0xc & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,"r12");
                            uVar8 = *(uint *)(lVar6 + 8);
                          }
                          if ((uVar8 >> 0xd & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,"r13");
                            uVar8 = *(uint *)(lVar6 + 8);
                          }
                          if ((uVar8 >> 0xe & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,"r14");
                            uVar8 = *(uint *)(lVar6 + 8);
                          }
                          if ((uVar8 >> 0xf & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,"r15");
                          }
                          __printf_chk(2,"\n    out : ");
                          uVar8 = *(uint *)(lVar6 + 0xc);
                          if ((uVar8 & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,&DAT_001f7e70);
                            uVar8 = *(uint *)(lVar6 + 0xc);
                          }
                          if ((uVar8 >> 1 & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,&DAT_001f7e80);
                            uVar8 = *(uint *)(lVar6 + 0xc);
                          }
                          if ((uVar8 >> 2 & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,&DAT_001f7e88);
                            uVar8 = *(uint *)(lVar6 + 0xc);
                          }
                          if ((uVar8 >> 3 & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,&DAT_001f7e90);
                            uVar8 = *(uint *)(lVar6 + 0xc);
                          }
                          if ((uVar8 >> 4 & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,&DAT_001f7e98);
                            uVar8 = *(uint *)(lVar6 + 0xc);
                          }
                          if ((uVar8 >> 5 & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,&DAT_001f7ea0);
                            uVar8 = *(uint *)(lVar6 + 0xc);
                          }
                          if ((uVar8 >> 6 & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,&DAT_001f7ea8);
                            uVar8 = *(uint *)(lVar6 + 0xc);
                          }
                          if ((uVar8 >> 7 & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,&DAT_001f7eb0);
                            uVar8 = *(uint *)(lVar6 + 0xc);
                          }
                          if ((uVar8 >> 8 & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,&DAT_0020a320);
                            uVar8 = *(uint *)(lVar6 + 0xc);
                          }
                          if ((uVar8 >> 9 & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,&DAT_0020a330);
                            uVar8 = *(uint *)(lVar6 + 0xc);
                          }
                          if ((uVar8 >> 10 & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,"r10");
                            uVar8 = *(uint *)(lVar6 + 0xc);
                          }
                          if ((uVar8 >> 0xb & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,"r11");
                            uVar8 = *(uint *)(lVar6 + 0xc);
                          }
                          if ((uVar8 >> 0xc & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,"r12");
                            uVar8 = *(uint *)(lVar6 + 0xc);
                          }
                          if ((uVar8 >> 0xd & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,"r13");
                            uVar8 = *(uint *)(lVar6 + 0xc);
                          }
                          if ((uVar8 >> 0xe & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,"r14");
                            uVar8 = *(uint *)(lVar6 + 0xc);
                          }
                          if ((uVar8 >> 0xf & 1) != 0) {
                            __printf_chk(2,&DAT_001f7e78,"r15");
                          }
                          putchar(10);
                          uVar8 = *(uint *)(lVar6 + 0x18);
                          uVar15 = 0;
                          if (uVar8 != 0) {
                            do {
                              while( true ) {
                                lVar10 = *(long *)(lVar6 + 0x10);
                                lVar7 = uVar15 * 8;
                                lVar16 = lVar10 + lVar7;
                                if ((*(int *)(lVar10 + lVar7) == 0) && (*(int *)(lVar16 + 4) == 0))
                                break;
                                __printf_chk(2,"    [%u] def:",uVar15 & 0xffffffff);
                                uVar8 = *(uint *)(lVar10 + lVar7);
                                if ((uVar8 & 1) != 0) {
                                  __printf_chk(2,&DAT_001f7ef8,&DAT_001f7e70);
                                  uVar8 = *(uint *)(lVar10 + lVar7);
                                }
                                if ((uVar8 >> 1 & 1) != 0) {
                                  __printf_chk(2,&DAT_001f7ef8,&DAT_001f7e80);
                                  uVar8 = *(uint *)(lVar10 + lVar7);
                                }
                                if ((uVar8 >> 2 & 1) != 0) {
                                  __printf_chk(2,&DAT_001f7ef8,&DAT_001f7e88);
                                  uVar8 = *(uint *)(lVar10 + lVar7);
                                }
                                if ((uVar8 >> 3 & 1) != 0) {
                                  __printf_chk(2,&DAT_001f7ef8,&DAT_001f7e90);
                                  uVar8 = *(uint *)(lVar10 + lVar7);
                                }
                                if ((uVar8 >> 4 & 1) != 0) {
                                  __printf_chk(2,&DAT_001f7ef8,&DAT_001f7e98);
                                  uVar8 = *(uint *)(lVar10 + lVar7);
                                }
                                if ((uVar8 >> 5 & 1) != 0) {
                                  __printf_chk(2,&DAT_001f7ef8,&DAT_001f7ea0);
                                  uVar8 = *(uint *)(lVar10 + lVar7);
                                }
                                if ((uVar8 >> 6 & 1) != 0) {
                                  __printf_chk(2,&DAT_001f7ef8,&DAT_001f7ea8);
                                  uVar8 = *(uint *)(lVar10 + lVar7);
                                }
                                if ((uVar8 >> 7 & 1) != 0) {
                                  __printf_chk(2,&DAT_001f7ef8,&DAT_001f7eb0);
                                  uVar8 = *(uint *)(lVar10 + lVar7);
                                }
                                if ((uVar8 >> 8 & 1) != 0) {
                                  __printf_chk(2,&DAT_001f7ef8,&DAT_0020a320);
                                  uVar8 = *(uint *)(lVar10 + lVar7);
                                }
                                if ((uVar8 >> 9 & 1) != 0) {
                                  __printf_chk(2,&DAT_001f7ef8,&DAT_0020a330);
                                  uVar8 = *(uint *)(lVar10 + lVar7);
                                }
                                if ((uVar8 >> 10 & 1) != 0) {
                                  __printf_chk(2,&DAT_001f7ef8,"r10");
                                  uVar8 = *(uint *)(lVar10 + lVar7);
                                }
                                if ((uVar8 >> 0xb & 1) != 0) {
                                  __printf_chk(2,&DAT_001f7ef8,"r11");
                                  uVar8 = *(uint *)(lVar10 + lVar7);
                                }
                                if ((uVar8 >> 0xc & 1) != 0) {
                                  __printf_chk(2,&DAT_001f7ef8,"r12");
                                  uVar8 = *(uint *)(lVar10 + lVar7);
                                }
                                if ((uVar8 >> 0xd & 1) != 0) {
                                  __printf_chk(2,&DAT_001f7ef8,"r13");
                                  uVar8 = *(uint *)(lVar10 + lVar7);
                                }
                                if ((uVar8 >> 0xe & 1) != 0) {
                                  __printf_chk(2,&DAT_001f7ef8,"r14");
                                  uVar8 = *(uint *)(lVar10 + lVar7);
                                }
                                if ((uVar8 >> 0xf & 1) != 0) {
                                  __printf_chk(2,&DAT_001f7ef8,"r15");
                                }
                                __printf_chk(2,"  use:");
                                uVar8 = *(uint *)(lVar16 + 4);
                                if ((uVar8 & 1) != 0) {
                                  __printf_chk(2,&DAT_001f7ef8,&DAT_001f7e70);
                                  uVar8 = *(uint *)(lVar16 + 4);
                                }
                                if ((uVar8 >> 1 & 1) != 0) {
                                  __printf_chk(2,&DAT_001f7ef8,&DAT_001f7e80);
                                  uVar8 = *(uint *)(lVar16 + 4);
                                }
                                if ((uVar8 >> 2 & 1) != 0) {
                                  __printf_chk(2,&DAT_001f7ef8,&DAT_001f7e88);
                                  uVar8 = *(uint *)(lVar16 + 4);
                                }
                                if ((uVar8 >> 3 & 1) != 0) {
                                  __printf_chk(2,&DAT_001f7ef8,&DAT_001f7e90);
                                  uVar8 = *(uint *)(lVar16 + 4);
                                }
                                if ((uVar8 >> 4 & 1) != 0) {
                                  __printf_chk(2,&DAT_001f7ef8,&DAT_001f7e98);
                                  uVar8 = *(uint *)(lVar16 + 4);
                                }
                                if ((uVar8 >> 5 & 1) != 0) {
                                  __printf_chk(2,&DAT_001f7ef8,&DAT_001f7ea0);
                                  uVar8 = *(uint *)(lVar16 + 4);
                                }
                                if ((uVar8 >> 6 & 1) != 0) {
                                  __printf_chk(2,&DAT_001f7ef8,&DAT_001f7ea8);
                                  uVar8 = *(uint *)(lVar16 + 4);
                                }
                                if ((uVar8 >> 7 & 1) != 0) {
                                  __printf_chk(2,&DAT_001f7ef8,&DAT_001f7eb0);
                                  uVar8 = *(uint *)(lVar16 + 4);
                                }
                                if ((uVar8 >> 8 & 1) != 0) {
                                  __printf_chk(2,&DAT_001f7ef8,&DAT_0020a320);
                                  uVar8 = *(uint *)(lVar16 + 4);
                                }
                                if ((uVar8 >> 9 & 1) != 0) {
                                  __printf_chk(2,&DAT_001f7ef8,&DAT_0020a330);
                                  uVar8 = *(uint *)(lVar16 + 4);
                                }
                                if ((uVar8 >> 10 & 1) != 0) {
                                  __printf_chk(2,&DAT_001f7ef8,"r10");
                                  uVar8 = *(uint *)(lVar16 + 4);
                                }
                                if ((uVar8 >> 0xb & 1) != 0) {
                                  __printf_chk(2,&DAT_001f7ef8,"r11");
                                  uVar8 = *(uint *)(lVar16 + 4);
                                }
                                if ((uVar8 >> 0xc & 1) != 0) {
                                  __printf_chk(2,&DAT_001f7ef8,"r12");
                                  uVar8 = *(uint *)(lVar16 + 4);
                                }
                                if ((uVar8 >> 0xd & 1) != 0) {
                                  __printf_chk(2,&DAT_001f7ef8,"r13");
                                  uVar8 = *(uint *)(lVar16 + 4);
                                }
                                if ((uVar8 >> 0xe & 1) != 0) {
                                  __printf_chk(2,&DAT_001f7ef8,"r14");
                                  uVar8 = *(uint *)(lVar16 + 4);
                                }
                                if ((uVar8 >> 0xf & 1) != 0) {
                                  __printf_chk(2,&DAT_001f7ef8,"r15");
                                }
                                putchar(10);
                                uVar8 = *(uint *)(lVar6 + 0x18);
                                uVar15 = uVar15 + 1;
                                if (uVar8 <= (uint)uVar15) goto LAB_00142518;
                              }
                              uVar15 = uVar15 + 1;
                            } while ((uint)uVar15 < uVar8);
                          }
LAB_00142518:
                          putchar(10);
                          uVar14 = uVar14 + 1;
                        } while ((uint)uVar14 < *(uint *)(plVar4 + 1));
                      }
                    }
                    else {
                      puts("{");
                      __printf_chk(2,"  \"file\": \"%s\",\n",param_1);
                      __printf_chk(2,"  \"func_addr\": %lu,\n",param_2);
                      puts("  \"blocks\": [");
                      if ((int)plVar4[1] != 0) {
                        uVar8 = 0;
                        local_c0 = 0;
                        do {
                          lVar6 = *plVar4;
                          puts("    {");
                          __printf_chk(2,"      \"id\": %u,\n",uVar8);
                          lVar16 = lVar6 + local_c0;
                          puVar12 = (undefined8 *)(lVar6 + local_c0);
                          uStack_98 = puVar12[1];
                          local_a0 = *puVar12;
                          lVar6 = 1;
                          local_88 = DAT_00600018;
                          uStack_87 = DAT_00600019;
                          uStack_86 = DAT_0060001a;
                          uStack_85 = DAT_0060001b;
                          uStack_84 = DAT_0060001c;
                          uStack_83 = DAT_0060001d;
                          uStack_82 = DAT_0060001e;
                          uStack_81 = DAT_0060001f;
                          uStack_80 = DAT_00600020;
                          uStack_7f = DAT_00600021;
                          uStack_7e = DAT_00600022;
                          uStack_7d = DAT_00600023;
                          uStack_7c = DAT_00600024;
                          uStack_7b = DAT_00600025;
                          uStack_7a = DAT_00600026;
                          uStack_79 = DAT_00600027;
                          uStack_78 = DAT_00600028;
                          uStack_77 = DAT_00600029;
                          uStack_76 = DAT_0060002a;
                          uStack_75 = DAT_0060002b;
                          uStack_74 = DAT_0060002c;
                          uStack_73 = DAT_0060002d;
                          uStack_72 = DAT_0060002e;
                          uStack_71 = DAT_0060002f;
                          uStack_70 = DAT_00600030;
                          uStack_6f = DAT_00600031;
                          uStack_6e = DAT_00600032;
                          uStack_6d = DAT_00600033;
                          uStack_6c = DAT_00600034;
                          uStack_6b = DAT_00600035;
                          uStack_6a = DAT_00600036;
                          uStack_69 = DAT_00600037;
                          do {
                            lVar7 = 0;
                            __printf_chk(2,"      \"%s\": [",(&uStack_90)[lVar6]);
                            bVar3 = true;
                            uVar9 = *(uint *)((long)&local_a8 + lVar6 * 4 + 4);
                            do {
                              if ((1 << (ulong)((uint)lVar7 & 0x1f) & uVar9) != 0) {
                                if (!bVar3) {
                                  __printf_chk(2,", ");
                                }
                                __printf_chk(2,&DAT_001f7db8,(&s_reg_names)[lVar7]);
                                bVar3 = false;
                              }
                              lVar7 = lVar7 + 1;
                            } while (lVar7 != 0x10);
                            lVar6 = lVar6 + 1;
                            puts("],");
                          } while (lVar6 != 5);
                          puts("      \"insns\": [");
                          lVar6 = 0;
                          uVar9 = *(uint *)(lVar16 + 0x18);
                          uVar11 = 0;
                          if (uVar9 != 0) {
                            do {
                              while( true ) {
                                uVar1 = uVar11 + 1;
                                puVar2 = (uint *)(*(long *)(lVar16 + 0x10) + lVar6);
                                if ((*(int *)(*(long *)(lVar16 + 0x10) + lVar6) == 0) &&
                                   (puVar2[1] == 0)) break;
                                lVar7 = 0;
                                __printf_chk(2,"        {\"idx\": %u, \"def\": [",uVar11);
                                bVar3 = true;
                                do {
                                  if ((1 << (ulong)((uint)lVar7 & 0x1f) & *puVar2) != 0) {
                                    if (!bVar3) {
                                      __printf_chk(2,", ");
                                    }
                                    __printf_chk(2,&DAT_001f7db8,(&s_reg_names)[lVar7]);
                                    bVar3 = false;
                                  }
                                  lVar7 = lVar7 + 1;
                                } while (lVar7 != 0x10);
                                __printf_chk(2,"], \"use\": [");
                                lVar7 = 0;
                                bVar3 = true;
                                do {
                                  if ((1 << (ulong)((uint)lVar7 & 0x1f) & puVar2[1]) != 0) {
                                    if (!bVar3) {
                                      __printf_chk(2,", ");
                                    }
                                    __printf_chk(2,&DAT_001f7db8,(&s_reg_names)[lVar7]);
                                    bVar3 = false;
                                  }
                                  lVar7 = lVar7 + 1;
                                } while (lVar7 != 0x10);
                                __printf_chk(2,&DAT_001f7e20);
                                if (uVar1 < *(uint *)(lVar16 + 0x18)) {
                                  putchar(0x2c);
                                }
                                putchar(10);
                                uVar9 = *(uint *)(lVar16 + 0x18);
                                lVar6 = lVar6 + 8;
                                uVar11 = uVar1;
                                if (uVar9 <= uVar1) goto LAB_00142fc8;
                              }
                              lVar6 = lVar6 + 8;
                              uVar11 = uVar1;
                            } while (uVar1 < uVar9);
                          }
LAB_00142fc8:
                          puts("      ]");
                          uVar8 = uVar8 + 1;
                          __printf_chk(2,"    }");
                          if (uVar8 < *(uint *)(plVar4 + 1)) {
                            putchar(0x2c);
                          }
                          putchar(10);
                          local_c0 = local_c0 + 0x20;
                        } while (uVar8 < *(uint *)(plVar4 + 1));
                      }
                      puts("  ]\n}");
                    }
                    dfg_destroy(&local_a8);
                    local_b4 = 0;
                    goto LAB_00142008;
                  }
                  fwrite("aura: dfg_analyze failed\n",1,0x19,*(FILE **)PTR_stderr_005fffd8);
                }
              }
              local_b4 = 0xfffffffe;
            }
            goto LAB_00142008;
          }
          puVar12 = puVar12 + 7;
        } while (puVar13 != puVar12);
      }
      __fprintf_chk(*(undefined8 *)PTR_stderr_005fffd8,2,"aura: .text section not found in \'%s\'\n"
                    ,param_1);
      file_info_destroy(lVar6);
LAB_00141ff4:
      local_b4 = 0xfffffffa;
    }
  }
LAB_00142008:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                     local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return local_b4;
}

