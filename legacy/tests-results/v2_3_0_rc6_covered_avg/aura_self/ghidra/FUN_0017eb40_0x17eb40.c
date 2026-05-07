
void FUN_0017eb40(long param_1)

{
  long lVar1;
  undefined4 *puVar2;
  
  lVar1 = *(long *)PTR___stack_chk_guard_005ffe88;
  puVar2 = calloc(1,0x130);
  if (puVar2 != (undefined4 *)0x0) {
    *puVar2 = 0xe;
    *(long *)(puVar2 + 0x26) = param_1;
    if (((param_1 == 0) || (param_1 + 0x80U < 0x100)) || (param_1 + 0x80000000U < 0x100000000)) {
      *(undefined8 *)(puVar2 + 3) = 0;
      *(undefined8 *)(puVar2 + 1) = 0x745f3233746e69;
      *(undefined8 *)(puVar2 + 7) = 0;
      *(undefined8 *)(puVar2 + 5) = 0;
      *(undefined8 *)(puVar2 + 0xb) = 0;
      *(undefined8 *)(puVar2 + 9) = 0;
      *(undefined8 *)(puVar2 + 0xf) = 0;
      *(undefined8 *)(puVar2 + 0xd) = 0;
      *(undefined8 *)(puVar2 + 0x21) = 0x10000000004;
      *(undefined8 *)(puVar2 + 0x13) = 0;
      *(undefined8 *)(puVar2 + 0x11) = 0;
      *(undefined8 *)(puVar2 + 0x17) = 0;
      *(undefined8 *)(puVar2 + 0x15) = 0;
      *(undefined8 *)(puVar2 + 0x1b) = 0;
      *(undefined8 *)(puVar2 + 0x19) = 0;
      *(undefined8 *)(puVar2 + 0x1f) = 0;
      *(undefined8 *)(puVar2 + 0x1d) = 0;
    }
    else {
      *(undefined8 *)(puVar2 + 3) = 0;
      *(undefined8 *)(puVar2 + 1) = 0x745f3436746e69;
      *(undefined8 *)(puVar2 + 7) = 0;
      *(undefined8 *)(puVar2 + 5) = 0;
      *(undefined8 *)(puVar2 + 0xb) = 0;
      *(undefined8 *)(puVar2 + 9) = 0;
      *(undefined8 *)(puVar2 + 0xf) = 0;
      *(undefined8 *)(puVar2 + 0xd) = 0;
      *(undefined8 *)(puVar2 + 0x13) = 0;
      *(undefined8 *)(puVar2 + 0x11) = 0;
      *(undefined8 *)(puVar2 + 0x17) = 0;
      *(undefined8 *)(puVar2 + 0x15) = 0;
      *(undefined8 *)(puVar2 + 0x1b) = 0;
      *(undefined8 *)(puVar2 + 0x19) = 0;
      *(undefined8 *)(puVar2 + 0x1f) = 0;
      *(undefined8 *)(puVar2 + 0x1d) = 0;
      *(undefined8 *)(puVar2 + 0x21) = 0x10000000008;
    }
  }
  if (lVar1 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(puVar2,PTR___stack_chk_guard_005ffe88,0,
                     lVar1 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return;
}

