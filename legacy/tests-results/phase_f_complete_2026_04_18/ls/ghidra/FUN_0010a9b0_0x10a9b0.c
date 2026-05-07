
void FUN_0010a9b0(void)

{
  int iVar1;
  undefined8 uVar2;
  int *piVar3;
  
  iVar1 = FUN_0010a940(*(undefined8 *)PTR_stdout_0013ffc0);
  if (iVar1 != 0) {
    uVar2 = dcgettext(0,"write error",5);
    piVar3 = __errno_location();
    error(0,*piVar3,"%s",uVar2);
                    /* WARNING: Subroutine does not return */
    _exit(DAT_00140080);
  }
  iVar1 = FUN_0010a940(*(undefined8 *)PTR_stderr_0013ffa0);
  if (iVar1 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  _exit(DAT_00140080);
}

