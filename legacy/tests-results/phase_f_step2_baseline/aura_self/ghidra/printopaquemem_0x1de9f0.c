
void printopaquemem(long param_1,undefined4 param_2,undefined8 param_3)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = **(uint **)(param_1 + 0x310);
  if (uVar1 == 0x151) {
LAB_001debb0:
    iVar2 = *(int *)(*(long *)(param_1 + 800) + 4);
    if (iVar2 == 4) goto LAB_001deaf4;
LAB_001dea4c:
    if (iVar2 == 8) {
      uVar1 = **(uint **)(param_1 + 0x310);
      if (uVar1 != 0x153) {
        if (uVar1 < 0x154) {
          if (uVar1 < 0xac) {
            if (uVar1 < 0xaa) {
LAB_001deb6c:
              *(undefined1 *)(param_1 + 0x328) = 8;
              printMemReference(param_1,param_2,param_3);
              return;
            }
          }
          else if (uVar1 != 0x151) goto LAB_001deb6c;
        }
        else if ((uVar1 & 0xffffffef) != 0x2a3) goto LAB_001deb6c;
      }
      *(undefined1 *)(param_1 + 0x328) = 10;
      printMemReference(param_1,param_2,param_3);
      return;
    }
    if (iVar2 != 2) goto LAB_001dea84;
    uVar1 = **(uint **)(param_1 + 0x310);
    if (uVar1 == 0x151) goto LAB_001deaf4;
    if (uVar1 < 0x152) {
      if (uVar1 - 0xaa < 2) goto LAB_001dea7c;
    }
    else if (((uVar1 & 0xffffffef) == 0x2a3) || (uVar1 == 0x153)) goto LAB_001deaf4;
    *(undefined1 *)(param_1 + 0x328) = 2;
  }
  else {
    if (uVar1 < 0x152) {
      if ((uVar1 - 0xaa < 0x2b) && ((0x50000000003U >> ((ulong)(uVar1 - 0xaa) & 0x3f) & 1) != 0)) {
        iVar2 = *(int *)(*(long *)(param_1 + 800) + 4);
        if (iVar2 != 4) goto LAB_001dea4c;
      }
      else {
LAB_001deab4:
        SStream_concat0(param_3,"ptr ");
        iVar2 = *(int *)(*(long *)(param_1 + 800) + 4);
        if (iVar2 != 4) goto LAB_001dea4c;
        uVar1 = **(uint **)(param_1 + 0x310);
        if (uVar1 == 0x153) goto LAB_001deaf4;
        if (0x153 < uVar1) goto LAB_001deae8;
      }
      if (uVar1 < 0xad) {
        if (0xa9 < uVar1) {
LAB_001deaf4:
          *(undefined1 *)(param_1 + 0x328) = 6;
          printMemReference(param_1,param_2,param_3);
          return;
        }
      }
      else if (uVar1 == 0x151) goto LAB_001deaf4;
    }
    else {
      if ((uVar1 & 0xffffffef) != 0x2a3) {
        if (uVar1 == 0x153) goto LAB_001debb0;
        goto LAB_001deab4;
      }
      iVar2 = *(int *)(*(long *)(param_1 + 800) + 4);
      if (iVar2 != 4) goto LAB_001dea4c;
LAB_001deae8:
      if ((uVar1 & 0xffffffef) == 0x2a3) goto LAB_001deaf4;
    }
LAB_001dea7c:
    *(undefined1 *)(param_1 + 0x328) = 4;
  }
LAB_001dea84:
  printMemReference(param_1,param_2,param_3);
  return;
}

