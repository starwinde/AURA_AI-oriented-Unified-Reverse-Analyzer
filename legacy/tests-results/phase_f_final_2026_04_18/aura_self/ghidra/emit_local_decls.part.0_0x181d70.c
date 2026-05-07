
int emit_local_decls_part_0(long param_1,FILE *param_2,char *param_3)

{
  int *__s;
  int *piVar1;
  uint uVar2;
  int iVar3;
  size_t sVar4;
  char *pcVar5;
  long lVar6;
  undefined1 *puVar7;
  uint uVar8;
  long lVar9;
  char acStack_a8 [64];
  long local_68;
  
  uVar2 = *(uint *)(param_1 + 0xde0);
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (uVar2 != 0) {
    lVar9 = 0;
    uVar8 = 0;
    do {
      piVar1 = (int *)(*(long *)(param_1 + 0xdd8) + lVar9);
      if (*(uint *)(param_1 + 0xdd0) != 0) {
        lVar6 = param_1;
        do {
          if ((*(int *)(lVar6 + 0x1d8) != -1) && (*(int *)(lVar6 + 0x1d8) == *piVar1))
          goto LAB_00181ec0;
          lVar6 = lVar6 + 0xcc;
        } while (lVar6 != param_1 + (ulong)*(uint *)(param_1 + 0xdd0) * 0xcc);
      }
      __s = piVar1 + 0x11;
      sVar4 = strlen((char *)__s);
      if (((sVar4 == 0) || (*(char *)((long)piVar1 + sVar4 + 0x43) != '*')) &&
         (param_3 != (char *)0x0)) {
        if ((char)piVar1[1] == '\0') {
          __snprintf_chk(acStack_a8,0x40,2,0x40,&DAT_001fc5d0,*piVar1);
        }
        else {
          __snprintf_chk(acStack_a8,0x40,2,0x40,&DAT_001fc5c8,piVar1 + 1);
        }
        pcVar5 = strstr(param_3,acStack_a8);
        fwrite(&DAT_001fb9d0,1,4,param_2);
        if ((char)piVar1[1] == '\0') {
          puVar7 = &DAT_001f98c0;
          if (pcVar5 == (char *)0x0) goto LAB_00181f34;
          goto LAB_00181f38;
        }
        puVar7 = &DAT_001f98c0;
        if (pcVar5 == (char *)0x0) goto LAB_00181f58;
LAB_00181ea0:
        __fprintf_chk(param_2,2,"%s %s%s;\n",__s,puVar7,piVar1 + 1);
        uVar2 = *(uint *)(param_1 + 0xde0);
      }
      else {
        fwrite(&DAT_001fb9d0,1,4,param_2);
        if ((char)piVar1[1] != '\0') {
LAB_00181f58:
          puVar7 = &DAT_001fd4a8;
          goto LAB_00181ea0;
        }
LAB_00181f34:
        puVar7 = &DAT_001fd4a8;
LAB_00181f38:
        __fprintf_chk(param_2,2,"%s %sv%u;\n",__s,puVar7,*piVar1);
        uVar2 = *(uint *)(param_1 + 0xde0);
      }
LAB_00181ec0:
      uVar8 = uVar8 + 1;
      lVar9 = lVar9 + 0xcc;
    } while (uVar8 < uVar2);
  }
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                     local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  iVar3 = fputc(10,param_2);
  return iVar3;
}

