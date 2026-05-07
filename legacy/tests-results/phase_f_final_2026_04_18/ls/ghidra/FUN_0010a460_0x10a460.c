
int FUN_0010a460(undefined8 *param_1,undefined8 *param_2)

{
  int iVar1;
  long lVar2;
  long lVar3;
  
  lVar3 = param_1[0x17];
  if (lVar3 == 0) {
    lVar3 = FUN_0010a130(*param_1,DAT_00140f20,*(undefined4 *)((long)param_1 + 0xb4));
  }
  lVar2 = param_2[0x17];
  if (lVar2 == 0) {
    lVar2 = FUN_0010a130(*param_2,DAT_00140f20,*(undefined4 *)((long)param_2 + 0xb4));
  }
  iVar1 = (int)lVar3 - (int)lVar2;
  if (iVar1 == 0) {
    iVar1 = strcmp((char *)*param_1,(char *)*param_2);
    return iVar1;
  }
  return iVar1;
}

