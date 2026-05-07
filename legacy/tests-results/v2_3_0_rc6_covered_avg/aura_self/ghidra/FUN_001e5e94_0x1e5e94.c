
undefined8
FUN_001e5e94(uint param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4,
            undefined4 *param_5)

{
  long lVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  
  if (param_1 - 0x3fa < 0x35f) {
    uVar6 = 7;
    uVar5 = 0;
    do {
      uVar2 = uVar5 + uVar6;
      uVar4 = uVar2 >> 1;
      uVar7 = (uint)*(ushort *)(&DAT_00409b60 + (ulong)uVar4 * 0x14);
      if (param_1 < uVar7 || param_1 == uVar7) {
        uVar6 = uVar4 - 1;
        if (param_1 == uVar7) {
          lVar1 = ((ulong)uVar4 * 4 + (long)(int)uVar4) * 4;
          uVar3 = *(undefined4 *)(&DAT_00409b64 + lVar1);
          *param_2 = *(undefined4 *)(&DAT_00409b68 + lVar1);
          *param_4 = uVar3;
          if (param_3 != (undefined4 *)0x0) {
            *param_3 = *(undefined4 *)(&DAT_00409b70 + lVar1);
          }
          if (param_5 != (undefined4 *)0x0) {
            *param_5 = *(undefined4 *)(&DAT_00409b6c + (long)(int)uVar4 * 0x14);
          }
          return 1;
        }
        if (uVar2 < 2) {
          return 0;
        }
      }
      else {
        uVar5 = uVar4 + 1;
      }
    } while (uVar5 <= uVar6);
  }
  return 0;
}

