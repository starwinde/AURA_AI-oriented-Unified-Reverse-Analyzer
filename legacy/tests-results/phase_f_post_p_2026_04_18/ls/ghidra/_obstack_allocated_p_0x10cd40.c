
undefined8 _obstack_allocated_p(long param_1,ulong *param_2)

{
  ulong *puVar1;
  
  puVar1 = *(ulong **)(param_1 + 8);
  while( true ) {
    if (puVar1 == (ulong *)0x0) {
      return 0;
    }
    if ((puVar1 < param_2) && (param_2 <= (ulong *)*puVar1)) break;
    puVar1 = (ulong *)puVar1[1];
  }
  return 1;
}

