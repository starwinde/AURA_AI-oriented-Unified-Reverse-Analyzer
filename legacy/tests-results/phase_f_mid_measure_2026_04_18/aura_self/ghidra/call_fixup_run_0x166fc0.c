
undefined8 call_fixup_run(long param_1)

{
  uint uVar1;
  long lVar2;
  int iVar3;
  void *__ptr;
  size_t __n;
  undefined8 *in_x4;
  char *__s1;
  undefined8 *puVar4;
  undefined8 *puVar5;
  ulong uVar6;
  long lVar7;
  char *__s2;
  
  if (param_1 == 0) {
    return 1;
  }
  __ptr = calloc(0x1e,0x10);
  if (__ptr == (void *)0x0) {
    return 2;
  }
  if (*(uint *)(param_1 + 0x30) != 0) {
    puVar4 = *(undefined8 **)(param_1 + 0x28);
    puVar5 = puVar4 + (ulong)*(uint *)(param_1 + 0x30) * 5;
    uVar6 = 0;
    do {
      __s1 = (char *)*puVar4;
      if ((__s1 != (char *)0x0) && (*__s1 != '\0')) {
        lVar7 = 0;
        do {
          __s2 = (&s_builtin_rules)[lVar7 * 2];
          iVar3 = strcmp(__s1,__s2);
          if (iVar3 == 0) {
LAB_00167090:
            iVar3 = (&DAT_005dfc20)[lVar7 * 4];
            if (iVar3 != 0) {
              lVar7 = uVar6 * 0x10;
              uVar1 = (int)uVar6 + 1;
              uVar6 = (ulong)uVar1;
              *(char **)((long)__ptr + lVar7) = __s1;
              *(int *)((long)__ptr + lVar7 + 8) = iVar3;
              if (0x1d < uVar1) goto LAB_001670c8;
            }
            break;
          }
          __n = strlen(__s2);
          lVar2 = lVar7 + 1;
          iVar3 = strncmp(__s1,__s2,__n);
          if ((iVar3 == 0) && ((__s1[__n] & 0xbfU) == 0)) goto LAB_00167090;
          lVar7 = lVar2;
        } while (lVar2 != 0x1e);
      }
      puVar4 = puVar4 + 5;
    } while (puVar4 != puVar5);
    if ((int)uVar6 != 0) {
LAB_001670c8:
      puVar4 = malloc(0x10);
      if (puVar4 == (undefined8 *)0x0) {
        free(__ptr);
        return 2;
      }
      *puVar4 = __ptr;
      *(int *)(puVar4 + 1) = (int)uVar6;
      *(undefined4 *)((long)puVar4 + 0xc) = 0x1e;
      *in_x4 = puVar4;
      return 0;
    }
  }
  free(__ptr);
  return 1;
}

