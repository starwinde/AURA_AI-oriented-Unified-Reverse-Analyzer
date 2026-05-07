
void FUN_0010ba30(int param_1)

{
  bool bVar1;
  int iVar2;
  char *pcVar3;
  size_t sVar4;
  char local_130 [264];
  long local_28;
  
  local_28 = *(long *)PTR___stack_chk_guard_0013ffd0;
  pcVar3 = setlocale(param_1,(char *)0x0);
  if (((pcVar3 == (char *)0x0) || (sVar4 = strlen(pcVar3), 0x100 < sVar4)) ||
     ((pcVar3 = memcpy(local_130,pcVar3,sVar4 + 1), local_130[0] == 'C' && (pcVar3[1] == '\0')))) {
    bVar1 = false;
  }
  else {
    iVar2 = strcmp(pcVar3,"POSIX");
    bVar1 = iVar2 != 0;
  }
  if (local_28 - *(long *)PTR___stack_chk_guard_0013ffd0 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(bVar1,PTR___stack_chk_guard_0013ffd0,0,
                     local_28 - *(long *)PTR___stack_chk_guard_0013ffd0);
  }
  return;
}

