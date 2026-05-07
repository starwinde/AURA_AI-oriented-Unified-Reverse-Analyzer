
void FUN_0010ae30(char *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  bool bVar3;
  int *piVar4;
  size_t sVar5;
  size_t sVar6;
  char local_40 [8];
  long local_38;
  
  local_38 = *(long *)PTR___stack_chk_guard_0013ffd0;
  puVar1 = &DAT_00140f48;
  if (DAT_00140f20 != (undefined4 *)0x0) {
    puVar1 = DAT_00140f20;
  }
  piVar4 = __errno_location();
  iVar2 = *piVar4;
  sVar5 = FUN_00111270(local_40,2,param_1,*puVar1,puVar1[1],puVar1 + 2,*(undefined8 *)(puVar1 + 10),
                       *(undefined8 *)(puVar1 + 0xc));
  *piVar4 = iVar2;
  if (*param_1 == local_40[0]) {
    sVar6 = strlen(param_1);
    bVar3 = sVar6 != sVar5;
  }
  else {
    bVar3 = true;
  }
  if (local_38 - *(long *)PTR___stack_chk_guard_0013ffd0 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(bVar3,PTR___stack_chk_guard_0013ffd0,0,
                   local_38 - *(long *)PTR___stack_chk_guard_0013ffd0);
}

