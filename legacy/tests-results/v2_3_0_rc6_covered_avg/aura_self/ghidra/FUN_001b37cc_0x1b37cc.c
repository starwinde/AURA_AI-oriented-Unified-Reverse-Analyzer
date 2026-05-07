
void FUN_001b37cc(long param_1,undefined8 param_2,undefined8 param_3)

{
  long lVar1;
  undefined4 uVar2;
  byte bVar3;
  code *pcVar4;
  undefined1 uVar5;
  uint uVar6;
  long lVar7;
  
  FUN_0018ffd0();
  uVar5 = FUN_001900a0();
  uVar6 = FUN_00190910(&DAT_00244640,0x21,uVar5);
  if (uVar6 != 0xffffffff) {
    uVar6 = *(uint *)(&DAT_00244644 + (ulong)uVar6 * 8);
    FUN_00190370(param_3,(&PTR_s_r8_usr_005ed480)[(ulong)uVar6 * 2]);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      uVar2 = *(undefined4 *)(&DAT_005ed488 + (ulong)uVar6 * 0x10);
      lVar7 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar3 = *(byte *)(lVar7 + 0x80);
      lVar1 = lVar7 + ((ulong)bVar3 * 2 + (ulong)bVar3) * 0x10;
      *(undefined4 *)(lVar1 + 0x94) = 0x43;
      *(undefined4 *)(lVar1 + 0x98) = uVar2;
      *(byte *)(lVar7 + 0x80) = bVar3 + 1;
    }
    return;
  }
                    /* WARNING: Does not return */
  pcVar4 = (code *)SoftwareBreakpoint(1000,0x1b388c);
  (*pcVar4)();
}

