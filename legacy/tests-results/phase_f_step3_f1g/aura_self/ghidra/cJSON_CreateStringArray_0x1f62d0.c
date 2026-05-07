
undefined8 * cJSON_CreateStringArray(long param_1,int param_2)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  size_t sVar3;
  void *__dest;
  ulong uVar4;
  char *__s;
  undefined8 *puVar5;
  
  if ((-1 < param_2 && param_1 != 0) &&
     (puVar1 = (undefined8 *)(*(code *)global_hooks)(0x40), puVar1 != (undefined8 *)0x0)) {
    puVar1[1] = 0;
    *puVar1 = 0;
    puVar1[3] = 0;
    puVar1[2] = 0;
    *(undefined4 *)(puVar1 + 3) = 0x20;
    puVar1[5] = 0;
    puVar1[4] = 0;
    puVar1[7] = 0;
    puVar1[6] = 0;
    if (param_2 == 0) {
      return puVar1;
    }
    uVar4 = 0;
    puVar5 = (undefined8 *)0x0;
    while( true ) {
      __s = *(char **)(param_1 + uVar4 * 8);
      puVar2 = (undefined8 *)(*(code *)global_hooks)(0x40);
      if (puVar2 == (undefined8 *)0x0) break;
      puVar2[1] = 0;
      *puVar2 = 0;
      puVar2[3] = 0;
      puVar2[2] = 0;
      *(undefined4 *)(puVar2 + 3) = 0x10;
      puVar2[5] = 0;
      puVar2[4] = 0;
      puVar2[7] = 0;
      puVar2[6] = 0;
      if (__s == (char *)0x0) {
LAB_001f6420:
        cJSON_Delete(puVar2);
        break;
      }
      sVar3 = strlen(__s);
      __dest = (void *)(*(code *)global_hooks)(sVar3 + 1);
      if (__dest == (void *)0x0) {
        puVar2[4] = 0;
        goto LAB_001f6420;
      }
      memcpy(__dest,__s,sVar3 + 1);
      puVar2[4] = __dest;
      if (uVar4 == 0) {
        puVar1[2] = puVar2;
        uVar4 = 1;
        puVar5 = puVar2;
        if ((long)param_2 == 1) {
          puVar2[1] = puVar2;
          return puVar1;
        }
      }
      else {
        *puVar5 = puVar2;
        uVar4 = uVar4 + 1;
        puVar2[1] = puVar5;
        puVar5 = puVar2;
        if ((ulong)(long)param_2 <= uVar4) {
          if (puVar1[2] != 0) {
            *(undefined8 **)(puVar1[2] + 8) = puVar2;
            return puVar1;
          }
          return puVar1;
        }
      }
    }
    cJSON_Delete(puVar1);
  }
  return (undefined8 *)0x0;
}

