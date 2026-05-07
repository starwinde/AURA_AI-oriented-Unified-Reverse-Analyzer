
void hir_node_destroy(undefined4 *param_1)

{
  long lVar1;
  uint uVar2;
  long lVar3;
  
  if (param_1 != (undefined4 *)0x0) {
    switch(*param_1) {
    case 0:
      if (param_1[0x28] != 0) {
        lVar3 = 0;
        do {
          lVar1 = lVar3 * 8;
          lVar3 = lVar3 + 1;
          hir_node_destroy(*(undefined8 *)(*(long *)(param_1 + 0x26) + lVar1));
        } while ((uint)lVar3 < (uint)param_1[0x28]);
      }
      free(*(void **)(param_1 + 0x26));
      break;
    case 1:
    case 0x15:
      hir_node_destroy(*(undefined8 *)(param_1 + 0x26));
      hir_node_destroy(*(undefined8 *)(param_1 + 0x28));
      hir_node_destroy(*(undefined8 *)(param_1 + 0x2a));
      free(param_1);
      return;
    case 2:
    case 3:
    case 10:
    case 0xf:
    case 0x14:
      hir_node_destroy(*(undefined8 *)(param_1 + 0x26));
      hir_node_destroy(*(undefined8 *)(param_1 + 0x28));
      free(param_1);
      return;
    case 4:
      hir_node_destroy(*(undefined8 *)(param_1 + 0x26));
      hir_node_destroy(*(undefined8 *)(param_1 + 0x28));
      hir_node_destroy(*(undefined8 *)(param_1 + 0x2a));
      hir_node_destroy(*(undefined8 *)(param_1 + 0x2c));
      break;
    case 5:
      hir_node_destroy(*(undefined8 *)(param_1 + 0x26));
      if (param_1[0x2a] != 0) {
        uVar2 = 0;
        lVar3 = 0;
        do {
          uVar2 = uVar2 + 1;
          lVar1 = *(long *)(param_1 + 0x28) + lVar3;
          lVar3 = lVar3 + 0x18;
          hir_node_destroy(*(undefined8 *)(lVar1 + 0x10));
        } while (uVar2 < (uint)param_1[0x2a]);
      }
      free(*(void **)(param_1 + 0x28));
      break;
    case 0xb:
    case 0x10:
    case 0x12:
    case 0x13:
      hir_node_destroy(*(undefined8 *)(param_1 + 0x26));
      free(param_1);
      return;
    case 0xc:
    case 0x11:
      lVar3 = 0;
      if (param_1[0x4a] != 0) {
        do {
          lVar1 = lVar3 * 8;
          lVar3 = lVar3 + 1;
          hir_node_destroy(*(undefined8 *)(*(long *)(param_1 + 0x48) + lVar1));
        } while ((uint)lVar3 < (uint)param_1[0x4a]);
      }
      free(*(void **)(param_1 + 0x48));
    }
    free(param_1);
    return;
  }
  return;
}

