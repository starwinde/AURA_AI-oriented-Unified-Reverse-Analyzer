
void _FINI_0(void)

{
  if ((DAT_001402a0 & 1) == 0) {
    if (PTR___cxa_finalize_0013ff98 != (undefined *)0x0) {
      __cxa_finalize(PTR_LOOP_00140008);
    }
    FUN_00105e10();
    DAT_001402a0 = 1;
  }
  return;
}

