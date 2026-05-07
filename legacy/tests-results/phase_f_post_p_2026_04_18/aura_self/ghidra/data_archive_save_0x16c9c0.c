
undefined8 data_archive_save(long *param_1,char *param_2)

{
  long lVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  undefined8 uVar5;
  char *__s;
  FILE *__s_00;
  size_t __n;
  size_t sVar6;
  long lVar7;
  long lVar8;
  
  if (param_1 == (long *)0x0 || param_2 == (char *)0x0) {
    uVar5 = 0xfffffffc;
  }
  else {
    lVar1 = cJSON_CreateObject();
    if (lVar1 != 0) {
      cJSON_AddNumberToObject((double)*(uint *)((long)param_1 + 0xc),lVar1,"version");
      if (param_1[2] != 0) {
        cJSON_AddStringToObject(lVar1,"description");
      }
      lVar2 = cJSON_AddArrayToObject(lVar1,"types");
      if (lVar2 == 0) {
        cJSON_Delete(lVar1);
      }
      else {
        lVar7 = 0;
        if ((int)param_1[1] != 0) {
          do {
            lVar8 = *param_1;
            lVar4 = cJSON_CreateObject();
            lVar3 = lVar8 + lVar7 * 0x20;
            if (lVar4 == 0) {
              cJSON_Delete(lVar1);
              goto LAB_0016cb24;
            }
            if (*(long *)(lVar8 + lVar7 * 0x20) != 0) {
              cJSON_AddStringToObject(lVar4,&DAT_001fac70);
            }
            if (*(long *)(lVar3 + 8) != 0) {
              cJSON_AddStringToObject(lVar4,"category");
            }
            cJSON_AddNumberToObject((double)*(uint *)(lVar3 + 0x18),lVar4,&DAT_001fac88);
            cJSON_AddNumberToObject((double)*(uint *)(lVar3 + 0x1c),lVar4,"alignment");
            if ((*(long *)(lVar3 + 0x10) != 0) && (lVar3 = cJSON_Parse(), lVar3 != 0)) {
              cJSON_AddItemToObject(lVar4,"fields",lVar3);
            }
            cJSON_AddItemToArray(lVar2,lVar4);
            lVar7 = lVar7 + 1;
          } while ((uint)lVar7 < *(uint *)(param_1 + 1));
        }
        __s = (char *)cJSON_Print(lVar1);
        cJSON_Delete(lVar1);
        if (__s != (char *)0x0) {
          __s_00 = fopen(param_2,"w");
          if (__s_00 == (FILE *)0x0) {
            cJSON_free(__s);
          }
          else {
            __n = strlen(__s);
            sVar6 = fwrite(__s,1,__n,__s_00);
            fclose(__s_00);
            cJSON_free(__s);
            if (__n == sVar6) {
              return 0;
            }
          }
          return 0xfffffffd;
        }
      }
    }
LAB_0016cb24:
    uVar5 = 0xfffffffe;
  }
  return uVar5;
}

