
void FUN_001110a0(char *param_1,char *param_2)

{
  char cVar1;
  long lVar2;
  bool bVar3;
  bool bVar4;
  long lVar5;
  long lVar6;
  undefined *puVar7;
  undefined *puVar8;
  long local_58;
  long local_50;
  long local_48;
  
  local_48 = *(long *)PTR___stack_chk_guard_0013ffd0;
  local_58 = -1;
  local_50 = -1;
  cVar1 = *param_2;
  if (*param_1 == '\0') {
    puVar7 = (undefined *)(ulong)-(uint)(cVar1 != '\0');
    goto LAB_001111cc;
  }
  if (cVar1 == '\0') {
LAB_001111c8:
    puVar7 = (undefined *)0x1;
  }
  else {
    if (*param_1 != '.') {
      if (cVar1 != '.') goto LAB_001110f8;
      goto LAB_001111c8;
    }
    if (cVar1 == '.') {
      cVar1 = param_2[1];
      if (param_1[1] == '\0') {
        puVar7 = (undefined *)(ulong)-(uint)(cVar1 != '\0');
      }
      else {
        if (cVar1 == '\0') goto LAB_001111c8;
        if (param_1[1] == '.') {
          if ((cVar1 == '.') && (param_2[2] == '\0')) {
            puVar7 = (undefined *)(ulong)(param_1[2] != '\0');
            goto LAB_001111cc;
          }
          if (param_1[2] == '\0') goto LAB_00111234;
        }
        else if ((cVar1 == '.') && (param_2[2] == '\0')) goto LAB_001111c8;
LAB_001110f8:
        lVar5 = FUN_0010b430(param_1,&local_58,0);
        lVar6 = FUN_0010b430(param_2,&local_50);
        lVar2 = local_58;
        bVar3 = lVar5 != local_58;
        bVar4 = local_50 != lVar6;
        puVar7 = (undefined *)FUN_0010b550(param_1,lVar5,param_2);
        if ((int)puVar7 == 0 && (bVar3 || bVar4)) {
          lVar5 = local_48 - *(long *)PTR___stack_chk_guard_0013ffd0;
          puVar7 = PTR___stack_chk_guard_0013ffd0;
          puVar8 = (undefined *)0x0;
          if (lVar5 == 0) {
            FUN_0010b550(param_1,lVar2,param_2,local_50);
            return;
          }
          goto LAB_00111264;
        }
      }
    }
    else {
LAB_00111234:
      puVar7 = (undefined *)0xffffffff;
    }
  }
LAB_001111cc:
  lVar5 = 0;
  puVar8 = PTR___stack_chk_guard_0013ffd0;
  if (local_48 == *(long *)PTR___stack_chk_guard_0013ffd0) {
    return;
  }
LAB_00111264:
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(puVar7,puVar8,lVar5);
}

