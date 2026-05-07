
void subroutine_refs_format_text(long *param_1,long param_2)

{
  long lVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  long lVar4;
  uint uVar5;
  
  if (param_1 == (long *)0x0 || param_2 == 0) {
    return;
  }
  __fprintf_chk(param_2,2,"Subroutine References: %u call edges\n",(int)param_1[1]);
  if ((int)param_1[1] != 0) {
    lVar4 = 0;
    uVar5 = 0;
    do {
      while( true ) {
        lVar1 = *param_1 + lVar4;
        uVar3 = *(undefined8 *)(*param_1 + lVar4);
        uVar2 = *(undefined8 *)(lVar1 + 8);
        if (*(long *)(lVar1 + 0x10) != 0) break;
        __fprintf_chk(param_2,2,"  0x%lx -> 0x%lx  %s\n",uVar3,uVar2,"(unknown)");
        uVar5 = uVar5 + 1;
        lVar4 = lVar4 + 0x18;
        if (*(uint *)(param_1 + 1) <= uVar5) {
          return;
        }
      }
      __fprintf_chk(param_2,2,"  0x%lx -> 0x%lx  %s\n",uVar3,uVar2);
      uVar5 = uVar5 + 1;
      lVar4 = lVar4 + 0x18;
    } while (uVar5 < *(uint *)(param_1 + 1));
  }
  return;
}

