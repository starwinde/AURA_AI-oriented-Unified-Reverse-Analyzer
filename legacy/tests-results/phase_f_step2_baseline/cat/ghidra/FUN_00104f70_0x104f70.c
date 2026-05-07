
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00104f70(void)

{
  int iVar1;
  undefined8 uVar2;
  int *piVar3;
  
  iVar1 = FUN_00103320(*(undefined8 *)PTR_stdout_0011ffd0);
  if (iVar1 != 0) {
    uVar2 = dcgettext(0,"write error",5);
    piVar3 = __errno_location();
    error(0,*piVar3,&DAT_00105230,uVar2);
                    /* WARNING: Subroutine does not return */
    _exit(_DAT_00120024);
  }
  iVar1 = FUN_00103320(*(undefined8 *)PTR_stderr_0011ffc0);
  if (iVar1 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  _exit(_DAT_00120024);
}

