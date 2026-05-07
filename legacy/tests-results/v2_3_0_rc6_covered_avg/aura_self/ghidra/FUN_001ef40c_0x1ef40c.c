
int FUN_001ef40c(ulong *param_1,undefined8 param_2)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = FUN_001ee2dc(param_1,param_2);
  if (iVar2 < 0) {
    return iVar2;
  }
  uVar1 = (uint)param_1[1];
  if (uVar1 == 5) {
    iVar2 = FUN_001ef270(param_1,param_2);
  }
  else {
    if (5 < uVar1) {
LAB_001ef540:
                    /* WARNING: Subroutine does not return */
      __assert_fail("0","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0xf13,
                    "ZydisEmitInstruction");
    }
    if (uVar1 == 4) {
      iVar2 = FUN_001ef038(param_1,param_2);
    }
    else {
      if (4 < uVar1) goto LAB_001ef540;
      if (uVar1 == 3) {
        iVar2 = FUN_001eebec(param_1,param_2);
      }
      else {
        if (3 < uVar1) goto LAB_001ef540;
        if (uVar1 < 2) {
          iVar2 = FUN_001ee7f8(param_1,param_2);
        }
        else {
          if (uVar1 != 2) goto LAB_001ef540;
          iVar2 = FUN_001eea38(param_1,param_2);
        }
      }
    }
  }
  if (iVar2 < 0) {
    return iVar2;
  }
  uVar1 = *(uint *)((long)param_1 + 0xc);
  if (uVar1 == 8) {
    iVar2 = FUN_001ee2b4(0xf,param_2);
    if (iVar2 < 0) {
      return iVar2;
    }
    iVar2 = FUN_001ee2b4(0xf,param_2);
  }
  else {
    if (8 < uVar1) {
LAB_001ef6c8:
                    /* WARNING: Subroutine does not return */
      __assert_fail("0","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0xf2a,
                    "ZydisEmitInstruction");
    }
    if (uVar1 == 3) {
      iVar2 = FUN_001ee2b4(0xf,param_2);
      if (iVar2 < 0) {
        return iVar2;
      }
      iVar2 = FUN_001ee2b4(0x3a,param_2);
    }
    else {
      if (3 < uVar1) goto LAB_001ef6c8;
      if (uVar1 == 2) {
        iVar2 = FUN_001ee2b4(0xf,param_2);
        if (iVar2 < 0) {
          return iVar2;
        }
        iVar2 = FUN_001ee2b4(0x38,param_2);
      }
      else {
        if (2 < uVar1) goto LAB_001ef6c8;
        if (uVar1 == 0) goto LAB_001ef70c;
        if (uVar1 != 1) goto LAB_001ef6c8;
        iVar2 = FUN_001ee2b4(0xf,param_2);
      }
    }
  }
  if (iVar2 < 0) {
    return iVar2;
  }
LAB_001ef70c:
  if (((((int)param_1[1] == 1) || (iVar2 = FUN_001ee2b4((char)param_1[2],param_2), -1 < iVar2)) &&
      (((*param_1 & 1) == 0 ||
       (iVar2 = FUN_001ee2b4(*(char *)((long)param_1 + 0x15) << 6 |
                             (*(byte *)((long)param_1 + 0x16) & 7) << 3 |
                             *(byte *)((long)param_1 + 0x17) & 7,param_2), -1 < iVar2)))) &&
     (((((*param_1 & 2) == 0 ||
        (iVar2 = FUN_001ee2b4((char)param_1[3] << 6 | (*(byte *)((long)param_1 + 0x19) & 7) << 3 |
                              *(byte *)((long)param_1 + 0x1a) & 7,param_2), -1 < iVar2)) &&
       ((*(char *)((long)param_1 + 0x21) == '\0' ||
        (iVar2 = FUN_001ee134(param_1[5],*(byte *)((long)param_1 + 0x21) >> 3,param_2), -1 < iVar2))
       )) && (((*(char *)((long)param_1 + 0x22) == '\0' ||
               (iVar2 = FUN_001ee134(param_1[6],*(byte *)((long)param_1 + 0x22) >> 3,param_2),
               -1 < iVar2)) &&
              (((int)param_1[1] != 1 || (iVar2 = FUN_001ee2b4((char)param_1[2],param_2), -1 < iVar2)
               ))))))) {
    iVar2 = 0x100000;
  }
  return iVar2;
}

