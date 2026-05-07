
void collect_locals_walk(undefined4 *param_1,long param_2,long *param_3)

{
  int iVar1;
  int *piVar2;
  size_t __size;
  long lVar3;
  int *piVar4;
  long *plVar5;
  long *plVar6;
  void *__ptr;
  uint uVar7;
  uint uVar8;
  undefined4 uVar9;
  long lVar10;
  undefined8 local_120;
  undefined8 uStack_118;
  undefined8 uStack_110;
  undefined8 uStack_108;
  undefined8 local_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined8 uStack_e8;
  undefined8 local_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 local_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 local_a0;
  undefined1 auStack_88 [64];
  long local_48;
  
  local_48 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (param_1 != (undefined4 *)0x0) {
    do {
      switch(*param_1) {
      case 0:
        if (param_1[0x28] != 0) {
          lVar10 = 0;
          do {
            lVar3 = lVar10 * 8;
            lVar10 = lVar10 + 1;
            collect_locals_walk(*(undefined8 *)(*(long *)(param_1 + 0x26) + lVar3),param_2,param_3);
          } while ((uint)lVar10 < (uint)param_1[0x28]);
        }
        goto switchD_0017d43c_caseD_6;
      case 1:
      case 0x15:
        collect_locals_walk(*(undefined8 *)(param_1 + 0x26),param_2,param_3);
        collect_locals_walk(*(undefined8 *)(param_1 + 0x28),param_2,param_3);
        param_1 = *(undefined4 **)(param_1 + 0x2a);
        break;
      case 2:
      case 3:
      case 10:
      case 0xf:
      case 0x14:
        collect_locals_walk(*(undefined8 *)(param_1 + 0x26),param_2,param_3);
        param_1 = *(undefined4 **)(param_1 + 0x28);
        break;
      case 4:
        collect_locals_walk(*(undefined8 *)(param_1 + 0x26),param_2,param_3);
        collect_locals_walk(*(undefined8 *)(param_1 + 0x28),param_2,param_3);
        collect_locals_walk(*(undefined8 *)(param_1 + 0x2a),param_2,param_3);
        param_1 = *(undefined4 **)(param_1 + 0x2c);
        break;
      case 5:
        collect_locals_walk(*(undefined8 *)(param_1 + 0x26),param_2,param_3);
        if (param_1[0x2a] != 0) {
          uVar8 = 0;
          lVar10 = 0;
          do {
            uVar8 = uVar8 + 1;
            lVar3 = *(long *)(param_1 + 0x28) + lVar10;
            lVar10 = lVar10 + 0x18;
            collect_locals_walk(*(undefined8 *)(lVar3 + 0x10),param_2,param_3);
          } while (uVar8 < (uint)param_1[0x2a]);
          goto LAB_0017d460;
        }
      default:
        goto switchD_0017d43c_caseD_6;
      case 0xb:
      case 0x10:
      case 0x12:
      case 0x13:
        param_1 = *(undefined4 **)(param_1 + 0x26);
        break;
      case 0xc:
      case 0x11:
        lVar10 = 0;
        if (param_1[0x4a] != 0) {
          do {
            lVar3 = lVar10 * 8;
            lVar10 = lVar10 + 1;
            collect_locals_walk(*(undefined8 *)(*(long *)(param_1 + 0x48) + lVar3),param_2,param_3);
          } while ((uint)lVar10 < (uint)param_1[0x4a]);
        }
        goto switchD_0017d43c_caseD_6;
      case 0xd:
        iVar1 = param_1[0x26];
        if (iVar1 != -1) {
          if (*(uint *)(param_3 + 1) != 0) {
            plVar5 = (long *)(*param_3 + 8);
            plVar6 = plVar5 + (ulong)*(uint *)(param_3 + 1) * 10;
            do {
              if (*(uint *)(plVar5 + 1) != 0) {
                lVar10 = *plVar5;
                lVar3 = lVar10 + (ulong)*(uint *)(plVar5 + 1) * 0x88;
                do {
                  if (iVar1 == *(int *)(lVar10 + 8)) {
                    uVar9 = *(undefined4 *)(lVar10 + 0xc);
                    goto LAB_0017d61c;
                  }
                  lVar10 = lVar10 + 0x88;
                } while (lVar3 != lVar10);
              }
              plVar5 = plVar5 + 10;
            } while (plVar6 != plVar5);
          }
          uVar9 = 4;
LAB_0017d61c:
          uVar8 = *(uint *)(param_2 + 0xde0);
          if (uVar8 == 0) {
LAB_0017d664:
            if (*(int *)(param_2 + 0xdd0) != 0) {
              uVar8 = 0;
              do {
                __snprintf_chk(auStack_88,0x40,2,0x40,&DAT_001fc380,uVar8);
                uVar8 = uVar8 + 1;
              } while (uVar8 < *(uint *)(param_2 + 0xdd0));
              uVar8 = *(uint *)(param_2 + 0xde0);
            }
            uVar7 = *(uint *)(param_2 + 0xde4);
            __ptr = *(void **)(param_2 + 0xdd8);
            if (uVar7 <= uVar8) {
              if (uVar7 == 0) {
                __size = 0xcc0;
                uVar7 = 0x10;
              }
              else {
                uVar7 = uVar7 << 1;
                __size = (ulong)uVar7 * 0xcc;
              }
              __ptr = realloc(__ptr,__size);
              if (__ptr == (void *)0x0) goto switchD_0017d43c_caseD_6;
              uVar8 = *(uint *)(param_2 + 0xde0);
              *(void **)(param_2 + 0xdd8) = __ptr;
              *(uint *)(param_2 + 0xde4) = uVar7;
            }
            *(uint *)(param_2 + 0xde0) = uVar8 + 1;
            lVar10 = (ulong)uVar8 * 0xcc;
            *(int *)((long)__ptr + lVar10) = iVar1;
            __snprintf_chk((long)__ptr + lVar10 + 4,0x40,2,0x40,&DAT_001f9928,iVar1);
            ir_type_to_hir(uVar9);
            *(undefined8 *)((long)__ptr + lVar10 + 0x4c) = uStack_118;
            *(undefined8 *)((long)__ptr + lVar10 + 0x44) = local_120;
            *(undefined8 *)((long)__ptr + lVar10 + 0x5c) = uStack_108;
            *(undefined8 *)((long)__ptr + lVar10 + 0x54) = uStack_110;
            *(undefined8 *)((long)__ptr + lVar10 + 0x6c) = uStack_f8;
            *(undefined8 *)((long)__ptr + lVar10 + 100) = local_100;
            *(undefined8 *)((long)__ptr + lVar10 + 0x7c) = uStack_e8;
            *(undefined8 *)((long)__ptr + lVar10 + 0x74) = uStack_f0;
            *(undefined8 *)((long)__ptr + lVar10 + 0x8c) = uStack_d8;
            *(undefined8 *)((long)__ptr + lVar10 + 0x84) = local_e0;
            *(undefined8 *)((long)__ptr + lVar10 + 0x9c) = uStack_c8;
            *(undefined8 *)((long)__ptr + lVar10 + 0x94) = uStack_d0;
            *(undefined8 *)((long)__ptr + lVar10 + 0xac) = uStack_b8;
            *(undefined8 *)((long)__ptr + lVar10 + 0xa4) = local_c0;
            *(undefined8 *)((long)__ptr + lVar10 + 0xbc) = uStack_a8;
            *(undefined8 *)((long)__ptr + lVar10 + 0xb4) = uStack_b0;
            *(undefined8 *)((long)__ptr + lVar10 + 0xc4) = local_a0;
            goto LAB_0017d460;
          }
          piVar2 = *(int **)(param_2 + 0xdd8);
          piVar4 = piVar2 + (ulong)uVar8 * 0x33;
          while (iVar1 != *piVar2) {
            piVar2 = piVar2 + 0x33;
            if (piVar4 == piVar2) goto LAB_0017d664;
          }
        }
        goto switchD_0017d43c_caseD_6;
      }
    } while (param_1 != (undefined4 *)0x0);
switchD_0017d43c_caseD_6:
  }
LAB_0017d460:
  if (local_48 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                   local_48 - *(long *)PTR___stack_chk_guard_005ffe88);
}

