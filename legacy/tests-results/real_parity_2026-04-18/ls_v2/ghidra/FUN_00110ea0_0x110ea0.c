
void FUN_00110ea0(char *param_1)

{
  char cVar1;
  int iVar2;
  undefined8 uVar3;
  char *pcVar4;
  uint uVar5;
  char *local_40;
  long local_38;
  
  local_38 = *(long *)PTR___stack_chk_guard_0013ffd0;
  if (((param_1 == (char *)0x0) && (param_1 = getenv("BLOCK_SIZE"), param_1 == (char *)0x0)) &&
     (param_1 = getenv("BLOCKSIZE"), param_1 == (char *)0x0)) {
    pcVar4 = getenv("POSIXLY_CORRECT");
    DAT_00141010 = 0x400;
    if (pcVar4 != (char *)0x0) {
      DAT_00141010 = 0x200;
    }
    DAT_00141018 = 0;
    uVar3 = 0;
  }
  else {
    uVar5 = 0;
    if (*param_1 == '\'') {
      param_1 = param_1 + 1;
      uVar5 = 4;
    }
    iVar2 = FUN_001108c4(param_1,&PTR_s_human_readable_0013f9d0,&DAT_0011d070);
    if (iVar2 < 0) {
      uVar3 = FUN_001109d0(param_1,&local_40,&DAT_00141010,"eEgGkKmMpPtTyYzZ0");
      if ((int)uVar3 == 0) {
        cVar1 = *param_1;
        while (DAT_00141018 = uVar5, 9 < (byte)(cVar1 - 0x30U)) {
          if (local_40 == param_1) {
            if (local_40[-1] == 'B') {
              DAT_00141018 = uVar5 | 0x180;
              if (local_40[-2] != 'i') break;
            }
            else {
              DAT_00141018 = uVar5 | 0x80;
            }
            DAT_00141018 = DAT_00141018 | 0x20;
            break;
          }
          param_1 = param_1 + 1;
          cVar1 = *param_1;
        }
      }
      else {
        DAT_00141018 = 0;
      }
      if (DAT_00141010 == 0) {
        pcVar4 = getenv("POSIXLY_CORRECT");
        uVar3 = 4;
        DAT_00141010 = 0x400;
        if (pcVar4 != (char *)0x0) {
          DAT_00141010 = 0x200;
        }
      }
    }
    else {
      DAT_00141010 = 1;
      DAT_00141018 = uVar5 | *(uint *)(&DAT_0011d070 + (long)iVar2 * 4);
      uVar3 = 0;
    }
  }
  if (local_38 - *(long *)PTR___stack_chk_guard_0013ffd0 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(uVar3,PTR___stack_chk_guard_0013ffd0,0,
                     local_38 - *(long *)PTR___stack_chk_guard_0013ffd0);
  }
  return;
}

