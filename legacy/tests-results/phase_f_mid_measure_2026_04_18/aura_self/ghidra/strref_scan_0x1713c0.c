
long * strref_scan(long param_1)

{
  bool bVar1;
  undefined8 *puVar2;
  long lVar3;
  ulong uVar4;
  undefined8 uVar5;
  long lVar6;
  char cVar7;
  uint uVar8;
  ulong uVar9;
  int iVar10;
  long *__ptr;
  void *pvVar11;
  ulong uVar12;
  char *__s1;
  ulong uVar13;
  uint uVar14;
  uint uVar15;
  long lVar16;
  long lVar17;
  
  if ((param_1 != 0) && (__ptr = calloc(1,0x10), __ptr != (long *)0x0)) {
    *(undefined4 *)((long)__ptr + 0xc) = 0x80;
    pvVar11 = calloc(0x80,0x20);
    *__ptr = (long)pvVar11;
    if (pvVar11 != (void *)0x0) {
      uVar15 = *(uint *)(param_1 + 0x20);
      uVar14 = 0;
      lVar17 = 0;
      if (uVar15 != 0) {
        do {
          puVar2 = (undefined8 *)(*(long *)(param_1 + 0x18) + lVar17);
          __s1 = *(char **)(*(long *)(param_1 + 0x18) + lVar17);
          if (((__s1 != (char *)0x0) &&
              (((((iVar10 = strcmp(__s1,".rodata"), iVar10 == 0 ||
                  (iVar10 = strcmp(__s1,".data"), iVar10 == 0)) ||
                 (iVar10 = strcmp(__s1,".rdata"), iVar10 == 0)) ||
                ((iVar10 = strcmp(__s1,".const"), iVar10 == 0 ||
                 (iVar10 = strcmp(__s1,"__cstring"), iVar10 == 0)))) ||
               (iVar10 = strcmp(__s1,"__const"), iVar10 == 0)))) &&
             ((lVar16 = puVar2[5], lVar16 != 0 && (puVar2[3] != 0)))) {
            uVar12 = 0;
            uVar4 = puVar2[4];
            if (puVar2[4] == 0) {
              uVar4 = puVar2[3];
            }
            do {
              while (uVar9 = uVar12, uVar13 = uVar12, uVar12 < uVar4) {
                do {
                  uVar13 = uVar9;
                  cVar7 = *(char *)(lVar16 + uVar13);
                  bVar1 = (byte)(cVar7 - 0x20U) < 0x5f;
                  if (((!bVar1 && cVar7 != '\t') && (bVar1 || cVar7 != '\n')) && (cVar7 != '\r')) {
                    if ((uVar4 <= uVar13) || (cVar7 != '\0' || uVar13 - uVar12 < 4))
                    goto LAB_001714d4;
                    uVar5 = *puVar2;
                    lVar6 = puVar2[1];
                    uVar15 = *(uint *)(__ptr + 1);
                    if (*(uint *)((long)__ptr + 0xc) <= uVar15) {
                      uVar8 = *(uint *)((long)__ptr + 0xc) << 1;
                      if (uVar8 < 0x40) {
                        uVar8 = 0x40;
                      }
                      pvVar11 = realloc((void *)*__ptr,(ulong)uVar8 << 5);
                      if (pvVar11 == (void *)0x0) goto LAB_001714d4;
                      *__ptr = (long)pvVar11;
                      *(uint *)((long)__ptr + 0xc) = uVar8;
                    }
                    if (uVar15 < 0x1000) {
                      *(uint *)(__ptr + 1) = uVar15 + 1;
                      lVar3 = *__ptr + (ulong)uVar15 * 0x20;
                      *(ulong *)(*__ptr + (ulong)uVar15 * 0x20) = uVar12 + lVar6;
                      *(ulong *)(lVar3 + 8) = lVar16 + uVar12;
                      *(int *)(lVar3 + 0x10) = (int)(uVar13 - uVar12);
                      *(undefined8 *)(lVar3 + 0x18) = uVar5;
                    }
                    goto LAB_001714d4;
                  }
                  uVar9 = uVar13 + 1;
                } while (uVar13 + 1 != uVar4);
                uVar12 = uVar13 + 2;
                if (uVar4 <= uVar12) goto LAB_00171528;
              }
LAB_001714d4:
              uVar12 = uVar13 + 1;
            } while (uVar12 < uVar4);
LAB_00171528:
            uVar15 = *(uint *)(param_1 + 0x20);
          }
          uVar14 = uVar14 + 1;
          lVar17 = lVar17 + 0x38;
        } while (uVar14 < uVar15);
      }
      return __ptr;
    }
    free(__ptr);
  }
  return (long *)0x0;
}

