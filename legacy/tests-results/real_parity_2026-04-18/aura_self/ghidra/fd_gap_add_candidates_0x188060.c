
int fd_gap_add_candidates
              (ulong *param_1,ulong param_2,long *param_3,ulong param_4,ulong param_5,int param_6)

{
  ulong uVar1;
  ulong uVar2;
  int iVar3;
  ulong *puVar4;
  ulong uVar5;
  ulong *puVar6;
  ulong uVar7;
  ulong uVar8;
  ulong *puVar9;
  int local_4;
  
  if ((param_3 != (long *)0x0) && (local_4 = 0, param_1 != (ulong *)0x0 && param_2 != 0)) {
    uVar1 = 0x10;
    if (param_6 - 3U < 5) {
      uVar1 = 4;
    }
    if (param_2 != 1) {
      uVar7 = 1;
      puVar6 = param_1;
      do {
        iVar3 = gap_is_terminator(puVar6);
        puVar9 = puVar6 + 0x1c;
        uVar5 = uVar7;
        if (iVar3 != 0) {
          while( true ) {
            if (param_2 <= uVar5) {
              return local_4;
            }
            iVar3 = strcmp((char *)(puVar9 + 4),"nop");
            if (iVar3 != 0) break;
            puVar9 = puVar9 + 0x1c;
            uVar5 = uVar5 + 1;
          }
          uVar8 = *puVar9;
          uVar2 = 0;
          if (uVar1 != 0) {
            uVar2 = uVar8 / uVar1;
          }
          if ((uVar8 == uVar2 * uVar1) && (param_4 <= uVar8 && uVar8 < param_5)) {
            uVar2 = uVar5 + 4;
            if (param_2 < uVar5 + 4) {
              uVar2 = param_2;
            }
            if (uVar5 + 1 < uVar2) {
              puVar9 = param_1 + (uVar5 + 1) * 0x1c;
              do {
                puVar4 = puVar9 + 0x1c;
                iVar3 = gap_is_terminator(puVar9);
                if (iVar3 != 0) goto joined_r0x001880d8;
                puVar9 = puVar4;
              } while (puVar4 != param_1 + uVar2 * 0x1c);
            }
            if (*(uint *)(param_3 + 1) != 0) {
              puVar4 = (ulong *)*param_3;
              puVar9 = puVar4 + (ulong)*(uint *)(param_3 + 1) * 2;
              do {
                uVar5 = *puVar4;
                puVar4 = puVar4 + 2;
                if (uVar8 == uVar5) goto joined_r0x001880d8;
              } while (puVar4 != puVar9);
            }
            iVar3 = candidateset_add(param_3,uVar8,6,0x1e,0);
            if (iVar3 == 0) {
              return local_4;
            }
            local_4 = local_4 + 1;
          }
        }
joined_r0x001880d8:
        uVar7 = uVar7 + 1;
        puVar6 = puVar6 + 0x1c;
        if (param_2 == uVar7) {
          return local_4;
        }
      } while( true );
    }
  }
  return 0;
}

