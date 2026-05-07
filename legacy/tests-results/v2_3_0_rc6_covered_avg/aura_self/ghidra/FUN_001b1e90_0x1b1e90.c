
void FUN_001b1e90(long param_1,undefined8 param_2,undefined8 param_3)

{
  long lVar1;
  byte bVar2;
  undefined8 uVar3;
  int iVar4;
  long lVar5;
  int iVar6;
  
  uVar3 = FUN_0018ffd0();
  FUN_00190370(param_3,"[pc, ");
  uVar3 = FUN_001900a0(uVar3);
  iVar4 = (int)uVar3;
  if (iVar4 == -0x80000000) {
    iVar6 = 0;
    iVar4 = 0;
  }
  else {
    iVar6 = -iVar4;
    if (-1 < iVar4) {
      FUN_001906d0(param_3,uVar3,iVar6);
      goto LAB_001b1ef4;
    }
  }
  FUN_001903f0(param_3,"#-0x%x",iVar6);
LAB_001b1ef4:
  FUN_00190370(param_3,&DAT_001fe598);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar5 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar2 = *(byte *)(lVar5 + 0x80);
    lVar1 = lVar5 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10;
    *(undefined8 *)(lVar1 + 0x94) = DAT_0020c590;
    *(undefined8 *)(lVar1 + 0x9c) = 0x100000000;
    *(int *)(lVar1 + 0xa4) = iVar4;
    *(undefined1 *)(lVar1 + 0xb1) = 1;
    *(byte *)(lVar5 + 0x80) = bVar2 + 1;
  }
  return;
}

