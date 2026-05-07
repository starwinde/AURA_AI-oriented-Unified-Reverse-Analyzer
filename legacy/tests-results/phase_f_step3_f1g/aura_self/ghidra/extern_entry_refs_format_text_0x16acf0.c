
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void extern_entry_refs_format_text(long *param_1,long param_2)

{
  long lVar1;
  char *pcVar2;
  undefined1 (*pauVar3) [16];
  uint uVar4;
  undefined1 (*pauVar5) [16];
  undefined1 (*pauVar6) [16];
  undefined8 uVar7;
  long lVar8;
  uint uVar9;
  undefined1 auVar10 [16];
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  
  if (param_1 == (long *)0x0 || param_2 == 0) {
    return;
  }
  __fprintf_chk(param_2,2,"External Entry References: %u entry points\n",(int)param_1[1]);
  uVar9 = *(uint *)(param_1 + 1);
  if (uVar9 == 0) {
    iVar13 = 0;
    iVar12 = 0;
  }
  else {
    uVar4 = uVar9 - 1;
    lVar8 = *param_1;
    if (uVar4 < 2) {
      iVar13 = 0;
      iVar12 = 0;
      uVar4 = 0;
    }
    else {
      pauVar6 = (undefined1 (*) [16])(lVar8 + 0x10);
      iVar11 = 0;
      iVar12 = 0;
      iVar13 = 0;
      iVar14 = 0;
      pauVar5 = pauVar6 + (ulong)(uVar4 >> 1) * 3;
      do {
        auVar10 = *pauVar6;
        pauVar3 = pauVar6 + 1;
        pauVar6 = pauVar6 + 3;
        auVar10 = a64_TBL(ZEXT816(0),auVar10,*pauVar3,_DAT_0020aaf0);
        iVar11 = iVar11 + (_DAT_0020ab10 ^
                          (_DAT_0020ab10 ^ _DAT_0020ab00) & -(uint)(auVar10._0_4_ == 0));
        iVar12 = iVar12 + (_UNK_0020ab14 ^
                          (_UNK_0020ab14 ^ _UNK_0020ab04) & -(uint)(auVar10._4_4_ == 0));
        iVar13 = iVar13 + (_UNK_0020ab18 ^
                          (_UNK_0020ab18 ^ _UNK_0020ab08) & -(uint)(auVar10._8_4_ == 0));
        iVar14 = iVar14 + (_UNK_0020ab1c ^
                          (_UNK_0020ab1c ^ _UNK_0020ab0c) & -(uint)(auVar10._12_4_ == 0));
      } while (pauVar6 != pauVar5);
      uVar4 = uVar4 & 0xfffffffe;
      iVar13 = iVar13 + iVar11;
      iVar12 = iVar12 + iVar14;
    }
    if (*(int *)(lVar8 + (ulong)uVar4 * 0x18 + 0x10) == 0) {
      iVar12 = iVar12 + 1;
    }
    else {
      iVar13 = iVar13 + 1;
    }
    if (uVar4 + 1 < uVar9) {
      if (*(int *)(lVar8 + (ulong)(uVar4 + 1) * 0x18 + 0x10) == 0) {
        iVar12 = iVar12 + 1;
      }
      else {
        iVar13 = iVar13 + 1;
      }
    }
  }
  __fprintf_chk(param_2,2,"  Exported: %u, Callback args: %u\n",iVar12,iVar13);
  if ((int)param_1[1] != 0) {
    lVar8 = 0;
    uVar9 = 0;
    do {
      while( true ) {
        lVar1 = *param_1 + lVar8;
        uVar7 = *(undefined8 *)(*param_1 + lVar8);
        pcVar2 = "CALLBACK";
        if (*(int *)(lVar1 + 0x10) == 0) {
          pcVar2 = "EXPORTED";
        }
        if (*(long *)(lVar1 + 8) == 0) break;
        __fprintf_chk(param_2,2,"  0x%lx  [%s]  %s\n",uVar7,pcVar2);
        uVar9 = uVar9 + 1;
        lVar8 = lVar8 + 0x18;
        if (*(uint *)(param_1 + 1) <= uVar9) {
          return;
        }
      }
      __fprintf_chk(param_2,2,"  0x%lx  [%s]  %s\n",uVar7,pcVar2,"(null)");
      uVar9 = uVar9 + 1;
      lVar8 = lVar8 + 0x18;
    } while (uVar9 < *(uint *)(param_1 + 1));
  }
  return;
}

