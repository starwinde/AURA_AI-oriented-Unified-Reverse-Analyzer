
void ARM_addUserMode(long param_1)

{
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    *(undefined1 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x60) = 1;
  }
  return;
}

