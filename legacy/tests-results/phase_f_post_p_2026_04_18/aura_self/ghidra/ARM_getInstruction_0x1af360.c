
undefined8
ARM_getInstruction(long param_1,uint *param_2,ulong param_3,long param_4,undefined2 *param_5)

{
  undefined4 *puVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  void *__s;
  undefined4 *puVar5;
  long lVar6;
  
  *param_5 = 0;
  if (param_3 < 4) {
    return 0;
  }
  __s = *(void **)(*(long *)(param_4 + 0x310) + 0xf0);
  if (__s != (void *)0x0) {
    memset(__s,0,0x748);
    lVar6 = *(long *)(*(long *)(param_4 + 0x310) + 0xf0);
    puVar5 = (undefined4 *)(lVar6 + 0x88);
    do {
      puVar1 = puVar5 + 0xc;
      *puVar5 = 0xffffffff;
      *(undefined1 *)((long)puVar5 + 0x2a) = 0xff;
      puVar5 = puVar1;
    } while (puVar1 != (undefined4 *)(lVar6 + 0x748));
  }
  uVar2 = *param_2;
  uVar3 = (uVar2 & 0xff00ff00) >> 8 | (uVar2 & 0xff00ff) << 8;
  uVar3 = uVar3 >> 0x10 | uVar3 << 0x10;
  if (-1 < *(int *)(param_1 + 4)) {
    uVar3 = uVar2;
  }
  iVar4 = decodeInstruction_4_isra_0(DecoderTableARM32,param_4,uVar3);
  if (iVar4 == 0) {
    MCInst_clear(param_4);
    iVar4 = decodeInstruction_4_isra_0(DecoderTableVFP32,param_4,uVar3);
    if (iVar4 != 0) goto LAB_001af440;
    MCInst_clear(param_4);
    iVar4 = decodeInstruction_4_isra_0(DecoderTableVFPV832,param_4,uVar3);
    if (iVar4 != 0) goto LAB_001af440;
    MCInst_clear(param_4);
    iVar4 = decodeInstruction_4_isra_0(DecoderTableNEONData32,param_4,uVar3);
    if (iVar4 != 0) {
LAB_001af558:
      *param_5 = 4;
      iVar4 = MCInst_getOpcode(param_4);
      if (iVar4 != 0xc4f) {
        MCOperand_CreateImm0(param_4,0xe);
        MCOperand_CreateReg0(param_4,0);
        return 1;
      }
      return 0;
    }
    MCInst_clear(param_4);
    iVar4 = decodeInstruction_4_isra_0(DecoderTableNEONLoadStore32,param_4,uVar3);
    if (iVar4 != 0) goto LAB_001af558;
    MCInst_clear(param_4);
    iVar4 = decodeInstruction_4_isra_0(DecoderTableNEONDup32,param_4,uVar3);
    if (iVar4 != 0) goto LAB_001af558;
    MCInst_clear(param_4);
    iVar4 = decodeInstruction_4_isra_0(DecoderTablev8NEON32,param_4,uVar3);
    if (iVar4 != 0) goto LAB_001af440;
    MCInst_clear(param_4);
    iVar4 = decodeInstruction_4_isra_0(DecoderTablev8Crypto32,param_4,uVar3);
    if (iVar4 != 0) goto LAB_001af440;
    iVar4 = decodeInstruction_4_isra_0(DecoderTableCoProc32,param_4,uVar3);
    if (iVar4 == 0) {
      MCInst_clear(param_4);
      *param_5 = 0;
      return 0;
    }
  }
  iVar4 = MCInst_getOpcode(param_4);
  if ((iVar4 == 0x25c) && (uVar3 >> 0x1c == 0xf)) {
    return 0;
  }
LAB_001af440:
  *param_5 = 4;
  return 1;
}

