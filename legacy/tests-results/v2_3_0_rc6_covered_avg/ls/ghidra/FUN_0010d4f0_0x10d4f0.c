
void FUN_0010d4f0(void)

{
  uint uVar1;
  long *plVar2;
  long lVar3;
  ulong uVar4;
  int iVar5;
  long *plVar6;
  long *plVar7;
  long *plVar8;
  long lVar9;
  ulong uVar10;
  undefined8 *puVar11;
  
  uVar4 = DAT_00140ee0;
  if (DAT_00141030 < DAT_00140ee0 + (DAT_00140ee0 >> 1)) {
    free(DAT_00140ee8);
    plVar6 = (long *)reallocarray(0,uVar4,0x18);
    if (plVar6 == (long *)0x0) {
                    /* WARNING: Subroutine does not return */
      FUN_0010d454();
    }
    DAT_00141030 = DAT_00140ee0 * 3;
    DAT_00140ee8 = plVar6;
  }
  uVar1 = DAT_00140f3c;
  plVar6 = DAT_00140ee8;
  uVar4 = DAT_00140ee0;
  if (DAT_00140ee0 == 0) {
    if (DAT_00140f3c != 2) goto LAB_0010d5a8;
  }
  else {
    lVar9 = 0;
    plVar2 = DAT_00140ee8 + DAT_00140ee0;
    plVar7 = DAT_00140ee8;
    do {
      plVar8 = plVar7 + 1;
      *plVar7 = DAT_00141038 + lVar9;
      lVar9 = lVar9 + 0xc0;
      plVar7 = plVar8;
    } while (plVar8 != plVar2);
    if ((uVar1 == 2) || ((DAT_00141020 != 0 && (plVar6 = DAT_00140ee8, DAT_00140f2c - 2U < 2)))) {
      uVar10 = 0;
      do {
        puVar11 = (undefined8 *)plVar6[uVar10];
        lVar9 = puVar11[0x17];
        if (lVar9 == 0) {
          lVar9 = FUN_0010a130(*puVar11,DAT_00140f20,*(undefined4 *)((long)puVar11 + 0xb4));
        }
        uVar10 = uVar10 + 1;
        puVar11[0x17] = lVar9;
      } while (uVar10 < uVar4);
    }
LAB_0010d5a8:
    if (uVar1 == 6) {
      return;
    }
  }
  iVar5 = _setjmp((__jmp_buf_tag *)&DAT_00141040);
  uVar1 = DAT_00140f3c;
  plVar6 = DAT_00140ee8;
  uVar4 = DAT_00140ee0;
  if (iVar5 == 0) {
    iVar5 = 0;
joined_r0x0010d6bc:
    if (uVar1 != 5) goto LAB_0010d61c;
  }
  else {
    if (DAT_00140f3c == 4) {
                    /* WARNING: Subroutine does not return */
      __assert_fail("sort_type != sort_version","src/ls.c",0x1016,"sort_files");
    }
    if (DAT_00140ee0 != 0) {
      plVar2 = DAT_00140ee8 + DAT_00140ee0;
      lVar9 = 0;
      plVar7 = DAT_00140ee8;
      do {
        plVar8 = plVar7 + 1;
        *plVar7 = DAT_00141038 + lVar9;
        lVar9 = lVar9 + 0xc0;
        plVar7 = plVar8;
      } while (plVar8 != plVar2);
      iVar5 = 1;
      goto joined_r0x0010d6bc;
    }
    if (DAT_00140f3c != 5) {
      return;
    }
    iVar5 = 1;
  }
  uVar1 = DAT_00140f34 + 5;
LAB_0010d61c:
  if (2 < uVar4) {
    FUN_00107c20(plVar6,uVar4,plVar6 + uVar4);
    return;
  }
  if (uVar4 == 2) {
    lVar9 = *plVar6;
    lVar3 = plVar6[1];
    iVar5 = (*(code *)(&PTR_FUN_0013ef40)
                      [(ulong)DAT_00141178 +
                       ((ulong)DAT_00141179 + ((ulong)uVar1 * 2 + (long)iVar5) * 2) * 2])
                      (lVar9,lVar3);
    if (0 < iVar5) {
      *plVar6 = lVar3;
      plVar6[1] = lVar9;
      return;
    }
  }
  return;
}

