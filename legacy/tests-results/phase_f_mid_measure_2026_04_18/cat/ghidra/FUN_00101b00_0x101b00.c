
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00101b00(int param_1,undefined8 *param_2)

{
  char *__s1;
  undefined2 *puVar1;
  byte bVar2;
  ulong uVar3;
  undefined8 *puVar4;
  bool bVar5;
  bool bVar6;
  bool bVar7;
  undefined1 uVar8;
  int iVar9;
  uint uVar10;
  char *pcVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  undefined **ppuVar14;
  long lVar15;
  byte *__file;
  uint *puVar16;
  __off_t _Var17;
  int *piVar18;
  ulong uVar19;
  byte bVar20;
  char *pcVar21;
  undefined **ppuVar22;
  undefined *puVar23;
  undefined8 uVar24;
  undefined *puVar25;
  undefined8 *puVar26;
  undefined **ppuVar27;
  undefined **ppuVar28;
  undefined **__dest;
  undefined **ppuVar29;
  undefined **ppuVar30;
  undefined **ppuVar31;
  undefined4 uVar32;
  undefined **ppuVar33;
  undefined **unaff_x27;
  undefined **ppuVar34;
  undefined **ppuVar35;
  undefined **local_340;
  undefined **local_330;
  uint local_328;
  undefined **local_318;
  uint local_310;
  uint local_30c;
  undefined *local_308;
  uint local_2fc;
  byte local_2f8;
  long local_2e8;
  uint local_2e0;
  uint local_2dc;
  int local_2d8;
  uint local_2d4;
  __dev_t local_2d0;
  __ino_t local_2c8;
  int local_2c0;
  uint local_2bc;
  int local_2ac;
  undefined8 local_2a8;
  undefined8 uStack_2a0;
  undefined8 uStack_298;
  undefined8 uStack_290;
  undefined8 local_288;
  undefined8 uStack_280;
  undefined8 local_278;
  undefined1 local_270 [132];
  undefined4 uStack_1ec;
  undefined4 uStack_1e8;
  undefined4 uStack_1e4;
  undefined4 local_1e0;
  undefined4 uStack_1dc;
  undefined4 uStack_1d8;
  undefined4 uStack_1d4;
  undefined4 local_1d0;
  undefined4 uStack_1cc;
  undefined4 uStack_1c8;
  undefined4 uStack_1c4;
  undefined4 local_1c0;
  undefined4 uStack_1bc;
  undefined *puStack_1b8;
  undefined *local_1b0;
  undefined *puStack_1a8;
  undefined *puStack_1a0;
  undefined *puStack_198;
  undefined8 local_190;
  undefined8 uStack_188;
  byte local_16e;
  char local_16d;
  byte local_16c;
  char local_16b;
  long local_68;
  
  pcVar21 = (char *)*param_2;
  local_68 = *(long *)PTR___stack_chk_guard_0011ffe0;
  if (pcVar21 == (char *)0x0) {
    fwrite("A NULL argv[0] was passed through an exec system call.\n",1,0x37,
           *(FILE **)PTR_stderr_0011ffc0);
                    /* WARNING: Subroutine does not return */
    abort();
  }
  pcVar11 = strrchr(pcVar21,0x2f);
  if ((((pcVar11 != (char *)0x0) && (__s1 = pcVar11 + 1, 6 < (long)__s1 - (long)pcVar21)) &&
      (iVar9 = strncmp(pcVar11 + -6,"/.libs/",7), iVar9 == 0)) &&
     (iVar9 = strncmp(__s1,"lt-",3), pcVar21 = __s1, iVar9 == 0)) {
    *(char **)PTR_program_invocation_short_name_0011fff0 = pcVar11 + 4;
    pcVar21 = pcVar11 + 4;
  }
  puVar23 = &DAT_00120000;
  ppuVar27 = (undefined **)0x105000;
  *(char **)PTR_program_invocation_name_0011ffa8 = pcVar21;
  DAT_001201e0 = pcVar21;
  setlocale(6,"");
  bindtextdomain("coreutils","/usr/share/locale");
  ppuVar30 = &PTR_s_number_nonblank_0011fa70;
  textdomain("coreutils");
  pcVar11 = "benstuvAET";
  ppuVar34 = (undefined **)0x0;
  FUN_00105190(FUN_00104f70);
  bVar5 = false;
  local_328 = 0;
  local_30c = 0;
  bVar6 = false;
  local_2dc = 0;
LAB_00101c00:
  iVar9 = getopt_long(param_1,param_2,"benstuvAET",&PTR_s_number_nonblank_0011fa70,0);
  puVar4 = (undefined8 *)PTR_stdout_0011ffd0;
  do {
    PTR_stdout_0011ffd0 = (undefined *)puVar4;
    if (iVar9 == -1) {
      iVar9 = fstat(1,(stat *)local_270);
      if (iVar9 < 0) {
        puVar16 = (uint *)__errno_location();
        pcVar21 = "standard output";
        ppuVar35 = ppuVar34;
        goto LAB_001029c4;
      }
      local_2bc = local_270._16_4_ & 0xf000;
      if ((int)local_270._56_4_ < 1) {
        ppuVar30 = (undefined **)0x20000;
      }
      else {
        uVar19 = (ulong)(int)local_270._56_4_;
        uVar3 = 0;
        if (uVar19 != 0) {
          uVar3 = 0x1ffff / uVar19;
        }
        ppuVar30 = (undefined **)(uVar19 + uVar3 * uVar19);
        if ((local_2bc == 0x8000) && (((ulong)((long)ppuVar30 + -1) & (ulong)ppuVar30) != 0)) {
          ppuVar30 = (undefined **)(1L << ((ulong)(uint)-(int)LZCOUNT(ppuVar30) & 0x3f));
        }
      }
      local_2d0 = local_270._0_8_;
      local_2c8 = local_270._8_8_;
      __file = &DAT_00105a98;
      DAT_001201e8 = &DAT_00105a98;
      uVar10 = *(uint *)PTR_optind_0011ffc8;
      ppuVar27 = (undefined **)(ulong)uVar10;
      local_2e0 = local_328 | local_30c;
      local_2d8 = getpagesize();
      local_2f8 = 1;
      local_2e8 = (long)(int)uVar10;
      local_2c0 = 0;
      puVar25 = puVar23;
      if ((int)uVar10 < param_1) goto LAB_0010211c;
      local_2d4 = DAT_00105a98 - 0x2d;
      if (local_2d4 == 0) goto LAB_0010213c;
      break;
    }
    if (iVar9 == 0x65) {
      bVar5 = true;
      local_30c = 1;
      goto LAB_00101c00;
    }
    if (iVar9 < 0x66) {
      if (iVar9 == 0x45) {
        local_30c = 1;
      }
      else if (iVar9 < 0x46) {
        if (iVar9 == -2) {
          uVar12 = dcgettext(0,"Usage: %s [OPTION]... [FILE]...\n",5);
          __printf_chk(2,uVar12,pcVar21);
          pcVar21 = (char *)dcgettext(0,"Concatenate FILE(s) to standard output.\n",5);
          fputs_unlocked(pcVar21,(FILE *)*puVar4);
          pcVar21 = (char *)dcgettext(0,"\nWith no FILE, or when FILE is -, read standard input.\n",
                                      5);
          fputs_unlocked(pcVar21,(FILE *)*puVar4);
          pcVar21 = (char *)dcgettext(0,
                                      "\n  -A, --show-all           equivalent to -vET\n  -b, --number-nonblank    number nonempty output lines, overrides -n\n  -e                       equivalent to -vE\n  -E, --show-ends          display $ at end of each line\n  -n, --number             number all output lines\n  -s, --squeeze-blank      suppress repeated empty output lines\n"
                                      ,5);
          fputs_unlocked(pcVar21,(FILE *)*puVar4);
          pcVar21 = (char *)dcgettext(0,
                                      "  -t                       equivalent to -vT\n  -T, --show-tabs          display TAB characters as ^I\n  -u                       (ignored)\n  -v, --show-nonprinting   use ^ and M- notation, except for LFD and TAB\n"
                                      ,5);
          fputs_unlocked(pcVar21,(FILE *)*puVar4);
          pcVar21 = (char *)dcgettext(0,"      --help        display this help and exit\n",5);
          fputs_unlocked(pcVar21,(FILE *)*puVar4);
          pcVar21 = (char *)dcgettext(0,"      --version     output version information and exit\n",
                                      5);
          fputs_unlocked(pcVar21,(FILE *)*puVar4);
          uVar12 = dcgettext(0,
                             "\nExamples:\n  %s f - g  Output f\'s contents, then standard input, then g\'s contents.\n  %s        Copy standard input to standard output.\n"
                             ,5);
          __printf_chk(2,uVar12,DAT_001201e0);
          puVar26 = (undefined8 *)(local_270 + 0x80);
          uStack_1e8 = SUB84(PTR_s_test_invocation_00120038,0);
          uStack_1e4 = (undefined4)((ulong)PTR_s_test_invocation_00120038 >> 0x20);
          local_270._128_4_ = SUB84(PTR_DAT_00120030,0);
          uStack_1ec = (undefined4)((ulong)PTR_DAT_00120030 >> 0x20);
          uStack_1d8 = SUB84(PTR_s_Multi_call_invocation_00120048,0);
          uStack_1d4 = (undefined4)((ulong)PTR_s_Multi_call_invocation_00120048 >> 0x20);
          local_1e0 = SUB84(PTR_s_coreutils_00120040,0);
          uStack_1dc = (undefined4)((ulong)PTR_s_coreutils_00120040 >> 0x20);
          uStack_1c8 = SUB84(PTR_s_sha2_utilities_00120058,0);
          uStack_1c4 = (undefined4)((ulong)PTR_s_sha2_utilities_00120058 >> 0x20);
          local_1d0 = SUB84(PTR_s_sha224sum_00120050,0);
          uStack_1cc = (undefined4)((ulong)PTR_s_sha224sum_00120050 >> 0x20);
          puStack_1b8 = PTR_s_sha2_utilities_00120068;
          local_1c0 = SUB84(PTR_s_sha256sum_00120060,0);
          uStack_1bc = (undefined4)((ulong)PTR_s_sha256sum_00120060 >> 0x20);
          puStack_1a8 = PTR_s_sha2_utilities_00120078;
          local_1b0 = PTR_s_sha384sum_00120070;
          puStack_198 = PTR_s_sha2_utilities_00120088;
          puStack_1a0 = PTR_s_sha512sum_00120080;
          uStack_188 = uRam0000000000120098;
          local_190 = _DAT_00120090;
          while (((char *)*puVar26 != (char *)0x0 &&
                 (iVar9 = strcmp("cat",(char *)*puVar26), iVar9 != 0))) {
            puVar26 = puVar26 + 2;
          }
          puVar23 = (undefined *)puVar26[1];
          if (puVar23 == (undefined *)0x0) {
            uVar12 = dcgettext(0,"\n%s online help: <%s>\n",5);
            __printf_chk(2,uVar12,"GNU coreutils","https://www.gnu.org/software/coreutils/");
            pcVar21 = setlocale(5,(char *)0x0);
            if (pcVar21 == (char *)0x0) {
              puVar23 = &DAT_00105248;
              uVar12 = dcgettext(0,"Full documentation <%s%s>\n",5);
              __printf_chk(2,uVar12,"https://www.gnu.org/software/coreutils/",&DAT_00105248);
              uVar12 = dcgettext(0,"or available locally via: info \'(coreutils) %s%s\'\n",5);
              pcVar21 = " invocation";
              goto LAB_0010288c;
            }
            puVar23 = &DAT_00105248;
LAB_0010281c:
            iVar9 = strncmp(pcVar21,"en_",3);
            if (iVar9 != 0) {
              pcVar21 = (char *)dcgettext(0,
                                          "Report any translation bugs to <https://translationproject.org/team/>\n"
                                          ,5);
              fputs_unlocked(pcVar21,(FILE *)*puVar4);
            }
          }
          else {
            uVar12 = dcgettext(0,"\n%s online help: <%s>\n",5);
            __printf_chk(2,uVar12,"GNU coreutils","https://www.gnu.org/software/coreutils/");
            pcVar21 = setlocale(5,(char *)0x0);
            if (pcVar21 != (char *)0x0) goto LAB_0010281c;
          }
          uVar12 = dcgettext(0,"Full documentation <%s%s>\n",5);
          __printf_chk(2,uVar12,"https://www.gnu.org/software/coreutils/",&DAT_00105248);
          uVar12 = dcgettext(0,"or available locally via: info \'(coreutils) %s%s\'\n",5);
          pcVar21 = "";
          if (puVar23 == &DAT_00105248) {
            pcVar21 = " invocation";
          }
LAB_0010288c:
          __printf_chk(2,uVar12,puVar23,pcVar21);
                    /* WARNING: Subroutine does not return */
          exit(0);
        }
        if (iVar9 != 0x41) {
          if (iVar9 == -3) {
            uVar24 = *puVar4;
            uVar12 = FUN_00102ee0("Torbjorn Granlund",&DAT_00105a00);
            uVar13 = FUN_00102ee0("Richard M. Stallman");
            FUN_00103390(uVar24,&DAT_00105248,"GNU coreutils",&DAT_00105a48,uVar12,uVar13,0);
                    /* WARNING: Subroutine does not return */
            exit(0);
          }
          goto LAB_00102974;
        }
        ppuVar34 = (undefined **)0x1;
        bVar5 = true;
        local_30c = 1;
      }
      else if (iVar9 == 0x54) {
        ppuVar34 = (undefined **)0x1;
      }
      else {
        if (iVar9 != 0x62) goto LAB_00102974;
        local_328 = 1;
        local_2dc = 1;
      }
      goto LAB_00101c00;
    }
    if (iVar9 == 0x74) {
      ppuVar34 = (undefined **)0x1;
      bVar5 = true;
      goto LAB_00101c00;
    }
    if (0x74 < iVar9) {
      if (iVar9 != 0x75) {
        if (iVar9 != 0x76) {
LAB_00102974:
          uVar13 = *(undefined8 *)PTR_stderr_0011ffc0;
          uVar12 = dcgettext(0,"Try \'%s --help\' for more information.\n",5);
          __fprintf_chk(uVar13,2,uVar12,pcVar21);
                    /* WARNING: Subroutine does not return */
          exit(1);
        }
        bVar5 = true;
      }
      goto LAB_00101c00;
    }
    if (iVar9 == 0x6e) goto LAB_00101dcc;
    if (iVar9 != 0x73) goto LAB_00102974;
    bVar6 = true;
    iVar9 = getopt_long(param_1,param_2,"benstuvAET",&PTR_s_number_nonblank_0011fa70,0);
    puVar4 = (undefined8 *)PTR_stdout_0011ffd0;
  } while( true );
LAB_00101e8c:
  ppuVar27 = (undefined **)(puVar25 + 0xe0);
  uVar10 = open((char *)__file,0);
  ppuVar22 = (undefined **)(ulong)uVar10;
  *(uint *)(puVar25 + 0x1f0) = uVar10;
  ppuVar35 = ppuVar34;
  if ((int)uVar10 < 0) {
    piVar18 = __errno_location();
    uVar12 = *(undefined8 *)(puVar25 + 0x1e8);
    goto LAB_00102650;
  }
LAB_00101ea4:
  iVar9 = fstat((int)ppuVar22,(stat *)local_270);
  puVar23 = puVar25;
  ppuVar34 = ppuVar35;
  if (iVar9 < 0) goto LAB_00102c2c;
  local_330 = (undefined **)0x20000;
  if (0 < (int)local_270._56_4_) {
    uVar19 = (ulong)(int)local_270._56_4_;
    uVar3 = 0;
    if (uVar19 != 0) {
      uVar3 = 0x1ffff / uVar19;
    }
    ppuVar14 = (undefined **)(uVar19 + uVar3 * uVar19);
    local_330 = ppuVar14;
    if ((local_270._16_4_ & 0xf000) == 0x8000) goto LAB_001025b0;
  }
LAB_00101eec:
  posix_fadvise((int)ppuVar22,0,0,2);
  ppuVar35 = ppuVar34;
  if (local_2bc == 0x8000) {
    if (((local_270._0_8_ == local_2d0) && (local_270._8_8_ == local_2c8)) &&
       (_Var17 = lseek((int)ppuVar22,0,1), _Var17 < (long)local_270._48_8_)) {
      uVar12 = dcgettext(0,"%s: input file is output file",5);
      uVar13 = FUN_00105014(*(undefined8 *)(puVar23 + 0x1e8));
      error(0,0,uVar12,uVar13);
      local_2f8 = 0;
      goto LAB_001020fc;
    }
    if ((local_2e0 == 0) && ((!bVar5 && (int)ppuVar34 == 0) && !bVar6)) {
      if ((local_270._16_4_ & 0xf000) != 0x8000) goto LAB_00102508;
      ppuVar27 = (undefined **)(puVar23 + 0xe0);
      pcVar11 = (char *)0x0;
      goto LAB_00102a1c;
    }
  }
  else if ((local_2e0 == 0) && ((!bVar5 && (int)ppuVar34 == 0) && !bVar6)) goto LAB_00102508;
  ppuVar27 = (undefined **)(long)local_2d8;
  ppuVar14 = (undefined **)aligned_alloc(ppuVar27,(undefined *)((long)local_330 + 1));
  pcVar11 = (char *)local_330;
  if (ppuVar14 == (undefined **)0x0) goto LAB_00102c28;
  puVar1 = (undefined2 *)((long)ppuVar30 + (long)local_330 * 4);
  local_308 = (undefined *)((long)puVar1 + 0x13);
  if (SCARRY8((long)puVar1,0x13)) goto LAB_00102c28;
  ppuVar27 = (undefined **)aligned_alloc(ppuVar27,local_308);
  if (ppuVar27 == (undefined **)0x0) goto LAB_00102c28;
  ppuVar31 = (undefined **)((long)ppuVar27 + (long)ppuVar30);
  ppuVar33 = (undefined **)((long)ppuVar14 + 1);
  bVar7 = true;
  pcVar11 = (char *)(ulong)*(uint *)(puVar23 + 0x1f8);
  local_2fc = local_328 & (local_2dc ^ 1);
  local_310 = local_30c;
  ppuVar28 = ppuVar14;
  __dest = ppuVar27;
  ppuVar35 = ppuVar30;
  local_340 = ppuVar27;
  local_318 = ppuVar33;
LAB_00101fd0:
  ppuVar30 = ppuVar31;
  unaff_x27 = ppuVar34;
  if (ppuVar31 <= __dest) goto LAB_00102198;
LAB_00101fd8:
  iVar9 = (int)pcVar11;
  ppuVar22 = ppuVar28;
  unaff_x27 = ppuVar34;
  ppuVar30 = ppuVar35;
  if (ppuVar33 <= ppuVar14) goto LAB_001021f8;
LAB_00101fe0:
  local_2ac = 0;
  ppuVar28 = ppuVar22;
  ppuVar29 = __dest;
  ppuVar30 = ppuVar31;
  unaff_x27 = ppuVar34;
  if (bVar7) {
    ppuVar27 = (undefined **)(ulong)*(uint *)(puVar23 + 0x1f0);
    iVar9 = ioctl(*(uint *)(puVar23 + 0x1f0),0x541b,&local_2ac);
    ppuVar30 = ppuVar35;
    if (iVar9 < 0) goto LAB_001023ec;
    goto LAB_001023a0;
  }
LAB_00101fec:
  ppuVar22 = (undefined **)((long)ppuVar29 - (long)local_340);
  if ((0 < (long)ppuVar22) &&
     (ppuVar27 = (undefined **)FUN_001050b4(local_340,ppuVar22), __dest = local_340,
     ppuVar29 = local_340, ppuVar22 != ppuVar27)) goto LAB_001023e8;
  ppuVar27 = (undefined **)(ulong)*(uint *)(puVar23 + 0x1f0);
  ppuVar22 = ppuVar28;
  ppuVar31 = ppuVar30;
LAB_00102004:
  ppuVar30 = ppuVar35;
  uVar32 = SUB84(pcVar11,0);
  lVar15 = FUN_00103144((ulong)ppuVar27 & 0xffffffff,ppuVar22,local_330);
  ppuVar27 = local_340;
  if (lVar15 == -1) {
    piVar18 = __errno_location();
    iVar9 = *piVar18;
    ppuVar35 = (undefined **)((ulong)unaff_x27 & 0xffffffff);
    uVar12 = FUN_00105014(*(undefined8 *)(puVar23 + 0x1e8));
    error(0,iVar9,&DAT_00105230,uVar12);
    pcVar11 = (char *)((long)ppuVar29 - (long)local_340);
    if ((long)pcVar11 < 1) goto LAB_001024c0;
    ppuVar34 = (undefined **)FUN_001050b4(local_340,pcVar11);
    ppuVar28 = local_340;
    __dest = ppuVar29;
    if ((undefined **)pcVar11 != ppuVar34) goto LAB_001023e8;
    local_2f8 = 0;
    local_340 = ppuVar29;
  }
  else {
    if (lVar15 != 0) {
      ppuVar14 = (undefined **)((long)ppuVar22 + lVar15);
      *(undefined1 *)((long)ppuVar22 + lVar15) = 10;
      ppuVar28 = ppuVar22;
      ppuVar33 = local_318;
      goto LAB_00102034;
    }
    ppuVar35 = (undefined **)((ulong)unaff_x27 & 0xffffffff);
    pcVar11 = (char *)((long)ppuVar29 - (long)local_340);
    if ((0 < (long)pcVar11) &&
       (ppuVar34 = (undefined **)FUN_001050b4(local_340,pcVar11), (undefined **)pcVar11 != ppuVar34)
       ) goto code_r0x001025ac;
  }
LAB_001020e4:
  *(undefined4 *)(puVar23 + 0x1f8) = uVar32;
  free(ppuVar27);
  ppuVar34 = ppuVar35;
LAB_001020f4:
  do {
    free(ppuVar22);
LAB_001020fc:
    puVar25 = puVar23;
    if ((local_2d4 != 0) && (iVar9 = close(*(int *)(puVar23 + 0x1f0)), iVar9 < 0)) {
      piVar18 = __errno_location();
      uVar12 = *(undefined8 *)(puVar23 + 0x1e8);
LAB_00102650:
      iVar9 = *piVar18;
      uVar12 = FUN_00105014(uVar12);
      error(0,iVar9,&DAT_00105230,uVar12);
      local_2f8 = 0;
    }
    local_2e8 = local_2e8 + 1;
    if ((int)local_2e8 < param_1) goto LAB_0010211c;
    puVar23 = puVar25 + 0xe0;
    if (((puVar25[0x1fc] & 1) == 0) || (lVar15 = FUN_001050b4(&DAT_00105ad8,1), lVar15 == 1)) {
      if ((local_2c0 == 0) || (iVar9 = close(0), -1 < iVar9)) {
        if (local_68 - *(long *)PTR___stack_chk_guard_0011ffe0 != 0) {
                    /* WARNING: Subroutine does not return */
          __stack_chk_fail(local_2f8 ^ 1,PTR___stack_chk_guard_0011ffe0,0,
                           local_68 - *(long *)PTR___stack_chk_guard_0011ffe0);
        }
        return;
      }
      puVar16 = (uint *)__errno_location();
      pcVar21 = "closing standard input";
      ppuVar35 = ppuVar34;
LAB_001029c4:
      ppuVar22 = (undefined **)(ulong)*puVar16;
      uVar12 = dcgettext(0,pcVar21,5);
      error(1,ppuVar22,uVar12);
      goto LAB_001029e0;
    }
    FUN_00102e84();
LAB_00102b04:
    ppuVar35 = ppuVar34;
    if ((int)pcVar11 == 0) {
LAB_00102508:
      ppuVar27 = (undefined **)(puVar23 + 0xe0);
      __dest = ppuVar30;
      if ((long)ppuVar30 < (long)local_330) {
        __dest = local_330;
      }
      ppuVar22 = (undefined **)aligned_alloc((long)local_2d8,__dest);
      if (ppuVar22 == (undefined **)0x0) goto LAB_00102c28;
      goto LAB_00102544;
    }
    iVar9 = 1;
LAB_00102b0c:
    ppuVar22 = (undefined **)0x0;
    local_2f8 = local_2f8 & 0 < iVar9;
  } while( true );
LAB_00102a1c:
  uVar32 = *(undefined4 *)(puVar23 + 0x1f0);
  if (puVar23[500] == '\0') {
    uname((utsname *)(local_270 + 0x80));
    if ((local_16d == '.') && (local_16e < 0x36)) {
      if (local_16e == 0x35) {
        if (local_16b != '.') goto LAB_00102bb0;
        uVar8 = 1;
        if (local_16c < 0x33) {
          uVar8 = 0xff;
        }
      }
      else {
        uVar8 = 0xff;
      }
    }
    else {
LAB_00102bb0:
      uVar8 = 1;
    }
    puVar23[500] = uVar8;
  }
  if ((char)puVar23[500] < '\x01') {
    piVar18 = __errno_location();
    *piVar18 = 0x26;
LAB_00102b34:
    puVar16 = (uint *)__errno_location();
    uVar10 = *puVar16;
    if ((int)uVar10 < 0x1b) {
      if ((0 < (int)uVar10) && ((0x4440202UL >> ((ulong)uVar10 & 0x3f) & 1) != 0))
      goto LAB_00102508;
    }
    else {
      if (uVar10 == 0x26) goto LAB_00102508;
      if (uVar10 == 0x5f) goto LAB_00102508;
    }
    uVar12 = FUN_00105014(*(undefined8 *)(puVar23 + 0x1e8));
    error(0,(ulong)uVar10,&DAT_00105230,uVar12);
    iVar9 = -1;
    goto LAB_00102b0c;
  }
  lVar15 = copy_file_range(uVar32,0,1,0,0x7fffffffc0000000,0);
  if (lVar15 == -1) goto LAB_00102b34;
  if (lVar15 == 0) goto LAB_00102b04;
  pcVar11 = (char *)0x1;
  goto LAB_00102a1c;
LAB_00102034:
  bVar20 = *(byte *)ppuVar22;
  __dest = ppuVar29;
  ppuVar34 = unaff_x27;
  ppuVar35 = ppuVar30;
  do {
    if (bVar20 == 10) goto LAB_00101fd0;
    ppuVar30 = __dest;
    if ((puVar23[0x1fc] & 1) != 0) {
      ppuVar30 = (undefined **)((long)__dest + 1);
      *(undefined1 *)__dest = 0xd;
      puVar23[0x1fc] = 0;
    }
    if (-1 < (int)pcVar11 && local_328 != 0) {
      FUN_00102de0();
      ppuVar30 = (undefined **)stpcpy((char *)ppuVar30,DAT_001200a8);
    }
    iVar9 = (int)ppuVar34;
    if (bVar5) {
      if (bVar20 < 0x20) goto LAB_001022c0;
      goto LAB_001022a8;
    }
    if (iVar9 == 0 || bVar20 != 9) goto LAB_001020a0;
LAB_00102088:
    bVar20 = *(byte *)ppuVar33;
    ppuVar27 = (undefined **)((long)ppuVar30 + 2);
    *(undefined2 *)ppuVar30 = 0x495e;
    while( true ) {
      ppuVar33 = (undefined **)((long)ppuVar33 + 1);
      ppuVar30 = ppuVar27;
      if (iVar9 != 0 && bVar20 == 9) goto LAB_00102088;
LAB_001020a0:
      if (bVar20 == 10) goto LAB_00102280;
      bVar2 = *(byte *)ppuVar33;
      if ((bVar20 == 0xd) && (local_30c != 0 && bVar2 == 10)) break;
      ppuVar27 = (undefined **)((long)ppuVar30 + 1);
      *(byte *)ppuVar30 = bVar20;
      bVar20 = bVar2;
    }
    if (ppuVar33 == ppuVar14) {
      ppuVar33 = (undefined **)((long)ppuVar33 + 1);
      puVar23[0x1fc] = 1;
      goto LAB_00102280;
    }
    __dest = (undefined **)((long)ppuVar30 + 2);
    *(undefined2 *)ppuVar30 = 0x4d5e;
    ppuVar33 = (undefined **)((long)ppuVar33 + 1);
    pcVar11 = (char *)0xffffffff;
    ppuVar30 = ppuVar31;
    unaff_x27 = ppuVar34;
    if (__dest < ppuVar31) goto LAB_00101fd8;
LAB_00102198:
    iVar9 = (int)pcVar11;
    ppuVar22 = local_340;
    do {
      ppuVar27 = (undefined **)FUN_001050b4(ppuVar22,ppuVar35);
      ppuVar29 = local_340;
      if (ppuVar35 != ppuVar27) goto LAB_001023e8;
      ppuVar22 = (undefined **)((long)ppuVar22 + (long)ppuVar35);
      lVar15 = (long)__dest - (long)ppuVar22;
    } while ((long)ppuVar35 <= lVar15);
    __memmove_chk(local_340,ppuVar22,lVar15,local_308);
    __dest = (undefined **)((long)local_340 + lVar15);
    ppuVar22 = ppuVar28;
    ppuVar31 = ppuVar30;
    ppuVar34 = unaff_x27;
    ppuVar30 = ppuVar35;
    if (ppuVar14 < ppuVar33) goto LAB_00101fe0;
LAB_001021f8:
    ppuVar22 = ppuVar33;
    uVar10 = iVar9 + 1;
    pcVar11 = (char *)(ulong)uVar10;
    ppuVar33 = (undefined **)((long)ppuVar22 + 1);
    if ((int)uVar10 < 1) goto LAB_00102224;
    if ((uVar10 == 1) || (pcVar11 = (char *)0x2, !bVar6)) break;
    bVar20 = *(byte *)ppuVar22;
    ppuVar34 = unaff_x27;
    ppuVar35 = ppuVar30;
  } while( true );
  if (local_2fc != 0) {
    FUN_00102de0();
    __dest = (undefined **)stpcpy((char *)__dest,DAT_001200a8);
  }
LAB_00102224:
  if (local_310 != 0) {
    ppuVar27 = __dest;
    if ((puVar23[0x1fc] & 1) != 0) {
      ppuVar27 = (undefined **)((long)__dest + 2);
      *(undefined2 *)__dest = 0x4d5e;
      puVar23[0x1fc] = 0;
    }
    __dest = (undefined **)((long)ppuVar27 + 1);
    *(undefined1 *)ppuVar27 = 0x24;
  }
  ppuVar29 = (undefined **)((long)__dest + 1);
  *(undefined1 *)__dest = 10;
  goto LAB_00102034;
LAB_001022b8:
  while (ppuVar30 = ppuVar27, ppuVar33 = ppuVar22, 0x1f < bVar20) {
LAB_001022a8:
    if (bVar20 < 0x7f) {
      ppuVar27 = (undefined **)((long)ppuVar30 + 1);
      *(byte *)ppuVar30 = bVar20;
      ppuVar22 = (undefined **)((long)ppuVar33 + 1);
      bVar20 = *(byte *)ppuVar33;
    }
    else if (bVar20 == 0x7f) {
      ppuVar22 = (undefined **)((long)ppuVar33 + 1);
      bVar20 = *(byte *)ppuVar33;
      ppuVar27 = (undefined **)((long)ppuVar30 + 2);
      *(undefined2 *)ppuVar30 = 0x3f5e;
    }
    else {
      *(undefined2 *)ppuVar30 = 0x2d4d;
      if (bVar20 < 0xa0) {
        ppuVar27 = (undefined **)((long)ppuVar30 + 4);
        *(undefined1 *)((long)ppuVar30 + 2) = 0x5e;
        *(byte *)((long)ppuVar30 + 3) = bVar20 - 0x40;
        ppuVar22 = (undefined **)((long)ppuVar33 + 1);
        bVar20 = *(byte *)ppuVar33;
      }
      else if (bVar20 == 0xff) {
        ppuVar22 = (undefined **)((long)ppuVar33 + 1);
        bVar20 = *(byte *)ppuVar33;
        ppuVar27 = (undefined **)((long)ppuVar30 + 4);
        *(undefined2 *)((long)ppuVar30 + 2) = 0x3f5e;
      }
      else {
        ppuVar27 = (undefined **)((long)ppuVar30 + 3);
        *(byte *)((long)ppuVar30 + 2) = bVar20 + 0x80;
        ppuVar22 = (undefined **)((long)ppuVar33 + 1);
        bVar20 = *(byte *)ppuVar33;
      }
    }
  }
LAB_001022c0:
  if (iVar9 == 1 || bVar20 != 9) {
    if (bVar20 == 10) goto LAB_00102280;
    ppuVar27 = (undefined **)((long)ppuVar30 + 2);
    *(undefined1 *)ppuVar30 = 0x5e;
    *(byte *)((long)ppuVar30 + 1) = bVar20 + 0x40;
    ppuVar22 = (undefined **)((long)ppuVar33 + 1);
    bVar20 = *(byte *)ppuVar33;
    goto LAB_001022b8;
  }
  ppuVar22 = (undefined **)((long)ppuVar33 + 1);
  bVar20 = *(byte *)ppuVar33;
  ppuVar27 = (undefined **)((long)ppuVar30 + 1);
  *(undefined1 *)ppuVar30 = 9;
  goto LAB_001022b8;
LAB_00102280:
  pcVar11 = (char *)0xffffffff;
  __dest = ppuVar30;
  goto LAB_00101fd0;
code_r0x001025ac:
  ppuVar14 = (undefined **)FUN_00102e84();
LAB_001025b0:
  ppuVar34 = ppuVar35;
  if (((ulong)((long)ppuVar14 + -1) & (ulong)ppuVar14) != 0) {
    local_330 = (undefined **)(1L << ((ulong)(uint)-(int)LZCOUNT(ppuVar14) & 0x3f));
  }
  goto LAB_00101eec;
LAB_0010211c:
  __file = (byte *)param_2[local_2e8];
  *(byte **)(puVar25 + 0x1e8) = __file;
  local_2d4 = *__file - 0x2d;
  if (local_2d4 != 0) goto LAB_00101e8c;
LAB_0010213c:
  local_2d4 = (uint)__file[1];
  if (local_2d4 != 0) goto LAB_00101e8c;
  ppuVar22 = (undefined **)0x0;
  local_2c0 = 1;
  *(undefined4 *)(puVar25 + 0x1f0) = 0;
  ppuVar35 = ppuVar34;
  goto LAB_00101ea4;
LAB_00102c28:
  FUN_001031c4();
  ppuVar34 = ppuVar35;
LAB_00102c2c:
  piVar18 = __errno_location();
  iVar9 = *piVar18;
  uVar12 = FUN_00105014(*(undefined8 *)(puVar23 + 0x1e8));
  error(0,iVar9,&DAT_00105230,uVar12);
  local_2f8 = 0;
  goto LAB_001020fc;
LAB_00102544:
  pcVar11 = (char *)FUN_00103144(*(undefined4 *)(puVar23 + 0x1f0),ppuVar22,__dest);
  if ((undefined **)pcVar11 == (undefined **)0xffffffffffffffff) goto LAB_001029e0;
  if ((undefined **)pcVar11 == (undefined **)0x0) {
    bVar20 = 1;
    ppuVar34 = ppuVar35;
    goto LAB_00102568;
  }
  ppuVar34 = (undefined **)FUN_001050b4(ppuVar22,pcVar11);
  ppuVar28 = ppuVar27;
  ppuVar29 = local_340;
  if ((undefined **)pcVar11 != ppuVar34) goto LAB_001023e8;
  goto LAB_00102544;
LAB_001029e0:
  puVar16 = (uint *)__errno_location();
  ppuVar34 = ppuVar27 + 0x21;
  ppuVar27 = (undefined **)(ulong)*puVar16;
  uVar12 = FUN_00105014(*ppuVar34);
  error(0,ppuVar27,&DAT_00105230,uVar12);
  bVar20 = 0;
  ppuVar34 = ppuVar35;
LAB_00102568:
  local_2f8 = local_2f8 & bVar20;
  goto LAB_001020f4;
LAB_001023e8:
  local_340 = ppuVar29;
  FUN_00102e84();
  ppuVar27 = ppuVar22;
  ppuVar22 = ppuVar28;
  ppuVar31 = ppuVar30;
  ppuVar34 = unaff_x27;
  ppuVar30 = ppuVar35;
LAB_001023ec:
  uVar32 = SUB84(pcVar11,0);
  puVar16 = (uint *)__errno_location();
  uVar10 = *puVar16;
  unaff_x27 = (undefined **)(ulong)uVar10;
  if ((int)uVar10 < 0x1a) {
    if ((0x12 < (int)uVar10) && ((0x2480000UL >> ((ulong)unaff_x27 & 0x3f) & 1) != 0))
    goto LAB_00102410;
  }
  else if ((uVar10 == 0x26) || (uVar10 == 0x5f)) goto LAB_00102410;
  ppuVar35 = (undefined **)((ulong)ppuVar34 & 0xffffffff);
  pcVar11 = (char *)dcgettext(0,"cannot do ioctl on %s",5);
  local_270._128_4_ = 4;
  uStack_1bc = 0;
  uStack_1e4 = 0;
  local_1e0 = 0;
  uStack_1ec = 0;
  uStack_1e8 = 0;
  uStack_1d4 = 0;
  local_1d0 = 0;
  uStack_1dc = 0;
  uStack_1d8 = 0;
  uStack_2a0 = 0;
  local_2a8 = 4;
  uStack_290 = 0;
  uStack_298 = 0;
  uStack_1c4 = 0;
  local_1c0 = 0;
  uStack_1cc = 0;
  uStack_1c8 = 0;
  uStack_280 = 0;
  local_288 = 0;
  local_278 = 0;
  uVar12 = FUN_00104d70(*(undefined8 *)(puVar23 + 0x1e8));
  error(0,unaff_x27,pcVar11,uVar12);
  ppuVar27 = local_340;
  ppuVar29 = local_340;
LAB_001024c0:
  local_340 = ppuVar29;
  local_2f8 = 0;
  goto LAB_001020e4;
LAB_00102410:
  bVar7 = false;
  ppuVar29 = __dest;
  ppuVar35 = ppuVar30;
LAB_001023a0:
  ppuVar28 = ppuVar22;
  ppuVar30 = ppuVar31;
  unaff_x27 = ppuVar34;
  if (local_2ac == 0) goto LAB_00101fec;
  goto LAB_00102004;
LAB_00101dcc:
  local_328 = 1;
  goto LAB_00101c00;
}

