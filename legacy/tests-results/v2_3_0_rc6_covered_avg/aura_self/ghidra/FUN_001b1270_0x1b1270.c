
void FUN_001b1270(long param_1,undefined4 param_2,undefined8 param_3)

{
  byte bVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  long lVar4;
  char cVar5;
  long lVar6;
  
  FUN_00190370(param_3,&DAT_001f95c0);
  lVar6 = *(long *)(param_1 + 800);
  FUN_0018ffd0(param_1,param_2);
  FUN_00190080();
  uVar3 = (**(code **)(lVar6 + 0x78))();
  FUN_00190370(param_3,uVar3);
  lVar6 = *(long *)(param_1 + 800);
  if (*(int *)(lVar6 + 0x60) != 0) {
    uVar2 = FUN_0018ffb0(param_1);
    bVar1 = *(byte *)(param_1 + 0x366);
    lVar6 = FUN_001bddc0(lVar6,uVar2);
    if (lVar6 == 0) {
      cVar5 = '\0';
    }
    else {
      cVar5 = *(char *)(lVar6 + (ulong)bVar1);
      if (cVar5 == -0x80) {
        cVar5 = '\0';
      }
    }
    lVar6 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    *(undefined4 *)(lVar6 + (ulong)*(byte *)(lVar6 + 0x80) * 0x30 + 0x94) = 1;
    FUN_0018ffd0(param_1,param_2);
    uVar2 = FUN_00190080();
    lVar4 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar4 + 0x80);
    lVar6 = lVar4 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
    *(undefined4 *)(lVar6 + 0x98) = uVar2;
    *(char *)(lVar6 + 0xb1) = cVar5;
    *(byte *)(lVar4 + 0x80) = bVar1 + 1;
    *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
    FUN_00190370(param_3,&DAT_001f96c0);
    return;
  }
  FUN_00190370(param_3,&DAT_001f96c0);
  return;
}

