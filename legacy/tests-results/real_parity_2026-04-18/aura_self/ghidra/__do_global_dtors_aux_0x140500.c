
void __do_global_dtors_aux(void)

{
  if ((completed_0 & 1) == 0) {
    if (PTR___cxa_finalize_005ffec0 != (undefined *)0x0) {
      __cxa_finalize(__dso_handle);
    }
    deregister_tm_clones();
    completed_0 = 1;
  }
  return;
}

