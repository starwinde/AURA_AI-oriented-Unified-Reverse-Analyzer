
void FUN_001b3890(long param_1,undefined8 param_2,undefined8 param_3)

{
  byte bVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long lVar5;
  
  uVar3 = FUN_0018ffd0();
  FUN_00190370(param_3,&DAT_001fdf80);
  FUN_001b3500(param_1,1);
  lVar5 = *(long *)(param_1 + 800);
  FUN_00190080(uVar3);
  uVar4 = (**(code **)(lVar5 + 0x78))();
  FUN_00190370(param_3,uVar4);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar5 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar5 + 0x80);
    uVar2 = FUN_00190080(uVar3);
    *(undefined4 *)(lVar5 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x98) = uVar2;
  }
  FUN_00190370(param_3,&DAT_001fe598);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 3) {
    lVar5 = *(long *)(param_1 + 0x310);
    *(undefined1 *)(*(long *)(param_1 + 800) + 0x6c) = 0;
    lVar5 = *(long *)(lVar5 + 0xf0);
    *(char *)(lVar5 + 0x80) = *(char *)(lVar5 + 0x80) + '\x01';
  }
  return;
}

