
undefined * xref_type_name(int param_1)

{
  undefined *puVar1;
  
  if (param_1 == 1) {
    return &DAT_001f8fd8;
  }
  if (param_1 != 2) {
    puVar1 = &DAT_001f8950;
    if (param_1 != 0) {
      puVar1 = &DAT_001f9560;
    }
    return puVar1;
  }
  return &DAT_001fa4a8;
}

