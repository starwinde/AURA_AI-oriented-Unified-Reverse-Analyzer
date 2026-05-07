
bool FUN_0018b6d0(long param_1)

{
  char *__s1;
  bool bVar1;
  int iVar2;
  
  __s1 = (char *)(param_1 + 0x20);
  bVar1 = true;
  iVar2 = strcmp(__s1,"ret");
  if (iVar2 != 0) {
    bVar1 = true;
    iVar2 = strcmp(__s1,"retn");
    if ((((iVar2 != 0) && (iVar2 = strcmp(__s1,"retf"), iVar2 != 0)) &&
        (iVar2 = strcmp(__s1,"hlt"), iVar2 != 0)) &&
       ((iVar2 = strcmp(__s1,"ud2"), iVar2 != 0 && (iVar2 = strcmp(__s1,"int3"), iVar2 != 0)))) {
      iVar2 = strcmp(__s1,"jmp");
      bVar1 = iVar2 == 0;
    }
  }
  return bVar1;
}

