
void printopaquemem(long param_1,undefined4 param_2,undefined8 param_3)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = **(uint **)(param_1 + 0x310);
  if (uVar1 == 0x151) {
LAB_001e0770:
    iVar2 = *(int *)(*(long *)(param_1 + 800) + 4);
    if (iVar2 == 4) goto LAB_001e06b4;
LAB_001e060c:
    if (iVar2 == 8) {
      uVar1 = **(uint **)(param_1 + 0x310);
      if (uVar1 != 0x153) {
        if (uVar1 < 0x154) {
          if (uVar1 < 0xac) {
            if (uVar1 < 0xaa) {
LAB_001e072c:
              *(undefined1 *)(param_1 + 0x328) = 8;
              printMemReference(param_1,param_2,param_3);
              return;
            }
          }
          else if (uVar1 != 0x151) goto LAB_001e072c;
        }
        else if ((uVar1 & 0xffffffef) != 0x2a3) goto LAB_001e072c;
      }
      *(undefined1 *)(param_1 + 0x328) = 10;
      printMemReference(param_1,param_2,param_3);
      return;
    }
    if (iVar2 != 2) goto LAB_001e0644;
    uVar1 = **(uint **)(param_1 + 0x310);
    if (uVar1 == 0x151) goto LAB_001e06b4;
    if (uVar1 < 0x152) {
      if (uVar1 - 0xaa < 2) goto LAB_001e063c;
    }
    else if (((uVar1 & 0xffffffef) == 0x2a3) || (uVar1 == 0x153)) goto LAB_001e06b4;
    *(undefined1 *)(param_1 + 0x328) = 2;
  }
  else {
    if (uVar1 < 0x152) {
      if ((uVar1 - 0xaa < 0x2b) && ((0x50000000003U >> ((ulong)(uVar1 - 0xaa) & 0x3f) & 1) != 0)) {
        iVar2 = *(int *)(*(long *)(param_1 + 800) + 4);
        if (iVar2 != 4) goto LAB_001e060c;
      }
      else {
LAB_001e0674:
        SStream_concat0(param_3,"ptr ");
        iVar2 = *(int *)(*(long *)(param_1 + 800) + 4);
        if (iVar2 != 4) goto LAB_001e060c;
        uVar1 = **(uint **)(param_1 + 0x310);
        if (uVar1 == 0x153) goto LAB_001e06b4;
        if (0x153 < uVar1) goto LAB_001e06a8;
      }
      if (uVar1 < 0xad) {
        if (0xa9 < uVar1) {
LAB_001e06b4:
          *(undefined1 *)(param_1 + 0x328) = 6;
          printMemReference(param_1,param_2,param_3);
          return;
        }
      }
      else if (uVar1 == 0x151) goto LAB_001e06b4;
    }
    else {
      if ((uVar1 & 0xffffffef) != 0x2a3) {
        if (uVar1 == 0x153) goto LAB_001e0770;
        goto LAB_001e0674;
      }
      iVar2 = *(int *)(*(long *)(param_1 + 800) + 4);
      if (iVar2 != 4) goto LAB_001e060c;
LAB_001e06a8:
      if ((uVar1 & 0xffffffef) == 0x2a3) goto LAB_001e06b4;
    }
LAB_001e063c:
    *(undefined1 *)(param_1 + 0x328) = 4;
  }
LAB_001e0644:
  printMemReference(param_1,param_2,param_3);
  return;
}

