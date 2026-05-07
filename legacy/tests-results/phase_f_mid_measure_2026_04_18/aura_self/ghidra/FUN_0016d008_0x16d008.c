
void FUN_0016d008(long *param_1,undefined8 param_2,long param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 *param_6)

{
  undefined8 *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  undefined8 uVar7;
  undefined2 *puVar8;
  undefined8 *__ptr;
  uint *puVar9;
  undefined8 *unaff_x19;
  ulong __n;
  void *__ptr_00;
  char *pcVar10;
  long lVar11;
  long lVar12;
  undefined2 in_stack_00000008;
  
  if (((param_1 == (long *)0x0) || (*param_1 == 0)) ||
     (pcVar10 = *(char **)(*param_1 + 0x18), pcVar10 == (char *)0x0)) {
joined_r0x0016d210:
    if (unaff_x19 != (undefined8 *)0x0) {
      *unaff_x19 = 0;
    }
  }
  else {
    pcVar6 = strrchr(pcVar10,0x2f);
    if (pcVar6 == (char *)0x0) {
      puVar8 = &stack0x00000008;
      in_stack_00000008 = 0x2e;
    }
    else {
      __n = (long)pcVar6 - (long)pcVar10;
      if (0xfff < __n) goto joined_r0x0016d210;
      puVar8 = memcpy(&stack0x00000008,pcVar10,__n);
      *(undefined1 *)((long)puVar8 + __n) = 0;
    }
    uVar4 = __snprintf_chk(&stack0x00001008,0x1000,2,0x1000,"%s/types.aura-types",puVar8);
    if ((0xfff < uVar4) ||
       (__ptr = (undefined8 *)data_archive_load(&stack0x00001008), __ptr == (undefined8 *)0x0))
    goto joined_r0x0016d210;
    __ptr_00 = (void *)*__ptr;
    uVar4 = *(uint *)(__ptr + 1);
    if (uVar4 != 0) {
      lVar12 = 0;
      uVar5 = uVar4;
      do {
        while( true ) {
          lVar11 = lVar12 * 0x20;
          puVar1 = (undefined8 *)((long)__ptr_00 + lVar11);
          if (puVar1 == (undefined8 *)0x0) break;
          lVar12 = lVar12 + 1;
          free(*(void **)((long)__ptr_00 + lVar11));
          free((void *)puVar1[1]);
          free((void *)puVar1[2]);
          uVar5 = *(uint *)(__ptr + 1);
          __ptr_00 = (void *)*__ptr;
          *puVar1 = 0;
          puVar1[1] = 0;
          puVar1[2] = 0;
          if (uVar5 <= (uint)lVar12) goto LAB_0016d158;
        }
        lVar12 = lVar12 + 1;
      } while ((uint)lVar12 < uVar5);
LAB_0016d158:
      free(__ptr_00);
      free((void *)__ptr[2]);
      free(__ptr);
      puVar9 = calloc(1,0x10);
      if (puVar9 == (uint *)0x0) {
        if (param_6 != (undefined8 *)0x0) {
          pcVar10 = malloc(0x40);
          *param_6 = pcVar10;
          uVar3 = s_data_archive__allocation_failed_001fbbe8._24_8_;
          uVar2 = s_data_archive__allocation_failed_001fbbe8._16_8_;
          uVar7 = s_data_archive__allocation_failed_001fbbe8._0_8_;
          if (pcVar10 != (char *)0x0) {
            *(undefined8 *)(pcVar10 + 8) = s_data_archive__allocation_failed_001fbbe8._8_8_;
            *(undefined8 *)pcVar10 = uVar7;
            *(undefined8 *)(pcVar10 + 0x18) = uVar3;
            *(undefined8 *)(pcVar10 + 0x10) = uVar2;
          }
        }
        uVar7 = 2;
      }
      else {
        *puVar9 = uVar4;
        pcVar10 = strdup(&stack0x00001008);
        *(char **)(puVar9 + 2) = pcVar10;
        if (unaff_x19 != (undefined8 *)0x0) {
          *unaff_x19 = puVar9;
        }
        uVar7 = 0;
      }
      goto LAB_0016d070;
    }
    free(__ptr_00);
    free((void *)__ptr[2]);
    free(__ptr);
    if (unaff_x19 != (undefined8 *)0x0) {
      *unaff_x19 = 0;
    }
  }
  uVar7 = 1;
LAB_0016d070:
  if (param_3 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(uVar7,PTR___stack_chk_guard_005ffe88,0,
                     param_3 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return;
}

