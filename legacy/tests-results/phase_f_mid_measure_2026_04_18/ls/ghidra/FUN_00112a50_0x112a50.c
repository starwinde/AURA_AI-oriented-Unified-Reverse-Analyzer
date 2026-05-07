
int FUN_00112a50(byte *param_1,long param_2)

{
  byte *pbVar1;
  int iVar2;
  size_t sVar3;
  long lVar4;
  ushort **ppuVar5;
  byte *pbVar6;
  int iVar7;
  wchar_t local_64;
  mbstate_t local_60;
  long local_58;
  
  pbVar1 = param_1 + param_2;
  local_58 = *(long *)PTR___stack_chk_guard_0013ffd0;
  sVar3 = __ctype_get_mb_cur_max();
  if (sVar3 < 2) {
    if (param_1 < pbVar1) {
      ppuVar5 = __ctype_b_loc();
      iVar7 = 0;
      do {
        pbVar6 = param_1 + 1;
        if ((((*ppuVar5)[*param_1] >> 0xe & 1) != 0) || (((*ppuVar5)[*param_1] >> 1 & 1) == 0)) {
          if (iVar7 == 0x7fffffff) goto LAB_00112bf4;
          iVar7 = iVar7 + 1;
        }
        param_1 = pbVar6;
      } while (pbVar1 != pbVar6);
      goto LAB_00112ba4;
    }
  }
  else if (param_1 < pbVar1) {
    iVar7 = 0;
    do {
      if (*param_1 - 0x20 < 0x5f) {
LAB_00112ab0:
        param_1 = param_1 + 1;
        iVar7 = iVar7 + 1;
      }
      else {
        local_60.__count = 0;
        local_60.__value = (_union_27)0x0;
        do {
          lVar4 = FUN_00110350(&local_64,param_1,(long)pbVar1 - (long)param_1,&local_60);
          if (lVar4 == -1) goto LAB_00112ab0;
          if (lVar4 == -2) {
            iVar7 = iVar7 + 1;
            goto LAB_00112ba4;
          }
          if (lVar4 == 0) {
            lVar4 = 1;
            iVar2 = wcwidth(local_64);
            if (-1 < iVar2) goto LAB_00112af0;
LAB_00112b48:
            iVar2 = iswcntrl(local_64);
            if (iVar2 == 0) {
              if (iVar7 == 0x7fffffff) goto LAB_00112bf4;
              iVar7 = iVar7 + 1;
            }
          }
          else {
            if (lVar4 == -3) {
              lVar4 = 0;
            }
            iVar2 = wcwidth(local_64);
            if (iVar2 < 0) goto LAB_00112b48;
LAB_00112af0:
            if (0x7fffffff - iVar7 < iVar2) goto LAB_00112bf4;
            iVar7 = iVar7 + iVar2;
          }
          param_1 = param_1 + lVar4;
          iVar2 = mbsinit(&local_60);
        } while (iVar2 == 0);
      }
    } while (param_1 < pbVar1);
    goto LAB_00112ba4;
  }
  iVar7 = 0;
  goto LAB_00112ba4;
LAB_00112bf4:
  iVar7 = 0x7fffffff;
LAB_00112ba4:
  if (local_58 - *(long *)PTR___stack_chk_guard_0013ffd0 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_0013ffd0,0,
                     local_58 - *(long *)PTR___stack_chk_guard_0013ffd0);
  }
  return iVar7;
}

