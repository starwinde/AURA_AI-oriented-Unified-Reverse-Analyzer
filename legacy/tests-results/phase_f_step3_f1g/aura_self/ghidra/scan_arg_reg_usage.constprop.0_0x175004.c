
uint scan_arg_reg_usage_constprop_0(long param_1,ulong param_2)

{
  ulong uVar1;
  char *pcVar2;
  char *pcVar3;
  char *pcVar4;
  char *pcVar5;
  char *pcVar6;
  uint uVar7;
  ulong uVar8;
  
  uVar1 = param_2;
  if (0x14 < param_2) {
    uVar1 = 0x14;
  }
  if (param_2 == 0) {
    return 0;
  }
  pcVar5 = (char *)(param_1 + 0x60);
  uVar7 = 0;
  uVar8 = 0;
  pcVar6 = pcVar5;
LAB_0017507c:
  pcVar2 = strstr(pcVar5,"rdi");
  pcVar5 = pcVar6;
  pcVar4 = pcVar6;
  if (pcVar2 == (char *)0x0) {
    do {
      pcVar2 = strstr(pcVar5,"edi");
      if (pcVar2 == (char *)0x0) goto LAB_001750e0;
      pcVar5 = pcVar2 + 3;
    } while (((pcVar6 < pcVar2) &&
             ((byte)(pcVar2[-1] + 0x9fU) < 0x1a || (byte)(pcVar2[-1] - 0x30U) < 10)) ||
            ((byte)(pcVar2[3] + 0x9fU) < 0x1a || (byte)(pcVar2[3] - 0x30U) < 10));
    uVar7 = uVar7 | 1;
  }
  else {
    pcVar5 = pcVar2 + 3;
    if (((pcVar6 < pcVar2) && ((byte)(pcVar2[-1] + 0x9fU) < 0x1a || (byte)(pcVar2[-1] - 0x30U) < 10)
        ) || ((byte)(pcVar2[3] + 0x9fU) < 0x1a || (byte)(pcVar2[3] - 0x30U) < 10))
    goto LAB_0017507c;
    uVar7 = uVar7 | 1;
  }
LAB_001750e0:
  do {
    pcVar3 = strstr(pcVar4,"rsi");
    pcVar5 = pcVar6;
    pcVar2 = pcVar6;
    if (pcVar3 == (char *)0x0) goto LAB_001755b8;
    pcVar4 = pcVar3 + 3;
  } while (((pcVar6 < pcVar3) &&
           ((byte)(pcVar3[-1] + 0x9fU) < 0x1a || (byte)(pcVar3[-1] - 0x30U) < 10)) ||
          ((byte)(pcVar3[3] + 0x9fU) < 0x1a || (byte)(pcVar3[3] - 0x30U) < 10));
  uVar7 = uVar7 | 2;
  goto LAB_00175144;
  while (((pcVar5 = pcVar4 + 3, pcVar6 < pcVar4 &&
          ((byte)(pcVar4[-1] + 0x9fU) < 0x1a || (byte)(pcVar4[-1] - 0x30U) < 10)) ||
         ((byte)(pcVar4[3] + 0x9fU) < 0x1a || (byte)(pcVar4[3] - 0x30U) < 10))) {
LAB_001755b8:
    pcVar4 = strstr(pcVar5,"esi");
    if (pcVar4 == (char *)0x0) goto LAB_00175144;
  }
  uVar7 = uVar7 | 2;
LAB_00175144:
  do {
    pcVar3 = strstr(pcVar2,"rdx");
    pcVar5 = pcVar6;
    pcVar4 = pcVar6;
    if (pcVar3 == (char *)0x0) goto LAB_00175544;
    pcVar2 = pcVar3 + 3;
  } while (((pcVar6 < pcVar3) &&
           ((byte)(pcVar3[-1] + 0x9fU) < 0x1a || (byte)(pcVar3[-1] - 0x30U) < 10)) ||
          ((byte)(pcVar3[3] + 0x9fU) < 0x1a || (byte)(pcVar3[3] - 0x30U) < 10));
  uVar7 = uVar7 | 4;
LAB_001751a8:
  do {
    pcVar3 = strstr(pcVar4,"rcx");
    pcVar5 = pcVar6;
    pcVar2 = pcVar6;
    if (pcVar3 == (char *)0x0) goto LAB_001754d0;
    pcVar4 = pcVar3 + 3;
  } while (((pcVar6 < pcVar3) &&
           ((byte)(pcVar3[-1] + 0x9fU) < 0x1a || (byte)(pcVar3[-1] - 0x30U) < 10)) ||
          ((byte)(pcVar3[3] + 0x9fU) < 0x1a || (byte)(pcVar3[3] - 0x30U) < 10));
  uVar7 = uVar7 | 8;
LAB_0017520c:
  do {
    pcVar3 = strstr(pcVar2,"r8");
    pcVar5 = pcVar6;
    pcVar4 = pcVar6;
    if (pcVar3 == (char *)0x0) goto LAB_0017545c;
    pcVar2 = pcVar3 + 2;
  } while (((pcVar6 < pcVar3) &&
           ((byte)(pcVar3[-1] + 0x9fU) < 0x1a || (byte)(pcVar3[-1] - 0x30U) < 10)) ||
          ((byte)(pcVar3[2] + 0x9fU) < 0x1a || (byte)(pcVar3[2] - 0x30U) < 10));
  uVar7 = uVar7 | 0x10;
LAB_00175270:
  do {
    pcVar3 = strstr(pcVar4,"r9");
    pcVar5 = pcVar6;
    pcVar2 = pcVar6;
    if (pcVar3 == (char *)0x0) goto LAB_001753e8;
    pcVar4 = pcVar3 + 2;
  } while (((pcVar6 < pcVar3) &&
           ((byte)(pcVar3[-1] + 0x9fU) < 0x1a || (byte)(pcVar3[-1] - 0x30U) < 10)) ||
          ((byte)(pcVar3[2] + 0x9fU) < 0x1a || (byte)(pcVar3[2] - 0x30U) < 10));
  uVar7 = uVar7 | 0x20;
LAB_001752d4:
  do {
    pcVar4 = strstr(pcVar2,"rax");
    pcVar5 = pcVar6;
    if (pcVar4 == (char *)0x0) goto LAB_00175378;
    pcVar2 = pcVar4 + 3;
  } while (((pcVar6 < pcVar4) &&
           ((byte)(pcVar4[-1] + 0x9fU) < 0x1a || (byte)(pcVar4[-1] - 0x30U) < 10)) ||
          ((byte)(pcVar4[3] + 0x9fU) < 0x1a || (byte)(pcVar4[3] - 0x30U) < 10));
LAB_00175330:
  uVar7 = uVar7 | 0x40;
LAB_00175334:
  uVar8 = uVar8 + 1;
  pcVar5 = pcVar6 + 0xe0;
  pcVar6 = pcVar5;
  if (uVar1 <= uVar8) {
    return uVar7;
  }
  goto LAB_0017507c;
  while (((pcVar5 = pcVar2 + 3, pcVar6 < pcVar2 &&
          ((byte)(pcVar2[-1] + 0x9fU) < 0x1a || (byte)(pcVar2[-1] - 0x30U) < 10)) ||
         ((byte)(pcVar2[3] + 0x9fU) < 0x1a || (byte)(pcVar2[3] - 0x30U) < 10))) {
LAB_00175544:
    pcVar2 = strstr(pcVar5,"edx");
    if (pcVar2 == (char *)0x0) goto LAB_001751a8;
  }
  uVar7 = uVar7 | 4;
  goto LAB_001751a8;
  while (((pcVar5 = pcVar4 + 3, pcVar6 < pcVar4 &&
          ((byte)(pcVar4[-1] + 0x9fU) < 0x1a || (byte)(pcVar4[-1] - 0x30U) < 10)) ||
         ((byte)(pcVar4[3] + 0x9fU) < 0x1a || (byte)(pcVar4[3] - 0x30U) < 10))) {
LAB_001754d0:
    pcVar4 = strstr(pcVar5,"ecx");
    if (pcVar4 == (char *)0x0) goto LAB_0017520c;
  }
  uVar7 = uVar7 | 8;
  goto LAB_0017520c;
  while (((pcVar5 = pcVar2 + 3, pcVar6 < pcVar2 &&
          ((byte)(pcVar2[-1] + 0x9fU) < 0x1a || (byte)(pcVar2[-1] - 0x30U) < 10)) ||
         ((byte)(pcVar2[3] + 0x9fU) < 0x1a || (byte)(pcVar2[3] - 0x30U) < 10))) {
LAB_0017545c:
    pcVar2 = strstr(pcVar5,"r8d");
    if (pcVar2 == (char *)0x0) goto LAB_00175270;
  }
  uVar7 = uVar7 | 0x10;
  goto LAB_00175270;
  while (((pcVar5 = pcVar4 + 3, pcVar6 < pcVar4 &&
          ((byte)(pcVar4[-1] + 0x9fU) < 0x1a || (byte)(pcVar4[-1] - 0x30U) < 10)) ||
         ((byte)(pcVar4[3] + 0x9fU) < 0x1a || (byte)(pcVar4[3] - 0x30U) < 10))) {
LAB_001753e8:
    pcVar4 = strstr(pcVar5,"r9d");
    if (pcVar4 == (char *)0x0) goto LAB_001752d4;
  }
  uVar7 = uVar7 | 0x20;
  goto LAB_001752d4;
LAB_00175378:
  do {
    pcVar4 = strstr(pcVar5,"eax");
    if (pcVar4 == (char *)0x0) goto LAB_00175334;
    pcVar5 = pcVar4 + 3;
  } while (((pcVar6 < pcVar4) &&
           ((byte)(pcVar4[-1] + 0x9fU) < 0x1a || (byte)(pcVar4[-1] - 0x30U) < 10)) ||
          ((byte)(pcVar4[3] + 0x9fU) < 0x1a || (byte)(pcVar4[3] - 0x30U) < 10));
  goto LAB_00175330;
}

