
long FUN_00112820(undefined8 param_1,undefined8 param_2,long *param_3,int *param_4,code *param_5)

{
  undefined *puVar1;
  int iVar2;
  long lVar3;
  char *pcVar4;
  undefined8 uVar5;
  _IO_FILE *p_Var6;
  int *piVar7;
  undefined8 uVar8;
  long lVar9;
  
  lVar3 = FUN_001108c4(param_2,param_3,param_4);
  puVar1 = PTR_stderr_0013ffa0;
  if (lVar3 < 0) {
    FUN_0010b310(param_1,param_2,lVar3);
    pcVar4 = (char *)dcgettext(0,"Valid arguments are:",5);
    fputs_unlocked(pcVar4,*(FILE **)puVar1);
    lVar3 = *param_3;
    if (lVar3 != 0) {
      uVar8 = *(undefined8 *)puVar1;
      lVar9 = 0;
      do {
        piVar7 = param_4;
        uVar5 = FUN_00112640(0,lVar3,&DAT_00140088);
        __fprintf_chk(uVar8,2,"\n  - %s",uVar5);
        param_4 = piVar7;
        while( true ) {
          lVar9 = lVar9 + 1;
          param_4 = param_4 + 1;
          lVar3 = param_3[lVar9];
          if (lVar3 == 0) goto LAB_00112960;
          uVar8 = *(undefined8 *)puVar1;
          if (*piVar7 != *param_4) break;
          uVar5 = FUN_00112640(0,lVar3,&DAT_00140088);
          __fprintf_chk(uVar8,2,&DAT_0011cc18,uVar5);
        }
      } while( true );
    }
LAB_00112960:
    p_Var6 = *(_IO_FILE **)puVar1;
    pcVar4 = p_Var6->_IO_write_ptr;
    if (pcVar4 < p_Var6->_IO_write_end) {
      p_Var6->_IO_write_ptr = pcVar4 + 1;
      iVar2 = 10;
      *pcVar4 = '\n';
    }
    else {
      iVar2 = __overflow(p_Var6,10);
    }
    (*param_5)(iVar2);
    lVar3 = -1;
  }
  return lVar3;
}

