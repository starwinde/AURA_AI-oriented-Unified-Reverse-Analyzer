
void FUN_001b091c(long param_1,undefined8 param_2,undefined8 param_3)

{
  long lVar1;
  byte bVar2;
  undefined8 uVar3;
  int iVar4;
  long lVar5;
  int iVar6;
  
  uVar3 = MCInst_getOperand();
  SStream_concat0(param_3,"[pc, ");
  uVar3 = MCOperand_getImm(uVar3);
  iVar4 = (int)uVar3;
  if (iVar4 == -0x80000000) {
    iVar6 = 0;
    iVar4 = 0;
  }
  else {
    iVar6 = -iVar4;
    if (-1 < iVar4) {
      printUInt32Bang(param_3,uVar3,iVar6);
      goto LAB_001b0984;
    }
  }
  SStream_concat(param_3,"#-0x%x",iVar6);
LAB_001b0984:
  SStream_concat0(param_3,&DAT_001fd038);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar5 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar2 = *(byte *)(lVar5 + 0x80);
    lVar1 = lVar5 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10;
    *(undefined8 *)(lVar1 + 0x94) = DAT_0020b030;
    *(undefined8 *)(lVar1 + 0x9c) = 0x100000000;
    *(int *)(lVar1 + 0xa4) = iVar4;
    *(undefined1 *)(lVar1 + 0xb1) = 1;
    *(byte *)(lVar5 + 0x80) = bVar2 + 1;
  }
  return;
}

