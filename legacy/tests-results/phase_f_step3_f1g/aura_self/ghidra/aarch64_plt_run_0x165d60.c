
void aarch64_plt_run(long param_1)

{
  uint uVar1;
  ulong uVar2;
  uint uVar3;
  int iVar4;
  undefined8 uVar5;
  void *__ptr;
  long lVar6;
  char *pcVar7;
  void *__ptr_00;
  ulong uVar8;
  undefined8 *in_x4;
  long lVar9;
  undefined8 *puVar10;
  long lVar11;
  undefined8 *puVar12;
  ulong __nmemb;
  uint uVar13;
  ulong uVar14;
  long local_70;
  long local_68;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (((param_1 != 0) && (*(long *)(param_1 + 8) == 0x400000001)) &&
     (*(uint *)(param_1 + 0x20) != 0)) {
    puVar10 = *(undefined8 **)(param_1 + 0x18);
    puVar12 = puVar10 + (ulong)*(uint *)(param_1 + 0x20) * 7;
    do {
      if (((char *)*puVar10 != (char *)0x0) && (iVar4 = strcmp((char *)*puVar10,".plt"), iVar4 == 0)
         ) {
        if ((puVar10[5] != 0) && (0x1f < (ulong)puVar10[3])) {
          local_70 = reloc_parse(param_1);
          __nmemb = (ulong)puVar10[3] >> 4;
          __ptr = calloc(__nmemb,0x18);
          if (__ptr == (void *)0x0) {
            reloc_table_destroy(&local_70);
            goto LAB_00166008;
          }
          lVar11 = 0;
          uVar14 = 0;
          if (__nmemb != 0) goto LAB_00165eac;
          reloc_table_destroy(&local_70);
          goto LAB_00165fc0;
        }
        break;
      }
      puVar10 = puVar10 + 7;
    } while (puVar12 != puVar10);
  }
LAB_00165da0:
  uVar5 = 1;
LAB_00165da4:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(uVar5,PTR___stack_chk_guard_005ffe88,0,
                   local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
LAB_00165eac:
  do {
    lVar9 = puVar10[5] + lVar11;
    uVar13 = *(uint *)(puVar10[5] + lVar11);
    if (((uVar13 & 0x9f00001f) == 0x90000010) &&
       (uVar3 = *(uint *)(lVar9 + 4),
       (uVar3 & 0xffc003ff) == 0xf9400211 && *(int *)(lVar9 + 0xc) == -0x29e0fde0)) {
      lVar9 = puVar10[1];
      uVar1 = (uVar13 & 0xffffe0) >> 3;
      uVar8 = (ulong)(uVar13 >> 0x1d & 3 | uVar1);
      uVar2 = uVar8 | 0xffffffffffe00000;
      if ((uVar1 & 0x100000) == 0) {
        uVar2 = uVar8;
      }
      if (((local_70 == 0) || (lVar6 = reloc_lookup(), lVar6 == 0)) ||
         (*(char **)(lVar6 + 8) == (char *)0x0)) {
        pcVar7 = (char *)0x0;
      }
      else {
        pcVar7 = strdup(*(char **)(lVar6 + 8));
      }
      lVar6 = uVar14 * 0x18;
      uVar14 = (ulong)((int)uVar14 + 1);
      *(long *)((long)__ptr + lVar6) = lVar11 + lVar9;
      *(ulong *)((long)__ptr + lVar6 + 8) =
           (lVar11 + lVar9 & 0xfffffffffffff000U) + ((ulong)(uVar3 >> 10) & 0xfff) * 8 +
           uVar2 * 0x1000;
      *(char **)((long)__ptr + lVar6 + 0x10) = pcVar7;
    }
    lVar11 = lVar11 + 0x10;
  } while (__nmemb * 0x10 - lVar11 != 0);
  reloc_table_destroy(&local_70);
  uVar13 = (uint)uVar14;
  if (uVar13 != 0) {
    __ptr_00 = realloc(__ptr,uVar14 * 0x18);
    if (__ptr_00 == (void *)0x0) {
      __ptr_00 = __ptr;
    }
    puVar10 = malloc(0x10);
    if (puVar10 == (undefined8 *)0x0) {
      lVar11 = 0;
      do {
        lVar9 = lVar11 * 0x18;
        lVar11 = lVar11 + 1;
        free(*(void **)((long)__ptr_00 + lVar9 + 0x10));
      } while ((uint)lVar11 < uVar13);
      free(__ptr_00);
LAB_00166008:
      uVar5 = 2;
    }
    else {
      uVar5 = 0;
      *puVar10 = __ptr_00;
      *(uint *)(puVar10 + 1) = uVar13;
      *in_x4 = puVar10;
    }
    goto LAB_00165da4;
  }
LAB_00165fc0:
  free(__ptr);
  goto LAB_00165da0;
}

