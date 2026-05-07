
undefined4 FUN_00141c60(long param_1)

{
  ulong uVar1;
  int iVar2;
  long lVar3;
  long lVar4;
  void *__ptr;
  undefined8 *puVar5;
  undefined4 uVar6;
  undefined8 *puVar7;
  long lVar8;
  ulong uVar9;
  long local_70;
  long local_68;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (param_1 == 0) {
    uVar6 = 0xfffffffc;
  }
  else {
    lVar3 = FUN_00140cb0(param_1,PTR___stack_chk_guard_005ffe88,0);
    if (lVar3 == 0) {
      __fprintf_chk(*(undefined8 *)PTR_stderr_005fffd8,2,"aura: failed to parse \'%s\'\n",param_1);
LAB_00141ef0:
      uVar6 = 0xfffffff9;
    }
    else {
      puVar5 = *(undefined8 **)(lVar3 + 0x18);
      if (*(uint *)(lVar3 + 0x20) != 0) {
        puVar7 = puVar5 + (ulong)*(uint *)(lVar3 + 0x20) * 7;
        do {
          if (((char *)*puVar5 != (char *)0x0) &&
             (iVar2 = strcmp((char *)*puVar5,".text"), iVar2 == 0)) {
            lVar8 = puVar5[5];
            if (lVar8 == 0) {
              __fprintf_chk(*(undefined8 *)PTR_stderr_005fffd8,2,
                            "aura: cannot map .text data from \'%s\'\n",param_1);
              FUN_00144de4(lVar3);
              goto LAB_00141ef0;
            }
            lVar4 = FUN_001446e0(*(undefined4 *)(lVar3 + 0xc));
            if (lVar4 == 0) {
              fwrite("aura: disassembler init failed\n",1,0x1f,*(FILE **)PTR_stderr_005fffd8);
              FUN_00144de4(lVar3);
LAB_00141e6c:
              uVar6 = 0xfffffff8;
            }
            else {
              uVar9 = puVar5[3];
              uVar1 = uVar9;
              if (0x800000 < uVar9) {
                uVar1 = 0x800000;
              }
              if (uVar1 < 0x2000) {
                uVar1 = 0x2000;
              }
              __ptr = malloc(uVar1 * 0xe0);
              if (__ptr == (void *)0x0) {
                FUN_001447a4(lVar4);
                FUN_00144de4(lVar3);
              }
              else {
                iVar2 = FUN_001447f0(lVar4,lVar8,uVar9,puVar5[1],__ptr,uVar1);
                FUN_001447a4(lVar4);
                if (iVar2 < 1) {
                  __fprintf_chk(*(undefined8 *)PTR_stderr_005fffd8,2,
                                "aura: disasm_run failed on .text of \'%s\'\n",param_1);
                  free(__ptr);
                  FUN_00144de4(lVar3);
                  goto LAB_00141e6c;
                }
                local_70 = FUN_00149f60(__ptr,(long)iVar2,lVar3,0);
                free(__ptr);
                FUN_00144de4(lVar3);
                if (local_70 != 0) {
                  FUN_0014ae90(local_70,*(undefined8 *)PTR_stdout_005fff40);
                  FUN_0014ae20(&local_70);
                  uVar6 = 0;
                  goto LAB_00141d28;
                }
                fwrite("aura: func_detect failed\n",1,0x19,*(FILE **)PTR_stderr_005fffd8);
              }
              uVar6 = 0xfffffffe;
            }
            goto LAB_00141d28;
          }
          puVar5 = puVar5 + 7;
        } while (puVar5 != puVar7);
      }
      uVar6 = 0xfffffffa;
      __fprintf_chk(*(undefined8 *)PTR_stderr_005fffd8,2,"aura: .text section not found in \'%s\'\n"
                    ,param_1);
      FUN_00144de4(lVar3);
    }
  }
LAB_00141d28:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                     local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return uVar6;
}

