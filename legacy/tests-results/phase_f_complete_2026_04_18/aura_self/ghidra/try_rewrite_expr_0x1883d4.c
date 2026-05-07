
/* WARNING: Type propagation algorithm not settling */

undefined4 * try_rewrite_expr(int *param_1,long param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  long lVar5;
  void *pvVar6;
  undefined8 uVar7;
  long lVar8;
  int *piVar9;
  undefined8 uVar10;
  int *piVar11;
  int *piVar12;
  undefined4 *puVar13;
  int *__src;
  void *pvVar14;
  undefined8 local_f0;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 local_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 local_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 local_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 local_70;
  long local_58;
  
  local_58 = *(long *)PTR___stack_chk_guard_005ffe88;
  if ((((param_1 != (int *)0x0 && param_2 != 0) && (*param_1 == 0x10)) && (param_1[0x28] == 3)) &&
     (__src = *(int **)(param_1 + 0x26), __src != (int *)0x0)) {
    iVar3 = *__src;
    if (iVar3 != 0xf) goto LAB_00188444;
    if (__src[0x2a] == 2) {
      piVar12 = *(int **)(__src + 0x26);
      piVar11 = *(int **)(__src + 0x28);
      if (piVar12 == (int *)0x0) goto LAB_00188a7c;
      if (*piVar12 != 0xd) {
        if ((*piVar12 == 0xe) && ((char)piVar12[0x2a] == '\0')) goto LAB_001885f4;
        goto joined_r0x00188a70;
      }
      iVar1 = piVar12[0x26];
      if (piVar11 == (int *)0x0) goto LAB_00188444;
      if ((*piVar11 == 0xe) && ((char)piVar11[0x2a] == '\0')) {
        lVar5 = *(long *)(piVar11 + 0x26);
        iVar3 = sr_get_struct_count(param_2);
        if (iVar3 != 0) {
          iVar4 = 0;
          do {
            iVar2 = sr_get_struct_base_id(param_2,iVar4);
            if (iVar1 == iVar2) {
              iVar3 = 0;
              iVar1 = sr_get_struct_field_count(param_2,iVar4);
              if (iVar1 != 0) goto LAB_0018888c;
              break;
            }
            iVar4 = iVar4 + 1;
          } while (iVar3 != iVar4);
        }
        goto LAB_00188a9c;
      }
      goto LAB_001889b0;
    }
  }
  goto LAB_00188590;
  while (iVar3 = iVar3 + 1, iVar1 != iVar3) {
LAB_0018888c:
    lVar8 = sr_get_struct_field_offset(param_2,iVar4,iVar3);
    if (lVar5 == lVar8) {
      puVar13 = calloc(1,0x130);
      if (puVar13 == (undefined4 *)0x0) goto LAB_00188590;
      pvVar14 = *(void **)(__src + 0x26);
      *puVar13 = 0x13;
      pvVar6 = (void *)0x0;
      if ((pvVar14 != (void *)0x0) && (pvVar6 = calloc(1,0x130), pvVar6 != (void *)0x0)) {
        memcpy(pvVar6,pvVar14,0x130);
      }
      *(void **)(puVar13 + 0x26) = pvVar6;
      *(long *)(puVar13 + 0x38) = lVar5;
      *(undefined1 *)(puVar13 + 0x3a) = 1;
      __snprintf_chk(puVar13 + 0x28,0x40,2,0x40,"field_%ld",lVar5);
      sr_get_struct_field_type(param_2,iVar4,iVar3);
      ir_type_to_hir_at(&local_f0);
      *(undefined8 *)(puVar13 + 3) = uStack_e8;
      *(undefined8 *)(puVar13 + 1) = local_f0;
      *(undefined8 *)(puVar13 + 7) = uStack_d8;
      *(undefined8 *)(puVar13 + 5) = uStack_e0;
      *(undefined8 *)(puVar13 + 0xb) = uStack_c8;
      *(undefined8 *)(puVar13 + 9) = local_d0;
      *(undefined8 *)(puVar13 + 0xf) = uStack_b8;
      *(undefined8 *)(puVar13 + 0xd) = uStack_c0;
      *(undefined8 *)(puVar13 + 0x13) = uStack_a8;
      *(undefined8 *)(puVar13 + 0x11) = local_b0;
      *(undefined8 *)(puVar13 + 0x17) = uStack_98;
      *(undefined8 *)(puVar13 + 0x15) = uStack_a0;
      *(undefined8 *)(puVar13 + 0x1b) = uStack_88;
      *(undefined8 *)(puVar13 + 0x19) = local_90;
      *(undefined8 *)(puVar13 + 0x1f) = uStack_78;
      *(undefined8 *)(puVar13 + 0x1d) = uStack_80;
      *(undefined8 *)(puVar13 + 0x21) = local_70;
      lVar5 = sr_get_struct_name(param_2,iVar4);
      lVar8 = *(long *)(puVar13 + 0x26);
      if (lVar5 != 0 && lVar8 != 0) goto LAB_00188984;
      goto LAB_00188764;
    }
  }
LAB_00188a9c:
  piVar12 = *(int **)(__src + 0x26);
  piVar11 = *(int **)(__src + 0x28);
  if (piVar12 == (int *)0x0) {
LAB_00188a7c:
    if (piVar11 == (int *)0x0) goto LAB_001887bc;
  }
  else {
    iVar3 = *piVar12;
    if (iVar3 != 0xe) goto LAB_00188784;
    if ((char)piVar12[0x2a] != '\0') goto joined_r0x00188a70;
LAB_001885f4:
    lVar5 = *(long *)(piVar12 + 0x26);
    if (piVar11 == (int *)0x0) {
      iVar3 = *__src;
      goto LAB_00188444;
    }
    if (*piVar11 == 0xd) {
      iVar3 = piVar11[0x26];
      iVar1 = sr_get_struct_count(param_2);
      if (iVar1 != 0) {
        iVar4 = 0;
        do {
          iVar2 = sr_get_struct_base_id(param_2,iVar4);
          if (iVar3 == iVar2) {
            iVar3 = 0;
            iVar1 = sr_get_struct_field_count(param_2,iVar4);
            if (iVar1 != 0) goto LAB_0018866c;
            break;
          }
          iVar4 = iVar4 + 1;
        } while (iVar1 != iVar4);
      }
      goto LAB_00188778;
    }
  }
LAB_00188798:
  iVar1 = *piVar11;
LAB_0018879c:
  if (iVar1 != 0xd) goto LAB_001887bc;
  piVar12 = *(int **)(__src + 0x26);
  if (((piVar12 == (int *)0x0) || (*piVar12 != 0xf)) ||
     ((piVar12[0x2a] != 4 ||
      (((piVar9 = *(int **)(piVar12 + 0x28), piVar9 == (int *)0x0 || (*piVar9 != 0xe)) ||
       ((char)piVar9[0x2a] != '\0')))))) goto LAB_001887bc;
  lVar5 = *(long *)(piVar9 + 0x26);
  if ((0 < lVar5) && (iVar3 = find_array_by_base(param_2,piVar11[0x26]), iVar3 != -1)) {
    iVar1 = sr_get_array_elem_size(param_2,iVar3);
    iVar4 = (int)lVar5;
    if (iVar1 == iVar4) {
      puVar13 = calloc(1,0x130);
      if (puVar13 == (undefined4 *)0x0) goto LAB_00188594;
      uVar7 = *(undefined8 *)(__src + 0x28);
      *puVar13 = 0x14;
      uVar7 = clone_leaf(uVar7);
      *(undefined8 *)(puVar13 + 0x26) = uVar7;
      uVar7 = clone_leaf(*(undefined8 *)(piVar12 + 0x26));
      *(undefined8 *)(puVar13 + 0x28) = uVar7;
      puVar13[0x2a] = iVar4;
      sr_get_array_elem_type(param_2,iVar3);
      goto LAB_00188534;
    }
  }
  iVar3 = *__src;
  goto LAB_00188444;
  while (iVar3 = iVar3 + 1, iVar1 != iVar3) {
LAB_0018866c:
    lVar8 = sr_get_struct_field_offset(param_2,iVar4,iVar3);
    if (lVar5 == lVar8) {
      puVar13 = calloc(1,0x130);
      if (puVar13 != (undefined4 *)0x0) {
        pvVar14 = *(void **)(__src + 0x28);
        *puVar13 = 0x13;
        pvVar6 = (void *)0x0;
        if ((pvVar14 != (void *)0x0) && (pvVar6 = calloc(1,0x130), pvVar6 != (void *)0x0)) {
          memcpy(pvVar6,pvVar14,0x130);
        }
        *(void **)(puVar13 + 0x26) = pvVar6;
        *(long *)(puVar13 + 0x38) = lVar5;
        *(undefined1 *)(puVar13 + 0x3a) = 1;
        __snprintf_chk(puVar13 + 0x28,0x40,2,0x40,"field_%ld",lVar5);
        sr_get_struct_field_type(param_2,iVar4,iVar3);
        ir_type_to_hir_at(&local_f0);
        *(undefined8 *)(puVar13 + 3) = uStack_e8;
        *(undefined8 *)(puVar13 + 1) = local_f0;
        *(undefined8 *)(puVar13 + 7) = uStack_d8;
        *(undefined8 *)(puVar13 + 5) = uStack_e0;
        *(undefined8 *)(puVar13 + 0xb) = uStack_c8;
        *(undefined8 *)(puVar13 + 9) = local_d0;
        *(undefined8 *)(puVar13 + 0xf) = uStack_b8;
        *(undefined8 *)(puVar13 + 0xd) = uStack_c0;
        *(undefined8 *)(puVar13 + 0x13) = uStack_a8;
        *(undefined8 *)(puVar13 + 0x11) = local_b0;
        *(undefined8 *)(puVar13 + 0x17) = uStack_98;
        *(undefined8 *)(puVar13 + 0x15) = uStack_a0;
        *(undefined8 *)(puVar13 + 0x1b) = uStack_88;
        *(undefined8 *)(puVar13 + 0x19) = local_90;
        *(undefined8 *)(puVar13 + 0x1f) = uStack_78;
        *(undefined8 *)(puVar13 + 0x1d) = uStack_80;
        *(undefined8 *)(puVar13 + 0x21) = local_70;
        lVar5 = sr_get_struct_name(param_2,iVar4);
        lVar8 = *(long *)(puVar13 + 0x26);
        if (lVar8 != 0 && lVar5 != 0) {
LAB_00188984:
          __snprintf_chk(lVar8 + 4,0x80,2,0x80,&DAT_001fd9a0,lVar5);
          lVar5 = *(long *)(puVar13 + 0x26);
          *(undefined1 *)(lVar5 + 0x88) = 1;
          *(undefined1 *)(lVar5 + 0x8a) = 1;
        }
LAB_00188764:
        *(undefined8 *)(puVar13 + 0x24) = *(undefined8 *)(param_1 + 0x24);
        goto LAB_00188594;
      }
      goto LAB_00188590;
    }
  }
LAB_00188778:
  piVar12 = *(int **)(__src + 0x26);
  piVar11 = *(int **)(__src + 0x28);
  if (piVar12 != (int *)0x0) {
    iVar3 = *piVar12;
LAB_00188784:
    if (iVar3 != 0xd) goto joined_r0x00188a70;
LAB_001889b0:
    iVar3 = piVar12[0x26];
    if (piVar11 == (int *)0x0) {
      iVar3 = *__src;
      goto LAB_00188444;
    }
    iVar1 = *piVar11;
    if (iVar1 != 0xf) goto LAB_0018879c;
    if (piVar11[0x2a] != 4) goto LAB_001887bc;
    piVar12 = *(int **)(piVar11 + 0x28);
    if ((((piVar12 == (int *)0x0) || (*piVar12 != 0xe)) || ((char)piVar12[0x2a] != '\0')) ||
       (lVar5 = *(long *)(piVar12 + 0x26), lVar5 < 1)) {
      piVar12 = *(int **)(piVar11 + 0x26);
      if (piVar12 == (int *)0x0) goto LAB_001887bc;
LAB_00188a08:
      if (((*piVar12 != 0xe) || ((char)piVar12[0x2a] != '\0')) ||
         ((lVar5 = *(long *)(piVar12 + 0x26), lVar5 < 1 ||
          (iVar3 = find_array_by_base(param_2,iVar3), iVar3 == -1)))) {
        piVar11 = *(int **)(__src + 0x28);
        goto joined_r0x00188a70;
      }
      iVar1 = sr_get_array_elem_size(param_2,iVar3);
      if (iVar1 != (int)lVar5) goto LAB_00188a68;
      puVar13 = calloc(1,0x130);
      if (puVar13 == (undefined4 *)0x0) goto LAB_00188594;
      uVar7 = *(undefined8 *)(__src + 0x26);
      *puVar13 = 0x14;
      uVar7 = clone_leaf(uVar7);
      uVar10 = *(undefined8 *)(piVar11 + 0x28);
      *(undefined8 *)(puVar13 + 0x26) = uVar7;
      uVar7 = clone_leaf(uVar10);
      *(undefined8 *)(puVar13 + 0x28) = uVar7;
      puVar13[0x2a] = iVar1;
      sr_get_array_elem_type(param_2,iVar3);
    }
    else {
      iVar1 = find_array_by_base(param_2,iVar3);
      if (iVar1 == -1) {
LAB_00188b7c:
        piVar12 = *(int **)(piVar11 + 0x26);
        if (piVar12 != (int *)0x0) goto LAB_00188a08;
LAB_00188a68:
        piVar11 = *(int **)(__src + 0x28);
        goto joined_r0x00188a70;
      }
      iVar4 = sr_get_array_elem_size(param_2,iVar1);
      iVar2 = (int)lVar5;
      if (iVar4 != iVar2) goto LAB_00188b7c;
      puVar13 = calloc(1,0x130);
      if (puVar13 == (undefined4 *)0x0) goto LAB_00188594;
      uVar7 = *(undefined8 *)(__src + 0x26);
      *puVar13 = 0x14;
      uVar7 = clone_leaf(uVar7);
      *(undefined8 *)(puVar13 + 0x26) = uVar7;
      uVar7 = clone_leaf(*(undefined8 *)(piVar11 + 0x26));
      *(undefined8 *)(puVar13 + 0x28) = uVar7;
      puVar13[0x2a] = iVar2;
      sr_get_array_elem_type(param_2,iVar1);
    }
LAB_00188534:
    ir_type_to_hir_at(&local_f0);
    uVar7 = *(undefined8 *)(param_1 + 0x24);
    *(undefined8 *)(puVar13 + 3) = uStack_e8;
    *(undefined8 *)(puVar13 + 1) = local_f0;
    *(undefined8 *)(puVar13 + 7) = uStack_d8;
    *(undefined8 *)(puVar13 + 5) = uStack_e0;
    *(undefined8 *)(puVar13 + 0xb) = uStack_c8;
    *(undefined8 *)(puVar13 + 9) = local_d0;
    *(undefined8 *)(puVar13 + 0xf) = uStack_b8;
    *(undefined8 *)(puVar13 + 0xd) = uStack_c0;
    *(undefined8 *)(puVar13 + 0x13) = uStack_a8;
    *(undefined8 *)(puVar13 + 0x11) = local_b0;
    *(undefined8 *)(puVar13 + 0x17) = uStack_98;
    *(undefined8 *)(puVar13 + 0x15) = uStack_a0;
    *(undefined8 *)(puVar13 + 0x1b) = uStack_88;
    *(undefined8 *)(puVar13 + 0x19) = local_90;
    *(undefined8 *)(puVar13 + 0x1f) = uStack_78;
    *(undefined8 *)(puVar13 + 0x1d) = uStack_80;
    *(undefined8 *)(puVar13 + 0x21) = local_70;
    *(undefined8 *)(puVar13 + 0x24) = uVar7;
    goto LAB_00188594;
  }
joined_r0x00188a70:
  if (piVar11 != (int *)0x0) goto LAB_00188798;
LAB_001887bc:
  iVar3 = *__src;
LAB_00188444:
  if (iVar3 == 0xd) {
    iVar3 = __src[0x26];
    iVar1 = sr_get_struct_count(param_2);
    if (iVar1 != 0) {
      iVar4 = 0;
      do {
        iVar2 = sr_get_struct_base_id(param_2,iVar4);
        if (iVar3 == iVar2) {
          iVar3 = 0;
          iVar1 = sr_get_struct_field_count(param_2,iVar4);
          if (iVar1 != 0) goto LAB_001884b0;
          break;
        }
        iVar4 = iVar4 + 1;
      } while (iVar1 != iVar4);
    }
  }
  goto LAB_00188590;
  while (iVar3 = iVar3 + 1, iVar1 != iVar3) {
LAB_001884b0:
    lVar5 = sr_get_struct_field_offset(param_2,iVar4,iVar3);
    if (lVar5 == 0) {
      puVar13 = calloc(1,0x130);
      if (puVar13 != (undefined4 *)0x0) {
        *puVar13 = 0x13;
        pvVar6 = calloc(1,0x130);
        if (pvVar6 != (void *)0x0) {
          memcpy(pvVar6,__src,0x130);
        }
        *(undefined8 *)(puVar13 + 0x38) = 0;
        *(undefined1 *)(puVar13 + 0x3a) = 1;
        *(void **)(puVar13 + 0x26) = pvVar6;
        *(undefined8 *)(puVar13 + 0x28) = 0x305f646c656966;
        sr_get_struct_field_type(param_2,iVar4,iVar3);
        goto LAB_00188534;
      }
      break;
    }
  }
LAB_00188590:
  puVar13 = (undefined4 *)0x0;
LAB_00188594:
  if (local_58 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return puVar13;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                   local_58 - *(long *)PTR___stack_chk_guard_005ffe88);
}

