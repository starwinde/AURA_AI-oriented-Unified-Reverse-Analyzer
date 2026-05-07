
void FUN_0018d23c(long param_1,char *param_2)

{
  int iVar1;
  size_t sVar2;
  
  sVar2 = strlen(param_2);
  memcpy((void *)(param_1 + *(int *)(param_1 + 0x200)),param_2,sVar2 & 0xffffffff);
  iVar1 = *(int *)(param_1 + 0x200) + (int)sVar2;
  *(int *)(param_1 + 0x200) = iVar1;
  *(undefined1 *)(param_1 + iVar1) = 0;
  return;
}

