
undefined * FUN_0010fc40(char *param_1,char *param_2,undefined1 param_3)

{
  undefined8 *puVar1;
  byte bVar2;
  int iVar3;
  uint uVar4;
  int *piVar5;
  DIR *__dirp;
  undefined8 *puVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  dirent *pdVar9;
  char *pcVar10;
  size_t sVar11;
  char *pcVar12;
  size_t sVar13;
  undefined *puVar14;
  ulong uVar15;
  long lVar16;
  _IO_FILE *p_Var17;
  void *__ptr;
  undefined4 uVar18;
  undefined1 auVar19 [16];
  long local_330;
  undefined8 *local_308;
  undefined1 local_300 [41] [16];
  long local_68;
  
  local_68 = *(long *)PTR___stack_chk_guard_0013ffd0;
  piVar5 = __errno_location();
  *piVar5 = 0;
  __dirp = opendir(param_1);
  lVar16 = DAT_00141350;
  if (__dirp == (DIR *)0x0) {
    uVar7 = dcgettext(0,"cannot open directory %s",5);
    if (local_68 - *(long *)PTR___stack_chk_guard_0013ffd0 == 0) {
      puVar14 = (undefined *)FUN_0010ad30(param_3,uVar7,param_1);
      return puVar14;
    }
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(local_68 - *(long *)PTR___stack_chk_guard_0013ffd0,uVar7,
                     PTR___stack_chk_guard_0013ffd0,0);
  }
  if (DAT_00141350 != 0) {
    iVar3 = dirfd(__dirp);
    if (iVar3 < 0) {
      iVar3 = FUN_0010ab50(0xffffff9c,param_1,local_300,0,0x100);
    }
    else {
      iVar3 = FUN_0010ab50(iVar3,"",local_300,0x1000,0x100);
    }
    if (iVar3 < 0) {
      uVar7 = dcgettext(0,"cannot determine device and inode of %s",5);
      FUN_0010ad30(param_3,uVar7,param_1);
      lVar16 = local_68 - *(long *)PTR___stack_chk_guard_0013ffd0;
      if (lVar16 == 0) {
        uVar4 = closedir(__dirp);
        return (undefined *)(ulong)uVar4;
      }
LAB_001102d8:
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_0013ffd0,0,lVar16);
    }
    auVar19 = NEON_ext(local_300[0],local_300[0],8,1);
    puVar6 = malloc(0x10);
    if (puVar6 == (undefined8 *)0x0) {
LAB_00110334:
                    /* WARNING: Subroutine does not return */
      FUN_0010d454();
    }
    puVar6[1] = auVar19._8_8_;
    *puVar6 = auVar19._0_8_;
    iVar3 = FUN_0010bd00(lVar16,puVar6,&local_308);
    if (iVar3 == -1) goto LAB_00110334;
    if (iVar3 == 0) {
      if (local_308 == (undefined8 *)0x0) goto LAB_00110334;
      if (local_308 != puVar6) {
        free(puVar6);
        uVar7 = dcgettext(0,"%s: not listing already-listed directory",5);
        uVar8 = FUN_001129a0(param_1);
        error(0,0,uVar7,uVar8);
        closedir(__dirp);
        DAT_00140f40 = 2;
LAB_0010ff30:
        lVar16 = local_68 - *(long *)PTR___stack_chk_guard_0013ffd0;
        if (lVar16 == 0) {
          return PTR___stack_chk_guard_0013ffd0;
        }
        goto LAB_001102d8;
      }
    }
    puVar6 = DAT_00141370;
    if ((ulong)(DAT_00141378 - (long)DAT_00141370) < 0x10) {
      _obstack_newchunk(&DAT_00141358,0x10);
      puVar6 = DAT_00141370;
    }
    DAT_00141370 = puVar6 + 2;
    puVar6[1] = auVar19._8_8_;
    *puVar6 = auVar19._0_8_;
  }
  FUN_00108de0();
  if ((DAT_001413b0 & 1) == 0) {
    if ((DAT_001413b1 & 1) == 0) goto LAB_0010fe30;
    if ((DAT_001400dc & 1) == 0) goto LAB_00110204;
LAB_0010fdcc:
    if ((DAT_00141290 & 1) == 0) goto LAB_0010fde0;
LAB_00110250:
    DAT_001400dc = 0;
    FUN_00107430(&DAT_0011bd00,2);
  }
  else {
    if ((DAT_001400dc & 1) != 0) goto LAB_0010fdcc;
LAB_00110204:
    p_Var17 = *(_IO_FILE **)PTR_stdout_0013ffc0;
    pcVar10 = p_Var17->_IO_write_ptr;
    DAT_001402c0 = DAT_001402c0 + 1;
    if (p_Var17->_IO_write_end <= pcVar10) {
      __overflow(p_Var17,10);
      goto LAB_0010fdcc;
    }
    p_Var17->_IO_write_ptr = pcVar10 + 1;
    *pcVar10 = '\n';
    if ((DAT_00141290 & 1) != 0) goto LAB_00110250;
LAB_0010fde0:
    DAT_001400dc = 0;
  }
  __ptr = (void *)0x0;
  if (((DAT_001413b2 & 1) != 0) && (__ptr = (void *)FUN_00114d14(param_1), __ptr == (void *)0x0)) {
    uVar7 = dcgettext(0,"error canonicalizing %s",5);
    FUN_0010ad30(param_3,uVar7,param_1);
  }
  if (param_2 == (char *)0x0) {
    param_2 = param_1;
  }
  FUN_0010d8c0(param_2,DAT_00141410,0xffffffff,0,1,&DAT_001413b8,__ptr);
  free(__ptr);
  FUN_00107430(&DAT_0011bdb0,2);
