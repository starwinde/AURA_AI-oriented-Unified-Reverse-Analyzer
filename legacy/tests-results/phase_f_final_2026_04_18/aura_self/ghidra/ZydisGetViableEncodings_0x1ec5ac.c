
uint ZydisGetViableEncodings(long param_1)

{
  uint uVar1;
  byte bVar2;
  char cVar3;
  uint uVar4;
  uint local_8;
  
  if (((((*(int *)(param_1 + 0x170) == 0) && (*(int *)(param_1 + 0x174) == 0)) &&
       (*(char *)(param_1 + 0x178) == '\0')) &&
      ((*(char *)(param_1 + 0x179) == '\0' && (*(char *)(param_1 + 0x17a) == '\0')))) &&
     (*(char *)(param_1 + 0x17b) == '\0')) {
    bVar2 = 0;
  }
  else {
    bVar2 = 1;
  }
  if (((*(int *)(param_1 + 0x17c) == 0) && (*(int *)(param_1 + 0x180) == 0)) &&
     ((*(int *)(param_1 + 0x184) == 0 &&
      (((*(int *)(param_1 + 0x188) == 0 && (*(char *)(param_1 + 0x18c) == '\0')) &&
       (*(char *)(param_1 + 0x18d) == '\0')))))) {
    cVar3 = '\0';
  }
  else {
    cVar3 = '\x01';
  }
  if ((bVar2 == 0) || (cVar3 == '\0')) {
    local_8 = *(uint *)(param_1 + 4);
    if (local_8 == 0) {
      local_8 = ~*(uint *)(excluded_encodings_18 + (long)(int)(uint)(byte)(cVar3 << 1 | bVar2) * 4)
                & 0x3f;
    }
    if ((bVar2 != 0) || (cVar3 != '\0')) {
      if (cVar3 == '\0') {
        uVar4 = 0x10;
      }
      else {
        uVar4 = 0x20;
      }
      uVar1 = local_8 & uVar4;
      local_8 = uVar4;
      if (uVar1 == 0) {
        local_8 = 0;
      }
    }
  }
  else {
    local_8 = 0;
  }
  return local_8;
}

