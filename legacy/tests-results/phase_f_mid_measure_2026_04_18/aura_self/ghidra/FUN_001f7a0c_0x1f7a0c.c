
undefined8 * FUN_001f7a0c(long param_1,ulong param_2,int param_3)

{
  undefined4 uVar1;
  undefined8 *puVar2;
  size_t sVar3;
  void *pvVar4;
  long *plVar5;
  long *plVar6;
  long *plVar7;
  char *pcVar8;
  undefined8 uVar9;
  
  if (param_1 == 0) {
    return (undefined8 *)0x0;
  }
  puVar2 = (undefined8 *)(*(code *)global_hooks)(0x40);
  if (puVar2 == (undefined8 *)0x0) {
    return (undefined8 *)0x0;
  }
  puVar2[1] = 0;
  *puVar2 = 0;
  puVar2[3] = 0;
  puVar2[2] = 0;
  puVar2[5] = 0;
  puVar2[4] = 0;
  puVar2[7] = 0;
  puVar2[6] = 0;
  uVar9 = *(undefined8 *)(param_1 + 0x30);
  pcVar8 = *(char **)(param_1 + 0x20);
  uVar1 = *(undefined4 *)(param_1 + 0x28);
  *(uint *)(puVar2 + 3) = *(uint *)(param_1 + 0x18) & 0xfffffeff;
  *(undefined4 *)(puVar2 + 5) = uVar1;
  puVar2[6] = uVar9;
  if (pcVar8 != (char *)0x0) {
    sVar3 = strlen(pcVar8);
    pvVar4 = (void *)(*(code *)global_hooks)(sVar3 + 1);
    if (pvVar4 == (void *)0x0) {
      puVar2[4] = 0;
      goto LAB_001f7b68;
    }
    memcpy(pvVar4,pcVar8,sVar3 + 1);
    puVar2[4] = pvVar4;
  }
  pcVar8 = *(char **)(param_1 + 0x38);
  if (pcVar8 != (char *)0x0) {
    if ((*(uint *)(param_1 + 0x18) >> 9 & 1) == 0) {
      sVar3 = strlen(pcVar8);
      pvVar4 = (void *)(*(code *)global_hooks)(sVar3 + 1);
      if (pvVar4 == (void *)0x0) {
        puVar2[7] = 0;
        goto LAB_001f7b68;
      }
      memcpy(pvVar4,pcVar8,sVar3 + 1);
      puVar2[7] = pvVar4;
    }
    else {
      puVar2[7] = pcVar8;
    }
  }
  if (param_3 == 0) {
    return puVar2;
  }
  plVar7 = *(long **)(param_1 + 0x10);
  if (plVar7 == (long *)0x0) {
    plVar5 = (long *)0x0;
LAB_001f7bc0:
    plVar6 = (long *)puVar2[2];
    if ((long *)puVar2[2] == (long *)0x0) {
      return puVar2;
    }
  }
  else {
    if (9999 < param_2) {
LAB_001f7b68:
      cJSON_Delete(puVar2);
      return (undefined8 *)0x0;
    }
    plVar6 = (long *)0x0;
    do {
      while( true ) {
        plVar5 = (long *)cJSON_Duplicate_rec(plVar7,param_2 + 1,1);
        if (plVar5 == (long *)0x0) goto LAB_001f7b68;
        if (plVar6 == (long *)0x0) break;
        *plVar6 = (long)plVar5;
        plVar7 = (long *)*plVar7;
        plVar5[1] = (long)plVar6;
        plVar6 = plVar5;
        if (plVar7 == (long *)0x0) goto LAB_001f7bc0;
      }
      plVar7 = (long *)*plVar7;
      puVar2[2] = plVar5;
      plVar6 = plVar5;
    } while (plVar7 != (long *)0x0);
  }
  plVar6[1] = (long)plVar5;
  return puVar2;
}

