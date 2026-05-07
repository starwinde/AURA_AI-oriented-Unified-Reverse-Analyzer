
void FUN_00182e70(long param_1,FILE *param_2,char *param_3)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  int iVar4;
  size_t sVar5;
  char *pcVar6;
  uint uVar7;
  long lVar8;
  undefined *puVar9;
  uint uVar10;
  long lVar11;
  int *__s;
  char acStack_a8 [64];
  undefined8 local_68;
  
  uVar7 = *(uint *)(param_1 + 0xde0);
  local_68 = *(undefined8 *)PTR___stack_chk_guard_005ffe88;
  if (uVar7 != 0) {
    lVar11 = 0;
    uVar10 = 0;
    do {
      piVar1 = (int *)(*(long *)(param_1 + 0xdd8) + lVar11);
      if (*(uint *)(param_1 + 0xdd0) != 0) {
        lVar8 = param_1;
        do {
          if ((*(int *)(lVar8 + 0x1d8) != -1) && (*(int *)(lVar8 + 0x1d8) == *piVar1))
          goto LAB_00182fe0;
          lVar8 = lVar8 + 0xcc;
        } while (lVar8 != param_1 + (ulong)*(uint *)(param_1 + 0xdd0) * 0xcc);
      }
      __s = piVar1 + 0x11;
      bVar3 = false;
      sVar5 = strlen((char *)__s);
      if (sVar5 != 0) {
        bVar3 = *(char *)((long)piVar1 + sVar5 + 0x43) == '*';
      }
      puVar9 = &DAT_001fe648;
      if (param_3 == (char *)0x0) {
LAB_00183034:
        fwrite(&DAT_001fcb60,1,4,param_2);
        cVar2 = (char)piVar1[1];
joined_r0x001830c4:
        if (cVar2 != '\0') goto LAB_00182fc0;
LAB_00183054:
        __fprintf_chk(param_2,2,"%s %sv%u;\n",__s,puVar9,*piVar1);
        uVar7 = *(uint *)(param_1 + 0xde0);
      }
      else {
        if ((char)piVar1[1] == '\0') {
          __snprintf_chk(acStack_a8,0x40,2,0x40,&DAT_001fd770,*piVar1);
        }
        else {
          __snprintf_chk(acStack_a8,0x40,2,0x40,&DAT_001fd768,piVar1 + 1);
        }
        pcVar6 = strstr(param_3,acStack_a8);
        if (pcVar6 == (char *)0x0) goto LAB_00183034;
        if (!bVar3) {
          fwrite(&DAT_001fcb60,1,4,param_2);
          cVar2 = (char)piVar1[1];
          puVar9 = &DAT_001faa68;
          goto joined_r0x001830c4;
        }
        iVar4 = strcmp((char *)__s,"void*");
        if (iVar4 != 0) goto LAB_00183034;
        fwrite(&DAT_001fcb60,1,4,param_2);
        if ((char)piVar1[1] == '\0') {
          __s = (int *)&DAT_001fb3b0;
          puVar9 = &DAT_001fe648;
          goto LAB_00183054;
        }
        __s = (int *)&DAT_001fb3b0;
LAB_00182fc0:
        __fprintf_chk(param_2,2,"%s %s%s;\n",__s,puVar9,piVar1 + 1);
        uVar7 = *(uint *)(param_1 + 0xde0);
      }
LAB_00182fe0:
      uVar10 = uVar10 + 1;
      lVar11 = lVar11 + 0xcc;
    } while (uVar10 < uVar7);
  }
  FUN_00187020(PTR___stack_chk_guard_005ffe88,uVar7,local_68);
  return;
}

