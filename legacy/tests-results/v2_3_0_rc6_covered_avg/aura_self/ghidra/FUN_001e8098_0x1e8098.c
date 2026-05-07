
ushort FUN_001e8098(long param_1,long param_2,byte param_3)

{
  byte bVar1;
  undefined1 uVar2;
  ushort uVar3;
  
  if (*(char *)(param_1 + 0x28) == '\0') {
    uVar2 = FUN_001e7e6c(param_1,param_2,param_3,0);
    *(undefined1 *)(param_1 + 0x28) = uVar2;
    if (*(char *)(param_1 + 0x28) == '\0') {
      uVar3 = 0;
    }
    else {
      uVar3 = *(ushort *)(param_2 + (ulong)(*(byte *)(param_1 + 0x28) >> 5) * 2) & 0xff;
    }
  }
  else {
    bVar1 = *(byte *)(param_1 + 0x28) >> 5;
    if (*(ushort *)(param_2 + (ulong)bVar1 * 2) < (ushort)param_3) {
      uVar3 = 0;
    }
    else {
      uVar3 = *(ushort *)(param_2 + (ulong)bVar1 * 2) & 0xff;
    }
  }
  return uVar3;
}

