
void FUN_0010d4a0(undefined8 param_1)

{
  undefined8 *puVar1;
  
  puVar1 = malloc(0x10);
  if (puVar1 != (undefined8 *)0x0) {
    *puVar1 = param_1;
    puVar1[1] = DAT_00141028;
    DAT_00141028 = puVar1;
    return;
  }
                    /* WARNING: Subroutine does not return */
  FUN_0010d454();
}

