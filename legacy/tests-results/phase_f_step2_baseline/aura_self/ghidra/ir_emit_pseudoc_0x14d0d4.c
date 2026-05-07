
undefined4 ir_emit_pseudoc(long *param_1,FILE *param_2)

{
  bool bVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  char *pcVar5;
  int *piVar6;
  undefined8 *puVar7;
  uint uVar8;
  
  if (param_1 == (long *)0x0) {
    return 0xfffffffc;
  }
  if (param_2 == (FILE *)0x0) {
    param_2 = *(FILE **)PTR_stdout_005fff40;
  }
  if (*(uint *)(param_1 + 1) == 0) {
switchD_0014d1f4_caseD_4:
    pcVar5 = "int64_t";
  }
  else {
    uVar8 = 0;
    puVar7 = (undefined8 *)(*param_1 + 8);
    do {
      if (*(uint *)(puVar7 + 1) != 0) {
        piVar4 = (int *)*puVar7;
        piVar6 = piVar4 + (ulong)*(uint *)(puVar7 + 1) * 0x22;
        do {
          if (*piVar4 == 0x1a) {
            if ((piVar4[0x12] == 0) || (piVar4[6] == -1)) goto switchD_0014d1f4_caseD_0;
            iVar3 = piVar4[7];
            bVar1 = iVar3 == 4;
            goto LAB_0014d154;
          }
          piVar4 = piVar4 + 0x22;
        } while (piVar4 != piVar6);
      }
      bVar1 = true;
      iVar3 = 4;
LAB_0014d154:
      uVar8 = uVar8 + 1;
      puVar7 = puVar7 + 9;
    } while (bVar1 && uVar8 < *(uint *)(param_1 + 1));
    switch(iVar3) {
    case 0:
switchD_0014d1f4_caseD_0:
      pcVar5 = "void";
      break;
    case 1:
      pcVar5 = "int8_t";
      break;
    case 2:
      pcVar5 = "int16_t";
      break;
    case 3:
      pcVar5 = "int32_t";
      break;
    default:
      goto switchD_0014d1f4_caseD_4;
    case 5:
      pcVar5 = "void*";
      break;
    case 6:
      pcVar5 = "int";
      break;
    case 7:
      pcVar5 = "float";
      break;
    case 8:
      pcVar5 = "double";
      break;
    case 9:
      pcVar5 = "long double";
      break;
    case 10:
      pcVar5 = "__m128";
      break;
    case 0xb:
      pcVar5 = "__m256";
      break;
    case 0xc:
      pcVar5 = "__m512";
      break;
    case 0xd:
      pcVar5 = "__m64";
    }
  }
  __fprintf_chk(param_2,2,"%s %s(...) {\n",pcVar5,param_1 + 4);
  uVar2 = cf_emit_structured(param_1,param_2);
  fwrite(&DAT_001f7e88,1,2,param_2);
  return uVar2;
}

