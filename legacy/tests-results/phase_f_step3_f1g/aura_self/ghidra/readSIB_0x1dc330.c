
undefined8 readSIB(long param_1)

{
  char cVar1;
  byte bVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  
  if ((*(byte *)(param_1 + 0xe) & 1) == 0) {
    cVar1 = *(char *)(param_1 + 0x7d);
    *(undefined1 *)(param_1 + 0xe) = 1;
    if (cVar1 == '\x04') {
      iVar5 = 1;
      *(undefined4 *)(param_1 + 0x24) = 0x11;
    }
    else if (cVar1 == '\b') {
      iVar5 = 0x11;
      *(undefined4 *)(param_1 + 0x24) = 0x21;
    }
    else {
      if (cVar1 == '\x02') {
        return 0xffffffff;
      }
      iVar5 = 0;
    }
    iVar4 = (**(code **)(param_1 + 0x48))
                      (*(undefined8 *)(param_1 + 0x50),param_1 + 0xf,*(undefined8 *)(param_1 + 0x58)
                      );
    if (iVar4 != 0) {
      return 0xffffffff;
    }
    iVar4 = 0;
    bVar2 = *(byte *)(param_1 + 0xf);
    uVar3 = ((int)(uint)*(byte *)(param_1 + 5) >> 1 & 1U) << 3 | bVar2 >> 3 & 7;
    *(long *)(param_1 + 0x58) = *(long *)(param_1 + 0x58) + 1;
    if (uVar3 != 4) {
      iVar4 = uVar3 + *(int *)(param_1 + 0x24);
    }
    *(int *)(param_1 + 0x28) = iVar4;
    *(char *)(param_1 + 0x2c) = (char)(1 << (ulong)(bVar2 >> 6));
    uVar3 = (*(byte *)(param_1 + 5) & 1) << 3 | bVar2 & 7;
    if ((bVar2 & 7) == 5) {
      bVar2 = *(byte *)(param_1 + 0xa0) >> 6;
      if (bVar2 == 2) {
        *(uint *)(param_1 + 0x30) = uVar3 + iVar5;
        *(undefined4 *)(param_1 + 200) = 3;
      }
      else {
        if (bVar2 == 3) {
          return 0xffffffff;
        }
        if (bVar2 == 1) {
          *(uint *)(param_1 + 0x30) = uVar3 + iVar5;
          *(undefined4 *)(param_1 + 200) = 1;
        }
        else {
          *(undefined4 *)(param_1 + 0x30) = 0;
          *(undefined4 *)(param_1 + 200) = 3;
        }
      }
    }
    else {
      *(uint *)(param_1 + 0x30) = uVar3 + iVar5;
    }
  }
  return 0;
}

