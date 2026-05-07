
long * data_archive_load(char *param_1)

{
  long lVar1;
  int iVar2;
  uint uVar3;
  FILE *__stream;
  ulong uVar4;
  void *pvVar5;
  size_t sVar6;
  long lVar7;
  long lVar8;
  long lVar9;
  long *plVar10;
  long lVar11;
  long lVar12;
  long lVar13;
  char *pcVar14;
  undefined8 uVar15;
  undefined4 uVar16;
  long lVar17;
  long *plVar18;
  long *local_70;
  long local_68;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (param_1 == (char *)0x0) {
LAB_0016d7c0:
    plVar10 = (long *)0x0;
  }
  else {
    __stream = fopen(param_1,"rb");
    if (__stream == (FILE *)0x0) {
      plVar10 = (long *)0x0;
      goto LAB_0016d760;
    }
    iVar2 = fseek(__stream,0,2);
    if (iVar2 != 0) {
      plVar10 = (long *)0x0;
      fclose(__stream);
      goto LAB_0016d760;
    }
    uVar4 = ftell(__stream);
    if (uVar4 < 0x6400001) {
      rewind(__stream);
      pvVar5 = malloc(uVar4 + 1);
      if (pvVar5 != (void *)0x0) {
        sVar6 = fread(pvVar5,1,uVar4,__stream);
        fclose(__stream);
        *(undefined1 *)((long)pvVar5 + sVar6) = 0;
        lVar7 = cJSON_Parse(pvVar5);
        free(pvVar5);
        if (lVar7 == 0) {
          plVar10 = (long *)0x0;
          goto LAB_0016d760;
        }
        lVar8 = cJSON_GetObjectItemCaseSensitive(lVar7,"version");
        iVar2 = cJSON_IsNumber();
        if (iVar2 != 0) {
          lVar9 = cJSON_GetObjectItemCaseSensitive(lVar7,"types");
          iVar2 = cJSON_IsArray();
          if (iVar2 != 0) {
            uVar3 = cJSON_GetArraySize(lVar9);
            if ((int)uVar3 < 0) {
              uVar3 = 0;
            }
            else if (0x1000 < uVar3) goto LAB_0016d7b0;
            plVar10 = calloc(1,0x18);
            local_70 = plVar10;
            if (plVar10 != (long *)0x0) {
              *(undefined4 *)((long)plVar10 + 0xc) = *(undefined4 *)(lVar8 + 0x28);
              lVar8 = cJSON_GetObjectItemCaseSensitive(lVar7,"description");
              iVar2 = cJSON_IsString();
              if ((iVar2 != 0) && (*(char **)(lVar8 + 0x20) != (char *)0x0)) {
                pcVar14 = strdup(*(char **)(lVar8 + 0x20));
                plVar10[2] = (long)pcVar14;
              }
              if (uVar3 != 0) {
                pvVar5 = calloc((long)(int)uVar3,0x20);
                *plVar10 = (long)pvVar5;
                if (pvVar5 == (void *)0x0) {
                  data_archive_destroy(&local_70);
                  goto LAB_0016d7b0;
                }
              }
              uVar4 = 0;
              if (lVar9 != 0) {
                for (plVar18 = *(long **)(lVar9 + 0x10); plVar18 != (long *)0x0;
                    plVar18 = (long *)*plVar18) {
                  iVar2 = cJSON_IsObject(plVar18);
                  if (iVar2 != 0) {
                    lVar8 = cJSON_GetObjectItemCaseSensitive(plVar18,&DAT_001fc1e0);
                    lVar9 = cJSON_GetObjectItemCaseSensitive(plVar18,"category");
                    lVar11 = cJSON_GetObjectItemCaseSensitive(plVar18,&DAT_001fc1f8);
                    lVar12 = cJSON_GetObjectItemCaseSensitive(plVar18,"alignment");
                    lVar13 = cJSON_GetObjectItemCaseSensitive(plVar18,"fields");
                    iVar2 = cJSON_IsString(lVar8);
                    if ((iVar2 != 0) && (*(char **)(lVar8 + 0x20) != (char *)0x0)) {
                      lVar17 = *plVar10;
                      lVar1 = lVar17 + uVar4 * 0x20;
                      pcVar14 = strdup(*(char **)(lVar8 + 0x20));
                      *(char **)(lVar17 + uVar4 * 0x20) = pcVar14;
                      iVar2 = cJSON_IsString(lVar9);
                      pcVar14 = (char *)0x0;
                      if (iVar2 != 0) {
                        pcVar14 = (char *)0x0;
                        if (*(char **)(lVar9 + 0x20) != (char *)0x0) {
                          pcVar14 = strdup(*(char **)(lVar9 + 0x20));
                        }
                      }
                      *(char **)(lVar1 + 8) = pcVar14;
                      iVar2 = cJSON_IsNumber(lVar11);
                      uVar16 = 0;
                      if (iVar2 != 0) {
                        uVar16 = *(undefined4 *)(lVar11 + 0x28);
                      }
                      *(undefined4 *)(lVar1 + 0x18) = uVar16;
                      iVar2 = cJSON_IsNumber(lVar12);
                      uVar16 = 0;
                      if (iVar2 != 0) {
                        uVar16 = *(undefined4 *)(lVar12 + 0x28);
                      }
                      *(undefined4 *)(lVar1 + 0x1c) = uVar16;
                      if ((lVar13 != 0) &&
                         ((iVar2 = cJSON_IsArray(lVar13), iVar2 != 0 ||
                          (iVar2 = cJSON_IsObject(lVar13), iVar2 != 0)))) {
                        uVar15 = cJSON_PrintUnformatted(lVar13);
                        *(undefined8 *)(lVar1 + 0x10) = uVar15;
                      }
                      uVar4 = (ulong)((int)uVar4 + 1);
                    }
                  }
                }
              }
              *(int *)(plVar10 + 1) = (int)uVar4;
              cJSON_Delete(lVar7);
              goto LAB_0016d760;
            }
          }
        }
LAB_0016d7b0:
        cJSON_Delete(lVar7);
        goto LAB_0016d7c0;
      }
    }
    fclose(__stream);
    plVar10 = (long *)0x0;
  }
LAB_0016d760:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return plVar10;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                   local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
}

