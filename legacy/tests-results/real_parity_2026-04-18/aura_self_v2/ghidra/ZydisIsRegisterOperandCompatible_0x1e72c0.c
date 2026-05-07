
bool ZydisIsRegisterOperandCompatible(long *param_1,long param_2,ushort *param_3)

{
  ushort uVar1;
  byte bVar2;
  char cVar3;
  ushort uVar4;
  int iVar5;
  ushort *puVar6;
  long lVar7;
  bool local_18;
  
  puVar6 = (ushort *)ZydisGetOperandDetails(param_3);
  iVar5 = ZydisRegisterGetClass(*(undefined4 *)(param_2 + 4));
  uVar4 = ZydisRegisterClassGetWidth(*(undefined4 *)*param_1,iVar5);
  if (uVar4 == 0) {
    return false;
  }
  local_18 = false;
  switch((byte)*param_3 & 0x3f) {
  case 1:
    bVar2 = (byte)*puVar6 & 7;
    if (bVar2 == 2) {
      if (((iVar5 != 1) && (iVar5 != 2)) && ((iVar5 != 3 && (iVar5 != 4)))) {
        return false;
      }
      uVar1 = *puVar6;
      cVar3 = ZydisRegisterGetId(*(undefined4 *)(param_2 + 4));
      if ((uVar1 >> 8 & 0x3f) != (int)cVar3) {
        return false;
      }
      cVar3 = ZydisCheckAsz(param_1,uVar4);
      if (cVar3 == '\0') {
        return false;
      }
    }
    else {
      if (2 < bVar2) {
LAB_001e74dc:
                    /* WARNING: Subroutine does not return */
        __assert_fail("0","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x56f,
                      "ZydisIsRegisterOperandCompatible");
      }
      if (((byte)*puVar6 & 7) == 0) {
        if ((((byte)puVar6[1] & 1) << 8 | (uint)*(byte *)((long)puVar6 + 1)) !=
            *(uint *)(param_2 + 4)) {
          return false;
        }
      }
      else {
        if (bVar2 != 1) goto LAB_001e74dc;
        if (((iVar5 != 1) && (iVar5 != 2)) && ((iVar5 != 3 && (iVar5 != 4)))) {
          return false;
        }
        uVar1 = *puVar6;
        cVar3 = ZydisRegisterGetId(*(undefined4 *)(param_2 + 4));
        if ((uVar1 >> 8 & 0x3f) != (int)cVar3) {
          return false;
        }
        cVar3 = ZydisCheckOsz(param_1,uVar4);
        if (cVar3 == '\0') {
          return false;
        }
      }
    }
    break;
  default:
                    /* WARNING: Subroutine does not return */
    __assert_fail("0","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x671,
                  "ZydisIsRegisterOperandCompatible");
  case 4:
    if (iVar5 != 1) {
      return false;
    }
    cVar3 = ZydisIsRegisterAllowed(param_1,*(undefined4 *)(param_2 + 4),1);
    if (cVar3 == '\0') {
      return false;
    }
    cVar3 = ZydisValidateRexType(param_1,*(undefined4 *)(param_2 + 4),0);
    if (cVar3 == '\0') {
      return false;
    }
    break;
  case 5:
    if (iVar5 != 2) {
      return false;
    }
    cVar3 = ZydisIsRegisterAllowed(param_1,*(undefined4 *)(param_2 + 4),2);
    if (cVar3 == '\0') {
      return false;
    }
    break;
  case 6:
    if (iVar5 != 3) {
      return false;
    }
    cVar3 = ZydisIsRegisterAllowed(param_1,*(undefined4 *)(param_2 + 4),3);
    if (cVar3 == '\0') {
      return false;
    }
    break;
  case 7:
    if (iVar5 != 4) {
      return false;
    }
    cVar3 = ZydisIsRegisterAllowed(param_1,*(undefined4 *)(param_2 + 4),4);
    if (cVar3 == '\0') {
      return false;
    }
    break;
  case 8:
    if (((iVar5 != 2) && (iVar5 != 3)) && (iVar5 != 4)) {
      return false;
    }
    cVar3 = ZydisCheckOsz(param_1,uVar4);
    if (cVar3 == '\0') {
      return false;
    }
    cVar3 = ZydisIsRegisterAllowed(param_1,*(undefined4 *)(param_2 + 4),iVar5);
    if (cVar3 == '\0') {
      return false;
    }
    cVar3 = ZydisValidateRexType(param_1,*(undefined4 *)(param_2 + 4),0);
    if (cVar3 == '\0') {
      return false;
    }
    break;
  case 9:
    if ((iVar5 != 3) && (iVar5 != 4)) {
      return false;
    }
    if ((char)param_1[5] == '\0') {
      if (iVar5 == 4) {
        *(undefined1 *)(param_1 + 5) = 0x40;
      }
      else {
        *(undefined1 *)((long)param_1 + 0x34) = 1;
      }
    }
    else if ((ushort)*(byte *)(param_1 + 5) != (uVar4 & 0xff)) {
      return false;
    }
    cVar3 = ZydisIsRegisterAllowed(param_1,*(undefined4 *)(param_2 + 4),iVar5);
    if (cVar3 == '\0') {
      return false;
    }
    cVar3 = ZydisValidateRexType(param_1,*(undefined4 *)(param_2 + 4),0);
    if (cVar3 == '\0') {
      return false;
    }
    break;
  case 10:
    if ((iVar5 != 2) && (iVar5 != 3)) {
      return false;
    }
    cVar3 = ZydisCheckOsz(param_1,uVar4);
    if ((cVar3 == '\0') && (((char)param_1[5] != '@' || (iVar5 != 3)))) {
      return false;
    }
    cVar3 = ZydisIsRegisterAllowed(param_1,*(undefined4 *)(param_2 + 4),iVar5);
    if (cVar3 == '\0') {
      return false;
    }
    break;
  case 0xb:
    if (((iVar5 != 2) && (iVar5 != 3)) && (iVar5 != 4)) {
      return false;
    }
    cVar3 = ZydisCheckAsz(param_1,uVar4);
    if (cVar3 == '\0') {
      return false;
    }
    cVar3 = ZydisIsRegisterAllowed(param_1,*(undefined4 *)(param_2 + 4),iVar5);
    if (cVar3 == '\0') {
      return false;
    }
    break;
  case 0xc:
    if (iVar5 != 5) {
      return false;
    }
    break;
  case 0xd:
    if (iVar5 != 6) {
      return false;
    }
    break;
  case 0xe:
    if (iVar5 != 7) {
      return false;
    }
    cVar3 = ZydisIsRegisterAllowed(param_1,*(undefined4 *)(param_2 + 4),7);
    if (cVar3 == '\0') {
      return false;
    }
    local_18 = (*puVar6 & 0x3f) == 5;
    break;
  case 0xf:
    if (iVar5 != 8) {
      return false;
    }
    cVar3 = ZydisIsRegisterAllowed(param_1,*(undefined4 *)(param_2 + 4),8);
    if (cVar3 == '\0') {
      return false;
    }
    local_18 = (*puVar6 & 0x3f) == 5;
    break;
  case 0x10:
    if (iVar5 != 9) {
      return false;
    }
    cVar3 = ZydisIsRegisterAllowed(param_1,*(undefined4 *)(param_2 + 4),9);
    if (cVar3 == '\0') {
      return false;
    }
    break;
  case 0x11:
    if (iVar5 != 10) {
      return false;
    }
    break;
  case 0x12:
    if (iVar5 != 0x13) {
      return false;
    }
    break;
  case 0x13:
    if (iVar5 != 0xd) {
      return false;
    }
    if (((*param_3 >> 8 & 10) != 0) && (*(int *)(param_2 + 4) == 0x107)) {
      return false;
    }
    break;
  case 0x14:
    if (iVar5 != 0x10) {
      return false;
    }
    cVar3 = ZydisRegisterGetId(*(undefined4 *)(param_2 + 4));
    if ((*(int *)*param_1 != 0) && (cVar3 == '\b')) {
      return false;
    }
    if (cr_lookup_30[(int)cVar3] == '\0') {
      return false;
    }
    break;
  case 0x15:
    if (iVar5 != 0x11) {
      return false;
    }
    if (0x12f < *(uint *)(param_2 + 4)) {
      return false;
    }
    break;
  case 0x16:
    if (iVar5 != 0x12) {
      return false;
    }
    if (((*(byte *)(param_1[1] + 6) & 7) == 4) && ((*puVar6 & 0x3f) == 6)) {
      lVar7 = param_1[2];
      if (((*(byte *)(lVar7 + 0xe) & 0x30) == 0) || ((*(byte *)(lVar7 + 0xe) & 0x30) == 0x30)) {
                    /* WARNING: Subroutine does not return */
        __assert_fail("(evex_def->mask_policy != ZYDIS_MASK_POLICY_INVALID) && (evex_def->mask_policy != ZYDIS_MASK_POLICY_FORBIDDEN)"
                      ,"/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x661,
                      "ZydisIsRegisterOperandCompatible");
      }
      if (((*(byte *)(lVar7 + 0xe) & 0x30) == 0x20) && (*(int *)(param_2 + 4) == 0x138)) {
        return false;
      }
      if ((((*(byte *)(lVar7 + 0xe) & 0x30) == 0x10) && (*(char *)(*param_1 + 0x179) != '\0')) &&
         (*(int *)(param_2 + 4) == 0x138)) {
        return false;
      }
    }
  }
  return local_18 == (bool)*(char *)(param_2 + 8);
}

