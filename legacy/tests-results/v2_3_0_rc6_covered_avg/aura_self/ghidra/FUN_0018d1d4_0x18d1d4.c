
void FUN_0018d1d4(long param_1,long param_2)

{
  long lVar1;
  undefined8 *puVar2;
  
  if (param_2 != 0) {
    lVar1 = 0;
    puVar2 = (undefined8 *)(param_1 + 0xf0);
    do {
      lVar1 = lVar1 + 1;
      (*(code *)PTR_free_00600588)(*puVar2);
      puVar2 = puVar2 + 0x1f;
    } while (param_2 != lVar1);
  }
  (*(code *)PTR_free_00600588)(param_1);
  return;
}

