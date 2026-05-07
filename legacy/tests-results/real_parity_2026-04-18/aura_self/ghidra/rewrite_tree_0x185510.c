
void rewrite_tree(undefined4 *param_1,undefined8 param_2)

{
  long lVar1;
  long lVar2;
  uint uVar3;
  long lVar4;
  long lVar5;
  
  if (param_1 == (undefined4 *)0x0) {
    return;
  }
  do {
    switch(*param_1) {
    case 0:
      if (param_1[0x28] == 0) {
        return;
      }
      lVar2 = 0;
      do {
        lVar4 = lVar2 * 8;
        lVar2 = lVar2 + 1;
        rewrite_tree(*(undefined8 *)(*(long *)(param_1 + 0x26) + lVar4),param_2);
      } while ((uint)lVar2 < (uint)param_1[0x28]);
      return;
    case 1:
      if (*(long *)(param_1 + 0x26) != 0) {
        rewrite_tree(*(long *)(param_1 + 0x26),param_2);
        lVar2 = try_rewrite_expr(*(undefined8 *)(param_1 + 0x26),param_2);
        if (lVar2 != 0) {
          free_node(*(undefined8 *)(param_1 + 0x26));
          *(long *)(param_1 + 0x26) = lVar2;
        }
      }
      rewrite_tree(*(undefined8 *)(param_1 + 0x28),param_2);
      param_1 = *(undefined4 **)(param_1 + 0x2a);
      break;
    case 2:
    case 3:
      if (*(long *)(param_1 + 0x26) != 0) {
        rewrite_tree(*(long *)(param_1 + 0x26),param_2);
        lVar2 = try_rewrite_expr(*(undefined8 *)(param_1 + 0x26),param_2);
        if (lVar2 != 0) {
          free_node(*(undefined8 *)(param_1 + 0x26));
          *(long *)(param_1 + 0x26) = lVar2;
        }
      }
      param_1 = *(undefined4 **)(param_1 + 0x28);
      break;
    case 4:
      rewrite_tree(*(undefined8 *)(param_1 + 0x26),param_2);
      if (*(long *)(param_1 + 0x28) != 0) {
        rewrite_tree(*(long *)(param_1 + 0x28),param_2);
        lVar2 = try_rewrite_expr(*(undefined8 *)(param_1 + 0x28),param_2);
        if (lVar2 != 0) {
          free_node(*(undefined8 *)(param_1 + 0x28));
          *(long *)(param_1 + 0x28) = lVar2;
        }
      }
      rewrite_tree(*(undefined8 *)(param_1 + 0x2a),param_2);
      param_1 = *(undefined4 **)(param_1 + 0x2c);
      break;
    case 5:
      if (*(long *)(param_1 + 0x26) != 0) {
        rewrite_tree(*(long *)(param_1 + 0x26),param_2);
        lVar2 = try_rewrite_expr(*(undefined8 *)(param_1 + 0x26),param_2);
        if (lVar2 != 0) {
          free_node(*(undefined8 *)(param_1 + 0x26));
          *(long *)(param_1 + 0x26) = lVar2;
        }
      }
      if (param_1[0x2a] == 0) {
        return;
      }
      uVar3 = 0;
      lVar2 = 0;
      do {
        uVar3 = uVar3 + 1;
        lVar4 = *(long *)(param_1 + 0x28) + lVar2;
        lVar2 = lVar2 + 0x18;
        rewrite_tree(*(undefined8 *)(lVar4 + 0x10),param_2);
      } while (uVar3 < (uint)param_1[0x2a]);
      return;
    default:
      goto switchD_0018554c_caseD_6;
    case 10:
    case 0xf:
    case 0x14:
      if (*(long *)(param_1 + 0x26) != 0) {
        rewrite_tree(*(long *)(param_1 + 0x26),param_2);
        lVar2 = try_rewrite_expr(*(undefined8 *)(param_1 + 0x26),param_2);
        if (lVar2 != 0) {
          free_node(*(undefined8 *)(param_1 + 0x26));
          *(long *)(param_1 + 0x26) = lVar2;
        }
      }
      if (*(long *)(param_1 + 0x28) == 0) {
        return;
      }
      rewrite_tree(*(long *)(param_1 + 0x28),param_2);
      lVar2 = try_rewrite_expr(*(undefined8 *)(param_1 + 0x28),param_2);
      if (lVar2 == 0) {
        return;
      }
      free_node(*(undefined8 *)(param_1 + 0x28));
      *(long *)(param_1 + 0x28) = lVar2;
      return;
    case 0xb:
    case 0x10:
    case 0x12:
    case 0x13:
      if (*(long *)(param_1 + 0x26) == 0) {
        return;
      }
      rewrite_tree(*(long *)(param_1 + 0x26),param_2);
      lVar2 = try_rewrite_expr(*(undefined8 *)(param_1 + 0x26),param_2);
      if (lVar2 == 0) {
        return;
      }
      free_node(*(undefined8 *)(param_1 + 0x26));
      *(long *)(param_1 + 0x26) = lVar2;
      return;
    case 0xc:
    case 0x11:
      uVar3 = param_1[0x4a];
      lVar2 = 0;
      if (uVar3 != 0) {
        do {
          lVar5 = lVar2 * 8;
          lVar4 = *(long *)(param_1 + 0x48);
          if ((lVar4 + lVar5 != 0) && (lVar1 = *(long *)(lVar4 + lVar2 * 8), lVar1 != 0)) {
            rewrite_tree(lVar1,param_2);
            lVar1 = try_rewrite_expr(*(undefined8 *)(lVar4 + lVar5),param_2);
            if (lVar1 != 0) {
              free_node(*(undefined8 *)(lVar4 + lVar5));
              *(long *)(lVar4 + lVar5) = lVar1;
            }
            uVar3 = param_1[0x4a];
          }
          lVar2 = lVar2 + 1;
        } while ((uint)lVar2 < uVar3);
      }
      goto switchD_0018554c_caseD_6;
    }
  } while (param_1 != (undefined4 *)0x0);
switchD_0018554c_caseD_6:
  return;
}

