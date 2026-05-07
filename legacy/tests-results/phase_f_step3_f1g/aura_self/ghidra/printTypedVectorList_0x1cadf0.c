
void printTypedVectorList
               (long param_1,undefined4 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5)

{
  uint uVar1;
  uint uVar2;
  undefined8 uVar3;
  undefined1 auStack_68 [32];
  long local_48;
  
  uVar1 = (uint)param_5 & 0xff;
  local_48 = *(long *)PTR___stack_chk_guard_005ffe88;
  uVar2 = (uint)param_4;
  if (uVar2 == 0) {
    cs_snprintf(auStack_68,0x20,&DAT_001fe070,uVar1,param_5,PTR___stack_chk_guard_005ffe88,0);
    if (uVar1 == 0x68) goto LAB_001caf6c;
    if (uVar1 < 0x69) {
      if (uVar1 == 0x62) goto LAB_001caf64;
      if (uVar1 == 100) {
LAB_001caec0:
        uVar3 = 0xd;
        goto LAB_001caec8;
      }
    }
    else {
      if (uVar1 == 0x71) {
LAB_001cafcc:
        uVar3 = 0xe;
        goto LAB_001caec8;
      }
      if (uVar1 == 0x73) goto LAB_001caf24;
    }
  }
  else {
    cs_snprintf(auStack_68,0x20,".%u%c",param_4,uVar1,PTR___stack_chk_guard_005ffe88,0);
    if (uVar1 == 0x68) {
      if (uVar2 == 4) {
        uVar3 = 6;
        goto LAB_001caec8;
      }
      if (4 < uVar2) {
        uVar3 = 5;
        if (uVar2 != 8) {
          uVar3 = 0;
        }
        goto LAB_001caec8;
      }
      if (uVar2 != 1) {
        uVar3 = 7;
        if (uVar2 != 2) {
          uVar3 = 0;
        }
        goto LAB_001caec8;
      }
LAB_001caf6c:
      uVar3 = 8;
      goto LAB_001caec8;
    }
    if (uVar1 < 0x69) {
      if (uVar1 == 0x62) {
        if (uVar2 == 8) {
          uVar3 = 2;
          goto LAB_001caec8;
        }
        if (8 < uVar2) {
          uVar3 = 1;
          if (uVar2 != 0x10) {
            uVar3 = 0;
          }
          goto LAB_001caec8;
        }
        if (uVar2 != 1) {
          uVar3 = 3;
          if (uVar2 != 4) {
            uVar3 = 0;
          }
          goto LAB_001caec8;
        }
LAB_001caf64:
        uVar3 = 4;
        goto LAB_001caec8;
      }
      if (uVar1 == 100) {
        if (uVar2 == 1) goto LAB_001caec0;
        uVar3 = 0xc;
        if (uVar2 == 2) goto LAB_001caec8;
      }
    }
    else if (uVar1 == 0x71) {
      if (uVar2 == 1) goto LAB_001cafcc;
    }
    else if (uVar1 == 0x73) {
      uVar3 = 10;
      if ((uVar2 == 2) || (uVar3 = 9, uVar2 == 4)) goto LAB_001caec8;
      if (uVar2 != 1) {
        uVar3 = 0;
        goto LAB_001caec8;
      }
LAB_001caf24:
      uVar3 = 0xb;
      goto LAB_001caec8;
    }
  }
  uVar3 = 0;
LAB_001caec8:
  printVectorList(param_1,param_2,param_3,auStack_68,*(undefined8 *)(param_1 + 0x3b0),uVar3);
  if (local_48 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                   local_48 - *(long *)PTR___stack_chk_guard_005ffe88);
}

