
void collect_callback_entries_isra_0
               (long param_1,long param_2,ulong param_3,undefined8 *param_4,uint *param_5,
               uint *param_6)

{
  ulong uVar1;
  ulong uVar2;
  int iVar3;
  undefined8 *puVar4;
  char *pcVar5;
  ulong *puVar6;
  undefined8 *puVar7;
  uint uVar8;
  ulong *puVar9;
  char *pcVar10;
  ulong uVar11;
  char *__s1;
  long *plVar12;
  char *pcVar13;
  long local_178;
  ulong local_170;
  char acStack_168 [256];
  long local_68;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if ((param_3 == 0 || param_1 == 0) || param_2 == 0) {
LAB_0016b360:
    if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    return;
  }
  pcVar10 = (char *)(param_2 + 0x60);
  uVar11 = 0;
LAB_0016b128:
  iVar3 = strcmp(pcVar10 + -0x40,"call");
  if ((iVar3 == 0) ||
     (((pcVar10[-0x40] == 'b' && (pcVar10[-0x3f] == 'l')) && (pcVar10[-0x3e] == '\0')))) {
    local_178 = 0;
    iVar3 = __isoc99_sscanf(pcVar10,"0x%lx",&local_178);
joined_r0x0016b114:
    if ((iVar3 == 1) && (*(uint *)(param_1 + 0x30) != 0)) {
      puVar4 = *(undefined8 **)(param_1 + 0x28);
      puVar7 = puVar4 + (ulong)*(uint *)(param_1 + 0x30) * 5;
      do {
        if (puVar4[2] == local_178) {
          __s1 = (char *)*puVar4;
          if (__s1 != (char *)0x0) {
            plVar12 = (long *)&s_callback_registrars;
            pcVar13 = "atexit";
            goto LAB_0016b1d4;
          }
          break;
        }
        puVar4 = puVar4 + 5;
      } while (puVar4 != puVar7);
    }
  }
  else {
    iVar3 = strcmp(pcVar10 + -0x40,"blr");
    if (iVar3 == 0) {
      local_178 = 0;
      iVar3 = __isoc99_sscanf(pcVar10,"0x%lx",&local_178);
      goto joined_r0x0016b114;
    }
  }
  goto LAB_0016b118;
  while (pcVar13 = (char *)*plVar12, pcVar13 != (char *)0x0) {
LAB_0016b1d4:
    plVar12 = plVar12 + 1;
    iVar3 = strcmp(__s1,pcVar13);
    if (iVar3 == 0) {
      uVar1 = uVar11;
      if (uVar11 < 5) {
        uVar1 = 5;
      }
      if (uVar1 - 5 < uVar11) {
        pcVar13 = (char *)(param_2 + uVar1 * 0xe0 + -0x400);
        goto LAB_0016b228;
      }
      break;
    }
  }
LAB_0016b118:
  uVar11 = uVar11 + 1;
  pcVar10 = pcVar10 + 0xe0;
  if (param_3 <= uVar11) goto LAB_0016b360;
  goto LAB_0016b128;
LAB_0016b228:
  local_170 = 0;
  pcVar5 = strstr(pcVar13,"0x");
  if (((pcVar5 != (char *)0x0) && (iVar3 = __isoc99_sscanf(pcVar5,"0x%lx",&local_170), iVar3 == 1))
     && ((local_170 != 0 && (*(uint *)(param_1 + 0x20) != 0)))) {
    puVar9 = (ulong *)(*(long *)(param_1 + 0x18) + 8);
    puVar6 = puVar9 + (ulong)*(uint *)(param_1 + 0x20) * 7;
    do {
      if (((((uint)puVar9[5] >> 2 & 1) != 0) && (*puVar9 <= local_170)) &&
         (local_170 < *puVar9 + puVar9[2])) {
        __snprintf_chk(acStack_168,0x100,2,0x100,"callback_%s_0x%lx",__s1);
        uVar1 = local_170;
        uVar8 = *param_5;
        puVar9 = (ulong *)*param_4;
        if (uVar8 == 0) goto LAB_0016b300;
        puVar6 = puVar9;
        goto LAB_0016b2e8;
      }
      puVar9 = puVar9 + 7;
    } while (puVar9 != puVar6);
  }
  goto LAB_0016b21c;
  while (puVar6 = puVar6 + 3, puVar9 + (ulong)uVar8 * 3 != puVar6) {
LAB_0016b2e8:
    if (local_170 == *puVar6) goto LAB_0016b21c;
  }
LAB_0016b300:
  if (*param_6 <= uVar8) {
    uVar8 = *param_6 << 1;
    if (uVar8 < 0x20) {
      uVar8 = 0x20;
    }
    puVar9 = realloc(puVar9,(ulong)uVar8 * 0x18);
    if (puVar9 == (ulong *)0x0) goto LAB_0016b360;
    *param_6 = uVar8;
    *param_4 = puVar9;
    uVar8 = *param_5;
  }
  uVar2 = (ulong)uVar8;
  puVar9[uVar2 * 3] = uVar1;
  pcVar5 = strdup(acStack_168);
  puVar9[uVar2 * 3 + 1] = (ulong)pcVar5;
  *(undefined4 *)(puVar9 + uVar2 * 3 + 2) = 1;
  *param_5 = *param_5 + 1;
LAB_0016b21c:
  pcVar13 = pcVar13 + 0xe0;
  if (pcVar13 == pcVar10) goto LAB_0016b118;
  goto LAB_0016b228;
}

