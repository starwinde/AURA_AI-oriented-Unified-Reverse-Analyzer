
undefined8
parse_shdr(long param_1,ulong param_2,long param_3,uint param_4,uint param_5,char param_6,
          int param_7,undefined8 *param_8)

{
  long lVar1;
  uint uVar2;
  ulong uVar3;
  ulong uVar6;
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  undefined8 uVar7;
  
  uVar3 = param_3 + (ulong)(param_4 & 0xffff) * (ulong)(param_5 & 0xffff);
  if (param_6 == '\x02') {
    if (param_2 <= uVar3) {
      return 0;
    }
    if (param_2 - uVar3 < 0x40) {
      return 0;
    }
    lVar1 = param_1 + uVar3;
    uVar7 = *(undefined8 *)(param_1 + uVar3);
    auVar5 = *(undefined1 (*) [16])(lVar1 + 8);
    auVar4 = *(undefined1 (*) [16])(lVar1 + 0x18);
    uVar2 = *(uint *)(lVar1 + 0x28);
    if (param_7 != 0) {
      uVar7 = NEON_rev32(uVar7,1);
      uVar2 = (uVar2 & 0xff00ff00) >> 8 | (uVar2 & 0xff00ff) << 8;
      uVar2 = uVar2 >> 0x10 | uVar2 << 0x10;
      auVar5 = NEON_rev64(auVar5,1);
      auVar4 = NEON_rev64(auVar4,1);
    }
    *param_8 = uVar7;
    param_8[2] = auVar5._8_8_;
    param_8[1] = auVar5._0_8_;
    param_8[4] = auVar4._8_8_;
    param_8[3] = auVar4._0_8_;
    *(uint *)(param_8 + 5) = uVar2;
  }
  else {
    if ((param_2 <= uVar3) || (param_2 - uVar3 < 0x28)) {
      return 0;
    }
    uVar7 = *(undefined8 *)(param_1 + uVar3);
    auVar5 = *(undefined1 (*) [16])(param_1 + uVar3 + 8);
    uVar2 = *(uint *)(param_1 + uVar3 + 0x18);
    if (param_7 == 0) {
      uVar3 = auVar5._0_8_;
      uVar6 = auVar5._8_8_;
    }
    else {
      auVar5 = NEON_rev32(auVar5,1);
      uVar2 = (uVar2 & 0xff00ff00) >> 8 | (uVar2 & 0xff00ff) << 8;
      uVar2 = uVar2 >> 0x10 | uVar2 << 0x10;
      uVar7 = NEON_rev32(uVar7,1);
      uVar3 = auVar5._0_8_;
      uVar6 = auVar5._8_8_;
    }
    *(uint *)(param_8 + 5) = uVar2;
    *param_8 = uVar7;
    param_8[2] = uVar3 >> 0x20;
    param_8[1] = uVar3 & 0xffffffff;
    param_8[4] = uVar6 >> 0x20;
    param_8[3] = uVar6 & 0xffffffff;
  }
  return 1;
}

