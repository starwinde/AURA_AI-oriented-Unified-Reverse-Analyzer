
void FUN_001b37a0(long param_1)

{
  long lVar1;
  
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 3) {
    lVar1 = *(long *)(param_1 + 0x310);
    *(undefined1 *)(*(long *)(param_1 + 800) + 0x6c) = 0;
    lVar1 = *(long *)(lVar1 + 0xf0);
    *(char *)(lVar1 + 0x80) = *(char *)(lVar1 + 0x80) + '\x01';
  }
  return;
}

