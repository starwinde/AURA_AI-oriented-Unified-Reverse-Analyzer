
bool ZydisHandleSwappableDefinition(long *param_1)

{
  uint uVar1;
  byte bVar2;
  char cVar3;
  char cVar4;
  long lVar5;
  
  if ((*(byte *)(param_1[1] + 9) & 0x10) == 0) {
    return false;
  }
  if (*(int *)(*param_1 + 8) == 0x1f9) {
    bVar2 = ZydisGetSignedImmSize(*(undefined8 *)(*param_1 + 0xa8));
    if (((*(int *)*param_1 == 0) && ((char)param_1[5] == '@')) && (bVar2 < 0x40)) {
      return true;
    }
    return false;
  }
  if (*(int *)(*param_1 + 8) == 0x73f) {
    if ((*(char *)(*param_1 + 0x28) != '\x02') || (*(int *)(*param_1 + 0x30) != 1)) {
                    /* WARNING: Subroutine does not return */
      __assert_fail("(match->request->operand_count == 2) && (match->request->operands[0].type == ZYDIS_OPERAND_TYPE_REGISTER)"
                    ,"/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0xbf3,
                    "ZydisHandleSwappableDefinition");
    }
    uVar1 = *(uint *)(*param_1 + 0x34);
    if (uVar1 != 0x65) {
      if (0x65 < uVar1) {
        return false;
      }
      if (uVar1 != 0x25) {
        if (uVar1 != 0x45) {
          return false;
        }
        *(undefined1 *)(param_1 + 5) = 0;
        cVar3 = ZydisGetMachineModeWidth(*(undefined4 *)*param_1);
        return cVar3 == '@';
      }
    }
    *(undefined1 *)(param_1 + 5) = 0;
    return false;
  }
  if ((*(char *)(*param_1 + 0x28) != '\x02') && (*(char *)(*param_1 + 0x28) != '\x03')) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("(match->request->operand_count == 2) || (match->request->operand_count == 3)",
                  "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0xc04,
                  "ZydisHandleSwappableDefinition");
  }
  if (*(char *)(*param_1 + 0x28) == '\x03') {
    bVar2 = 2;
  }
  else {
    bVar2 = 1;
  }
  cVar3 = ZydisRegisterGetId(*(undefined4 *)(*param_1 + 0x34));
  cVar4 = ZydisRegisterGetId(*(undefined4 *)(*param_1 + (long)(int)(uint)bVar2 * 0x40 + 0x34));
  if ((cVar3 < '\b') && ('\a' < cVar4)) {
    param_1[1] = param_1[1] + 10;
    ZydisGetInstructionDefinition
              (*(byte *)(param_1[1] + 6) & 7,*(undefined2 *)param_1[1],param_1 + 2);
    lVar5 = ZydisGetOperandDefinitions(param_1[2]);
    param_1[3] = lVar5;
    return true;
  }
  return false;
}

