
void analyzer_registry_clear(void)

{
  free(g_entries);
  g_entries = (void *)0x0;
  g_capacity = 0;
  g_initialized = 0;
  g_count = 0;
  return;
}

