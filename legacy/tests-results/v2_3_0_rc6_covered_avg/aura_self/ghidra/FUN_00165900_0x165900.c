
void FUN_00165900(long *param_1,long param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  void *__ptr;
  void *__ptr_00;
  undefined4 *__ptr_01;
  uint *puVar6;
  undefined8 uVar7;
  uint uVar8;
  uint *puVar9;
  long lVar10;
  long lVar11;
  long lVar12;
  long lVar13;
  long extraout_x9;
  long lVar14;
  long lVar15;
  long lVar16;
  long extraout_x14;
  long lVar17;
  long extraout_x15;
  long lVar18;
  long extraout_x18;
  ulong __nmemb;
  long lVar19;
  long lVar20;
  long lVar21;
  undefined8 *local_80;
  undefined8 local_78;
  undefined8 local_70;
  long local_68;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (param_1 == (long *)0x0) {
    uVar7 = 0xfffffffc;
  }
  else {
    uVar1 = *(uint *)(param_1 + 1);
    if (uVar1 == 0) {
      uVar7 = 0xfffffffc;
    }
    else {
      if (param_2 == 0) {
        param_2 = *(long *)PTR_stdout_005fff40;
      }
      __nmemb = (ulong)uVar1;
      __ptr = calloc(__nmemb,1);
      __ptr_00 = calloc(__nmemb,1);
      __ptr_01 = calloc(__nmemb,4);
      if ((__ptr == (void *)0x0 || __ptr_00 == (void *)0x0) || __ptr_01 == (undefined4 *)0x0) {
        free(__ptr);
        free(__ptr_00);
        free(__ptr_01);
        uVar7 = 0xfffffffe;
      }
      else {
        lVar20 = *param_1;
        *__ptr_01 = 1;
        uVar8 = *(uint *)(lVar20 + 0x30);
        if (uVar8 != 0) {
          lVar13 = 0;
          lVar19 = *(long *)(lVar20 + 0x28);
          do {
            uVar2 = *(uint *)(lVar19 + lVar13 * 4);
            if (uVar2 < uVar1) {
              if (__ptr_01[uVar2] == 1) {
                *(undefined1 *)((long)__ptr + (ulong)uVar2) = 1;
              }
              else if (__ptr_01[uVar2] == 0) {
                __ptr_01[uVar2] = 1;
                lVar16 = lVar20 + (ulong)uVar2 * 0x50;
                uVar8 = *(uint *)(lVar16 + 0x30);
                if (uVar8 != 0) {
                  lVar11 = *(long *)(lVar16 + 0x28);
                  lVar17 = 0;
                  do {
                    uVar3 = *(uint *)(lVar11 + lVar17 * 4);
                    if (uVar3 < uVar1) {
                      if (__ptr_01[uVar3] == 1) {
                        *(undefined1 *)((long)__ptr + (ulong)uVar3) = 1;
                      }
                      else if (__ptr_01[uVar3] == 0) {
                        __ptr_01[uVar3] = 1;
                        lVar18 = lVar20 + (ulong)uVar3 * 0x50;
                        uVar8 = *(uint *)(lVar18 + 0x30);
                        if (uVar8 != 0) {
                          lVar14 = *(long *)(lVar18 + 0x28);
                          lVar21 = 0;
                          do {
                            uVar4 = *(uint *)(lVar14 + lVar21 * 4);
                            if (uVar4 < uVar1) {
                              if (__ptr_01[uVar4] == 1) {
                                *(undefined1 *)((long)__ptr + (ulong)uVar4) = 1;
                              }
                              else if (__ptr_01[uVar4] == 0) {
                                __ptr_01[uVar4] = 1;
                                lVar10 = lVar20 + (ulong)uVar4 * 0x50;
                                uVar8 = *(uint *)(lVar10 + 0x30);
                                if (uVar8 != 0) {
                                  lVar15 = *(long *)(lVar10 + 0x28);
                                  lVar12 = 0;
                                  do {
                                    uVar5 = *(uint *)(lVar15 + lVar12 * 4);
                                    if (uVar5 < uVar1) {
                                      if (__ptr_01[uVar5] == 1) {
                                        *(undefined1 *)((long)__ptr + (ulong)uVar5) = 1;
                                      }
                                      else if (__ptr_01[uVar5] == 0) {
                                        FUN_0015b0e4(param_1,(ulong)uVar5,__ptr_01,__ptr);
                                        uVar8 = *(uint *)(lVar10 + 0x30);
                                        lVar13 = extraout_x9;
                                        lVar16 = extraout_x14;
                                        lVar17 = extraout_x15;
                                        lVar18 = extraout_x18;
                                      }
                                    }
                                    lVar12 = lVar12 + 1;
                                  } while ((uint)lVar12 < uVar8);
                                }
                                __ptr_01[uVar4] = 2;
                                uVar8 = *(uint *)(lVar18 + 0x30);
                              }
                            }
                            lVar21 = lVar21 + 1;
                          } while ((uint)lVar21 < uVar8);
                        }
                        __ptr_01[uVar3] = 2;
                        uVar8 = *(uint *)(lVar16 + 0x30);
                      }
                    }
                    lVar17 = lVar17 + 1;
                  } while ((uint)lVar17 < uVar8);
                }
                __ptr_01[uVar2] = 2;
                uVar8 = *(uint *)(lVar20 + 0x30);
              }
            }
            lVar13 = lVar13 + 1;
          } while ((uint)lVar13 < uVar8);
        }
        *__ptr_01 = 2;
        local_80 = (undefined8 *)FUN_0017b990(param_1);
        if ((local_80 != (undefined8 *)0x0) && (*(uint *)(local_80 + 1) != 0)) {
          puVar9 = (uint *)*local_80;
          uVar1 = *(uint *)(param_1 + 1);
          puVar6 = puVar9 + (ulong)*(uint *)(local_80 + 1) * 0x18;
          do {
            if (*puVar9 < uVar1) {
              *(undefined1 *)((long)__ptr + (ulong)*puVar9) = 1;
            }
            puVar9 = puVar9 + 0x18;
          } while (puVar6 != puVar9);
        }
        local_78 = FUN_0017caa0(param_1);
        local_70 = FUN_0017d550(param_1);
        FUN_00163ec0(param_1,0,(int)param_1[1],__ptr,local_80,local_78,local_70,__ptr_00,param_2);
        FUN_0017db04(&local_70);
        FUN_0017d400(&local_78);
        FUN_0017c620(&local_80);
        free(__ptr);
        free(__ptr_00);
        free(__ptr_01);
        uVar7 = 0;
      }
    }
  }
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(uVar7,PTR___stack_chk_guard_005ffe88,0,
                   local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
}

