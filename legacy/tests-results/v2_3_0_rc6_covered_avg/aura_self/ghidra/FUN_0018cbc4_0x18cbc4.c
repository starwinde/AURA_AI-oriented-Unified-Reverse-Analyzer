
long FUN_0018cbc4(int *param_1,undefined1 *param_2,ulong param_3,long param_4,long param_5,
                 undefined8 *param_6)

{
  undefined8 uVar1;
  byte bVar2;
  bool bVar3;
  int iVar4;
  int *piVar5;
  undefined8 uVar6;
  ulong uVar7;
  int *piVar8;
  code *pcVar9;
  long lVar10;
  undefined1 *__src;
  long lVar11;
  ulong uVar12;
  uint uVar13;
  uint uVar14;
  size_t __n;
  size_t sVar15;
  long lVar16;
  long local_6a8;
  uint local_69c;
  int *local_688;
  long local_670;
  ushort local_632;
  undefined1 auStack_630 [520];
  undefined1 auStack_428 [8];
  undefined4 local_420;
  undefined8 local_2b0;
  int *local_118;
  long local_110;
  int *local_108;
  byte local_c1;
  long local_68;
  
  local_2b0 = 0;
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (param_1 != (int *)0x0) {
    param_1[0x14] = 0;
    if (*param_1 == 0) {
      param_1[0x17] = 0;
    }
    if (param_5 - 1U < 0x20) {
      local_670 = param_5 * 0xf8;
      local_69c = (uint)param_5;
      piVar5 = (int *)(*(code *)PTR_calloc_00600578)(0xf8,param_5);
    }
    else {
      local_670 = 0x1f00;
      local_69c = 0x20;
      piVar5 = (int *)(*(code *)PTR_calloc_00600578)(0xf8,0x20);
    }
    if (piVar5 != (int *)0x0) {
      local_688 = piVar5;
      if (param_3 == 0) {
LAB_0018cf78:
        local_6a8 = 0;
        (*(code *)PTR_free_00600588)(local_688);
        piVar5 = (int *)0x0;
      }
      else {
        local_6a8 = 0;
        __src = param_2;
        lVar11 = param_4;
        uVar12 = param_3;
        uVar13 = 0;
        lVar10 = local_6a8;
        do {
          local_6a8 = lVar10;
          FUN_0018fec0(auStack_428);
          uVar6 = 0;
          local_110 = lVar11;
          local_108 = param_1;
          if (param_1[0x18] != 0) {
            uVar6 = (*(code *)PTR_malloc_00600570)(0x748);
          }
          pcVar9 = *(code **)(param_1 + 6);
          uVar1 = *(undefined8 *)(param_1 + 8);
          *(undefined8 *)(piVar5 + 0x3c) = uVar6;
          *(long *)(piVar5 + 2) = lVar11;
          local_118 = piVar5;
          uVar7 = (*pcVar9)(param_1,__src,uVar12,auStack_428,&local_632,lVar11,uVar1);
          if ((uVar7 & 1) == 0) {
            if (param_1[0x18] != 0) {
              (*(code *)PTR_free_00600588)(*(undefined8 *)(piVar5 + 0x3c));
            }
            if ((*(byte *)(param_1 + 0x20) & 1) == 0) goto joined_r0x0018d088;
            bVar2 = *(byte *)((long)param_1 + 0x81);
            __n = (size_t)bVar2;
            if (uVar12 < bVar2) goto joined_r0x0018d088;
            if (*(code **)(param_1 + 0x24) == (code *)0x0) {
              *piVar5 = 0;
              *(long *)(piVar5 + 2) = lVar11;
              *(ushort *)(piVar5 + 4) = (ushort)bVar2;
              memcpy((void *)((long)piVar5 + 0x12),__src,__n);
              strncpy((char *)((long)piVar5 + 0x2a),*(char **)(param_1 + 0x22),0x1f);
              if (__n != 0) goto LAB_0018cdac;
              *(undefined1 *)((long)piVar5 + 0x4a) = 0;
            }
            else {
              __n = (**(code **)(param_1 + 0x24))
                              (param_2,param_3,lVar11 - param_4,*(undefined8 *)(param_1 + 0x26));
              if (uVar12 <= __n - 1) goto joined_r0x0018d088;
              *piVar5 = 0;
              *(long *)(piVar5 + 2) = lVar11;
              *(short *)(piVar5 + 4) = (short)__n;
              memcpy((void *)((long)piVar5 + 0x12),__src,__n);
              strncpy((char *)((long)piVar5 + 0x2a),*(char **)(param_1 + 0x22),0x1f);
LAB_0018cdac:
              iVar4 = FUN_001907d0((long)piVar5 + 0x4a,0xa0,"0x%02x",*__src);
              lVar16 = 0xa0 - (long)iVar4;
              lVar10 = (long)piVar5 + 0x4a + (long)iVar4;
              if (__n != 1) {
                sVar15 = 1;
                do {
                  iVar4 = FUN_001907d0(lVar10,lVar16,", 0x%02x",__src[sVar15]);
                  if ((iVar4 < 0) || (uVar7 = (ulong)iVar4, lVar16 - 1U < uVar7)) break;
                  sVar15 = sVar15 + 1;
                  lVar10 = lVar10 + uVar7;
                  lVar16 = lVar16 - uVar7;
                } while (sVar15 != __n);
              }
            }
            piVar5[0x3c] = 0;
            piVar5[0x3d] = 0;
            uVar14 = uVar13 + 1;
            if (param_5 != 0 && param_5 == local_6a8 + 1) break;
          }
          else {
            FUN_00190360(auStack_630);
            pcVar9 = *(code **)(param_1 + 0x10);
            *(ushort *)(local_118 + 4) = local_632;
            (*pcVar9)(param_1,piVar5,local_420);
            (**(code **)(param_1 + 2))(auStack_428,auStack_630,*(undefined8 *)(param_1 + 4));
            FUN_0018c330(param_1,piVar5,auStack_630,auStack_428,*(undefined8 *)(param_1 + 0x12),
                         __src);
            if (*param_1 == 3) {
              *piVar5 = *piVar5 + (uint)local_c1;
            }
            __n = (size_t)local_632;
            uVar14 = uVar13 + 1;
            if (param_5 != 0 && param_5 == local_6a8 + 1) break;
          }
          lVar10 = local_6a8 + 1;
          uVar14 = uVar13 + 1;
          piVar5 = piVar5 + 0x3e;
          if (uVar14 == local_69c) {
            local_69c = (uVar14 * 8) / 5;
            local_670 = local_670 + (ulong)local_69c * 0xf8;
            piVar8 = (int *)(*(code *)PTR_realloc_00600580)(local_688);
            if (piVar8 == (int *)0x0) {
              if ((param_1[0x18] != 0) && (lVar10 != 0)) {
                lVar11 = 0;
                piVar5 = local_688;
                do {
                  (*(code *)PTR_free_00600588)(*(undefined8 *)(piVar5 + 0x3c));
                  bVar3 = local_6a8 != lVar11;
                  lVar11 = lVar11 + 1;
                  piVar5 = piVar5 + 0x3e;
                } while (bVar3);
              }
              goto LAB_0018d128;
            }
            uVar14 = 0;
            piVar5 = piVar8 + lVar10 * 0x3e;
            local_688 = piVar8;
          }
          __src = __src + __n;
          lVar11 = lVar11 + __n;
          uVar12 = uVar12 - __n;
          uVar13 = uVar14;
        } while (uVar12 != 0);
        local_6a8 = local_6a8 + 1;
        uVar13 = uVar14;
joined_r0x0018d088:
        if (local_6a8 == 0) goto LAB_0018cf78;
        piVar5 = local_688;
        if ((uVar13 != local_69c) &&
           (piVar5 = (int *)(*(code *)PTR_realloc_00600580)
                                      (local_688,local_670 + (ulong)(local_69c - uVar13) * -0xf8),
           piVar5 == (int *)0x0)) {
          if (param_1[0x18] != 0) {
            lVar11 = 0;
            piVar5 = local_688;
            do {
              lVar11 = lVar11 + 1;
              piVar8 = piVar5 + 0x3c;
              piVar5 = piVar5 + 0x3e;
              (*(code *)PTR_free_00600588)(*(undefined8 *)piVar8);
            } while (local_6a8 != lVar11);
          }
LAB_0018d128:
          local_6a8 = 0;
          (*(code *)PTR_free_00600588)(local_688);
          *param_6 = 0;
          param_1[0x14] = 1;
          goto LAB_0018cfa8;
        }
      }
      *param_6 = piVar5;
      goto LAB_0018cfa8;
    }
    param_1[0x14] = 1;
  }
  local_6a8 = 0;
LAB_0018cfa8:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return local_6a8;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                   local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
}

