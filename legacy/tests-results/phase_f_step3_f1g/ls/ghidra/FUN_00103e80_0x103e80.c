
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00103e80(int param_1,undefined8 *param_2)

{
  char *__s1;
  char cVar1;
  byte bVar2;
  undefined4 uVar3;
  bool bVar4;
  undefined1 uVar5;
  byte bVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  char *pcVar11;
  undefined8 *puVar12;
  int *piVar13;
  ulong uVar14;
  uint *puVar15;
  long lVar16;
  void *pvVar17;
  float *pfVar18;
  undefined8 uVar19;
  undefined8 uVar20;
  size_t sVar21;
  _IO_FILE *p_Var22;
  undefined **ppuVar23;
  long lVar24;
  undefined4 *puVar25;
  byte *pbVar26;
  long extraout_x12;
  undefined8 extraout_x13;
  long *__ptr;
  undefined *puVar27;
  undefined8 uVar28;
  char *pcVar29;
  size_t *psVar30;
  void *pvVar31;
  size_t *psVar32;
  int *piVar33;
  size_t *psVar34;
  ulong uVar35;
  size_t sVar36;
  void *pvVar37;
  float fVar38;
  float fVar39;
  float fVar40;
  undefined1 auVar41 [16];
  char *local_150;
  int local_140;
  uint local_138;
  long local_130;
  int local_128;
  int local_104;
  char *local_100;
  long *local_f8;
  undefined8 local_f0;
  undefined8 uStack_e8;
  undefined2 local_d8;
  undefined1 local_d6;
  char local_d0 [104];
  long local_68;
  
  pcVar29 = (char *)*param_2;
  local_68 = *(long *)PTR___stack_chk_guard_0013ffd0;
  if (pcVar29 == (char *)0x0) {
    fwrite("A NULL argv[0] was passed through an exec system call.\n",1,0x37,
           *(FILE **)PTR_stderr_0013ffa0);
                    /* WARNING: Subroutine does not return */
    abort();
  }
  pcVar11 = strrchr(pcVar29,0x2f);
  if ((((pcVar11 != (char *)0x0) && (__s1 = pcVar11 + 1, 6 < (long)__s1 - (long)pcVar29)) &&
      (iVar7 = strncmp(pcVar11 + -6,"/.libs/",7), iVar7 == 0)) &&
     (iVar7 = strncmp(__s1,"lt-",3), pcVar29 = __s1, iVar7 == 0)) {
    *(char **)PTR_program_invocation_short_name_0013fff0 = pcVar11 + 4;
    pcVar29 = pcVar11 + 4;
  }
  *(char **)PTR_program_invocation_name_0013ff88 = pcVar29;
  uVar35 = 0xffffffffffffffff;
  DAT_00140ed8 = pcVar29;
  setlocale(6,"");
  bindtextdomain("coreutils","/usr/share/locale");
  textdomain("coreutils");
  DAT_00140080 = 2;
  FUN_00118160(FUN_0010a9b0);
  piVar33 = &local_104;
  DAT_00141348 = (long *)0x0;
  local_150 = (char *)0x0;
  DAT_001413b1 = 1;
  uVar10 = 0xffffffff;
  local_140 = -1;
  local_138 = 0xffffffff;
  local_130 = -1;
  local_128 = -1;
  bVar4 = false;
  DAT_00140f40 = 0;
  DAT_001412e8 = _UNK_0011cd48;
  DAT_001412e0 = _DAT_0011cd40;
LAB_00103fd8:
  local_104 = -1;
  iVar7 = getopt_long(param_1,param_2,"abcdfghiklmnopqrstuvw:xABCDFGHI:LNQRST:UXZ1",
                      &PTR_DAT_0013f1a8,piVar33);
  puVar27 = PTR_optarg_0013ffa8;
  if (iVar7 != -1) {
    switch(iVar7) {
    case 0x31:
      uVar10 = (uint)(uVar10 != 0);
      break;
    case 0x41:
      DAT_00141418 = 1;
      break;
    case 0x42:
      FUN_0010d4a0(&DAT_0011bf40);
      FUN_0010d4a0(&DAT_0011bf48);
      break;
    case 0x43:
      uVar10 = 2;
      break;
    case 0x44:
      DAT_00141290 = 1;
      break;
    case 0x46:
      if (*(long *)PTR_optarg_0013ffa8 != 0) {
        lVar16 = FUN_00112820("--classify",*(long *)PTR_optarg_0013ffa8,&PTR_s_always_0013f750,
                              &DAT_00118550,FUN_001087a4);
        if ((*(int *)(&DAT_00118550 + lVar16 * 4) != 1) &&
           ((*(int *)(&DAT_00118550 + lVar16 * 4) != 2 ||
            (uVar14 = FUN_00108d80(), (uVar14 & 1) == 0)))) break;
      }
      DAT_00140f80 = 3;
      break;
    case 0x47:
      DAT_001400cb = 0;
      break;
    case 0x48:
      DAT_0014142c = 2;
      break;
    case 0x49:
      FUN_0010d4a0(*(undefined8 *)PTR_optarg_0013ffa8);
      break;
    case 0x4c:
      DAT_0014142c = 4;
      break;
    case 0x4e:
      local_138 = 0;
      break;
    case 0x51:
      local_138 = 5;
      break;
    case 0x52:
      DAT_001413b0 = 1;
      break;
    case 0x54:
      uVar20 = *(undefined8 *)PTR_optarg_0013ffa8;
      uVar19 = dcgettext(0,"invalid tab size",5);
      iVar7 = FUN_001109d0(uVar20,0,&local_f0,"");
      if (iVar7 == 0) {
        local_130 = local_f0;
        if (-1 < local_f0) break;
        piVar13 = __errno_location();
        *piVar13 = 0x4b;
      }
      else {
        local_150 = (char *)CONCAT44(local_150._4_4_,iVar7);
        piVar13 = __errno_location();
        if (iVar7 == 1) {
          *piVar13 = 0x4b;
        }
        else if (iVar7 == 3) {
          *piVar13 = 0;
        }
      }
      puVar15 = (uint *)__errno_location();
      uVar8 = *puVar15;
      if (uVar8 == 0x16) {
        uVar8 = 0;
      }
      param_2 = (undefined8 *)(ulong)uVar8;
      uVar20 = FUN_00112640(0,uVar20,&DAT_00140088);
      error(2,param_2,"%s: %s",uVar19,uVar20);
    case 0x53:
      local_140 = 3;
      break;
    case 0x55:
      local_140 = 6;
      break;
    case 0x58:
      local_140 = 1;
      break;
    case 0x5a:
      DAT_0014101c = 1;
      break;
    case 0x61:
      DAT_00141418 = 2;
      break;
    case 0x62:
      local_138 = 7;
      break;
    case 99:
      DAT_00140f34 = 1;
      break;
    case 100:
      DAT_00141428 = 1;
      break;
    case 0x66:
      if (uVar10 == 0) {
        uVar10 = 0xffffffff;
      }
      DAT_001413b2 = 0;
      DAT_00141418 = 2;
      local_140 = 6;
      DAT_00140f28 = 0;
      DAT_00141291 = 0;
      break;
    case 0x67:
      uVar10 = 0;
      DAT_001400ca = 0;
      break;
    case 0x68:
      DAT_00141018 = 0xb0;
      goto LAB_00104158;
    case 0x69:
      DAT_00140f30 = 1;
      break;
    case 0x6b:
      bVar4 = true;
      break;
    case 0x6c:
      uVar10 = 0;
      break;
    case 0x6d:
      uVar10 = 4;
      break;
    case 0x6e:
      uVar10 = 0;
      DAT_001412c0 = 1;
      break;
    case 0x6f:
      uVar10 = 0;
      DAT_001400cb = 0;
      break;
    case 0x70:
      DAT_00140f80 = 1;
      break;
    case 0x71:
      local_128 = 1;
      break;
    case 0x72:
      DAT_00141179 = 1;
      break;
    case 0x73:
      DAT_00140f28 = 1;
      break;
    case 0x74:
      local_140 = 5;
      break;
    case 0x75:
      DAT_00140f34 = 2;
      break;
    case 0x76:
      goto code_r0x001044b8;
    case 0x77:
      uVar35 = FUN_00107f74(*(undefined8 *)PTR_optarg_0013ffa8);
      if ((long)uVar35 < 0) {
        param_2 = (undefined8 *)dcgettext(0,"invalid line width",5);
        uVar19 = FUN_00108b10(*(undefined8 *)puVar27);
        error(2,0,"%s: %s",param_2,uVar19);
code_r0x001044b8:
        local_140 = 4;
      }
      break;
    case 0x78:
      uVar10 = 3;
      break;
    case 0x100:
      DAT_00140f38 = 1;
      break;
    case 0x101:
      uVar8 = FUN_00110ea0(*(undefined8 *)PTR_optarg_0013ffa8);
      uVar3 = DAT_00140080;
      if (uVar8 != 0) {
        uVar19 = *(undefined8 *)puVar27;
        if (uVar8 < 4) {
          pcVar29 = "invalid suffix in %s%s argument \'%s\'";
          if (uVar8 == 1) {
            pcVar29 = "%s%s argument \'%s\' too large";
          }
        }
        else {
          if (uVar8 != 4) goto LAB_00105c8c;
          pcVar29 = "invalid %s%s argument \'%s\'";
        }
        if (local_104 < 0) {
          puVar27 = &UNK_0011be58 + -(long)local_104;
          pcVar11 = local_d0;
          local_d0[0] = '\0';
          local_d0[1] = '\0';
        }
        else {
          puVar27 = &UNK_0011be58;
          pcVar11 = (&PTR_DAT_0013f1a8)[(long)local_104 * 4];
        }
        uVar20 = dcgettext(0,pcVar29,5);
        error(uVar3,0,uVar20,puVar27,pcVar11,uVar19);
LAB_00105c8c:
                    /* WARNING: Subroutine does not return */
        abort();
      }
      DAT_001400d0 = DAT_00141010;
      DAT_001412d0 = DAT_00141018;
      break;
    case 0x102:
      if (*(long *)PTR_optarg_0013ffa8 == 0) {
LAB_001043d8:
        bVar6 = 1;
      }
      else {
        lVar16 = FUN_00112820("--color",*(long *)PTR_optarg_0013ffa8,&PTR_s_always_0013f750,
                              &DAT_00118550,FUN_001087a4);
        if (*(int *)(&DAT_00118550 + lVar16 * 4) == 1) goto LAB_001043d8;
        if (*(int *)(&DAT_00118550 + lVar16 * 4) == 2) {
          bVar6 = FUN_00108d80();
        }
        else {
          bVar6 = 0;
        }
      }
      DAT_00141291 = bVar6 & 1;
      break;
    case 0x103:
      DAT_0014142c = 3;
      break;
    case 0x104:
      DAT_00140f80 = 2;
      break;
    case 0x105:
      lVar16 = FUN_00112820("--format",*(undefined8 *)PTR_optarg_0013ffa8,&PTR_s_verbose_0013f830,
                            &DAT_001185d0,FUN_001087a4);
      uVar10 = *(uint *)(&DAT_001185d0 + lVar16 * 4);
      break;
    case 0x106:
      local_150 = "full-iso";
      uVar10 = 0;
      break;
    case 0x107:
      DAT_00141178 = 1;
      break;
    case 0x108:
      puVar12 = malloc(0x10);
      if (puVar12 == (undefined8 *)0x0) goto LAB_00105514;
      *puVar12 = *(undefined8 *)PTR_optarg_0013ffa8;
      puVar12[1] = DAT_00141420;
      DAT_00141420 = puVar12;
      break;
    case 0x109:
      if (*(long *)PTR_optarg_0013ffa8 == 0) {
LAB_00104288:
        bVar6 = 1;
      }
      else {
        lVar16 = FUN_00112820("--hyperlink",*(long *)PTR_optarg_0013ffa8,&PTR_s_always_0013f750,
                              &DAT_00118550,FUN_001087a4);
        if (*(int *)(&DAT_00118550 + lVar16 * 4) == 1) goto LAB_00104288;
        if (*(int *)(&DAT_00118550 + lVar16 * 4) == 2) {
          bVar6 = FUN_00108d80();
        }
        else {
          bVar6 = 0;
        }
      }
      DAT_001413b2 = bVar6 & 1;
      break;
    case 0x10a:
      lVar16 = FUN_00112820("--indicator-style",*(undefined8 *)PTR_optarg_0013ffa8,&PTR_DAT_0013f870
                            ,&DAT_001185f0,FUN_001087a4);
      DAT_00140f80 = *(uint *)(&DAT_001185f0 + lVar16 * 4);
      break;
    case 0x10b:
      lVar16 = FUN_00112820("--quoting-style",*(undefined8 *)PTR_optarg_0013ffa8,
                            &PTR_s_literal_0013f8a0,&DAT_00118600,FUN_001087a4);
      local_138 = *(uint *)(&DAT_00118600 + lVar16 * 4);
      break;
    case 0x10c:
      local_128 = 0;
      break;
    case 0x10d:
      DAT_00141018 = 0x90;
LAB_00104158:
      DAT_001400d0 = 1;
      DAT_00141010 = 1;
      DAT_001412d0 = DAT_00141018;
      break;
    case 0x10e:
      lVar16 = FUN_00112820("--sort",*(undefined8 *)PTR_optarg_0013ffa8,&PTR_DAT_0013f7a0,
                            &DAT_00118580,FUN_001087a4);
      local_140 = *(int *)(&DAT_00118580 + lVar16 * 4);
      break;
    case 0x10f:
      lVar16 = FUN_00112820("--time",*(undefined8 *)PTR_optarg_0013ffa8,&PTR_s_atime_0013f7e0,
                            &DAT_001185a0,FUN_001087a4);
      DAT_00140f34 = *(int *)(&DAT_001185a0 + lVar16 * 4);
      break;
    case 0x110:
      local_150 = *(char **)PTR_optarg_0013ffa8;
      break;
    case 0x111:
      goto code_r0x00104054;
    case -3:
      uVar28 = *(undefined8 *)PTR_stdout_0013ffc0;
      uVar19 = FUN_00107b10("Richard M. Stallman");
      uVar20 = FUN_00107b10("David MacKenzie");
      FUN_001103e4(uVar28,&DAT_00119c00,"GNU coreutils",&DAT_0011c000,uVar19,uVar20,0);
                    /* WARNING: Subroutine does not return */
      exit(0);
    case -2:
                    /* WARNING: Subroutine does not return */
      FUN_00108000(0);
    default:
      goto code_r0x0010400c;
    }
    goto LAB_00103fd8;
  }
  if (DAT_00141010 == 0) {
    pcVar29 = getenv("LS_BLOCK_SIZE");
    FUN_00110ea0();
    if ((pcVar29 != (char *)0x0) || (pcVar29 = getenv("BLOCK_SIZE"), pcVar29 != (char *)0x0)) {
      DAT_001400d0 = DAT_00141010;
      DAT_001412d0 = DAT_00141018;
    }
    if (bVar4) {
      DAT_00141010 = 0x400;
      DAT_00141018 = 0;
    }
  }
  if ((int)uVar10 < 0) {
    uVar10 = FUN_00108d80();
    uVar10 = (uVar10 & 0xff) + 1;
  }
  DAT_00140f2c = uVar10;
  if ((uVar10 - 2 < 3) || ((DAT_00141291 & 1) != 0)) {
    if ((long)uVar35 < 0) {
      uVar35 = FUN_00108d80();
      if (((uVar35 & 1) != 0) && (iVar7 = ioctl(1,0x5413,&local_f0), -1 < iVar7)) {
        uVar35 = (ulong)local_f0._2_2_;
        if (local_f0._2_2_ != 0) goto LAB_00104934;
      }
      pcVar29 = getenv("COLUMNS");
      if ((pcVar29 == (char *)0x0) || (*pcVar29 == '\0')) goto LAB_00104ee8;
      uVar35 = FUN_00107f74();
      if ((long)uVar35 < 0) {
        uVar19 = dcgettext(0,"ignoring invalid width in environment variable COLUMNS: %s",5);
        uVar20 = FUN_00108b10(pcVar29);
        uVar35 = 0x50;
        error(0,0,uVar19,uVar20);
      }
    }
  }
  else if ((long)uVar35 < 0) {
LAB_00104ee8:
    uVar35 = 0x50;
  }
LAB_00104934:
  DAT_001412a0 = uVar35 / 3;
  if (uVar35 != DAT_001412a0 * 3) {
    DAT_001412a0 = DAT_001412a0 + 1;
  }
  DAT_00141020 = uVar35;
  if (DAT_00140f2c - 2 < 3) {
    if (local_130 < 0) {
      DAT_001402b8 = 8;
      pcVar29 = getenv("TABSIZE");
      if (pcVar29 != (char *)0x0) {
        iVar7 = FUN_001109d0(pcVar29,0,&local_f0,"");
        if (iVar7 == 0) {
          DAT_001402b8 = local_f0;
        }
        else {
          uVar19 = dcgettext(0,"ignoring invalid tab size in environment variable TABSIZE: %s",5);
          uVar20 = FUN_00108b10(pcVar29);
          error(0,0,uVar19,uVar20);
        }
      }
    }
    else {
      DAT_001402b8 = local_130;
    }
  }
  uVar5 = local_128 != 0;
  if (local_128 < 0) {
    uVar5 = FUN_00108d80();
  }
  DAT_00141430 = uVar5;
  if ((int)local_138 < 0) {
    pcVar29 = getenv("QUOTING_STYLE");
    if (pcVar29 != (char *)0x0) {
      iVar7 = FUN_001108c4(pcVar29,&PTR_s_literal_0013f8a0,&DAT_00118600);
      if (iVar7 < 0) {
        uVar19 = dcgettext(0,"ignoring invalid value of environment variable QUOTING_STYLE: %s",5);
        uVar20 = FUN_00108b10(pcVar29);
        error(0,0,uVar19,uVar20);
      }
      else {
        local_138 = *(uint *)(&DAT_00118600 + (long)iVar7 * 4);
        if (-1 < (int)local_138) goto LAB_00104990;
      }
    }
    uVar35 = FUN_00108d80();
    if ((uVar35 & 1) != 0) {
      local_138 = 3;
      goto LAB_00104990;
    }
  }
  else {
LAB_00104990:
    DAT_00140f48 = local_138;
  }
  uVar8 = DAT_00140f48;
  uVar10 = DAT_00140f2c;
  if (((DAT_00140f2c == 0) || ((DAT_00140f2c - 2 < 2 && (DAT_00141020 != 0)))) && (DAT_00140f48 < 7)
     ) {
    if ((0x4aUL >> ((ulong)DAT_00140f48 & 0x3f) & 1) == 0) {
      DAT_00141280 = 0;
      puVar15 = (uint *)FUN_00110864();
      DAT_00140f20 = puVar15;
    }
    else {
      DAT_00141280 = 1;
      puVar15 = (uint *)FUN_00110864();
      DAT_00140f20 = puVar15;
    }
  }
  else {
    DAT_00141280 = 0;
    puVar15 = (uint *)FUN_00110864();
    DAT_00140f20 = puVar15;
    if (uVar8 == 7) {
      puVar15[3] = puVar15[3] | 1;
    }
  }
  if (1 < DAT_00140f80) {
    pbVar26 = &DAT_0011c110 + (DAT_00140f80 - 2);
    bVar6 = (&DAT_0011c110)[DAT_00140f80 - 2];
    while (bVar6 != 0) {
      bVar2 = bVar6 >> 5;
      uVar8 = (uint)bVar6;
      pbVar26 = pbVar26 + 1;
      bVar6 = *pbVar26;
      puVar15[(ulong)bVar2 + 2] =
           (~(puVar15[(ulong)bVar2 + 2] >> (ulong)(uVar8 & 0x1f)) & 1) << (ulong)(uVar8 & 0x1f) ^
           puVar15[(ulong)bVar2 + 2];
    }
  }
  DAT_00141410 = FUN_00110864();
  bVar6 = DAT_001400cc;
  DAT_00141290 = uVar10 == 0 & (DAT_001413b2 ^ 1) & DAT_00141290;
  *(uint *)(DAT_00141410 + 0xc) =
       (~(*(uint *)(DAT_00141410 + 0xc) >> 0x1a) & 1) << 0x1a ^ *(uint *)(DAT_00141410 + 0xc);
  if (bVar6 < DAT_00141290) {
    uVar19 = dcgettext(0,"--dired and --zero are incompatible",5);
    error(2,0,uVar19);
    goto LAB_00105c04;
  }
  if (local_140 < 0) {
    if (uVar10 == 0) {
      local_140 = 0;
    }
    else {
      local_140 = 5;
      if (2 < DAT_00140f34 - 1U) {
        local_140 = 0;
      }
    }
  }
  DAT_00140f3c = local_140;
  if (uVar10 == 0) {
    if ((local_150 == (char *)0x0) && (local_150 = getenv("TIME_STYLE"), local_150 == (char *)0x0))
    {
      local_150 = "locale";
    }
    else {
      while (iVar7 = strncmp(local_150,"posix-",6), iVar7 == 0) {
        uVar35 = FUN_0010ba30(2);
        if ((uVar35 & 1) == 0) goto LAB_00104ae0;
        local_150 = local_150 + 6;
      }
    }
    if (*local_150 == '+') {
      pcVar29 = local_150 + 1;
      ppuVar23 = (undefined **)strchr(pcVar29,10);
      pcVar11 = pcVar29;
      if (ppuVar23 != (undefined **)0x0) {
        pcVar11 = strchr((char *)((long)ppuVar23 + 1),10);
        if (pcVar11 != (char *)0x0) {
          uVar19 = dcgettext(0,"invalid time style format %s",5);
          uVar20 = FUN_00108b10(pcVar29);
          lVar16 = error(2,0,uVar19,uVar20);
          goto LAB_00105b60;
        }
        *(undefined1 *)ppuVar23 = 0;
        pcVar11 = (char *)((long)ppuVar23 + 1);
      }
      PTR_DAT_001400e0 = pcVar29;
      PTR_DAT_001400e8 = pcVar11;
      FUN_00107570();
    }
    else {
      ppuVar23 = &PTR_s_full_iso_0013f180;
      lVar16 = FUN_001108c4(local_150,&PTR_s_full_iso_0013f180,&DAT_00118630);
      if (lVar16 < 0) {
LAB_00105b60:
        puVar27 = PTR_stderr_0013ffa0;
        FUN_0010b310("time style",local_150,lVar16);
        pcVar29 = (char *)dcgettext(0,"Valid arguments are:\n",5);
        fputs_unlocked(pcVar29,*(FILE **)puVar27);
        for (; *ppuVar23 != (undefined *)0x0; ppuVar23 = ppuVar23 + 1) {
          __fprintf_chk(*(undefined8 *)puVar27,2,"  - [posix-]%s\n");
        }
        pcVar29 = (char *)dcgettext(0,"  - +FORMAT (e.g., +%H:%M) for a \'date\'-style format\n",5);
        fputs_unlocked(pcVar29,*(FILE **)puVar27);
code_r0x0010400c:
                    /* WARNING: Subroutine does not return */
        FUN_00108000(2);
      }
      if (lVar16 == 2) {
        PTR_DAT_001400e0 = s__Y__m__d_0011c208;
        PTR_DAT_001400e8 = s__m__d__H__M_0011c218;
        FUN_00107570();
      }
      else if (lVar16 < 3) {
        if (lVar16 == 0) {
          PTR_DAT_001400e0 = s__Y__m__d__H__M__S__N__z_0011c1e0;
          PTR_DAT_001400e8 = s__Y__m__d__H__M__S__N__z_0011c1e0;
          FUN_00107570();
        }
        else {
          PTR_DAT_001400e0 = s__Y__m__d__H__M_0011c1f8;
          PTR_DAT_001400e8 = s__Y__m__d__H__M_0011c1f8;
LAB_001055bc:
          FUN_00107570();
        }
      }
      else {
        if ((lVar16 != 3) || (uVar35 = FUN_0010ba30(2), (uVar35 & 1) == 0)) goto LAB_001055bc;
        PTR_DAT_001400e0 = (undefined *)dcgettext(0,PTR_DAT_001400e0,2);
        PTR_DAT_001400e8 = (undefined *)dcgettext(0,PTR_DAT_001400e8,2);
        FUN_00107570();
      }
    }
  }
LAB_00104ae0:
  bVar6 = DAT_00141291;
  uVar10 = *(uint *)PTR_optind_0013ffb8;
  local_150 = (char *)(ulong)uVar10;
  if ((DAT_00141291 & 1) != 0) {
    local_100 = getenv("LS_COLORS");
    local_150._0_4_ = uVar10;
    if ((local_100 != (char *)0x0) && (*local_100 != '\0')) {
      local_d8 = DAT_0011c3b8;
      local_d6 = DAT_0011c3ba;
      DAT_00141438 = (long *)FUN_0010f784();
      local_f8 = DAT_00141438;
LAB_00105154:
      do {
        while( true ) {
          pcVar29 = local_100;
          cVar1 = *local_100;
          if (cVar1 == '*') {
            psVar32 = malloc(0x30);
            if (psVar32 == (size_t *)0x0) goto LAB_00105514;
            local_100 = pcVar29 + 1;
            psVar32[1] = (size_t)local_f8;
            *(undefined1 *)(psVar32 + 4) = 0;
            psVar32[5] = (size_t)DAT_00141298;
            DAT_00141298 = psVar32;
            auVar41 = FUN_00105fe0(&local_f8,&local_100,1,psVar32);
            pcVar29 = local_100;
            if (((auVar41._0_8_ & 1) != 0) && (pcVar29 = local_100 + 1, *local_100 == '='))
            goto code_r0x001058bc;
            goto LAB_001052c8;
          }
          if (cVar1 != ':') break;
          local_100 = local_100 + 1;
        }
        if (cVar1 == '\0') {
          psVar32 = DAT_00141298;
          if (DAT_00141298 != (size_t *)0x0) {
            while (psVar30 = psVar32, psVar32 = (size_t *)psVar30[5], psVar32 != (size_t *)0x0) {
              bVar2 = 0;
              psVar34 = psVar32;
              do {
                sVar36 = *psVar34;
                if ((sVar36 != 0xffffffffffffffff) && (sVar36 == *psVar30)) {
                  pvVar17 = (void *)psVar34[1];
                  pvVar31 = (void *)psVar30[1];
                  iVar7 = memcmp(pvVar31,pvVar17,sVar36);
                  if (iVar7 == 0) {
                    *psVar34 = 0xffffffffffffffff;
                  }
                  else if ((sVar36 == 0 || pvVar31 == pvVar17) ||
                          (iVar7 = FUN_00107090(pvVar31,pvVar17,sVar36), iVar7 == 0)) {
                    if (((bVar2 & 1) == 0) &&
                       ((psVar30[2] != psVar34[2] ||
                        (iVar7 = memcmp((void *)psVar30[3],(void *)psVar34[3],psVar30[2]),
                        iVar7 != 0)))) {
                      *(undefined1 *)(psVar30 + 4) = 1;
                      *(undefined1 *)(psVar34 + 4) = 1;
                    }
                    else {
                      *psVar34 = 0xffffffffffffffff;
                      bVar2 = bVar6;
                    }
                  }
                }
                psVar34 = (size_t *)psVar34[5];
              } while (psVar34 != (size_t *)0x0);
            }
          }
          piVar33 = (int *)&DAT_00140000;
          goto LAB_001058f0;
        }
        local_d8 = CONCAT11(local_d8._1_1_,cVar1);
        pcVar29 = local_100 + 1;
        if (local_100[1] == '\0') goto LAB_001052c8;
        local_d8 = CONCAT11(local_100[1],cVar1);
        pcVar29 = local_100 + 3;
        if (local_100[2] != '=') goto LAB_001052c8;
        lVar16 = 0;
        pcVar29 = "lc";
        local_100 = local_100 + 3;
        while (iVar7 = strcmp((char *)&local_d8,pcVar29), iVar7 != 0) {
          lVar16 = lVar16 + 1;
          pcVar29 = *(char **)(&UNK_0013f900 + lVar16 * 8);
          if (pcVar29 == (char *)0x0) goto LAB_00105294;
        }
        (&PTR_DAT_001400f8)[(long)(int)lVar16 * 2] = (undefined *)local_f8;
        uVar35 = FUN_00105fe0(&local_f8,&local_100,0);
      } while ((uVar35 & 1) != 0);
LAB_00105294:
      uVar19 = dcgettext(0,"unrecognized prefix: %s",5);
      uVar20 = FUN_00108b10(&local_d8);
      error(0,0,uVar19,uVar20);
      pcVar29 = local_100;
      goto LAB_001052c8;
    }
    pcVar29 = getenv("COLORTERM");
    if ((pcVar29 == (char *)0x0) || (*pcVar29 == '\0')) {
      pcVar29 = getenv("TERM");
      if ((pcVar29 != (char *)0x0) && (*pcVar29 != '\0')) {
        for (pcVar11 = "# Configuration file for dircolors, a utility to help you set the";
            pcVar11 + -0x118660 < (char *)0x1569; pcVar11 = pcVar11 + sVar36 + 1) {
          iVar7 = strncmp(pcVar11,"TERM ",5);
          if ((iVar7 == 0) && (iVar7 = fnmatch(pcVar11 + 5,pcVar29,0), iVar7 == 0))
          goto LAB_001057b4;
          sVar36 = strlen(pcVar11);
        }
      }
      DAT_00141291 = 0;
    }
    goto LAB_001057b4;
  }
LAB_00104b00:
  local_150._0_4_ = uVar10;
  if ((DAT_00141178 & 1) != 0) {
LAB_00104b0c:
    DAT_00141440 = 1;
  }
LAB_00104b18:
  if (DAT_0014142c == 0) {
    if (((DAT_00141428 & 1) == 0) && (DAT_00140f80 != 3)) {
      DAT_0014142c = 3;
      if (DAT_00140f2c == 0) {
        DAT_0014142c = 1;
      }
    }
    else {
      DAT_0014142c = 1;
    }
  }
  if ((DAT_001413b0 & 1) != 0) {
    DAT_00141350 = FUN_00114c30(0x1e,FUN_00105ee0,FUN_00105f04,FUN_00105fc0);
    if (DAT_00141350 == 0) goto LAB_00105514;
    _obstack_begin(&DAT_00141358,0,0,PTR_malloc_0013ffb0,PTR_free_0013ffe0);
  }
  getenv("TZ");
  DAT_001412d8 = FUN_00107ec0();
  if (((((DAT_00140f3c - 3U & 0xfffffffd) == 0) || (DAT_00140f2c == 0)) || ((DAT_0014101c & 1) != 0)
      ) || ((DAT_00140f28 & 1) != 0)) {
    DAT_00141441 = 1;
    bVar6 = 0;
  }
  else {
    DAT_00141441 = 0;
    if ((((DAT_001413b0 & 1) != 0) || ((DAT_00141291 & 1) != 0)) ||
       (bVar6 = DAT_00141178, DAT_00140f80 != 0)) {
      bVar6 = 1;
    }
  }
  DAT_00141442 = bVar6 & 1;
  if ((DAT_00141290 & 1) != 0) {
    _obstack_begin(&DAT_001412f0,0,0,PTR_malloc_0013ffb0,PTR_free_0013ffe0);
    _obstack_begin(&DAT_001413b8,0,0,PTR_malloc_0013ffb0,PTR_free_0013ffe0);
  }
  pcVar29 = DAT_00141288;
  if ((DAT_001413b2 & 1) != 0) {
    uVar35 = 0;
    do {
      for (; iVar7 = (int)uVar35, uVar35 < 0x5b; uVar35 = uVar35 + 1) {
        if ((uVar35 < 0x41) && (9 < iVar7 - 0x30U)) goto LAB_00105344;
LAB_00105400:
        (&DAT_00141180)[uVar35] = (&DAT_00141180)[uVar35] | 1;
      }
      bVar4 = true;
      if (0x19 < iVar7 - 0x61U) {
LAB_00105344:
        if (iVar7 == 0x7e || iVar7 == 0x2d) goto LAB_00105400;
        bVar4 = iVar7 == 0x2e || iVar7 == 0x5f;
      }
      (&DAT_00141180)[uVar35] = bVar4 | (&DAT_00141180)[uVar35];
      uVar35 = uVar35 + 1;
    } while (uVar35 != 0x100);
    local_f0 = 100;
    puVar15 = (uint *)__errno_location();
    pcVar29 = (char *)0x0;
    pcVar11 = local_d0;
    while( true ) {
      sVar36 = local_f0 - 1;
      pcVar11[sVar36] = '\0';
      *puVar15 = 0;
      iVar7 = gethostname(pcVar11,sVar36);
      if (iVar7 == 0) {
        sVar21 = strlen(pcVar11);
        sVar21 = sVar21 + 1;
        if ((long)sVar21 < (long)sVar36) {
          if (pcVar29 != (char *)0x0) goto LAB_00104bf4;
          pvVar17 = malloc(sVar21);
          if (pvVar17 == (void *)0x0) goto LAB_00105514;
          pcVar29 = (char *)__memcpy_chk(pvVar17,pcVar11,sVar21);
          goto LAB_00104bf4;
        }
        *puVar15 = 0;
      }
      free(pcVar29);
      if ((0x24 < *puVar15) || ((-0x1000401002 >> ((ulong)*puVar15 & 0x3f) & 1U) != 0)) break;
      pcVar29 = (char *)FUN_0010f680(0,&local_f0,1,0xffffffffffffffff);
      pcVar11 = pcVar29;
    }
    DAT_00141288 = "";
    pcVar29 = DAT_00141288;
  }
LAB_00104bf4:
  DAT_00141288 = pcVar29;
  DAT_00141448 = 100;
  lVar16 = reallocarray(0,100,0xc0);
  if (lVar16 == 0) {
LAB_00105514:
                    /* WARNING: Subroutine does not return */
    FUN_0010d454();
  }
  DAT_00140ee0 = 0;
  DAT_00141038 = lVar16;
  FUN_00108de0();
  if ((int)(param_1 - (uint)local_150) < 1) {
    if ((DAT_00141428 & 1) == 0) {
      FUN_0010f7d0(&DAT_0011bc28,0,1);
    }
    else {
      FUN_00115420(&DAT_0011bc28,3,1,"");
    }
    if (DAT_00140ee0 != 0) goto LAB_00105618;
LAB_00104ecc:
    if (DAT_00141348 == (long *)0x0) goto LAB_00104d64;
    if (DAT_00141348[3] == 0) {
      DAT_001413b1 = 0;
    }
  }
  else {
    lVar16 = (long)(int)(uint)local_150;
    do {
      puVar12 = param_2 + lVar16;
      lVar16 = lVar16 + 1;
      FUN_00115420(*puVar12,0,1,"");
    } while ((int)lVar16 < param_1);
    if (DAT_00140ee0 == 0) {
LAB_00104c6c:
      if ((int)(param_1 - (uint)local_150) < 2) goto LAB_00104ecc;
LAB_00104c7c:
      if (DAT_00141348 == (long *)0x0) goto LAB_00104d64;
    }
    else {
LAB_00105618:
      FUN_0010d4f0();
      if ((DAT_00141428 & 1) == 0) {
        FUN_0010f860(0,1);
      }
      if (DAT_00140ee0 == 0) goto LAB_00104c6c;
      FUN_0010f220();
      if (DAT_00141348 == (long *)0x0) goto LAB_00104d64;
      p_Var22 = *(_IO_FILE **)PTR_stdout_0013ffc0;
      DAT_001402c0 = DAT_001402c0 + 1;
      pcVar29 = p_Var22->_IO_write_ptr;
      if (p_Var22->_IO_write_end <= pcVar29) {
        __overflow(p_Var22,10);
        goto LAB_00104c7c;
      }
      p_Var22->_IO_write_ptr = pcVar29 + 1;
      *pcVar29 = '\n';
    }
  }
  __ptr = DAT_00141348;
  do {
    while( true ) {
      lVar16 = DAT_00141350;
      DAT_00141348 = (long *)__ptr[3];
      if ((DAT_00141350 == 0) || (*__ptr != 0)) break;
      if ((ulong)(DAT_00141370 - DAT_00141368) < 0x10) {
                    /* WARNING: Subroutine does not return */
        __assert_fail("dev_ino_size <= __extension__ ({ struct obstack const *__o = (&dev_ino_obstack); (size_t) (__o->next_free - __o->object_base); })"
                      ,"src/ls.c",0x41e,"dev_ino_pop");
      }
      uStack_e8 = *(undefined8 *)(DAT_00141370 + -8);
      local_f0 = *(long *)(DAT_00141370 + -0x10);
      DAT_00141370 = DAT_00141370 + -0x10;
      pvVar17 = (void *)FUN_00108820(DAT_00141350,&local_f0,&local_f8,1);
      if (pvVar17 == (void *)0x0) {
                    /* WARNING: Subroutine does not return */
        __assert_fail("found","src/ls.c",0x70d,"main");
      }
      lVar24 = *local_f8;
      *(long *)(lVar16 + 0x20) = *(long *)(lVar16 + 0x20) + -1;
      if (lVar24 == 0) {
        fVar39 = (float)*(ulong *)(lVar16 + 0x10);
        fVar38 = **(float **)(lVar16 + 0x28);
        uVar35 = *(long *)(lVar16 + 0x18) - 1;
        *(ulong *)(lVar16 + 0x18) = uVar35;
        fVar40 = (float)uVar35;
        if (fVar40 < fVar39 * fVar38) {
          FUN_0010bb04(lVar16);
          pfVar18 = *(float **)(lVar16 + 0x28);
          if (fVar40 < fVar39 * *pfVar18) {
            fVar39 = fVar39 * pfVar18[1];
            if (((uint)pfVar18[4] & 1) == 0) {
              fVar39 = fVar39 * pfVar18[2];
            }
            uVar35 = FUN_0010a6e0(lVar16,(long)fVar39);
            if ((uVar35 & 1) == 0) {
              pvVar31 = *(void **)(lVar16 + 0x48);
              while (pvVar31 != (void *)0x0) {
                pvVar37 = *(void **)((long)pvVar31 + 8);
                free(pvVar31);
                pvVar31 = pvVar37;
              }
              *(undefined8 *)(lVar16 + 0x48) = 0;
            }
          }
        }
      }
      free(pvVar17);
      free((void *)*__ptr);
      free((void *)__ptr[1]);
      free(__ptr);
      __ptr = DAT_00141348;
      if (DAT_00141348 == (long *)0x0) goto LAB_00104d64;
    }
    FUN_0010fc40(*__ptr,__ptr[1],(char)__ptr[2]);
    free((void *)*__ptr);
    free((void *)__ptr[1]);
    free(__ptr);
    DAT_001413b1 = 1;
    __ptr = DAT_00141348;
  } while (DAT_00141348 != (long *)0x0);
LAB_00104d64:
  if (((DAT_00141291 & 1) != 0) && ((DAT_00140f84 & 1) != 0)) {
    if ((DAT_001400f0 != 2) ||
       (((*(short *)PTR_DAT_001400f8 != 0x5b1b || (DAT_00140100 != 1)) || (*PTR_DAT_00140108 != 'm')
        ))) {
      FUN_0010b000(&DAT_001400f0);
      FUN_0010b000(&DAT_00140100);
    }
    piVar33 = &DAT_00118470;
    fflush_unlocked(*(FILE **)PTR_stdout_0013ffc0);
    do {
      iVar7 = *piVar33;
      iVar9 = sigismember((sigset_t *)&DAT_00140f90,iVar7);
      if (iVar9 != 0) {
        signal(iVar7,(__sighandler_t)0x0);
      }
      piVar33 = piVar33 + 1;
      iVar7 = DAT_001402b4;
    } while (piVar33 != (int *)&DAT_001184a0);
    for (; iVar7 != 0; iVar7 = iVar7 + -1) {
      raise(0x13);
    }
    if (DAT_001402b0 != 0) {
      raise(DAT_001402b0);
    }
  }
  if ((DAT_00141290 & 1) != 0) {
    FUN_00107470("//DIRED//",&DAT_001412f0);
    FUN_00107470("//SUBDIRED//",&DAT_001413b8);
    puVar15 = DAT_00140f20;
    if (DAT_00140f20 == (uint *)0x0) {
      puVar15 = &DAT_00140f48;
    }
    __printf_chk(2,"//DIRED-OPTIONS// --quoting-style=%s\n",(&PTR_s_literal_0013f8a0)[*puVar15]);
  }
  if (DAT_00141350 != 0) {
    if (*(long *)(DAT_00141350 + 0x20) != 0) {
                    /* WARNING: Subroutine does not return */
      __assert_fail("hash_get_n_entries (active_dir_set) == 0","src/ls.c",0x741,"main");
    }
    FUN_0010bbf0();
  }
  if (local_68 - *(long *)PTR___stack_chk_guard_0013ffd0 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(DAT_00140f40,PTR___stack_chk_guard_0013ffd0,0,
                   local_68 - *(long *)PTR___stack_chk_guard_0013ffd0);
code_r0x00104054:
  local_138 = 0;
  uVar10 = (uint)(uVar10 != 0);
  local_128 = 0;
  DAT_001400cc = 0;
  DAT_00141291 = 0;
  goto LAB_00103fd8;
code_r0x001058bc:
  *(long **)(extraout_x12 + 0x18) = local_f8;
  local_100 = local_100 + 1;
  uVar35 = FUN_00105fe0(extraout_x13,auVar41._8_8_,0,extraout_x12 + 0x10);
  pcVar29 = local_100;
  if ((uVar35 & 1) == 0) goto LAB_001052c8;
  goto LAB_00105154;
LAB_001052c8:
  local_100 = pcVar29;
  piVar33 = (int *)&DAT_00140000;
  uVar19 = dcgettext(0,"unparsable value for LS_COLORS environment variable",5);
  error(0,0,uVar19);
  free(DAT_00141438);
  psVar32 = DAT_00141298;
  while (psVar32 != (size_t *)0x0) {
    psVar30 = (size_t *)psVar32[5];
    free(psVar32);
    psVar32 = psVar30;
  }
LAB_00105c04:
  DAT_00141291 = 0;
LAB_001058f0:
  if ((*(long *)(piVar33 + 0x58) == 6) &&
     (iVar7 = strncmp(*(char **)(piVar33 + 0x5a),"target",6), iVar7 == 0)) {
    DAT_00141292 = 1;
  }
LAB_001057b4:
  puVar25 = &DAT_001402b0;
  uVar10 = (uint)local_150;
  if ((DAT_00141291 & 1) == 0) goto LAB_00104b00;
  DAT_001402b8 = 0;
  if (((((DAT_00141178 & 1) != 0) || (uVar35 = FUN_0010aca0(0xd), (uVar35 & 1) != 0)) ||
      ((uVar35 = FUN_0010aca0(0xe), (uVar35 & 1) != 0 &&
       ((*(byte *)((long)puVar25 + 0xfe2) & 1) != 0)))) ||
     ((uVar35 = FUN_0010aca0(0xc), (uVar35 & 1) != 0 && (DAT_00140f2c == 0)))) goto LAB_00104b0c;
  goto LAB_00104b18;
}

