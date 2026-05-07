
void detect_ret_cleanup(long param_1,long param_2,undefined2 *param_3)

{
  char *__s1;
  long lVar1;
  int iVar2;
  undefined8 uVar3;
  long lVar4;
  char *local_60;
  long local_58;
  
  local_58 = *(long *)PTR___stack_chk_guard_005ffe88;
  *param_3 = 0;
  if (param_2 != 0) {
    lVar1 = param_1 + param_2 * 0xe0;
    do {
      __s1 = (char *)(lVar1 + -0xc0);
      iVar2 = strcmp(__s1,"ret");
      if (((iVar2 == 0) || (iVar2 = strcmp(__s1,"retn"), iVar2 == 0)) ||
         (iVar2 = strcmp(__s1,"retf"), iVar2 == 0)) {
        if (*(char *)(lVar1 + -0x80) != '\0') {
          local_60 = (char *)0x0;
          lVar4 = strtol((char *)(lVar1 + -0x80),&local_60,0);
          if ((local_60 != (char *)(lVar1 + -0x80)) && (lVar4 - 1U < 0xffff)) {
            uVar3 = 1;
            *param_3 = (short)lVar4;
            goto LAB_00174018;
          }
        }
        break;
      }
      param_2 = param_2 + -1;
      lVar1 = lVar1 + -0xe0;
    } while (param_2 != 0);
  }
  uVar3 = 0;
LAB_00174018:
  if (local_58 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(uVar3,PTR___stack_chk_guard_005ffe88,0,
                     local_58 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return;
}

