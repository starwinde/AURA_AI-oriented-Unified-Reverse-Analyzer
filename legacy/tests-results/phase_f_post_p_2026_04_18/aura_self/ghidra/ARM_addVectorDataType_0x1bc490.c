
void ARM_addVectorDataType(long param_1,undefined4 param_2)

{
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = param_2;
  }
  return;
}

