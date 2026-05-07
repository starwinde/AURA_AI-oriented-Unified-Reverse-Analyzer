
undefined4 * FUN_0017d440(long param_1,undefined8 param_2)

{
  undefined4 *puVar1;
  
  if (param_1 != 0) {
    puVar1 = calloc(1,0x18);
    if (puVar1 != (undefined4 *)0x0) {
      *puVar1 = *(undefined4 *)(param_1 + 8);
      *(undefined8 *)(puVar1 + 2) = param_2;
      *(long *)(puVar1 + 4) = param_1;
    }
    return puVar1;
  }
  return (undefined4 *)0x0;
}

