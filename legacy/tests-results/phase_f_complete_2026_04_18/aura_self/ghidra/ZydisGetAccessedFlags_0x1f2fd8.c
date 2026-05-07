
bool ZydisGetAccessedFlags(long param_1,long *param_2)

{
  if (0x4b < (*(ushort *)(param_1 + 4) >> 6 & 0x7f)) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("definition->flags_reference < (sizeof(ACCESSED_FLAGS) / sizeof((ACCESSED_FLAGS)[0]))"
                  ,"/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/SharedData.c",0xc3,
                  "ZydisGetAccessedFlags");
  }
  *param_2 = (long)(ACCESSED_FLAGS + (long)(int)(*(ushort *)(param_1 + 4) >> 6 & 0x7f) * 0x28);
  return (*(ushort *)(param_1 + 4) >> 6 & 0x7f) != 0;
}

