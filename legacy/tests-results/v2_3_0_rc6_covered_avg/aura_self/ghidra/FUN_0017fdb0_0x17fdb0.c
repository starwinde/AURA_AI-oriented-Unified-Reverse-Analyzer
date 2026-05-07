
void FUN_0017fdb0(long *param_1,uint param_2,uint param_3,int *param_4)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined1 uVar6;
  long *plVar7;
  int *piVar8;
  undefined4 *puVar9;
  undefined8 uVar10;
  void *pvVar11;
  void *pvVar12;
  int *piVar13;
  undefined4 *puVar14;
  undefined4 *puVar15;
  undefined4 *puVar16;
  uint uVar17;
  long lVar18;
  void *pvVar19;
  long lVar20;
  long lVar21;
  uint uVar22;
  ulong uVar23;
  long lVar24;
  ulong uVar25;
  uint uVar26;
  size_t sVar27;
  long *local_10;
  
  plVar7 = (long *)*param_1;
  if (*(uint *)(plVar7 + 1) <= param_2 || param_3 == param_2) {
    return;
  }
  lVar18 = param_1[6];
  uVar25 = (ulong)param_2;
LAB_0017fdfc:
  do {
    if ((*(byte *)(lVar18 + uVar25) & 1) != 0) {
      return;
    }
    lVar21 = *plVar7;
    *(undefined1 *)(lVar18 + uVar25) = 1;
    lVar21 = lVar21 + uVar25 * 0x50;
    uVar17 = *(uint *)(lVar21 + 0x10) - 1;
    if (-1 < (int)uVar17) {
      piVar13 = (int *)(*(long *)(lVar21 + 8) + (long)(int)uVar17 * 0x90);
      do {
        piVar8 = piVar13 + -0x24;
        if (*piVar13 - 0x17U < 2 || *piVar13 == 0x1a) goto LAB_0017fe68;
        piVar13 = piVar8;
      } while (piVar8 != (int *)(*(long *)(lVar21 + 8) + -0x120 +
                                ((ulong)*(uint *)(lVar21 + 0x10) - (ulong)uVar17) * 0x90));
    }
    piVar13 = (int *)0x0;
LAB_0017fe68:
    plVar7 = (long *)param_1[2];
    if ((((plVar7 == (long *)0x0) ||
         (uVar17 = *(uint *)(plVar7[2] + uVar25 * 4), uVar17 == 0xffffffff)) ||
        (*(uint *)(plVar7 + 1) <= uVar17)) ||
       (lVar18 = *plVar7 + (ulong)uVar17 * 0x60,
       *(int *)(*plVar7 + (ulong)uVar17 * 0x60) != (int)uVar25)) {
      FUN_0017f720(param_1,uVar25,param_4);
      if (2 < *(uint *)(lVar21 + 0x30)) {
        puVar9 = calloc(1,0x130);
        if (puVar9 == (undefined4 *)0x0) {
          return;
        }
        *puVar9 = 5;
        if (piVar13 == (int *)0x0) goto LAB_001801a8;
LAB_001801a0:
        if (piVar13[0x12] == 0) goto LAB_001801a8;
        uVar10 = FUN_0017f300(param_1,piVar13[6]);
LAB_001801b0:
        uVar17 = *(uint *)(lVar21 + 0x30);
        *(undefined8 *)(puVar9 + 0x26) = uVar10;
        lVar18 = 0;
        pvVar11 = calloc((ulong)uVar17,0x18);
        *(void **)(puVar9 + 0x28) = pvVar11;
        puVar9[0x2a] = uVar17;
        puVar9[0x2b] = uVar17;
        if (uVar17 == 0) goto LAB_00180308;
        break;
      }
      if (piVar13 == (int *)0x0) {
        return;
      }
LAB_0017fec8:
      iVar1 = *piVar13;
      if (iVar1 == 0x18) {
        plVar7 = (long *)*param_1;
        uVar17 = piVar13[0x19];
        if (*(uint *)(plVar7 + 1) <= uVar17 || param_3 == uVar17) {
          return;
        }
        lVar18 = param_1[6];
        uVar25 = (ulong)uVar17;
        if ((*(byte *)(lVar18 + (ulong)uVar17) & 1) != 0) {
          return;
        }
      }
      else {
        if (iVar1 == 0x1a) {
          puVar9 = calloc(1,0x130);
          if (puVar9 == (undefined4 *)0x0) {
            return;
          }
          iVar1 = piVar13[0x12];
          *puVar9 = 0xb;
          if ((iVar1 != 0) && (piVar13[6] != -1)) {
            uVar10 = FUN_0017f300(param_1);
            *(undefined8 *)(puVar9 + 0x26) = uVar10;
          }
          if (param_4 != (int *)0x0) {
            if (*param_4 != 0) {
              return;
            }
            uVar17 = param_4[0x28];
            uVar26 = param_4[0x29];
            pvVar11 = *(void **)(param_4 + 0x26);
            if (uVar26 <= uVar17) {
              pvVar11 = realloc(pvVar11,((ulong)uVar26 & 0x7fffffff) << 4);
              if (pvVar11 == (void *)0x0) {
                return;
              }
              uVar17 = param_4[0x28];
              *(void **)(param_4 + 0x26) = pvVar11;
              param_4[0x29] = uVar26 << 1;
            }
            param_4[0x28] = uVar17 + 1;
            *(undefined4 **)((long)pvVar11 + (ulong)uVar17 * 8) = puVar9;
            return;
          }
          return;
        }
        if (iVar1 != 0x17) {
          return;
        }
        uVar23 = 0xffffffff;
        uVar17 = piVar13[0x19];
        uVar26 = piVar13[0x1a];
        if (param_1[1] != 0) {
          uVar23 = FUN_0017d320(param_1[1],*param_1,uVar25);
          uVar23 = uVar23 & 0xffffffff;
        }
        puVar9 = calloc(1,0x130);
        if (puVar9 == (undefined4 *)0x0) {
          return;
        }
        iVar1 = piVar13[0x12];
        *puVar9 = 1;
        if (iVar1 == 0) {
          uVar10 = FUN_0017eb40(1);
        }
        else {
          uVar10 = FUN_0017f300(param_1,piVar13[6]);
        }
        *(undefined8 *)(puVar9 + 0x26) = uVar10;
        pvVar11 = calloc(1,0x130);
        uVar22 = (uint)uVar23;
        if (pvVar11 != (void *)0x0) {
          pvVar12 = calloc(8,8);
          *(void **)((long)pvVar11 + 0x98) = pvVar12;
          *(undefined4 *)((long)pvVar11 + 0xa4) = 8;
          FUN_0017f560(param_1,uVar23,uVar25,pvVar11);
          uVar2 = *(uint *)(*param_1 + 8);
          sVar27 = (size_t)uVar2;
          pvVar12 = calloc(sVar27,1);
          if (pvVar12 != (void *)0x0) {
            pvVar19 = (void *)param_1[6];
            __memcpy_chk(pvVar12,pvVar19,sVar27,sVar27);
            if (uVar17 < uVar2 && uVar22 != uVar17) {
              uVar2 = param_3;
              if (uVar22 != 0xffffffff) {
                uVar2 = uVar22;
              }
              FUN_0017fdb0(param_1,uVar17,uVar2,pvVar11);
              pvVar19 = (void *)param_1[6];
              sVar27 = (size_t)*(uint *)(*param_1 + 8);
            }
            memcpy(pvVar19,pvVar12,sVar27);
            free(pvVar12);
          }
        }
        plVar7 = (long *)*param_1;
        uVar17 = *(uint *)(plVar7 + 1);
        *(void **)(puVar9 + 0x28) = pvVar11;
        if (uVar26 < uVar17) {
          if (uVar22 != uVar26) {
            pvVar11 = calloc(1,0x130);
            if (pvVar11 != (void *)0x0) {
              pvVar12 = calloc(8,8);
              *(void **)((long)pvVar11 + 0x98) = pvVar12;
              *(undefined4 *)((long)pvVar11 + 0xa4) = 8;
              FUN_0017f560(param_1,uVar23,uVar25,pvVar11);
              uVar25 = (ulong)*(uint *)(*param_1 + 8);
              pvVar12 = calloc(uVar25,1);
              if (pvVar12 != (void *)0x0) {
                __memcpy_chk(pvVar12,param_1[6],uVar25,uVar25);
                uVar17 = param_3;
                if (uVar22 != 0xffffffff) {
                  uVar17 = uVar22;
                }
                FUN_0017fdb0(param_1,uVar26,uVar17,pvVar11);
                memcpy((void *)param_1[6],pvVar12,(ulong)*(uint *)(*param_1 + 8));
                free(pvVar12);
              }
            }
            *(void **)(puVar9 + 0x2a) = pvVar11;
            goto LAB_001806f4;
          }
          if ((param_4 != (int *)0x0) && (*param_4 == 0)) goto LAB_00180044;
        }
        else {
LAB_001806f4:
          if ((param_4 != (int *)0x0) && (*param_4 == 0)) {
LAB_00180044:
            uVar17 = param_4[0x28];
            uVar26 = param_4[0x29];
            pvVar11 = *(void **)(param_4 + 0x26);
            if (uVar26 <= uVar17) {
              pvVar11 = realloc(pvVar11,((ulong)uVar26 & 0x7fffffff) << 4);
              if (pvVar11 == (void *)0x0) goto LAB_00180060;
              uVar17 = param_4[0x28];
              *(void **)(param_4 + 0x26) = pvVar11;
              param_4[0x29] = uVar26 << 1;
            }
            param_4[0x28] = uVar17 + 1;
            *(undefined4 **)((long)pvVar11 + (ulong)uVar17 * 8) = puVar9;
          }
LAB_00180060:
          if (uVar22 == 0xffffffff) {
            return;
          }
          plVar7 = (long *)*param_1;
          uVar17 = *(uint *)(plVar7 + 1);
        }
        if (uVar22 == param_3 || uVar17 <= uVar22) {
          return;
        }
        lVar18 = param_1[6];
        uVar25 = uVar23;
      }
      goto LAB_0017fdfc;
    }
    if (piVar13 == (int *)0x0) {
      FUN_0017f720(param_1,uVar25,param_4);
      if (*(uint *)(lVar21 + 0x30) < 3) {
        return;
      }
      puVar9 = calloc(1,0x130);
      if (puVar9 == (undefined4 *)0x0) {
        return;
      }
      *puVar9 = 5;
LAB_001801a8:
      uVar10 = FUN_0017eb40(0);
      goto LAB_001801b0;
    }
    iVar1 = *(int *)(lVar18 + 0x18);
    if (iVar1 == 3) {
      if ((*(byte *)(lVar18 + 0x44) & 1) == 0) {
        iVar3 = *piVar13;
        goto joined_r0x00180370;
      }
      FUN_0017f720(param_1,uVar25,param_4);
      puVar9 = calloc(1,0x130);
      if (puVar9 == (undefined4 *)0x0) {
        return;
      }
      *puVar9 = 4;
      puVar14 = calloc(1,0x130);
      if (puVar14 != (undefined4 *)0x0) {
        uVar4 = *(undefined4 *)(lVar18 + 0x20);
        *puVar14 = 10;
        puVar15 = calloc(1,0x130);
        if (puVar15 != (undefined4 *)0x0) {
          *puVar15 = 0xd;
          puVar15[0x26] = uVar4;
          __snprintf_chk(puVar15 + 0x27,0x40,2,0x40,&DAT_001faad0);
        }
        uVar4 = *(undefined4 *)(lVar18 + 0x24);
        *(undefined4 **)(puVar14 + 0x26) = puVar15;
        uVar10 = FUN_0017f300(param_1,uVar4);
        *(undefined8 *)(puVar14 + 0x28) = uVar10;
      }
      iVar1 = *piVar13;
      *(undefined4 **)(puVar9 + 0x26) = puVar14;
      if ((iVar1 == 0x17) && (piVar13[0x12] != 0)) {
        uVar10 = FUN_0017f300(param_1,piVar13[6]);
      }
      else {
        uVar10 = FUN_0017eb40(1);
      }
      *(undefined8 *)(puVar9 + 0x28) = uVar10;
      puVar14 = calloc(1,0x130);
      if (puVar14 != (undefined4 *)0x0) {
        uVar4 = *(undefined4 *)(lVar18 + 0x20);
        *puVar14 = 10;
        puVar15 = calloc(1,0x130);
        if (puVar15 != (undefined4 *)0x0) {
          *puVar15 = 0xd;
          puVar15[0x26] = uVar4;
          __snprintf_chk(puVar15 + 0x27,0x40,2,0x40,&DAT_001faad0);
        }
        *(undefined4 **)(puVar14 + 0x26) = puVar15;
        puVar15 = calloc(1,0x130);
        if (puVar15 != (undefined4 *)0x0) {
          uVar4 = *(undefined4 *)(lVar18 + 0x20);
          uVar5 = *(undefined4 *)(lVar18 + 0x38);
          *puVar15 = 0xf;
          puVar15[0x2a] = uVar5;
          puVar16 = calloc(1,0x130);
          if (puVar16 != (undefined4 *)0x0) {
            *puVar16 = 0xd;
            puVar16[0x26] = uVar4;
            __snprintf_chk(puVar16 + 0x27,0x40,2,0x40,&DAT_001faad0);
          }
          uVar10 = *(undefined8 *)(lVar18 + 0x30);
          *(undefined4 **)(puVar15 + 0x26) = puVar16;
          uVar10 = FUN_0017eb40(uVar10);
          *(undefined8 *)(puVar15 + 0x28) = uVar10;
        }
        *(undefined4 **)(puVar14 + 0x28) = puVar15;
      }
      *(undefined4 **)(puVar9 + 0x2a) = puVar14;
      pvVar11 = calloc(1,0x130);
      if (pvVar11 != (void *)0x0) {
        pvVar12 = calloc(8,8);
        iVar1 = *piVar13;
        *(void **)((long)pvVar11 + 0x98) = pvVar12;
        *(undefined4 *)((long)pvVar11 + 0xa4) = 8;
        if (iVar1 == 0x17) {
          uVar26 = piVar13[0x19];
          uVar17 = *(uint *)(*param_1 + 8);
          if ((*(uint *)(lVar18 + 0x14) != 0xffffffff) && (*(uint *)(lVar18 + 0x14) == uVar26)) {
            uVar26 = piVar13[0x1a];
          }
        }
        else {
          uVar17 = *(uint *)(*param_1 + 8);
          uVar26 = uVar17;
          if (*(int *)(lVar21 + 0x30) != 0) {
            uVar26 = **(uint **)(lVar21 + 0x28);
          }
        }
        pvVar12 = calloc((ulong)uVar17,1);
        if (pvVar12 != (void *)0x0) {
          lVar21 = param_1[6];
          __memcpy_chk(pvVar12,lVar21,(ulong)uVar17);
          *(undefined1 *)(lVar21 + uVar25) = 1;
          FUN_0017fdb0(param_1,uVar26,uVar25,pvVar11);
          uVar6 = *(undefined1 *)(param_1[6] + uVar25);
          memcpy((void *)param_1[6],pvVar12,(ulong)*(uint *)(*param_1 + 8));
          *(undefined1 *)(param_1[6] + uVar25) = uVar6;
          free(pvVar12);
        }
      }
      *(void **)(puVar9 + 0x2c) = pvVar11;
      if ((param_4 != (int *)0x0) && (*param_4 == 0)) {
        uVar17 = param_4[0x28];
        uVar26 = param_4[0x29];
        pvVar11 = *(void **)(param_4 + 0x26);
        if (uVar26 <= uVar17) {
          pvVar11 = realloc(pvVar11,((ulong)uVar26 & 0x7fffffff) << 4);
          if (pvVar11 == (void *)0x0) goto LAB_00180628;
          uVar17 = param_4[0x28];
          *(void **)(param_4 + 0x26) = pvVar11;
          param_4[0x29] = uVar26 << 1;
        }
        param_4[0x28] = uVar17 + 1;
        *(undefined4 **)((long)pvVar11 + (ulong)uVar17 * 8) = puVar9;
      }
    }
    else {
      if ((iVar1 != 2) && ((iVar3 = *piVar13, iVar1 != 0 || (iVar3 != 0x18)))) {
joined_r0x00180370:
        if (iVar3 != 0x17) {
          FUN_0017f720(param_1,uVar25,param_4);
          if (2 < *(uint *)(lVar21 + 0x30)) {
            puVar9 = calloc(1,0x130);
            if (puVar9 == (undefined4 *)0x0) {
              return;
            }
            *puVar9 = 5;
            goto LAB_001801a0;
          }
          goto LAB_0017fec8;
        }
        FUN_0017f720(param_1,uVar25,param_4);
        puVar9 = calloc(1,0x130);
        if (puVar9 == (undefined4 *)0x0) {
          return;
        }
        iVar1 = piVar13[0x12];
        *puVar9 = 2;
        if (iVar1 == 0) {
          uVar10 = FUN_0017eb40(1);
        }
        else {
          uVar10 = FUN_0017f300(param_1,piVar13[6]);
        }
        uVar17 = piVar13[0x19];
        uVar26 = *(uint *)(lVar18 + 0x14);
        *(undefined8 *)(puVar9 + 0x26) = uVar10;
        if ((uVar26 == 0xffffffff) || (*(uint *)(*param_1 + 8) <= uVar26)) {
          uVar26 = piVar13[0x1a];
        }
        else if (uVar26 == uVar17) {
          uVar17 = piVar13[0x1a];
        }
        pvVar11 = calloc(1,0x130);
        if (pvVar11 != (void *)0x0) {
          pvVar12 = calloc(8,8);
          *(void **)((long)pvVar11 + 0x98) = pvVar12;
          lVar18 = *param_1;
          *(undefined4 *)((long)pvVar11 + 0xa4) = 8;
          uVar22 = *(uint *)(lVar18 + 8);
          pvVar12 = calloc((ulong)uVar22,1);
          if (pvVar12 != (void *)0x0) {
            lVar18 = param_1[6];
            __memcpy_chk(pvVar12,lVar18,(ulong)uVar22);
            *(undefined1 *)(lVar18 + uVar25) = 1;
            FUN_0017fdb0(param_1,uVar17,uVar25,pvVar11);
            memcpy((void *)param_1[6],pvVar12,(ulong)*(uint *)(*param_1 + 8));
            *(undefined1 *)(param_1[6] + uVar25) = 1;
            free(pvVar12);
          }
        }
        *(void **)(puVar9 + 0x28) = pvVar11;
        if ((param_4 != (int *)0x0) && (*param_4 == 0)) {
          uVar17 = param_4[0x28];
          uVar22 = param_4[0x29];
          pvVar11 = *(void **)(param_4 + 0x26);
          if (uVar22 <= uVar17) {
            pvVar11 = realloc(pvVar11,((ulong)uVar22 & 0x7fffffff) << 4);
            if (pvVar11 == (void *)0x0) goto LAB_001804b0;
            uVar17 = param_4[0x28];
            *(void **)(param_4 + 0x26) = pvVar11;
            param_4[0x29] = uVar22 << 1;
          }
          param_4[0x28] = uVar17 + 1;
          *(undefined4 **)((long)pvVar11 + (ulong)uVar17 * 8) = puVar9;
        }
LAB_001804b0:
        plVar7 = (long *)*param_1;
        if (*(uint *)(plVar7 + 1) <= uVar26 || uVar26 == param_3) {
          return;
        }
        uVar25 = (ulong)uVar26;
        lVar18 = param_1[6];
        goto LAB_0017fdfc;
      }
      puVar9 = calloc(1,0x130);
      if (puVar9 == (undefined4 *)0x0) {
        return;
      }
      *puVar9 = 3;
      pvVar11 = calloc(1,0x130);
      if (pvVar11 == (void *)0x0) {
        local_10 = (long *)*param_1;
        uVar26 = *(uint *)(lVar18 + 4);
        uVar17 = *(uint *)(local_10 + 1);
LAB_00180d64:
        *(void **)(puVar9 + 0x28) = pvVar11;
        if (uVar26 < uVar17) goto LAB_00180a1c;
      }
      else {
        pvVar12 = calloc(8,8);
        *(void **)((long)pvVar11 + 0x98) = pvVar12;
        *(undefined4 *)((long)pvVar11 + 0xa4) = 8;
        FUN_0017f720(param_1,uVar25,pvVar11);
        if (*piVar13 == 0x18) {
          uVar26 = piVar13[0x19];
LAB_00180550:
          local_10 = (long *)*param_1;
          uVar17 = *(uint *)(local_10 + 1);
          pvVar12 = calloc((ulong)uVar17,1);
          if (pvVar12 == (void *)0x0) {
LAB_00180d60:
            uVar26 = *(uint *)(lVar18 + 4);
            goto LAB_00180d64;
          }
          lVar21 = param_1[6];
          __memcpy_chk(pvVar12,lVar21,(ulong)uVar17);
          uVar22 = *(uint *)(lVar18 + 4);
          *(undefined1 *)(lVar21 + uVar25) = 1;
          if (uVar26 < uVar17 && uVar22 != uVar26) {
            FUN_0017fdb0(param_1,uVar26,uVar22,pvVar11);
            uVar22 = *(uint *)(lVar18 + 4);
            uVar17 = *(uint *)(*param_1 + 8);
          }
        }
        else {
          if (*(int *)(lVar21 + 0x30) != 0) {
            uVar26 = **(uint **)(lVar21 + 0x28);
            goto LAB_00180550;
          }
          local_10 = (long *)*param_1;
          uVar17 = *(uint *)(local_10 + 1);
          pvVar12 = calloc((ulong)uVar17,1);
          if (pvVar12 == (void *)0x0) goto LAB_00180d60;
          lVar21 = param_1[6];
          __memcpy_chk(pvVar12,lVar21,(ulong)uVar17);
          uVar22 = *(uint *)(lVar18 + 4);
          *(undefined1 *)(lVar21 + uVar25) = 1;
        }
        if (uVar22 < uVar17) {
          FUN_0017f720(param_1,uVar22,pvVar11);
          pvVar19 = (void *)param_1[6];
          uVar17 = *(uint *)(*param_1 + 8);
          *(undefined1 *)((long)pvVar19 + (ulong)*(uint *)(lVar18 + 4)) = 1;
        }
        else {
          pvVar19 = (void *)param_1[6];
        }
        memcpy(pvVar19,pvVar12,(ulong)uVar17);
        local_10 = (long *)*param_1;
        lVar21 = param_1[6];
        uVar26 = *(uint *)(lVar18 + 4);
        uVar17 = *(uint *)(local_10 + 1);
        *(undefined1 *)(lVar21 + uVar25) = 1;
        if (uVar26 < uVar17) {
          *(undefined1 *)(lVar21 + (ulong)uVar26) = 1;
          free(pvVar12);
          *(void **)(puVar9 + 0x28) = pvVar11;
LAB_00180a1c:
          lVar21 = *local_10 + (ulong)uVar26 * 0x50;
          uVar17 = *(uint *)(lVar21 + 0x10);
          uVar26 = uVar17 - 1;
          if (-1 < (int)uVar26) {
            lVar21 = *(long *)(lVar21 + 8);
            piVar13 = (int *)(lVar21 + (long)(int)uVar26 * 0x90);
            do {
              iVar1 = *piVar13;
              if (iVar1 - 0x17U < 2 || iVar1 == 0x1a) {
                if ((iVar1 == 0x17) && (piVar13[0x12] != 0)) {
                  uVar10 = FUN_0017f300(param_1,piVar13[6]);
                  goto LAB_001805f4;
                }
                break;
              }
              piVar13 = piVar13 + -0x24;
            } while (piVar13 != (int *)(lVar21 + -0x120 + ((ulong)uVar17 - (ulong)uVar26) * 0x90));
          }
        }
        else {
          free(pvVar12);
          *(void **)(puVar9 + 0x28) = pvVar11;
        }
      }
      uVar10 = FUN_0017eb40(1);
LAB_001805f4:
      *(undefined8 *)(puVar9 + 0x26) = uVar10;
      if ((param_4 != (int *)0x0) && (*param_4 == 0)) {
        uVar17 = param_4[0x28];
        uVar26 = param_4[0x29];
        pvVar11 = *(void **)(param_4 + 0x26);
        if (uVar26 <= uVar17) {
          pvVar11 = realloc(pvVar11,((ulong)uVar26 & 0x7fffffff) << 4);
          if (pvVar11 == (void *)0x0) goto LAB_00180628;
          uVar17 = param_4[0x28];
          *(void **)(param_4 + 0x26) = pvVar11;
          param_4[0x29] = uVar26 << 1;
        }
        param_4[0x28] = uVar17 + 1;
        *(undefined4 **)((long)pvVar11 + (ulong)uVar17 * 8) = puVar9;
      }
    }
LAB_00180628:
    plVar7 = (long *)*param_1;
    uVar17 = *(uint *)(lVar18 + 0x14);
    uVar25 = (ulong)uVar17;
    if (*(uint *)(plVar7 + 1) <= uVar17 || uVar17 == param_3) {
      return;
    }
    lVar18 = param_1[6];
  } while( true );
