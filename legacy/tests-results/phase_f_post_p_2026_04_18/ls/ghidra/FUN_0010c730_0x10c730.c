
long FUN_0010c730(undefined8 *param_1)

{
  bool bVar1;
  byte bVar2;
  char cVar3;
  size_t sVar4;
  long lVar5;
  ulong uVar6;
  char *pcVar7;
  long lVar8;
  undefined1 auStack_2c8 [19];
  char local_2b5 [637];
  long local_38;
  
  bVar2 = DAT_00140f28;
  local_38 = *(long *)PTR___stack_chk_guard_0013ffd0;
  if ((DAT_00140f30 & 1) == 0) {
    lVar8 = 0;
    if ((DAT_00140f28 & 1) != 0) {
      if (DAT_00140f2c == 4) goto LAB_0010c824;
LAB_0010c78c:
      lVar5 = (long)DAT_00140ef8 + 1;
LAB_0010c798:
      lVar8 = lVar8 + lVar5;
    }
LAB_0010c79c:
    if ((DAT_0014101c & 1) != 0) {
      if (DAT_00140f2c == 4) goto LAB_0010c908;
LAB_0010c868:
      lVar8 = lVar8 + (long)DAT_00140f0c + 1;
LAB_0010c878:
      lVar5 = param_1[0x17];
      goto joined_r0x0010c87c;
    }
  }
  else {
    if (DAT_00140f2c == 4) {
      pcVar7 = local_2b5 + 1;
      local_2b5[1] = 0;
      uVar6 = param_1[4];
      do {
        pcVar7 = pcVar7 + -1;
        *pcVar7 = (char)uVar6 + (char)(uVar6 / 10) * -10 + '0';
        bVar1 = 9 < uVar6;
        uVar6 = uVar6 / 10;
      } while (bVar1);
      sVar4 = strlen(pcVar7);
      lVar8 = sVar4 + 1;
      if ((bVar2 & 1) != 0) {
LAB_0010c824:
        lVar5 = 2;
        if ((*(byte *)(param_1 + 0x15) & 1) != 0) {
          pcVar7 = (char *)FUN_0010beb0(param_1[0xb],auStack_2c8,DAT_00141018,0x200,DAT_00141010);
          sVar4 = strlen(pcVar7);
          lVar8 = lVar8 + sVar4 + 1;
          goto LAB_0010c79c;
        }
        goto LAB_0010c798;
      }
      if ((DAT_0014101c & 1) == 0) goto LAB_0010c7a8;
LAB_0010c908:
      sVar4 = strlen((char *)param_1[0x14]);
      lVar8 = lVar8 + sVar4 + 1;
      goto LAB_0010c878;
    }
    lVar8 = (long)DAT_00140ef4 + 1;
    if ((DAT_00140f28 & 1) != 0) goto LAB_0010c78c;
    if ((DAT_0014101c & 1) != 0) goto LAB_0010c868;
  }
LAB_0010c7a8:
  lVar5 = param_1[0x17];
joined_r0x0010c87c:
  if (lVar5 == 0) {
    lVar5 = FUN_0010a130(*param_1,DAT_00140f20,*(undefined4 *)((long)param_1 + 0xb4));
  }
  lVar8 = lVar8 + lVar5;
  if ((DAT_00140f80 != 0) &&
     (cVar3 = FUN_0010af10(*(undefined1 *)(param_1 + 0x15),*(undefined4 *)(param_1 + 5),
                           *(undefined4 *)(param_1 + 0x13)), cVar3 != '\0')) {
    lVar8 = lVar8 + 1;
  }
  if (local_38 - *(long *)PTR___stack_chk_guard_0013ffd0 == 0) {
    return lVar8;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_0013ffd0,0,
                   local_38 - *(long *)PTR___stack_chk_guard_0013ffd0);
}

