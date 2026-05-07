
undefined8 * cJSON_AddRawToObject(undefined8 *param_1,char *param_2,char *param_3)

{
  uint uVar1;
  undefined8 *puVar2;
  size_t sVar3;
  void *pvVar4;
  long lVar5;
  undefined8 *puVar6;
  
  puVar2 = (undefined8 *)(*(code *)global_hooks)(0x40);
  if (puVar2 != (undefined8 *)0x0) {
    puVar2[1] = 0;
    *puVar2 = 0;
    puVar2[3] = 0;
    puVar2[2] = 0;
    *(undefined4 *)(puVar2 + 3) = 0x80;
    puVar2[5] = 0;
    puVar2[4] = 0;
    puVar2[7] = 0;
    puVar2[6] = 0;
    if (param_3 != (char *)0x0) {
      sVar3 = strlen(param_3);
      pvVar4 = (void *)(*(code *)global_hooks)(sVar3 + 1);
      if (pvVar4 != (void *)0x0) {
        memcpy(pvVar4,param_3,sVar3 + 1);
        puVar2[4] = pvVar4;
        if ((param_2 != (char *)0x0 && param_1 != (undefined8 *)0x0) && (param_1 != puVar2)) {
          sVar3 = strlen(param_2);
          pvVar4 = (void *)(*(code *)global_hooks)(sVar3 + 1);
          if (pvVar4 != (void *)0x0) {
            memcpy(pvVar4,param_2,sVar3 + 1);
            uVar1 = *(uint *)(puVar2 + 3);
            if (((uVar1 >> 9 & 1) == 0) && (puVar2[7] != 0)) {
              (*(code *)PTR_free_006005a0)();
            }
            lVar5 = param_1[2];
            *(uint *)(puVar2 + 3) = uVar1 & 0xfffffdff;
            puVar2[7] = pvVar4;
            if (lVar5 != 0) {
              puVar6 = *(undefined8 **)(lVar5 + 8);
              if (puVar6 == (undefined8 *)0x0) {
                return puVar2;
              }
              *puVar6 = puVar2;
              puVar2[1] = puVar6;
              *(undefined8 **)(lVar5 + 8) = puVar2;
              return puVar2;
            }
            param_1[2] = puVar2;
            *puVar2 = 0;
            puVar2[1] = puVar2;
            return puVar2;
          }
        }
        goto LAB_001f527c;
      }
      puVar2[4] = 0;
    }
    cJSON_Delete(puVar2);
  }
  puVar2 = (undefined8 *)0x0;
LAB_001f527c:
  cJSON_Delete(puVar2);
  return (undefined8 *)0x0;
}

