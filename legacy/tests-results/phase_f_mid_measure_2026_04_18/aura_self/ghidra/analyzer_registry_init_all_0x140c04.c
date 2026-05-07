
void analyzer_registry_init_all(void)

{
  if ((g_initialized & 1) != 0) {
    return;
  }
  g_initialized = 1;
  aarch64_plt_thunks_init();
  addr_tables_init();
  call_fixup_init();
  const_refs_init();
  elf_scalar_refs_init();
  embedded_media_init();
  data_archive_init();
  entry_points_init();
  extern_entry_refs_init();
  extern_resolver_init();
  func_id_init();
  func_start_after_code_init();
  func_start_after_data_init();
  param_id_init();
  shared_return_init();
  subroutine_refs_init();
  return;
}

