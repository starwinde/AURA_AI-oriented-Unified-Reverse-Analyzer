
undefined8 FUN_001deec4(undefined2 *param_1,long param_2,uint param_3)

{
  uint uVar1;
  byte bVar2;
  byte bVar3;
  code *pcVar4;
  undefined2 uVar5;
  int iVar6;
  ulong uVar7;
  byte *pbVar8;
  
  uVar1 = *(uint *)(param_2 + 0x84);
  pbVar8 = (byte *)(ulong)(byte)(&DAT_003d98b0)[(int)(param_3 & 0xffff)];
  bVar2 = *(byte *)(param_2 + 0x81);
  uVar7 = (ulong)bVar2;
  if (uVar1 == 4) {
    if ((pbVar8[0x364e30] == 0) ||
       ((&DAT_00374490)[uVar7 * 4 + (ulong)(pbVar8[0x364e30] - 1) * 0x400] == '\0')) {
      if (pbVar8[0x364e30] == 0) goto LAB_001df008;
      pbVar8 = &DAT_00374490 + (uVar7 + (ulong)(pbVar8[0x364e30] - 1) * 0x100) * 4;
      goto LAB_001df010;
    }
LAB_001def48:
    iVar6 = FUN_001dea60(param_2);
    if (iVar6 != 0) {
      return 0xffffffff;
    }
    uVar1 = *(uint *)(param_2 + 0x84);
    uVar7 = (ulong)*(byte *)(param_2 + 0x81);
    bVar2 = *(byte *)(param_2 + 0xa0);
    if (uVar1 == 4) {
      if (pbVar8[0x364e30] == 0) goto LAB_001df390;
      pbVar8 = &DAT_00374490 + (uVar7 + (ulong)(pbVar8[0x364e30] - 1) * 0x100) * 4;
    }
    else if (uVar1 < 5) {
      if (uVar1 == 2) {
        if (pbVar8[0x364cb0] == 0) goto LAB_001df390;
        pbVar8 = &DAT_00384890 + (uVar7 + (ulong)(pbVar8[0x364cb0] - 1) * 0x100) * 4;
      }
      else if (uVar1 == 3) {
        if (pbVar8[0x364d70] == 0) goto LAB_001df390;
        pbVar8 = &DAT_00375490 + (uVar7 + (ulong)(pbVar8[0x364d70] - 1) * 0x100) * 4;
      }
      else if (uVar1 == 0) {
        if (pbVar8[0x364b30] == 0) goto LAB_001df390;
        pbVar8 = &DAT_003cb090 + (uVar7 + (ulong)(pbVar8[0x364b30] - 1) * 0x100) * 4;
      }
      else if (pbVar8[0x364bf0] == 0) {
LAB_001df390:
        pbVar8 = &DAT_00365070 + (ulong)*(byte *)(param_2 + 0x81) * 4;
      }
      else {
        pbVar8 = &DAT_0039d890 + (uVar7 + (ulong)(pbVar8[0x364bf0] - 1) * 0x100) * 4;
      }
    }
    else if (uVar1 == 6) {
      if (pbVar8[0x364fb0] == 0) goto LAB_001df390;
      pbVar8 = &DAT_00366070 + (uVar7 + (ulong)(pbVar8[0x364fb0] - 1) * 0x100) * 4;
    }
    else if (uVar1 == 7) {
      if (pbVar8[0x364b30] == 0) goto LAB_001df390;
      pbVar8 = &DAT_0036f890 + (uVar7 + (ulong)(pbVar8[0x364b30] - 1) * 0x100) * 4;
    }
    else {
      if (uVar1 != 5) {
LAB_001df174:
                    /* WARNING: Does not return */
        pcVar4 = (code *)SoftwareBreakpoint(1000,0x1df180);
        (*pcVar4)();
      }
      if (pbVar8[0x364ef0] == 0) goto LAB_001df390;
      pbVar8 = &DAT_00365470 + (uVar7 + (ulong)(pbVar8[0x364ef0] - 1) * 0x100) * 4;
    }
    bVar3 = *pbVar8;
    if (bVar3 == 2) {
      if (bVar2 >> 6 == 3) {
        uVar5 = *(undefined2 *)
                 (&DAT_003cfc90 +
                 (long)(int)((bVar2 & 0x3f) + (uint)*(ushort *)(pbVar8 + 2) + 8) * 2);
      }
      else {
        uVar5 = *(undefined2 *)
                 (&DAT_003cfc90 + (long)(int)((bVar2 >> 3 & 7) + (uint)*(ushort *)(pbVar8 + 2)) * 2)
        ;
      }
      goto LAB_001df040;
    }
    if (bVar3 < 3) {
      if (bVar3 == 0) {
        uVar5 = *(undefined2 *)(&DAT_003cfc90 + (ulong)*(ushort *)(pbVar8 + 2) * 2);
        goto LAB_001df040;
      }
      uVar7 = (ulong)*(ushort *)(pbVar8 + 2);
      if (bVar2 >> 6 == 3) {
        uVar5 = *(undefined2 *)(&DAT_003cfc90 + (long)(int)(*(ushort *)(pbVar8 + 2) + 1) * 2);
        goto LAB_001df040;
      }
    }
    else {
      if (bVar3 != 3) {
        if (bVar3 == 4) {
          uVar5 = *(undefined2 *)
                   (&DAT_003cfc90 + (long)(int)((uint)*(ushort *)(pbVar8 + 2) + (uint)bVar2) * 2);
          goto LAB_001df040;
        }
        goto LAB_001df308;
      }
      iVar6 = (bVar2 >> 3 & 7) + (uint)*(ushort *)(pbVar8 + 2);
      if (bVar2 >> 6 == 3) {
        uVar5 = *(undefined2 *)(&DAT_003cfc90 + (long)(iVar6 + 8) * 2);
        goto LAB_001df040;
      }
      uVar7 = (ulong)iVar6;
    }
    uVar5 = *(undefined2 *)(&DAT_003cfc90 + uVar7 * 2);
  }
  else {
    if (4 < uVar1) {
      if (uVar1 == 6) {
        if ((pbVar8[0x364fb0] == 0) ||
           ((&DAT_00366070)[(ulong)(pbVar8[0x364fb0] - 1) * 0x400 + (ulong)bVar2 * 4] == '\0')) {
          if (pbVar8[0x364fb0] == 0) goto LAB_001df008;
          pbVar8 = &DAT_00366070 + (uVar7 + (ulong)(pbVar8[0x364fb0] - 1) * 0x100) * 4;
          goto LAB_001df010;
        }
      }
      else if (uVar1 != 7) {
        if (uVar1 == 5) {
          if ((pbVar8[0x364ef0] == 0) ||
             ((&DAT_00365470)[(ulong)(pbVar8[0x364ef0] - 1) * 0x400 + (ulong)bVar2 * 4] == '\0')) {
            if (pbVar8[0x364ef0] == 0) goto LAB_001df008;
            pbVar8 = &DAT_00365470 + (uVar7 + (ulong)(pbVar8[0x364ef0] - 1) * 0x100) * 4;
            goto LAB_001df010;
          }
        }
        else if ((*pbVar8 == 0) || (*(char *)(uVar7 * 4 + (ulong)(*pbVar8 - 1) * 0x400) == '\0'))
        goto LAB_001df174;
      }
      goto LAB_001def48;
    }
    if (uVar1 == 2) {
      if ((pbVar8[0x364cb0] != 0) &&
         ((&DAT_00384890)[uVar7 * 4 + (ulong)(pbVar8[0x364cb0] - 1) * 0x400] != '\0'))
      goto LAB_001def48;
      if (pbVar8[0x364cb0] == 0) goto LAB_001df008;
      pbVar8 = &DAT_00384890 + (uVar7 + (ulong)(pbVar8[0x364cb0] - 1) * 0x100) * 4;
    }
    else if (uVar1 == 3) {
      if ((pbVar8[0x364d70] != 0) &&
         ((&DAT_00375490)[uVar7 * 4 + (ulong)(pbVar8[0x364d70] - 1) * 0x400] != '\0'))
      goto LAB_001def48;
      if (pbVar8[0x364d70] == 0) goto LAB_001df008;
      pbVar8 = &DAT_00375490 + (uVar7 + (ulong)(pbVar8[0x364d70] - 1) * 0x100) * 4;
    }
    else if (uVar1 == 0) {
      if ((pbVar8[0x364b30] != 0) &&
         ((&DAT_003cb090)[uVar7 * 4 + (ulong)(pbVar8[0x364b30] - 1) * 0x400] != '\0'))
      goto LAB_001def48;
      if (pbVar8[0x364b30] == 0) goto LAB_001df008;
      pbVar8 = &DAT_003cb090 + (uVar7 + (ulong)(pbVar8[0x364b30] - 1) * 0x100) * 4;
    }
    else {
      if ((pbVar8[0x364bf0] != 0) &&
         ((&DAT_0039d890)[uVar7 * 4 + (ulong)(pbVar8[0x364bf0] - 1) * 0x400] != '\0'))
      goto LAB_001def48;
      if (pbVar8[0x364bf0] == 0) {
LAB_001df008:
        pbVar8 = &DAT_00365070 + (ulong)bVar2 * 4;
      }
      else {
        pbVar8 = &DAT_0039d890 + (uVar7 + (ulong)(pbVar8[0x364bf0] - 1) * 0x100) * 4;
      }
    }
LAB_001df010:
    bVar2 = *pbVar8;
    if ((((bVar2 == 2) || (bVar2 < 3)) || (bVar2 == 3)) || (bVar2 == 4)) {
      uVar5 = *(undefined2 *)(&DAT_003cfc90 + (ulong)*(ushort *)(pbVar8 + 2) * 2);
      goto LAB_001df040;
    }
LAB_001df308:
    uVar5 = 0;
  }
LAB_001df040:
  *param_1 = uVar5;
  return 0;
}

