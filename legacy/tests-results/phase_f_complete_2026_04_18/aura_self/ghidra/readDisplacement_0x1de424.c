
void readDisplacement(long param_1)

{
  byte bVar1;
  int iVar2;
  undefined8 uVar3;
  long lVar4;
  long lVar5;
  uint uVar6;
  byte local_39;
  long local_38;
  
  local_38 = *(long *)PTR___stack_chk_guard_005ffe88;
  if ((*(byte *)(param_1 + 0x10) & 1) == 0) {
    lVar4 = *(long *)(param_1 + 0x58);
    *(undefined1 *)(param_1 + 0x10) = 1;
    uVar6 = *(uint *)(param_1 + 200);
    *(char *)(param_1 + 0x40) = (char)lVar4 - (char)*(undefined8 *)(param_1 + 0x68);
    if (uVar6 == 2) {
      iVar2 = (**(code **)(param_1 + 0x48))(*(undefined8 *)(param_1 + 0x50),&local_39);
      bVar1 = local_39;
      if (iVar2 == 0) {
        iVar2 = (**(code **)(param_1 + 0x48))
                          (*(undefined8 *)(param_1 + 0x50),&local_39,*(long *)(param_1 + 0x58) + 1);
        if (iVar2 == 0) {
          *(long *)(param_1 + 0x58) = *(long *)(param_1 + 0x58) + 2;
          *(long *)(param_1 + 0x18) = (long)CONCAT11(local_39,bVar1);
          goto LAB_001de4f8;
        }
      }
LAB_001de490:
      uVar3 = 0xffffffff;
      goto LAB_001de4fc;
    }
    if (uVar6 < 3) {
      if (uVar6 == 0) {
        *(undefined1 *)(param_1 + 0x10) = 0;
      }
      else {
        iVar2 = (**(code **)(param_1 + 0x48))(*(undefined8 *)(param_1 + 0x50),&local_39);
        if (iVar2 != 0) goto LAB_001de490;
        *(long *)(param_1 + 0x18) = (long)(char)local_39;
        *(long *)(param_1 + 0x58) = *(long *)(param_1 + 0x58) + 1;
      }
    }
    else if (uVar6 == 3) {
      lVar5 = 0;
      uVar6 = 0;
      do {
        iVar2 = (**(code **)(param_1 + 0x48))
                          (*(undefined8 *)(param_1 + 0x50),&local_39,lVar4 + lVar5);
        if (iVar2 != 0) {
          uVar3 = 0xffffffff;
          goto LAB_001de4fc;
        }
        iVar2 = (int)lVar5;
        lVar5 = lVar5 + 1;
        lVar4 = *(long *)(param_1 + 0x58);
        uVar6 = uVar6 | (uint)local_39 << ((ulong)(uint)(iVar2 << 3) & 0x3f);
      } while (lVar5 != 4);
      *(long *)(param_1 + 0x18) = (long)(int)uVar6;
      *(long *)(param_1 + 0x58) = lVar4 + 4;
    }
  }
LAB_001de4f8:
  uVar3 = 0;
LAB_001de4fc:
  if (local_38 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(uVar3,PTR___stack_chk_guard_005ffe88,0,
                   local_38 - *(long *)PTR___stack_chk_guard_005ffe88);
}

