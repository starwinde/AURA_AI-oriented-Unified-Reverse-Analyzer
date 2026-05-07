
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0010bd00(long param_1,long param_2,long *param_3)

{
  long lVar1;
  undefined8 uVar2;
  long *plVar3;
  ulong uVar4;
  int *piVar5;
  long lVar6;
  float fVar7;
  float fVar8;
  long *local_40;
  long local_38;
  
  local_38 = *(long *)PTR___stack_chk_guard_0013ffd0;
  if (param_2 == 0) {
LAB_0010be58:
                    /* WARNING: Subroutine does not return */
    abort();
  }
  lVar1 = FUN_00108820(param_1,param_2,&local_40,0,0);
  if (lVar1 != 0) {
    uVar2 = 0;
    *param_3 = lVar1;
    goto LAB_0010bd5c;
  }
  fVar7 = (float)*(ulong *)(param_1 + 0x10);
  fVar8 = (float)*(ulong *)(param_1 + 0x18);
  if (fVar7 * *(float *)(*(long *)(param_1 + 0x28) + 8) < fVar8) {
    FUN_0010bb04(param_1);
    lVar1 = *(long *)(param_1 + 0x28);
    if (fVar7 * *(float *)(lVar1 + 8) < fVar8) {
      fVar7 = fVar7 * *(float *)(lVar1 + 0xc);
      if ((*(byte *)(lVar1 + 0x10) & 1) == 0) {
        fVar7 = fVar7 * *(float *)(lVar1 + 8);
      }
      if (1.8446744e+19 <= fVar7) {
        piVar5 = __errno_location();
        *piVar5 = 0xc;
      }
      else {
        uVar4 = FUN_0010a6e0(param_1,(long)fVar7);
        if ((uVar4 & 1) != 0) {
          lVar1 = FUN_00108820(param_1,param_2,&local_40,0);
          if (lVar1 != 0) goto LAB_0010be58;
          goto LAB_0010bdb4;
        }
      }
      uVar2 = 0xffffffff;
      goto LAB_0010bd5c;
    }
  }
LAB_0010bdb4:
  if (*local_40 == 0) {
    lVar6 = *(long *)(param_1 + 0x20);
    lVar1 = *(long *)(param_1 + 0x18);
    *local_40 = param_2;
    uVar2 = 1;
    lVar1 = lVar1 + _DAT_0011cd00;
    *(long *)(param_1 + 0x20) = lVar6 + _UNK_0011cd08;
    *(long *)(param_1 + 0x18) = lVar1;
  }
  else {
    plVar3 = *(long **)(param_1 + 0x48);
    if (plVar3 == (long *)0x0) {
      plVar3 = malloc(0x10);
      if (plVar3 == (long *)0x0) {
        uVar2 = 0xffffffff;
        goto LAB_0010bd5c;
      }
    }
    else {
      *(long *)(param_1 + 0x48) = plVar3[1];
    }
    lVar1 = *(long *)(param_1 + 0x20);
    lVar6 = local_40[1];
    *plVar3 = param_2;
    plVar3[1] = lVar6;
    local_40[1] = (long)plVar3;
    *(long *)(param_1 + 0x20) = lVar1 + 1;
    uVar2 = 1;
  }
LAB_0010bd5c:
  if (local_38 - *(long *)PTR___stack_chk_guard_0013ffd0 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(uVar2,PTR___stack_chk_guard_0013ffd0,0,
                   local_38 - *(long *)PTR___stack_chk_guard_0013ffd0);
}

