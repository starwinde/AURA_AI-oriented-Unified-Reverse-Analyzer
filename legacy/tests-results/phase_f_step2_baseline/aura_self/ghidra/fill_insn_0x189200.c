
void fill_insn(long param_1,int *param_2,char *param_3,undefined8 param_4,code *param_5,long param_6
              )

{
  ushort uVar1;
  ushort uVar2;
  int iVar3;
  char *pcVar4;
  size_t sVar5;
  size_t sVar6;
  size_t sVar7;
  char *pcVar8;
  char *pcVar9;
  char cVar10;
  int *piVar11;
  char acStack_78 [32];
  long local_58;
  
  uVar2 = *(ushort *)(param_2 + 4);
  uVar1 = uVar2;
  if (0x18 < uVar2) {
    uVar1 = 0x18;
  }
  local_58 = *(long *)PTR___stack_chk_guard_005ffe88;
  memcpy((void *)((long)param_2 + 0x12),(void *)(param_6 + ((ulong)uVar2 - (ulong)uVar1)),
         (ulong)uVar1);
  *(ushort *)(param_2 + 4) = uVar1;
  *(undefined1 *)((long)param_2 + 0x4a) = 0;
  iVar3 = MCInst_getOpcodePub(param_4);
  if (iVar3 != 0) {
    iVar3 = MCInst_getOpcodePub(param_4);
    *param_2 = iVar3;
  }
  if (param_5 != (code *)0x0) {
    (*param_5)(param_1,param_2,param_3,param_4);
  }
  pcVar8 = (char *)((long)param_2 + 0x2a);
  cVar10 = *param_3;
  pcVar4 = pcVar8;
  while (pcVar9 = pcVar4, cVar10 != '\0') {
    while( true ) {
      pcVar9 = pcVar4;
      if (cVar10 == ' ' || cVar10 == '\t') goto LAB_001892cc;
      if (cVar10 == '|') break;
      pcVar9 = pcVar4 + 1;
      *pcVar4 = *param_3;
      param_3 = param_3 + 1;
      cVar10 = *param_3;
      pcVar4 = pcVar9;
      if (cVar10 == '\0') goto LAB_001892cc;
    }
    *param_3 = ' ';
    *pcVar4 = ' ';
    param_3 = param_3 + 1;
    pcVar4 = pcVar4 + 1;
    cVar10 = *param_3;
  }
LAB_001892cc:
  *pcVar9 = '\0';
  piVar11 = *(int **)(param_1 + 0xb0);
  if (piVar11 != (int *)0x0) {
    do {
      if (*piVar11 == *param_2) {
        if (*(code **)(param_1 + 0x30) == (code *)0x0) {
          pcVar4 = (char *)0x0;
        }
        else {
          pcVar4 = (char *)(**(code **)(param_1 + 0x30))(param_1);
        }
        sVar5 = strlen(pcVar8);
        sVar6 = strlen(pcVar4);
        sVar7 = strlen((char *)(piVar11 + 1));
        if ((sVar5 + sVar7) - sVar6 < 0x1f) {
          __memcpy_chk(acStack_78,piVar11 + 1,sVar7,0x20);
          __strcpy_chk(acStack_78 + sVar7,pcVar8 + sVar6,0x20 - sVar7);
          strncpy(pcVar8,acStack_78,0x1f);
          *(undefined1 *)((long)param_2 + 0x49) = 0;
        }
        break;
      }
      piVar11 = *(int **)(piVar11 + 10);
    } while (piVar11 != (int *)0x0);
  }
  if (*param_3 == '\0') {
    *(undefined1 *)((long)param_2 + 0x4a) = 0;
  }
  else {
    pcVar8 = param_3 + 1;
    if (param_3[1] == ' ' || param_3[1] == '\t') {
      do {
        pcVar8 = pcVar8 + 1;
      } while (*pcVar8 == ' ' || *pcVar8 == '\t');
    }
    strncpy((char *)((long)param_2 + 0x4a),pcVar8,0x9f);
    *(undefined1 *)((long)param_2 + 0xe9) = 0;
  }
  if (local_58 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                   local_58 - *(long *)PTR___stack_chk_guard_005ffe88);
}

