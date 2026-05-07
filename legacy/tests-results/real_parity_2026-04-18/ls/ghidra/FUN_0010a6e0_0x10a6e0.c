
void FUN_0010a6e0(undefined8 *param_1,undefined8 param_2)

{
  int iVar1;
  size_t __nmemb;
  ulong uVar2;
  int *piVar3;
  undefined8 uVar4;
  long lVar5;
  void *local_90;
  void *pvStack_88;
  size_t sStack_80;
  undefined8 local_78;
  undefined8 uStack_70;
  long local_68;
  undefined8 local_60;
  undefined8 uStack_58;
  undefined8 local_50;
  undefined8 local_48;
  long local_38;
  
  lVar5 = param_1[5];
  local_38 = *(long *)PTR___stack_chk_guard_0013ffd0;
  __nmemb = FUN_00114b40(*(undefined4 *)(lVar5 + 8),param_2,*(undefined1 *)(lVar5 + 0x10),0);
  if (__nmemb != 0) {
    if (param_1[2] == __nmemb) {
LAB_0010a818:
      uVar4 = 1;
      goto LAB_0010a7cc;
    }
    local_90 = calloc(__nmemb,0x10);
    if (local_90 != (void *)0x0) {
      local_50 = param_1[8];
      local_48 = param_1[9];
      pvStack_88 = (void *)((long)local_90 + __nmemb * 0x10);
      uStack_58 = param_1[7];
      local_60 = param_1[6];
      local_78 = 0;
      uStack_70 = 0;
      sStack_80 = __nmemb;
      local_68 = lVar5;
      uVar2 = FUN_00108970(&local_90,param_1,0);
      if ((uVar2 & 1) != 0) {
        free((void *)*param_1);
        param_1[9] = local_48;
        param_1[1] = pvStack_88;
        *param_1 = local_90;
        param_1[3] = local_78;
        param_1[2] = sStack_80;
        goto LAB_0010a818;
      }
      piVar3 = __errno_location();
      iVar1 = *piVar3;
      param_1[9] = local_48;
      uVar2 = FUN_00108970(param_1,&local_90,1);
      if (((uVar2 & 1) == 0) || (uVar2 = FUN_00108970(param_1,&local_90,0), (uVar2 & 1) == 0)) {
                    /* WARNING: Subroutine does not return */
        abort();
      }
      free(local_90);
      *piVar3 = iVar1;
    }
  }
  uVar4 = 0;
LAB_0010a7cc:
  if (local_38 - *(long *)PTR___stack_chk_guard_0013ffd0 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(uVar4,PTR___stack_chk_guard_0013ffd0,0,
                   local_38 - *(long *)PTR___stack_chk_guard_0013ffd0);
}

