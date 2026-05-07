
/* WARNING: Type propagation algorithm not settling */

void FUN_001e1630(long param_1,ulong param_2,undefined8 param_3)

{
  uint uVar1;
  byte bVar2;
  int iVar3;
  bool bVar4;
  undefined1 uVar5;
  int iVar6;
  undefined4 uVar7;
  uint uVar8;
  undefined8 uVar9;
  long lVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  ulong uVar14;
  char *pcVar15;
  char *pcVar16;
  long lVar17;
  char cVar18;
  undefined8 uVar19;
  char local_70 [8];
  long local_68;
  
  iVar3 = (int)param_2;
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  uVar9 = FUN_0018ffd0(param_1,param_2,0);
  FUN_0018ffd0(param_1,iVar3 + 1);
  lVar10 = FUN_001900a0();
  uVar11 = FUN_0018ffd0(param_1,iVar3 + 2);
  uVar12 = FUN_0018ffd0(param_1,iVar3 + 3);
  uVar13 = FUN_0018ffd0(param_1,iVar3 + 4);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
    iVar6 = FUN_00190080(uVar13);
  }
  else {
    lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    lVar17 = lVar17 + (ulong)*(byte *)(lVar17 + 0xa0) * 0x30;
    *(undefined4 *)(lVar17 + 0xa8) = 3;
    uVar5 = *(undefined1 *)(param_1 + 0x328);
    *(undefined4 *)(lVar17 + 0xb0) = 0;
    *(undefined1 *)(lVar17 + 200) = uVar5;
    FUN_00190080(uVar9);
    uVar8 = FUN_001e6bd4();
    lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    *(uint *)(lVar17 + (ulong)*(byte *)(lVar17 + 0xa0) * 0x30 + 0xb4) = uVar8 & 0xffff;
    iVar6 = FUN_00190080(uVar11);
    if (iVar6 == 0x1e) {
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      uVar14 = (ulong)*(byte *)(lVar17 + 0xa0);
    }
    else {
      FUN_00190080(uVar11);
      uVar8 = FUN_001e6bd4();
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      uVar14 = (ulong)*(byte *)(lVar17 + 0xa0);
      *(uint *)(lVar17 + uVar14 * 0x30 + 0xb8) = uVar8 & 0xffff;
    }
    uVar19 = *(undefined8 *)(param_1 + 800);
    lVar17 = lVar17 + uVar14 * 0x30;
    *(int *)(lVar17 + 0xbc) = (int)lVar10;
    *(undefined8 *)(lVar17 + 0xc0) = 0;
    uVar7 = FUN_0018ffb0(param_1);
    pcVar15 = (char *)FUN_001e68d4(uVar19,uVar7,*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x98)
    ;
    if (pcVar15 == (char *)0x0) {
      local_70[0] = '\0';
    }
    else {
      cVar18 = *pcVar15;
      pcVar16 = local_70;
      uVar8 = 0;
      uVar14 = 0;
      if (cVar18 != '\0') {
        do {
          while (cVar18 != -0x80) {
            uVar1 = uVar8 + 1;
            pcVar16[uVar14] = cVar18;
            uVar8 = uVar1 & 0xff;
            uVar14 = (ulong)uVar1 & 0xff;
            cVar18 = pcVar15[uVar8];
            if (cVar18 == '\0') {
              pcVar16 = pcVar16 + uVar14;
              goto LAB_001e1874;
            }
          }
          uVar1 = uVar8 + 1;
          pcVar16[uVar14] = '\0';
          uVar8 = uVar1 & 0xff;
          uVar14 = (ulong)uVar1 & 0xff;
          cVar18 = pcVar15[uVar8];
        } while (cVar18 != '\0');
        pcVar16 = pcVar16 + uVar14;
      }
LAB_001e1874:
      *pcVar16 = '\0';
    }
    lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar2 = *(byte *)(lVar17 + 0xa0);
    *(char *)(lVar17 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10 + 0xc9) = local_70[(int)(uint)bVar2]
    ;
    iVar6 = FUN_00190080(uVar13);
  }
  if (iVar6 == 0) {
    FUN_00190370(param_3,&DAT_001fdf80);
    iVar6 = FUN_00190080(uVar9);
  }
  else {
    FUN_001e12b0(param_1,iVar3 + 4,param_3);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      uVar8 = FUN_001e6bd4(iVar6);
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(uint *)(lVar17 + (ulong)*(byte *)(lVar17 + 0xa0) * 0x30 + 0xb0) = uVar8 & 0xffff;
    }
    FUN_00190370(param_3,&DAT_001fde10);
    FUN_00190370(param_3,&DAT_001fdf80);
    iVar6 = FUN_00190080(uVar9);
  }
  bVar4 = iVar6 != 0;
  if (bVar4) {
    FUN_001e12b0(param_1,param_2 & 0xffffffff,param_3);
    iVar6 = FUN_00190080(uVar11);
  }
  else {
    iVar6 = FUN_00190080(uVar11);
  }
  if ((iVar6 == 0) || (iVar6 = FUN_00190080(uVar11), iVar6 == 0x1e)) {
    uVar14 = FUN_00190030(uVar12);
  }
  else {
    if (bVar4) {
      FUN_00190370(param_3,&DAT_00203938);
    }
    FUN_001e12b0(param_1,iVar3 + 2,param_3);
    if (lVar10 != 1) {
      FUN_001903f0(param_3,&DAT_00203940,lVar10);
    }
    bVar4 = true;
    uVar14 = FUN_00190030(uVar12);
  }
  if ((uVar14 & 1) != 0) {
    uVar14 = FUN_001900a0(uVar12);
    lVar10 = *(long *)(param_1 + 800);
    if (*(int *)(lVar10 + 0x60) != 0) {
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(ulong *)(lVar17 + (ulong)*(byte *)(lVar17 + 0xa0) * 0x30 + 0xc0) = uVar14;
    }
    if (uVar14 == 0) {
      if (!bVar4) {
        FUN_00190370(param_3,&DAT_001ffe18);
      }
    }
    else if (bVar4) {
      if ((long)uVar14 < 0) {
        FUN_00190370(param_3,&DAT_00203948);
        FUN_001e1080(*(undefined1 *)(param_1 + 6),*(undefined8 *)(param_1 + 800),param_3,-uVar14,1);
      }
      else {
        FUN_00190370(param_3,&DAT_00203938);
        FUN_001e1080(*(undefined1 *)(param_1 + 6),*(undefined8 *)(param_1 + 800),param_3,uVar14,1);
      }
    }
    else {
      uVar8 = *(uint *)(lVar10 + 4);
      if (uVar8 == 8) {
        *(undefined1 *)(param_1 + 6) = 8;
        uVar5 = 8;
      }
      else {
        uVar5 = *(undefined1 *)(param_1 + 6);
      }
      if ((long)uVar14 < 0) {
        FUN_001e1080(uVar5,lVar10,param_3,uVar14 & *(ulong *)(PTR_DAT_005ffe50 + (ulong)uVar8 * 8),1
                    );
      }
      else {
        FUN_001e1080(uVar5,lVar10,param_3,uVar14,1);
      }
    }
  }
  FUN_00190370(param_3,&DAT_001fe598);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar10 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    *(char *)(lVar10 + 0xa0) = *(char *)(lVar10 + 0xa0) + '\x01';
  }
  if (*(char *)(param_1 + 6) == '\0') {
    *(undefined1 *)(param_1 + 6) = *(undefined1 *)(param_1 + 0x328);
  }
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                   local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
}

