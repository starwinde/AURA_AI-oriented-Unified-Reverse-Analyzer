
void dfg_parse_reg(byte *param_1)

{
  byte bVar1;
  int iVar2;
  undefined4 uVar3;
  __int32_t **pp_Var4;
  __int32_t *p_Var5;
  int iVar6;
  undefined **ppuVar7;
  char local_50 [24];
  long local_38;
  
  local_38 = *(long *)PTR___stack_chk_guard_005ffe88;
  if ((param_1 != (byte *)0x0) && (bVar1 = *param_1, bVar1 != 0)) {
    pp_Var4 = __ctype_tolower_loc();
    p_Var5 = *pp_Var4;
    local_50[0] = (char)p_Var5[bVar1];
    if (param_1[1] == 0) {
      iVar2 = 1;
    }
    else {
      local_50[1] = (char)p_Var5[param_1[1]];
      if (param_1[2] == 0) {
        iVar2 = 2;
      }
      else {
        local_50[2] = (char)p_Var5[param_1[2]];
        if (param_1[3] == 0) {
          iVar2 = 3;
        }
        else {
          local_50[3] = (char)p_Var5[param_1[3]];
          if (param_1[4] == 0) {
            iVar2 = 4;
          }
          else {
            local_50[4] = (char)p_Var5[param_1[4]];
            if (param_1[5] == 0) {
              iVar2 = 5;
            }
            else {
              local_50[5] = (char)p_Var5[param_1[5]];
              if (param_1[6] == 0) {
                iVar2 = 6;
              }
              else {
                local_50[6] = (char)p_Var5[param_1[6]];
                if (param_1[7] == 0) {
                  iVar2 = 7;
                }
                else {
                  local_50[7] = (char)p_Var5[param_1[7]];
                  if (param_1[8] == 0) {
                    iVar2 = 8;
                  }
                  else {
                    local_50[8] = (char)p_Var5[param_1[8]];
                    if (param_1[9] == 0) {
                      iVar2 = 9;
                    }
                    else {
                      local_50[9] = (char)p_Var5[param_1[9]];
                      if (param_1[10] == 0) {
                        iVar2 = 10;
                      }
                      else {
                        local_50[10] = (char)p_Var5[param_1[10]];
                        if (param_1[0xb] == 0) {
                          iVar2 = 0xb;
                        }
                        else {
                          local_50[0xb] = (char)p_Var5[param_1[0xb]];
                          if (param_1[0xc] == 0) {
                            iVar2 = 0xc;
                          }
                          else {
                            local_50[0xc] = (char)p_Var5[param_1[0xc]];
                            if (param_1[0xd] == 0) {
                              iVar2 = 0xd;
                            }
                            else {
                              local_50[0xd] = (char)p_Var5[param_1[0xd]];
                              if (param_1[0xe] == 0) {
                                iVar2 = 0xe;
                              }
                              else {
                                local_50[0xe] = (char)p_Var5[param_1[0xe]];
                                if (param_1[0xf] == 0) {
                                  iVar2 = 0xf;
                                }
                                else {
                                  iVar2 = 0x10;
                                  local_50[0xf] = (char)p_Var5[param_1[0xf]];
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
    iVar6 = 0;
    ppuVar7 = &REG_TABLE;
    local_50[iVar2] = '\0';
    do {
      iVar2 = strcmp(local_50,*ppuVar7);
      if (iVar2 == 0) {
        uVar3 = (&DAT_005df5d8)[(long)iVar6 * 4];
        goto LAB_00148c34;
      }
      iVar6 = iVar6 + 1;
      ppuVar7 = ppuVar7 + 2;
    } while (iVar6 != 0x30);
  }
  uVar3 = 0xffffffff;
LAB_00148c34:
  if (local_38 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(uVar3,PTR___stack_chk_guard_005ffe88,0,
                     local_38 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return;
}

