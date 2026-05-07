
long FUN_0018d244(long param_1)

{
  long lVar1;
  long lVar2;
  
  lVar1 = (*(code *)PTR_malloc_00600570)(0xf8);
  if (lVar1 == 0) {
LAB_0018d2b4:
    *(undefined4 *)(param_1 + 0x50) = 1;
    return 0;
  }
  if (*(int *)(param_1 + 0x60) == 0) {
    *(undefined8 *)(lVar1 + 0xf0) = 0;
  }
  else {
    lVar2 = (*(code *)PTR_malloc_00600570)(0x748);
    *(long *)(lVar1 + 0xf0) = lVar2;
    if (lVar2 == 0) {
      (*(code *)PTR_free_00600588)(lVar1);
      goto LAB_0018d2b4;
    }
  }
  return lVar1;
}

