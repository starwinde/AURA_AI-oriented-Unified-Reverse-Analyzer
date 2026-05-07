
void FUN_001e1360(long param_1,undefined8 param_2)

{
  uint uVar1;
  undefined1 uVar2;
  byte bVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  ulong uVar9;
  char *pcVar10;
  char *pcVar11;
  long lVar12;
  char cVar13;
  long lVar14;
  char local_50 [8];
  long local_48;
  
  pcVar11 = local_50;
  local_48 = *(long *)PTR___stack_chk_guard_005ffe88;
  uVar7 = FUN_0018ffd0(param_1,0);
  uVar8 = FUN_0018ffd0(param_1,1);
  lVar14 = *(long *)(param_1 + 800);
  if (*(int *)(lVar14 + 0x60) == 0) {
    iVar4 = FUN_00190080(uVar8);
  }
  else {
    lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    lVar12 = lVar12 + (ulong)*(byte *)(lVar12 + 0xa0) * 0x30;
    *(undefined4 *)(lVar12 + 0xa8) = 3;
    uVar2 = *(undefined1 *)(param_1 + 0x328);
    *(undefined8 *)(lVar12 + 0xb0) = 0;
    *(undefined8 *)(lVar12 + 0xb8) = 0x100000000;
    *(undefined8 *)(lVar12 + 0xc0) = 0;
    *(undefined1 *)(lVar12 + 200) = uVar2;
    uVar5 = FUN_0018ffb0(param_1);
    pcVar10 = (char *)FUN_001e68d4(lVar14,uVar5,*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x98)
    ;
    if (pcVar10 == (char *)0x0) {
      local_50[0] = '\0';
    }
    else {
      cVar13 = *pcVar10;
      uVar6 = 0;
      uVar9 = 0;
      if (cVar13 != '\0') {
        do {
          while( true ) {
            uVar1 = uVar6 + 1;
            if (cVar13 == -0x80) break;
            uVar6 = uVar1 & 0xff;
            local_50[uVar9] = cVar13;
            uVar9 = (ulong)uVar1 & 0xff;
            cVar13 = pcVar10[uVar6];
            if (cVar13 == '\0') {
              pcVar11 = local_50 + uVar9;
              goto LAB_001e14ec;
            }
          }
          uVar6 = uVar1 & 0xff;
          local_50[uVar9] = '\0';
          uVar9 = (ulong)uVar1 & 0xff;
          cVar13 = pcVar10[uVar6];
        } while (cVar13 != '\0');
        pcVar11 = local_50 + uVar9;
      }
LAB_001e14ec:
      *pcVar11 = '\0';
    }
    lVar14 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar3 = *(byte *)(lVar14 + 0xa0);
    *(char *)(lVar14 + ((ulong)bVar3 * 2 + (ulong)bVar3) * 0x10 + 0xc9) = local_50[(int)(uint)bVar3]
    ;
    iVar4 = FUN_00190080(uVar8);
  }
  if (iVar4 != 0) {
    FUN_001e12b0(param_1,1,param_2);
    FUN_00190370(param_2,&DAT_001fde10);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      uVar6 = FUN_001e6bd4(iVar4);
      lVar14 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(uint *)(lVar14 + (ulong)*(byte *)(lVar14 + 0xa0) * 0x30 + 0xb0) = uVar6 & 0xffff;
      FUN_00190370(param_2,&DAT_001fdf80);
      uVar9 = FUN_00190030(uVar7);
      goto joined_r0x001e1588;
    }
  }
  FUN_00190370(param_2,&DAT_001fdf80);
  uVar9 = FUN_00190030(uVar7);
joined_r0x001e1588:
  if ((uVar9 & 1) != 0) {
    uVar9 = FUN_001900a0(uVar7);
    lVar14 = *(long *)(param_1 + 800);
    if (*(int *)(lVar14 + 0x60) != 0) {
      lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(ulong *)(lVar12 + (ulong)*(byte *)(lVar12 + 0xa0) * 0x30 + 0xc0) = uVar9;
    }
    if ((long)uVar9 < 0) {
      FUN_001e1080(*(undefined1 *)(param_1 + 6),lVar14,param_2,
                   uVar9 & *(ulong *)(PTR_DAT_005ffe50 + (ulong)*(uint *)(lVar14 + 4) * 8),1);
    }
    else {
      FUN_001e1080(*(undefined1 *)(param_1 + 6),lVar14,param_2,uVar9,1);
    }
  }
  FUN_00190370(param_2,&DAT_001fe598);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar14 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    *(char *)(lVar14 + 0xa0) = *(char *)(lVar14 + 0xa0) + '\x01';
  }
  if (*(char *)(param_1 + 6) == '\0') {
    *(undefined1 *)(param_1 + 6) = *(undefined1 *)(param_1 + 0x328);
  }
  if (local_48 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                     local_48 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return;
}

