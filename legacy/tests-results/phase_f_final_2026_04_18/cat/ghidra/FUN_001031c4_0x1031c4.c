
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_001031c4(void)

{
  undefined4 uVar1;
  undefined8 uVar2;
  
  uVar1 = _DAT_00120024;
  uVar2 = dcgettext(0,"memory exhausted",5);
  error(uVar1,0,&DAT_00105230,uVar2);
                    /* WARNING: Subroutine does not return */
  abort();
}

