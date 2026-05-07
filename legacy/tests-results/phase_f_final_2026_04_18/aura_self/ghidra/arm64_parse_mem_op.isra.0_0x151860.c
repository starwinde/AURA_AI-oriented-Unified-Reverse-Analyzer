
void arm64_parse_mem_op_isra_0(char *param_1,undefined4 *param_2,longlong *param_3)

{
  char cVar1;
  byte bVar2;
  char cVar3;
  ushort uVar4;
  uint3 uVar5;
  uint uVar6;
  uint5 uVar7;
  uint6 uVar8;
  uint7 uVar9;
  int iVar10;
  size_t sVar11;
  char *pcVar12;
  char *pcVar13;
  longlong lVar14;
  char *pcVar15;
  undefined1 auStack_4c [4];
  undefined8 local_48;
  undefined8 local_40;
  long local_38;
  
  local_38 = *(long *)PTR___stack_chk_guard_005ffe88;
  *param_2 = 0xfffffffe;
  *param_3 = 0;
  cVar1 = *param_1;
  while (cVar1 == ' ') {
    param_1 = param_1 + 1;
    cVar1 = *param_1;
  }
  if (cVar1 == '[') {
    bVar2 = param_1[1];
    local_48 = 0;
    local_40 = 0;
    if ((bVar2 == 0x2c || bVar2 == 0) || bVar2 == 0x5d) {
      param_1 = param_1 + 1;
      iVar10 = 0;
    }
    else {
      cVar1 = param_1[2];
      local_48 = (ulong)bVar2;
      if ((cVar1 == ',' || cVar1 == '\0') || cVar1 == ']') {
        param_1 = param_1 + 2;
        iVar10 = 1;
      }
      else {
        cVar3 = param_1[3];
        local_48._0_2_ = CONCAT11(cVar1,bVar2);
        uVar4 = (ushort)local_48;
        local_48 = (ulong)(ushort)local_48;
        if ((cVar3 == ',' || cVar3 == '\0') || cVar3 == ']') {
          param_1 = param_1 + 3;
          iVar10 = 2;
        }
        else {
          cVar1 = param_1[4];
          local_48._0_3_ = CONCAT12(cVar3,uVar4);
          uVar5 = (uint3)local_48;
          local_48 = (ulong)(uint3)local_48;
          if ((cVar1 == ',' || cVar1 == '\0') || cVar1 == ']') {
            param_1 = param_1 + 4;
            iVar10 = 3;
          }
          else {
            cVar3 = param_1[5];
            local_48._0_4_ = CONCAT13(cVar1,uVar5);
            uVar6 = (uint)local_48;
            local_48 = (ulong)(uint)local_48;
            if ((cVar3 == ',' || cVar3 == '\0') || cVar3 == ']') {
              param_1 = param_1 + 5;
              iVar10 = 4;
            }
            else {
              cVar1 = param_1[6];
              local_48._0_5_ = CONCAT14(cVar3,uVar6);
              uVar7 = (uint5)local_48;
              local_48 = (ulong)(uint5)local_48;
              if ((cVar1 == ',' || cVar1 == '\0') || cVar1 == ']') {
                param_1 = param_1 + 6;
                iVar10 = 5;
              }
              else {
                cVar3 = param_1[7];
                local_48._0_6_ = CONCAT15(cVar1,uVar7);
                uVar8 = (uint6)local_48;
                local_48 = (ulong)(uint6)local_48;
                if ((cVar3 == ',' || cVar3 == '\0') || cVar3 == ']') {
                  param_1 = param_1 + 7;
                  iVar10 = 6;
                }
                else {
                  cVar1 = param_1[8];
                  local_48._0_7_ = CONCAT16(cVar3,uVar8);
                  uVar9 = (uint7)local_48;
                  local_48 = (ulong)(uint7)local_48;
                  if ((cVar1 == ',' || cVar1 == '\0') || cVar1 == ']') {
                    param_1 = param_1 + 8;
                    iVar10 = 7;
                  }
                  else {
                    bVar2 = param_1[9];
                    local_48 = CONCAT17(cVar1,uVar9);
                    if ((bVar2 == 0x2c || bVar2 == 0) || bVar2 == 0x5d) {
                      param_1 = param_1 + 9;
                      iVar10 = 8;
                    }
                    else {
                      cVar1 = param_1[10];
                      local_40 = (ulong)bVar2;
                      if ((cVar1 == ',' || cVar1 == '\0') || cVar1 == ']') {
                        param_1 = param_1 + 10;
                        iVar10 = 9;
                      }
                      else {
                        cVar3 = param_1[0xb];
                        local_40._0_2_ = CONCAT11(cVar1,bVar2);
                        uVar4 = (ushort)local_40;
                        local_40 = (ulong)(ushort)local_40;
                        if ((cVar3 == ',' || cVar3 == '\0') || cVar3 == ']') {
                          param_1 = param_1 + 0xb;
                          iVar10 = 10;
                        }
                        else {
                          cVar1 = param_1[0xc];
                          local_40._0_3_ = CONCAT12(cVar3,uVar4);
                          uVar5 = (uint3)local_40;
                          local_40 = (ulong)(uint3)local_40;
                          if ((cVar1 == ',' || cVar1 == '\0') || cVar1 == ']') {
                            param_1 = param_1 + 0xc;
                            iVar10 = 0xb;
                          }
                          else {
                            cVar3 = param_1[0xd];
                            local_40._0_4_ = CONCAT13(cVar1,uVar5);
                            uVar6 = (uint)local_40;
                            local_40 = (ulong)(uint)local_40;
                            if ((cVar3 == ',' || cVar3 == '\0') || cVar3 == ']') {
                              param_1 = param_1 + 0xd;
                              iVar10 = 0xc;
                            }
                            else {
                              cVar1 = param_1[0xe];
                              local_40._0_5_ = CONCAT14(cVar3,uVar6);
                              uVar7 = (uint5)local_40;
                              local_40 = (ulong)(uint5)local_40;
                              if ((cVar1 == ',' || cVar1 == '\0') || cVar1 == ']') {
                                param_1 = param_1 + 0xe;
                                iVar10 = 0xd;
                              }
                              else {
                                cVar3 = param_1[0xf];
                                local_40._0_6_ = CONCAT15(cVar1,uVar7);
                                uVar8 = (uint6)local_40;
                                local_40 = (ulong)(uint6)local_40;
                                if ((cVar3 == ',' || cVar3 == '\0') || cVar3 == ']') {
                                  param_1 = param_1 + 0xf;
                                  iVar10 = 0xe;
                                }
                                else {
                                  param_1 = param_1 + 0x10;
                                  iVar10 = 0xf;
                                  local_40 = (ulong)CONCAT16(cVar3,uVar8);
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    pcVar15 = (char *)&local_48;
    pcVar15[iVar10] = '\0';
    cVar1 = (char)local_48;
    while (cVar1 == ' ') {
      pcVar15 = pcVar15 + 1;
      cVar1 = *pcVar15;
    }
    sVar11 = strlen(pcVar15);
    pcVar13 = pcVar15 + (sVar11 - 1);
    if (pcVar15 < pcVar15 + (sVar11 - 1)) {
      do {
        if (*pcVar13 != ' ') break;
        pcVar12 = pcVar13 + -1;
        *pcVar13 = '\0';
        pcVar13 = pcVar12;
      } while (pcVar12 != pcVar15);
    }
    iVar10 = arm64_reg_lookup(pcVar15,param_2,auStack_4c);
    if ((iVar10 != 0) && (*param_1 == ',')) {
      pcVar15 = param_1 + 1;
      cVar1 = param_1[1];
      while (cVar1 == ' ') {
        pcVar15 = pcVar15 + 1;
        cVar1 = *pcVar15;
      }
      if (cVar1 == '#') {
        pcVar15 = pcVar15 + 1;
      }
      lVar14 = strtoll(pcVar15,(char **)0x0,0);
      *param_3 = lVar14;
    }
  }
  if (local_38 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                     local_38 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return;
}

