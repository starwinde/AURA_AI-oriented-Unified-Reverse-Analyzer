
undefined4 FUN_001435b0(long param_1,ulong param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  long lVar4;
  long lVar5;
  ulong *__ptr;
  void *__ptr_00;
  long lVar6;
  ulong *puVar7;
  ulong *puVar8;
  undefined8 *puVar9;
  undefined4 uVar10;
  char *__s2;
  ulong uVar11;
  undefined **ppuVar12;
  undefined8 *puVar13;
  long local_b8;
  long local_b0;
  long local_a8;
  long local_a0;
  long local_98;
  long local_90;
  long local_88;
  long *local_80 [3];
  long local_68;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (param_1 == 0) {
    uVar10 = 0xfffffffc;
    goto LAB_00143a1c;
  }
  lVar4 = FUN_00140cb0(param_1,0);
  if (lVar4 == 0) {
    uVar10 = 0xfffffff9;
    __fprintf_chk(*(undefined8 *)PTR_stderr_005fffd8,2,"aura: failed to parse \'%s\'\n",param_1);
    goto LAB_00143a1c;
  }
  uVar1 = *(uint *)(lVar4 + 0x20);
  puVar13 = *(undefined8 **)(lVar4 + 0x18);
  if (uVar1 != 0) {
    __s2 = ".text";
    puVar9 = puVar13;
    do {
      if (((char *)*puVar9 != (char *)0x0) && (iVar2 = strcmp((char *)*puVar9,".text"), iVar2 == 0))
      {
        if (puVar9[5] != 0) {
          puVar9 = puVar13;
          ppuVar12 = &PTR_DAT_005df528;
          goto LAB_00143688;
        }
        break;
      }
      puVar9 = puVar9 + 7;
    } while (puVar9 != puVar13 + (ulong)uVar1 * 7);
  }
  __fprintf_chk(*(undefined8 *)PTR_stderr_005fffd8,2,"aura: .text section not found in \'%s\'\n",
                param_1);
  FUN_00144de4(lVar4);
  goto LAB_001436dc;
  while (puVar7 = puVar7 + 0x13, puVar7 != puVar8) {
LAB_001437c8:
    if ((*puVar7 == param_2) && (param_2 < puVar7[1])) {
      lVar5 = 0;
      puVar8 = __ptr;
      goto LAB_001437fc;
    }
  }
  goto LAB_00143810;
  while( true ) {
    lVar5 = lVar5 + 1;
    puVar8 = puVar8 + 0x1c;
    if (lVar6 == lVar5) break;
LAB_001437fc:
    if (puVar7[1] <= *puVar8) {
      if (lVar5 != 0) {
        lVar6 = lVar5;
      }
      break;
    }
  }
LAB_00143810:
  FUN_0014ae20(local_80);
  __ptr_00 = (void *)FUN_0016a2d0(lVar4,__ptr,lVar6,param_2);
  local_b8 = 0;
  FUN_00176034(local_80,__ptr,lVar6,*(undefined4 *)(lVar4 + 0xc));
  local_b8 = FUN_00176fd0(__ptr,lVar6,param_2,*(undefined4 *)(lVar4 + 0xc),local_80,0);
  lVar5 = FUN_00147b50(__ptr,lVar6,param_2);
  local_b0 = lVar5;
  free(__ptr);
  if (lVar5 == 0) {
    fwrite("aura: cfg_build failed\n",1,0x17,*(FILE **)PTR_stderr_005fffd8);
  }
  else {
    local_a8 = FUN_001498a0(lVar5);
    if (local_a8 == 0) {
      FUN_00148610(&local_b0,0);
      fwrite("aura: dfg_analyze failed\n",1,0x19,*(FILE **)PTR_stderr_005fffd8);
    }
    else {
      if (iVar2 == 4) {
        local_a0 = FUN_00152120(local_b0,local_a8,&DAT_001f9a68,param_2);
      }
      else {
        local_a0 = FUN_0014df90();
      }
      FUN_00149820(&local_a8);
      FUN_00148610(&local_b0);
      if (local_a0 != 0) {
        FUN_0014cd90();
        FUN_0014d570(local_a0,7);
        FUN_00158620(local_a0);
        local_98 = FUN_0017caa0(local_a0);
        local_90 = FUN_0017b990(local_a0);
        local_88 = FUN_00180d90(local_a0,local_98,local_90,lVar4,__ptr_00);
        puVar13 = (undefined8 *)PTR_stdout_005fff40;
        if (local_88 == 0) {
LAB_00143a60:
          __fprintf_chk(*puVar13,2,&DAT_001f9ae0,param_1,param_2);
          FUN_0014d7d4(local_a0,*puVar13);
        }
        else {
          local_80[0] = (long *)FUN_00157780(local_a0);
          if (local_80[0] != (long *)0x0) {
            FUN_00188f20(local_88,local_a0,local_80[0]);
          }
          puVar13 = (undefined8 *)PTR_stdout_005fff40;
          __fprintf_chk(*(undefined8 *)PTR_stdout_005fff40,2,
                        "// AURA decompile (HIR pipeline)\n// file:    %s\n// func:    0x%016lx\n\n"
                        ,param_1,param_2);
          if (local_80[0] != (long *)0x0) {
            FUN_00157f94(local_80[0],*puVar13);
            FUN_00157f10(local_80);
          }
          FUN_00183e80(local_b8);
          iVar2 = FUN_00186974(local_88,*puVar13,lVar4);
          if (iVar2 != 0) {
            FUN_00183e80(0);
            FUN_001815b0(&local_88);
            goto LAB_00143a60;
          }
          FUN_00183e80(0);
          FUN_001815b0(&local_88);
        }
        if (local_90 != 0) {
          FUN_0017c620(&local_90);
        }
        if (local_98 != 0) {
          FUN_0017d400(&local_98);
        }
        if (__ptr_00 != (void *)0x0) {
          FUN_00169ff0(__ptr_00);
          free(__ptr_00);
        }
        if (local_b8 != 0) {
          FUN_00178844(&local_b8);
        }
        FUN_0014deb0(&local_a0);
        FUN_00144de4(lVar4);
        uVar10 = 0;
        goto LAB_00143a1c;
      }
      __fprintf_chk(*(undefined8 *)PTR_stderr_005fffd8,2,"aura: ir_lift failed at 0x%016lx\n",
                    param_2);
    }
  }
LAB_00143b10:
  uVar10 = 0xfffffffe;
  goto LAB_00143a1c;
LAB_00143688:
  do {
    if (((char *)*puVar9 == (char *)0x0) || (iVar2 = strcmp((char *)*puVar9,__s2), iVar2 != 0)) {
      puVar9 = puVar9 + 7;
      if (puVar9 != puVar13 + (ulong)uVar1 * 7) goto LAB_00143688;
    }
    else if (((puVar9[5] != 0) && (puVar9[3] != 0)) &&
            (uVar11 = puVar9[1], param_2 < puVar9[3] + uVar11 && uVar11 <= param_2)) {
      lVar5 = FUN_001446e0(*(undefined4 *)(lVar4 + 0xc));
      if (lVar5 == 0) {
        fwrite("aura: disassembler init failed\n",1,0x1f,*(FILE **)PTR_stderr_005fffd8);
        FUN_00144de4(lVar4);
      }
      else {
        lVar6 = puVar9[3];
        __ptr = malloc(0x1c000);
        if (__ptr == (ulong *)0x0) {
          FUN_001447a4(lVar5);
          FUN_00144de4(lVar4);
          goto LAB_00143b10;
        }
        iVar3 = FUN_001447f0(lVar5,puVar9[5] + (param_2 - uVar11),(uVar11 + lVar6) - param_2,param_2
                             ,__ptr,0x200);
        lVar6 = (long)iVar3;
        FUN_001447a4(lVar5);
        iVar2 = *(int *)(lVar4 + 0xc);
        if (0 < iVar3) {
          local_80[0] = (long *)FUN_00149f60(__ptr,lVar6,lVar4,0);
          if (((local_80[0] == (long *)0x0) ||
              (puVar13 = (undefined8 *)*local_80[0], puVar13 == (undefined8 *)0x0)) ||
             ((puVar7 = (ulong *)*puVar13, puVar7 == (ulong *)0x0 || (*(uint *)(puVar13 + 1) == 0)))
             ) goto LAB_00143810;
          puVar8 = puVar7 + (ulong)*(uint *)(puVar13 + 1) * 0x13;
          goto LAB_001437c8;
        }
        __fprintf_chk(*(undefined8 *)PTR_stderr_005fffd8,2,"aura: disasm_run failed at 0x%016lx\n",
                      param_2);
        free(__ptr);
      }
      uVar10 = 0xfffffff8;
      goto LAB_00143a1c;
    }
    __s2 = *ppuVar12;
    puVar9 = puVar13;
    ppuVar12 = ppuVar12 + 1;
  } while (__s2 != (char *)0x0);
  __fprintf_chk(*(undefined8 *)PTR_stderr_005fffd8,2,
                "aura: func_addr 0x%016lx is outside code sections (.text/.plt/.init/.fini)\n",
                param_2);
  FUN_00144de4(lVar4);
LAB_001436dc:
  uVar10 = 0xfffffffa;
LAB_00143a1c:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return uVar10;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                   local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
}

