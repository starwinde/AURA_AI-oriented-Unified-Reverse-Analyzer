
void readImmediate(long param_1,byte param_2)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  undefined8 uVar4;
  long lVar5;
  long lVar6;
  ulong uVar7;
  byte local_39;
  long local_38;
  
  bVar2 = *(byte *)(param_1 + 0x35);
  local_38 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (bVar2 == 2) goto LAB_001ddcf4;
  if (param_2 == 0) {
    lVar5 = *(long *)(param_1 + 0x58);
    param_2 = *(byte *)(param_1 + 0x7f);
    *(char *)(param_1 + 0x41) = (char)lVar5 - (char)*(undefined8 *)(param_1 + 0x68);
    if (param_2 != 4) goto LAB_001ddb38;
LAB_001ddbf4:
    lVar6 = 0;
    uVar7 = 0;
    do {
      iVar3 = (**(code **)(param_1 + 0x48))(*(undefined8 *)(param_1 + 0x50),&local_39,lVar5 + lVar6)
      ;
      if (iVar3 != 0) goto LAB_001ddcf4;
      iVar3 = (int)lVar6;
      lVar6 = lVar6 + 1;
      lVar5 = *(long *)(param_1 + 0x58);
      uVar7 = (ulong)((uint)uVar7 | (uint)local_39 << ((ulong)(uint)(iVar3 << 3) & 0x3f));
    } while (lVar6 != 4);
    bVar2 = *(byte *)(param_1 + 0x35);
    *(long *)(param_1 + 0x58) = lVar5 + 4;
    *(ulong *)(param_1 + (ulong)bVar2 * 8 + 0xa8) = uVar7;
  }
  else {
    lVar5 = *(long *)(param_1 + 0x58);
    *(byte *)(param_1 + 0x7f) = param_2;
    *(char *)(param_1 + 0x41) = (char)lVar5 - (char)*(undefined8 *)(param_1 + 0x68);
    if (param_2 == 4) goto LAB_001ddbf4;
LAB_001ddb38:
    if (param_2 < 4) {
      if (param_2 == 1) {
        iVar3 = (**(code **)(param_1 + 0x48))(*(undefined8 *)(param_1 + 0x50),&local_39);
        if (iVar3 != 0) {
LAB_001ddcf4:
          uVar4 = 0xffffffff;
          goto LAB_001ddbac;
        }
        bVar2 = *(byte *)(param_1 + 0x35);
        *(long *)(param_1 + 0x58) = *(long *)(param_1 + 0x58) + 1;
        *(ulong *)(param_1 + (ulong)bVar2 * 8 + 0xa8) = (ulong)local_39;
      }
      else if (param_2 == 2) {
        iVar3 = (**(code **)(param_1 + 0x48))(*(undefined8 *)(param_1 + 0x50),&local_39);
        bVar1 = local_39;
        if ((iVar3 != 0) ||
           (iVar3 = (**(code **)(param_1 + 0x48))
                              (*(undefined8 *)(param_1 + 0x50),&local_39,
                               *(long *)(param_1 + 0x58) + 1), iVar3 != 0)) goto LAB_001ddcf4;
        bVar2 = *(byte *)(param_1 + 0x35);
        *(long *)(param_1 + 0x58) = *(long *)(param_1 + 0x58) + 2;
        *(ulong *)(param_1 + (ulong)bVar2 * 8 + 0xa8) = (ulong)CONCAT11(local_39,bVar1);
      }
    }
    else if (param_2 == 8) {
      lVar6 = 0;
      uVar7 = 0;
      do {
        iVar3 = (**(code **)(param_1 + 0x48))
                          (*(undefined8 *)(param_1 + 0x50),&local_39,lVar5 + lVar6);
        if (iVar3 != 0) goto LAB_001ddcf4;
        iVar3 = (int)lVar6;
        lVar6 = lVar6 + 1;
        lVar5 = *(long *)(param_1 + 0x58);
        uVar7 = uVar7 | (ulong)local_39 << ((ulong)(uint)(iVar3 << 3) & 0x3f);
      } while (lVar6 != 8);
      bVar2 = *(byte *)(param_1 + 0x35);
      *(long *)(param_1 + 0x58) = lVar5 + 8;
      *(ulong *)(param_1 + (ulong)bVar2 * 8 + 0xa8) = uVar7;
    }
  }
  uVar4 = 0;
  *(byte *)(param_1 + 0x35) = bVar2 + 1;
LAB_001ddbac:
  if (local_38 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(uVar4,PTR___stack_chk_guard_005ffe88,0,
                     local_38 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return;
}

