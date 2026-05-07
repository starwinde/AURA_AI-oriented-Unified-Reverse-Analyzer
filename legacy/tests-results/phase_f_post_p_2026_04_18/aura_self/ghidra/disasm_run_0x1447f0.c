
ulong disasm_run(undefined8 *param_1,long param_2,undefined8 param_3,undefined8 param_4,long param_5
                ,int param_6)

{
  undefined4 uVar1;
  ulong uVar2;
  long lVar3;
  char *__dest;
  char *__src;
  ulong uVar4;
  size_t __n;
  ulong uVar5;
  long local_60;
  
  lVar3 = *(long *)PTR___stack_chk_guard_005ffe88;
  if ((param_2 == 0 || param_5 == 0) || param_1 == (undefined8 *)0x0) {
    uVar4 = 0xffffffff;
  }
  else {
    uVar2 = cs_disasm(*param_1);
    if (uVar2 == 0) {
      uVar4 = 0;
      uVar1 = cs_errno(*param_1);
      *(undefined4 *)((long)param_1 + 0xc) = uVar1;
    }
    else {
      uVar4 = 0;
      if (0 < param_6) {
        __dest = (char *)(param_5 + 0x60);
        __src = (char *)(local_60 + 0x4a);
        uVar5 = 1;
        do {
          __n = (size_t)*(ushort *)(__src + -0x3a);
          *(undefined8 *)(__dest + -0x60) = *(undefined8 *)(__src + -0x42);
          if (0x10 < __n) {
            __n = 0x10;
          }
          memcpy(__dest + -0x58,__src + -0x38,__n);
          *(size_t *)(__dest + -0x48) = __n;
          strncpy(__dest + -0x40,__src + -0x20,0x3f);
          __dest[-1] = '\0';
          if (*__src == '\0') {
            *__dest = '\0';
          }
          else {
            strncpy(__dest,__src,0x7f);
            __dest[0x7f] = '\0';
          }
          uVar4 = uVar5 & 0xffffffff;
          if (uVar2 == uVar5) break;
          uVar4 = uVar5 & 0xffffffff;
          uVar5 = uVar5 + 1;
          __dest = __dest + 0xe0;
          __src = __src + 0xf8;
        } while ((ulong)(param_6 - 1) + 2 != uVar5);
      }
      cs_free(local_60,uVar2);
    }
  }
  if (lVar3 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                     lVar3 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return uVar4;
}

