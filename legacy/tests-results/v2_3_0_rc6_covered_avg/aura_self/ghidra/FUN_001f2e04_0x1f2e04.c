
undefined * FUN_001f2e04(long param_1)

{
  undefined *puVar1;
  
  if ((*(byte *)(param_1 + 1) & 0x78) == 0) {
    puVar1 = (undefined *)0x0;
  }
  else {
    if (((*(byte *)(param_1 + 4) & 1) << 0xe |
        (uint)*(byte *)(param_1 + 3) << 6 | (uint)(*(byte *)(param_1 + 2) >> 2)) == 0x7fff) {
                    /* WARNING: Subroutine does not return */
      __assert_fail("definition->operand_reference != 0x7FFF",
                    "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/SharedData.c",0x77,
                    "ZydisGetOperandDefinitions");
    }
    puVar1 = &UNK_005b06a8 +
             (long)(int)((*(byte *)(param_1 + 4) & 1) << 0xe |
                        (uint)*(byte *)(param_1 + 3) << 6 | (uint)(*(byte *)(param_1 + 2) >> 2)) * 5
    ;
  }
  return puVar1;
}

