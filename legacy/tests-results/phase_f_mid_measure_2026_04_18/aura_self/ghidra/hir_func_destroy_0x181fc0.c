
void hir_func_destroy(undefined8 *param_1)

{
  long lVar1;
  undefined4 *__ptr;
  void *__ptr_00;
  uint uVar2;
  long lVar3;
  
  if (param_1 == (undefined8 *)0x0) {
    return;
  }
  __ptr_00 = (void *)*param_1;
  if (__ptr_00 == (void *)0x0) {
    return;
  }
  __ptr = *(undefined4 **)((long)__ptr_00 + 0xde8);
  if (__ptr != (undefined4 *)0x0) {
    switch(*__ptr) {
    case 0:
      if (__ptr[0x28] != 0) {
        lVar3 = 0;
        do {
          lVar1 = lVar3 * 8;
          lVar3 = lVar3 + 1;
          hir_node_destroy(*(undefined8 *)(*(long *)(__ptr + 0x26) + lVar1));
        } while ((uint)lVar3 < (uint)__ptr[0x28]);
      }
      free(*(void **)(__ptr + 0x26));
      break;
    case 1:
    case 0x15:
      hir_node_destroy(*(undefined8 *)(__ptr + 0x26));
      hir_node_destroy(*(undefined8 *)(__ptr + 0x28));
      hir_node_destroy(*(undefined8 *)(__ptr + 0x2a));
      break;
    case 2:
    case 3:
    case 10:
    case 0xf:
    case 0x14:
      hir_node_destroy(*(undefined8 *)(__ptr + 0x26));
      hir_node_destroy(*(undefined8 *)(__ptr + 0x28));
      break;
    case 4:
      hir_node_destroy(*(undefined8 *)(__ptr + 0x26));
      hir_node_destroy(*(undefined8 *)(__ptr + 0x28));
      hir_node_destroy(*(undefined8 *)(__ptr + 0x2a));
      hir_node_destroy(*(undefined8 *)(__ptr + 0x2c));
      break;
    case 5:
      hir_node_destroy(*(undefined8 *)(__ptr + 0x26));
      if (__ptr[0x2a] != 0) {
        uVar2 = 0;
        lVar3 = 0;
        do {
          uVar2 = uVar2 + 1;
          lVar1 = *(long *)(__ptr + 0x28) + lVar3;
          lVar3 = lVar3 + 0x18;
          hir_node_destroy(*(undefined8 *)(lVar1 + 0x10));
        } while (uVar2 < (uint)__ptr[0x2a]);
      }
      free(*(void **)(__ptr + 0x28));
      break;
    case 0xb:
    case 0x10:
    case 0x12:
    case 0x13:
      hir_node_destroy(*(undefined8 *)(__ptr + 0x26));
      free(__ptr);
      goto LAB_00182024;
    case 0xc:
    case 0x11:
      lVar3 = 0;
      if (__ptr[0x4a] != 0) {
        do {
          lVar1 = lVar3 * 8;
          lVar3 = lVar3 + 1;
          hir_node_destroy(*(undefined8 *)(*(long *)(__ptr + 0x48) + lVar1));
        } while ((uint)lVar3 < (uint)__ptr[0x4a]);
      }
      free(*(void **)(__ptr + 0x48));
    }
    free(__ptr);
  }
LAB_00182024:
  free(*(void **)((long)__ptr_00 + 0xdd8));
  free(__ptr_00);
  *param_1 = 0;
  return;
}

