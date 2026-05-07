
int emit_local_decls_part_0(long param_1,FILE *param_2,char *param_3)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  int iVar4;
  size_t sVar5;
  char *pcVar6;
  uint uVar7;
  long lVar8;
  undefined1 *puVar9;
  uint uVar10;
  long lVar11;
  char *__s;
  char acStack_a8 [64];
  long local_68;
  
  uVar7 = *(uint *)(param_1 + 0xde0);
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (uVar7 != 0) {
    lVar11 = 0;
    uVar10 = 0;
    do {
      piVar1 = (int *)(*(long *)(param_1 + 0xdd8) + lVar11);
      if (*(uint *)(param_1 + 0xdd0) != 0) {
        lVar8 = param_1;
        do {
          if ((*(int *)(lVar8 + 0x1d8) != -1) && (*(int *)(lVar8 + 0x1d8) == *piVar1))
          goto LAB_001839f0;
          lVar8 = lVar8 + 0xcc;
        } while (lVar8 != param_1 + (ulong)*(uint *)(param_1 + 0xdd0) * 0xcc);
      }
      __s = (char *)(piVar1 + 0x11);
      bVar3 = false;
      sVar5 = strlen(__s);
      if (sVar5 != 0) {
        bVar3 = *(char *)((long)piVar1 + sVar5 + 0x43) == '*';
      }
      puVar9 = &DAT_001fe008;
      if (param_3 == (char *)0x0) {
LAB_00183a44:
        fwrite(&DAT_001fc530,1,4,param_2);
        cVar2 = (char)piVar1[1];
joined_r0x00183ad4:
        if (cVar2 != '\0') goto LAB_001839d0;
LAB_00183a64:
        __fprintf_chk(param_2,2,"%s %sv%u;\n",__s,puVar9,*piVar1);
        uVar7 = *(uint *)(param_1 + 0xde0);
      }
      else {
        if ((char)piVar1[1] == '\0') {
          __snprintf_chk(acStack_a8,0x40,2,0x40,&DAT_001fd130,*piVar1);
        }
        else {
          __snprintf_chk(acStack_a8,0x40,2,0x40,&DAT_001fd128,piVar1 + 1);
        }
        pcVar6 = strstr(param_3,acStack_a8);
        if (pcVar6 == (char *)0x0) goto LAB_00183a44;
        if (!bVar3) {
          fwrite(&DAT_001fc530,1,4,param_2);
          cVar2 = (char)piVar1[1];
          puVar9 = &DAT_001fa420;
          goto joined_r0x00183ad4;
        }
        iVar4 = strcmp(__s,"void*");
        if (iVar4 != 0) goto LAB_00183a44;
        fwrite(&DAT_001fc530,1,4,param_2);
        if ((char)piVar1[1] == '\0') {
          __s = "int64_t*";
          puVar9 = &DAT_001fe008;
          goto LAB_00183a64;
        }
        __s = "int64_t*";
LAB_001839d0:
        __fprintf_chk(param_2,2,"%s %s%s;\n",__s,puVar9,piVar1 + 1);
        uVar7 = *(uint *)(param_1 + 0xde0);
      }
LAB_001839f0:
      uVar10 = uVar10 + 1;
      lVar11 = lVar11 + 0xcc;
    } while (uVar10 < uVar7);
  }
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    iVar4 = fputc(10,param_2);
    return iVar4;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                   local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
}

