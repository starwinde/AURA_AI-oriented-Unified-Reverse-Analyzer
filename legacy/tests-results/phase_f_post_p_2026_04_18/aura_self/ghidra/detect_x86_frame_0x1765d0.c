
void detect_x86_frame(long param_1,ulong param_2,int param_3,undefined4 *param_4)

{
  ulong uVar1;
  char cVar2;
  int iVar3;
  char *pcVar4;
  long lVar5;
  char *__nptr;
  char *__s1;
  char *__haystack;
  ulong uVar6;
  char *__needle;
  char *__needle_00;
  char *pcStack_70;
  long local_68;
  
  uVar1 = param_2;
  if (0x20 < param_2) {
    uVar1 = 0x20;
  }
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  *param_4 = 0;
  if (param_3 == 0) {
    __needle = "ebp";
    __needle_00 = "esp";
  }
  else {
    __needle = "rbp";
    __needle_00 = "rsp";
  }
  if (param_2 != 0) {
    __haystack = (char *)(param_1 + 0x60);
    uVar6 = 0;
    do {
      __s1 = __haystack + -0x40;
      iVar3 = strcmp(__s1,"push");
      if (iVar3 == 0) {
        pcVar4 = strstr(__haystack,__needle);
        if (pcVar4 != (char *)0x0) {
          *param_4 = 1;
          goto LAB_001766b8;
        }
LAB_001766f0:
        iVar3 = strcmp(__s1,"sub");
        if (((iVar3 == 0) && (pcVar4 = strstr(__haystack,__needle_00), pcVar4 != (char *)0x0)) &&
           (pcVar4 = strchr(__haystack,0x2c), pcVar4 != (char *)0x0)) {
          __nptr = pcVar4 + 1;
          cVar2 = pcVar4[1];
          while (cVar2 == ' ') {
            __nptr = __nptr + 1;
            cVar2 = *__nptr;
          }
          pcStack_70 = (char *)0x0;
          lVar5 = strtol(__nptr,&pcStack_70,0);
          if ((pcStack_70 != __nptr) && (lVar5 - 1U < 0xfffff)) goto LAB_0017678c;
        }
      }
      else {
LAB_001766b8:
        iVar3 = strcmp(__s1,"mov");
        if ((iVar3 != 0) || (pcVar4 = strstr(__haystack,__needle), pcVar4 == (char *)0x0))
        goto LAB_001766f0;
        pcVar4 = strstr(__haystack,__needle_00);
        if (pcVar4 != (char *)0x0) {
          *param_4 = 1;
          goto LAB_001766f0;
        }
      }
      iVar3 = strcmp(__s1,"call");
      if ((iVar3 == 0) || (iVar3 = strcmp(__s1,"ret"), iVar3 == 0)) break;
      uVar6 = uVar6 + 1;
      __haystack = __haystack + 0xe0;
    } while (uVar6 < uVar1);
  }
  lVar5 = 0;
LAB_0017678c:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(lVar5,PTR___stack_chk_guard_005ffe88,0,
                   local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
}

