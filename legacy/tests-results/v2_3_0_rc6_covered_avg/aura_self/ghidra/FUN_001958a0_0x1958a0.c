
undefined8 FUN_001958a0(long param_1,undefined8 param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  ulong uVar4;
  undefined8 uVar5;
  long lVar6;
  uint uVar7;
  uint uVar8;
  undefined *puVar9;
  char cVar10;
  undefined8 uVar11;
  
  uVar2 = FUN_0018ffb0(param_2);
  if (uVar2 == 0xaf7) {
    FUN_0018ffd0(param_2,0);
    lVar6 = FUN_001900a0();
    if (lVar6 == 0x10) {
      uVar2 = *(uint *)(param_1 + 0x5c);
      uVar11 = 1;
    }
    else {
      uVar2 = *(uint *)(param_1 + 0x5c);
      uVar11 = 3;
    }
LAB_00195a34:
    if (uVar2 != 0) goto LAB_0019591c;
    uVar4 = FUN_0018ffb0(param_2);
    cVar10 = '\x0e';
    puVar9 = (&PTR_DAT_005e0b78)[(uVar4 & 0xffffffff) * 2];
    uVar4 = FUN_0018ffb0(param_2);
    uVar2 = (uint)(byte)(&DAT_005e0b70)[(uVar4 & 0xffffffff) * 0x10];
    if (uVar2 != 0) goto LAB_00195968;
    uVar8 = 1;
    uVar5 = FUN_00190124(param_2,0xe);
    FUN_0018ff10(param_2,0,uVar5);
  }
  else {
    if (0xaf7 < uVar2) {
      if (uVar2 < 0xc0c) {
        if (0xc09 < uVar2) goto LAB_00195b00;
      }
      else if (uVar2 - 0xc46 < 0x36) {
        uVar4 = 1L << ((ulong)(uVar2 - 0xc46) & 0x3f);
        if ((uVar4 & 0x20004000010e00) != 0) goto LAB_00195908;
        if ((uVar4 & 1) != 0) goto LAB_00195b00;
      }
LAB_00195a28:
      uVar2 = *(uint *)(param_1 + 0x5c);
      uVar11 = 3;
      goto LAB_00195a34;
    }
    if (uVar2 == 0xad3) {
LAB_00195b00:
      uVar2 = *(uint *)(param_1 + 0x5c);
      if (uVar2 < 2) {
        uVar11 = 3;
        goto LAB_00195a34;
      }
    }
    else {
      if ((uVar2 < 0xad3) || ((uVar2 != 0xada && (2 < uVar2 - 0xae5)))) goto LAB_00195a28;
LAB_00195908:
      uVar2 = *(uint *)(param_1 + 0x5c);
      if (uVar2 == 0) {
        return 3;
      }
    }
    uVar11 = 1;
LAB_0019591c:
    cVar10 = *(char *)(param_1 + 0x54 + (ulong)(uVar2 - 1));
    if (cVar10 == '\x0f') {
      cVar10 = '\x0e';
    }
    *(uint *)(param_1 + 0x5c) = uVar2 - 1;
    uVar4 = FUN_0018ffb0(param_2);
    puVar9 = (&PTR_DAT_005e0b78)[(uVar4 & 0xffffffff) * 2];
    uVar4 = FUN_0018ffb0(param_2);
    uVar2 = (uint)(byte)(&DAT_005e0b70)[(uVar4 & 0xffffffff) * 0x10];
    if ((&DAT_005e0b70)[(uVar4 & 0xffffffff) * 0x10] == 0) {
      uVar3 = 0;
      uVar1 = 1;
    }
    else {
LAB_00195968:
      uVar8 = 0;
      do {
        uVar7 = uVar8;
        uVar3 = FUN_0018ffe0(param_2);
        uVar8 = uVar7 + 1;
        uVar1 = uVar8;
        if (uVar3 == uVar7) goto LAB_001959a8;
        uVar4 = FUN_001902e0(puVar9);
        if ((uVar4 & 1) != 0) {
          uVar5 = FUN_00190124(param_2,cVar10);
          FUN_0018ff10(param_2,uVar7,uVar5);
          if (cVar10 != '\x0e') goto LAB_001959cc;
          uVar5 = 0;
          goto LAB_001959d0;
        }
        puVar9 = puVar9 + 8;
      } while (uVar8 < uVar2);
      uVar1 = uVar7 + 2;
      uVar3 = uVar8;
    }
LAB_001959a8:
    uVar8 = uVar1;
    uVar5 = FUN_00190124(param_2,cVar10);
    FUN_0018ff10(param_2,uVar3,uVar5);
    if (cVar10 != '\x0e') {
LAB_001959cc:
      uVar5 = 3;
      goto LAB_001959d0;
    }
  }
  uVar5 = 0;
LAB_001959d0:
  uVar5 = FUN_001900e0(param_2,uVar5);
  FUN_0018ff10(param_2,uVar8,uVar5);
  return uVar11;
}

