
void FUN_0010d454(void)

{
  undefined4 uVar1;
  undefined8 uVar2;
  
  uVar1 = DAT_00140080;
  uVar2 = dcgettext(0,"memory exhausted",5);
  error(uVar1,0,"%s",uVar2);
                    /* WARNING: Subroutine does not return */
  abort();
}

