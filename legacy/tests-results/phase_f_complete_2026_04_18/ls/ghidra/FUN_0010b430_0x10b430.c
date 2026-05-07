
ulong FUN_0010b430(long param_1,ulong *param_2)

{
  ulong uVar1;
  byte bVar2;
  ulong uVar3;
  ulong uVar4;
  ulong uVar5;
  
  uVar5 = *param_2;
  uVar4 = 0;
  uVar3 = 0;
  do {
    if ((long)uVar5 < 0) {
      do {
        uVar1 = uVar4 + 2;
        if (*(char *)(param_1 + uVar4) == '\0') {
LAB_0010b538:
          *param_2 = uVar4;
          return uVar3;
        }
        uVar3 = uVar4 + 1;
        uVar4 = uVar3;
      } while (uVar5 <= uVar1);
    }
    else {
      do {
        uVar1 = uVar4 + 2;
        if (uVar5 == uVar4) goto LAB_0010b538;
        uVar3 = uVar4 + 1;
        uVar4 = uVar3;
      } while (uVar5 <= uVar1);
    }
    do {
      if (*(char *)(param_1 + uVar4) != '.') break;
      bVar2 = *(byte *)(param_1 + uVar4 + 1);
      if (bVar2 < 0x5b) {
        if (bVar2 < 0x41) break;
      }
      else if ((0x19 < (byte)(bVar2 + 0x9f)) && (bVar2 != 0x7e)) break;
      for (uVar4 = uVar4 + 2; uVar4 < uVar5; uVar4 = uVar4 + 1) {
        bVar2 = *(byte *)(param_1 + uVar4);
        if (bVar2 < 0x5b) {
          if ((bVar2 < 0x41) && (9 < (byte)(bVar2 - 0x30))) break;
        }
        else if ((0x19 < (byte)(bVar2 + 0x9f)) && (bVar2 != 0x7e)) break;
      }
    } while (uVar4 + 1 < uVar5);
  } while( true );
}

