
void FUN_0014bcc0(long *param_1)

{
  long *plVar1;
  long *plVar2;
  long lVar3;
  long *plVar4;
  int iVar5;
  ulong uVar6;
  long lVar7;
  ulong uVar8;
  
  if (param_1 == (long *)0x0) {
    return;
  }
  if (1 < *(uint *)(param_1 + 1)) {
    qsort((void *)*param_1,(ulong)*(uint *)(param_1 + 1),0x10,FUN_0014bbc0);
    if (*(uint *)(param_1 + 1) < 2) {
      *(undefined4 *)(param_1 + 1) = 1;
    }
    else {
      lVar7 = *param_1;
      uVar6 = 0;
      uVar8 = 0;
      plVar1 = (long *)(lVar7 + 0x20 + (ulong)(*(uint *)(param_1 + 1) - 2) * 0x10);
      plVar4 = (long *)(lVar7 + 0x10);
LAB_0014bd44:
      do {
        iVar5 = (int)uVar6;
        lVar3 = lVar7 + uVar8 * 0x10;
        if (*plVar4 == *(long *)(lVar7 + uVar8 * 0x10)) {
          if (*(byte *)(lVar3 + 9) < *(byte *)((long)plVar4 + 9)) {
            *(byte *)(lVar3 + 9) = *(byte *)((long)plVar4 + 9);
            plVar2 = plVar4 + 2;
            *(char *)(lVar3 + 8) = (char)plVar4[1];
            *(undefined2 *)(lVar3 + 10) = *(undefined2 *)((long)plVar4 + 10);
            plVar4 = plVar2;
            if (plVar2 == plVar1) break;
            goto LAB_0014bd44;
          }
        }
        else {
          uVar6 = (ulong)(iVar5 + 1);
          lVar3 = plVar4[1];
          plVar2 = (long *)(lVar7 + uVar6 * 0x10);
          *plVar2 = *plVar4;
          plVar2[1] = lVar3;
          uVar8 = uVar6;
        }
        iVar5 = (int)uVar6;
        plVar4 = plVar4 + 2;
      } while (plVar4 != plVar1);
      *(int *)(param_1 + 1) = iVar5 + 1;
    }
  }
  return;
}

