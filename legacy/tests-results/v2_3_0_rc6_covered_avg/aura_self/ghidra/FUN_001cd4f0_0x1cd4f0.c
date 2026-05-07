
void FUN_001cd4f0(long param_1,undefined8 param_2,undefined8 param_3,int param_4)

{
  byte bVar1;
  char cVar2;
  short sVar3;
  undefined4 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  long lVar7;
  long lVar8;
  
  uVar5 = FUN_0018ffd0();
  if (param_4 == 8) {
    cVar2 = FUN_001900a0();
    FUN_001904e0(param_3,(long)cVar2);
  }
  else if (param_4 == 0x10) {
    sVar3 = FUN_001900a0();
    FUN_001904e0(param_3,(long)sVar3);
  }
  else {
    uVar6 = FUN_001900a0();
    FUN_001904e0(param_3,uVar6);
  }
  lVar8 = *(long *)(param_1 + 800);
  if (*(int *)(lVar8 + 0x60) == 0) {
    return;
  }
  uVar4 = FUN_0018ffb0(param_1);
  bVar1 = *(byte *)(param_1 + 0x366);
  lVar7 = FUN_001dbcf0(lVar8,uVar4);
  lVar8 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
  cVar2 = *(char *)(lVar7 + (ulong)bVar1);
  if (cVar2 == -0x80) {
    cVar2 = '\0';
  }
  lVar8 = lVar8 + (ulong)*(byte *)(lVar8 + 0x67) * 0x38;
  *(char *)(lVar8 + 0x98) = cVar2;
  *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
  *(undefined4 *)(lVar8 + 0x7c) = 2;
  uVar5 = FUN_001900a0(uVar5);
  lVar7 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
  *(undefined8 *)(lVar8 + 0x88) = uVar5;
  *(char *)(lVar7 + 0x67) = *(char *)(lVar7 + 0x67) + '\x01';
  return;
}

