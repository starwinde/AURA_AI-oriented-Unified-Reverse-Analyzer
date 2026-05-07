
undefined8 getIDWithAttrMask(undefined2 *param_1,long param_2,uint param_3)

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
  pbVar8 = (byte *)(ulong)(byte)(&x86DisassemblerContexts)[(int)(param_3 & 0xffff)];
  bVar2 = *(byte *)(param_2 + 0x81);
  uVar7 = (ulong)bVar2;
  if (uVar1 == 4) {
    if ((pbVar8[0x362630] == 0) ||
       (x86DisassemblerXOP8Opcodes[uVar7 * 4 + (ulong)(pbVar8[0x362630] - 1) * 0x400] == '\0')) {
      if (pbVar8[0x362630] == 0) goto LAB_001dc8d8;
      pbVar8 = x86DisassemblerXOP8Opcodes + (uVar7 + (ulong)(pbVar8[0x362630] - 1) * 0x100) * 4;
      goto LAB_001dc8e0;
    }
LAB_001dc818:
    iVar6 = readModRM(param_2);
    if (iVar6 != 0) {
      return 0xffffffff;
    }
    uVar1 = *(uint *)(param_2 + 0x84);
    uVar7 = (ulong)*(byte *)(param_2 + 0x81);
    bVar2 = *(byte *)(param_2 + 0xa0);
    if (uVar1 == 4) {
      if (pbVar8[0x362630] == 0) goto LAB_001dcc60;
      pbVar8 = x86DisassemblerXOP8Opcodes + (uVar7 + (ulong)(pbVar8[0x362630] - 1) * 0x100) * 4;
    }
    else if (uVar1 < 5) {
      if (uVar1 == 2) {
        if (pbVar8[0x3624b0] == 0) goto LAB_001dcc60;
        pbVar8 = x86DisassemblerThreeByte38Opcodes +
                 (uVar7 + (ulong)(pbVar8[0x3624b0] - 1) * 0x100) * 4;
      }
      else if (uVar1 == 3) {
        if (pbVar8[0x362570] == 0) goto LAB_001dcc60;
        pbVar8 = x86DisassemblerThreeByte3AOpcodes +
                 (uVar7 + (ulong)(pbVar8[0x362570] - 1) * 0x100) * 4;
      }
      else if (uVar1 == 0) {
        if (pbVar8[0x362330] == 0) goto LAB_001dcc60;
        pbVar8 = x86DisassemblerOneByteOpcodes + (uVar7 + (ulong)(pbVar8[0x362330] - 1) * 0x100) * 4
        ;
      }
      else if (pbVar8[0x3623f0] == 0) {
LAB_001dcc60:
        pbVar8 = emptyDecision_0 + (ulong)*(byte *)(param_2 + 0x81) * 4;
      }
      else {
        pbVar8 = x86DisassemblerTwoByteOpcodes + (uVar7 + (ulong)(pbVar8[0x3623f0] - 1) * 0x100) * 4
        ;
      }
    }
    else if (uVar1 == 6) {
      if (pbVar8[0x3627b0] == 0) goto LAB_001dcc60;
      pbVar8 = x86DisassemblerXOPAOpcodes + (uVar7 + (ulong)(pbVar8[0x3627b0] - 1) * 0x100) * 4;
    }
    else if (uVar1 == 7) {
      if (pbVar8[0x362330] == 0) goto LAB_001dcc60;
      pbVar8 = x86Disassembler3DNowOpcodes + (uVar7 + (ulong)(pbVar8[0x362330] - 1) * 0x100) * 4;
    }
    else {
      if (uVar1 != 5) {
LAB_001dca44:
                    /* WARNING: Does not return */
        pcVar4 = (code *)SoftwareBreakpoint(1000,0x1dca50);
        (*pcVar4)();
      }
      if (pbVar8[0x3626f0] == 0) goto LAB_001dcc60;
      pbVar8 = x86DisassemblerXOP9Opcodes + (uVar7 + (ulong)(pbVar8[0x3626f0] - 1) * 0x100) * 4;
    }
    bVar3 = *pbVar8;
    if (bVar3 == 2) {
      if (bVar2 >> 6 == 3) {
        uVar5 = *(undefined2 *)
                 (modRMTable + (long)(int)((bVar2 & 0x3f) + (uint)*(ushort *)(pbVar8 + 2) + 8) * 2);
      }
      else {
        uVar5 = *(undefined2 *)
                 (modRMTable + (long)(int)((bVar2 >> 3 & 7) + (uint)*(ushort *)(pbVar8 + 2)) * 2);
      }
      goto LAB_001dc910;
    }
    if (bVar3 < 3) {
      if (bVar3 == 0) {
        uVar5 = *(undefined2 *)(modRMTable + (ulong)*(ushort *)(pbVar8 + 2) * 2);
        goto LAB_001dc910;
      }
      uVar7 = (ulong)*(ushort *)(pbVar8 + 2);
      if (bVar2 >> 6 == 3) {
        uVar5 = *(undefined2 *)(modRMTable + (long)(int)(*(ushort *)(pbVar8 + 2) + 1) * 2);
        goto LAB_001dc910;
      }
    }
    else {
      if (bVar3 != 3) {
        if (bVar3 == 4) {
          uVar5 = *(undefined2 *)
                   (modRMTable + (long)(int)((uint)*(ushort *)(pbVar8 + 2) + (uint)bVar2) * 2);
          goto LAB_001dc910;
        }
        goto LAB_001dcbd8;
      }
      iVar6 = (bVar2 >> 3 & 7) + (uint)*(ushort *)(pbVar8 + 2);
      if (bVar2 >> 6 == 3) {
        uVar5 = *(undefined2 *)(modRMTable + (long)(iVar6 + 8) * 2);
        goto LAB_001dc910;
      }
      uVar7 = (ulong)iVar6;
    }
    uVar5 = *(undefined2 *)(modRMTable + uVar7 * 2);
  }
  else {
    if (4 < uVar1) {
      if (uVar1 == 6) {
        if ((pbVar8[0x3627b0] == 0) ||
           (x86DisassemblerXOPAOpcodes[(ulong)(pbVar8[0x3627b0] - 1) * 0x400 + (ulong)bVar2 * 4] ==
            '\0')) {
          if (pbVar8[0x3627b0] == 0) goto LAB_001dc8d8;
          pbVar8 = x86DisassemblerXOPAOpcodes + (uVar7 + (ulong)(pbVar8[0x3627b0] - 1) * 0x100) * 4;
          goto LAB_001dc8e0;
        }
      }
      else if (uVar1 != 7) {
        if (uVar1 == 5) {
          if ((pbVar8[0x3626f0] == 0) ||
             (x86DisassemblerXOP9Opcodes[(ulong)(pbVar8[0x3626f0] - 1) * 0x400 + (ulong)bVar2 * 4]
              == '\0')) {
            if (pbVar8[0x3626f0] == 0) goto LAB_001dc8d8;
            pbVar8 = x86DisassemblerXOP9Opcodes +
                     (uVar7 + (ulong)(pbVar8[0x3626f0] - 1) * 0x100) * 4;
            goto LAB_001dc8e0;
          }
        }
        else if ((*pbVar8 == 0) || (*(char *)(uVar7 * 4 + (ulong)(*pbVar8 - 1) * 0x400) == '\0'))
        goto LAB_001dca44;
      }
      goto LAB_001dc818;
    }
    if (uVar1 == 2) {
      if ((pbVar8[0x3624b0] != 0) &&
         (x86DisassemblerThreeByte38Opcodes[uVar7 * 4 + (ulong)(pbVar8[0x3624b0] - 1) * 0x400] !=
          '\0')) goto LAB_001dc818;
      if (pbVar8[0x3624b0] == 0) goto LAB_001dc8d8;
      pbVar8 = x86DisassemblerThreeByte38Opcodes +
               (uVar7 + (ulong)(pbVar8[0x3624b0] - 1) * 0x100) * 4;
    }
    else if (uVar1 == 3) {
      if ((pbVar8[0x362570] != 0) &&
         (x86DisassemblerThreeByte3AOpcodes[uVar7 * 4 + (ulong)(pbVar8[0x362570] - 1) * 0x400] !=
          '\0')) goto LAB_001dc818;
      if (pbVar8[0x362570] == 0) goto LAB_001dc8d8;
      pbVar8 = x86DisassemblerThreeByte3AOpcodes +
               (uVar7 + (ulong)(pbVar8[0x362570] - 1) * 0x100) * 4;
    }
    else if (uVar1 == 0) {
      if ((pbVar8[0x362330] != 0) &&
         (x86DisassemblerOneByteOpcodes[uVar7 * 4 + (ulong)(pbVar8[0x362330] - 1) * 0x400] != '\0'))
      goto LAB_001dc818;
      if (pbVar8[0x362330] == 0) goto LAB_001dc8d8;
      pbVar8 = x86DisassemblerOneByteOpcodes + (uVar7 + (ulong)(pbVar8[0x362330] - 1) * 0x100) * 4;
    }
    else {
      if ((pbVar8[0x3623f0] != 0) &&
         (x86DisassemblerTwoByteOpcodes[uVar7 * 4 + (ulong)(pbVar8[0x3623f0] - 1) * 0x400] != '\0'))
      goto LAB_001dc818;
      if (pbVar8[0x3623f0] == 0) {
LAB_001dc8d8:
        pbVar8 = emptyDecision_0 + (ulong)bVar2 * 4;
      }
      else {
        pbVar8 = x86DisassemblerTwoByteOpcodes + (uVar7 + (ulong)(pbVar8[0x3623f0] - 1) * 0x100) * 4
        ;
      }
    }
LAB_001dc8e0:
    bVar2 = *pbVar8;
    if ((((bVar2 == 2) || (bVar2 < 3)) || (bVar2 == 3)) || (bVar2 == 4)) {
      uVar5 = *(undefined2 *)(modRMTable + (ulong)*(ushort *)(pbVar8 + 2) * 2);
      goto LAB_001dc910;
    }
LAB_001dcbd8:
    uVar5 = 0;
  }
LAB_001dc910:
  *param_1 = uVar5;
  return 0;
}

