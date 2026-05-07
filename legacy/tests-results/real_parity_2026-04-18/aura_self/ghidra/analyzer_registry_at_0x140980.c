
undefined8 analyzer_registry_at(ulong param_1)

{
  if (param_1 < g_count) {
    return *(undefined8 *)(g_entries + param_1 * 8);
  }
  return 0;
}

