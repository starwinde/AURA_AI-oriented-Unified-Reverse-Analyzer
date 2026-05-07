
void readModRM(long param_1)

{
  byte bVar1;
  char cVar2;
  uint uVar3;
  undefined1 uVar4;
  char cVar5;
  int iVar6;
  undefined4 uVar7;
  uint uVar8;
  int iVar9;
  ulong uVar10;
  long lVar11;
  int iVar12;
  uint uVar13;
  long lVar14;
  byte local_39;
  long local_38;
  
  local_38 = *(long *)PTR___stack_chk_guard_005ffe88;
  if ((*(byte *)(param_1 + 0xc) & 1) != 0) {
LAB_001dd648:
    iVar6 = 0;
    goto LAB_001dd758;
  }
  *(char *)(param_1 + 0x42) =
       (char)*(undefined8 *)(param_1 + 0x58) - (char)*(undefined8 *)(param_1 + 0x68);
  iVar6 = (**(code **)(param_1 + 0x48))(*(undefined8 *)(param_1 + 0x50),param_1 + 0xa0);
  if (iVar6 == 0) {
    bVar1 = *(byte *)(param_1 + 0xa0);
    uVar10 = (ulong)bVar1;
    lVar11 = *(long *)(param_1 + 0x58) + 1;
    *(undefined1 *)(param_1 + 0xc) = 1;
    *(byte *)(param_1 + 0xd) = bVar1;
    *(long *)(param_1 + 0x58) = lVar11;
    if (((*(char *)(param_1 + 0xa1) == '\x0f') && (*(int *)(param_1 + 0x84) == 1)) &&
       ((byte)(*(char *)(param_1 + 0x81) - 0x20U) < 4)) {
      uVar10 = (ulong)(bVar1 | 0xc0);
      *(char *)(param_1 + 0xa0) = (char)(bVar1 | 0xc0);
    }
    cVar2 = *(char *)(param_1 + 0x7c);
    iVar6 = (int)(uVar10 >> 6);
    uVar13 = (uint)uVar10 & 7;
    if (cVar2 == '\x04') {
      iVar9 = 0x24;
      *(undefined8 *)(param_1 + 0xbc) = DAT_0020b058;
    }
    else if (cVar2 == '\b') {
      iVar9 = 0x34;
      *(undefined8 *)(param_1 + 0xbc) = DAT_0020b060;
    }
    else if (cVar2 == '\x02') {
      iVar9 = 0x14;
      *(undefined8 *)(param_1 + 0xbc) = DAT_0020b050;
    }
    else {
      iVar9 = *(int *)(param_1 + 0xc0);
    }
    iVar12 = 0;
    uVar3 = uVar13 | (*(byte *)(param_1 + 5) & 1) << 3;
    uVar8 = (uint)(uVar10 >> 3) & 7 | ((int)(uint)*(byte *)(param_1 + 5) >> 2 & 1U) << 3;
    if ((*(int *)(param_1 + 0x78) == 3) && (*(int *)(param_1 + 0x60) == 2)) {
      uVar8 = uVar8 | ~(uint)*(byte *)(param_1 + 0x3d) & 0x10;
      iVar12 = ((int)~(uint)*(byte *)(param_1 + 0x3d) >> 6 & 1U) << 4;
    }
    cVar2 = *(char *)(param_1 + 0x7d);
    *(uint *)(param_1 + 0xcc) = uVar8 + iVar9;
    uVar4 = (undefined1)(uVar10 >> 6);
    cVar5 = (char)lVar11;
    if ((cVar2 - 4U & 0xfb) != 0) {
      if (cVar2 == '\x02') {
        if (iVar6 == 2) {
          *(uint *)(param_1 + 0xc4) = uVar3 + 1;
          *(undefined4 *)(param_1 + 200) = 2;
          if ((*(byte *)(param_1 + 0x10) & 1) == 0) {
LAB_001dd814:
            *(undefined1 *)(param_1 + 0x10) = 1;
            *(char *)(param_1 + 0x40) = cVar5 - (char)*(undefined8 *)(param_1 + 0x68);
            iVar6 = (**(code **)(param_1 + 0x48))(*(undefined8 *)(param_1 + 0x50),&local_39);
            bVar1 = local_39;
            if ((iVar6 == 0) &&
               (iVar6 = (**(code **)(param_1 + 0x48))
                                  (*(undefined8 *)(param_1 + 0x50),&local_39,
                                   *(long *)(param_1 + 0x58) + 1), iVar6 == 0)) {
              *(long *)(param_1 + 0x58) = *(long *)(param_1 + 0x58) + 2;
              *(long *)(param_1 + 0x18) = (long)CONCAT11(local_39,bVar1);
              iVar6 = 0;
              goto LAB_001dd758;
            }
            goto LAB_001dd750;
          }
        }
        else {
          if (iVar6 == 3) {
            *(uint *)(param_1 + 0xc4) = *(int *)(param_1 + 0xbc) + uVar3;
            iVar6 = readDisplacement(param_1);
            iVar6 = -(uint)(iVar6 != 0);
            goto LAB_001dd758;
          }
          if (iVar6 != 1) {
            if (uVar3 != 6) {
              iVar6 = 0;
              *(uint *)(param_1 + 0xc4) = uVar3 + 1;
              *(undefined4 *)(param_1 + 200) = 0;
              goto LAB_001dd758;
            }
            *(undefined8 *)(param_1 + 0xc4) = DAT_0020b068;
            if ((*(byte *)(param_1 + 0x10) & 1) != 0) {
              iVar6 = 0;
              goto LAB_001dd758;
            }
            goto LAB_001dd814;
          }
          *(undefined1 *)(param_1 + 0x7e) = uVar4;
          *(uint *)(param_1 + 0xc4) = uVar3 + 1;
          *(undefined4 *)(param_1 + 200) = 1;
          if ((*(byte *)(param_1 + 0x10) & 1) == 0) {
            *(undefined1 *)(param_1 + 0x10) = uVar4;
            *(char *)(param_1 + 0x40) = cVar5 - (char)*(undefined8 *)(param_1 + 0x68);
            iVar6 = (**(code **)(param_1 + 0x48))(*(undefined8 *)(param_1 + 0x50),&local_39);
            if (iVar6 != 0) goto LAB_001dd750;
            *(long *)(param_1 + 0x18) = (long)(char)local_39;
            *(long *)(param_1 + 0x58) = *(long *)(param_1 + 0x58) + 1;
          }
        }
      }
      goto LAB_001dd648;
    }
    iVar9 = 0x21;
    if (cVar2 == '\x04') {
      iVar9 = 0x11;
    }
    if (iVar6 == 2) {
      uVar7 = 3;
LAB_001dd6e8:
      *(undefined4 *)(param_1 + 200) = uVar7;
      if (uVar13 == 4) {
        *(undefined4 *)(param_1 + 0xc4) = 0x15;
        iVar6 = readSIB(param_1);
        goto joined_r0x001dd74c;
      }
      *(uint *)(param_1 + 0xc4) = uVar3 + iVar9;
    }
    else {
      if (iVar6 == 3) {
        *(uint *)(param_1 + 0xc4) = uVar3 + *(int *)(param_1 + 0xbc) + iVar12;
        *(undefined4 *)(param_1 + 200) = 0;
        iVar6 = 0;
        goto LAB_001dd758;
      }
      if (iVar6 == 1) {
        *(undefined1 *)(param_1 + 0x7e) = uVar4;
        uVar7 = 1;
        goto LAB_001dd6e8;
      }
      *(undefined4 *)(param_1 + 200) = 0;
      if (uVar13 != 4) {
        if (uVar13 != 5) {
          iVar6 = 0;
          *(uint *)(param_1 + 0xc4) = uVar3 + iVar9;
          goto LAB_001dd758;
        }
        *(undefined8 *)(param_1 + 0xc4) = DAT_0020b070;
        if ((*(byte *)(param_1 + 0x10) & 1) == 0) {
          lVar14 = 0;
          *(undefined1 *)(param_1 + 0x10) = 1;
          *(char *)(param_1 + 0x40) = cVar5 - (char)*(undefined8 *)(param_1 + 0x68);
          uVar13 = 0;
          do {
            iVar6 = (**(code **)(param_1 + 0x48))
                              (*(undefined8 *)(param_1 + 0x50),&local_39,lVar11 + lVar14);
            if (iVar6 != 0) goto LAB_001dd750;
            iVar6 = (int)lVar14;
            lVar14 = lVar14 + 1;
            lVar11 = *(long *)(param_1 + 0x58);
            uVar13 = uVar13 | (uint)local_39 << ((ulong)(uint)(iVar6 << 3) & 0x3f);
          } while (lVar14 != 4);
          *(long *)(param_1 + 0x18) = (long)(int)uVar13;
          *(long *)(param_1 + 0x58) = lVar11 + 4;
          iVar6 = 0;
          goto LAB_001dd758;
        }
        goto LAB_001dd648;
      }
      uVar7 = 0x25;
      if (cVar2 == '\x04') {
        uVar7 = 0x15;
      }
      *(undefined4 *)(param_1 + 0xc4) = uVar7;
      iVar6 = readSIB(param_1);
joined_r0x001dd74c:
      if (iVar6 != 0) goto LAB_001dd750;
    }
    iVar6 = readDisplacement(param_1);
    iVar6 = -(uint)(iVar6 != 0);
  }
  else {
LAB_001dd750:
    iVar6 = -1;
  }
LAB_001dd758:
  if (local_38 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(iVar6,PTR___stack_chk_guard_005ffe88,0,
                   local_38 - *(long *)PTR___stack_chk_guard_005ffe88);
}

