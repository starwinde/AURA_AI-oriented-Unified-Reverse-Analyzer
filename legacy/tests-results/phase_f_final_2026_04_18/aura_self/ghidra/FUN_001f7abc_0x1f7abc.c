
bool FUN_001f7abc(long param_1,long param_2,undefined4 param_3)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  long lVar4;
  long *plVar5;
  long *plVar6;
  double dVar7;
  double dVar8;
  
  if (param_1 == 0 || param_2 == 0) {
    return false;
  }
  uVar2 = *(uint *)(param_1 + 0x18);
  if (((uVar2 ^ *(uint *)(param_2 + 0x18)) & 0xff) != 0) {
    return false;
  }
  uVar1 = uVar2 & 0xff;
  if (uVar1 < 0x41) {
    if ((uVar2 & 0xfc) == 0) {
      return uVar1 - 1 < 2;
    }
    if ((0x1000000010001011U >> ((ulong)(uVar1 - 4) & 0x3f) & 1) == 0) {
      return false;
    }
    if (param_1 == param_2) {
      return true;
    }
    if (uVar1 != 0x10) {
      if (uVar1 < 0x11) {
        if (uVar1 == 4) {
          return true;
        }
        if (uVar1 != 8) {
          return false;
        }
        dVar7 = ABS(*(double *)(param_2 + 0x30));
        dVar8 = ABS(*(double *)(param_1 + 0x30));
        if (dVar7 < dVar8) {
          dVar7 = dVar8;
        }
        return ABS(*(double *)(param_1 + 0x30) - *(double *)(param_2 + 0x30)) <=
               dVar7 * 2.220446049250313e-16;
      }
      if (uVar1 == 0x40) {
        plVar5 = *(long **)(param_1 + 0x10);
        while( true ) {
          if (plVar5 == (long *)0x0) {
            plVar5 = *(long **)(param_2 + 0x10);
            while( true ) {
              if (plVar5 == (long *)0x0) {
                return true;
              }
              lVar4 = get_object_item(param_1,plVar5[7],param_3);
              if (lVar4 == 0) break;
              iVar3 = cJSON_Compare(plVar5,lVar4,param_3);
              if (iVar3 == 0) {
                return false;
              }
              plVar5 = (long *)*plVar5;
            }
            return false;
          }
          lVar4 = get_object_item(param_2,plVar5[7],param_3);
          if (lVar4 == 0) {
            return false;
          }
          iVar3 = cJSON_Compare(plVar5,lVar4,param_3);
          if (iVar3 == 0) break;
          plVar5 = (long *)*plVar5;
        }
        return false;
      }
      if (uVar1 != 0x20) {
        return false;
      }
      plVar6 = *(long **)(param_1 + 0x10);
      plVar5 = *(long **)(param_2 + 0x10);
      if (plVar6 != (long *)0x0 && plVar5 != (long *)0x0) {
        do {
          iVar3 = cJSON_Compare(plVar6,plVar5,param_3);
          if (iVar3 == 0) {
            return false;
          }
          plVar6 = (long *)*plVar6;
          plVar5 = (long *)*plVar5;
        } while (plVar6 != (long *)0x0 && plVar5 != (long *)0x0);
      }
      return plVar6 == plVar5;
    }
  }
  else {
    if (uVar1 != 0x80) {
      return false;
    }
    if (param_1 == param_2) {
      return true;
    }
  }
  if ((*(char **)(param_1 + 0x20) != (char *)0x0) && (*(char **)(param_2 + 0x20) != (char *)0x0)) {
    iVar3 = strcmp(*(char **)(param_1 + 0x20),*(char **)(param_2 + 0x20));
    return iVar3 == 0;
  }
  return false;
}

