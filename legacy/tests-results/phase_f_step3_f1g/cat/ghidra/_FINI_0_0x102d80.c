
void _FINI_0(void)

{
  if ((DAT_001200d0 & 1) == 0) {
    if (PTR___cxa_finalize_0011ffb8 != (undefined *)0x0) {
      __cxa_finalize(PTR_LOOP_00120008);
    }
    FUN_00102d10();
    DAT_001200d0 = 1;
  }
  return;
}

