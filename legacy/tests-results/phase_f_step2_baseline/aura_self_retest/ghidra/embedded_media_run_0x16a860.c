
void embedded_media_run(long *param_1)

{
  long *plVar1;
  ulong uVar2;
  int iVar3;
  uint uVar4;
  ulong uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  long lVar9;
  undefined8 uVar10;
  long *__ptr;
  void *pvVar11;
  ulong uVar12;
  char *pcVar13;
  long *plVar14;
  undefined8 *in_x4;
  undefined8 *in_x5;
  ulong uVar15;
  long *plVar16;
  ulong uVar17;
  long lStack_f8;
  undefined4 local_ec;
  undefined4 uStack_e8;
  undefined4 uStack_e4;
  undefined4 uStack_e0;
  undefined4 uStack_dc;
  undefined4 uStack_d8;
  undefined4 uStack_d4;
  undefined4 uStack_d0;
  undefined4 local_cc;
  undefined4 uStack_c8;
  undefined4 uStack_c4;
  undefined4 uStack_c0;
  undefined4 uStack_bc;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined4 uStack_b0;
  undefined4 local_ac;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined4 uStack_a0;
  undefined4 uStack_9c;
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined4 uStack_90;
  undefined4 local_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 local_70;
  undefined4 uStack_6c;
  long local_68;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if ((param_1 != (long *)0x0) && (lVar9 = *param_1, lVar9 != 0)) {
    plVar1 = *(long **)(lVar9 + 8);
    uVar2 = *(ulong *)(lVar9 + 0x10);
    if (plVar1 != (long *)0x0 && uVar2 != 0) {
      __ptr = calloc(1,0x10);
      if (__ptr != (long *)0x0) {
        pvVar11 = calloc(0x100,0x98);
        *__ptr = (long)pvVar11;
        if (pvVar11 != (void *)0x0) {
          uVar15 = 3;
          uVar17 = 4;
          *(undefined4 *)(__ptr + 1) = 0;
          plVar16 = plVar1;
LAB_0016aa18:
          if ((uVar15 + 5 <= uVar2) && (*plVar16 == 0xa1a0a0d474e5089)) {
            lVar9 = 0;
LAB_0016aa58:
            uStack_6c = 0;
            iVar3 = (&DAT_005dff00)[lVar9 * 8];
            uStack_e4 = 0;
            uStack_e0 = 0;
            local_ec = 0;
            uStack_e8 = 0;
            uStack_d4 = 0;
            uStack_d0 = 0;
            uStack_dc = 0;
            uStack_d8 = 0;
            uStack_c4 = 0;
            uStack_c0 = 0;
            local_cc = 0;
            uStack_c8 = 0;
            uStack_b4 = 0;
            uStack_b0 = 0;
            uStack_bc = 0;
            uStack_b8 = 0;
            uStack_a4 = 0;
            uStack_a0 = 0;
            local_ac = 0;
            uStack_a8 = 0;
            uStack_94 = 0;
            uStack_90 = 0;
            uStack_9c = 0;
            uStack_98 = 0;
            uStack_84 = 0;
            uStack_80 = 0;
            local_8c = 0;
            uStack_88 = 0;
            uStack_74 = 0;
            local_70 = 0;
            uStack_7c = 0;
            uStack_78 = 0;
            if (iVar3 == 2) {
              uVar12 = uVar15 + 0x11;
              uVar5 = uVar15 + 5;
              while (uVar12 <= uVar2) {
                if ((*(long *)((long)plVar1 + uVar5) == 0x444e454900000000) &&
                   (*(int *)((long)plVar1 + uVar5 + 8) == -0x7d9fbd52)) {
                  lStack_f8 = (uVar5 - uVar15) + 0xf;
                  goto LAB_0016acac;
                }
                uVar12 = uVar5 + 0xd;
                uVar5 = uVar5 + 1;
              }
            }
            else if (iVar3 == 5) {
              for (uVar12 = uVar15 + 6; uVar12 <= uVar2; uVar12 = uVar12 + 1) {
                if ((*(int *)((long)plVar1 + (uVar12 - 5)) == 0x4f452525) &&
                   (*(char *)((long)plVar1 + (uVar12 - 1)) == 'F')) goto joined_r0x0016aba0;
              }
            }
            else {
              uVar12 = uVar15;
              if (iVar3 == 1) {
                for (; uVar12 < uVar2; uVar12 = uVar12 + 1) {
                  if ((*(char *)((long)plVar1 + (uVar12 - 1)) == -1) &&
                     (*(char *)((long)plVar1 + uVar12) == -0x27)) {
                    lStack_f8 = (uVar12 - uVar15) + 4;
                    goto LAB_0016acac;
                  }
                }
              }
            }
            lStack_f8 = 0;
            goto LAB_0016abcc;
          }
          if (((uVar15 <= uVar2) && ((short)*plVar16 == -0x2701)) &&
             (lVar9 = 1, *(char *)((long)plVar16 + 2) == -1)) goto LAB_0016aa58;
          if (uVar15 + 3 <= uVar2) {
            if ((int)*plVar16 == 0x38464947) {
              lVar9 = 2;
              if (*(short *)((long)plVar16 + 4) == 0x6137) goto LAB_0016aa58;
              iVar3 = (int)*plVar16;
            }
            else {
              iVar3 = (int)*plVar16;
            }
            if ((iVar3 == 0x38464947) && (lVar9 = 3, *(short *)((long)plVar16 + 4) == 0x6139))
            goto LAB_0016aa58;
          }
          if (uVar17 <= uVar2) {
            iVar3 = (int)*plVar16;
            if (iVar3 == 0x46445025) {
              lVar9 = 4;
            }
            else if (iVar3 == 0x4034b50) {
              lVar9 = 5;
            }
            else if (iVar3 == 0x464c457f) {
              lVar9 = 6;
            }
            else if (iVar3 == 0x46464952) {
              lVar9 = 7;
            }
            else {
              if (iVar3 != 0x5367674f) goto LAB_0016a9d4;
              lVar9 = 8;
            }
            goto LAB_0016aa58;
          }
LAB_0016a9d4:
          if (uVar15 - 1 <= uVar2) {
            if ((short)*plVar16 == 0x4d42) {
              lVar9 = 9;
            }
            else {
              lVar9 = 10;
              if ((short)*plVar16 != 0x5a4d) goto LAB_0016aa00;
            }
            goto LAB_0016aa58;
          }
          goto LAB_0016aa00;
        }
        free(__ptr);
      }
      if (in_x5 != (undefined8 *)0x0) {
        pcVar13 = malloc(0x40);
        *in_x5 = pcVar13;
        uVar8 = s_embedded_media__allocation_faile_001f9bb8._24_8_;
        uVar7 = s_embedded_media__allocation_faile_001f9bb8._16_8_;
        uVar6 = s_embedded_media__allocation_faile_001f9bb8._8_8_;
        uVar10 = s_embedded_media__allocation_faile_001f9bb8._0_8_;
        if (pcVar13 != (char *)0x0) {
          *(undefined2 *)(pcVar13 + 0x20) = s_embedded_media__allocation_faile_001f9bb8._32_2_;
          *(undefined8 *)(pcVar13 + 8) = uVar6;
          *(undefined8 *)pcVar13 = uVar10;
          *(undefined8 *)(pcVar13 + 0x18) = uVar8;
          *(undefined8 *)(pcVar13 + 0x10) = uVar7;
        }
      }
      uVar10 = 2;
      goto LAB_0016a8c0;
    }
  }
  if (in_x4 != (undefined8 *)0x0) {
    *in_x4 = 0;
  }
LAB_0016a8bc:
  uVar10 = 1;
LAB_0016a8c0:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(uVar10,PTR___stack_chk_guard_005ffe88,0,
                   local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
joined_r0x0016aba0:
  for (; (uVar12 < uVar2 &&
         (*(char *)((long)plVar1 + uVar12) == '\r' || *(char *)((long)plVar1 + uVar12) == '\n'));
      uVar12 = uVar12 + 1) {
  }
  lStack_f8 = uVar12 - (uVar15 - 3);
LAB_0016acac:
  if (lStack_f8 == 0) {
LAB_0016abcc:
    __snprintf_chk(&local_ec,0x80,2,0x80,"%s at offset 0x%lx",(&PTR_s_PNG_image_005dff08)[lVar9 * 4]
                  );
  }
  else {
    __snprintf_chk(&local_ec,0x80,2,0x80,"%s at offset 0x%lx (%lu bytes)",
                   (&PTR_s_PNG_image_005dff08)[lVar9 * 4]);
  }
  uVar4 = *(uint *)(__ptr + 1);
  if (uVar4 < 0x100) {
    *(uint *)(__ptr + 1) = uVar4 + 1;
    plVar14 = (long *)(*__ptr + (ulong)uVar4 * 0x98);
    plVar14[1] = lStack_f8;
    *plVar14 = uVar15 - 3;
    plVar14[3] = CONCAT44(uStack_e4,uStack_e8);
    plVar14[2] = CONCAT44(local_ec,iVar3);
    plVar14[5] = CONCAT44(uStack_d4,uStack_d8);
    plVar14[4] = CONCAT44(uStack_dc,uStack_e0);
    plVar14[7] = CONCAT44(uStack_c4,uStack_c8);
    plVar14[6] = CONCAT44(local_cc,uStack_d0);
    plVar14[9] = CONCAT44(uStack_b4,uStack_b8);
    plVar14[8] = CONCAT44(uStack_bc,uStack_c0);
    plVar14[0xb] = CONCAT44(uStack_a4,uStack_a8);
    plVar14[10] = CONCAT44(local_ac,uStack_b0);
    plVar14[0xd] = CONCAT44(uStack_94,uStack_98);
    plVar14[0xc] = CONCAT44(uStack_9c,uStack_a0);
    plVar14[0xf] = CONCAT44(uStack_84,uStack_88);
    plVar14[0xe] = CONCAT44(local_8c,uStack_90);
    plVar14[0x11] = CONCAT44(uStack_74,uStack_78);
    plVar14[0x10] = CONCAT44(uStack_7c,uStack_80);
    plVar14[0x12] = CONCAT44(uStack_6c,local_70);
  }
LAB_0016aa00:
  uVar12 = uVar15 - 2;
  plVar16 = (long *)((long)plVar16 + 1);
  uVar17 = uVar17 + 1;
  uVar15 = uVar15 + 1;
  if (uVar2 <= uVar12) goto LAB_0016aaf0;
  goto LAB_0016aa18;
LAB_0016aaf0:
  if ((int)__ptr[1] != 0) {
    if (in_x4 != (undefined8 *)0x0) {
      *in_x4 = __ptr;
    }
    uVar10 = 0;
    goto LAB_0016a8c0;
  }
  free((void *)*__ptr);
  free(__ptr);
  if (in_x4 != (undefined8 *)0x0) {
    *in_x4 = 0;
  }
  goto LAB_0016a8bc;
}

