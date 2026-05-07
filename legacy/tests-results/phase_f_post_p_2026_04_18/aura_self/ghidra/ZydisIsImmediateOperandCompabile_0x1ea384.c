
undefined8 ZydisIsImmediateOperandCompabile(long param_1,long param_2,byte *param_3)

{
  uint uVar1;
  char cVar2;
  byte *pbVar3;
  
  uVar1 = *param_3 & 0x3f;
  if (uVar1 == 0x1d) {
    *(undefined1 *)(param_1 + 0x2b) = 0x40;
  }
  else {
    if (0x1d < uVar1) {
LAB_001ea524:
                    /* WARNING: Subroutine does not return */
      __assert_fail("0","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x901,
                    "ZydisIsImmediateOperandCompabile");
    }
    if (uVar1 == 3) {
      if (*(long *)(param_2 + 0x38) != 1) {
        return 0;
      }
    }
    else {
      if ((uVar1 < 3) || (1 < uVar1 - 0x1b)) goto LAB_001ea524;
      cVar2 = ZydisGetEffectiveImmSize(param_1,*(undefined8 *)(param_2 + 0x38),param_3);
      pbVar3 = (byte *)ZydisGetOperandDetails(param_3);
      if ((*pbVar3 & 0x3f) == 5) {
        if (*(char *)(param_1 + 0x2b) != '\0') {
                    /* WARNING: Subroutine does not return */
          __assert_fail("match->imm_size == 0",
                        "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x8f3,
                        "ZydisIsImmediateOperandCompabile");
        }
        if (cVar2 != '\b') {
          return 0;
        }
      }
      else {
        if (cVar2 == '\0') {
          return 0;
        }
        if (*(char *)(param_1 + 0x2b) != '\0') {
          if (*(char *)(param_1 + 0x2a) != '\0') {
                    /* WARNING: Subroutine does not return */
            __assert_fail("match->disp_size == 0",
                          "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x8ed,
                          "ZydisIsImmediateOperandCompabile");
          }
          *(undefined1 *)(param_1 + 0x2a) = *(undefined1 *)(param_1 + 0x2b);
        }
      }
      *(char *)(param_1 + 0x2b) = cVar2;
      *(bool *)(param_1 + 0x35) = (*param_3 & 0x3f) == 0x1c;
    }
  }
  return 1;
}