LAB_0010fe30:
  *piVar5 = 0;
  local_330 = 0;
  pdVar9 = readdir(__dirp);
  if (pdVar9 == (dirent *)0x0) goto LAB_0010fec8;
  do {
    pcVar10 = pdVar9->d_name;
    puVar6 = DAT_00141028;
    if (DAT_00141418 != 2) {
      if (pdVar9->d_name[0] == '.') {
        if (DAT_00141418 == 0) goto LAB_0010feb0;
        pcVar12 = pcVar10;
        if (pdVar9->d_name[1] == '.') {
          pcVar12 = pdVar9->d_name + 1;
        }
        if (pcVar12[1] == '\0') goto LAB_0010feb0;
      }
      else {
        puVar1 = DAT_00141420;
        if (DAT_00141418 == 0) {
          for (; puVar6 = DAT_00141028, puVar1 != (undefined8 *)0x0;
              puVar1 = (undefined8 *)puVar1[1]) {
            iVar3 = fnmatch((char *)*puVar1,pcVar10,4);
            if (iVar3 == 0) goto LAB_0010feb0;
          }
        }
      }
    }
    for (; puVar6 != (undefined8 *)0x0; puVar6 = (undefined8 *)puVar6[1]) {
      iVar3 = fnmatch((char *)*puVar6,pcVar10,4);
      if (iVar3 == 0) goto LAB_0010feb0;
    }
    uVar18 = 0;
    uVar15 = (ulong)(pdVar9->d_type - 1) & 0xff;
    if ((uint)uVar15 < 0xe) {
      uVar18 = *(undefined4 *)(&DAT_00118518 + uVar15 * 4);
    }
    lVar16 = FUN_00115420(pcVar10,uVar18,0,param_1);
    if ((((DAT_00140f2c == 1) && (DAT_00140f3c == 6)) && ((DAT_00140f28 & 1) == 0)) &&
       ((DAT_001413b0 & 1) == 0)) {
      FUN_0010d4f0();
      FUN_0010f220();
      FUN_00108de0();
    }
    local_330 = local_330 + lVar16;
    FUN_0010b1e0();
    while( true ) {
      *piVar5 = 0;
      pdVar9 = readdir(__dirp);
      if (pdVar9 != (dirent *)0x0) break;
LAB_0010fec8:
      if (*piVar5 == 0) {
LAB_0010fef8:
        iVar3 = closedir(__dirp);
        if (iVar3 == 0) {
          FUN_0010d4f0();
        }
        else {
          uVar7 = dcgettext(0,"closing directory %s",5);
          FUN_0010ad30(param_3,uVar7,param_1);
          FUN_0010d4f0();
        }
        if ((DAT_001413b0 & 1) != 0) {
          FUN_0010f860(param_1,0);
        }
        if ((DAT_00140f2c == 0) || ((DAT_00140f28 & 1) != 0)) {
          pcVar10 = (char *)FUN_0010beb0(local_330,local_300[0] + 1,DAT_00141018,0x200,DAT_00141010)
          ;
          sVar11 = strlen(pcVar10);
          bVar2 = DAT_00141290;
          pcVar10[-1] = ' ';
          pcVar10[sVar11] = DAT_001400cc;
          if ((bVar2 & 1) != 0) {
            FUN_00107430(&DAT_0011bd00,2);
          }
          pcVar12 = (char *)dcgettext(0,"total",5);
          sVar13 = strlen(pcVar12);
          FUN_00107430(pcVar12,sVar13);
          FUN_00107430(pcVar10 + -1,pcVar10 + ((sVar11 + 1) - (long)(pcVar10 + -1)));
        }
        if (DAT_00140ee0 == 0) goto LAB_0010ff30;
        lVar16 = local_68 - *(long *)PTR___stack_chk_guard_0013ffd0;
        if (lVar16 == 0) {
          puVar14 = (undefined *)FUN_0010f220(PTR___stack_chk_guard_0013ffd0,0,0);
          return puVar14;
        }
        goto LAB_001102d8;
      }
      uVar7 = dcgettext(0,"reading directory %s",5);
      FUN_0010ad30(param_3,uVar7,param_1);
      if (*piVar5 != 0x4b) goto LAB_0010fef8;
LAB_0010feb0:
      FUN_0010b1e0();
    }
  } while( true );
}

