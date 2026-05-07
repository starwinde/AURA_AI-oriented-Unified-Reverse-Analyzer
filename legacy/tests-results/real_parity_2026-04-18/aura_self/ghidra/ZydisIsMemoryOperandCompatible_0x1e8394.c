
undefined8 ZydisIsMemoryOperandCompatible(undefined8 *param_1,long param_2,byte *param_3)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  undefined1 uVar4;
  char cVar5;
  char cVar6;
  char cVar7;
  byte bVar8;
  byte bVar9;
  int iVar10;
  int iVar11;
  ulong uVar12;
  long lVar13;
  byte local_4c;
  byte local_4a;
  byte local_49;
  byte local_47;
  int local_3c;
  
  bVar8 = *param_3 & 0x3f;
  if (bVar8 != 0x21) {
    if (0x21 < bVar8) {
LAB_001e902c:
                    /* WARNING: Subroutine does not return */
      __assert_fail("0","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x8aa,
                    "ZydisIsMemoryOperandCompatible");
    }
    if (bVar8 == 0x20) {
      if (((*(int *)(param_2 + 0x10) != 0) || (*(int *)(param_2 + 0x14) != 0)) ||
         (*(char *)(param_2 + 0x18) != '\0')) {
        return 0;
      }
      bVar8 = ZydisGetSignedImmSize(*(undefined8 *)(param_2 + 0x20));
      bVar9 = ZydisGetMaxAddressSize(*param_1);
      if (bVar9 < bVar8) {
        return 0;
      }
      lVar13 = ZydisGetOperandSizes(param_3);
      if (*(char *)(param_1 + 5) == '\0') {
        uVar4 = ZydisGetOperandSizeFromElementSize(param_1,lVar13,*(undefined2 *)(param_2 + 0x28),1)
        ;
        *(undefined1 *)(param_1 + 5) = uVar4;
        if (*(char *)(param_1 + 5) == '\0') {
          return 0;
        }
      }
      else if (*(short *)(lVar13 + (ulong)(*(byte *)(param_1 + 5) >> 5) * 2) !=
               *(short *)(param_2 + 0x28)) {
        return 0;
      }
      uVar4 = ZydisGetEffectiveImmSize(param_1,*(undefined8 *)(param_2 + 0x20),param_3);
      *(undefined1 *)((long)param_1 + 0x2a) = uVar4;
      if (*(char *)((long)param_1 + 0x2a) != '\0') {
        if (*(char *)((long)param_1 + 0x2a) != '@') {
          return 1;
        }
        if (*(byte *)((long)param_1 + 0x2a) <= bVar8) {
          return 1;
        }
        return 0;
      }
      return 0;
    }
    if (0x20 < bVar8) goto LAB_001e902c;
    if (bVar8 < 0x1b) {
      if (bVar8 < 0x17) goto LAB_001e902c;
    }
    else if (bVar8 != 0x1f) goto LAB_001e902c;
  }
  if (((*param_3 & 0x3f) == 0x21) && (*(char *)(param_2 + 0x18) != '\0')) {
    return 0;
  }
  uVar12 = *(ulong *)(param_2 + 0x20);
  local_4c = 0;
  if (uVar12 != 0) {
    local_4c = ZydisGetSignedImmSize(uVar12);
    if (0x20 < local_4c) {
      return 0;
    }
    uVar4 = ZydisGetCompDispScale(param_1);
    *(undefined1 *)((long)param_1 + 0x2c) = uVar4;
    if (*(char *)((long)param_1 + 0x2c) != '\0') {
      if ((uVar12 & (long)((1 << (ulong)(*(byte *)((long)param_1 + 0x2c) & 0x1f)) + -1)) == 0) {
        cVar5 = ZydisGetSignedImmSize
                          ((long)uVar12 >> ((ulong)*(byte *)((long)param_1 + 0x2c) & 0x3f));
        if (cVar5 == '\b') {
          local_4c = 8;
        }
      }
      else if (local_4c == 8) {
        local_4c = 0x10;
      }
    }
  }
  if ((*param_3 & 0x3f) == 0x1f) {
    if (*(char *)((long)param_1 + 0x29) == '\0') {
      if ((8 < *(ushort *)(param_2 + 0x28)) ||
         ((0x114UL >> ((ulong)*(ushort *)(param_2 + 0x28) & 0x3f) & 1) == 0)) {
        return 0;
      }
      *(char *)((long)param_1 + 0x29) = (char)((*(ushort *)(param_2 + 0x28) & 0x1f) << 3);
    }
    else if ((ushort)*(byte *)((long)param_1 + 0x29) != *(ushort *)(param_2 + 0x28)) {
      return 0;
    }
  }
  else {
    lVar13 = ZydisGetOperandSizes(param_3);
    if (*(char *)(param_1 + 5) == '\0') {
      if (((*(byte *)(param_1[1] + 8) & 0x80) == 0) &&
         (((*(byte *)(param_1[1] + 9) & 3) != 0 || ((*(byte *)(param_1[1] + 6) & 7) == 5)))) {
        cVar5 = ZydisCheckVectorMemorySize(param_1,param_2,lVar13);
        if (cVar5 == '\0') {
          return 0;
        }
      }
      else if ((*(byte *)(param_1[1] + 8) & 4) == 0) {
        if (((*(byte *)(param_1[1] + 8) & 0x80) == 0) && ((*(byte *)(param_1[1] + 9) & 3) != 0)) {
                    /* WARNING: Subroutine does not return */
          __assert_fail("0","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x782
                        ,"ZydisIsMemoryOperandCompatible");
        }
        uVar4 = ZydisGetOperandSizeFromElementSize(param_1,lVar13,*(undefined2 *)(param_2 + 0x28),1)
        ;
        *(undefined1 *)(param_1 + 5) = uVar4;
        if (*(char *)(param_1 + 5) == '\0') {
          return 0;
        }
      }
      else {
        *(undefined1 *)(param_1 + 5) = 0x40;
      }
    }
    else if (*(short *)(lVar13 + (ulong)(*(byte *)(param_1 + 5) >> 5) * 2) !=
             *(short *)(param_2 + 0x28)) {
      return 0;
    }
  }
  local_3c = 0;
  bVar2 = true;
  bVar8 = *param_3 & 0x3f;
  if (bVar8 == 0x1a) {
    local_3c = 9;
    goto LAB_001e87b8;
  }
  if (bVar8 < 0x1b) {
    if (bVar8 == 0x18) {
      local_3c = 7;
      goto LAB_001e87b8;
    }
    if (bVar8 == 0x19) {
      local_3c = 8;
      goto LAB_001e87b8;
    }
  }
  bVar2 = false;
