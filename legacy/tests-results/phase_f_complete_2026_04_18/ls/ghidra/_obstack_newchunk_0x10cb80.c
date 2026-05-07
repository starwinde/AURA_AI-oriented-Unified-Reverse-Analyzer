
void _obstack_newchunk(ulong *param_1,ulong param_2)

{
  ulong uVar1;
  ulong *puVar2;
  ulong uVar3;
  long lVar4;
  void *__src;
  undefined8 *puVar5;
  void *__dest;
  ulong __n;
  ulong uVar6;
  
  __n = param_1[3] - param_1[2];
  uVar6 = param_1[6] + __n + param_2;
  uVar1 = (__n >> 3) + 100 + uVar6;
  uVar3 = *param_1;
  if (*param_1 < uVar6) {
    uVar3 = uVar6;
  }
  if (uVar1 < uVar3) {
    uVar1 = uVar3;
  }
  uVar6 = param_1[1];
  if (!CARRY8(__n,param_2) && !CARRY8(param_1[6],__n + param_2)) {
    if ((param_1[10] & 1) == 0) {
      puVar2 = (ulong *)(*(code *)param_1[7])(uVar1);
    }
    else {
      puVar2 = (ulong *)(*(code *)param_1[7])(param_1[9],uVar1);
    }
    if (puVar2 != (ulong *)0x0) {
      param_1[1] = (ulong)puVar2;
      __src = (void *)param_1[2];
      uVar3 = param_1[6];
      puVar2[1] = uVar6;
      param_1[4] = (long)puVar2 + uVar1;
      *puVar2 = (long)puVar2 + uVar1;
      __dest = (void *)((long)puVar2 + uVar3 + 0x10 & (uVar3 ^ 0xffffffffffffffff));
      memcpy(__dest,__src,__n);
      uVar1 = param_1[10];
      if ((((byte)uVar1 >> 1 & 1) == 0) &&
         (param_1[2] == (uVar6 + 0x10 + param_1[6] & (param_1[6] ^ 0xffffffffffffffff)))) {
        puVar2[1] = *(ulong *)(uVar6 + 8);
        if (((byte)uVar1 & 1) == 0) {
          (*(code *)param_1[8])(uVar6);
        }
        else {
          (*(code *)param_1[8])(param_1[9],uVar6);
        }
      }
      param_1[2] = (ulong)__dest;
      param_1[3] = (long)__dest + __n;
      *(byte *)(param_1 + 10) = (byte)param_1[10] & 0xfd;
      return;
    }
  }
  lVar4 = (**(code **)PTR_obstack_alloc_failed_handler_0013ff80)();
  puVar5 = *(undefined8 **)(lVar4 + 0x18);
  if ((ulong)(*(long *)(lVar4 + 0x20) - (long)puVar5) < 8) {
    _obstack_newchunk(lVar4,8);
    puVar5 = *(undefined8 **)(lVar4 + 0x18);
  }
  *puVar5 = DAT_001402c0;
  *(long *)(lVar4 + 0x18) = *(long *)(lVar4 + 0x18) + 8;
  return;
}

