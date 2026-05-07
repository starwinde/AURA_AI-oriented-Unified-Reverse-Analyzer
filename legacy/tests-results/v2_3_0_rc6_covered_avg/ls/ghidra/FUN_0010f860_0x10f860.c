
void FUN_0010f860(char *param_1,undefined1 param_2)

{
  int iVar1;
  bool bVar2;
  bool bVar3;
  undefined8 *puVar4;
  char cVar5;
  undefined8 *puVar6;
  undefined8 uVar7;
  size_t sVar8;
  void *__ptr;
  undefined1 *puVar9;
  void *pvVar10;
  long lVar11;
  char cVar12;
  long lVar13;
  char *pcVar14;
  char *pcVar15;
  char *pcVar16;
  long lVar17;
  long lVar18;
  ulong uVar19;
  char *__s;
  long local_18;
  undefined1 local_4;
  
  lVar18 = DAT_00140ee0;
  if ((param_1 != (char *)0x0) && (DAT_00141350 != 0)) {
    puVar6 = malloc(0x20);
    if (puVar6 == (undefined8 *)0x0) {
LAB_0010fc34:
                    /* WARNING: Subroutine does not return */
      FUN_0010d454();
    }
    uVar7 = FUN_0010f784(param_1);
    puVar4 = DAT_00141348;
    DAT_00141348 = puVar6;
    *puVar6 = 0;
    puVar6[1] = uVar7;
    lVar18 = DAT_00140ee0;
    *(undefined1 *)(puVar6 + 2) = 0;
    puVar6[3] = puVar4;
  }
  if (lVar18 != 0) {
    lVar18 = lVar18 + -1;
    do {
      while( true ) {
        puVar6 = *(undefined8 **)(DAT_00140ee8 + lVar18 * 8);
        iVar1 = *(int *)(puVar6 + 0x13);
        bVar2 = iVar1 == 3 || iVar1 == 9;
        if (iVar1 == 3 || iVar1 == 9) break;
joined_r0x0010fbd4:
        lVar18 = lVar18 + -1;
        if (lVar18 == -1) goto LAB_0010faf4;
      }
      __s = (char *)*puVar6;
      if (param_1 == (char *)0x0) {
LAB_0010fb54:
        FUN_0010f7d0(__s,puVar6[1],param_2);
      }
      else {
        cVar5 = *__s;
        pcVar14 = __s;
        if (cVar5 == '/') {
          do {
            pcVar14 = pcVar14 + 1;
            cVar12 = *pcVar14;
          } while (cVar12 == '/');
          if (cVar12 != '\0') {
LAB_0010f968:
            pcVar15 = pcVar14;
            bVar3 = false;
            do {
              while (cVar12 == '/') {
                pcVar14 = pcVar14 + 1;
                cVar12 = *pcVar14;
                pcVar16 = pcVar15;
                bVar3 = bVar2;
                if (cVar12 == '\0') goto LAB_0010f99c;
              }
              pcVar16 = pcVar14;
              if (!bVar3) {
                pcVar16 = pcVar15;
              }
              pcVar14 = pcVar14 + 1;
              cVar12 = *pcVar14;
              if (bVar3) {
                bVar3 = false;
              }
              pcVar15 = pcVar16;
            } while (cVar12 != '\0');
LAB_0010f99c:
            if (*pcVar16 == '.') {
              if (pcVar16[1] == '.') {
                pcVar16 = pcVar16 + 1;
              }
              if (pcVar16[1] == '/' || pcVar16[1] == '\0') goto joined_r0x0010fbd4;
            }
            if (cVar5 != '/') goto LAB_0010f9b0;
          }
          goto LAB_0010fb54;
        }
        cVar12 = cVar5;
        if (cVar5 != '\0') goto LAB_0010f968;
LAB_0010f9b0:
        cVar5 = *param_1;
        pcVar14 = param_1;
        while (cVar5 == '/') {
          pcVar14 = pcVar14 + 1;
          cVar5 = *pcVar14;
        }
        pcVar15 = pcVar14;
        if (cVar5 != '\0') {
          pcVar16 = pcVar14;
          bVar3 = false;
          do {
            while (cVar5 == '/') {
              pcVar14 = pcVar14 + 1;
              cVar5 = *pcVar14;
              pcVar15 = pcVar16;
              bVar3 = bVar2;
              if (cVar5 == '\0') goto LAB_0010fa0c;
            }
            pcVar15 = pcVar14;
            if (!bVar3) {
              pcVar15 = pcVar16;
            }
            pcVar14 = pcVar14 + 1;
            cVar5 = *pcVar14;
            if (bVar3) {
              bVar3 = false;
            }
            pcVar16 = pcVar15;
          } while (cVar5 != '\0');
        }
LAB_0010fa0c:
        sVar8 = strlen(pcVar15);
        do {
          uVar19 = sVar8;
          if (uVar19 < 2) {
            pcVar15 = pcVar15 + (uVar19 - (long)param_1);
            sVar8 = strlen(__s);
            lVar11 = sVar8 + 1;
            if (uVar19 == 0) goto LAB_0010fbf8;
            goto LAB_0010fa48;
          }
          sVar8 = uVar19 - 1;
        } while (pcVar15[uVar19 - 1] == '/');
        pcVar15 = pcVar15 + (uVar19 - (long)param_1);
        sVar8 = strlen(__s);
        lVar11 = sVar8 + 1;
LAB_0010fa48:
        if (param_1[(long)(pcVar15 + -1)] == '/') {
LAB_0010fbf8:
          local_18 = 0;
          local_4 = 0;
        }
        else {
          local_18 = 1;
          local_4 = 0x2f;
        }
        __ptr = malloc((size_t)(pcVar15 + lVar11 + local_18));
        if (__ptr == (void *)0x0) goto LAB_0010fc34;
        puVar9 = (undefined1 *)__mempcpy_chk(__ptr,param_1,pcVar15,pcVar15 + lVar11 + local_18);
        *puVar9 = local_4;
        pvVar10 = memcpy(puVar9 + local_18,__s,sVar8);
        *(undefined1 *)((long)pvVar10 + sVar8) = 0;
        FUN_0010f7d0(__ptr,puVar6[1],param_2);
        free(__ptr);
        iVar1 = *(int *)(puVar6 + 0x13);
      }
      if (iVar1 != 9) goto joined_r0x0010fbd4;
      free((void *)*puVar6);
      free((void *)puVar6[1]);
      free((void *)puVar6[2]);
      if ((undefined *)puVar6[0x14] == &DAT_001400c8) goto joined_r0x0010fbd4;
      lVar18 = lVar18 + -1;
      freecon();
    } while (lVar18 != -1);
LAB_0010faf4:
    lVar18 = DAT_00140ee8;
    if (DAT_00140ee0 != 0) {
      lVar13 = 0;
      lVar11 = 0;
      do {
        lVar17 = *(long *)(lVar18 + lVar11 * 8);
        *(long *)(lVar18 + lVar13 * 8) = lVar17;
        lVar11 = lVar11 + 1;
        if (*(int *)(lVar17 + 0x98) != 9) {
          lVar13 = lVar13 + 1;
        }
      } while (lVar11 != DAT_00140ee0);
      DAT_00140ee0 = lVar13;
      return;
    }
  }
  DAT_00140ee0 = 0;
  return;
}

