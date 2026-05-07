
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
LAB_0017619c:
  pcVar2 = strstr(pcVar5,"rdi");
  pcVar5 = pcVar6;
  pcVar4 = pcVar6;
  if (pcVar2 == (char *)0x0) {
    do {
      pcVar2 = strstr(pcVar5,"edi");
      if (pcVar2 == (char *)0x0) goto LAB_00176200;
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
    goto LAB_0017619c;
    uVar7 = uVar7 | 1;
  }
LAB_00176200:
  do {
    pcVar3 = strstr(pcVar4,"rsi");
    pcVar5 = pcVar6;
    pcVar2 = pcVar6;
    if (pcVar3 == (char *)0x0) goto LAB_001766d8;
    pcVar4 = pcVar3 + 3;
  } while (((pcVar6 < pcVar3) &&
           ((byte)(pcVar3[-1] + 0x9fU) < 0x1a || (byte)(pcVar3[-1] - 0x30U) < 10)) ||
          ((byte)(pcVar3[3] + 0x9fU) < 0x1a || (byte)(pcVar3[3] - 0x30U) < 10));
  uVar7 = uVar7 | 2;
  goto LAB_00176264;
  while (((pcVar5 = pcVar4 + 3, pcVar6 < pcVar4 &&
          ((byte)(pcVar4[-1] + 0x9fU) < 0x1a || (byte)(pcVar4[-1] - 0x30U) < 10)) ||
         ((byte)(pcVar4[3] + 0x9fU) < 0x1a || (byte)(pcVar4[3] - 0x30U) < 10))) {
LAB_001766d8:
    pcVar4 = strstr(pcVar5,"esi");
    if (pcVar4 == (char *)0x0) goto LAB_00176264;
  }
  uVar7 = uVar7 | 2;
LAB_00176264:
  do {
    pcVar3 = strstr(pcVar2,"rdx");
    pcVar5 = pcVar6;
    pcVar4 = pcVar6;
    if (pcVar3 == (char *)0x0) goto LAB_00176664;
    pcVar2 = pcVar3 + 3;
  } while (((pcVar6 < pcVar3) &&
           ((byte)(pcVar3[-1] + 0x9fU) < 0x1a || (byte)(pcVar3[-1] - 0x30U) < 10)) ||
          ((byte)(pcVar3[3] + 0x9fU) < 0x1a || (byte)(pcVar3[3] - 0x30U) < 10));
  uVar7 = uVar7 | 4;
LAB_001762c8:
  do {
    pcVar3 = strstr(pcVar4,"rcx");
    pcVar5 = pcVar6;
    pcVar2 = pcVar6;
    if (pcVar3 == (char *)0x0) goto LAB_001765f0;
    pcVar4 = pcVar3 + 3;
  } while (((pcVar6 < pcVar3) &&
           ((byte)(pcVar3[-1] + 0x9fU) < 0x1a || (byte)(pcVar3[-1] - 0x30U) < 10)) ||
          ((byte)(pcVar3[3] + 0x9fU) < 0x1a || (byte)(pcVar3[3] - 0x30U) < 10));
  uVar7 = uVar7 | 8;
LAB_0017632c:
  do {
    pcVar3 = strstr(pcVar2,"r8");
    pcVar5 = pcVar6;
    pcVar4 = pcVar6;
    if (pcVar3 == (char *)0x0) goto LAB_0017657c;
    pcVar2 = pcVar3 + 2;
  } while (((pcVar6 < pcVar3) &&
           ((byte)(pcVar3[-1] + 0x9fU) < 0x1a || (byte)(pcVar3[-1] - 0x30U) < 10)) ||
          ((byte)(pcVar3[2] + 0x9fU) < 0x1a || (byte)(pcVar3[2] - 0x30U) < 10));
  uVar7 = uVar7 | 0x10;
LAB_00176390:
  do {
    pcVar3 = strstr(pcVar4,"r9");
    pcVar5 = pcVar6;
    pcVar2 = pcVar6;
    if (pcVar3 == (char *)0x0) goto LAB_00176508;
    pcVar4 = pcVar3 + 2;
  } while (((pcVar6 < pcVar3) &&
           ((byte)(pcVar3[-1] + 0x9fU) < 0x1a || (byte)(pcVar3[-1] - 0x30U) < 10)) ||
          ((byte)(pcVar3[2] + 0x9fU) < 0x1a || (byte)(pcVar3[2] - 0x30U) < 10));
  uVar7 = uVar7 | 0x20;
LAB_001763f4:
  do {
    pcVar4 = strstr(pcVar2,"rax");
    pcVar5 = pcVar6;
    if (pcVar4 == (char *)0x0) goto LAB_00176498;
    pcVar2 = pcVar4 + 3;
  } while (((pcVar6 < pcVar4) &&
           ((byte)(pcVar4[-1] + 0x9fU) < 0x1a || (byte)(pcVar4[-1] - 0x30U) < 10)) ||
          ((byte)(pcVar4[3] + 0x9fU) < 0x1a || (byte)(pcVar4[3] - 0x30U) < 10));
LAB_00176450:
  uVar7 = uVar7 | 0x40;
LAB_00176454:
  uVar8 = uVar8 + 1;
  pcVar5 = pcVar6 + 0xe0;
  pcVar6 = pcVar5;
  if (uVar1 <= uVar8) {
    return uVar7;
  }
  goto LAB_0017619c;
  while (((pcVar5 = pcVar2 + 3, pcVar6 < pcVar2 &&
          ((byte)(pcVar2[-1] + 0x9fU) < 0x1a || (byte)(pcVar2[-1] - 0x30U) < 10)) ||
         ((byte)(pcVar2[3] + 0x9fU) < 0x1a || (byte)(pcVar2[3] - 0x30U) < 10))) {
LAB_00176664:
    pcVar2 = strstr(pcVar5,"edx");
    if (pcVar2 == (char *)0x0) goto LAB_001762c8;
  }
  uVar7 = uVar7 | 4;
  goto LAB_001762c8;
  while (((pcVar5 = pcVar4 + 3, pcVar6 < pcVar4 &&
          ((byte)(pcVar4[-1] + 0x9fU) < 0x1a || (byte)(pcVar4[-1] - 0x30U) < 10)) ||
         ((byte)(pcVar4[3] + 0x9fU) < 0x1a || (byte)(pcVar4[3] - 0x30U) < 10))) {
LAB_001765f0:
    pcVar4 = strstr(pcVar5,"ecx");
    if (pcVar4 == (char *)0x0) goto LAB_0017632c;
  }
  uVar7 = uVar7 | 8;
  goto LAB_0017632c;
  while (((pcVar5 = pcVar2 + 3, pcVar6 < pcVar2 &&
          ((byte)(pcVar2[-1] + 0x9fU) < 0x1a || (byte)(pcVar2[-1] - 0x30U) < 10)) ||
         ((byte)(pcVar2[3] + 0x9fU) < 0x1a || (byte)(pcVar2[3] - 0x30U) < 10))) {
LAB_0017657c:
    pcVar2 = strstr(pcVar5,"r8d");
    if (pcVar2 == (char *)0x0) goto LAB_00176390;
  }
  uVar7 = uVar7 | 0x10;
  goto LAB_00176390;
  while (((pcVar5 = pcVar4 + 3, pcVar6 < pcVar4 &&
          ((byte)(pcVar4[-1] + 0x9fU) < 0x1a || (byte)(pcVar4[-1] - 0x30U) < 10)) ||
         ((byte)(pcVar4[3] + 0x9fU) < 0x1a || (byte)(pcVar4[3] - 0x30U) < 10))) {
LAB_00176508:
    pcVar4 = strstr(pcVar5,"r9d");
    if (pcVar4 == (char *)0x0) goto LAB_001763f4;
  }
  uVar7 = uVar7 | 0x20;
  goto LAB_001763f4;
LAB_00176498:
  do {
    pcVar4 = strstr(pcVar5,"eax");
    if (pcVar4 == (char *)0x0) goto LAB_00176454;
    pcVar5 = pcVar4 + 3;
  } while (((pcVar6 < pcVar4) &&
           ((byte)(pcVar4[-1] + 0x9fU) < 0x1a || (byte)(pcVar4[-1] - 0x30U) < 10)) ||
          ((byte)(pcVar4[3] + 0x9fU) < 0x1a || (byte)(pcVar4[3] - 0x30U) < 10));
  goto LAB_00176450;
}

