
undefined1 ZydisGetCompDispScaleEvex(long *param_1)

{
  byte bVar1;
  byte bVar2;
  undefined1 uVar3;
  long lVar4;
  
  lVar4 = param_1[2];
  if ((*(byte *)(param_1[1] + 6) & 7) != 4) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("match->definition->encoding == ZYDIS_INSTRUCTION_ENCODING_EVEX",
                  "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x423,
                  "ZydisGetCompDispScaleEvex");
  }
  if ((*(byte *)(lVar4 + 0xd) & 0x7c) == 4) {
    uVar3 = 0;
  }
  else {
    if ((*(byte *)(lVar4 + 0xd) & 0x7c) == 0) {
                    /* WARNING: Subroutine does not return */
      __assert_fail("evex_def->tuple_type != ZYDIS_TUPLETYPE_INVALID",
                    "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x428,
                    "ZydisGetCompDispScaleEvex");
    }
    if ((*(byte *)(lVar4 + 0xe) & 3) == 0 && -1 < *(char *)(lVar4 + 0xd)) {
                    /* WARNING: Subroutine does not return */
      __assert_fail("evex_def->element_size",
                    "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x429,
                    "ZydisGetCompDispScaleEvex");
    }
    bVar2 = ((byte)((ushort)*(undefined2 *)(param_1[1] + 8) >> 8) & 3) - 1;
    if (5 < (byte)((*(byte *)(lVar4 + 0xe) & 3) << 1 | *(byte *)(lVar4 + 0xd) >> 7)) {
                    /* WARNING: Subroutine does not return */
      __assert_fail("evex_def->element_size < (sizeof(size_indexes) / sizeof((size_indexes)[0]))",
                    "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x42f,
                    "ZydisGetCompDispScaleEvex");
    }
    bVar1 = *(byte *)((long)&size_indexes_48 +
                     (long)(int)((*(byte *)(lVar4 + 0xe) & 3) << 1 |
                                (uint)(*(byte *)(lVar4 + 0xd) >> 7)));
    switch(*(ushort *)(lVar4 + 0xc) >> 10 & 0x1f) {
    case 2:
      if (2 < bVar1) {
                    /* WARNING: Subroutine does not return */
        __assert_fail("size_index < 3",
                      "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x43b,
                      "ZydisGetCompDispScaleEvex");
      }
      uVar3 = scales_47[(long)(int)(uint)bVar2 +
                        (long)(int)(uint)(*(int *)(*param_1 + 0x170) != 0) * 9 +
                        (long)(int)(uint)bVar1 * 3];
      break;
    case 3:
      if (2 < bVar1) {
                    /* WARNING: Subroutine does not return */
        __assert_fail("size_index < 3",
                      "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x446,
                      "ZydisGetCompDispScaleEvex");
      }
      uVar3 = scales_46[(long)(int)(uint)bVar2 +
                        (long)(int)(uint)(*(int *)(*param_1 + 0x170) != 0) * 6 +
                        (long)(int)(uint)bVar1 * 3];
      break;
    case 4:
      uVar3 = *(undefined1 *)((long)&scales_45 + (long)(int)(uint)bVar2);
      break;
    case 5:
    case 8:
      if (5 < (byte)((*(byte *)(lVar4 + 0xe) & 3) << 1 | *(byte *)(lVar4 + 0xd) >> 7)) {
                    /* WARNING: Subroutine does not return */
        __assert_fail("evex_def->element_size < (sizeof(scales) / sizeof((scales)[0]))",
                      "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x45d,
                      "ZydisGetCompDispScaleEvex");
      }
      uVar3 = *(undefined1 *)
               ((long)&scales_44 +
               (long)(int)((*(byte *)(lVar4 + 0xe) & 3) << 1 | (uint)(*(byte *)(lVar4 + 0xd) >> 7)))
      ;
      break;
    case 6:
      if (2 < bVar1) {
                    /* WARNING: Subroutine does not return */
        __assert_fail("size_index < 3",
                      "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x468,
                      "ZydisGetCompDispScaleEvex");
      }
      uVar3 = *(undefined1 *)((long)&scales_43 + (long)(int)(uint)bVar1);
      break;
    case 7:
      uVar3 = 4;
      break;
    case 9:
      if ((*(byte *)(param_1[1] + 8) & 4) == 0) {
        uVar3 = 3;
      }
      else {
        uVar3 = 4;
      }
      break;
    case 10:
      if ((*(byte *)(param_1[1] + 8) & 4) == 0) {
        uVar3 = 4;
      }
      else {
        uVar3 = 5;
      }
      break;
    case 0xb:
      uVar3 = 5;
      break;
    case 0xc:
      uVar3 = *(undefined1 *)((long)&scales_42 + (long)(int)(uint)bVar2);
      break;
    case 0xd:
      uVar3 = *(undefined1 *)((long)&scales_41 + (long)(int)(uint)bVar2);
      break;
    case 0xe:
      uVar3 = *(undefined1 *)((long)&scales_40 + (long)(int)(uint)bVar2);
      break;
    case 0xf:
      uVar3 = 4;
      break;
    case 0x10:
      uVar3 = *(undefined1 *)((long)&scales_39 + (long)(int)(uint)bVar2);
      break;
    case 0x11:
      uVar3 = *(undefined1 *)
               ((long)&scales_38 +
               (long)(int)(uint)bVar2 + (long)(int)(uint)(*(int *)(*param_1 + 0x170) != 0) * 3);
      break;
    default:
                    /* WARNING: Subroutine does not return */
      __assert_fail("0","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x4a0,
                    "ZydisGetCompDispScaleEvex");
    }
  }
  return uVar3;
}

