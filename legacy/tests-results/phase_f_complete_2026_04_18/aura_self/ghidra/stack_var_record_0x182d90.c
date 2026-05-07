
void stack_var_record(long param_1)

{
  uint uVar1;
  long *plVar2;
  long *plVar3;
  size_t __size;
  long lVar4;
  uint uVar5;
  
  uVar1 = s_stack_var_count;
  plVar2 = s_stack_var_offsets;
  if (s_stack_var_count == 0) {
    if (s_stack_var_cap != 0) {
      s_stack_var_count = 1;
      goto LAB_00182e04;
    }
LAB_00182e54:
    __size = 0x80;
    uVar5 = 0x10;
  }
  else {
    do {
      lVar4 = *plVar2;
      plVar2 = plVar2 + 1;
      if (lVar4 == param_1) {
        return;
      }
    } while (plVar2 != s_stack_var_offsets + s_stack_var_count);
    if (s_stack_var_count < s_stack_var_cap) {
      s_stack_var_count = s_stack_var_count + 1;
      goto LAB_00182e04;
    }
    if (s_stack_var_cap == 0) goto LAB_00182e54;
    uVar5 = s_stack_var_cap << 1;
    __size = ((ulong)s_stack_var_cap & 0x7fffffff) << 4;
  }
  plVar3 = realloc(s_stack_var_offsets,__size);
  if (plVar3 == (long *)0x0) {
    return;
  }
  s_stack_var_count = uVar1 + 1;
  plVar2 = plVar3 + uVar1;
  s_stack_var_offsets = plVar3;
  s_stack_var_cap = uVar5;
LAB_00182e04:
  *plVar2 = param_1;
  return;
}

