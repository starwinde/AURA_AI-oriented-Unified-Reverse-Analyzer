
void FUN_001901d0(long param_1,long param_2)

{
  byte bVar1;
  int iVar2;
  long lVar3;
  ulong uVar4;
  long lVar5;
  ulong uVar6;
  
  lVar3 = (ulong)*(uint *)(param_1 + 8) * 0x10;
  bVar1 = *(byte *)(param_2 + lVar3);
  lVar3 = *(long *)(param_2 + lVar3 + 8);
  if (bVar1 != 0) {
    uVar6 = 0;
    do {
      while( true ) {
        uVar4 = FUN_00190300(lVar3);
        if (((uVar4 & 1) != 0) &&
           (iVar2 = FUN_00190310(param_2 + (ulong)*(uint *)(param_1 + 8) * 0x10,uVar6 & 0xffffffff,0
                                ), iVar2 != -1)) break;
LAB_00190218:
        uVar6 = uVar6 + 1;
        lVar3 = lVar3 + 8;
        if ((uint)bVar1 <= (uint)uVar6) {
          return;
        }
      }
      *(char *)(param_1 + 0x336 + uVar6) = (char)iVar2;
      lVar5 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      if (lVar5 == 0) goto LAB_00190218;
      uVar6 = uVar6 + 1;
      *(undefined1 *)(lVar5 + 0x5c) = 1;
      lVar3 = lVar3 + 8;
    } while ((uint)uVar6 <= (uint)bVar1 && (uint)bVar1 != (uint)uVar6);
  }
  return;
}

