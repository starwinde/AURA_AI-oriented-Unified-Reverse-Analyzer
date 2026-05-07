
void FUN_00107570(void)

{
  bool bVar1;
  ulong uVar2;
  char cVar3;
  ushort uVar4;
  char cVar5;
  int iVar6;
  uint uVar8;
  char *pcVar9;
  byte *__s;
  ushort **ppuVar10;
  size_t sVar11;
  size_t sVar12;
  ulong uVar13;
  undefined1 *puVar14;
  ulong uVar16;
  long lVar17;
  ulong uVar18;
  undefined *puVar19;
  undefined1 *puVar20;
  undefined *puVar21;
  byte *__ptr;
  ulong uVar22;
  undefined1 *puVar23;
  wchar_t *pwVar24;
  long lVar25;
  undefined1 *puVar26;
  ulong local_6c0;
  wchar_t *local_6b8;
  ulong local_6b0;
  nl_item local_6a8;
  long alStack_680 [3];
  undefined1 local_668 [127];
  undefined1 auStack_5e9 [793];
  undefined8 local_2d0;
  long local_68;
  wchar_t wVar7;
  undefined1 *puVar15;
  
  local_2d0 = 0;
  lVar17 = 1;
  local_68 = *(long *)PTR___stack_chk_guard_0013ffd0;
  while( true ) {
    pcVar9 = *(char **)(&DAT_001400d8 + lVar17 * 2);
    cVar5 = *pcVar9;
    while (cVar5 != '\0') {
      cVar3 = pcVar9[1];
      if (cVar5 == '%') {
        if (cVar3 == '%') {
          cVar3 = pcVar9[2];
          pcVar9 = pcVar9 + 1;
        }
        else if (cVar3 == 'b') {
          alStack_680[lVar17] = (long)pcVar9;
          if (lVar17 == 1) goto LAB_001078d4;
          goto LAB_00107608;
        }
      }
      pcVar9 = pcVar9 + 1;
      cVar5 = cVar3;
    }
    alStack_680[lVar17] = 0;
    if (lVar17 != 1) break;
LAB_001078d4:
    lVar17 = 2;
  }
LAB_00107608:
  if ((alStack_680[1] != 0) || (alStack_680[2] != 0)) {
    uVar22 = 0xc;
    do {
      local_6c0 = 0x600;
      local_6b0 = 0;
      local_6a8 = 0x2000e;
      puVar20 = local_668;
      puVar26 = auStack_5e9;
      do {
        __s = (byte *)nl_langinfo(local_6a8);
        pcVar9 = strchr((char *)__s,0x25);
        if (pcVar9 != (char *)0x0) goto LAB_00107960;
        ppuVar10 = __ctype_b_loc();
        uVar4 = (*ppuVar10)[*__s];
        sVar11 = strlen((char *)__s);
        sVar12 = __ctype_get_mb_cur_max();
        local_6b8 = (wchar_t *)0x0;
        __ptr = (byte *)0x0;
        uVar13 = sVar11;
        uVar16 = local_6c0;
        if (sVar12 < 2) {
joined_r0x00107650:
          uVar18 = uVar22;
          sVar12 = uVar22;
          if (uVar13 <= uVar22) goto LAB_00107850;
LAB_0010765c:
          if ((uVar4 & 0x800) != 0) {
            lVar17 = 0;
            uVar13 = 0x7f;
            puVar23 = puVar20;
            goto LAB_00107670;
          }
          lVar17 = 0;
LAB_001078ec:
          *puVar20 = 0;
          uVar16 = sVar12;
          if (0x7f < sVar12) {
            uVar16 = 0x7f;
          }
          puVar23 = (undefined1 *)__mempcpy_chk(puVar20,__s,uVar16,local_6c0);
          if (lVar17 == 0 || puVar26 <= puVar23) goto LAB_00107688;
          puVar15 = puVar23;
          do {
            puVar14 = puVar15 + 1;
            *puVar15 = 0x20;
            puVar15 = puVar14;
          } while (puVar23 + lVar17 != puVar14 && puVar14 < puVar26);
          *puVar14 = 0;
          free(local_6b8);
          free(__ptr);
          uVar16 = sVar12 + lVar17;
        }
        else {
          sVar12 = mbstowcs((wchar_t *)0x0,(char *)__s,0);
          if (sVar12 == 0xffffffffffffffff) goto LAB_00107960;
          uVar18 = sVar12 + 1;
          local_6b8 = malloc(uVar18 * 4);
          if (local_6b8 == (wchar_t *)0x0) goto LAB_00107960;
          lVar17 = __mbstowcs_chk(local_6b8,__s,uVar18,uVar18 & 0x3fffffffffffffff);
          if (lVar17 == 0) goto joined_r0x00107650;
          local_6b8[sVar12] = L'\0';
          wVar7 = *local_6b8;
          if (wVar7 != L'\0') {
            bVar1 = false;
            pwVar24 = local_6b8;
            do {
              iVar6 = iswprint(wVar7);
              if (iVar6 == 0) {
                bVar1 = true;
                *pwVar24 = L'�';
              }
              pwVar24 = pwVar24 + 1;
              wVar7 = *pwVar24;
            } while (wVar7 != L'\0');
            iVar6 = wcswidth(local_6b8,uVar18);
            if (!bVar1) goto LAB_001077c8;
            sVar11 = wcstombs((char *)0x0,local_6b8,0);
LAB_001077d4:
            __s = malloc(sVar11 + 1);
            if (__s != (byte *)0x0) {
              wVar7 = *local_6b8;
              uVar13 = 0;
              pwVar24 = local_6b8;
              while (wVar7 != L'\0') {
                iVar6 = wcwidth(wVar7);
                lVar17 = (long)iVar6;
                if (iVar6 == -1) {
                  lVar17 = 1;
                  *pwVar24 = L'�';
                }
                if (uVar22 < uVar13 + lVar17) break;
                pwVar24 = pwVar24 + 1;
                uVar13 = uVar13 + lVar17;
                wVar7 = *pwVar24;
              }
              *pwVar24 = L'\0';
              sVar11 = wcstombs((char *)__s,local_6b8,sVar11 + 1);
              __ptr = __s;
              goto joined_r0x00107650;
            }
            lVar17 = local_68 - *(long *)PTR___stack_chk_guard_0013ffd0;
            if (lVar17 == 0) {
              free(local_6b8);
              return;
            }
            goto LAB_00107b04;
          }
          iVar6 = wcswidth(local_6b8,uVar18);
LAB_001077c8:
          uVar13 = (ulong)iVar6;
          if (uVar22 < uVar13) goto LAB_001077d4;
LAB_00107850:
          uVar18 = uVar13;
          sVar12 = sVar11;
          if (uVar22 <= uVar13) goto LAB_0010765c;
          lVar17 = uVar22 - uVar13;
          puVar15 = puVar20;
          if ((uVar4 & 0x800) == 0) goto LAB_001078ec;
          do {
            uVar13 = uVar16;
            if (uVar16 < 0x600) {
              uVar13 = 0x600;
            }
            puVar23 = puVar15 + 1;
            *puVar15 = 0x20;
            uVar2 = (uVar13 - uVar16) + 1;
            if (uVar2 < uVar13) {
              uVar2 = uVar13;
            }
            uVar16 = (uVar2 - uVar13) + (uVar16 - 1);
            puVar15 = puVar23;
          } while (puVar20 + (lVar17 - (long)puVar23) != (undefined1 *)0x0 && puVar23 < puVar26);
          uVar13 = (long)puVar26 - (long)puVar23;
LAB_00107670:
          *puVar23 = 0;
          uVar2 = sVar12;
          if (uVar13 < sVar12) {
            uVar2 = uVar13;
          }
          puVar23 = (undefined1 *)__mempcpy_chk(puVar23,__s,uVar2,uVar16);
LAB_00107688:
          *puVar23 = 0;
          free(local_6b8);
          free(__ptr);
          uVar16 = sVar12 + lVar17;
        }
        if (0x7f < uVar16) goto LAB_00107960;
        puVar26 = puVar26 + 0x80;
        puVar20 = puVar20 + 0x80;
        if (local_6b0 < uVar18) {
          local_6b0 = uVar18;
        }
        local_6a8 = local_6a8 + 1;
        local_6c0 = local_6c0 - 0x80;
      } while (local_6c0 != 0);
      bVar1 = local_6b0 < uVar22;
      uVar22 = local_6b0;
    } while (bVar1);
    puVar19 = &DAT_001402d0;
    local_6c0 = 0;
    while( true ) {
      puVar19 = puVar19 + 0x600;
      lVar17 = 0x600;
      lVar25 = alStack_680[local_6c0 + 1];
      puVar21 = (&PTR_DAT_001400e0)[local_6c0];
      do {
        if (lVar25 == 0) {
          uVar8 = snprintf(puVar19 + -lVar17,0x80,"%s",puVar21);
        }
        else {
          if (0x80 < lVar25 - (long)puVar21) goto LAB_00107960;
          uVar8 = __snprintf_chk(puVar19 + -lVar17,0x80,2,lVar17,"%.*s%s%s",
                                 lVar25 - (long)puVar21 & 0xffffffff,puVar21,
                                 (long)&local_68 - lVar17,lVar25 + 2);
        }
        if (0x7f < uVar8) goto LAB_00107960;
        lVar17 = lVar17 + -0x80;
      } while (lVar17 != 0);
      if (local_6c0 != 0) break;
      local_6c0 = 1;
    }
    DAT_00140ed0 = 1;
  }
LAB_00107960:
  lVar17 = local_68 - *(long *)PTR___stack_chk_guard_0013ffd0;
  if (lVar17 == 0) {
    return;
  }
LAB_00107b04:
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_0013ffd0,0,lVar17);
}

