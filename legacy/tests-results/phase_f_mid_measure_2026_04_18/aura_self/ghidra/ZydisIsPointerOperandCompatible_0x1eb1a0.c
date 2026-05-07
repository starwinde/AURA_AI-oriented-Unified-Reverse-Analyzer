
bool ZydisIsPointerOperandCompatible(long *param_1,long param_2)

{
  byte bVar1;
  byte bVar2;
  
  if ((char)param_1[5] != '\0') {
                    /* WARNING: Subroutine does not return */
    __assert_fail("match->eosz == 0",
                  "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x8bb,
                  "ZydisIsPointerOperandCompatible");
  }
  if (*(int *)*param_1 != 0) {
    if ((*(int *)(*param_1 + 0x18) != 0) && (*(int *)(*param_1 + 0x18) != 3)) {
                    /* WARNING: Subroutine does not return */
      __assert_fail("(match->request->branch_type == ZYDIS_BRANCH_TYPE_NONE) || (match->request->branch_type == ZYDIS_BRANCH_TYPE_FAR)"
                    ,"/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x8bd,
                    "ZydisIsPointerOperandCompatible");
    }
    bVar1 = ZydisGetUnsignedImmSize(*(undefined4 *)(param_2 + 0x34));
    if (*(int *)(*param_1 + 0x1c) == 0) {
      bVar2 = ZydisGetMachineModeWidth(*(undefined4 *)*param_1);
    }
    else {
      bVar2 = (byte)(4 << (ulong)(*(uint *)(*param_1 + 0x1c) & 0x1f));
    }
    if (bVar1 <= bVar2) {
      *(byte *)((long)param_1 + 0x2a) = bVar2;
      *(undefined1 *)(param_1 + 5) = *(undefined1 *)((long)param_1 + 0x2a);
      *(undefined1 *)((long)param_1 + 0x2b) = 0x10;
    }
    return bVar1 <= bVar2;
  }
                    /* WARNING: Subroutine does not return */
  __assert_fail("match->request->machine_mode != ZYDIS_MACHINE_MODE_LONG_64",
                "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x8bc,
                "ZydisIsPointerOperandCompatible");
}

