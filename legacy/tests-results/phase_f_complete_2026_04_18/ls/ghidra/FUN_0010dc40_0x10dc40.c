
long FUN_0010dc40(undefined8 *param_1,byte param_2,undefined8 param_3,ulong param_4)

{
  ulong uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  long lVar5;
  ulong uVar6;
  size_t sVar7;
  size_t __n;
  long lVar8;
  uint uVar9;
  undefined8 uVar10;
  ulong extraout_x8;
  size_t *psVar11;
  char *__s;
  
  if ((param_2 & 1) == 0) {
    __s = (char *)*param_1;
    if ((DAT_00141291 & 1) == 0) goto LAB_0010dc84;
    uVar3 = (uint)*(byte *)((long)param_1 + 0xa9);
    if (((DAT_00141292 & 1) == 0) || ((*(byte *)((long)param_1 + 0xa9) & 1) == 0)) {
      uVar9 = *(uint *)(param_1 + 5);
    }
    else {
      uVar9 = *(uint *)((long)param_1 + 0x9c);
    }
LAB_0010dd08:
    uVar2 = uVar3;
    if ((*(byte *)(param_1 + 0x15) & 1) == 0) goto LAB_0010dd10;
LAB_0010de04:
    uVar3 = uVar9 & 0xf000;
    if (uVar3 == 0x8000) {
      if (((uVar9 >> 0xb & 1) != 0) && (uVar6 = FUN_0010aca0(0x10), (uVar6 & 1) != 0)) {
        lVar5 = 0x100;
        goto LAB_0010dd60;
      }
      if (((uVar9 >> 10 & 1) != 0) && (uVar6 = FUN_0010aca0(0x11), (uVar6 & 1) != 0)) {
        lVar5 = 0x110;
        goto LAB_0010dd60;
      }
      uVar6 = FUN_0010aca0(0x15);
      if (((uVar6 & 1) != 0) && ((*(byte *)(param_1 + 0x16) & 1) != 0)) {
        lVar5 = 0x150;
        goto LAB_0010dd60;
      }
      if (((uVar9 & 0x49) != 0) && (uVar6 = FUN_0010aca0(0xe), (uVar6 & 1) != 0)) {
        lVar5 = 0xe0;
        goto LAB_0010dd60;
      }
      if ((1 < *(uint *)((long)param_1 + 0x2c)) && (uVar6 = FUN_0010aca0(0x16), (uVar6 & 1) != 0)) {
        lVar5 = 0x160;
        goto LAB_0010dd60;
      }
      goto LAB_0010ded4;
    }
    if (uVar3 == 0x4000) {
      if ((uVar9 & 0x202) == 0x202) {
        lVar5 = 0x140;
        uVar6 = FUN_0010aca0(0x14);
        if ((uVar6 & 1) != 0) goto LAB_0010dd60;
      }
      if ((uVar9 >> 1 & 1) != 0) {
        lVar5 = 0x130;
        uVar6 = FUN_0010aca0(0x13);
        if ((uVar6 & 1) != 0) goto LAB_0010dd60;
      }
      lVar8 = 0x60;
      lVar5 = lVar8;
      if ((uVar9 >> 9 & 1) != 0) {
        uVar6 = FUN_0010aca0(0x12);
        lVar5 = 0x120;
        if ((uVar6 & 1) == 0) {
          lVar5 = lVar8;
        }
      }
      goto LAB_0010dd60;
    }
    if (uVar3 != 0xa000) {
      lVar5 = 0x80;
      if ((((uVar3 != 0x1000) && (lVar5 = 0x90, uVar3 != 0xc000)) && (lVar5 = 0xa0, uVar3 != 0x6000)
          ) && (lVar5 = 0xb0, uVar3 != 0x2000)) {
        lVar5 = 0xd0;
      }
      goto LAB_0010dd60;
    }
    lVar5 = 0x70;
    if (uVar2 != 0) goto LAB_0010dd60;
  }
  else {
    __s = (char *)param_1[1];
    if ((DAT_00141291 & 1) == 0) {
LAB_0010dc84:
      lVar5 = FUN_0010d8c0(__s,DAT_00140f20,*(undefined4 *)((long)param_1 + 0xb4),0,param_2 ^ 1,
                           param_3,param_1[2]);
      FUN_0010b1e0();
      return lVar5;
    }
    uVar9 = *(uint *)((long)param_1 + 0x9c);
    if ((*(byte *)((long)param_1 + 0xa9) & 1) == 0) {
      uVar6 = FUN_0010aca0(0xc);
      if ((uVar6 & 1) != 0) {
        lVar5 = 0xc0;
        goto LAB_0010dd60;
      }
      uVar3 = 0xffffffff;
      goto LAB_0010dd08;
    }
    uVar2 = 0;
    uVar3 = 0;
    if ((*(byte *)(param_1 + 0x15) & 1) != 0) goto LAB_0010de04;
LAB_0010dd10:
    uVar9 = *(uint *)(&DAT_001184e0 + (ulong)*(uint *)(param_1 + 0x13) * 4);
    if (uVar9 == 5) {
LAB_0010ded4:
      sVar7 = strlen(__s);
      for (psVar11 = DAT_00141298; psVar11 != (size_t *)0x0; psVar11 = (size_t *)psVar11[5]) {
        __n = *psVar11;
        if (__n <= sVar7) {
          if ((psVar11[4] & 1) == 0) {
            if (__n != 0 && __s + (sVar7 - __n) != (char *)psVar11[1]) {
              iVar4 = FUN_00107090();
              goto joined_r0x0010def4;
            }
          }
          else {
            iVar4 = strncmp(__s + (sVar7 - __n),(char *)psVar11[1],__n);
joined_r0x0010def4:
            if (iVar4 != 0) goto LAB_0010def8;
          }
          psVar11 = psVar11 + 2;
          goto LAB_0010dd70;
        }
LAB_0010def8:
      }
      lVar5 = 0x50;
      goto LAB_0010dd60;
    }
    lVar5 = (ulong)uVar9 << 4;
    if (uVar3 != 0 || uVar9 != 7) goto LAB_0010dd60;
  }
  lVar5 = 0xd0;
  if (((DAT_00141292 & 1) == 0) && (uVar6 = FUN_0010aca0(0xd), (uVar6 & 1) == 0)) {
    lVar5 = 0x70;
  }
LAB_0010dd60:
  psVar11 = (size_t *)((long)&DAT_001400f0 + lVar5);
LAB_0010dd70:
  if (psVar11[1] == 0) {
    uVar10 = DAT_00140f20;
    uVar3 = FUN_0010aca0(*(undefined4 *)((long)param_1 + 0xb4),4);
    lVar5 = FUN_0010d8c0(__s,uVar10,extraout_x8 & 0xffffffff,0);
    FUN_0010b1e0();
    if ((uVar3 & 1) == 0) {
      return lVar5;
    }
  }
  else {
    lVar5 = FUN_0010d8c0(__s,DAT_00140f20,*(undefined4 *)((long)param_1 + 0xb4),psVar11,param_2 ^ 1,
                         param_3);
    FUN_0010b1e0();
  }
  if (DAT_00140118 == 0) {
    FUN_0010b000(&DAT_001400f0);
    FUN_0010b000(&DAT_00140120);
    FUN_0010b000(&DAT_00140100);
  }
  else {
    FUN_0010b000(&DAT_00140110);
  }
  if (DAT_00141020 == 0) {
    return lVar5;
  }
  uVar6 = 0;
  if (DAT_00141020 != 0) {
    uVar6 = param_4 / DAT_00141020;
  }
  uVar1 = 0;
  if (DAT_00141020 != 0) {
    uVar1 = ((param_4 - 1) + lVar5) / DAT_00141020;
  }
  if (uVar6 == uVar1) {
    return lVar5;
  }
  FUN_0010b000(&DAT_00140260);
  return lVar5;
}

