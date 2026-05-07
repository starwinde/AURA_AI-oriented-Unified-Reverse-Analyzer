
undefined8 * cJSON_Duplicate(long param_1,int param_2)

{
  undefined4 uVar1;
  long lVar2;
  undefined8 *puVar3;
  size_t sVar4;
  void *pvVar5;
  undefined8 *puVar6;
  undefined8 *puVar7;
  undefined8 *puVar8;
  long *plVar9;
  long *plVar10;
  undefined8 *puVar11;
  undefined8 *puVar12;
  long *plVar13;
  char *pcVar14;
  undefined8 *puVar15;
  long *plVar16;
  long *plVar17;
  undefined8 uVar18;
  long lVar19;
  long *local_40;
  undefined8 *local_38;
  long *local_30;
  undefined8 *local_28;
  undefined8 *local_18;
  undefined8 *local_8;
  
  if (param_1 == 0) {
    return (undefined8 *)0x0;
  }
  puVar3 = (undefined8 *)(*(code *)global_hooks)(0x40);
  if (puVar3 == (undefined8 *)0x0) {
    return (undefined8 *)0x0;
  }
  puVar3[1] = 0;
  *puVar3 = 0;
  puVar3[3] = 0;
  puVar3[2] = 0;
  puVar3[5] = 0;
  puVar3[4] = 0;
  puVar3[7] = 0;
  puVar3[6] = 0;
  uVar18 = *(undefined8 *)(param_1 + 0x30);
  pcVar14 = *(char **)(param_1 + 0x20);
  uVar1 = *(undefined4 *)(param_1 + 0x28);
  *(uint *)(puVar3 + 3) = *(uint *)(param_1 + 0x18) & 0xfffffeff;
  *(undefined4 *)(puVar3 + 5) = uVar1;
  puVar3[6] = uVar18;
  if (pcVar14 != (char *)0x0) {
    sVar4 = strlen(pcVar14);
    pvVar5 = (void *)(*(code *)global_hooks)(sVar4 + 1);
    if (pvVar5 == (void *)0x0) {
      puVar3[4] = 0;
      goto LAB_001f85a8;
    }
    memcpy(pvVar5,pcVar14,sVar4 + 1);
    puVar3[4] = pvVar5;
  }
  pcVar14 = *(char **)(param_1 + 0x38);
  if (pcVar14 != (char *)0x0) {
    if ((*(uint *)(param_1 + 0x18) >> 9 & 1) == 0) {
      sVar4 = strlen(pcVar14);
      pvVar5 = (void *)(*(code *)global_hooks)(sVar4 + 1);
      if (pvVar5 == (void *)0x0) {
        puVar3[7] = 0;
        goto LAB_001f85a8;
      }
      memcpy(pvVar5,pcVar14,sVar4 + 1);
      puVar3[7] = pvVar5;
    }
    else {
      puVar3[7] = pcVar14;
    }
  }
  if (param_2 == 0) {
    return puVar3;
  }
  local_18 = *(undefined8 **)(param_1 + 0x10);
  if (local_18 == (undefined8 *)0x0) {
LAB_001f8900:
    puVar11 = (undefined8 *)puVar3[2];
    if (puVar11 == (undefined8 *)0x0) {
      return puVar3;
    }
LAB_001f890c:
    puVar11[1] = local_18;
    return puVar3;
  }
  local_8 = (undefined8 *)0x0;
  puVar6 = (undefined8 *)(*(code *)global_hooks)(0x40);
  while (puVar11 = puVar6, puVar11 != (undefined8 *)0x0) {
    puVar11[1] = 0;
    *puVar11 = 0;
    puVar11[3] = 0;
    puVar11[2] = 0;
    puVar11[5] = 0;
    puVar11[4] = 0;
    puVar11[7] = 0;
    puVar11[6] = 0;
    uVar18 = local_18[6];
    pcVar14 = (char *)local_18[4];
    uVar1 = *(undefined4 *)(local_18 + 5);
    *(uint *)(puVar11 + 3) = *(uint *)(local_18 + 3) & 0xfffffeff;
    *(undefined4 *)(puVar11 + 5) = uVar1;
    puVar11[6] = uVar18;
    if (pcVar14 != (char *)0x0) {
      sVar4 = strlen(pcVar14);
      pvVar5 = (void *)(*(code *)global_hooks)(sVar4 + 1);
      if (pvVar5 != (void *)0x0) {
        memcpy(pvVar5,pcVar14,sVar4 + 1);
        puVar11[4] = pvVar5;
        goto LAB_001f832c;
      }
      puVar11[4] = 0;
LAB_001f859c:
      cJSON_Delete(puVar11);
      break;
    }
LAB_001f832c:
    pcVar14 = (char *)local_18[7];
    if (pcVar14 != (char *)0x0) {
      if ((*(uint *)(local_18 + 3) >> 9 & 1) == 0) {
        sVar4 = strlen(pcVar14);
        pvVar5 = (void *)(*(code *)global_hooks)(sVar4 + 1);
        if (pvVar5 == (void *)0x0) {
          puVar11[7] = 0;
          goto LAB_001f859c;
        }
        memcpy(pvVar5,pcVar14,sVar4 + 1);
        puVar11[7] = pvVar5;
      }
      else {
        puVar11[7] = pcVar14;
      }
    }
    local_30 = (long *)local_18[2];
    if (local_30 == (long *)0x0) {
      local_38 = (undefined8 *)0x0;
    }
    else {
      local_28 = (undefined8 *)0x0;
LAB_001f835c:
      do {
        puVar6 = (undefined8 *)(*(code *)global_hooks)(0x40);
        if (puVar6 == (undefined8 *)0x0) goto LAB_001f859c;
        puVar6[1] = 0;
        *puVar6 = 0;
        puVar6[3] = 0;
        puVar6[2] = 0;
        puVar6[5] = 0;
        puVar6[4] = 0;
        puVar6[7] = 0;
        puVar6[6] = 0;
        lVar19 = local_30[6];
        pcVar14 = (char *)local_30[4];
        lVar2 = local_30[5];
        *(uint *)(puVar6 + 3) = *(uint *)(local_30 + 3) & 0xfffffeff;
        *(int *)(puVar6 + 5) = (int)lVar2;
        puVar6[6] = lVar19;
        if (pcVar14 != (char *)0x0) {
          sVar4 = strlen(pcVar14);
          pvVar5 = (void *)(*(code *)global_hooks)(sVar4 + 1);
          if (pvVar5 != (void *)0x0) {
            memcpy(pvVar5,pcVar14,sVar4 + 1);
            puVar6[4] = pvVar5;
            goto LAB_001f83dc;
          }
          puVar6[4] = 0;
LAB_001f8594:
          cJSON_Delete(puVar6);
          goto LAB_001f859c;
        }
LAB_001f83dc:
        pcVar14 = (char *)local_30[7];
        if (pcVar14 != (char *)0x0) {
          if ((*(uint *)(local_30 + 3) >> 9 & 1) == 0) {
            sVar4 = strlen(pcVar14);
            pvVar5 = (void *)(*(code *)global_hooks)(sVar4 + 1);
            if (pvVar5 == (void *)0x0) {
              puVar6[7] = 0;
              goto LAB_001f8594;
            }
            memcpy(pvVar5,pcVar14,sVar4 + 1);
            puVar6[7] = pvVar5;
          }
          else {
            puVar6[7] = pcVar14;
          }
        }
        plVar13 = (long *)local_30[2];
        if (plVar13 == (long *)0x0) {
          puVar12 = (undefined8 *)0x0;
        }
        else {
          puVar15 = (undefined8 *)0x0;
LAB_001f8408:
          do {
            puVar7 = (undefined8 *)(*(code *)global_hooks)(0x40);
            if (puVar7 == (undefined8 *)0x0) goto LAB_001f8594;
            puVar7[1] = 0;
            *puVar7 = 0;
            puVar7[3] = 0;
            puVar7[2] = 0;
            puVar7[5] = 0;
            puVar7[4] = 0;
            puVar7[7] = 0;
            puVar7[6] = 0;
            lVar19 = plVar13[6];
            pcVar14 = (char *)plVar13[4];
            lVar2 = plVar13[5];
            *(uint *)(puVar7 + 3) = *(uint *)(plVar13 + 3) & 0xfffffeff;
            *(int *)(puVar7 + 5) = (int)lVar2;
            puVar7[6] = lVar19;
            if (pcVar14 != (char *)0x0) {
              sVar4 = strlen(pcVar14);
              pvVar5 = (void *)(*(code *)global_hooks)(sVar4 + 1);
              if (pvVar5 != (void *)0x0) {
                memcpy(pvVar5,pcVar14,sVar4 + 1);
                puVar7[4] = pvVar5;
                goto LAB_001f847c;
              }
              puVar7[4] = 0;
LAB_001f858c:
              cJSON_Delete(puVar7);
              goto LAB_001f8594;
            }
LAB_001f847c:
            pcVar14 = (char *)plVar13[7];
            if (pcVar14 != (char *)0x0) {
              if ((*(uint *)(plVar13 + 3) >> 9 & 1) == 0) {
                sVar4 = strlen(pcVar14);
                pvVar5 = (void *)(*(code *)global_hooks)(sVar4 + 1);
                if (pvVar5 == (void *)0x0) {
                  puVar7[7] = 0;
                  goto LAB_001f858c;
                }
                memcpy(pvVar5,pcVar14,sVar4 + 1);
                puVar7[7] = pvVar5;
              }
              else {
                puVar7[7] = pcVar14;
              }
            }
            plVar17 = (long *)plVar13[2];
            if (plVar17 == (long *)0x0) {
              puVar8 = (undefined8 *)0x0;
            }
            else {
              puVar12 = (undefined8 *)0x0;
LAB_001f84a0:
              do {
                puVar8 = (undefined8 *)(*(code *)global_hooks)(0x40);
                if (puVar8 == (undefined8 *)0x0) goto LAB_001f858c;
                puVar8[1] = 0;
                *puVar8 = 0;
                puVar8[3] = 0;
                puVar8[2] = 0;
                puVar8[5] = 0;
                puVar8[4] = 0;
                puVar8[7] = 0;
                puVar8[6] = 0;
                lVar19 = plVar17[6];
                pcVar14 = (char *)plVar17[4];
                lVar2 = plVar17[5];
                *(uint *)(puVar8 + 3) = *(uint *)(plVar17 + 3) & 0xfffffeff;
                *(int *)(puVar8 + 5) = (int)lVar2;
                puVar8[6] = lVar19;
                if (pcVar14 != (char *)0x0) {
                  sVar4 = strlen(pcVar14);
                  pvVar5 = (void *)(*(code *)global_hooks)(sVar4 + 1);
                  if (pvVar5 != (void *)0x0) {
                    memcpy(pvVar5,pcVar14,sVar4 + 1);
                    puVar8[4] = pvVar5;
                    goto LAB_001f8514;
                  }
                  puVar8[4] = 0;
LAB_001f8584:
                  cJSON_Delete(puVar8);
                  goto LAB_001f858c;
                }
LAB_001f8514:
                pcVar14 = (char *)plVar17[7];
                if (pcVar14 != (char *)0x0) {
                  if ((*(uint *)(plVar17 + 3) >> 9 & 1) == 0) {
                    sVar4 = strlen(pcVar14);
                    pvVar5 = (void *)(*(code *)global_hooks)(sVar4 + 1);
                    if (pvVar5 == (void *)0x0) {
                      puVar8[7] = 0;
                      goto LAB_001f8584;
                    }
                    memcpy(pvVar5,pcVar14,sVar4 + 1);
                    puVar8[7] = pvVar5;
                  }
                  else {
                    puVar8[7] = pcVar14;
                  }
                }
                local_40 = (long *)plVar17[2];
                if (local_40 != (long *)0x0) {
                  plVar9 = (long *)cJSON_Duplicate_rec(local_40,5,1);
                  plVar16 = (long *)0x0;
                  if (plVar9 != (long *)0x0) {
                    do {
                      plVar10 = plVar9;
                      if (plVar16 == (long *)0x0) {
                        local_40 = (long *)*local_40;
                        puVar8[2] = plVar10;
                        if (local_40 == (long *)0x0) {
                          plVar10[1] = (long)plVar10;
                          goto LAB_001f85e4;
                        }
                      }
                      else {
                        *plVar16 = (long)plVar10;
                        local_40 = (long *)*local_40;
                        plVar10[1] = (long)plVar16;
                        if (local_40 == (long *)0x0) goto LAB_001f85d8;
                      }
                      plVar9 = (long *)cJSON_Duplicate_rec(local_40,5,1);
                      plVar16 = plVar10;
                      if (plVar9 == (long *)0x0) break;
                    } while( true );
                  }
                  goto LAB_001f8584;
                }
                plVar10 = (long *)0x0;
LAB_001f85d8:
                if (puVar8[2] != 0) {
                  *(long **)(puVar8[2] + 8) = plVar10;
                }
LAB_001f85e4:
                if (puVar12 == (undefined8 *)0x0) {
                  plVar17 = (long *)*plVar17;
                  puVar7[2] = puVar8;
                  puVar12 = puVar8;
                  if (plVar17 == (long *)0x0) {
                    puVar8[1] = puVar8;
                    goto LAB_001f8614;
                  }
                  goto LAB_001f84a0;
                }
                *puVar12 = puVar8;
                plVar17 = (long *)*plVar17;
                puVar8[1] = puVar12;
                puVar12 = puVar8;
              } while (plVar17 != (long *)0x0);
            }
            if (puVar7[2] != 0) {
              *(undefined8 **)(puVar7[2] + 8) = puVar8;
            }
LAB_001f8614:
            puVar12 = puVar7;
            if (puVar15 == (undefined8 *)0x0) {
              plVar13 = (long *)*plVar13;
              puVar6[2] = puVar7;
              puVar15 = puVar7;
              if (plVar13 == (long *)0x0) goto LAB_001f8640;
              goto LAB_001f8408;
            }
            *puVar15 = puVar7;
            plVar13 = (long *)*plVar13;
            puVar7[1] = puVar15;
            puVar15 = puVar7;
          } while (plVar13 != (long *)0x0);
        }
        puVar7 = (undefined8 *)puVar6[2];
        if (puVar7 != (undefined8 *)0x0) {
LAB_001f8640:
          puVar7[1] = puVar12;
        }
        local_38 = puVar6;
        if (local_28 == (undefined8 *)0x0) {
          local_30 = (long *)*local_30;
          puVar11[2] = puVar6;
          local_28 = puVar6;
          if (local_30 == (long *)0x0) goto LAB_001f8788;
          goto LAB_001f835c;
        }
        *local_28 = puVar6;
        puVar6[1] = local_28;
        local_30 = (long *)*local_30;
        local_28 = puVar6;
      } while (local_30 != (long *)0x0);
    }
    puVar6 = (undefined8 *)puVar11[2];
    if (puVar6 != (undefined8 *)0x0) {
LAB_001f8788:
      puVar6[1] = local_38;
    }
    if (local_8 == (undefined8 *)0x0) {
      puVar6 = (undefined8 *)*local_18;
      puVar3[2] = puVar11;
      local_18 = puVar11;
      if (puVar6 == (undefined8 *)0x0) goto LAB_001f890c;
    }
    else {
      *local_8 = puVar11;
      puVar11[1] = local_8;
      puVar6 = (undefined8 *)*local_18;
      local_18 = puVar11;
      if (puVar6 == (undefined8 *)0x0) goto LAB_001f8900;
    }
    local_18 = puVar6;
    puVar6 = (undefined8 *)(*(code *)global_hooks)(0x40);
    local_8 = puVar11;
  }
LAB_001f85a8:
  cJSON_Delete(puVar3);
  return (undefined8 *)0x0;
}

