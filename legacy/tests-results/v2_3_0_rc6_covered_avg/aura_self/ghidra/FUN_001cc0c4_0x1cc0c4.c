
void FUN_001cc0c4(long param_1,undefined8 param_2,undefined8 param_3,char param_4)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  long lVar5;
  long lVar6;
  
  FUN_0018ffd0();
  iVar3 = FUN_00190080();
  lVar6 = *(long *)(param_1 + 800);
  if (*(int *)(lVar6 + 0x60) != 0) {
    uVar4 = FUN_0018ffb0(param_1);
    bVar1 = *(byte *)(param_1 + 0x366);
    lVar6 = FUN_001dbcf0(lVar6,uVar4);
    lVar5 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    cVar2 = *(char *)(lVar6 + (ulong)bVar1);
    bVar1 = *(byte *)(lVar5 + 0x67);
    if (cVar2 == -0x80) {
      cVar2 = '\0';
    }
    lVar6 = lVar5 + ((ulong)bVar1 * 8 - (ulong)bVar1) * 8;
    *(char *)(lVar6 + 0x98) = cVar2;
    *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
    *(undefined4 *)(lVar6 + 0x7c) = 1;
    *(int *)(lVar6 + 0x88) = iVar3;
    *(byte *)(lVar5 + 0x67) = bVar1 + 1;
  }
  FUN_00190370(param_3,&DAT_002b3bf0 + *(ushort *)(&DAT_002b4900 + (ulong)(iVar3 - 1) * 2));
  if (param_4 == '\0') {
    return;
  }
  FUN_001903f0(param_3,&DAT_001ffc30,param_4);
  return;
}