LAB_001801d4:
  lVar24 = lVar18 * 0x18;
  *(long *)((long)pvVar11 + lVar18 * 0x18) = lVar18;
  *(bool *)((long)pvVar11 + lVar24 + 8) = uVar17 - 1 == (int)lVar18;
  piVar13 = calloc(1,0x130);
  if (piVar13 == (int *)0x0) {
    puVar14 = calloc(1,0x130);
    if (puVar14 != (undefined4 *)0x0) {
      *puVar14 = 8;
    }
  }
  else {
    pvVar11 = calloc(8,8);
    *(void **)(piVar13 + 0x26) = pvVar11;
    lVar20 = *param_1;
    piVar13[0x29] = 8;
    uVar17 = *(uint *)(lVar20 + 8);
    sVar27 = (size_t)uVar17;
    pvVar11 = calloc(sVar27,1);
    if (pvVar11 != (void *)0x0) {
      pvVar12 = (void *)param_1[6];
      __memcpy_chk();
      uVar26 = *(uint *)(*(long *)(lVar21 + 0x28) + lVar18 * 4);
      *(undefined1 *)((long)pvVar12 + uVar25) = 1;
      if ((uVar26 < uVar17) && ((*(byte *)((long)pvVar12 + (ulong)uVar26) & 1) == 0)) {
        FUN_0017fdb0(param_1,uVar26,param_3,piVar13);
        pvVar12 = (void *)param_1[6];
        sVar27 = (size_t)*(uint *)(*param_1 + 8);
      }
      memcpy(pvVar12,pvVar11,sVar27);
      *(undefined1 *)(param_1[6] + uVar25) = 1;
      free(pvVar11);
    }
    puVar14 = calloc(1,0x130);
    if ((puVar14 != (undefined4 *)0x0) && (*puVar14 = 8, *piVar13 == 0)) {
      uVar17 = piVar13[0x28];
      uVar26 = piVar13[0x29];
      pvVar11 = *(void **)(piVar13 + 0x26);
      if (uVar26 <= uVar17) {
        pvVar11 = realloc(pvVar11,((ulong)uVar26 & 0x7fffffff) << 4);
        if (pvVar11 == (void *)0x0) goto LAB_001802ec;
        uVar17 = piVar13[0x28];
        *(void **)(piVar13 + 0x26) = pvVar11;
        piVar13[0x29] = uVar26 << 1;
      }
      piVar13[0x28] = uVar17 + 1;
      *(undefined4 **)((long)pvVar11 + (ulong)uVar17 * 8) = puVar14;
    }
  }
LAB_001802ec:
  pvVar11 = *(void **)(puVar9 + 0x28);
  lVar18 = lVar18 + 1;
  uVar17 = *(uint *)(lVar21 + 0x30);
  *(int **)((long)pvVar11 + lVar24 + 0x10) = piVar13;
  if (uVar17 <= (uint)lVar18) {
LAB_00180308:
    if ((param_4 != (int *)0x0) && (*param_4 == 0)) {
      uVar17 = param_4[0x28];
      uVar26 = param_4[0x29];
      pvVar11 = *(void **)(param_4 + 0x26);
      if (uVar26 <= uVar17) {
        pvVar11 = realloc(pvVar11,((ulong)uVar26 & 0x7fffffff) << 4);
        if (pvVar11 == (void *)0x0) {
          return;
        }
        uVar17 = param_4[0x28];
        *(void **)(param_4 + 0x26) = pvVar11;
        param_4[0x29] = uVar26 << 1;
      }
      param_4[0x28] = uVar17 + 1;
      *(undefined4 **)((long)pvVar11 + (ulong)uVar17 * 8) = puVar9;
    }
    return;
  }
  goto LAB_001801d4;
}

