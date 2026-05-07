
void free_node(uint *param_1)

{
  long lVar1;
  uint uVar2;
  long lVar3;
  
  if (param_1 == (uint *)0x0) {
    return;
  }
  uVar2 = *param_1;
  if (uVar2 == 0x11) {
LAB_00186084:
    lVar3 = 0;
    if (param_1[0x4a] != 0) {
      do {
        lVar1 = lVar3 * 8;
        lVar3 = lVar3 + 1;
        free_node(*(undefined8 *)(*(long *)(param_1 + 0x48) + lVar1));
      } while ((uint)lVar3 < param_1[0x4a]);
    }
    free(*(void **)(param_1 + 0x48));
    free(param_1);
    return;
  }
  if (uVar2 < 0x12) {
    if (uVar2 == 0xf) {
LAB_00186058:
      free_node(*(undefined8 *)(param_1 + 0x26));
      free_node(*(undefined8 *)(param_1 + 0x28));
      free(param_1);
      return;
    }
    if (uVar2 != 0x10) {
      if (uVar2 == 0) {
        if (param_1[0x28] != 0) {
          lVar3 = 0;
          do {
            lVar1 = lVar3 * 8;
            lVar3 = lVar3 + 1;
            free_node(*(undefined8 *)(*(long *)(param_1 + 0x26) + lVar1));
          } while ((uint)lVar3 < param_1[0x28]);
        }
        free(*(void **)(param_1 + 0x26));
        free(param_1);
        return;
      }
      if (uVar2 == 0xc) goto LAB_00186084;
      goto LAB_00186048;
    }
  }
  else if (uVar2 != 0x13) {
    if (uVar2 == 0x14) goto LAB_00186058;
    if (uVar2 != 0x12) goto LAB_00186048;
  }
  free_node(*(undefined8 *)(param_1 + 0x26));
LAB_00186048:
  free(param_1);
  return;
}

