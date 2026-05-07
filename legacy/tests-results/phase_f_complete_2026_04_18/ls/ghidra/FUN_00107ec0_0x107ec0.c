
undefined8 * FUN_00107ec0(char *param_1)

{
  ulong uVar1;
  size_t sVar2;
  undefined8 *puVar3;
  long lVar4;
  undefined8 *puVar5;
  ulong uVar6;
  
  if (param_1 == (char *)0x0) {
    puVar5 = malloc(0x80);
    puVar3 = (undefined8 *)0x0;
    if (puVar5 != (undefined8 *)0x0) {
      *puVar5 = 0;
      *(undefined2 *)(puVar5 + 1) = 0;
      return puVar5;
    }
  }
  else {
    sVar2 = strlen(param_1);
    uVar1 = sVar2 + 1;
    uVar6 = uVar1;
    if (uVar1 < 0x76) {
      uVar6 = 0x76;
    }
    uVar6 = uVar6 + 0x11 & 0xfffffffffffffff8;
    puVar3 = malloc(uVar6);
    if (puVar3 != (undefined8 *)0x0) {
      *puVar3 = 0;
      *(undefined2 *)(puVar3 + 1) = 1;
      lVar4 = __memcpy_chk((long)puVar3 + 9,param_1,uVar1,uVar6 - 9);
      *(undefined1 *)(lVar4 + uVar1) = 0;
    }
  }
  return puVar3;
}

