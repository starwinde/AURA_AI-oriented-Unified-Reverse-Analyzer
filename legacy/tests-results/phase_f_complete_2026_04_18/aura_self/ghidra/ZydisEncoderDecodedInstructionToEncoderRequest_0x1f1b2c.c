
undefined8
ZydisEncoderDecodedInstructionToEncoderRequest
          (undefined4 *param_1,long param_2,byte param_3,undefined4 *param_4)

{
  long lVar1;
  undefined4 *puVar2;
  uint uVar3;
  byte bVar4;
  undefined4 uVar5;
  int iVar6;
  undefined1 uVar7;
  byte local_11;
  
  if ((((param_1 == (undefined4 *)0x0) || (param_4 == (undefined4 *)0x0)) ||
      ((param_3 != 0 && (param_2 == 0)))) || (param_3 != *(byte *)((long)param_1 + 0x19))) {
    return 0x80100004;
  }
  memset(param_4,0,400);
  *param_4 = *param_1;
  param_4[2] = param_1[1];
  *(ulong *)(param_4 + 4) = *(ulong *)(param_1 + 8) & 0x7fff8000000;
  if (param_1[0x1d] == 4) {
    uVar5 = 0;
  }
  else {
    uVar5 = param_1[0x1d];
  }
  param_4[6] = uVar5;
  if ((*(ulong *)(param_1 + 8) & 0x4000000) == 0) {
    *(ulong *)(param_4 + 4) = *(ulong *)(param_4 + 4) & 0xfffff81fffffffff;
  }
  bVar4 = *(byte *)((long)param_1 + 0x17);
  if (bVar4 == 0x40) {
    param_4[8] = 3;
  }
  else {
    if (0x40 < bVar4) {
      return 0x80100004;
    }
    if (bVar4 == 0x10) {
      param_4[8] = 1;
    }
    else {
      if (bVar4 != 0x20) {
        return 0x80100004;
      }
      param_4[8] = 2;
    }
  }
  bVar4 = *(byte *)((long)param_1 + 0x16);
  if (bVar4 == 0x40) {
    param_4[9] = 4;
  }
  else {
    if (0x40 < bVar4) {
      return 0x80100004;
    }
    if (bVar4 == 0x20) {
      param_4[9] = 3;
    }
    else {
      if (0x20 < bVar4) {
        return 0x80100004;
      }
      if (bVar4 == 8) {
        param_4[9] = 1;
      }
      else {
        if (bVar4 != 0x10) {
          return 0x80100004;
        }
        param_4[9] = 2;
      }
    }
  }
  uVar3 = param_4[6];
  if (uVar3 != 4) {
    if ((4 < uVar3) || (3 < uVar3)) {
      return 0x80100004;
    }
    if (1 < uVar3) {
      bVar4 = *(byte *)((long)param_1 + 0x16);
      if (bVar4 == 0x40) {
        param_4[7] = 4;
      }
      else {
        if (0x40 < bVar4) {
LAB_001f1dcc:
                    /* WARNING: Subroutine does not return */
          __assert_fail("0","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",
                        0x135a,"ZydisEncoderDecodedInstructionToEncoderRequest");
        }
        if (bVar4 == 0x10) {
          param_4[7] = 2;
        }
        else {
          if (bVar4 != 0x20) goto LAB_001f1dcc;
          param_4[7] = 3;
        }
      }
      goto LAB_001f1dfc;
    }
    if (uVar3 != 0) {
      if (uVar3 != 1) {
        return 0x80100004;
      }
      param_4[7] = 1;
      goto LAB_001f1dfc;
    }
  }
  param_4[7] = 0;
LAB_001f1dfc:
  uVar3 = param_1[3];
  if (uVar3 != 6) {
    if (6 < uVar3) {
      return 0x80100004;
    }
    if (uVar3 == 5) {
      if (*(char *)(param_1 + 0x11) == '\0') {
        uVar5 = param_1[0x12];
      }
      else {
        uVar5 = 0;
      }
      param_4[0x5f] = uVar5;
      param_4[0x60] = param_1[0x15];
      param_4[0x61] = param_1[0x13];
      param_4[0x62] = param_1[0x14];
      *(undefined1 *)(param_4 + 99) = *(undefined1 *)(param_1 + 0x16);
      *(undefined1 *)((long)param_4 + 0x18d) = *(undefined1 *)((long)param_1 + 0x59);
    }
    else {
      if (5 < uVar3) {
        return 0x80100004;
      }
      if (3 < uVar3) {
        if (uVar3 != 4) {
          return 0x80100004;
        }
        if (*(char *)(param_1 + 0x11) == '\0') {
          uVar5 = param_1[0x12];
        }
        else {
          uVar5 = 0;
        }
        param_4[0x5c] = uVar5;
        param_4[0x5d] = param_1[0x13];
        *(undefined1 *)(param_4 + 0x5e) = *(undefined1 *)(param_1 + 0x16);
        if (((param_1[0xf] == 3) || (param_1[0xf] == 5)) &&
           (*(char *)((long)param_1 + 0x10b) != '\0')) {
          uVar7 = 1;
        }
        else {
          uVar7 = 0;
        }
        *(undefined1 *)((long)param_4 + 0x179) = uVar7;
        *(undefined1 *)((long)param_4 + 0x17a) = *(undefined1 *)((long)param_1 + 0x5d);
        if (param_1[0x18] != 0) {
          *(undefined1 *)((long)param_4 + 0x17b) = *(undefined1 *)(param_1 + 0x19);
        }
      }
    }
  }
  if (param_1[3] == 6) {
    iVar6 = 1;
  }
  else {
    iVar6 = 1 << (ulong)(param_1[3] & 0x1f);
  }
  param_4[1] = iVar6;
  *(byte *)(param_4 + 10) = param_3;
  local_11 = 0;
  do {
    if (param_3 <= local_11) {
      return 0x100000;
    }
    lVar1 = param_2 + (ulong)local_11 * 0x50;
    puVar2 = param_4 + (long)(int)(uint)local_11 * 0x10 + 0xc;
    *puVar2 = *(undefined4 *)(lVar1 + 0x20);
    uVar3 = *(uint *)(lVar1 + 0x20);
    if (uVar3 == 4) {
      *(undefined8 *)(puVar2 + 0xe) = *(undefined8 *)(lVar1 + 0x30);
      if ((*(char *)(lVar1 + 0x2a) != '\0') && (param_1[1] != 0x73e)) {
        bVar4 = *(byte *)(param_1 + 0x50);
        if (bVar4 == 0x20) {
          param_4[7] = 3;
        }
        else {
          if (0x20 < bVar4) {
            return 0x80100004;
          }
          if (bVar4 == 8) {
            param_4[7] = 1;
          }
          else {
            if (bVar4 != 0x10) {
              return 0x80100004;
            }
            param_4[7] = 2;
          }
        }
      }
    }
    else {
      if (4 < uVar3) {
        return 0x80100004;
      }
      if (uVar3 == 3) {
        *(undefined2 *)(puVar2 + 0xc) = *(undefined2 *)(lVar1 + 0x28);
        puVar2[0xd] = *(undefined4 *)(lVar1 + 0x2c);
      }
      else {
        if (3 < uVar3) {
          return 0x80100004;
        }
        if (uVar3 == 1) {
          puVar2[1] = *(undefined4 *)(lVar1 + 0x28);
          *(bool *)(puVar2 + 2) = *(int *)(lVar1 + 0xc) == 5;
        }
        else {
          if (uVar3 != 2) {
            return 0x80100004;
          }
          puVar2[4] = *(undefined4 *)(lVar1 + 0x30);
          puVar2[5] = *(undefined4 *)(lVar1 + 0x34);
          if (*(int *)(lVar1 + 0x28) == 3) {
            uVar7 = 0;
          }
          else {
            uVar7 = *(undefined1 *)(lVar1 + 0x38);
          }
          *(undefined1 *)(puVar2 + 6) = uVar7;
          if (*(char *)(lVar1 + 0x49) != '\0') {
            *(undefined8 *)(puVar2 + 8) = *(undefined8 *)(lVar1 + 0x40);
          }
          *(ushort *)(puVar2 + 10) = *(ushort *)(lVar1 + 0x10) >> 3;
        }
      }
    }
    local_11 = local_11 + 1;
  } while( true );
}

