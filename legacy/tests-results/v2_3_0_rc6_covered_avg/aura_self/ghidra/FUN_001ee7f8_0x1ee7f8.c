
int FUN_001ee7f8(ulong *param_1,undefined8 param_2)

{
  byte bVar1;
  int iVar2;
  
  bVar1 = FUN_001ee5e8(param_1);
  if (((bVar1 & 0x70) == 0) && ((*param_1 & 0x400000000000) == 0)) {
    if ((((bVar1 & 0xf) == 0) && ((*param_1 & 4) == 0)) ||
       (iVar2 = FUN_001ee2b4(bVar1 & 0xf | 0x40,param_2), -1 < iVar2)) {
      iVar2 = 0x100000;
    }
  }
  else {
    *(undefined4 *)((long)param_1 + 0xc) = 0;
    iVar2 = FUN_001ee2b4(0xffffffd5,param_2);
    if ((-1 < iVar2) && (iVar2 = FUN_001ee2b4(bVar1,param_2), -1 < iVar2)) {
      iVar2 = 0x100000;
    }
  }
  return iVar2;
}

