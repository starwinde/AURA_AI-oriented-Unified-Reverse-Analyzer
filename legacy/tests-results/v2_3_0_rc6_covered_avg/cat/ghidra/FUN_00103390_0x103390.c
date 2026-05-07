
void FUN_00103390(FILE *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  undefined8 uVar1;
  char *pcVar2;
  long *plVar3;
  long lVar4;
  long *plVar5;
  int iVar6;
  int iVar7;
  ulong uVar8;
  long local_118 [4];
  undefined8 local_f8;
  undefined8 uStack_f0;
  undefined8 local_e8;
  undefined8 local_e0;
  undefined8 local_d8;
  long local_c8;
  
  plVar3 = local_118;
  iVar6 = -0x20;
  uVar8 = 0;
  local_c8 = *(long *)PTR___stack_chk_guard_0011ffe0;
  plVar5 = (long *)register0x00000008;
  while( true ) {
    iVar7 = iVar6;
    if ((iVar6 < 0) && (iVar7 = iVar6 + 8, iVar7 < 1)) {
      lVar4 = *(long *)(&stack0x00000000 + iVar6);
      *plVar3 = lVar4;
      iVar6 = iVar7;
    }
    else {
      lVar4 = *plVar5;
      *plVar3 = lVar4;
      iVar6 = iVar7;
      plVar5 = plVar5 + 1;
    }
    if (lVar4 == 0) break;
    uVar8 = uVar8 + 1;
    plVar3 = plVar3 + 1;
    if (uVar8 == 10) {
      __fprintf_chk(param_1,2,"%s (%s) %s\n",&DAT_00105248,"GNU coreutils",param_4);
      uVar1 = dcgettext(0,&DAT_00105260,5);
      __fprintf_chk(param_1,2,"Copyright %s %d Free Software Foundation, Inc.",uVar1,0x7e7);
      fputc_unlocked(10,param_1);
      uVar1 = dcgettext(0,
                        "License GPLv3+: GNU GPL version 3 or later <%s>.\nThis is free software: you are free to change and redistribute it.\nThere is NO WARRANTY, to the extent permitted by law.\n"
                        ,5);
      __fprintf_chk(param_1,2,uVar1,"https://gnu.org/licenses/gpl.html");
      fputc_unlocked(10,param_1);
      pcVar2 = "Written by %s, %s, %s,\n%s, %s, %s, %s,\n%s, %s, and others.\n";
LAB_001034e0:
      uVar1 = dcgettext(0,pcVar2,5);
      __fprintf_chk(param_1,2,uVar1,local_118[0],local_118[1],local_118[2],local_118[3],local_f8,
                    uStack_f0,local_e8,local_e0,local_d8);
LAB_00103520:
      if (local_c8 - *(long *)PTR___stack_chk_guard_0011ffe0 == 0) {
        return;
      }
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_0011ffe0,0,
                       local_c8 - *(long *)PTR___stack_chk_guard_0011ffe0);
    }
  }
  __fprintf_chk(param_1,2,"%s (%s) %s\n",&DAT_00105248,"GNU coreutils",param_4);
  uVar1 = dcgettext(0,&DAT_00105260,5);
  __fprintf_chk(param_1,2,"Copyright %s %d Free Software Foundation, Inc.",uVar1,0x7e7);
  fputc_unlocked(10,param_1);
  uVar1 = dcgettext(0,
                    "License GPLv3+: GNU GPL version 3 or later <%s>.\nThis is free software: you are free to change and redistribute it.\nThere is NO WARRANTY, to the extent permitted by law.\n"
                    ,5);
  __fprintf_chk(param_1,2,uVar1,"https://gnu.org/licenses/gpl.html");
  fputc_unlocked(10,param_1);
  if (uVar8 == 5) {
    uVar1 = dcgettext(0,"Written by %s, %s, %s,\n%s, and %s.\n",5);
    __fprintf_chk(param_1,2,uVar1,local_118[0],local_118[1],local_118[2],local_118[3],local_f8);
    goto LAB_00103520;
  }
  if (uVar8 < 6) {
    if (uVar8 == 2) {
      uVar1 = dcgettext(0,"Written by %s and %s.\n",5);
      __fprintf_chk(param_1,2,uVar1,local_118[0],local_118[1]);
    }
    else if (uVar8 < 3) {
      if (uVar8 != 0) {
        uVar1 = dcgettext(0,"Written by %s.\n",5);
        __fprintf_chk(param_1,2,uVar1,local_118[0]);
      }
    }
    else if (uVar8 == 3) {
      uVar1 = dcgettext(0,"Written by %s, %s, and %s.\n",5);
      __fprintf_chk(param_1,2,uVar1,local_118[0],local_118[1],local_118[2]);
    }
    else {
      uVar1 = dcgettext(0,"Written by %s, %s, %s,\nand %s.\n",5);
      __fprintf_chk(param_1,2,uVar1,local_118[0],local_118[1],local_118[2],local_118[3]);
    }
    goto LAB_00103520;
  }
  if (uVar8 == 8) {
    uVar1 = dcgettext(0,"Written by %s, %s, %s,\n%s, %s, %s, %s,\nand %s.\n",5);
    __fprintf_chk(param_1,2,uVar1,local_118[0],local_118[1],local_118[2],local_118[3],local_f8,
                  uStack_f0,local_e8,local_e0);
    goto LAB_00103520;
  }
  if (uVar8 == 9) {
    pcVar2 = "Written by %s, %s, %s,\n%s, %s, %s, %s,\n%s, and %s.\n";
    goto LAB_001034e0;
  }
  if (uVar8 == 6) {
    uVar1 = dcgettext(0,"Written by %s, %s, %s,\n%s, %s, and %s.\n",5);
    __fprintf_chk(param_1,2,uVar1,local_118[0],local_118[1],local_118[2],local_118[3],local_f8,
                  uStack_f0);
  }
  else {
    uVar1 = dcgettext(0,"Written by %s, %s, %s,\n%s, %s, %s, and %s.\n",5);
    __fprintf_chk(param_1,2,uVar1,local_118[0],local_118[1],local_118[2],local_118[3],local_f8,
                  uStack_f0,local_e8);
  }
  goto LAB_00103520;
}

