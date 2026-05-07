
void FUN_001e6d70(long param_1,uint param_2)

{
  ushort *puVar1;
  byte bVar2;
  ushort uVar3;
  ushort *puVar4;
  long lVar5;
  
  lVar5 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
  if (lVar5 != 0) {
    bVar2 = *(byte *)(lVar5 + 0x52);
    puVar4 = (ushort *)(lVar5 + 0x2a);
    puVar1 = puVar4 + bVar2;
    do {
      if (puVar4 == puVar1) {
        *puVar4 = (ushort)param_2;
        *(byte *)(lVar5 + 0x52) = bVar2 + 1;
        return;
      }
      uVar3 = *puVar4;
      puVar4 = puVar4 + 1;
    } while ((uVar3 != param_2) && (puVar4 != (ushort *)(lVar5 + 0x52)));
  }
  return;
}

