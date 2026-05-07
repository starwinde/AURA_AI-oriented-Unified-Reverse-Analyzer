
byte FUN_001ee5e8(ulong *param_1)

{
  byte local_1;
  
  if ((*param_1 & 2) == 0) {
    local_1 = (byte)((int)(uint)*(byte *)((long)param_1 + 0x17) >> 3) & 1 |
              *(byte *)((long)param_1 + 0x17) & 0x10;
    if ((*param_1 & 1) != 0) {
      local_1 = (byte)((int)(uint)*(byte *)((long)param_1 + 0x16) >> 1) & 4 |
                (*(byte *)((long)param_1 + 0x16) & 0x10) << 2 | local_1;
    }
  }
  else {
    if ((*param_1 & 1) == 0) {
                    /* WARNING: Subroutine does not return */
      __assert_fail("instruction->attributes & (1ULL << 0)",
                    "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0xddc,
                    "ZydisEncodeRex2");
    }
    local_1 = (byte)((int)(uint)*(byte *)((long)param_1 + 0x1a) >> 3) & 1 |
              *(byte *)((long)param_1 + 0x1a) & 0x10 |
              (byte)((int)(uint)*(byte *)((long)param_1 + 0x19) >> 2) & 2 |
              (*(byte *)((long)param_1 + 0x19) & 0x10) << 1 |
              (byte)((int)(uint)*(byte *)((long)param_1 + 0x16) >> 1) & 4 |
              (*(byte *)((long)param_1 + 0x16) & 0x10) << 2;
  }
  if (*(int *)((long)param_1 + 0xc) == 1) {
    local_1 = local_1 | 0x80;
  }
  if (*(char *)((long)param_1 + 0x1d) != '\0') {
    local_1 = local_1 | 8;
  }
  return local_1;
}

