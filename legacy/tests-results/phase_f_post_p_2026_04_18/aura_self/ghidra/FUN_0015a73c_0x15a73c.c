
void FUN_0015a73c(long param_1,ulong param_2,int param_3,FILE *param_4,int param_5)

{
  long lVar1;
  uint uVar2;
  ulong uVar3;
  uint uVar4;
  long lVar5;
  int iVar6;
  
  param_1 = param_1 + (param_2 & 0xffffffff) * 0x50;
  uVar2 = *(uint *)(param_1 + 0x10);
  if (uVar2 != 0) {
    uVar4 = 0;
    lVar5 = 0;
    do {
      while ((lVar1 = *(long *)(param_1 + 8) + lVar5,
             *(int *)(*(long *)(param_1 + 8) + lVar5) == 0x1b && (*(uint *)(lVar1 + 0x60) != 0))) {
        uVar3 = 0;
        while (*(int *)(*(long *)(lVar1 + 0x58) + uVar3 * 4) != param_3) {
          uVar3 = uVar3 + 1;
          if (*(uint *)(lVar1 + 0x60) == uVar3) goto LAB_0015a79c;
        }
        iVar6 = 0;
        if (0 < param_5) {
          do {
            iVar6 = iVar6 + 1;
            fputc(0x20,param_4);
          } while (iVar6 < param_5 * 4);
        }
        if (*(int *)(lVar1 + 8) == -1) {
          fwrite("__undef",1,7,param_4);
        }
        else {
          __fprintf_chk(param_4,2,&DAT_001f9570);
        }
        fwrite(&DAT_001f9578,1,3,param_4);
        if (*(int *)(*(long *)(lVar1 + 0x50) + uVar3 * 0x10) == -1) {
          fwrite("__undef",1,7,param_4);
        }
        else {
          __fprintf_chk(param_4,2,&DAT_001f9570);
        }
        uVar4 = uVar4 + 1;
        lVar5 = lVar5 + 0x88;
        fwrite("; /* phi */\n",1,0xc,param_4);
        uVar2 = *(uint *)(param_1 + 0x10);
        if (uVar2 <= uVar4) {
          return;
        }
      }
LAB_0015a79c:
      uVar4 = uVar4 + 1;
      lVar5 = lVar5 + 0x88;
    } while (uVar4 < uVar2);
  }
  return;
}

