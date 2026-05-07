
void MCInst_insert0(long param_1,uint param_2,undefined8 *param_3)

{
  undefined8 uVar1;
  byte bVar2;
  uint uVar3;
  ulong uVar4;
  long lVar5;
  uint uVar6;
  
  bVar2 = *(byte *)(param_1 + 4);
  uVar6 = bVar2 + 1;
  uVar3 = (uint)bVar2;
  if (uVar3 != param_2 && (int)param_2 <= (int)(uint)bVar2) {
    uVar6 = uVar3 + 1;
    uVar4 = (ulong)((uVar3 - param_2) - 1);
    lVar5 = uVar4 * -0x10;
    memmove((void *)(param_1 + (ulong)uVar6 * 0x10 + lVar5),
            (void *)(param_1 + (ulong)uVar6 * 0x10 + -0x10 + lVar5),(uVar4 + 1) * 0x10);
  }
  lVar5 = param_1 + (long)(int)param_2 * 0x10;
  uVar1 = param_3[1];
  *(undefined8 *)(lVar5 + 0x10) = *param_3;
  *(undefined8 *)(lVar5 + 0x18) = uVar1;
  *(char *)(param_1 + 4) = (char)uVar6;
  return;
}

