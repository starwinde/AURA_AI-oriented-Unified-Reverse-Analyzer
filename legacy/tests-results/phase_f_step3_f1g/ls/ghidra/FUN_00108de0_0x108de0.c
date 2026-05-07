
void FUN_00108de0(void)

{
  undefined8 *puVar1;
  ulong uVar2;
  
  if (DAT_00140ee0 != 0) {
    uVar2 = 0;
    do {
      puVar1 = *(undefined8 **)(DAT_00140ee8 + uVar2 * 8);
      free((void *)*puVar1);
      free((void *)puVar1[1]);
      free((void *)puVar1[2]);
      if ((undefined *)puVar1[0x14] != &DAT_001400c8) {
        freecon();
      }
      uVar2 = uVar2 + 1;
    } while (uVar2 < DAT_00140ee0);
  }
  DAT_00140ee0 = 0;
  DAT_00140ef4 = 0;
  DAT_00140ef8 = 0;
  DAT_00140f04 = 0;
  DAT_00140f08 = 0;
  DAT_00140efc = 0;
  DAT_00140f00 = 0;
  DAT_00140f0c = 0;
  DAT_00140f10 = 0;
  DAT_00140ef0 = 0;
  DAT_00140ef1 = 0;
  DAT_00140f14 = 0;
  DAT_00140f18 = 0;
  return;
}

