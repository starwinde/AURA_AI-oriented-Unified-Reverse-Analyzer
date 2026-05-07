
undefined8 FUN_0018b29c(undefined8 *param_1)

{
  long lVar1;
  undefined *puVar2;
  long lVar3;
  undefined8 *puVar4;
  
  puVar4 = (undefined8 *)*param_1;
  if (puVar4 == (undefined8 *)0x0) {
    return 4;
  }
  if (puVar4[2] != 0) {
    (*(code *)cs_mem_free)();
  }
  lVar1 = puVar4[0x16];
  while (lVar1 != 0) {
    lVar3 = *(long *)(lVar1 + 0x28);
    (*(code *)cs_mem_free)(lVar1);
    lVar1 = lVar3;
  }
  (*(code *)cs_mem_free)(puVar4[0xe]);
  puVar4[0x16] = 0;
  puVar2 = cs_mem_free;
  puVar4[1] = 0;
  *puVar4 = 0;
  puVar4[3] = 0;
  puVar4[2] = 0;
  puVar4[5] = 0;
  puVar4[4] = 0;
  puVar4[7] = 0;
  puVar4[6] = 0;
  puVar4[9] = 0;
  puVar4[8] = 0;
  puVar4[0xb] = 0;
  puVar4[10] = 0;
  puVar4[0xd] = 0;
  puVar4[0xc] = 0;
  puVar4[0xf] = 0;
  puVar4[0xe] = 0;
  puVar4[0x11] = 0;
  puVar4[0x10] = 0;
  puVar4[0x13] = 0;
  puVar4[0x12] = 0;
  puVar4[0x15] = 0;
  puVar4[0x14] = 0;
  (*(code *)puVar2)(puVar4);
  *param_1 = 0;
  return 0;
}

