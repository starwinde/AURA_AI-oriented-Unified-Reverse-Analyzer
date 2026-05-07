
undefined * xref_type_name(int param_1)

{
  undefined *puVar1;
  
  if (param_1 == 1) {
    return &DAT_001f8970;
  }
  if (param_1 != 2) {
    puVar1 = &DAT_001f82e8;
    if (param_1 != 0) {
      puVar1 = &DAT_001f8ef8;
    }
    return puVar1;
  }
  return &DAT_001f9e48;
}

