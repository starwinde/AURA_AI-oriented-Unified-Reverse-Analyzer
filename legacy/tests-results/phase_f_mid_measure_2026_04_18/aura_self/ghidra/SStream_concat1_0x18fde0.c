
void SStream_concat1(long param_1,undefined1 param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x200) + 1;
  *(undefined1 *)(param_1 + *(int *)(param_1 + 0x200)) = param_2;
  *(int *)(param_1 + 0x200) = iVar1;
  *(undefined1 *)(param_1 + iVar1) = 0;
  return;
}

