
undefined8 FUN_00114d14(char *param_1)

{
  char *__file;
  char cVar1;
  bool bVar2;
  char cVar3;
  int iVar4;
  char *pcVar5;
  int *piVar6;
  ulong uVar7;
  void *pvVar8;
  size_t sVar9;
  ulong uVar10;
  char *pcVar11;
  char **ppcVar12;
  long *plVar13;
  char *pcVar14;
  undefined8 uVar15;
  undefined1 *__dest;
  size_t __len;
  char *__path;
  long lVar16;
  undefined1 auVar17 [16];
  char *local_d78;
  long *local_d70;
  size_t local_d60;
  int local_d54;
  long local_d48;
  char *local_d40;
  undefined8 local_d38;
  undefined8 uStack_d30;
  undefined1 local_d20 [8] [16];
  char *local_ca0;
  size_t local_c98;
  char local_c90;
  char acStack_c8f [783];
  undefined8 local_980;
  undefined1 *local_890;
  ulong local_888;
  undefined1 auStack_880 [1024];
  char *local_480;
  long local_478;
  char local_470 [1032];
  long local_68;
  
  local_980 = 0;
  local_68 = *(long *)PTR___stack_chk_guard_0013ffd0;
  local_c98 = 0x400;
  local_890 = auStack_880;
  local_888 = 0x400;
  local_480 = local_470;
  local_478 = 0x400;
  local_ca0 = &local_c90;
  if (param_1 == (char *)0x0) {
    piVar6 = __errno_location();
    *piVar6 = 0x16;
  }
  else {
    cVar3 = *param_1;
    if (cVar3 != '\0') {
      if (cVar3 != '/') {
        do {
          __path = local_ca0;
          pcVar5 = getcwd(local_ca0,local_c98);
          if (pcVar5 != (char *)0x0) {
            pcVar5 = rawmemchr(__path,0);
            cVar3 = *param_1;
            if (cVar3 != '\0') goto LAB_00114e18;
            if (__path + 1 < pcVar5) {
              pcVar5 = pcVar5 + -(ulong)(pcVar5[-1] == '/');
            }
            goto LAB_00114ef4;
          }
          piVar6 = __errno_location();
          if (*piVar6 == 0xc) break;
          if (*piVar6 != 0x22) goto LAB_00114db8;
          uVar7 = FUN_0010b8d0(&local_ca0);
        } while ((uVar7 & 1) != 0);
LAB_00115068:
                    /* WARNING: Subroutine does not return */
        FUN_0010d454();
      }
      pcVar5 = acStack_c8f;
      local_c90 = cVar3;
      cVar3 = '/';
      __path = &local_c90;
LAB_00114e18:
      local_d70 = (long *)0x0;
      bVar2 = false;
      local_d54 = 0;
      do {
        while( true ) {
          local_d78 = param_1;
          if (cVar3 == '/') {
            do {
              param_1 = param_1 + 1;
              cVar3 = *param_1;
            } while (cVar3 == '/');
            local_d78 = param_1;
            if (cVar3 == '\0') goto LAB_00114ec8;
          }
          do {
            pcVar11 = param_1;
            param_1 = pcVar11 + 1;
            cVar1 = *param_1;
          } while (cVar1 != '/' && cVar1 != '\0');
          sVar9 = (long)param_1 - (long)local_d78;
          if (sVar9 == 0) goto LAB_00114ec8;
          if (sVar9 == 1) break;
          if ((cVar3 == '.' && sVar9 == 2) && (local_d78[1] == '.')) {
            if ((__path + 1 < pcVar5) && (pcVar5 = pcVar5 + -1, __path < pcVar5)) {
              do {
                if (pcVar5[-1] == '/') break;
                pcVar5 = pcVar5 + -1;
              } while (__path != pcVar5);
            }
            goto LAB_00114ec0;
          }
LAB_00114f2c:
          pcVar14 = pcVar5;
          if (pcVar5[-1] != '/') {
            pcVar14 = pcVar5 + 1;
            *pcVar5 = '/';
          }
          pcVar5 = __path + (local_c98 - (long)pcVar14);
          while (pcVar5 < (char *)(sVar9 + 2)) {
            lVar16 = (long)pcVar14 - (long)__path;
            uVar7 = FUN_0010b970(&local_ca0);
            if ((uVar7 & 1) == 0) goto LAB_00114f88;
            pcVar14 = local_ca0 + lVar16;
            __path = local_ca0;
            pcVar5 = (char *)(local_c98 - lVar16);
          }
          pvVar8 = memcpy(pcVar14,local_d78,sVar9);
          pcVar5 = (char *)((long)pvVar8 + sVar9);
          *(undefined1 *)((long)pvVar8 + sVar9) = 0;
          while (pcVar14 = local_480, __len = local_478 - 1,
                sVar9 = readlink(__path,local_480,__len), (long)__len <= (long)sVar9) {
            uVar7 = FUN_0010b8d0(&local_480);
            if ((uVar7 & 1) == 0) {
                    /* WARNING: Subroutine does not return */
              FUN_0010d454();
            }
          }
          if (-1 < (long)sVar9) {
            if (local_d54 < 0x14) {
              local_d54 = local_d54 + 1;
LAB_001151d8:
              __dest = local_890;
              pcVar14[sVar9] = '\0';
              if (bVar2) {
                local_d48 = (long)param_1 - (long)local_890;
                local_d60 = strlen(param_1);
                uVar7 = sVar9 + local_d60;
                if (local_888 <= uVar7) {
LAB_0011521c:
                  do {
                    uVar10 = FUN_0010b970(&local_890);
                    if ((uVar10 & 1) == 0) {
                    /* WARNING: Subroutine does not return */
                      FUN_0010d454();
                    }
                  } while (local_888 <= uVar7);
                  __dest = local_890;
                  if (!bVar2) goto LAB_00115288;
                }
                param_1 = __dest + local_d48;
              }
              else {
                local_d60 = strlen(param_1);
                uVar7 = local_d60 + sVar9;
                if (local_888 <= uVar7) goto LAB_0011521c;
              }
LAB_00115288:
              memmove(__dest + sVar9,param_1,local_d60 + 1);
              param_1 = memcpy(__dest,pcVar14,sVar9);
              if (*pcVar14 == '/') {
                *__path = '/';
                bVar2 = true;
                cVar3 = *param_1;
                pcVar5 = __path + 1;
              }
              else {
                cVar3 = *param_1;
                pcVar11 = pcVar5;
                if (__path + 1 < pcVar5) {
                  do {
                    pcVar5 = pcVar11 + -1;
                    if (__path == pcVar5) break;
                    pcVar14 = pcVar11 + -2;
                    pcVar11 = pcVar5;
                  } while (*pcVar14 != '/');
                }
                bVar2 = true;
              }
              goto joined_r0x001153f4;
            }
            if (*local_d78 == '\0') goto LAB_001151d8;
            pcVar5[(long)local_d78 - (long)param_1] = '\0';
            __file = ".";
            if (*__path != '\0') {
              __file = __path;
            }
            iVar4 = stat(__file,(stat *)local_d20);
            if (iVar4 == 0) {
              pcVar5[(long)local_d78 - (long)param_1] = *local_d78;
              if ((local_d70 == (long *)0x0) &&
                 (local_d70 = (long *)FUN_00114c30(7,FUN_00107160,FUN_001071b4,FUN_00107220),
                 local_d70 == (long *)0x0)) {
                    /* WARNING: Subroutine does not return */
                FUN_0010d454();
              }
              local_d40 = local_d78;
              auVar17 = NEON_ext(local_d20[0],local_d20[0],8,1);
              uStack_d30 = auVar17._8_8_;
              local_d38 = auVar17._0_8_;
              uVar7 = (*(code *)local_d70[6])(&local_d40,local_d70[2]);
              if ((ulong)local_d70[2] <= uVar7) {
                    /* WARNING: Subroutine does not return */
                abort();
              }
              plVar13 = (long *)(*local_d70 + uVar7 * 0x10);
              ppcVar12 = *(char ***)(*local_d70 + uVar7 * 0x10);
              if (ppcVar12 != (char **)0x0) {
                while ((ppcVar12 != &local_d40 &&
                       (uVar7 = (*(code *)local_d70[7])(&local_d40), (uVar7 & 1) == 0))) {
                  plVar13 = (long *)plVar13[1];
                  if (plVar13 == (long *)0x0) goto LAB_00115300;
                  ppcVar12 = (char **)*plVar13;
                }
                if (*plVar13 != 0) goto LAB_001151a4;
              }
LAB_00115300:
              pcVar11 = malloc(0x18);
              if (pcVar11 == (char *)0x0) {
LAB_00114f88:
                    /* WARNING: Subroutine does not return */
                FUN_0010d454();
              }
              uVar15 = FUN_0010f784(local_d78);
              *(undefined8 *)pcVar11 = uVar15;
              auVar17 = NEON_ext(local_d20[0],local_d20[0],8,1);
              *(long *)(pcVar11 + 0x10) = auVar17._8_8_;
              *(long *)(pcVar11 + 8) = auVar17._0_8_;
              iVar4 = FUN_0010bd00(local_d70,pcVar11,&local_d40);
              if (iVar4 == -1) goto LAB_00114f88;
              if (iVar4 == 0) {
                if (local_d40 == (char *)0x0) goto LAB_00114f88;
                if (local_d40 != pcVar11) {
                  free(*(void **)pcVar11);
                  free(pcVar11);
                }
              }
              goto LAB_001151d8;
            }
            if (local_d70 != (long *)0x0) {
              FUN_0010bbf0(local_d70);
            }
LAB_00114db8:
            uVar15 = 0;
            goto LAB_00114dc0;
          }
LAB_001151a4:
          cVar3 = pcVar11[1];
joined_r0x001153f4:
          if (cVar3 == '\0') goto LAB_00114ec8;
        }
        if (cVar3 != '.') goto LAB_00114f2c;
LAB_00114ec0:
        cVar3 = cVar1;
      } while (cVar1 != '\0');
LAB_00114ec8:
      if ((__path + 1 < pcVar5) && (pcVar5[-1] == '/')) {
        pcVar5 = pcVar5 + -1;
      }
      if (local_d70 != (long *)0x0) {
        FUN_0010bbf0();
      }
LAB_00114ef4:
      *pcVar5 = '\0';
      pcVar5 = pcVar5 + (1 - (long)__path);
      pvVar8 = malloc((size_t)pcVar5);
      if (pvVar8 == (void *)0x0) goto LAB_00115068;
      uVar15 = __memcpy_chk(pvVar8,__path,pcVar5,pcVar5);
LAB_00114dc0:
      if (local_480 != local_470) {
        free(local_480);
      }
      if (local_890 != auStack_880) {
        free(local_890);
      }
      goto LAB_00114fa4;
    }
    piVar6 = __errno_location();
    *piVar6 = 2;
  }
  uVar15 = 0;
LAB_00114fa4:
  if (local_ca0 != &local_c90) {
    free(local_ca0);
  }
  if (local_68 - *(long *)PTR___stack_chk_guard_0013ffd0 == 0) {
    return uVar15;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_0013ffd0,0,
                   local_68 - *(long *)PTR___stack_chk_guard_0013ffd0);
}

