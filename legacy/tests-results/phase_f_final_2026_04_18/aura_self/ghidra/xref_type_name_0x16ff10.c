
undefined * xref_type_name(int param_1)

{
  undefined *puVar1;
  
  if (param_1 == 1) {
    return &DAT_001f9390;
  }
  if (param_1 != 2) {
    puVar1 = &DAT_001f8d08;
    if (param_1 != 0) {
      puVar1 = &DAT_001f9918;
    }
    return puVar1;
  }
  return &DAT_001fa868;
}

