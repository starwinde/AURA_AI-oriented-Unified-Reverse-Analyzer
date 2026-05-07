
undefined4 FUN_00143f00(long param_1)

{
  int iVar1;
  long lVar2;
  long lVar3;
  undefined8 uVar4;
  char *__ptr;
  size_t __n;
  ulong uVar5;
  undefined8 *puVar6;
  undefined4 uVar7;
  undefined8 *puVar8;
  ulong uVar9;
  ulong uVar10;
  long lVar11;
  long local_60;
  long local_58;
  
  local_58 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (param_1 == 0) {
    uVar7 = 0xfffffffc;
  }
  else {
    lVar2 = FUN_00140cb0(param_1,PTR___stack_chk_guard_005ffe88,0);
    if (lVar2 == 0) {
      __fprintf_chk(*(undefined8 *)PTR_stderr_005fffd8,2,"aura: failed to parse \'%s\'\n",param_1);
LAB_00144134:
      uVar7 = 0xfffffff9;
    }
    else {
      puVar6 = *(undefined8 **)(lVar2 + 0x18);
      if (*(uint *)(lVar2 + 0x20) != 0) {
        puVar8 = puVar6 + (ulong)*(uint *)(lVar2 + 0x20) * 7;
        do {
          if (((char *)*puVar6 != (char *)0x0) &&
             (iVar1 = strcmp((char *)*puVar6,".text"), iVar1 == 0)) {
            lVar11 = puVar6[5];
            if (lVar11 == 0) {
              __fprintf_chk(*(undefined8 *)PTR_stderr_005fffd8,2,
                            "aura: cannot map .text data from \'%s\'\n",param_1);
              FUN_00144de4(lVar2);
              goto LAB_00144134;
            }
            lVar3 = FUN_001446e0(*(undefined4 *)(lVar2 + 0xc));
            if (lVar3 == 0) {
              __n = 0x1f;
              __ptr = "aura: disassembler init failed\n";
            }
            else {
              uVar5 = puVar6[1];
              uVar9 = *(ulong *)(lVar2 + 0x10);
              uVar10 = uVar5;
              if ((uVar5 <= uVar9) && (uVar10 = uVar9, uVar5 + puVar6[3] <= uVar9)) {
                uVar10 = uVar5;
              }
              local_60 = FUN_00171d40(lVar3,lVar11,puVar6[3],uVar5,uVar10);
              FUN_001447a4(lVar3);
              if (local_60 != 0) {
                puts("=== Full Recursive Descent Disassembly ===");
                uVar4 = FUN_00144f60(*(undefined4 *)(lVar2 + 0xc));
                __printf_chk(2,"  File: %s  Arch: %s\n",param_1,uVar4);
                __printf_chk(2,"  .text: 0x%lx .. 0x%lx (%lu bytes)\n",puVar6[1],
                             puVar6[1] + puVar6[3]);
                __printf_chk(2,"  Entry: 0x%lx\n\n",uVar10);
                FUN_00171f60(local_60,*(undefined8 *)PTR_stdout_005fff40);
                puts("\n--- Benchmark ---");
                __printf_chk(2,"  Recursive: %u functions, %u instructions\n",
                             *(undefined4 *)(local_60 + 8),*(undefined4 *)(local_60 + 0xc));
                FUN_00171ed0(&local_60);
                FUN_00144de4(lVar2);
                uVar7 = 0;
                goto LAB_00143fc0;
              }
              __ptr = "aura: recursive disassembly failed\n";
              __n = 0x23;
            }
            uVar7 = 0xfffffff8;
            fwrite(__ptr,1,__n,*(FILE **)PTR_stderr_005fffd8);
            FUN_00144de4(lVar2);
            goto LAB_00143fc0;
          }
          puVar6 = puVar6 + 7;
        } while (puVar6 != puVar8);
      }
      uVar7 = 0xfffffffa;
      __fprintf_chk(*(undefined8 *)PTR_stderr_005fffd8,2,"aura: .text section not found in \'%s\'\n"
                    ,param_1);
      FUN_00144de4(lVar2);
    }
  }
LAB_00143fc0:
  if (local_58 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                     local_58 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return uVar7;
}

