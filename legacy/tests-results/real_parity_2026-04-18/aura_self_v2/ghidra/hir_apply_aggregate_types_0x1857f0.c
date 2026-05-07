
undefined8 hir_apply_aggregate_types(long param_1,undefined8 param_2,long param_3)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  long lVar5;
  int iVar6;
  long lVar7;
  uint uVar8;
  
  if (param_1 == 0) {
    return 0xfffffffc;
  }
  if (param_3 != 0) {
    if (*(long *)(param_1 + 0xde8) != 0) {
      rewrite_tree(*(long *)(param_1 + 0xde8),param_3);
    }
    lVar7 = 0;
    uVar8 = 0;
    if (*(int *)(param_1 + 0xde0) != 0) {
      do {
        iVar6 = 0;
        iVar3 = *(int *)(*(long *)(param_1 + 0xdd8) + lVar7);
        iVar1 = sr_get_struct_count(param_3);
        if (iVar1 != 0) {
          do {
            iVar4 = sr_get_struct_base_id(param_3,iVar6);
            if (iVar3 == iVar4) {
              lVar5 = sr_get_struct_name(param_3,iVar6);
              if (lVar5 != 0) {
                __snprintf_chk(*(long *)(param_1 + 0xdd8) + lVar7 + 0x44,0x80,2,0x80,&DAT_001fb0b8,
                               lVar5);
                lVar5 = *(long *)(param_1 + 0xdd8) + lVar7;
                *(undefined4 *)(lVar5 + 0xc4) = 8;
                *(undefined1 *)(lVar5 + 200) = 1;
                *(undefined1 *)(lVar5 + 0xca) = 1;
              }
              break;
            }
            iVar6 = iVar6 + 1;
          } while (iVar1 != iVar6);
        }
        uVar8 = uVar8 + 1;
        lVar7 = lVar7 + 0xcc;
      } while (uVar8 < *(uint *)(param_1 + 0xde0));
    }
    uVar2 = *(uint *)(param_1 + 0xdd0);
    lVar7 = param_1 + 0x150;
    uVar8 = 0;
    if (uVar2 != 0) {
      do {
        iVar6 = *(int *)(lVar7 + 0x88);
        if (iVar6 != -1) {
          iVar3 = sr_get_struct_count(param_3);
          if (iVar3 != 0) {
            iVar1 = 0;
            do {
              iVar4 = sr_get_struct_base_id(param_3,iVar1);
              if (iVar6 == iVar4) {
                lVar5 = sr_get_struct_name(param_3,iVar1);
                if (lVar5 != 0) {
                  __snprintf_chk(lVar7,0x80,2,0x80,&DAT_001fb0b8,lVar5);
                  *(undefined4 *)(lVar7 + 0x80) = 8;
                  *(undefined1 *)(lVar7 + 0x84) = 1;
                  *(undefined1 *)(lVar7 + 0x86) = 1;
                }
                break;
              }
              iVar1 = iVar1 + 1;
            } while (iVar3 != iVar1);
          }
          uVar2 = *(uint *)(param_1 + 0xdd0);
        }
        uVar8 = uVar8 + 1;
        lVar7 = lVar7 + 0xcc;
      } while (uVar8 < uVar2);
    }
  }
  return 0;
}

