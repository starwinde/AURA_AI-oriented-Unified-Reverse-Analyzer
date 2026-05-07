
void _FINI_0(void)

{
  if ((DAT_006005b0 & 1) == 0) {
    if (PTR___cxa_finalize_005ffec0 != (undefined *)0x0) {
      __cxa_finalize(PTR_LOOP_00600008);
    }
    FUN_00140650();
    DAT_006005b0 = 1;
  }
  return;
}

