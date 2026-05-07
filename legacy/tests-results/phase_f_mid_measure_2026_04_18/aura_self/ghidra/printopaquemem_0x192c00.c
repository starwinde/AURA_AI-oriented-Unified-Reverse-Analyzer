
void printopaquemem(long param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = *(int *)(*(long *)(param_1 + 800) + 4);
  if (iVar1 == 4) {
    uVar2 = **(uint **)(param_1 + 0x310);
    if (uVar2 == 0x153) {
LAB_00192ca0:
      *(undefined1 *)(param_1 + 0x328) = 6;
      printMemReference();
      return;
    }
    if (uVar2 < 0x154) {
      if (uVar2 < 0xad) {
        if (0xa9 < uVar2) goto LAB_00192ca0;
      }
      else if (uVar2 == 0x151) goto LAB_00192ca0;
    }
    else if ((uVar2 & 0xffffffef) == 0x2a3) goto LAB_00192ca0;
  }
  else {
    if (iVar1 == 8) {
      uVar2 = **(uint **)(param_1 + 0x310);
      if (uVar2 != 0x153) {
        if (uVar2 < 0x154) {
          if (uVar2 < 0xac) {
            if (uVar2 < 0xaa) {
LAB_00192cc8:
              *(undefined1 *)(param_1 + 0x328) = 8;
              printMemReference();
              return;
            }
          }
          else if (uVar2 != 0x151) goto LAB_00192cc8;
        }
        else if ((uVar2 & 0xffffffef) != 0x2a3) goto LAB_00192cc8;
      }
      *(undefined1 *)(param_1 + 0x328) = 10;
      printMemReference();
      return;
    }
    if (iVar1 != 2) goto LAB_00192c48;
    uVar2 = **(uint **)(param_1 + 0x310);
    if (uVar2 == 0x151) goto LAB_00192ca0;
    if (0x151 < uVar2) {
      if (((uVar2 & 0xffffffef) == 0x2a3) || (uVar2 == 0x153)) goto LAB_00192ca0;
LAB_00192ce8:
      *(undefined1 *)(param_1 + 0x328) = 2;
      printMemReference();
      return;
    }
    if (1 < uVar2 - 0xaa) goto LAB_00192ce8;
  }
  *(undefined1 *)(param_1 + 0x328) = 4;
LAB_00192c48:
  printMemReference();
  return;
}

