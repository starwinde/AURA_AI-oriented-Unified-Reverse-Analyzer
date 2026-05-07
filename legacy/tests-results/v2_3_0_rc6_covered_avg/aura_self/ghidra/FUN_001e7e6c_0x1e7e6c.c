
uint FUN_001e7e6c(undefined8 *param_1,ushort *param_2,ushort param_3,char param_4)

{
  char cVar1;
  uint uVar2;
  int local_4;
  
  if (((*(byte *)(param_1[2] + 4) & 0xe) == 8) && (*(int *)*param_1 == 0)) {
    if (((param_4 != '\0') && (param_3 == param_2[2])) ||
       ((param_4 == '\0' && (param_3 <= param_2[2])))) {
      return 0x40;
    }
    if (param_3 == *param_2) {
      return 0x10;
    }
  }
  else if (((*(byte *)(param_1[2] + 4) & 0xe) == 10) && (*(int *)*param_1 == 0)) {
    if (param_3 == param_2[2]) {
      return 0x40;
    }
  }
  else {
    uVar2 = FUN_001e7d38(*(undefined4 *)*param_1);
    for (local_4 = 0; local_4 < 3; local_4 = local_4 + 1) {
      cVar1 = (&UNK_00570fe0)[(long)local_4 + (long)(int)((uVar2 & 0xff) >> 5) * 3];
      if (((cVar1 != -1) &&
          (((int)(uint)(*(byte *)(param_1[1] + 7) >> 5) >> ((int)cVar1 & 0x1fU) & 1U) != 0)) &&
         (((param_4 != '\0' && (param_3 == param_2[cVar1])) ||
          ((param_4 == '\0' && (param_3 <= param_2[cVar1])))))) {
        return 0x10 << (ulong)((int)cVar1 & 0x1f) & 0xff;
      }
    }
  }
  return 0;
}

