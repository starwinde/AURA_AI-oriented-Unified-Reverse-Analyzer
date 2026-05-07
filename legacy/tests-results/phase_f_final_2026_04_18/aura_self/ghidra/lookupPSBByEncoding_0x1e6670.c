
undefined1 * lookupPSBByEncoding(undefined4 param_1)

{
  undefined1 *puVar1;
  int iVar2;
  
  iVar2 = binsearch_IndexTypeEncoding(&Index_9,1,param_1);
  puVar1 = PSBsList;
  if (iVar2 == -1) {
    puVar1 = (undefined1 *)0x0;
  }
  return puVar1;
}

