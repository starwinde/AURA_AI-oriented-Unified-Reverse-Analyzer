
undefined8 insert_one_phi_at(long *param_1,ulong param_2)

{
  uint uVar1;
  undefined8 uVar2;
  void *pvVar3;
  void *pvVar4;
  long lVar5;
  long lVar6;
  long lVar7;
  ulong __size;
  undefined4 *puVar8;
  
  lVar7 = *param_1 + (param_2 & 0xffffffff) * 0x50;
  __size = (ulong)(*(int *)(lVar7 + 0x10) + 1) * 0x90;
  pvVar3 = realloc(*(void **)(lVar7 + 8),__size);
  if (pvVar3 != (void *)0x0) {
    *(void **)(lVar7 + 8) = pvVar3;
    *(uint *)(lVar7 + 0x14) = *(uint *)(lVar7 + 0x10) + 1;
    if (__size < 0x90) {
      __size = 0x90;
    }
    __memmove_chk((long)pvVar3 + 0x90,pvVar3,(ulong)*(uint *)(lVar7 + 0x10) * 0x90,__size - 0x90);
    puVar8 = *(undefined4 **)(lVar7 + 8);
    *(int *)(lVar7 + 0x10) = *(int *)(lVar7 + 0x10) + 1;
    *(undefined8 *)(puVar8 + 0x1b) = 0;
    *(undefined8 *)(puVar8 + 0x19) = 0;
    *(undefined8 *)(puVar8 + 0x1f) = 0;
    *(undefined8 *)(puVar8 + 0x1d) = 0;
    *(undefined8 *)(puVar8 + 3) = 0;
    *(undefined8 *)(puVar8 + 1) = 0;
    *(undefined8 *)(puVar8 + 7) = 0;
    *(undefined8 *)(puVar8 + 5) = 0;
    *(undefined8 *)(puVar8 + 0xb) = 0;
    *(undefined8 *)(puVar8 + 9) = 0;
    *(undefined8 *)(puVar8 + 0xf) = 0;
    *(undefined8 *)(puVar8 + 0xd) = 0;
    *(undefined8 *)(puVar8 + 0x13) = 0;
    *(undefined8 *)(puVar8 + 0x11) = 0;
    *(undefined8 *)(puVar8 + 0x17) = 0;
    *(undefined8 *)(puVar8 + 0x15) = 0;
    *(undefined8 *)(puVar8 + 0x22) = 0;
    *(undefined8 *)(puVar8 + 0x20) = 0;
    lVar5 = param_1[2];
    uVar1 = *(uint *)(lVar7 + 0x20);
    *puVar8 = 0x1b;
    *(int *)(param_1 + 2) = (int)lVar5 + 1;
    puVar8[2] = (int)lVar5;
    puVar8[3] = 4;
    puVar8[0x18] = uVar1;
    pvVar3 = calloc((ulong)uVar1,0x10);
    *(void **)(puVar8 + 0x14) = pvVar3;
    pvVar4 = calloc((ulong)uVar1,4);
    *(void **)(puVar8 + 0x16) = pvVar4;
    uVar2 = DAT_0020c580;
    if (pvVar4 != (void *)0x0 && pvVar3 != (void *)0x0) {
      if (uVar1 != 0) {
        lVar5 = 0;
        lVar6 = *(long *)(lVar7 + 0x18);
        do {
          *(undefined8 *)((long)pvVar3 + lVar5 * 0x10) = uVar2;
          *(undefined4 *)((long)pvVar4 + lVar5 * 4) = *(undefined4 *)(lVar6 + lVar5 * 4);
          lVar5 = lVar5 + 1;
        } while ((uint)lVar5 < *(uint *)(lVar7 + 0x20));
      }
      return 0;
    }
  }
  return 0xfffffffe;
}

