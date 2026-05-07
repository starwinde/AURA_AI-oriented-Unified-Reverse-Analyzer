
void emit_phi_assigns_part_0_constprop_0_isra_0
               (long param_1,ulong param_2,int param_3,FILE *param_4)

{
  long lVar1;
  uint uVar2;
  ulong uVar3;
  long lVar4;
  int iVar5;
  
  param_1 = param_1 + (param_2 & 0xffffffff) * 0x50;
  uVar2 = *(uint *)(param_1 + 0x10);
  if (uVar2 != 0) {
    lVar4 = 0;
    do {
      while ((lVar1 = *(long *)(param_1 + 8) + lVar4 * 0x88,
             *(int *)(*(long *)(param_1 + 8) + lVar4 * 0x88) == 0x1b &&
             (*(uint *)(lVar1 + 0x60) != 0))) {
        uVar3 = 0;
        while (*(int *)(*(long *)(lVar1 + 0x58) + uVar3 * 4) != param_3) {
          uVar3 = uVar3 + 1;
          if (uVar3 == *(uint *)(lVar1 + 0x60)) goto LAB_0015a450;
        }
        iVar5 = 8;
        do {
          fputc(0x20,param_4);
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
        if (*(int *)(lVar1 + 8) == -1) {
          fwrite("__undef",1,7,param_4);
        }
        else {
          __fprintf_chk(param_4,2,&DAT_001f8f08);
        }
        fwrite(&DAT_001f8f10,1,3,param_4);
        if (*(int *)(*(long *)(lVar1 + 0x50) + uVar3 * 0x10) == -1) {
          fwrite("__undef",1,7,param_4);
        }
        else {
          __fprintf_chk(param_4,2,&DAT_001f8f08);
        }
        fwrite("; /* phi */\n",1,0xc,param_4);
        lVar4 = lVar4 + 1;
        uVar2 = *(uint *)(param_1 + 0x10);
        if (uVar2 <= (uint)lVar4) {
          return;
        }
      }
LAB_0015a450:
      lVar4 = lVar4 + 1;
    } while ((uint)lVar4 < uVar2);
  }
  return;
}

