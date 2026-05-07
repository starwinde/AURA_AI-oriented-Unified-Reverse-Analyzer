
uint FUN_0014ba20(long param_1,long param_2)

{
  long *plVar1;
  int iVar2;
  long lVar3;
  uint uVar4;
  long lVar5;
  long *local_58;
  void *local_50;
  long local_48;
  
  local_48 = *(long *)PTR___stack_chk_guard_005ffe88;
  if ((param_1 != 0 && param_2 != 0) && (*(long *)(param_1 + 8) == 0x400000001)) {
    if (DAT_006005dc == 0) {
      DAT_006005dc = 1;
      FUN_001669e0();
    }
    lVar3 = FUN_00140b70("aarch64_plt_thunks");
    if (((lVar3 != 0) && (*(code **)(lVar3 + 0x28) != (code *)0x0)) &&
       (*(long *)(lVar3 + 0x30) != 0)) {
      local_58 = (long *)0x0;
      local_50 = (void *)0x0;
      iVar2 = (**(code **)(lVar3 + 0x28))(param_1,0,0,0,&local_58,&local_50);
      free(local_50);
      plVar1 = local_58;
      if (iVar2 == 0) {
        if (local_58 != (long *)0x0) {
          lVar5 = 0;
          uVar4 = 0;
          if ((int)local_58[1] != 0) {
            do {
              iVar2 = FUN_0014bbf0(param_2,*(undefined8 *)(*plVar1 + lVar5),7,0xffffffaf,0);
              if (iVar2 == 0) break;
              uVar4 = uVar4 + 1;
              lVar5 = lVar5 + 0x18;
            } while (uVar4 < *(uint *)(plVar1 + 1));
          }
          (**(code **)(lVar3 + 0x30))(local_58);
          goto LAB_0014ba70;
        }
      }
      else if (local_58 != (long *)0x0) {
        (**(code **)(lVar3 + 0x30))();
      }
    }
  }
  uVar4 = 0;
LAB_0014ba70:
  if (local_48 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return uVar4;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                   local_48 - *(long *)PTR___stack_chk_guard_005ffe88);
}

