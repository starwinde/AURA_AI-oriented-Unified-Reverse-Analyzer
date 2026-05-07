
void FUN_0010f7d0(long param_1,long param_2,undefined1 param_3)

{
  undefined8 *puVar1;
  undefined8 uVar2;
  
  puVar1 = malloc(0x20);
  if (puVar1 != (undefined8 *)0x0) {
    uVar2 = 0;
    if (param_2 != 0) {
      uVar2 = FUN_0010f784(param_2);
    }
    puVar1[1] = uVar2;
    uVar2 = 0;
    if (param_1 != 0) {
      uVar2 = FUN_0010f784(param_1);
    }
    *(undefined1 *)(puVar1 + 2) = param_3;
    *puVar1 = uVar2;
    puVar1[3] = DAT_00141348;
    DAT_00141348 = puVar1;
    return;
  }
                    /* WARNING: Subroutine does not return */
  FUN_0010d454();
}

