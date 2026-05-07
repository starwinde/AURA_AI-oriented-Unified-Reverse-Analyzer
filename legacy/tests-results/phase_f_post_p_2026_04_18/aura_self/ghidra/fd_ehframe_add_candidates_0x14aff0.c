
int fd_ehframe_add_candidates(long param_1,long param_2,ulong param_3,ulong param_4)

{
  long lVar1;
  int iVar2;
  int iVar3;
  long lVar4;
  ulong uVar5;
  long lVar6;
  ulong uVar7;
  long lVar8;
  ulong uVar9;
  uint uVar10;
  int iVar11;
  
  if (((param_2 == 0 || param_4 <= param_3) || param_1 == 0) ||
     (lVar4 = eh_frame_parse(), lVar4 == 0)) {
    return 0;
  }
  uVar10 = *(uint *)(lVar4 + 0x18);
  uVar9 = (ulong)uVar10;
  if ((*(int *)(param_1 + 0x30) != 0) || (uVar10 < 2)) {
    iVar11 = 0;
    if (uVar10 == 0) {
LAB_0014b1a0:
      eh_frame_info_destroy(lVar4);
      return iVar11;
    }
    lVar6 = *(long *)(lVar4 + 0x10);
LAB_0014b128:
    iVar11 = 0;
    lVar8 = 0;
    iVar2 = 0;
    do {
      uVar5 = *(ulong *)(lVar6 + lVar8 + 0x10);
      if ((uVar5 < param_3 || param_4 <= uVar5) ||
         (uVar7 = *(ulong *)(lVar6 + lVar8 + 0x18), param_4 < uVar5 + uVar7 || uVar7 < 8)) {
LAB_0014b130:
        if ((uint)uVar9 <= iVar2 + 1U) goto LAB_0014b1a0;
      }
      else {
        if (0xffff < uVar7) {
          uVar7 = 0xffff;
        }
        iVar3 = candidateset_add(param_2,uVar5,4,0xfffffff0,uVar7);
        uVar9 = (ulong)*(uint *)(lVar4 + 0x18);
        if (iVar3 == 0) goto LAB_0014b130;
        iVar11 = iVar11 + 1;
        if (*(uint *)(lVar4 + 0x18) <= iVar2 + 1U) goto LAB_0014b1a0;
      }
      iVar2 = iVar2 + 1;
      lVar8 = lVar8 + 0x28;
      lVar6 = *(long *)(lVar4 + 0x10);
    } while( true );
  }
  lVar8 = 0;
  lVar6 = *(long *)(lVar4 + 0x10);
  do {
    lVar1 = lVar6 + lVar8;
    lVar8 = lVar8 + 0x28;
    if (*(long *)(lVar1 + 0x10) != 0) goto LAB_0014b128;
  } while (lVar8 != uVar9 * 0x28);
  uVar10 = 0;
  iVar11 = 0;
  lVar8 = 0;
  do {
    uVar7 = *(ulong *)(lVar6 + lVar8 + 0x18);
    uVar5 = uVar7 + param_3;
    if (7 < uVar7) {
      if (param_4 < uVar5) {
LAB_0014b0f4:
        eh_frame_info_destroy(lVar4);
        return iVar11;
      }
      if (0xffff < uVar7) {
        uVar7 = 0xffff;
      }
      iVar2 = candidateset_add(param_2,param_3,4,0xfffffff0,uVar7);
      uVar9 = (ulong)*(uint *)(lVar4 + 0x18);
      param_3 = uVar5;
      if (iVar2 != 0) {
        iVar11 = iVar11 + 1;
      }
    }
    uVar10 = uVar10 + 1;
    lVar8 = lVar8 + 0x28;
    if ((uint)uVar9 <= uVar10) goto LAB_0014b0f4;
    lVar6 = *(long *)(lVar4 + 0x10);
  } while( true );
}

