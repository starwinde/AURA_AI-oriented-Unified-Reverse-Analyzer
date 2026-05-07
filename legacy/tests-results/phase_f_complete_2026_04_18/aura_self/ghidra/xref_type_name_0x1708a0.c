
undefined * xref_type_name(int param_1)

{
  undefined *puVar1;
  
  if (param_1 == 1) {
    return &DAT_001fa550;
  }
  if (param_1 != 2) {
    puVar1 = &DAT_001f9ec0;
    if (param_1 != 0) {
      puVar1 = &DAT_001faad0;
    }
    return puVar1;
  }
  return &DAT_001fba18;
}

