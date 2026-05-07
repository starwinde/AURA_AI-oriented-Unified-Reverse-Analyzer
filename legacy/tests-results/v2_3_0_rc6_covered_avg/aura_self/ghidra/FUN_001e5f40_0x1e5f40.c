
undefined8 FUN_001e5f40(long param_1,undefined8 param_2)

{
  char cVar1;
  byte bVar2;
  ushort uVar3;
  uint uVar4;
  uint uVar5;
  long lVar6;
  uint uVar7;
  uint uVar8;
  char *pcVar9;
  undefined2 uVar10;
  uint uVar11;
  
  cVar1 = *(char *)(param_1 + 0x330);
  if (cVar1 == -0xe) {
    uVar4 = FUN_0018ffb0();
    if (8 < uVar4 - 0x3b68) {
      if (uVar4 - 0x92 < 0x3b23) goto LAB_001e61cc;
      *(undefined1 *)(param_1 + 0x330) = 0;
      goto LAB_001e60f8;
    }
    if (((0x149UL >> ((ulong)(uVar4 - 0x3b68) & 0x3f) & 1) != 0) &&
       (*(char *)(param_1 + 0x3b8) != '\0')) {
      FUN_001903f0(param_2,"xacquire|");
      goto LAB_001e5f98;
    }
LAB_001e61cc:
    uVar5 = 0;
    uVar8 = 0x3b22;
    uVar11 = 0x1e23;
    uVar7 = 0x3b22;
    while( true ) {
      uVar7 = uVar7 >> 1;
      if (uVar4 == uVar11) break;
      if (uVar4 < uVar11) {
        uVar8 = uVar7 - 1;
        if (uVar8 < uVar5) goto LAB_001e6218;
      }
      else {
        uVar5 = uVar7 + 1;
        if (uVar8 < uVar5) goto LAB_001e6218;
      }
      uVar7 = uVar8 + uVar5;
      uVar11 = (uint)*(ushort *)(&DAT_00445c58 + (ulong)(uVar7 >> 1) * 0x50);
    }
    uVar3 = *(ushort *)(&UNK_00445c5a + ((ulong)uVar7 * 4 + (ulong)uVar7) * 0x10);
    if (uVar3 == 0x1e6) {
      if (uVar4 == 0x6a3) goto LAB_001e6370;
    }
    else if (uVar3 < 0x1e7) {
      if (uVar3 == 0x6d) {
        if (uVar4 == 0x2b6) goto LAB_001e6370;
      }
      else if (uVar3 < 0x6e) {
        if (uVar3 == 0x6c) goto LAB_001e6370;
      }
      else if (uVar3 < 0xee) {
        if (((0xeb < uVar3) || (uVar3 < 0x71)) || (uVar3 == 0xe9)) goto LAB_001e6370;
      }
      else if (uVar3 < 0x15c) {
        if (0x157 < uVar3) goto LAB_001e6370;
      }
      else if (uVar3 == 0x1e5) goto LAB_001e6370;
    }
    else if (uVar3 == 0x28e) {
      if (uVar4 == 0x9d1) goto LAB_001e6370;
    }
    else if (uVar3 < 0x28f) {
      if (uVar3 < 0x207) {
        if ((0x203 < uVar3) || ((ushort)(uVar3 - 0x1e9) < 3)) {
LAB_001e6370:
          pcVar9 = "repne|";
          goto LAB_001e637c;
        }
      }
      else if (uVar3 == 0x28d) goto LAB_001e6370;
    }
    else if ((uVar3 < 0x291) || ((ushort)(uVar3 - 0x2c4) < 4)) goto LAB_001e6370;
LAB_001e6218:
    uVar11 = 0x1e23;
    uVar8 = 0x3b22;
    uVar5 = 0;
    uVar7 = 0x3b22;
    while( true ) {
      uVar7 = uVar7 >> 1;
      if (uVar4 == uVar11) break;
      if (uVar4 < uVar11) {
        uVar8 = uVar7 - 1;
        if (uVar8 < uVar5) goto LAB_001e60f0;
      }
      else {
        uVar5 = uVar7 + 1;
        if (uVar8 < uVar5) {
          *(undefined1 *)(param_1 + 0x330) = 0;
          goto LAB_001e60f8;
        }
      }
      uVar7 = uVar5 + uVar8;
      uVar11 = (uint)*(ushort *)(&DAT_00445c58 + (ulong)(uVar7 >> 1) * 0x50);
    }
    uVar3 = *(ushort *)(&UNK_00445c5a + ((ulong)uVar7 * 4 + (ulong)uVar7) * 0x10);
    if (0x110 < uVar3) {
      if (uVar3 < 0x161) {
        if (0x15e < uVar3) goto LAB_001e64c8;
        *(undefined1 *)(param_1 + 0x330) = 0;
      }
      else {
        if (uVar3 == 0x279) goto LAB_001e64c8;
        *(undefined1 *)(param_1 + 0x330) = 0;
      }
LAB_001e60f8:
      cVar1 = *(char *)(param_1 + 0x331);
      goto joined_r0x001e6100;
    }
    if (((uVar3 < 0xfe) && (uVar3 != 0x3e)) && (uVar3 != 0xac)) goto LAB_001e60f0;
LAB_001e64c8:
    FUN_001903f0(param_2,&DAT_00203bb0);
  }
  else if (cVar1 == -0xd) {
    uVar4 = FUN_0018ffb0();
    if (uVar4 - 0x3b68 < 9) {
      if (((0x149UL >> ((ulong)(uVar4 - 0x3b68) & 0x3f) & 1) != 0) &&
         (*(char *)(param_1 + 0x3b8) != '\0')) {
        FUN_001903f0(param_2,"xrelease|");
        goto LAB_001e5f98;
      }
    }
    else if (0x3b22 < uVar4 - 0x92) {
      *(undefined1 *)(param_1 + 0x330) = 0;
      goto LAB_001e60f8;
    }
    uVar5 = 0;
    uVar8 = 0x3b22;
    uVar11 = 0x1e23;
    uVar7 = 0x3b22;
    while( true ) {
      uVar7 = uVar7 >> 1;
      if (uVar4 == uVar11) break;
      if (uVar4 < uVar11) {
        uVar8 = uVar7 - 1;
        if (uVar8 < uVar5) goto LAB_001e6040;
      }
      else {
        uVar5 = uVar7 + 1;
        if (uVar8 < uVar5) goto LAB_001e6040;
      }
      uVar7 = uVar5 + uVar8;
      uVar11 = (uint)*(ushort *)(&DAT_00445c58 + (ulong)(uVar7 >> 1) * 0x50);
    }
    uVar5 = (uint)*(ushort *)(&UNK_00445c5a + ((ulong)uVar7 * 4 + (ulong)uVar7) * 0x10);
    if (*(ushort *)(&UNK_00445c5a + ((ulong)uVar7 * 4 + (ulong)uVar7) * 0x10) < 0x207) {
      if (uVar5 < 0x1e5) {
        if (uVar5 == 0x159) {
          if (uVar4 == 0x4fc) goto LAB_001e6308;
        }
        else {
          if (0x159 < uVar5) {
            uVar5 = uVar5 - 0x15a;
            goto joined_r0x001e66b8;
          }
          if (uVar5 < 0xee) {
            if ((0xeb < uVar5) || (uVar5 == 0xe9)) goto LAB_001e6308;
          }
          else if (uVar5 == 0x158) goto LAB_001e6308;
        }
      }
      else if (((1L << ((ulong)(uVar5 - 0x1e5) & 0x3f) & 0x380000051U) != 0) ||
              ((uVar5 == 0x1e6 && (uVar4 == 0x699)))) goto LAB_001e6308;
LAB_001e6040:
      uVar11 = 0x1e23;
      uVar8 = 0x3b22;
      uVar5 = 0;
      uVar7 = 0x3b22;
      while( true ) {
        uVar7 = uVar7 >> 1;
        if (uVar4 == uVar11) break;
        if (uVar4 < uVar11) {
          uVar8 = uVar7 - 1;
          if (uVar8 < uVar5) goto LAB_001e6098;
        }
        else {
          uVar5 = uVar7 + 1;
          if (uVar8 < uVar5) goto LAB_001e6098;
        }
        uVar7 = uVar5 + uVar8;
        uVar11 = (uint)*(ushort *)(&DAT_00445c58 + (ulong)(uVar7 >> 1) * 0x50);
      }
      uVar3 = *(ushort *)(&UNK_00445c5a + ((ulong)uVar7 * 4 + (ulong)uVar7) * 0x10);
      if (uVar3 == 0x70) goto LAB_001e6514;
      if (uVar3 < 0x71) {
        if (uVar3 == 0x6d) {
          if (uVar4 == 0x2b6) {
LAB_001e6514:
            pcVar9 = "repe|";
            goto LAB_001e637c;
          }
        }
        else if ((uVar3 & 0xfffd) == 0x6c) goto LAB_001e6514;
      }
      else if (uVar3 == 0x28e) {
        if (uVar4 == 0x9d1) goto LAB_001e6514;
      }
      else if (uVar3 < 0x28f) {
        if (uVar3 == 0x28d) goto LAB_001e6514;
      }
      else if ((ushort)(uVar3 - 0x28f) < 2) goto LAB_001e6514;
LAB_001e6098:
      uVar11 = 0x1e23;
      uVar8 = 0x3b22;
      uVar5 = 0;
      uVar7 = 0x3b22;
      while( true ) {
        uVar7 = uVar7 >> 1;
        if (uVar4 == uVar11) break;
        if (uVar4 < uVar11) {
          uVar8 = uVar7 - 1;
          if (uVar8 < uVar5) goto LAB_001e60f0;
        }
        else {
          uVar5 = uVar7 + 1;
          if (uVar8 < uVar5) goto LAB_001e60f0;
        }
        uVar7 = uVar8 + uVar5;
        uVar11 = (uint)*(ushort *)(&DAT_00445c58 + (ulong)(uVar7 >> 1) * 0x50);
      }
      if (*(short *)(&UNK_00445c5a + ((ulong)uVar7 * 4 + (ulong)uVar7) * 0x10) == 0x279) {
        FUN_001903f0(param_2,"repz|");
        goto LAB_001e5f98;
      }
LAB_001e60f0:
      *(undefined1 *)(param_1 + 0x330) = 0;
      goto LAB_001e60f8;
    }
    if (uVar5 == 0x2c5) {
      if (uVar4 == 0xa84) goto LAB_001e6308;
      goto LAB_001e6040;
    }
    if (0x2c5 < uVar5) {
      uVar5 = uVar5 - 0x2c6;
joined_r0x001e66b8:
      if ((uVar5 & 0xffff) < 2) goto LAB_001e6308;
      goto LAB_001e6040;
    }
    if (uVar5 != 0x2c4) goto LAB_001e6040;
LAB_001e6308:
    pcVar9 = "rep|";
LAB_001e637c:
    FUN_001903f0(param_2,pcVar9);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      uVar4 = *(uint *)(*(long *)(param_1 + 800) + 4);
      uVar10 = 0xc;
      if (((uVar4 >> 1 & 1) == 0) && (uVar10 = 0x26, (uVar4 & 4) != 0)) {
        uVar10 = 0x16;
      }
      lVar6 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar2 = *(byte *)(lVar6 + 0x28);
      *(undefined2 *)(lVar6 + (ulong)bVar2 * 2) = uVar10;
      *(byte *)(lVar6 + 0x28) = bVar2 + 1;
      bVar2 = *(byte *)(lVar6 + 0x52);
      *(undefined2 *)(lVar6 + (ulong)bVar2 * 2 + 0x2a) = uVar10;
      *(byte *)(lVar6 + 0x52) = bVar2 + 1;
    }
  }
  else if (cVar1 == -0x10) {
    if (*(char *)(param_1 + 0x3b8) == -0xe) {
      FUN_001903f0(param_2,"xacquire|lock|");
    }
    else if (*(char *)(param_1 + 0x3b8) == -0xd) {
      FUN_001903f0(param_2,"xrelease|lock|");
    }
    else {
      FUN_001903f0(param_2,"lock|");
    }
  }
