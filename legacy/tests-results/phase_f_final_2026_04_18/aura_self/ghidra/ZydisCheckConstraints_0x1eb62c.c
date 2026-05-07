
undefined8 ZydisCheckConstraints(long *param_1)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  char cVar4;
  char cVar5;
  int iVar6;
  long lVar7;
  long lVar8;
  byte local_3e;
  
  lVar7 = *param_1;
  piVar1 = (int *)(lVar7 + 0x30);
  bVar2 = *(byte *)(param_1[1] + 6) & 7;
  if (bVar2 == 5) {
    local_3e = *(byte *)(param_1[2] + 0xc) >> 5 & 1;
  }
  else {
    if (5 < bVar2) {
      return 1;
    }
    if (bVar2 == 3) {
      lVar8 = param_1[2];
      if ((*(byte *)(lVar8 + 0xc) & 0x20) != 0) {
        if (*(char *)(*param_1 + 0x28) != '\x03') {
                    /* WARNING: Subroutine does not return */
          __assert_fail("match->request->operand_count == 3",
                        "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0xaa1,
                        "ZydisCheckConstraints");
        }
        if (*piVar1 != 1) {
                    /* WARNING: Subroutine does not return */
          __assert_fail("operands[0].type == ZYDIS_OPERAND_TYPE_REGISTER",
                        "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0xaa2,
                        "ZydisCheckConstraints");
        }
        if (*(int *)(lVar7 + 0x70) != 2) {
                    /* WARNING: Subroutine does not return */
          __assert_fail("operands[1].type == ZYDIS_OPERAND_TYPE_MEMORY",
                        "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0xaa3,
                        "ZydisCheckConstraints");
        }
        if (*(int *)(lVar7 + 0xb0) != 1) {
                    /* WARNING: Subroutine does not return */
          __assert_fail("operands[2].type == ZYDIS_OPERAND_TYPE_REGISTER",
                        "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0xaa4,
                        "ZydisCheckConstraints");
        }
        cVar4 = ZydisRegisterGetId(*(undefined4 *)(lVar7 + 0x34));
        cVar5 = ZydisRegisterGetId(*(undefined4 *)(lVar7 + 0x84));
        cVar3 = ZydisRegisterGetId(*(undefined4 *)(lVar7 + 0xb4));
        if (((cVar4 == cVar5) || (cVar4 == cVar3)) || (cVar5 == cVar3)) {
          return 0;
        }
      }
      if ((*(byte *)(lVar8 + 0xc) & 0x80) != 0) {
        if (*(char *)(*param_1 + 0x28) != '\x03') {
                    /* WARNING: Subroutine does not return */
          __assert_fail("match->request->operand_count == 3",
                        "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0xab2,
                        "ZydisCheckConstraints");
        }
        if (*piVar1 != 1) {
                    /* WARNING: Subroutine does not return */
          __assert_fail("operands[0].type == ZYDIS_OPERAND_TYPE_REGISTER",
                        "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0xab3,
                        "ZydisCheckConstraints");
        }
        if (*(int *)(lVar7 + 0x70) != 1) {
                    /* WARNING: Subroutine does not return */
          __assert_fail("operands[1].type == ZYDIS_OPERAND_TYPE_REGISTER",
                        "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0xab4,
                        "ZydisCheckConstraints");
        }
        if (*(int *)(lVar7 + 0xb0) != 1) {
                    /* WARNING: Subroutine does not return */
          __assert_fail("operands[2].type == ZYDIS_OPERAND_TYPE_REGISTER",
                        "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0xab5,
                        "ZydisCheckConstraints");
        }
        if (((*(int *)(lVar7 + 0x34) == *(int *)(lVar7 + 0x74)) ||
            (*(int *)(lVar7 + 0x74) == *(int *)(lVar7 + 0xb4))) ||
           (*(int *)(lVar7 + 0x34) == *(int *)(lVar7 + 0xb4))) {
          return 0;
        }
      }
      return 1;
    }
    if (bVar2 != 4) {
      return 1;
    }
    local_3e = *(byte *)(param_1[2] + 0xc) >> 5 & 1;
    if ((*(byte *)(param_1[2] + 0xc) & 0x40) != 0) {
      if (*piVar1 != 1) {
                    /* WARNING: Subroutine does not return */
        __assert_fail("operands[0].type == ZYDIS_OPERAND_TYPE_REGISTER",
                      "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0xac9,
                      "ZydisCheckConstraints");
      }
      if (*(int *)(lVar7 + 0xb0) != 1) {
                    /* WARNING: Subroutine does not return */
        __assert_fail("operands[2].type == ZYDIS_OPERAND_TYPE_REGISTER",
                      "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0xaca,
                      "ZydisCheckConstraints");
      }
      if ((*(int *)(lVar7 + 0xf0) != 1) && (*(int *)(lVar7 + 0xf0) != 2)) {
                    /* WARNING: Subroutine does not return */
        __assert_fail("(operands[3].type == ZYDIS_OPERAND_TYPE_REGISTER) || (operands[3].type == ZYDIS_OPERAND_TYPE_MEMORY)"
                      ,"/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0xacb,
                      "ZydisCheckConstraints");
      }
      if (*(int *)(lVar7 + 0xf0) == 1) {
        iVar6 = *(int *)(lVar7 + 0xf4);
      }
      else {
        iVar6 = 0;
      }
      if ((*(int *)(lVar7 + 0x34) == *(int *)(lVar7 + 0xb4)) || (*(int *)(lVar7 + 0x34) == iVar6)) {
        return 0;
      }
    }
  }
  if ((local_3e != 0) && (*piVar1 == 1)) {
    if (*(char *)(*param_1 + 0x28) != '\x03') {
                    /* WARNING: Subroutine does not return */
      __assert_fail("match->request->operand_count == 3",
                    "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0xae7,
                    "ZydisCheckConstraints");
    }
    if (*piVar1 != 1) {
                    /* WARNING: Subroutine does not return */
      __assert_fail("operands[0].type == ZYDIS_OPERAND_TYPE_REGISTER",
                    "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0xae8,
                    "ZydisCheckConstraints");
    }
    if (*(int *)(lVar7 + 0xb0) != 2) {
                    /* WARNING: Subroutine does not return */
      __assert_fail("operands[2].type == ZYDIS_OPERAND_TYPE_MEMORY",
                    "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0xae9,
                    "ZydisCheckConstraints");
    }
    cVar4 = ZydisRegisterGetId(*(undefined4 *)(lVar7 + 0x34));
    cVar5 = ZydisRegisterGetId(*(undefined4 *)(lVar7 + 0xc4));
    if (cVar4 == cVar5) {
      return 0;
    }
  }
  return 1;
}

