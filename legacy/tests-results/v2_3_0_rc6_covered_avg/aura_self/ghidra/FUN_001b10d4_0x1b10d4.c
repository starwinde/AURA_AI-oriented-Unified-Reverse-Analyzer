
void FUN_001b10d4(long param_1,int param_2,undefined8 param_3)

{
  byte bVar1;
  int iVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  long lVar5;
  int iVar6;
  long lVar7;
  char cVar8;
  
  FUN_00190370(param_3,&DAT_001f95c0);
  lVar7 = *(long *)(param_1 + 800);
  if (*(int *)(lVar7 + 0x60) != 0) {
    uVar3 = FUN_0018ffb0(param_1);
    bVar1 = *(byte *)(param_1 + 0x366);
    lVar7 = FUN_001bddc0(lVar7,uVar3);
    if ((lVar7 != 0) && (cVar8 = *(char *)(lVar7 + (ulong)bVar1), cVar8 != -0x80))
    goto LAB_001b1118;
  }
  cVar8 = '\0';
LAB_001b1118:
  iVar2 = FUN_0018ffe0(param_1);
  iVar6 = param_2;
  if (param_2 != iVar2) {
    while( true ) {
      lVar7 = *(long *)(param_1 + 800);
      FUN_0018ffd0(param_1,iVar6);
      FUN_00190080();
      uVar4 = (**(code **)(lVar7 + 0x78))();
      FUN_00190370(param_3,uVar4);
      if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
        lVar7 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        *(undefined4 *)(lVar7 + (ulong)*(byte *)(lVar7 + 0x80) * 0x30 + 0x94) = 1;
        FUN_0018ffd0(param_1,iVar6);
        uVar3 = FUN_00190080();
        lVar5 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        bVar1 = *(byte *)(lVar5 + 0x80);
        lVar7 = lVar5 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
        *(undefined4 *)(lVar7 + 0x98) = uVar3;
        *(char *)(lVar7 + 0xb1) = cVar8;
        *(byte *)(lVar5 + 0x80) = bVar1 + 1;
      }
      if (iVar2 == iVar6 + 1) break;
      iVar6 = iVar6 + 1;
      if (param_2 != iVar6) {
        FUN_00190370(param_3,", ");
      }
    }
  }
  FUN_00190370(param_3,&DAT_001f96c0);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
  }
  return;
}

