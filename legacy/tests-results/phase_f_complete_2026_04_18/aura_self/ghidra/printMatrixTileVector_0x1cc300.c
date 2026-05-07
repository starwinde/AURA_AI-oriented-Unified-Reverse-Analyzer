
void printMatrixTileVector(long param_1,undefined8 param_2,undefined8 param_3,char param_4)

{
  char *pcVar1;
  char cVar2;
  byte bVar3;
  int iVar4;
  undefined4 uVar5;
  size_t sVar6;
  long lVar7;
  int iVar8;
  long lVar9;
  char *__s;
  undefined1 uVar10;
  long lVar11;
  
  MCInst_getOperand();
  iVar4 = MCOperand_getReg();
  __s = &AsmStrsNoRegAltName_11 + *(ushort *)(RegAsmOffsetNoRegAltName_12 + (ulong)(iVar4 - 1) * 2);
  sVar6 = strlen(__s);
  lVar7 = (**(code **)PTR_cs_mem_malloc_005ffed0)(sVar6 + 3);
  pcVar1 = __s + sVar6 + 2;
  uVar10 = 0x76;
  if (param_4 == '\0') {
    uVar10 = 0x68;
  }
  iVar8 = 0;
  do {
    while( true ) {
      cVar2 = *__s;
      if (cVar2 != '.') break;
      *(undefined1 *)(lVar7 + iVar8) = uVar10;
      __s = __s + 1;
      *(undefined1 *)(lVar7 + iVar8 + 1) = 0x2e;
      iVar8 = iVar8 + 2;
      if (__s == pcVar1) goto LAB_001cc3d4;
    }
    __s = __s + 1;
    *(char *)(lVar7 + iVar8) = cVar2;
    iVar8 = iVar8 + 1;
  } while (__s != pcVar1);
LAB_001cc3d4:
  SStream_concat0(param_3,lVar7);
  lVar11 = *(long *)(param_1 + 800);
  if (*(int *)(lVar11 + 0x60) != 0) {
    uVar5 = MCInst_getOpcode(param_1);
    bVar3 = *(byte *)(param_1 + 0x366);
    lVar11 = AArch64_get_op_access(lVar11,uVar5);
    lVar9 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    cVar2 = *(char *)(lVar11 + (ulong)bVar3);
    bVar3 = *(byte *)(lVar9 + 0x67);
    if (cVar2 == -0x80) {
      cVar2 = '\0';
    }
    lVar11 = lVar9 + ((ulong)bVar3 * 8 - (ulong)bVar3) * 8;
    *(char *)(lVar11 + 0x98) = cVar2;
    *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
    *(undefined4 *)(lVar11 + 0x7c) = 1;
    *(int *)(lVar11 + 0x88) = iVar4;
    *(byte *)(lVar9 + 0x67) = bVar3 + 1;
  }
  (**(code **)PTR_cs_mem_free_005fff60)(lVar7);
  return;
}

