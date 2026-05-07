
ulong map_groups(ulong param_1,long param_2)

{
  byte bVar1;
  char cVar2;
  byte bVar3;
  byte bVar4;
  uint uVar5;
  ulong uVar6;
  long lVar7;
  
  lVar7 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
  if (lVar7 != 0) {
    uVar6 = MCInst_getOpcode();
    param_1 = param_2 + (uVar6 & 0xffffffff) * 0x5e;
    cVar2 = *(char *)(param_1 + 0x54);
    if (cVar2 != '\0') {
      bVar3 = *(byte *)(lVar7 + 0x5b);
      if (7 < bVar3) {
LAB_001e4900:
        uVar5 = puts("ERROR: Too many groups defined in instruction mapping.");
        return (ulong)uVar5;
      }
      bVar4 = bVar3 + 1;
      *(byte *)(lVar7 + 0x5b) = bVar4;
      *(char *)(lVar7 + (ulong)bVar3 + 0x53) = cVar2;
      cVar2 = *(char *)(param_1 + 0x55);
      if (cVar2 != '\0') {
        if (bVar4 == 8) goto LAB_001e4900;
        bVar1 = bVar3 + 2;
        *(byte *)(lVar7 + 0x5b) = bVar1;
        *(char *)(lVar7 + (ulong)bVar4 + 0x53) = cVar2;
        cVar2 = *(char *)(param_1 + 0x56);
        if (cVar2 != '\0') {
          if (bVar1 == 8) goto LAB_001e4900;
          bVar4 = bVar3 + 3;
          *(byte *)(lVar7 + 0x5b) = bVar4;
          *(char *)(lVar7 + (ulong)bVar1 + 0x53) = cVar2;
          cVar2 = *(char *)(param_1 + 0x57);
          if (cVar2 != '\0') {
            if (bVar4 == 8) goto LAB_001e4900;
            bVar1 = bVar3 + 4;
            *(byte *)(lVar7 + 0x5b) = bVar1;
            *(char *)(lVar7 + (ulong)bVar4 + 0x53) = cVar2;
            cVar2 = *(char *)(param_1 + 0x58);
            if (cVar2 != '\0') {
              if (bVar1 == 8) goto LAB_001e4900;
              bVar4 = bVar3 + 5;
              *(byte *)(lVar7 + 0x5b) = bVar4;
              *(char *)(lVar7 + (ulong)bVar1 + 0x53) = cVar2;
              cVar2 = *(char *)(param_1 + 0x59);
              if (cVar2 != '\0') {
                if (bVar4 == 8) goto LAB_001e4900;
                bVar1 = bVar3 + 6;
                *(byte *)(lVar7 + 0x5b) = bVar1;
                *(char *)(lVar7 + (ulong)bVar4 + 0x53) = cVar2;
                cVar2 = *(char *)(param_1 + 0x5a);
                if (cVar2 != '\0') {
                  if (bVar1 == 8) goto LAB_001e4900;
                  *(byte *)(lVar7 + 0x5b) = bVar3 + 7;
                  *(char *)(lVar7 + (ulong)bVar1 + 0x53) = cVar2;
                  bVar4 = *(byte *)(param_1 + 0x5b);
                  param_1 = (ulong)bVar4;
                  if (bVar4 != 0) {
                    if ((byte)(bVar3 + 7) == '\b') goto LAB_001e4900;
                    *(byte *)(lVar7 + 0x5a) = bVar4;
                    *(undefined1 *)(lVar7 + 0x5b) = 8;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return param_1;
}