LAB_001e87b8:
  if ((*(int *)(param_2 + 0x10) == 0x105) || (*(int *)(param_2 + 0x10) == 0x104)) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) &&
     (((((ulong)(*(uint *)(param_1[2] + 8) >> 0x14) & 0x1f) >> 3 & 1) != 0 ||
      ((*(byte *)(param_1[1] + 5) & 7) == 4)))) {
    return 0;
  }
  iVar10 = ZydisRegisterGetClass(*(undefined4 *)(param_2 + 0x10));
  if ((iVar10 == 0) && (*(int *)(param_2 + 0x10) != 0)) {
    return 0;
  }
  iVar11 = ZydisRegisterGetClass(*(undefined4 *)(param_2 + 0x14));
  if ((iVar11 == 0) && (*(int *)(param_2 + 0x14) != 0)) {
    return 0;
  }
  if (bVar2) {
    cVar5 = ZydisGetMachineModeWidth(*(undefined4 *)*param_1);
    cVar6 = ZydisRegisterGetId(*(undefined4 *)(param_2 + 0x14));
    if (((*(int *)*param_1 != 0) || (iVar10 != 4)) && ((iVar10 != 3 && (iVar10 != 0)))) {
      return 0;
    }
    if (((iVar10 == 3) && (cVar5 != '@')) &&
       (cVar7 = ZydisRegisterGetId(*(undefined4 *)(param_2 + 0x10)), '\a' < cVar7)) {
      return 0;
    }
    if (((*(byte *)(param_1[1] + 6) & 7) != 4) &&
       (cVar7 = ZydisRegisterGetId(*(undefined4 *)(param_2 + 0x10)), '\x0f' < cVar7)) {
      return 0;
    }
    local_4a = 7;
    if (cVar5 == '@') {
      if ((*(byte *)(param_1[1] + 6) & 7) == 3) {
        local_4a = 0xf;
      }
      else {
        local_4a = 0x1f;
      }
    }
    if ((iVar11 != local_3c) || ((int)(uint)local_4a < (int)cVar6)) {
      return 0;
    }
  }
  else {
    cVar5 = ZydisIsValidAddressingClass(param_1,iVar10,*(undefined4 *)(param_2 + 0x10));
    if ((cVar5 == '\0') && ((!bVar1 || (*(int *)*param_1 != 0)))) {
      return 0;
    }
    cVar5 = ZydisIsValidAddressingClass(param_1,iVar11,*(undefined4 *)(param_2 + 0x14));
    if (cVar5 == '\0') {
      return 0;
    }
    if (((iVar10 != 0) && (iVar11 != 0)) && (iVar10 != iVar11)) {
      return 0;
    }
    if ((*(int *)(param_2 + 0x14) == 0x49) || (*(int *)(param_2 + 0x14) == 0x69)) {
      return 0;
    }
  }
  if (((iVar11 != 0) && (*(char *)(param_2 + 0x18) == '\0')) && ((*param_3 & 0x3f) != 0x21)) {
    return 0;
  }
  if ((iVar11 == 0) && (*(char *)(param_2 + 0x18) != '\0')) {
    return 0;
  }
  bVar3 = false;
  if (iVar10 == 0) {
    if (iVar11 == 0) {
      local_49 = ZydisGetMaxAddressSize(*param_1);
      if (local_49 < local_4c) {
        return 0;
      }
      if (*(char *)((long)param_1 + 0x29) == '\0') {
        local_47 = 0x10;
      }
      else {
        local_47 = *(byte *)((long)param_1 + 0x29);
      }
      if (((local_47 == 0x10) && (((uint)((ulong)*(undefined8 *)param_1[1] >> 0x3a) & 1) == 0)) ||
         ((local_47 == 0x40 || (*(int *)*param_1 == 0)))) {
        local_47 = 0x20;
      }
      if (local_4c < local_47) {
        local_4c = local_47;
      }
      if (*(int *)*param_1 == 0) {
        if (((local_49 == 0x20) && (-1 < (long)*(ulong *)(param_2 + 0x20))) &&
           (*(char *)((long)param_1 + 0x29) != ' ')) {
          local_49 = 0x40;
        }
      }
      else {
        if ((local_4c < local_49) &&
           (bVar8 = ZydisGetUnsignedImmSize
                              (~((-1L << ((ulong)(local_49 - 1) & 0x3f)) << 1) &
                               *(ulong *)(param_2 + 0x20)), local_4c < bVar8)) {
          local_4c = local_49;
        }
        local_49 = local_4c;
      }
      bVar3 = true;
    }
    else if (bVar2) {
      local_49 = ZydisGetMachineModeWidth(*(undefined4 *)*param_1);
    }
    else {
      local_49 = ZydisRegisterClassGetWidth(*(undefined4 *)*param_1,iVar11);
    }
  }
  else if (bVar1) {
    if (*(int *)(param_2 + 0x10) == 0x105) {
      local_49 = 0x40;
    }
    else {
      local_49 = 0x20;
    }
  }
  else {
    local_49 = ZydisRegisterClassGetWidth(*(undefined4 *)*param_1,iVar10);
  }
  if (*(int *)*param_1 == 0) {
    if ((bVar1) && (iVar11 != 0)) {
      return 0;
    }
  }
  else if (local_49 == 0x10) {
    if (bVar2) {
      local_49 = 0x20;
    }
    else if (!bVar3) {
      if (0x10 < local_4c) {
        return 0;
      }
      cVar5 = ZydisGetRm16(*(undefined4 *)(param_2 + 0x10),*(undefined4 *)(param_2 + 0x14));
      if (cVar5 == -1) {
        return 0;
      }
      if (cVar5 < '\x04' != (bool)*(char *)(param_2 + 0x18)) {
        return 0;
      }
    }
  }
  if (*(char *)((long)param_1 + 0x29) == '\0') {
    *(byte *)((long)param_1 + 0x29) = local_49;
  }
  else if (local_49 != *(byte *)((long)param_1 + 0x29)) {
    return 0;
  }
  if (((*(byte *)(param_1[2] + 4) & 0x30) == 0x10) &&
     (cVar5 = *(char *)((long)param_1 + 0x29),
     cVar6 = ZydisGetMachineModeWidth(*(undefined4 *)*param_1), cVar5 != cVar6)) {
    return 0;
  }
  *(byte *)((long)param_1 + 0x2a) = local_4c;
  return 1;
}

