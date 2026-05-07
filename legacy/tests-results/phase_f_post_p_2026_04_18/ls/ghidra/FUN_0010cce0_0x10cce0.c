
void FUN_0010cce0(long param_1)

{
  undefined8 *puVar1;
  
  puVar1 = *(undefined8 **)(param_1 + 0x18);
  if ((ulong)(*(long *)(param_1 + 0x20) - (long)puVar1) < 8) {
    _obstack_newchunk(param_1,8);
    puVar1 = *(undefined8 **)(param_1 + 0x18);
  }
  *puVar1 = DAT_001402c0;
  *(long *)(param_1 + 0x18) = *(long *)(param_1 + 0x18) + 8;
  return;
}

