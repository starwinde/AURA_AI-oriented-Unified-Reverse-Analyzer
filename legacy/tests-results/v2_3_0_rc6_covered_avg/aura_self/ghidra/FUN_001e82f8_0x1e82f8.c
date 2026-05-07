
byte FUN_001e82f8(long *param_1,ulong param_2,long param_3)

{
  uint uVar1;
  char cVar2;
  byte bVar3;
  byte bVar4;
  byte *pbVar5;
  byte local_14;
  byte local_13;
  
  pbVar5 = (byte *)FUN_001f2f18(param_3);
  local_14 = 0;
  cVar2 = FUN_001e825c(*pbVar5 & 0x3f);
  if (cVar2 == '\0') {
    local_13 = FUN_001e8204(param_2);
  }
  else {
    local_13 = FUN_001e8184(param_2);
  }
  switch(*pbVar5 & 0x3f) {
  case 5:
    if ((byte)((*(byte *)(param_3 + 2) & 1) << 4 | *(byte *)(param_3 + 1) >> 4) != 0xd) {
                    /* WARNING: Subroutine does not return */
      __assert_fail("def_op->element_type == ZYDIS_IELEMENT_TYPE_UINT8",
                    "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x23b,
                    "ZydisGetEffectiveImmSize");
    }
    if (param_2 < 0x10) {
      local_14 = 8;
    }
    else {
      local_14 = 0;
    }
    break;
  default:
                    /* WARNING: Subroutine does not return */
    __assert_fail("0","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x29e,
                  "ZydisGetEffectiveImmSize");
  case 0xb:
    if (*(char *)((long)param_1 + 0x29) != '\0') {
                    /* WARNING: Subroutine does not return */
      __assert_fail("match->easz == 0",
                    "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x25e,
                    "ZydisGetEffectiveImmSize");
    }
    bVar4 = FUN_001e7e28(*param_1);
    if ((local_13 < bVar4) &&
       (bVar3 = FUN_001e8204(~((-1L << ((ulong)(bVar4 - 1) & 0x3f)) << 1) & param_2),
       local_13 < bVar3)) {
      local_13 = bVar4;
    }
    if (*(int *)*param_1 == 0) {
      if (local_13 < 0x20) {
        local_13 = 0x20;
      }
      local_14 = local_13;
      *(byte *)((long)param_1 + 0x29) = local_13;
    }
    else {
      if (local_13 < 0x10) {
        local_13 = 0x10;
      }
      if ((local_13 == 0x10) || (local_13 == 0x20)) {
        local_14 = local_13;
        *(byte *)((long)param_1 + 0x29) = local_13;
      }
    }
    break;
  case 0xe:
  case 0x15:
    local_14 = 8;
    break;
  case 0xf:
  case 0x16:
    local_14 = 0x10;
    break;
  case 0x10:
  case 0x17:
    local_14 = 0x20;
    break;
  case 0x11:
  case 0x18:
    local_14 = 0x40;
    break;
  case 0x12:
  case 0x19:
    bVar4 = FUN_001e8098(param_1,&DAT_00571028,local_13);
    return bVar4;
  case 0x13:
  case 0x1a:
    bVar4 = FUN_001e8098(param_1,&DAT_00571030,local_13);
    return bVar4;
  case 0x14:
  case 0x1b:
    bVar4 = FUN_001e8098(param_1,&DAT_00571038,local_13);
    return bVar4;
  case 0x1c:
  case 0x1d:
  case 0x1e:
  case 0x1f:
    bVar4 = (*pbVar5 & 0x3f) - 0x1c;
    if ((*(int *)(*param_1 + 0x1c) != 0) && (*(int *)(*param_1 + 0x1c) != bVar4 + 1)) {
      return 0;
    }
    local_14 = (byte)(8 << (ulong)(bVar4 & 0x1f));
    break;
  case 0x22:
    uVar1 = *(uint *)(*param_1 + 0x1c);
    if (uVar1 == 4) {
      return 0;
    }
    if (uVar1 < 5) {
      if (uVar1 == 3) {
        local_14 = 0x20;
        break;
      }
      if (uVar1 < 4) {
        if (uVar1 == 2) {
          local_14 = 0x10;
          break;
        }
        if (uVar1 < 3) {
          if (uVar1 == 0) {
            bVar4 = FUN_001e8098(param_1,&DAT_00571040,local_13);
            return bVar4;
          }
          if (uVar1 == 1) {
            return 0;
          }
        }
      }
    }
                    /* WARNING: Subroutine does not return */
    __assert_fail("0","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x29a,
                  "ZydisGetEffectiveImmSize");
  }
  if (local_14 < local_13) {
    local_14 = 0;
  }
  return local_14;
}

