
undefined8 * xref_build(long param_1,ulong param_2)

{
  uint uVar1;
  char cVar2;
  uint uVar3;
  int iVar4;
  undefined8 *__ptr;
  void *pvVar5;
  char *pcVar6;
  char *pcVar7;
  ulonglong uVar8;
  ulonglong uVar9;
  long lVar10;
  byte *pbVar11;
  undefined8 uVar12;
  byte *__s;
  byte bVar13;
  byte *pbVar14;
  ulong uVar15;
  long lVar16;
  long lVar17;
  byte *local_70;
  long local_68;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  __ptr = calloc(1,0x10);
  if (__ptr != (undefined8 *)0x0) {
    *(undefined4 *)((long)__ptr + 0xc) = 0x100;
    pvVar5 = calloc(0x100,0x18);
    *__ptr = pvVar5;
    if (pvVar5 != (void *)0x0) {
      *(undefined4 *)(__ptr + 1) = 0;
      if (param_1 != 0 && param_2 != 0) {
        __s = (byte *)(param_1 + 0x60);
        uVar15 = 0;
        do {
          while( true ) {
            pbVar14 = __s + -0x40;
            iVar4 = strcmp((char *)pbVar14,"call");
            if (iVar4 != 0) break;
            if ((*__s != 0) && (pcVar6 = strchr((char *)__s,0x5b), pcVar6 == (char *)0x0)) {
              local_70 = (byte *)0x0;
              uVar9 = strtoull((char *)__s,(char **)&local_70,0);
              if ((local_70 != __s) && ((*local_70 & 0xdf) == 0)) {
                uVar1 = *(uint *)(__ptr + 1);
                uVar12 = *(undefined8 *)(__s + -0x60);
                pvVar5 = (void *)*__ptr;
                if (*(uint *)((long)__ptr + 0xc) <= uVar1) {
                  uVar3 = *(uint *)((long)__ptr + 0xc) << 1;
                  if (uVar3 < 0x40) {
                    uVar3 = 0x40;
                  }
                  pvVar5 = realloc(pvVar5,(ulong)uVar3 * 0x18);
                  if (pvVar5 == (void *)0x0) goto LAB_0016ff18;
                  *__ptr = pvVar5;
                  *(uint *)((long)__ptr + 0xc) = uVar3;
                }
                *(uint *)(__ptr + 1) = uVar1 + 1;
                lVar10 = (ulong)uVar1 * 0x18;
                *(undefined8 *)((long)pvVar5 + lVar10) = uVar12;
                *(ulonglong *)((long)pvVar5 + lVar10 + 8) = uVar9;
                *(undefined4 *)((long)pvVar5 + lVar10 + 0x10) = 0;
              }
            }
LAB_0016ff18:
            uVar15 = uVar15 + 1;
            __s = __s + 0xe0;
            if (param_2 <= uVar15) goto LAB_00170070;
          }
          if (__s[-0x40] == 0x6a) {
            if ((*__s != 0) && (pcVar6 = strchr((char *)__s,0x5b), pcVar6 == (char *)0x0)) {
              local_70 = (byte *)0x0;
              uVar9 = strtoull((char *)__s,(char **)&local_70,0);
              if ((local_70 != __s) && ((*local_70 & 0xdf) == 0)) {
                uVar1 = *(uint *)(__ptr + 1);
                uVar12 = *(undefined8 *)(__s + -0x60);
                pvVar5 = (void *)*__ptr;
                if (*(uint *)((long)__ptr + 0xc) <= uVar1) {
                  uVar3 = *(uint *)((long)__ptr + 0xc) << 1;
                  if (uVar3 < 0x40) {
                    uVar3 = 0x40;
                  }
                  pvVar5 = realloc(pvVar5,(ulong)uVar3 * 0x18);
                  if (pvVar5 == (void *)0x0) goto LAB_0016ff18;
                  *__ptr = pvVar5;
                  *(uint *)((long)__ptr + 0xc) = uVar3;
                }
                *(uint *)(__ptr + 1) = uVar1 + 1;
                lVar10 = (ulong)uVar1 * 0x18;
                *(undefined8 *)((long)pvVar5 + lVar10) = uVar12;
                *(ulonglong *)((long)pvVar5 + lVar10 + 8) = uVar9;
                *(undefined4 *)((long)pvVar5 + lVar10 + 0x10) = 1;
              }
            }
            goto LAB_0016ff18;
          }
          iVar4 = strcmp((char *)pbVar14,"lea");
          if (iVar4 == 0) {
            pcVar6 = strstr((char *)__s,"rip");
            if (pcVar6 != (char *)0x0) {
              pcVar7 = pcVar6 + 3;
              cVar2 = pcVar6[3];
              while (cVar2 == ' ') {
                pcVar7 = pcVar7 + 1;
                cVar2 = *pcVar7;
              }
              iVar4 = 1;
              if (cVar2 != '+') {
                if (cVar2 != '-') goto LAB_0016ff18;
                iVar4 = -1;
              }
              pbVar14 = (byte *)(pcVar7 + 1);
              bVar13 = *pbVar14;
              while (bVar13 == 0x20) {
                pbVar14 = pbVar14 + 1;
                bVar13 = *pbVar14;
              }
              local_70 = (byte *)0x0;
              uVar9 = strtoull((char *)pbVar14,(char **)&local_70,0);
              if (local_70 != pbVar14) {
                lVar16 = *(long *)(__s + -0x60);
                lVar10 = *(long *)(__s + -0x48);
                uVar1 = *(uint *)(__ptr + 1);
                pvVar5 = (void *)*__ptr;
                uVar8 = -uVar9;
                if (iVar4 == 1) {
                  uVar8 = uVar9;
                }
                if (*(uint *)((long)__ptr + 0xc) <= uVar1) {
                  uVar3 = *(uint *)((long)__ptr + 0xc) << 1;
                  if (uVar3 < 0x40) {
                    uVar3 = 0x40;
                  }
                  pvVar5 = realloc(pvVar5,(ulong)uVar3 * 0x18);
                  if (pvVar5 == (void *)0x0) goto LAB_0016ff18;
                  *__ptr = pvVar5;
                  *(uint *)((long)__ptr + 0xc) = uVar3;
                }
                *(uint *)(__ptr + 1) = uVar1 + 1;
                lVar17 = (ulong)uVar1 * 0x18;
                *(long *)((long)pvVar5 + lVar17) = lVar16;
                *(ulonglong *)((long)pvVar5 + lVar17 + 8) = lVar16 + lVar10 + uVar8;
                *(undefined4 *)((long)pvVar5 + lVar17 + 0x10) = 2;
              }
            }
            goto LAB_0016ff18;
          }
          iVar4 = strcmp((char *)pbVar14,"mov");
          if ((((iVar4 != 0) && (iVar4 = strcmp((char *)pbVar14,"movabs"), iVar4 != 0)) &&
              (iVar4 = strcmp((char *)pbVar14,"push"), iVar4 != 0)) || (bVar13 = *__s, bVar13 == 0))
          goto LAB_0016ff18;
          pcVar6 = strstr((char *)__s,"rip");
          if (pcVar6 == (char *)0x0) {
            pcVar6 = strrchr((char *)__s,0x2c);
            pbVar14 = __s;
            if (pcVar6 != (char *)0x0) {
              bVar13 = pcVar6[1];
              pbVar14 = (byte *)(pcVar6 + 1);
            }
            while (bVar13 == 0x20) {
              pbVar14 = pbVar14 + 1;
              bVar13 = *pbVar14;
            }
            if (bVar13 != 0x5b && bVar13 != 0x25) {
              if (((byte)(bVar13 + 0x9f) < 0x1a) &&
                 (pbVar11 = pbVar14, (byte)(pbVar14[1] + 0x9f) < 0x1a)) {
                do {
                  bVar13 = pbVar11[1];
                  pbVar11 = pbVar11 + 1;
                } while ((byte)(bVar13 + 0x9f) < 0x1a);
                if (((bVar13 & 0xdf) == 0) || (bVar13 == 0x5d)) goto LAB_0016ff18;
              }
              local_70 = (byte *)0x0;
              uVar9 = strtoull((char *)pbVar14,(char **)&local_70,0);
              if ((local_70 != pbVar14) &&
                 ((*local_70 == 0x5d || (*local_70 & 0xdf) == 0 && (0xfff < uVar9)))) {
                lVar10 = *(long *)(__s + -0x60);
                goto LAB_00170028;
              }
            }
            goto LAB_0016ff18;
          }
          pcVar7 = pcVar6 + 3;
          cVar2 = pcVar6[3];
          while (cVar2 == ' ') {
            pcVar7 = pcVar7 + 1;
            cVar2 = *pcVar7;
          }
          iVar4 = 1;
          if (cVar2 != '+') {
            if (cVar2 != '-') goto LAB_0016ff18;
            iVar4 = -1;
          }
          pbVar14 = (byte *)(pcVar7 + 1);
          bVar13 = *pbVar14;
          while (bVar13 == 0x20) {
            pbVar14 = pbVar14 + 1;
            bVar13 = *pbVar14;
          }
          local_70 = (byte *)0x0;
          uVar8 = strtoull((char *)pbVar14,(char **)&local_70,0);
          if (pbVar14 == local_70) goto LAB_0016ff18;
          lVar10 = *(long *)(__s + -0x60);
          uVar9 = -uVar8;
          if (iVar4 == 1) {
            uVar9 = uVar8;
          }
          uVar9 = lVar10 + *(long *)(__s + -0x48) + uVar9;
LAB_00170028:
          uVar1 = *(uint *)(__ptr + 1);
          pvVar5 = (void *)*__ptr;
          if (*(uint *)((long)__ptr + 0xc) <= uVar1) {
            uVar3 = *(uint *)((long)__ptr + 0xc) << 1;
            if (uVar3 < 0x40) {
              uVar3 = 0x40;
            }
            pvVar5 = realloc(pvVar5,(ulong)uVar3 * 0x18);
            if (pvVar5 == (void *)0x0) goto LAB_0016ff18;
            *__ptr = pvVar5;
            *(uint *)((long)__ptr + 0xc) = uVar3;
          }
          uVar15 = uVar15 + 1;
          lVar16 = (ulong)uVar1 * 0x18;
          *(uint *)(__ptr + 1) = uVar1 + 1;
          __s = __s + 0xe0;
          *(long *)((long)pvVar5 + lVar16) = lVar10;
          *(ulonglong *)((long)pvVar5 + lVar16 + 8) = uVar9;
          *(undefined4 *)((long)pvVar5 + lVar16 + 0x10) = 2;
        } while (uVar15 < param_2);
LAB_00170070:
        if (1 < *(uint *)(__ptr + 1)) {
          qsort((void *)*__ptr,(ulong)*(uint *)(__ptr + 1),0x18,compare_xref_by_to);
        }
      }
      goto LAB_00170084;
    }
    free(__ptr);
  }
  __ptr = (undefined8 *)0x0;
LAB_00170084:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                     local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return __ptr;
}

