
undefined8 ZydisAreEvexFeaturesCompatible(long param_1,long param_2)

{
  byte bVar1;
  byte bVar2;
  char cVar3;
  undefined8 uVar4;
  undefined1 auStack_24 [4];
  long local_20;
  long local_18;
  
  local_18 = *(long *)PTR___stack_chk_guard_005ffe88;
  if ((*(byte *)(*(long *)(param_1 + 8) + 6) & 7) == 4) {
    local_20 = *(long *)(param_1 + 0x10);
    cVar3 = ZydisGetCcInfo(*(undefined4 *)(param_2 + 8),auStack_24);
    if (((cVar3 == '\0') &&
        ((uint)*(byte *)(param_2 + 0x17a) !=
         ((uint)((ulong)*(undefined8 *)(local_20 + 8) >> 0x3e) & 1))) ||
       ((cVar3 != '\0' && (*(char *)(param_2 + 0x17a) != '\0')))) {
      uVar4 = 0;
    }
    else if ((((*(byte *)(local_20 + 0xe) & 0x40) == 0) &&
             (((uint)((ulong)*(undefined8 *)(local_20 + 8) >> 0x37) & 3) != 1)) &&
            (*(char *)(param_2 + 0x179) != '\0')) {
      uVar4 = 0;
    }
    else {
      bVar1 = *(byte *)(local_20 + 0xe) >> 2;
      bVar2 = bVar1 & 3;
      if (bVar2 == 3) {
        if ((*(int *)(param_2 + 0x170) != 0) || (*(int *)(param_2 + 0x174) != 0)) {
          uVar4 = 0;
          goto LAB_001eba24;
        }
      }
      else {
        if (3 < bVar2) {
LAB_001eb9e4:
                    /* WARNING: Subroutine does not return */
          __assert_fail("0","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x9b6
                        ,"ZydisAreEvexFeaturesCompatible");
        }
        if (bVar2 == 2) {
          if (*(int *)(param_2 + 0x170) != 0) {
            uVar4 = 0;
            goto LAB_001eba24;
          }
          if (*(int *)(param_2 + 0x174) == 0) {
            if (*(char *)(param_2 + 0x178) != '\0') {
              uVar4 = 0;
              goto LAB_001eba24;
            }
          }
          else if (*(char *)(param_2 + 0x178) == '\0') {
            uVar4 = 0;
            goto LAB_001eba24;
          }
        }
        else {
          if (2 < bVar2) goto LAB_001eb9e4;
          if ((bVar1 & 3) == 0) {
            if (((*(char *)(param_2 + 0x178) != '\0') || (*(int *)(param_2 + 0x170) != 0)) ||
               (*(int *)(param_2 + 0x174) != 0)) {
              uVar4 = 0;
              goto LAB_001eba24;
            }
          }
          else {
            if (bVar2 != 1) goto LAB_001eb9e4;
            if ((*(char *)(param_2 + 0x178) != '\0') || (*(int *)(param_2 + 0x174) != 0)) {
              uVar4 = 0;
              goto LAB_001eba24;
            }
            cVar3 = ZydisIsBroadcastModeCompatible
                              (local_20,*(ushort *)(*(long *)(param_1 + 8) + 8) >> 8 & 3,
                               *(undefined4 *)(param_2 + 0x170));
            if (cVar3 == '\0') {
              uVar4 = 0;
              goto LAB_001eba24;
            }
          }
        }
      }
      uVar4 = 1;
    }
  }
  else {
    uVar4 = 1;
  }
LAB_001eba24:
  if (local_18 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return uVar4;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,uVar4,0,
                   local_18 - *(long *)PTR___stack_chk_guard_005ffe88);
}