LAB_001e5f98:
  cVar1 = *(char *)(param_1 + 0x331);
joined_r0x001e6100:
  if (cVar1 == '>') {
    uVar5 = FUN_0018ffb0(param_1);
    uVar4 = 0x3b22;
    if (uVar5 - 0x92 < 0x3b23) {
      uVar8 = 0x3b22;
      uVar11 = 0x1e23;
      uVar7 = 0;
      while( true ) {
        uVar8 = uVar8 >> 1;
        if (uVar5 == uVar11) break;
        if (uVar5 < uVar11) {
          uVar4 = uVar8 - 1;
          if (uVar4 < uVar7) goto LAB_001e5fa4;
        }
        else {
          uVar7 = uVar8 + 1;
          if (uVar4 < uVar7) goto LAB_001e5fa4;
        }
        uVar8 = uVar7 + uVar4;
        uVar11 = (uint)*(ushort *)(&DAT_00445c58 + (ulong)(uVar8 >> 1) * 0x50);
      }
      if ((*(short *)(&UNK_00445c5a + ((ulong)uVar8 * 4 + (ulong)uVar8) * 0x10) == 0x3e) ||
         (*(short *)(&UNK_00445c5a + ((ulong)uVar8 * 4 + (ulong)uVar8) * 0x10) == 0xac)) {
        FUN_001903f0(param_2,"notrack|");
      }
    }
  }
LAB_001e5fa4:
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x60) =
         *(undefined4 *)(param_1 + 0x330);
    return 0;
  }
  return 0;
}

