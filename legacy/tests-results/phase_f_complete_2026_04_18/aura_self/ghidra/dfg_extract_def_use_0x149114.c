
void dfg_extract_def_use(long param_1,uint *param_2,uint *param_3)

{
  char *__s1;
  ushort uVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  char *pcVar7;
  ushort **ppuVar8;
  size_t sVar9;
  char *pcVar10;
  byte *pbVar11;
  ushort *puVar12;
  byte *__dest;
  byte *pbVar13;
  byte local_158;
  byte local_157 [126];
  undefined1 local_d9;
  char acStack_d8 [127];
  undefined1 local_59;
  long local_58;
  
  pcVar10 = (char *)(param_1 + 0x60);
  __dest = &local_158;
  __s1 = (char *)(param_1 + 0x20);
  local_58 = *(long *)PTR___stack_chk_guard_005ffe88;
  *param_2 = 0;
  *param_3 = 0;
  strncpy((char *)__dest,pcVar10,0x7f);
  local_d9 = 0;
  pcVar7 = strchr((char *)__dest,0x2c);
  if (pcVar7 == (char *)0x0) {
    iVar3 = strcasecmp(__s1,"mov");
    if (iVar3 == 0) goto LAB_001494b0;
    pbVar13 = (byte *)0x0;
    __dest = (byte *)0x0;
    bVar2 = false;
    iVar3 = strcasecmp(__s1,"movsx");
    if (iVar3 == 0) goto LAB_001494b0;
LAB_0014925c:
    iVar3 = strcasecmp(__s1,"movzx");
    if ((iVar3 == 0) || (iVar3 = strcasecmp(__s1,"lea"), iVar3 == 0)) {
      if (!bVar2) goto LAB_001494b0;
      uVar5 = dfg_reg_from_operand(__dest);
      if (-1 < (int)uVar5) {
        if (__dest == (byte *)0x0) {
          *param_2 = 1 << (ulong)(uVar5 & 0x1f);
          uVar5 = dfg_reg_from_operand(pbVar13);
          if (-1 < (int)uVar5) {
            *param_3 = *param_3 | 1 << (ulong)(uVar5 & 0x1f);
          }
          goto LAB_001494b0;
        }
        goto LAB_00149530;
      }
LAB_0014972c:
      uVar5 = dfg_reg_from_operand(pbVar13);
      if (-1 < (int)uVar5) {
LAB_00149464:
        *param_3 = 1 << (ulong)(uVar5 & 0x1f);
      }
      if (__dest == (byte *)0x0) goto LAB_001494b0;
      goto LAB_00149478;
    }
    iVar3 = strcasecmp(__s1,"add");
    if (((((iVar3 == 0) || (iVar3 = strcasecmp(__s1,"sub"), iVar3 == 0)) ||
         (iVar3 = strcasecmp(__s1,"and"), iVar3 == 0)) ||
        ((((iVar3 = strcasecmp(__s1,"or"), iVar3 == 0 ||
           (iVar3 = strcasecmp(__s1,"shl"), iVar3 == 0)) ||
          ((iVar3 = strcasecmp(__s1,"shr"), iVar3 == 0 ||
           ((iVar3 = strcasecmp(__s1,"sar"), iVar3 == 0 ||
            (iVar3 = strcasecmp(__s1,"imul"), iVar3 == 0)))))) ||
         (iVar3 = strcasecmp(__s1,"adc"), iVar3 == 0)))) ||
       (iVar3 = strcasecmp(__s1,"sbb"), iVar3 == 0)) {
      if (bVar2) {
        uVar6 = dfg_reg_from_operand(__dest);
        uVar5 = 0;
        uVar4 = dfg_reg_from_operand(pbVar13);
        if ((-1 < (int)uVar6) &&
           ((__dest == (byte *)0x0 ||
            (pcVar10 = strchr((char *)__dest,0x5b), pcVar10 == (char *)0x0)))) {
          uVar5 = 1 << (ulong)(uVar6 & 0x1f);
          *param_2 = uVar5;
          uVar5 = uVar5 | *param_3;
          *param_3 = uVar5;
        }
        if (-1 < (int)uVar4) {
          *param_3 = 1 << (ulong)(uVar4 & 0x1f) | uVar5;
        }
      }
      goto LAB_001494b0;
    }
    iVar3 = strcasecmp(__s1,"xor");
    if (iVar3 == 0) {
      if (!bVar2) goto LAB_001494b0;
      uVar5 = dfg_reg_from_operand(__dest);
      uVar6 = dfg_reg_from_operand(pbVar13);
      if (-1 < (int)uVar5) {
        if (__dest == (byte *)0x0) {
          *param_2 = 1 << (ulong)(uVar5 & 0x1f);
          if (-1 < (int)uVar6) {
LAB_001497e0:
            if (uVar5 == uVar6) goto LAB_00149804;
            if (__dest != (byte *)0x0) goto LAB_00149660;
          }
        }
        else {
          pcVar10 = strchr((char *)__dest,0x5b);
          if (pcVar10 != (char *)0x0) {
            if ((int)uVar6 < 0) goto LAB_001494b0;
            if (uVar5 != uVar6) goto LAB_00149660;
LAB_00149804:
            *param_3 = 0;
            goto LAB_001494b0;
          }
          *param_2 = 1 << (ulong)(uVar5 & 0x1f);
          if (-1 < (int)uVar6) goto LAB_001497e0;
LAB_00149660:
          pcVar10 = strchr((char *)__dest,0x5b);
          if (pcVar10 != (char *)0x0) goto LAB_00149670;
        }
        *param_3 = *param_3 | 1 << (ulong)(uVar5 & 0x1f);
      }
LAB_00149670:
      if (-1 < (int)uVar6) {
        *param_3 = *param_3 | 1 << (ulong)(uVar6 & 0x1f);
      }
      goto LAB_001494b0;
    }
    iVar3 = strcasecmp(__s1,"cmp");
    if ((iVar3 != 0) && (iVar3 = strcasecmp(__s1,"test"), iVar3 != 0)) {
      iVar3 = strcasecmp(__s1,"neg");
      if ((iVar3 == 0) ||
         (((iVar3 = strcasecmp(__s1,"not"), iVar3 == 0 ||
           (iVar3 = strcasecmp(__s1,"inc"), iVar3 == 0)) ||
          (iVar3 = strcasecmp(__s1,"dec"), iVar3 == 0)))) {
        strncpy(acStack_d8,pcVar10,0x7f);
        local_59 = 0;
        dfg_trim_part_0();
        uVar5 = dfg_reg_from_operand();
        if (-1 < (int)uVar5) {
          uVar5 = 1 << (ulong)(uVar5 & 0x1f);
          *param_2 = *param_2 | uVar5;
          *param_3 = *param_3 | uVar5;
        }
        goto LAB_001494b0;
      }
      iVar3 = strcasecmp(__s1,"push");
      if (iVar3 == 0) {
        strncpy(acStack_d8,pcVar10,0x7f);
        local_59 = 0;
        dfg_trim_part_0();
        uVar6 = dfg_reg_from_operand();
        *param_2 = *param_2 | 0x10;
        uVar5 = *param_3 | 0x10;
        if (-1 < (int)uVar6) {
          *param_3 = uVar5 | 1 << (ulong)(uVar6 & 0x1f);
          goto LAB_001494b0;
        }
      }
      else {
        iVar3 = strcasecmp(__s1,"pop");
        if (iVar3 == 0) {
          strncpy(acStack_d8,pcVar10,0x7f);
          local_59 = 0;
          dfg_trim_part_0();
          uVar6 = dfg_reg_from_operand();
          *param_3 = *param_3 | 0x10;
          uVar5 = *param_2 | 0x10;
          if (-1 < (int)uVar6) {
            uVar5 = uVar5 | 1 << (ulong)(uVar6 & 0x1f);
          }
          *param_2 = uVar5;
          goto LAB_001494b0;
        }
        iVar3 = strcasecmp(__s1,"ret");
        if (((iVar3 != 0) && (iVar3 = strcasecmp(__s1,"retq"), iVar3 != 0)) &&
           (iVar3 = strcasecmp(__s1,"retn"), iVar3 != 0)) goto LAB_001494b0;
        uVar5 = 1;
      }
      *param_3 = uVar5;
      goto LAB_001494b0;
    }
    if (!bVar2) goto LAB_001494b0;
    uVar6 = dfg_reg_from_operand(__dest);
    uVar5 = dfg_reg_from_operand(pbVar13);
    if (-1 < (int)uVar6) {
      *param_3 = 1 << (ulong)(uVar6 & 0x1f);
    }
  }
  else {
    *pcVar7 = '\0';
    ppuVar8 = __ctype_b_loc();
    puVar12 = *ppuVar8;
    uVar1 = puVar12[local_158];
    while ((uVar1 >> 0xd & 1) != 0) {
      __dest = __dest + 1;
      uVar1 = puVar12[*__dest];
    }
    sVar9 = strlen((char *)__dest);
    pbVar13 = __dest + sVar9;
    if (__dest < pbVar13) {
      do {
        if ((puVar12[pbVar13[-1]] >> 0xd & 1) == 0) break;
        pbVar13 = pbVar13 + -1;
      } while (__dest != pbVar13);
    }
    *pbVar13 = 0;
    pbVar13 = (byte *)(pcVar7 + 1);
    uVar1 = puVar12[(byte)pcVar7[1]];
    while ((uVar1 >> 0xd & 1) != 0) {
      pbVar13 = pbVar13 + 1;
      uVar1 = puVar12[*pbVar13];
    }
    sVar9 = strlen((char *)pbVar13);
    pbVar11 = pbVar13 + sVar9;
    if (pbVar13 < pbVar11) {
      do {
        if ((puVar12[pbVar11[-1]] >> 0xd & 1) == 0) break;
        pbVar11 = pbVar11 + -1;
      } while (pbVar11 != pbVar13);
    }
    *pbVar11 = 0;
    iVar3 = strcasecmp(__s1,"mov");
    if (iVar3 != 0) {
      bVar2 = true;
      iVar3 = strcasecmp(__s1,"movsx");
      if (iVar3 != 0) goto LAB_0014925c;
      uVar5 = dfg_reg_from_operand(__dest);
      if (-1 < (int)uVar5) goto LAB_00149530;
      goto LAB_0014972c;
    }
    uVar5 = dfg_reg_from_operand(__dest);
    if ((int)uVar5 < 0) {
      uVar5 = dfg_reg_from_operand(pbVar13);
      if (-1 < (int)uVar5) goto LAB_00149464;
    }
    else {
LAB_00149530:
      pcVar10 = strchr((char *)__dest,0x5b);
      if (pcVar10 == (char *)0x0) {
        *param_2 = 1 << (ulong)(uVar5 & 0x1f);
        uVar5 = dfg_reg_from_operand(pbVar13);
        if (-1 < (int)uVar5) {
          *param_3 = *param_3 | 1 << (ulong)(uVar5 & 0x1f);
        }
      }
      else {
        uVar5 = dfg_reg_from_operand(pbVar13);
        if (-1 < (int)uVar5) {
          *param_3 = 1 << (ulong)(uVar5 & 0x1f);
        }
      }
    }
LAB_00149478:
    pcVar10 = strchr((char *)__dest,0x5b);
    if (pcVar10 == (char *)0x0) goto LAB_001494b0;
    uVar5 = dfg_reg_from_operand(__dest);
  }
  if (-1 < (int)uVar5) {
    *param_3 = *param_3 | 1 << (ulong)(uVar5 & 0x1f);
  }
LAB_001494b0:
  if (local_58 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                   local_58 - *(long *)PTR___stack_chk_guard_005ffe88);
}

