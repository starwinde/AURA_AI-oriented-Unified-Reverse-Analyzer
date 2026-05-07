
void FUN_001087c0(void)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  uVar2 = *(undefined8 *)PTR_stderr_0013ffa0;
  uVar1 = dcgettext(0,"memory exhausted",5);
  __fprintf_chk(uVar2,2,"%s\n",uVar1);
                    /* WARNING: Subroutine does not return */
  exit(DAT_00140080);
}

