
void FUN_001e12b0(long param_1,undefined8 param_2,undefined8 param_3)

{
  int iVar1;
  undefined8 uVar2;
  ulong uVar3;
  
  uVar2 = FUN_0018ffd0();
  uVar3 = FUN_00190020();
  if ((uVar3 & 1) != 0) {
    iVar1 = FUN_00190080(uVar2);
    FUN_00190370(param_3,&UNK_003e7d80 + *(ushort *)(&DAT_003e8250 + (ulong)(iVar1 - 1) * 2));
    return;
  }
  uVar3 = FUN_00190030(uVar2);
  if ((uVar3 & 1) == 0) {
    return;
  }
  uVar2 = FUN_001900a0(uVar2);
  FUN_001e1080(*(undefined1 *)(param_1 + 6),*(long *)(param_1 + 800),param_3,uVar2,
               *(int *)(*(long *)(param_1 + 800) + 100) != 0);
  return;
}

