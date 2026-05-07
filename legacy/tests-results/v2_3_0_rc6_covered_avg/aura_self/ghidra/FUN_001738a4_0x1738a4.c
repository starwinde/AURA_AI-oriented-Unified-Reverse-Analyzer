
undefined8
FUN_001738a4(long param_1,ulong param_2,long param_3,uint param_4,uint param_5,char param_6,
            int param_7,undefined8 *param_8)

{
  long lVar1;
  uint uVar2;
  uint uVar3;
  ulong uVar4;
  uint uVar5;
  ulong uVar6;
  undefined1 auVar7 [16];
  undefined8 uVar8;
  
  uVar6 = param_3 + (ulong)(param_4 & 0xffff) * (ulong)(param_5 & 0xffff);
  if (param_6 == '\x02') {
    if (param_2 <= uVar6) {
      return 0;
    }
    if (param_2 - uVar6 < 0x40) {
      return 0;
    }
    lVar1 = param_1 + uVar6;
    uVar8 = *(undefined8 *)(param_1 + uVar6);
    uVar6 = *(ulong *)(lVar1 + 0x10);
    auVar7 = *(undefined1 (*) [16])(lVar1 + 0x18);
    uVar3 = *(uint *)(lVar1 + 0x28);
    uVar4 = *(ulong *)(lVar1 + 0x38);
    if (param_7 != 0) {
      uVar8 = NEON_rev32(uVar8,1);
      uVar6 = (uVar6 & 0xff00ff00ff00ff00) >> 8 | (uVar6 & 0xff00ff00ff00ff) << 8;
      uVar6 = (uVar6 & 0xffff0000ffff0000) >> 0x10 | (uVar6 & 0xffff0000ffff) << 0x10;
      uVar6 = uVar6 >> 0x20 | uVar6 << 0x20;
      auVar7 = NEON_rev64(auVar7,1);
      uVar3 = (uVar3 & 0xff00ff00) >> 8 | (uVar3 & 0xff00ff) << 8;
      uVar3 = uVar3 >> 0x10 | uVar3 << 0x10;
      uVar4 = (uVar4 & 0xff00ff00ff00ff00) >> 8 | (uVar4 & 0xff00ff00ff00ff) << 8;
      uVar4 = (uVar4 & 0xffff0000ffff0000) >> 0x10 | (uVar4 & 0xffff0000ffff) << 0x10;
      uVar4 = uVar4 >> 0x20 | uVar4 << 0x20;
    }
    *param_8 = uVar8;
    param_8[2] = auVar7._8_8_;
    param_8[1] = auVar7._0_8_;
    *(uint *)(param_8 + 3) = uVar3;
    param_8[4] = uVar4;
    param_8[5] = uVar6;
  }
  else {
    if ((param_2 <= uVar6) || (param_2 - uVar6 < 0x28)) {
      return 0;
    }
    lVar1 = param_1 + uVar6;
    uVar8 = *(undefined8 *)(param_1 + uVar6);
    uVar6 = *(ulong *)(lVar1 + 0x10);
    uVar3 = *(uint *)(lVar1 + 0xc);
    uVar5 = *(uint *)(lVar1 + 0x18);
    uVar2 = *(uint *)(lVar1 + 0x24);
    if (param_7 != 0) {
      uVar6 = NEON_rev32(uVar6,1);
      uVar8 = NEON_rev32(uVar8,1);
      uVar3 = (uVar3 & 0xff00ff00) >> 8 | (uVar3 & 0xff00ff) << 8;
      uVar3 = uVar3 >> 0x10 | uVar3 << 0x10;
      uVar5 = (uVar5 & 0xff00ff00) >> 8 | (uVar5 & 0xff00ff) << 8;
      uVar5 = uVar5 >> 0x10 | uVar5 << 0x10;
      uVar2 = (uVar2 & 0xff00ff00) >> 8 | (uVar2 & 0xff00ff) << 8;
      uVar2 = uVar2 >> 0x10 | uVar2 << 0x10;
    }
    *(uint *)(param_8 + 3) = uVar5;
    param_8[4] = (ulong)uVar2;
    param_8[5] = (ulong)uVar3;
    *param_8 = uVar8;
    param_8[2] = uVar6 >> 0x20;
    param_8[1] = uVar6 & 0xffffffff;
  }
  return 1;
}

