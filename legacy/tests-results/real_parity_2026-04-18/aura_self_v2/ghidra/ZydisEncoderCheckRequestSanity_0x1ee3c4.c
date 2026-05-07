
undefined8 ZydisEncoderCheckRequestSanity(uint *param_1)

{
  uint *puVar1;
  uint uVar2;
  char cVar3;
  undefined8 uVar4;
  char local_b;
  byte local_a;
  byte local_9;
  
  if (((((((*param_1 < 6) && (param_1[1] < 0x40)) && (param_1[2] < 0x75e)) &&
        ((param_1[6] < 5 && (param_1[7] < 5)))) && (param_1[8] < 4)) &&
      ((((param_1[9] < 5 && (param_1[0x5c] < 0xd)) &&
        ((param_1[0x5d] < 5 &&
         (((param_1[0x5f] < 0xd && (param_1[0x60] < 6)) && (param_1[0x61] < 5)))))) &&
       ((param_1[0x62] < 9 && ((byte)param_1[10] < 6)))))) &&
     ((param_1[2] != 0 &&
      (((*(ulong *)(param_1 + 4) & 0xfffff80007ffffff) == 0 &&
       (*(byte *)((long)param_1 + 0x17b) < 0x10)))))) {
    if ((param_1[1] & mutually_exclusive_encodings_7) == mutually_exclusive_encodings_7) {
      uVar4 = 0x80100004;
    }
    else {
      if ((*(ulong *)(param_1 + 4) & 0x7e000000000) != 0) {
        if ((*param_1 == 0) && ((*(ulong *)(param_1 + 4) & 0x1e000000000) != 0)) {
          return 0x80100004;
        }
        local_b = (*(ulong *)(param_1 + 4) & 0x2000000000) != 0;
        if ((*(ulong *)(param_1 + 4) & 0x4000000000) != 0) {
          local_b = local_b + '\x01';
        }
        if ((*(ulong *)(param_1 + 4) & 0x8000000000) != 0) {
          local_b = local_b + '\x01';
        }
        if ((*(ulong *)(param_1 + 4) & 0x10000000000) != 0) {
          local_b = local_b + '\x01';
        }
        if ((*(ulong *)(param_1 + 4) & 0x20000000000) != 0) {
          local_b = local_b + '\x01';
        }
        if ((*(ulong *)(param_1 + 4) & 0x40000000000) != 0) {
          local_b = local_b + '\x01';
        }
        if (local_b != '\x01') {
          return 0x80100004;
        }
      }
      local_a = (*(ulong *)(param_1 + 4) & 0x10000000) != 0;
      if ((*(ulong *)(param_1 + 4) & 0x20000000) != 0) {
        local_a = local_a + 1;
      }
      if ((*(ulong *)(param_1 + 4) & 0x40000000) != 0) {
        local_a = local_a + 1;
      }
      if (local_a < 2) {
        if (((*(ulong *)(param_1 + 4) & 0x100000000) == 0) ||
           ((*(ulong *)(param_1 + 4) & 0x200000000) == 0)) {
          if (((*(ulong *)(param_1 + 4) & 0x400000000) == 0) ||
             ((*(ulong *)(param_1 + 4) & 0x800000000) == 0)) {
            if (((*(ulong *)(param_1 + 4) & 0x1000000000) == 0) ||
               ((*(ulong *)(param_1 + 4) & 0x7e000000000) == 0)) {
              if (branch_lookup_6[(ulong)param_1[6] + (ulong)param_1[7] * 5] == '\0') {
                uVar4 = 0x80100004;
              }
              else {
                if (*param_1 == 0) {
                  if (param_1[8] == 1) {
                    return 0x80100004;
                  }
                }
                else if (((param_1[7] == 4) || (param_1[8] == 3)) || (param_1[9] == 4)) {
                  return 0x80100004;
                }
                for (local_9 = 0; local_9 < (byte)param_1[10]; local_9 = local_9 + 1) {
                  puVar1 = param_1 + (long)(int)(uint)local_9 * 0x10 + 0xc;
                  if ((*puVar1 == 0) || (4 < *puVar1)) {
                    return 0x80100004;
                  }
                  uVar2 = *puVar1;
                  if (4 < uVar2) {
                    return 0x80100004;
                  }
                  if (uVar2 < 3) {
                    if (uVar2 == 1) {
                      if (0x14a < puVar1[1]) {
                        return 0x80100004;
                      }
                    }
                    else {
                      if (uVar2 != 2) {
                        return 0x80100004;
                      }
                      if (((0x14a < puVar1[4]) || (0x14a < puVar1[5])) ||
                         (cVar3 = ZydisIsScaleValid((char)puVar1[6]), cVar3 == '\0')) {
                        return 0x80100004;
                      }
                    }
                  }
                }
                uVar4 = 0x100000;
              }
            }
            else {
              uVar4 = 0x80100004;
            }
          }
          else {
            uVar4 = 0x80100004;
          }
        }
        else {
          uVar4 = 0x80100004;
        }
      }
      else {
        uVar4 = 0x80100004;
      }
    }
  }
  else {
    uVar4 = 0x80100004;
  }
  return uVar4;
}

