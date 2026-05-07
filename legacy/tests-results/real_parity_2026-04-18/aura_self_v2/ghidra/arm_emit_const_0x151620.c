
undefined1  [16] arm_emit_const(long param_1,long param_2,undefined8 param_3,undefined8 param_4)

{
  void *__ptr;
  size_t __size;
  uint uVar1;
  long lVar2;
  uint uVar3;
  uint uVar4;
  undefined1 auVar5 [16];
  
  uVar3 = *(uint *)(param_2 + 0x10);
  uVar1 = *(uint *)(param_1 + 0x10);
  uVar4 = *(uint *)(param_1 + 0x14);
  *(uint *)(param_2 + 0x10) = uVar3 + 1;
  __ptr = *(void **)(param_1 + 8);
  if (uVar4 <= uVar1) {
    if (uVar4 == 0) {
      __size = 0x880;
      uVar4 = 0x10;
    }
    else {
      uVar4 = uVar4 << 1;
      __size = (ulong)uVar4 * 0x88;
    }
    __ptr = realloc(__ptr,__size);
    if (__ptr == (void *)0x0) {
      uVar3 = 0xffffffff;
      goto LAB_001516c4;
    }
    uVar1 = *(uint *)(param_1 + 0x10);
    *(void **)(param_1 + 8) = __ptr;
    *(uint *)(param_1 + 0x14) = uVar4;
  }
  *(uint *)(param_1 + 0x10) = uVar1 + 1;
  lVar2 = (ulong)uVar1 * 0x88;
  *(undefined4 *)((long)__ptr + lVar2 + 0x84) = 0;
  *(undefined8 *)((long)__ptr + lVar2 + 0xc) = 0;
  *(undefined8 *)((long)__ptr + lVar2 + 4) = 0;
  *(undefined8 *)((long)__ptr + lVar2 + 0x1c) = 0;
  *(undefined8 *)((long)__ptr + lVar2 + 0x14) = 0;
  *(undefined8 *)((long)__ptr + lVar2 + 0x2c) = 0;
  *(undefined8 *)((long)__ptr + lVar2 + 0x24) = 0;
  *(undefined8 *)((long)__ptr + lVar2 + 0x3c) = 0;
  *(undefined8 *)((long)__ptr + lVar2 + 0x34) = 0;
  *(undefined8 *)((long)__ptr + lVar2 + 0x4c) = 0;
  *(undefined8 *)((long)__ptr + lVar2 + 0x44) = 0;
  *(undefined8 *)((long)__ptr + lVar2 + 0x5c) = 0;
  *(undefined8 *)((long)__ptr + lVar2 + 0x54) = 0;
  *(undefined8 *)((long)__ptr + lVar2 + 0x6c) = 0;
  *(undefined8 *)((long)__ptr + lVar2 + 100) = 0;
  *(undefined8 *)((long)__ptr + lVar2 + 0x7c) = 0;
  *(undefined8 *)((long)__ptr + lVar2 + 0x74) = 0;
  *(undefined4 *)((long)__ptr + lVar2) = 1;
  *(uint *)((long)__ptr + lVar2 + 8) = uVar3;
  *(undefined4 *)((long)__ptr + lVar2 + 0xc) = 4;
  *(undefined8 *)((long)__ptr + lVar2 + 0x10) = param_3;
  *(undefined8 *)((long)__ptr + lVar2 + 0x70) = param_4;
LAB_001516c4:
  auVar5._0_8_ = (ulong)uVar3 | 0x400000000;
  auVar5._8_8_ = param_3;
  return auVar5;
}

