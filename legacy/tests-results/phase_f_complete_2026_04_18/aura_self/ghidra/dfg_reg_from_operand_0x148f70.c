
void dfg_reg_from_operand(char *param_1)

{
  ushort uVar1;
  ushort **ppuVar2;
  size_t sVar3;
  char *pcVar4;
  undefined8 uVar5;
  byte *pbVar6;
  ushort *puVar7;
  byte *pbVar8;
  byte local_b8;
  byte local_b7 [62];
  undefined1 local_79;
  byte local_78;
  byte local_77 [62];
  undefined1 local_39;
  long local_38;
  
  local_38 = *(long *)PTR___stack_chk_guard_005ffe88;
  if ((param_1 != (char *)0x0) && (*param_1 != '\0')) {
    pbVar6 = &local_b8;
    strncpy((char *)pbVar6,param_1,0x3f);
    local_79 = 0;
    ppuVar2 = __ctype_b_loc();
    puVar7 = *ppuVar2;
    uVar1 = puVar7[local_b8];
    while ((uVar1 >> 0xd & 1) != 0) {
      pbVar6 = pbVar6 + 1;
      uVar1 = puVar7[*pbVar6];
    }
    sVar3 = strlen((char *)pbVar6);
    pbVar8 = pbVar6 + sVar3;
    if (pbVar6 < pbVar8) {
      do {
        if ((puVar7[pbVar8[-1]] >> 0xd & 1) == 0) break;
        pbVar8 = pbVar8 + -1;
      } while (pbVar8 != pbVar6);
    }
    *pbVar8 = 0;
    if (*pbVar6 == 0x5b) {
      pbVar8 = &local_78;
      strncpy((char *)pbVar8,(char *)(pbVar6 + 1),0x3f);
      local_39 = 0;
      pcVar4 = strpbrk((char *)pbVar8,"+- ]");
      if (pcVar4 != (char *)0x0) {
        *pcVar4 = '\0';
      }
      uVar1 = puVar7[local_78];
      while ((uVar1 >> 0xd & 1) != 0) {
        pbVar8 = pbVar8 + 1;
        uVar1 = puVar7[*pbVar8];
      }
      sVar3 = strlen((char *)pbVar8);
      pbVar6 = pbVar8 + sVar3;
      if (pbVar8 < pbVar6) {
        do {
          if ((puVar7[pbVar6[-1]] >> 0xd & 1) == 0) break;
          pbVar6 = pbVar6 + -1;
        } while (pbVar8 != pbVar6);
      }
      *pbVar6 = 0;
      uVar5 = dfg_parse_reg(pbVar8);
      goto LAB_0014903c;
    }
    pcVar4 = strstr((char *)pbVar6,"ptr");
    if (pcVar4 == (char *)0x0) {
      uVar5 = dfg_parse_reg(pbVar6);
      goto LAB_0014903c;
    }
  }
  uVar5 = 0xffffffff;
LAB_0014903c:
  if (local_38 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(uVar5,PTR___stack_chk_guard_005ffe88,0,
                   local_38 - *(long *)PTR___stack_chk_guard_005ffe88);
}

