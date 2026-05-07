
void FUN_001cd140(long param_1,ulong param_2)

{
  byte bVar1;
  char cVar2;
  undefined4 uVar3;
  long lVar4;
  
  lVar4 = *(long *)(param_1 + 800);
  if ((param_2 & 1) == 0) {
    if ((*(byte *)(lVar4 + 0x6d) & 1) != 0) {
      *(undefined1 *)(lVar4 + 0x6d) = 0;
      return;
    }
    *(undefined1 *)(lVar4 + 0x6c) = 0;
    if (*(int *)(lVar4 + 0x60) == 3) {
      lVar4 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(char *)(lVar4 + 0x67) = *(char *)(lVar4 + 0x67) + '\x01';
      return;
    }
  }
  else {
    *(undefined1 *)(lVar4 + 0x6c) = 1;
    if (*(int *)(lVar4 + 0x60) == 3) {
      uVar3 = FUN_0018ffb0();
      bVar1 = *(byte *)(param_1 + 0x366);
      lVar4 = FUN_001dbcf0(lVar4,uVar3);
      cVar2 = *(char *)(lVar4 + (ulong)bVar1);
      lVar4 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      if (cVar2 == -0x80) {
        cVar2 = '\0';
      }
      lVar4 = lVar4 + (ulong)*(byte *)(lVar4 + 0x67) * 0x38;
      *(char *)(lVar4 + 0x98) = cVar2;
      *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
      *(undefined4 *)(lVar4 + 0x7c) = 3;
      *(undefined8 *)(lVar4 + 0x88) = 0;
      *(undefined4 *)(lVar4 + 0x90) = 0;
    }
  }
  return;
}

