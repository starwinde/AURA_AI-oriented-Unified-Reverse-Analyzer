
void FUN_001f7530(void)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)(*(code *)PTR_malloc_00600598)(0x40);
  if (puVar1 != (undefined8 *)0x0) {
    puVar1[1] = 0;
    *puVar1 = 0;
    puVar1[3] = 0;
    puVar1[2] = 0;
    *(undefined4 *)(puVar1 + 3) = 1;
    puVar1[5] = 0;
    puVar1[4] = 0;
    puVar1[7] = 0;
    puVar1[6] = 0;
  }
  return;
}

