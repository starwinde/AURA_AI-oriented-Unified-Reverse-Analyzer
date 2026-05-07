
void _obstack_free(long param_1,ulong *param_2)

{
  ulong *puVar1;
  ulong *puVar2;
  
  puVar1 = *(ulong **)(param_1 + 8);
  while( true ) {
    if (puVar1 == (ulong *)0x0) {
      if (param_2 == (ulong *)0x0) {
        return;
      }
                    /* WARNING: Subroutine does not return */
      abort();
    }
    if ((puVar1 < param_2) && (puVar2 = (ulong *)*puVar1, param_2 <= puVar2)) break;
    puVar2 = (ulong *)puVar1[1];
    if ((*(byte *)(param_1 + 0x50) & 1) == 0) {
      (**(code **)(param_1 + 0x40))();
      *(byte *)(param_1 + 0x50) = *(byte *)(param_1 + 0x50) | 2;
      puVar1 = puVar2;
    }
    else {
      (**(code **)(param_1 + 0x40))(*(undefined8 *)(param_1 + 0x48),puVar1);
      *(byte *)(param_1 + 0x50) = *(byte *)(param_1 + 0x50) | 2;
      puVar1 = puVar2;
    }
  }
  *(ulong **)(param_1 + 8) = puVar1;
  *(ulong **)(param_1 + 0x10) = param_2;
  *(ulong **)(param_1 + 0x18) = param_2;
  *(ulong **)(param_1 + 0x20) = puVar2;
  return;
}

