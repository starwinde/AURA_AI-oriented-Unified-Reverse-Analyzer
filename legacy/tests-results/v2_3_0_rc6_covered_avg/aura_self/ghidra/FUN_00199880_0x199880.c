
/* WARNING: Type propagation algorithm not settling */

uint FUN_00199880(undefined8 param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  ulong uVar3;
  uint uVar4;
  ulong uVar5;
  
  uVar3 = (ulong)(param_2 >> 0xc) & 0xf;
  uVar2 = (uint)uVar3;
  if (uVar2 == 0xf) {
    uVar5 = (ulong)(param_2 >> 0x10) & 0xf;
    FUN_00190100(param_1,0xb);
    uVar4 = 1;
    uVar3 = (ulong)(param_2 & 0xf);
    if ((int)uVar5 == 0xf || (param_2 & 0xf) == 0xf) goto LAB_001998d8;
  }
  else {
    uVar5 = (ulong)(param_2 >> 0x10) & 0xf;
    uVar4 = 3;
    FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + uVar3 * 2));
    uVar3 = (ulong)(param_2 & 0xf);
    if (((uint)uVar5 == 0xf || uVar2 == (uint)uVar5) || uVar2 == (param_2 & 0xf)) {
LAB_001998d8:
      uVar4 = 1;
      goto LAB_001998dc;
    }
  }
  if (uVar2 == (int)uVar3 + 1U) {
    uVar4 = 1;
  }
LAB_001998dc:
  if ((uint)uVar3 < 0xe) {
    uVar2 = param_2 & 1;
    if ((param_2 & 1) == 0) {
      FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f478 + (uVar3 & 0xfffffffffffffffe)));
      uVar2 = uVar4;
    }
    else {
      FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f478 + (uVar3 & 0xfffffffffffffffe)));
    }
    param_2 = param_2 >> 0x1c;
    FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + uVar5 * 2));
    if (param_2 != 0xf) {
      iVar1 = FUN_0018ffb0(param_1);
      if (iVar1 == 0xc4f) {
        if (param_2 == 0xe) {
          return 0;
        }
        FUN_00190140(param_1,param_2);
      }
      else {
        FUN_00190140(param_1,param_2);
        if (param_2 == 0xe) {
          FUN_00190100(param_1,0);
          return uVar2;
        }
      }
      FUN_00190100(param_1,3);
      return uVar2;
    }
  }
  return 0;
}

