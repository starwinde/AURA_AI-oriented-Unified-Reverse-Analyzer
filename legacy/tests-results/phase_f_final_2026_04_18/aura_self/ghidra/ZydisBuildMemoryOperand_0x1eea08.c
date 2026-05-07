
/* WARNING: Removing unreachable block (ram,0x001eee18) */

void ZydisBuildMemoryOperand(undefined8 *param_1,long param_2,ulong *param_3)

{
  byte bVar1;
  char cVar2;
  byte bVar3;
  
  *param_3 = *param_3 | 1;
  param_3[5] = *(ulong *)(param_2 + 0x20);
  if (*(char *)((long)param_1 + 0x29) == '\x10') {
    cVar2 = ZydisGetRm16(*(undefined4 *)(param_2 + 0x10),*(undefined4 *)(param_2 + 0x14));
    if (cVar2 == -1) {
      *(undefined1 *)((long)param_3 + 0x17) = 6;
      *(undefined1 *)((long)param_3 + 0x21) = 0x10;
      return;
    }
    *(char *)((long)param_3 + 0x17) = cVar2;
    *(undefined1 *)((long)param_3 + 0x21) = *(undefined1 *)((long)param_1 + 0x2a);
    bVar1 = *(byte *)((long)param_3 + 0x21);
    if (bVar1 == 0x10) {
      *(undefined1 *)((long)param_3 + 0x15) = 2;
      return;
    }
    if (bVar1 < 0x11) {
      if (bVar1 == 0) {
        if (cVar2 != '\x06') {
          return;
        }
        *(undefined1 *)((long)param_3 + 0x21) = 8;
        *(undefined1 *)((long)param_3 + 0x15) = 1;
        return;
      }
      if (bVar1 == 8) {
        *(undefined1 *)((long)param_3 + 0x15) = 1;
        return;
      }
    }
                    /* WARNING: Subroutine does not return */
    __assert_fail("0","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0xfb2,
                  "ZydisBuildMemoryOperand");
  }
  if (*(int *)(param_2 + 0x14) == 0) {
    if (*(int *)(param_2 + 0x10) == 0) {
      if (*(int *)*param_1 == 0) {
        *(undefined1 *)((long)param_3 + 0x17) = 4;
        *param_3 = *param_3 | 2;
        *(undefined1 *)((long)param_3 + 0x1a) = 5;
        *(undefined1 *)((long)param_3 + 0x19) = 4;
      }
      else {
        *(undefined1 *)((long)param_3 + 0x17) = 5;
      }
      *(undefined1 *)((long)param_3 + 0x21) = 0x20;
      return;
    }
    if ((*(int *)(param_2 + 0x10) == 0x105) || (*(int *)(param_2 + 0x10) == 0x104)) {
      *(undefined1 *)((long)param_3 + 0x17) = 5;
      *(undefined1 *)((long)param_3 + 0x21) = 0x20;
      return;
    }
  }
  bVar3 = ZydisRegisterGetId(*(undefined4 *)(param_2 + 0x10));
  cVar2 = ZydisRegisterGetId(*(undefined4 *)(param_2 + 0x14));
  *(undefined1 *)((long)param_3 + 0x21) = *(undefined1 *)((long)param_1 + 0x2a);
  bVar1 = *(byte *)((long)param_3 + 0x21);
  if (bVar1 == 0x20) {
LAB_001eece0:
    *(undefined1 *)((long)param_3 + 0x15) = 2;
  }
  else {
    if (0x20 < bVar1) {
LAB_001eecf0:
                    /* WARNING: Subroutine does not return */
      __assert_fail("0","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0xfef,
                    "ZydisBuildMemoryOperand");
    }
    if (bVar1 == 0x10) {
      *(undefined1 *)((long)param_3 + 0x21) = 0x20;
      goto LAB_001eece0;
    }
    if (0x10 < bVar1) goto LAB_001eecf0;
    if (bVar1 == 0) {
      if ((bVar3 & 7) == 5) {
        *(undefined1 *)((long)param_3 + 0x21) = 8;
        param_3[5] = 0;
        *(undefined1 *)((long)param_3 + 0x15) = 1;
      }
    }
    else {
      if (bVar1 != 8) goto LAB_001eecf0;
      *(undefined1 *)((long)param_3 + 0x15) = 1;
    }
  }
  if (((*(int *)(param_2 + 0x14) == 0) && ((bVar3 & 7) != 4)) &&
     ((*(byte *)(param_1[1] + 5) & 7) != 4)) {
    *(byte *)((long)param_3 + 0x17) = bVar3;
  }
  else {
    *(undefined1 *)((long)param_3 + 0x17) = 4;
    *param_3 = *param_3 | 2;
    if (bVar3 == 0xff) {
      *(undefined1 *)((long)param_3 + 0x1a) = 5;
      *(undefined1 *)((long)param_3 + 0x15) = 0;
      *(undefined1 *)((long)param_3 + 0x21) = 0x20;
    }
    else {
      *(byte *)((long)param_3 + 0x1a) = bVar3;
    }
    if (cVar2 == -1) {
      *(undefined1 *)((long)param_3 + 0x19) = 4;
    }
    else {
      *(char *)((long)param_3 + 0x19) = cVar2;
    }
    bVar1 = *(byte *)(param_2 + 0x18);
    if (bVar1 == 8) {
      *(undefined1 *)(param_3 + 3) = 3;
    }
    else {
      if (8 < bVar1) {
LAB_001eee54:
                    /* WARNING: Subroutine does not return */
        __assert_fail("0","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x101b,
                      "ZydisBuildMemoryOperand");
      }
      if (bVar1 == 4) {
        *(undefined1 *)(param_3 + 3) = 2;
      }
      else {
        if (4 < bVar1) goto LAB_001eee54;
        if (1 < bVar1) {
          if (bVar1 != 2) goto LAB_001eee54;
          *(undefined1 *)(param_3 + 3) = 1;
        }
      }
    }
  }
  return;
}

