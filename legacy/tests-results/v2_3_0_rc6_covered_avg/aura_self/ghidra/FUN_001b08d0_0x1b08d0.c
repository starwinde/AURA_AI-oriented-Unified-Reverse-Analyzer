
undefined8 FUN_001b08d0(long param_1,uint *param_2,ulong param_3,long param_4,undefined2 *param_5)

{
  undefined4 *puVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  void *__s;
  undefined4 *puVar5;
  long lVar6;
  
  *param_5 = 0;
  if (param_3 < 4) {
    return 0;
  }
  __s = *(void **)(*(long *)(param_4 + 0x310) + 0xf0);
  if (__s != (void *)0x0) {
    memset(__s,0,0x748);
    lVar6 = *(long *)(*(long *)(param_4 + 0x310) + 0xf0);
    puVar5 = (undefined4 *)(lVar6 + 0x88);
    do {
      puVar1 = puVar5 + 0xc;
      *puVar5 = 0xffffffff;
      *(undefined1 *)((long)puVar5 + 0x2a) = 0xff;
      puVar5 = puVar1;
    } while (puVar1 != (undefined4 *)(lVar6 + 0x748));
  }
  uVar2 = *param_2;
  uVar3 = (uVar2 & 0xff00ff00) >> 8 | (uVar2 & 0xff00ff) << 8;
  uVar3 = uVar3 >> 0x10 | uVar3 << 0x10;
  if (-1 < *(int *)(param_1 + 4)) {
    uVar3 = uVar2;
  }
  iVar4 = FUN_001afcf0(&DAT_0023c790,param_4,uVar3);
  if (iVar4 == 0) {
    FUN_0018ff00(param_4);
    iVar4 = FUN_001afcf0(&DAT_002333c0,param_4,uVar3);
    if (iVar4 != 0) goto LAB_001b09b0;
    FUN_0018ff00(param_4);
    iVar4 = FUN_001afcf0(&DAT_0022d670,param_4,uVar3);
    if (iVar4 != 0) goto LAB_001b09b0;
    FUN_0018ff00(param_4);
    iVar4 = FUN_001afcf0(&DAT_00237f10,param_4,uVar3);
    if (iVar4 != 0) {
LAB_001b0ac8:
      *param_5 = 4;
      iVar4 = FUN_0018ffb0(param_4);
      if (iVar4 != 0xc4f) {
        FUN_00190140(param_4,0xe);
        FUN_00190100(param_4,0);
        return 1;
      }
      return 0;
    }
    FUN_0018ff00(param_4);
    iVar4 = FUN_001afcf0(&DAT_002364e0,param_4,uVar3);
    if (iVar4 != 0) goto LAB_001b0ac8;
    FUN_0018ff00(param_4);
    iVar4 = FUN_001afcf0(&DAT_0022c6f0,param_4,uVar3);
    if (iVar4 != 0) goto LAB_001b0ac8;
    FUN_0018ff00(param_4);
    iVar4 = FUN_001afcf0(&DAT_0022cb00,param_4,uVar3);
    if (iVar4 != 0) goto LAB_001b09b0;
    FUN_0018ff00(param_4);
    iVar4 = FUN_001afcf0(&DAT_0022c8d0,param_4,uVar3);
    if (iVar4 != 0) goto LAB_001b09b0;
    iVar4 = FUN_001afcf0(&DAT_0022e080,param_4,uVar3);
    if (iVar4 == 0) {
      FUN_0018ff00(param_4);
      *param_5 = 0;
      return 0;
    }
  }
  iVar4 = FUN_0018ffb0(param_4);
  if ((iVar4 == 0x25c) && (uVar3 >> 0x1c == 0xf)) {
    return 0;
  }
LAB_001b09b0:
  *param_5 = 4;
  return 1;
}

