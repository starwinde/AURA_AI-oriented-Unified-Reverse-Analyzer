
void FUN_00108b40(undefined8 *param_1,undefined8 *param_2,code *UNRECOVERED_JUMPTABLE)

{
  char *pcVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  
  pcVar3 = strrchr((char *)*param_1,0x2e);
  pcVar4 = strrchr((char *)*param_2,0x2e);
  pcVar1 = "";
  if (pcVar3 != (char *)0x0) {
    pcVar1 = pcVar3;
  }
  pcVar3 = "";
  if (pcVar4 != (char *)0x0) {
    pcVar3 = pcVar4;
  }
  iVar2 = (*UNRECOVERED_JUMPTABLE)(pcVar1,pcVar3);
  if (iVar2 == 0) {
                    /* WARNING: Could not recover jumptable at 0x00108bc0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*UNRECOVERED_JUMPTABLE)(*param_1,*param_2);
    return;
  }
  return;
}

