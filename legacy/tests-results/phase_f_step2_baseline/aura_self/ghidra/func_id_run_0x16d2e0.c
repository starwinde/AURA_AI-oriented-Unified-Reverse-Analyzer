
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Restarted to delay deadcode elimination for space: ram */

void func_id_run(long *param_1,long param_2,long param_3,undefined8 param_4,undefined8 *param_5,
                undefined8 *param_6)

{
  int iVar1;
  undefined8 uVar2;
  ulong uVar3;
  byte *pbVar4;
  long *__ptr;
  void *pvVar5;
  ulong uVar6;
  long lVar7;
  long lVar8;
  char *pcVar9;
  byte *pbVar10;
  ulong *puVar11;
  ulong uVar12;
  long lVar13;
  ulong uVar14;
  undefined8 *puVar15;
  long *plVar16;
  uint uVar17;
  undefined8 *puVar18;
  long lVar19;
  uint uVar20;
  int iVar21;
  int iVar22;
  int iVar23;
  ulong local_108;
  long local_f0;
  long local_d0;
  undefined8 *local_c0;
  undefined4 local_b8;
  undefined1 uStack_b4;
  undefined2 uStack_b3;
  undefined1 uStack_b1;
  undefined1 uStack_b0;
  undefined1 uStack_af;
  undefined1 uStack_ae;
  undefined2 uStack_ad;
  byte abStack_a8 [64];
  long local_68;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if ((param_1 == (long *)0x0 || param_2 == 0) || (param_3 == 0 || param_5 == (undefined8 *)0x0)) {
    if (param_6 != (undefined8 *)0x0) {
      *param_6 = 0;
    }
  }
  else {
    if (g_builtin_db_ready == 0) {
      local_b8 = (undefined4)(undefined5)DAT_001fa418;
      uStack_b4 = (undefined1)((uint5)(undefined5)DAT_001fa418 >> 0x20);
      uStack_b3 = (undefined2)DAT_001fa418._5_3_;
      uStack_b1 = (undefined1)((uint3)DAT_001fa418._5_3_ >> 0x10);
      uStack_b0 = (undefined1)_UNK_001fa420;
      uStack_af = (undefined1)((uint5)_UNK_001fa420 >> 8);
      uStack_ae = (undefined1)((uint5)_UNK_001fa420 >> 0x10);
      uStack_ad = (undefined2)((uint5)_UNK_001fa420 >> 0x18);
      g_builtin_db_ready = 1;
      lVar8 = func_id_normalize_bytes_part_0(&local_b8,0xd,abStack_a8,2);
      uVar3 = g_builtin_db_count;
      if (lVar8 == 0) {
        uVar6 = 0xcbf29ce484222325;
      }
      else {
        uVar6 = 0xcbf29ce484222325;
        pbVar4 = abStack_a8;
        do {
          pbVar10 = pbVar4 + 1;
          uVar6 = (*pbVar4 ^ uVar6) * 0x100000001b3;
          pbVar4 = pbVar10;
        } while (abStack_a8 + lVar8 != pbVar10);
      }
      uVar14 = g_builtin_db_count;
      if (g_builtin_db_count < 0x14) {
        uVar14 = g_builtin_db_count + 1;
        lVar8 = g_builtin_db_count * 3;
        g_builtin_db_count = uVar14;
        (&g_builtin_db)[lVar8] = uVar6;
        (&DAT_00600610)[uVar3 * 3] = "memcpy";
        (&DAT_00600618)[uVar3 * 6] = 0x3f59999a;
      }
      local_b8 = (undefined4)(undefined7)DAT_001fa428;
      uStack_b4 = (undefined1)((uint7)(undefined7)DAT_001fa428 >> 0x20);
      uStack_b3 = (undefined2)((uint7)(undefined7)DAT_001fa428 >> 0x28);
      uStack_b0 = (undefined1)((uint)ram0x001fa42f >> 8);
      uStack_af = (undefined1)((uint)ram0x001fa42f >> 0x10);
      uStack_ae = (undefined1)((uint)ram0x001fa42f >> 0x18);
      uStack_b1 = DAT_001fa428._7_1_;
      lVar8 = func_id_normalize_bytes_part_0(&local_b8,0xb,abStack_a8,2);
      if (lVar8 == 0) {
        uVar3 = 0xcbf29ce484222325;
      }
      else {
        uVar3 = 0xcbf29ce484222325;
        pbVar4 = abStack_a8;
        do {
          pbVar10 = pbVar4 + 1;
          uVar3 = (*pbVar4 ^ uVar3) * 0x100000001b3;
          pbVar4 = pbVar10;
        } while (abStack_a8 + lVar8 != pbVar10);
      }
      uVar6 = uVar14;
      if (uVar14 < 0x14) {
        uVar6 = uVar14 + 1;
        (&g_builtin_db)[uVar14 * 3] = uVar3;
        (&DAT_00600610)[uVar14 * 3] = "memset";
        g_builtin_db_count = uVar6;
        (&DAT_00600618)[uVar14 * 6] = 0x3f59999a;
      }
      local_b8 = (undefined4)(undefined5)DAT_001fa438;
      uStack_b4 = (undefined1)((uint5)(undefined5)DAT_001fa438 >> 0x20);
      uStack_b3 = (undefined2)DAT_001fa438._5_3_;
      uStack_b1 = (undefined1)((uint3)DAT_001fa438._5_3_ >> 0x10);
      uStack_b0 = (undefined1)_UNK_001fa440;
      uStack_af = (undefined1)((uint5)_UNK_001fa440 >> 8);
      uStack_ae = (undefined1)((uint5)_UNK_001fa440 >> 0x10);
      uStack_ad = (undefined2)((uint5)_UNK_001fa440 >> 0x18);
      lVar8 = func_id_normalize_bytes_part_0(&local_b8,0xd,abStack_a8,2);
      if (lVar8 == 0) {
        uVar3 = 0xcbf29ce484222325;
      }
      else {
        uVar3 = 0xcbf29ce484222325;
        pbVar4 = abStack_a8;
        do {
          pbVar10 = pbVar4 + 1;
          uVar3 = (*pbVar4 ^ uVar3) * 0x100000001b3;
          pbVar4 = pbVar10;
        } while (abStack_a8 + lVar8 != pbVar10);
      }
      uVar14 = uVar6;
      if (uVar6 < 0x14) {
        uVar14 = uVar6 + 1;
        (&g_builtin_db)[uVar6 * 3] = uVar3;
        (&DAT_00600610)[uVar6 * 3] = "strlen";
        g_builtin_db_count = uVar14;
        (&DAT_00600618)[uVar6 * 6] = 0x3f4ccccd;
      }
      local_b8 = DAT_001fa448;
      uStack_b4 = (undefined1)_UNK_001fa44c;
      uStack_b3 = (undefined2)((uint3)_UNK_001fa44c >> 8);
      lVar8 = func_id_normalize_bytes_part_0(&local_b8,7,abStack_a8,2);
      if (lVar8 == 0) {
        uVar3 = 0xcbf29ce484222325;
      }
      else {
        uVar3 = 0xcbf29ce484222325;
        pbVar4 = abStack_a8;
        do {
          pbVar10 = pbVar4 + 1;
          uVar3 = (*pbVar4 ^ uVar3) * 0x100000001b3;
          pbVar4 = pbVar10;
        } while (abStack_a8 + lVar8 != pbVar10);
      }
      uVar6 = uVar14;
      if (uVar14 < 0x14) {
        uVar6 = uVar14 + 1;
        (&g_builtin_db)[uVar14 * 3] = uVar3;
        (&DAT_00600610)[uVar14 * 3] = "strcmp";
        g_builtin_db_count = uVar6;
        (&DAT_00600618)[uVar14 * 6] = 0x3f333333;
      }
      local_b8 = (undefined4)DAT_001fa450;
      uStack_b4 = (undefined1)((ulong)DAT_001fa450 >> 0x20);
      uStack_b3 = (undefined2)((ulong)DAT_001fa450 >> 0x28);
      uStack_b1 = (undefined1)((ulong)DAT_001fa450 >> 0x38);
      uStack_b0 = (undefined1)DAT_001fa458;
      uStack_af = (undefined1)((ushort)DAT_001fa458 >> 8);
      lVar8 = func_id_normalize_bytes_part_0(&local_b8,10,abStack_a8,2);
      if (lVar8 == 0) {
        uVar3 = 0xcbf29ce484222325;
      }
      else {
        uVar3 = 0xcbf29ce484222325;
        pbVar4 = abStack_a8;
        do {
          pbVar10 = pbVar4 + 1;
          uVar3 = (*pbVar4 ^ uVar3) * 0x100000001b3;
          pbVar4 = pbVar10;
        } while (abStack_a8 + lVar8 != pbVar10);
      }
      uStack_b4 = (undefined1)((ulong)DAT_001fa460 >> 0x20);
      uStack_b1 = (undefined1)((ulong)DAT_001fa460 >> 0x38);
      uStack_b3 = (undefined2)((ulong)DAT_001fa460 >> 0x28);
      local_b8 = (undefined4)DAT_001fa460;
      if (uVar6 < 0x14) {
        uStack_b0 = DAT_001fa468;
        uVar14 = uVar6 + 1;
        (&g_builtin_db)[uVar6 * 3] = uVar3;
        (&DAT_00600610)[uVar6 * 3] = "_start";
        g_builtin_db_count = uVar14;
        (&DAT_00600618)[uVar6 * 6] = 0x3f666666;
        lVar8 = func_id_normalize_bytes_part_0(&local_b8,9,abStack_a8,2);
        uVar6 = uVar14;
        if (lVar8 == 0) {
          uVar3 = 0xcbf29ce484222325;
        }
        else {
LAB_0016d768:
          uVar3 = 0xcbf29ce484222325;
          pbVar4 = abStack_a8;
          do {
            pbVar10 = pbVar4 + 1;
            uVar3 = (*pbVar4 ^ uVar3) * 0x100000001b3;
            pbVar4 = pbVar10;
            uVar14 = uVar6;
          } while (abStack_a8 + lVar8 != pbVar10);
        }
        uVar6 = uVar14;
        if (uVar14 < 0x14) {
          uVar6 = uVar14 + 1;
          (&g_builtin_db)[uVar14 * 3] = uVar3;
          (&DAT_00600610)[uVar14 * 3] = "_start";
          g_builtin_db_count = uVar6;
          (&DAT_00600618)[uVar14 * 6] = 0x3f59999a;
        }
      }
      else {
        uStack_b0 = DAT_001fa468;
        lVar8 = func_id_normalize_bytes_part_0(&local_b8,9,abStack_a8,2);
        if (lVar8 != 0) goto LAB_0016d768;
      }
      local_b8 = DAT_001fa470;
      uStack_b4 = (undefined1)_UNK_001fa474;
      uStack_b3 = (undefined2)((uint3)_UNK_001fa474 >> 8);
      lVar8 = func_id_normalize_bytes_part_0(&local_b8,7,abStack_a8,2);
      if (lVar8 == 0) {
        uVar3 = 0xcbf29ce484222325;
      }
      else {
        uVar3 = 0xcbf29ce484222325;
        pbVar4 = abStack_a8;
        do {
          pbVar10 = pbVar4 + 1;
          uVar3 = (*pbVar4 ^ uVar3) * 0x100000001b3;
          pbVar4 = pbVar10;
        } while (abStack_a8 + lVar8 != pbVar10);
      }
      uStack_b4 = (undefined1)_UNK_001fa47c;
      uStack_b3 = (undefined2)((uint3)_UNK_001fa47c >> 8);
      if (uVar6 < 0x14) {
        local_b8 = DAT_001fa478;
        uVar14 = uVar6 + 1;
        (&g_builtin_db)[uVar6 * 3] = uVar3;
        g_builtin_db_count = uVar14;
        (&DAT_00600610)[uVar6 * 3] = "strcpy";
        (&DAT_00600618)[uVar6 * 6] = 0x3f19999a;
        lVar8 = func_id_normalize_bytes_part_0(&local_b8,7,abStack_a8,2);
        uVar6 = uVar14;
        if (lVar8 == 0) {
          uVar3 = 0xcbf29ce484222325;
        }
        else {
LAB_0016d8b8:
          uVar3 = 0xcbf29ce484222325;
          pbVar4 = abStack_a8;
          do {
            pbVar10 = pbVar4 + 1;
            uVar3 = (*pbVar4 ^ uVar3) * 0x100000001b3;
            pbVar4 = pbVar10;
            uVar14 = uVar6;
          } while (abStack_a8 + lVar8 != pbVar10);
        }
        uVar6 = uVar14;
        if (uVar14 < 0x14) {
          uVar6 = uVar14 + 1;
          (&g_builtin_db)[uVar14 * 3] = uVar3;
          (&DAT_00600610)[uVar14 * 3] = "memmove";
          g_builtin_db_count = uVar6;
          (&DAT_00600618)[uVar14 * 6] = 0x3f266666;
        }
      }
      else {
        local_b8 = DAT_001fa478;
        lVar8 = func_id_normalize_bytes_part_0(&local_b8,7,abStack_a8,2);
        if (lVar8 != 0) goto LAB_0016d8b8;
      }
      local_b8 = DAT_001fa480;
      uStack_b4 = (undefined1)_UNK_001fa484;
      uStack_b3 = (undefined2)((uint3)_UNK_001fa484 >> 8);
      lVar8 = func_id_normalize_bytes_part_0(&local_b8,7,abStack_a8,2);
      if (lVar8 == 0) {
        uVar3 = 0xcbf29ce484222325;
      }
      else {
        uVar3 = 0xcbf29ce484222325;
        pbVar4 = abStack_a8;
        do {
          pbVar10 = pbVar4 + 1;
          uVar3 = (*pbVar4 ^ uVar3) * 0x100000001b3;
          pbVar4 = pbVar10;
        } while (abStack_a8 + lVar8 != pbVar10);
      }
      if (uVar6 < 0x14) {
        uVar14 = uVar6 + 1;
        (&g_builtin_db)[uVar6 * 3] = uVar3;
        (&DAT_00600610)[uVar6 * 3] = "memcmp";
        g_builtin_db_count = uVar14;
        (&DAT_00600618)[uVar6 * 6] = 0x3f266666;
        local_b8 = 0xfa1e0ff3;
        uStack_b4 = 0x53;
        uStack_b3 = 0x8948;
        uStack_b1 = 0xd3;
        lVar8 = func_id_normalize_bytes_part_0(&local_b8,8,abStack_a8,2);
        uVar6 = uVar14;
        if (lVar8 == 0) {
          uVar3 = 0xcbf29ce484222325;
        }
        else {
LAB_0016da04:
          uVar3 = 0xcbf29ce484222325;
          pbVar4 = abStack_a8;
          do {
            pbVar10 = pbVar4 + 1;
            uVar3 = (*pbVar4 ^ uVar3) * 0x100000001b3;
            pbVar4 = pbVar10;
            uVar14 = uVar6;
          } while (abStack_a8 + lVar8 != pbVar10);
        }
        uVar6 = uVar14;
        if (uVar14 < 0x14) {
          uVar6 = uVar14 + 1;
          (&g_builtin_db)[uVar14 * 3] = uVar3;
          (&DAT_00600610)[uVar14 * 3] = "strncpy";
          g_builtin_db_count = uVar6;
          (&DAT_00600618)[uVar14 * 6] = 0x3f19999a;
        }
      }
      else {
        local_b8 = 0xfa1e0ff3;
        uStack_b4 = 0x53;
        uStack_b3 = 0x8948;
        uStack_b1 = 0xd3;
        lVar8 = func_id_normalize_bytes_part_0(&local_b8,8,abStack_a8,2);
        if (lVar8 != 0) goto LAB_0016da04;
      }
      local_b8 = (undefined4)DAT_001fa488;
      uStack_b4 = (undefined1)((ulong)DAT_001fa488 >> 0x20);
      uStack_b3 = (undefined2)((ulong)DAT_001fa488 >> 0x28);
      uStack_b1 = (undefined1)((ulong)DAT_001fa488 >> 0x38);
      uStack_b0 = (undefined1)DAT_001fa490;
      uStack_af = (undefined1)((ushort)DAT_001fa490 >> 8);
      lVar8 = func_id_normalize_bytes_part_0(&local_b8,10,abStack_a8,2);
      if (lVar8 == 0) {
        uVar3 = 0xcbf29ce484222325;
      }
      else {
        uVar3 = 0xcbf29ce484222325;
        pbVar4 = abStack_a8;
        do {
          pbVar10 = pbVar4 + 1;
          uVar3 = (*pbVar4 ^ uVar3) * 0x100000001b3;
          pbVar4 = pbVar10;
        } while (abStack_a8 + lVar8 != pbVar10);
      }
      uStack_b4 = (undefined1)((ulong)DAT_001fa498 >> 0x20);
      uStack_b1 = (undefined1)((ulong)DAT_001fa498 >> 0x38);
      uStack_b3 = (undefined2)((ulong)DAT_001fa498 >> 0x28);
      local_b8 = (undefined4)DAT_001fa498;
      uStack_b0 = (undefined1)DAT_001fa4a0;
      uStack_af = (undefined1)((ushort)DAT_001fa4a0 >> 8);
      if (uVar6 < 0x14) {
        uVar14 = uVar6 + 1;
        (&g_builtin_db)[uVar6 * 3] = uVar3;
        (&DAT_00600610)[uVar6 * 3] = &DAT_001fa348;
        g_builtin_db_count = uVar14;
        (&DAT_00600618)[uVar6 * 6] = 0x3f0ccccd;
        lVar8 = func_id_normalize_bytes_part_0(&local_b8,10,abStack_a8,2);
        uVar6 = uVar14;
        if (lVar8 == 0) {
          uVar3 = 0xcbf29ce484222325;
        }
        else {
LAB_0016db58:
          uVar3 = 0xcbf29ce484222325;
          pbVar4 = abStack_a8;
          do {
            pbVar10 = pbVar4 + 1;
            uVar3 = (*pbVar4 ^ uVar3) * 0x100000001b3;
            uVar14 = uVar6;
            pbVar4 = pbVar10;
          } while (abStack_a8 + lVar8 != pbVar10);
        }
        uVar6 = uVar14;
        if (uVar14 < 0x14) {
          uVar6 = uVar14 + 1;
          (&g_builtin_db)[uVar14 * 3] = uVar3;
          (&DAT_00600610)[uVar14 * 3] = &DAT_001fa350;
          g_builtin_db_count = uVar6;
          (&DAT_00600618)[uVar14 * 6] = 0x3f19999a;
        }
      }
      else {
        lVar8 = func_id_normalize_bytes_part_0(&local_b8,10,abStack_a8,2);
        if (lVar8 != 0) goto LAB_0016db58;
      }
      aura_log(0,"/home/str_dgx_spark/Desktop/AURA/src/symbolic/func_id.c",0x12f,
               "func_id: built-in DB initialized with %zu entries",uVar6);
    }
    local_c0 = (undefined8 *)func_detect(param_2,param_3,param_1,0);
    if (((local_c0 != (undefined8 *)0x0) && (plVar16 = (long *)*local_c0, plVar16 != (long *)0x0))
       && (uVar20 = *(uint *)(plVar16 + 1), uVar20 != 0)) {
      lVar8 = *(long *)(*param_1 + 8);
      uVar3 = *(ulong *)(*param_1 + 0x10);
      if (*(uint *)(param_1 + 4) != 0) {
        puVar15 = (undefined8 *)param_1[3];
        puVar18 = puVar15 + (ulong)*(uint *)(param_1 + 4) * 7;
        do {
          if (((char *)*puVar15 != (char *)0x0) &&
             (iVar1 = strcmp((char *)*puVar15,".text"), iVar1 == 0)) {
            local_108 = puVar15[1];
            local_d0 = puVar15[2];
            local_f0 = puVar15[4];
            goto LAB_0016dc4c;
          }
          puVar15 = puVar15 + 7;
        } while (puVar18 != puVar15);
      }
      local_108 = 0;
      local_f0 = 0;
      local_d0 = 0;
LAB_0016dc4c:
      __ptr = calloc(1,0x10);
      if (__ptr != (long *)0x0) {
        uVar17 = uVar20;
        if (uVar20 < 0x40) {
          uVar17 = 0x40;
        }
        pvVar5 = calloc((ulong)uVar17,0x98);
        *__ptr = (long)pvVar5;
        if (pvVar5 != (void *)0x0) {
          lVar19 = 0;
          do {
            lVar13 = *plVar16;
            if (((lVar8 != 0 && local_f0 != 0) &&
                (uVar6 = *(ulong *)(lVar13 + lVar19 * 0x98), local_108 <= uVar6)) &&
               ((uVar6 < local_108 + local_f0 &&
                (uVar6 = (local_d0 - local_108) + uVar6, uVar6 < uVar3)))) {
              uVar12 = uVar3 - uVar6;
              uVar14 = uVar12;
              if (0x40 < uVar12) {
                uVar14 = 0x40;
              }
              if (3 < uVar12) {
                lVar7 = func_id_normalize_bytes_part_0
                                  (lVar8 + uVar6,uVar14,abStack_a8,
                                   *(undefined4 *)((long)param_1 + 0xc));
                if (lVar7 == 0) {
                  uVar6 = 0xcbf29ce484222325;
                }
                else {
                  uVar6 = 0xcbf29ce484222325;
                  pbVar4 = abStack_a8;
                  do {
                    pbVar10 = pbVar4 + 1;
                    uVar6 = (*pbVar4 ^ uVar6) * 0x100000001b3;
                    pbVar4 = pbVar10;
                  } while (abStack_a8 + lVar7 != pbVar10);
                }
                uVar20 = *(uint *)(__ptr + 1);
                pvVar5 = (void *)*__ptr;
                if (uVar20 < uVar17) {
LAB_0016ddb0:
                  uVar2 = *(undefined8 *)(lVar13 + lVar19 * 0x98);
                  lVar13 = (ulong)uVar20 * 0x98;
                  *(uint *)(__ptr + 1) = uVar20 + 1;
                  *(undefined8 *)((long)pvVar5 + lVar13) = uVar2;
                  uVar14 = g_builtin_db_count;
                  *(ulong *)((long)pvVar5 + lVar13 + 8) = uVar6;
                  *(undefined1 *)((long)pvVar5 + lVar13 + 0x10) = 0;
                  *(undefined4 *)((long)pvVar5 + lVar13 + 0x90) = 0;
                  if (uVar14 != 0) {
                    puVar11 = &g_builtin_db;
                    uVar12 = 0;
                    do {
                      if (uVar6 == *puVar11) {
                        snprintf((char *)((long)pvVar5 + lVar13 + 0x10),0x80,"%s",
                                 (&DAT_00600610)[uVar12 * 3]);
                        *(undefined4 *)((long)pvVar5 + lVar13 + 0x90) = (&DAT_00600618)[uVar12 * 6];
                        break;
                      }
                      uVar12 = uVar12 + 1;
                      puVar11 = puVar11 + 3;
                    } while (uVar14 != uVar12);
                  }
                }
                else {
                  uVar17 = uVar17 << 1;
                  pvVar5 = realloc(pvVar5,(ulong)uVar17 * 0x98);
                  if (pvVar5 != (void *)0x0) {
                    uVar20 = *(uint *)(__ptr + 1);
                    *__ptr = (long)pvVar5;
                    goto LAB_0016ddb0;
                  }
                }
                uVar20 = *(uint *)(plVar16 + 1);
              }
            }
            lVar19 = lVar19 + 1;
          } while ((uint)lVar19 < uVar20);
          func_detect_destroy(&local_c0);
          uVar20 = *(uint *)(__ptr + 1);
          if (uVar20 == 0) {
            iVar1 = 0;
          }
          else {
            lVar8 = *__ptr;
            if (uVar20 - 1 < 0xf) {
              uVar17 = 0;
              iVar1 = 0;
            }
            else {
              iVar1 = 0;
              iVar21 = 0;
              iVar22 = 0;
              iVar23 = 0;
              lVar19 = lVar8;
              do {
                lVar13 = lVar19 + 0x980;
                iVar1 = iVar1 + ((((uint)(-(*(char *)(lVar19 + 0x10) != '\0') & 1) -
                                  (int)(short)-(*(char *)(lVar19 + 0x270) != '\0')) -
                                 (int)(short)-(*(char *)(lVar19 + 0x4d0) != '\0')) -
                                (int)(short)-(*(char *)(lVar19 + 0x730) != '\0'));
                iVar21 = iVar21 + ((((uint)(-(*(char *)(lVar19 + 0xa8) != '\0') & 1) -
                                    (int)(short)-(*(char *)(lVar19 + 0x308) != '\0')) -
                                   (int)(short)-(*(char *)(lVar19 + 0x568) != '\0')) -
                                  (int)(short)-(*(char *)(lVar19 + 0x7c8) != '\0'));
                iVar22 = iVar22 + ((((uint)(-(*(char *)(lVar19 + 0x140) != '\0') & 1) -
                                    (int)(short)-(*(char *)(lVar19 + 0x3a0) != '\0')) -
                                   (int)(short)-(*(char *)(lVar19 + 0x600) != '\0')) -
                                  (int)(short)-(*(char *)(lVar19 + 0x860) != '\0'));
                iVar23 = iVar23 + ((((uint)(-(*(char *)(lVar19 + 0x1d8) != '\0') & 1) -
                                    (int)(short)-(*(char *)(lVar19 + 0x438) != '\0')) -
                                   (int)(short)-(*(char *)(lVar19 + 0x698) != '\0')) -
                                  (int)(short)-(*(char *)(lVar19 + 0x8f8) != '\0'));
                lVar19 = lVar13;
              } while (lVar8 + (ulong)(uVar20 >> 4) * 0x980 != lVar13);
              iVar1 = iVar1 + iVar21 + iVar22 + iVar23;
              uVar17 = uVar20 & 0xfffffff0;
              if ((uVar20 & 0xf) == 0) goto LAB_0016e0d8;
            }
            if (*(char *)(lVar8 + (ulong)uVar17 * 0x98 + 0x10) != '\0') {
              iVar1 = iVar1 + 1;
            }
            if (uVar17 + 1 < uVar20) {
              if (*(char *)(lVar8 + (ulong)(uVar17 + 1) * 0x98 + 0x10) != '\0') {
                iVar1 = iVar1 + 1;
              }
              if (uVar17 + 2 < uVar20) {
                if (*(char *)(lVar8 + (ulong)(uVar17 + 2) * 0x98 + 0x10) != '\0') {
                  iVar1 = iVar1 + 1;
                }
                if (uVar17 + 3 < uVar20) {
                  if (*(char *)(lVar8 + (ulong)(uVar17 + 3) * 0x98 + 0x10) != '\0') {
                    iVar1 = iVar1 + 1;
                  }
                  if (uVar17 + 4 < uVar20) {
                    if (*(char *)(lVar8 + (ulong)(uVar17 + 4) * 0x98 + 0x10) != '\0') {
                      iVar1 = iVar1 + 1;
                    }
                    if (uVar17 + 5 < uVar20) {
                      if (*(char *)(lVar8 + (ulong)(uVar17 + 5) * 0x98 + 0x10) != '\0') {
                        iVar1 = iVar1 + 1;
                      }
                      if (uVar17 + 6 < uVar20) {
                        if (*(char *)(lVar8 + (ulong)(uVar17 + 6) * 0x98 + 0x10) != '\0') {
                          iVar1 = iVar1 + 1;
                        }
                        if (uVar17 + 7 < uVar20) {
                          if (*(char *)(lVar8 + (ulong)(uVar17 + 7) * 0x98 + 0x10) != '\0') {
                            iVar1 = iVar1 + 1;
                          }
                          if (uVar17 + 8 < uVar20) {
                            if (*(char *)(lVar8 + (ulong)(uVar17 + 8) * 0x98 + 0x10) != '\0') {
                              iVar1 = iVar1 + 1;
                            }
                            if (uVar17 + 9 < uVar20) {
                              if (*(char *)(lVar8 + (ulong)(uVar17 + 9) * 0x98 + 0x10) != '\0') {
                                iVar1 = iVar1 + 1;
                              }
                              if (uVar17 + 10 < uVar20) {
                                if (*(char *)(lVar8 + (ulong)(uVar17 + 10) * 0x98 + 0x10) != '\0') {
                                  iVar1 = iVar1 + 1;
                                }
                                if (uVar17 + 0xb < uVar20) {
                                  if (*(char *)(lVar8 + (ulong)(uVar17 + 0xb) * 0x98 + 0x10) != '\0'
                                     ) {
                                    iVar1 = iVar1 + 1;
                                  }
                                  if (uVar17 + 0xc < uVar20) {
                                    if (*(char *)(lVar8 + (ulong)(uVar17 + 0xc) * 0x98 + 0x10) !=
                                        '\0') {
                                      iVar1 = iVar1 + 1;
                                    }
                                    if (uVar17 + 0xd < uVar20) {
                                      if (*(char *)(lVar8 + (ulong)(uVar17 + 0xd) * 0x98 + 0x10) !=
                                          '\0') {
                                        iVar1 = iVar1 + 1;
                                      }
                                      if ((uVar17 + 0xe < uVar20) &&
                                         (*(char *)(lVar8 + (ulong)(uVar17 + 0xe) * 0x98 + 0x10) !=
                                          '\0')) {
                                        iVar1 = iVar1 + 1;
                                      }
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
LAB_0016e0d8:
          aura_log(1,0,0,"func_id: %u functions hashed, %u identified",uVar20,iVar1);
          *param_5 = __ptr;
          if (param_6 != (undefined8 *)0x0) {
            *param_6 = 0;
          }
          uVar2 = 0;
          goto LAB_0016d348;
        }
        free(__ptr);
      }
      func_detect_destroy(&local_c0);
      if (param_6 != (undefined8 *)0x0) {
        pcVar9 = strdup("func_id: allocation failure");
        *param_6 = pcVar9;
      }
      uVar2 = 2;
      goto LAB_0016d348;
    }
    func_detect_destroy(&local_c0);
    if (param_6 != (undefined8 *)0x0) {
      *param_6 = 0;
    }
  }
  uVar2 = 1;
LAB_0016d348:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(uVar2,PTR___stack_chk_guard_005ffe88,0,
                     local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return;
}

