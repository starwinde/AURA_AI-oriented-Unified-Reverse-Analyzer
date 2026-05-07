
long elf_sym_name_at_isra_0
               (long param_1,ulong param_2,long param_3,long param_4,ulong param_5,ulong param_6,
               char param_7,int param_8)

{
  uint uVar1;
  long lVar2;
  uint uVar3;
  ulong uVar4;
  ulong uVar5;
  
  uVar5 = 0x10;
  if (param_7 == '\x02') {
    uVar5 = 0x18;
  }
  uVar4 = param_3 + (param_6 & 0xffffffff) * uVar5;
  if ((uVar4 < param_2) && (uVar5 <= param_2 - uVar4)) {
    if (param_7 == '\x02') {
      uVar1 = *(uint *)(param_1 + uVar4);
      uVar3 = (uVar1 & 0xff00ff00) >> 8 | (uVar1 & 0xff00ff) << 8;
      uVar3 = uVar3 >> 0x10 | uVar3 << 0x10;
      if (param_8 == 0) {
        uVar3 = uVar1;
      }
    }
    else {
      uVar3 = (uint)*(undefined8 *)(param_1 + uVar4);
      uVar1 = (uVar3 & 0xff00ff00) >> 8 | (uVar3 & 0xff00ff) << 8;
      if (param_8 != 0) {
        uVar3 = uVar1 >> 0x10 | uVar1 << 0x10;
      }
    }
    if (((param_4 != 0 && param_5 != 0) && (uVar5 = (ulong)uVar3, uVar5 < param_5)) &&
       (param_4 + uVar5 < param_2)) {
      param_1 = param_1 + param_4 + uVar5;
      lVar2 = 0;
      do {
        if (*(char *)(param_1 + lVar2) == '\0') {
          if (lVar2 != 0) {
            return param_1;
          }
          return 0;
        }
        lVar2 = lVar2 + 1;
      } while (param_5 - uVar5 != lVar2);
      return param_1;
    }
  }
  return 0;
}

