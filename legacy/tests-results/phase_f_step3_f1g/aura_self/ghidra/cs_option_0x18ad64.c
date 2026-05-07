
undefined8 cs_option(uint *param_1,undefined8 param_2,int *param_3)

{
  int iVar1;
  int *piVar2;
  undefined8 uVar3;
  ulong uVar4;
  int *piVar5;
  undefined1 uVar6;
  uint uVar7;
  char *__src;
  int *piVar8;
  
  uVar7 = (uint)param_2;
  if (uVar7 == 4) {
    cs_vsnprintf = *(undefined **)(param_3 + 8);
    cs_mem_free = *(undefined **)(param_3 + 6);
    cs_mem_realloc = *(undefined **)(param_3 + 4);
    cs_mem_calloc = *(undefined **)(param_3 + 2);
    cs_mem_malloc = *(undefined **)param_3;
    return 0;
  }
  if (param_1 == (uint *)0x0) {
    return 4;
  }
  if (uVar7 == 6) {
    if (param_3 == (int *)0x0) {
      return 0;
    }
    uVar3 = *(undefined8 *)(param_3 + 2);
    *(undefined8 *)(param_1 + 0x22) = *(undefined8 *)param_3;
    *(undefined8 *)(param_1 + 0x24) = uVar3;
    *(undefined8 *)(param_1 + 0x26) = *(undefined8 *)(param_3 + 4);
    if (*(long *)(param_1 + 0x22) != 0) {
      return 0;
    }
    *(char **)(param_1 + 0x22) = ".byte";
    return 0;
  }
  if (uVar7 < 7) {
    if (uVar7 == 3) {
      uVar4 = (ulong)*param_1;
      if (((ulong)*(uint *)(&DAT_005ff858 + uVar4 * 0x18) & (ulong)param_3) != 0) {
        return 6;
      }
      goto LAB_0018af04;
    }
    if (uVar7 == 5) {
      *(bool *)(param_1 + 0x20) = param_3 == (int *)0x3;
      if (param_3 != (int *)0x3) {
        return 0;
      }
      if (*(char *)((long)param_1 + 0x81) != '\0') {
        return 0;
      }
      uVar7 = *param_1;
      if (uVar7 < 0xe) {
        if (uVar7 == 0) {
          uVar6 = 2;
          if ((param_1[1] & 0x10) == 0) {
            uVar6 = 4;
          }
          *(undefined1 *)((long)param_1 + 0x81) = uVar6;
          return 0;
        }
        uVar4 = 1L << ((ulong)uVar7 & 0x3f);
        uVar6 = 4;
        if ((((uVar4 & 0x236) == 0) && (uVar6 = 1, (uVar4 & 0x3c08) == 0)) &&
           (uVar6 = 0xff, (uVar4 & 0x1c0) != 0)) {
          uVar6 = 2;
        }
      }
      else {
        if (uVar7 == 0xf) {
          uVar6 = 2;
          if ((param_1[1] & 4) == 0) {
            uVar6 = 4;
          }
          *(undefined1 *)((long)param_1 + 0x81) = uVar6;
          return 0;
        }
        uVar6 = 8;
        if (0xf < uVar7) {
          uVar6 = 2;
          if (1 < uVar7 - 0x10) {
            uVar6 = 0xff;
          }
          *(undefined1 *)((long)param_1 + 0x81) = uVar6;
          return 0;
        }
      }
      *(undefined1 *)((long)param_1 + 0x81) = uVar6;
      return 0;
    }
    if (uVar7 == 2) {
      param_1[0x18] = (uint)param_3;
      return 0;
    }
  }
  else {
    if (uVar7 == 7) {
      iVar1 = *param_3;
      if (iVar1 == 0) {
        return 0;
      }
      piVar8 = *(int **)(param_1 + 0x2c);
      piVar5 = piVar8;
      if (*(char **)(param_3 + 2) != (char *)0x0) {
        while( true ) {
          if (piVar8 == (int *)0x0) {
            piVar5 = (int *)(*(code *)cs_mem_malloc)(0x30);
            __src = *(char **)(param_3 + 2);
            *piVar5 = *param_3;
            strncpy((char *)(piVar5 + 1),__src,0x1f);
            *(undefined1 *)((long)piVar5 + 0x23) = 0;
            *(undefined8 *)(piVar5 + 10) = *(undefined8 *)(param_1 + 0x2c);
            *(int **)(param_1 + 0x2c) = piVar5;
            return 0;
          }
          if (iVar1 == *piVar8) break;
          piVar8 = *(int **)(piVar8 + 10);
        }
        strncpy((char *)(piVar8 + 1),*(char **)(param_3 + 2),0x1f);
        *(undefined1 *)((long)piVar8 + 0x23) = 0;
        return 0;
      }
      do {
        piVar2 = piVar5;
        piVar5 = piVar8;
        if (piVar5 == (int *)0x0) {
          return 0;
        }
        piVar8 = *(int **)(piVar5 + 10);
      } while (iVar1 != *piVar5);
      if (piVar2 == piVar5) {
        *(int **)(param_1 + 0x2c) = piVar8;
      }
      else {
        *(int **)(piVar2 + 10) = piVar8;
      }
      (*(code *)cs_mem_free)();
      return 0;
    }
    if (uVar7 == 8) {
      param_1[0x19] = (uint)param_3;
      return 0;
    }
  }
  uVar4 = (ulong)*param_1;
LAB_0018af04:
                    /* WARNING: Could not recover jumptable at 0x0018af28. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar3 = (*(code *)(&PTR_ARM_option_005ff850)[uVar4 * 3])(param_1,param_2,param_3);
  return uVar3;
}

