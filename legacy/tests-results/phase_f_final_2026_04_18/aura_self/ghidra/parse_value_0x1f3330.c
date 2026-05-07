
void parse_value(long param_1,long *param_2)

{
  uint uVar1;
  ulong uVar2;
  char cVar3;
  int iVar4;
  undefined8 uVar5;
  ulong uVar6;
  undefined8 *puVar7;
  char *pcVar8;
  code *pcVar9;
  ulong uVar10;
  undefined8 *puVar11;
  size_t __n;
  undefined8 *puVar12;
  undefined8 *puVar13;
  long lVar14;
  double dVar15;
  char *local_60;
  long local_58;
  
  local_58 = *(long *)PTR___stack_chk_guard_005ffe88;
  if ((param_2 == (long *)0x0) || (lVar14 = *param_2, lVar14 == 0)) goto LAB_001f3424;
  uVar2 = param_2[1];
  uVar10 = param_2[2];
  uVar6 = uVar10 + 4;
  if (uVar2 < uVar6) {
    if ((uVar2 < uVar10 + 5) || (iVar4 = strncmp((char *)(lVar14 + uVar10),"false",5), iVar4 != 0))
    {
LAB_001f33e0:
      if (uVar2 <= uVar10) goto LAB_001f3424;
      cVar3 = *(char *)(lVar14 + uVar10);
      if (cVar3 == '\"') {
        if (local_58 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
          parse_string(param_1,param_2);
          return;
        }
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                         local_58 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      if (cVar3 == '-' || (byte)(cVar3 - 0x30U) < 10) {
        __n = 0;
        local_60 = (char *)0x0;
        do {
          uVar1 = *(byte *)(lVar14 + uVar10 + __n) - 0x2b & 0xff;
          if ((0x3a < uVar1) || ((0x400000004007fedU >> ((ulong)uVar1 & 0x3f) & 1) == 0)) break;
          __n = __n + 1;
        } while (uVar2 - uVar10 != __n);
        pcVar8 = (char *)(*(code *)param_2[4])(__n + 1);
        if (pcVar8 != (char *)0x0) {
          memcpy(pcVar8,(void *)(*param_2 + param_2[2]),__n);
          pcVar8[__n] = '\0';
          dVar15 = strtod(pcVar8,&local_60);
          if (pcVar8 != local_60) {
            iVar4 = 0x7fffffff;
            if ((dVar15 < 2147483647.0) && (iVar4 = -0x80000000, -2147483648.0 < dVar15)) {
              iVar4 = (int)dVar15;
            }
            lVar14 = param_2[2];
            pcVar9 = (code *)param_2[5];
            *(undefined4 *)(param_1 + 0x18) = 8;
            *(int *)(param_1 + 0x28) = iVar4;
            *(double *)(param_1 + 0x30) = dVar15;
            param_2[2] = (long)(local_60 + (lVar14 - (long)pcVar8));
            (*pcVar9)(pcVar8);
            uVar5 = 1;
            goto LAB_001f3468;
          }
          (*(code *)param_2[5])(pcVar8);
        }
        uVar5 = 0;
        goto LAB_001f3468;
      }
      if (cVar3 == '[') {
        uVar6 = param_2[3];
        if ((uVar6 < 1000) && (param_2[3] = uVar6 + 1, *(char *)(lVar14 + uVar10) == '[')) {
          uVar10 = uVar10 + 1;
          param_2[2] = uVar10;
          if (uVar10 < uVar2) {
            do {
              if (0x20 < *(byte *)(lVar14 + uVar10)) {
                if (uVar2 == uVar10) goto LAB_001f3a80;
                uVar10 = param_2[2];
                if (uVar2 <= uVar10) goto LAB_001f3a34;
                goto LAB_001f389c;
              }
              uVar10 = uVar10 + 1;
              param_2[2] = uVar10;
            } while (uVar10 < uVar2);
            if (uVar2 == uVar10) {
LAB_001f3a80:
              uVar10 = uVar10 - 1;
              param_2[2] = uVar10;
LAB_001f389c:
              if (*(char *)(lVar14 + uVar10) == ']') {
                puVar13 = (undefined8 *)0x0;
                param_2[3] = uVar6;
              }
              else {
                param_2[2] = uVar10 - 1;
                puVar11 = (undefined8 *)0x0;
                puVar12 = (undefined8 *)0x0;
                do {
                  puVar7 = (undefined8 *)(*(code *)param_2[4])(0x40);
                  puVar13 = puVar12;
                  if (puVar7 == (undefined8 *)0x0) goto LAB_001f3a40;
                  puVar7[1] = 0;
                  *puVar7 = 0;
                  puVar7[3] = 0;
                  puVar7[2] = 0;
                  puVar7[5] = 0;
                  puVar7[4] = 0;
                  puVar7[7] = 0;
                  puVar7[6] = 0;
                  puVar13 = puVar7;
                  if (puVar12 != (undefined8 *)0x0) {
                    *puVar11 = puVar7;
                    puVar7[1] = puVar11;
                    puVar13 = puVar12;
                  }
                  uVar10 = param_2[2] + 1;
                  param_2[2] = uVar10;
                  if ((*param_2 != 0) && (uVar6 = param_2[1], uVar10 < uVar6)) {
                    do {
                      if (0x20 < *(byte *)(*param_2 + uVar10)) break;
                      uVar10 = uVar10 + 1;
                      param_2[2] = uVar10;
                    } while (uVar10 < uVar6);
                    if (uVar6 == uVar10) {
                      param_2[2] = uVar6 - 1;
                    }
                  }
                  iVar4 = parse_value(puVar7,param_2);
                  if (iVar4 == 0) goto LAB_001f3a18;
                  lVar14 = *param_2;
                  uVar6 = param_2[1];
                  uVar10 = param_2[2];
                  if (lVar14 == 0) {
LAB_001f3984:
                    if (uVar6 <= uVar10) goto LAB_001f3a18;
                  }
                  else {
                    if (uVar6 <= uVar10) goto LAB_001f3a18;
                    do {
                      if (0x20 < *(byte *)(lVar14 + uVar10)) {
                        if (uVar10 != uVar6) goto LAB_001f3984;
                        break;
                      }
                      uVar10 = uVar10 + 1;
                      param_2[2] = uVar10;
                    } while (uVar10 != uVar6);
                    uVar10 = uVar6 - 1;
                    param_2[2] = uVar10;
                  }
                  puVar11 = puVar7;
                  puVar12 = puVar13;
                } while (*(char *)(lVar14 + uVar10) == ',');
                if ((uVar6 <= uVar10) || (*(char *)(lVar14 + uVar10) != ']')) goto LAB_001f3a18;
                param_2[3] = param_2[3] + -1;
                puVar13[1] = puVar7;
              }
              lVar14 = param_2[2];
              *(undefined8 **)(param_1 + 0x10) = puVar13;
              uVar6 = lVar14 + 1;
              *(undefined4 *)(param_1 + 0x18) = 0x20;
              goto LAB_001f3458;
            }
          }
          goto LAB_001f3a34;
        }
      }
      else if (((cVar3 == '{') && (uVar6 = param_2[3], uVar6 < 1000)) &&
              (param_2[3] = uVar6 + 1, *(char *)(lVar14 + uVar10) == '{')) {
        uVar10 = uVar10 + 1;
        param_2[2] = uVar10;
        if (uVar10 < uVar2) {
          do {
            if (0x20 < *(byte *)(lVar14 + uVar10)) {
              if (uVar2 == uVar10) goto LAB_001f3a94;
              uVar10 = param_2[2];
              if (uVar2 <= uVar10) goto LAB_001f3a34;
              goto LAB_001f3524;
            }
            uVar10 = uVar10 + 1;
            param_2[2] = uVar10;
          } while (uVar10 < uVar2);
          if (uVar2 == uVar10) {
LAB_001f3a94:
            uVar10 = uVar10 - 1;
            param_2[2] = uVar10;
LAB_001f3524:
            if (*(char *)(lVar14 + uVar10) == '}') {
              puVar13 = (undefined8 *)0x0;
              param_2[3] = uVar6;
            }
            else {
              param_2[2] = uVar10 - 1;
              puVar11 = (undefined8 *)0x0;
              puVar12 = (undefined8 *)0x0;
              do {
                puVar7 = (undefined8 *)(*(code *)param_2[4])(0x40);
                puVar13 = puVar12;
                if (puVar7 == (undefined8 *)0x0) goto LAB_001f3a40;
                puVar7[1] = 0;
                *puVar7 = 0;
                puVar7[3] = 0;
                puVar7[2] = 0;
                puVar7[5] = 0;
                puVar7[4] = 0;
                puVar7[7] = 0;
                puVar7[6] = 0;
                puVar13 = puVar7;
                if (puVar12 != (undefined8 *)0x0) {
                  *puVar11 = puVar7;
                  puVar7[1] = puVar11;
                  puVar13 = puVar12;
                }
                uVar6 = param_2[1];
                uVar10 = param_2[2] + 1;
                if (uVar6 <= uVar10) goto LAB_001f3a18;
                param_2[2] = uVar10;
                if (*param_2 != 0) {
                  do {
                    if (0x20 < *(byte *)(*param_2 + uVar10)) break;
                    uVar10 = uVar10 + 1;
                    param_2[2] = uVar10;
                  } while (uVar10 < uVar6);
                  if (uVar6 == uVar10) {
                    param_2[2] = uVar6 - 1;
                  }
                }
                iVar4 = parse_string(puVar7,param_2);
                if (iVar4 == 0) goto LAB_001f3a18;
                lVar14 = *param_2;
                uVar6 = param_2[1];
                uVar10 = param_2[2];
                if (lVar14 == 0) {
LAB_001f360c:
                  uVar5 = puVar7[4];
                  puVar7[4] = 0;
                  puVar7[7] = uVar5;
                  if (uVar6 <= uVar10) goto LAB_001f3a18;
                }
                else {
                  if (uVar6 <= uVar10) {
                    uVar5 = puVar7[4];
                    puVar7[4] = 0;
                    puVar7[7] = uVar5;
                    goto LAB_001f3a18;
                  }
                  do {
                    if (0x20 < *(byte *)(lVar14 + uVar10)) {
                      if (uVar10 != uVar6) {
                        uVar10 = param_2[2];
                        goto LAB_001f360c;
                      }
                      break;
                    }
                    uVar10 = uVar10 + 1;
                    param_2[2] = uVar10;
                  } while (uVar10 != uVar6);
                  uVar5 = puVar7[4];
                  uVar10 = uVar6 - 1;
                  param_2[2] = uVar10;
                  puVar7[4] = 0;
                  puVar7[7] = uVar5;
                }
                if (*(char *)(lVar14 + uVar10) != ':') goto LAB_001f3a18;
                uVar10 = uVar10 + 1;
                param_2[2] = uVar10;
                if (lVar14 != 0 && uVar10 < uVar6) {
                  do {
                    if (0x20 < *(byte *)(lVar14 + uVar10)) break;
                    uVar10 = uVar10 + 1;
                    param_2[2] = uVar10;
                  } while (uVar10 < uVar6);
                  if (uVar10 == uVar6) {
                    param_2[2] = uVar10 - 1;
                  }
                }
                iVar4 = parse_value(puVar7,param_2);
                if (iVar4 == 0) goto LAB_001f3a18;
                lVar14 = *param_2;
                uVar6 = param_2[1];
                uVar10 = param_2[2];
                if (lVar14 == 0) {
LAB_001f36bc:
                  if (uVar6 <= uVar10) goto LAB_001f3a18;
                }
                else {
                  if (uVar6 <= uVar10) goto LAB_001f3a18;
                  do {
                    if (0x20 < *(byte *)(lVar14 + uVar10)) {
                      if (uVar10 != uVar6) goto LAB_001f36bc;
                      break;
                    }
                    uVar10 = uVar10 + 1;
                    param_2[2] = uVar10;
                  } while (uVar10 != uVar6);
                  uVar10 = uVar6 - 1;
                  param_2[2] = uVar10;
                }
                puVar11 = puVar7;
                puVar12 = puVar13;
              } while (*(char *)(lVar14 + uVar10) == ',');
              if ((uVar6 <= uVar10) || (*(char *)(lVar14 + uVar10) != '}')) {
LAB_001f3a18:
                cJSON_Delete(puVar13);
                uVar5 = 0;
                goto LAB_001f3468;
              }
              param_2[3] = param_2[3] + -1;
              puVar13[1] = puVar7;
            }
            lVar14 = param_2[2];
            *(undefined8 **)(param_1 + 0x10) = puVar13;
            uVar6 = lVar14 + 1;
            *(undefined4 *)(param_1 + 0x18) = 0x40;
            goto LAB_001f3458;
          }
        }
LAB_001f3a34:
        param_2[2] = uVar10 - 1;
      }
LAB_001f3424:
      uVar5 = 0;
      goto LAB_001f3468;
    }
LAB_001f3450:
    uVar6 = uVar10 + 5;
    *(undefined4 *)(param_1 + 0x18) = 1;
  }
  else {
    pcVar8 = (char *)(lVar14 + uVar10);
    iVar4 = strncmp(pcVar8,"null",4);
    if (iVar4 == 0) {
      *(undefined4 *)(param_1 + 0x18) = 4;
    }
    else {
      if ((uVar10 + 5 <= uVar2) && (iVar4 = strncmp(pcVar8,"false",5), iVar4 == 0))
      goto LAB_001f3450;
      iVar4 = strncmp(pcVar8,"true",4);
      if (iVar4 != 0) goto LAB_001f33e0;
      *(undefined4 *)(param_1 + 0x18) = 2;
      *(undefined4 *)(param_1 + 0x28) = 1;
    }
  }
LAB_001f3458:
  param_2[2] = uVar6;
  uVar5 = 1;
LAB_001f3468:
  if (local_58 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(uVar5,PTR___stack_chk_guard_005ffe88,0,
                   local_58 - *(long *)PTR___stack_chk_guard_005ffe88);
LAB_001f3a40:
  if (puVar13 == (undefined8 *)0x0) {
    uVar5 = 0;
    goto LAB_001f3468;
  }
  goto LAB_001f3a18;
}

