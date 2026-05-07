
void cs_disasm_iter(int *param_1,long *param_2,ulong *param_3,long *param_4,int *param_5)

{
  byte bVar1;
  int iVar2;
  undefined8 uVar3;
  ulong uVar4;
  void *pvVar5;
  long lVar6;
  ulong uVar7;
  code *pcVar8;
  size_t __n;
  long lVar9;
  undefined1 *puVar10;
  undefined1 *puVar11;
  ushort local_632;
  undefined1 auStack_630 [520];
  undefined1 auStack_428 [8];
  undefined4 local_420;
  undefined8 local_240;
  int *local_118;
  long local_110;
  int *local_108;
  byte local_c1;
  long local_68;
  
  local_240 = 0;
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (param_1 != (int *)0x0) {
    param_1[0x14] = 0;
    MCInst_Init(auStack_428);
    local_110 = *param_4;
    lVar6 = *param_2;
    pcVar8 = *(code **)(param_1 + 6);
    uVar3 = *(undefined8 *)(param_1 + 8);
    *(long *)(param_5 + 2) = local_110;
    local_118 = param_5;
    local_108 = param_1;
    uVar4 = (*pcVar8)(param_1,lVar6,*param_3,auStack_428,&local_632,*param_4,uVar3);
    if ((uVar4 & 1) != 0) {
      SStream_Init(auStack_630);
      pcVar8 = *(code **)(param_1 + 0x10);
      *(ushort *)(local_118 + 4) = local_632;
      (*pcVar8)(param_1,param_5,local_420);
      (**(code **)(param_1 + 2))(auStack_428,auStack_630,*(undefined8 *)(param_1 + 4));
      fill_insn(param_1,param_5,auStack_630,auStack_428,*(undefined8 *)(param_1 + 0x12),*param_2);
      if (*param_1 == 3) {
        *param_5 = *param_5 + (uint)local_c1;
      }
      uVar4 = *param_3;
      uVar7 = (ulong)local_632;
      *param_2 = *param_2 + uVar7;
      *param_3 = uVar4 - uVar7;
      *param_4 = *param_4 + uVar7;
LAB_0018c45c:
      uVar3 = 1;
      goto LAB_0018c1b0;
    }
    if ((*(byte *)(param_1 + 0x20) & 1) != 0) {
      bVar1 = *(byte *)((long)param_1 + 0x81);
      __n = (size_t)bVar1;
      if ((ulong)bVar1 <= *param_3) {
        pvVar5 = (void *)*param_2;
        if (*(code **)(param_1 + 0x24) == (code *)0x0) {
          lVar6 = *param_4;
          *param_5 = 0;
          *(long *)(param_5 + 2) = lVar6;
          *(ushort *)(param_5 + 4) = (ushort)bVar1;
          memcpy((void *)((long)param_5 + 0x12),pvVar5,__n);
          strncpy((char *)((long)param_5 + 0x2a),*(char **)(param_1 + 0x22),0x1f);
          puVar11 = (undefined1 *)*param_2;
          if (__n != 0) goto LAB_0018c2dc;
          *(undefined1 *)((long)param_5 + 0x4a) = 0;
        }
        else {
          __n = (**(code **)(param_1 + 0x24))(pvVar5,*param_3,0,*(undefined8 *)(param_1 + 0x26));
          if (*param_3 <= __n - 1) goto LAB_0018c1ac;
          pvVar5 = (void *)*param_2;
          lVar6 = *param_4;
          *param_5 = 0;
          *(long *)(param_5 + 2) = lVar6;
          *(short *)(param_5 + 4) = (short)__n;
          memcpy((void *)((long)param_5 + 0x12),pvVar5,__n);
          strncpy((char *)((long)param_5 + 0x2a),*(char **)(param_1 + 0x22),0x1f);
          puVar11 = (undefined1 *)*param_2;
LAB_0018c2dc:
          iVar2 = cs_snprintf((long)param_5 + 0x4a,0xa0,"0x%02x",*puVar11);
          lVar6 = (long)param_5 + 0x4a + (long)iVar2;
          lVar9 = 0xa0 - (long)iVar2;
          if (__n != 1) {
            puVar10 = puVar11 + 1;
            do {
              iVar2 = cs_snprintf(lVar6,lVar9,", 0x%02x",*puVar10);
              if ((iVar2 < 0) || (uVar4 = (ulong)iVar2, lVar9 - 1U < uVar4)) break;
              puVar10 = puVar10 + 1;
              lVar6 = lVar6 + uVar4;
              lVar9 = lVar9 - uVar4;
            } while (puVar11 + __n != puVar10);
          }
        }
        uVar4 = *param_3;
        *param_2 = *param_2 + __n;
        *param_3 = uVar4 - __n;
        *param_4 = *param_4 + __n;
        goto LAB_0018c45c;
      }
    }
  }
LAB_0018c1ac:
  uVar3 = 0;
LAB_0018c1b0:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(uVar3,PTR___stack_chk_guard_005ffe88,0,
                     local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return;
}

