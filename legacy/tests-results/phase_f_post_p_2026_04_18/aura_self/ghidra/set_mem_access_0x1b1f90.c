
void set_mem_access(long param_1,byte param_2)

{
  byte bVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined4 uVar4;
  char cVar5;
  long lVar6;
  long lVar7;
  
  lVar7 = *(long *)(param_1 + 800);
  if (*(int *)(lVar7 + 0x60) == 3) {
    *(byte *)(lVar7 + 0x6c) = param_2;
    uVar3 = DAT_0020b020;
    uVar2 = DAT_0020b018;
    if ((param_2 & 1) != 0) {
      lVar6 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      lVar6 = lVar6 + (ulong)*(byte *)(lVar6 + 0x80) * 0x30;
      *(undefined4 *)(lVar6 + 0x9c) = 0;
      *(undefined8 *)(lVar6 + 0x94) = uVar3;
      *(undefined8 *)(lVar6 + 0xa0) = uVar2;
      uVar4 = MCInst_getOpcode();
      bVar1 = *(byte *)(param_1 + 0x366);
      lVar7 = ARM_get_op_access(lVar7,uVar4);
      if (lVar7 == 0) {
        cVar5 = '\0';
      }
      else {
        cVar5 = *(char *)(lVar7 + (ulong)bVar1);
        if (cVar5 == -0x80) {
          cVar5 = '\0';
        }
      }
      lVar7 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(char *)(lVar7 + (ulong)*(byte *)(lVar7 + 0x80) * 0x30 + 0xb1) = cVar5;
      *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
      return;
    }
    lVar7 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    *(char *)(lVar7 + 0x80) = *(char *)(lVar7 + 0x80) + '\x01';
  }
  return;
}

