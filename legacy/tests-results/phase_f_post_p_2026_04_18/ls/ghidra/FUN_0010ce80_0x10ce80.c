
undefined * FUN_0010ce80(char *param_1,int param_2)

{
  byte bVar1;
  undefined *puVar2;
  byte *pbVar3;
  
  pbVar3 = (byte *)nl_langinfo(0xe);
  if ((pbVar3 != (byte *)0x0) && (*pbVar3 != 0)) {
    bVar1 = *pbVar3 & 0xdf;
    if (bVar1 == 0x55) {
      if (((((pbVar3[1] & 0xdf) == 0x54) && ((pbVar3[2] & 0xdf) == 0x46)) && (pbVar3[3] == 0x2d)) &&
         ((pbVar3[4] == 0x38 && (pbVar3[5] == 0)))) {
        puVar2 = &DAT_0011bc40;
        if (*param_1 == '`') {
          puVar2 = &DAT_0011bc68;
        }
        return puVar2;
      }
    }
    else if ((((bVar1 == 0x47) && ((pbVar3[1] & 0xdf) == 0x42)) && (pbVar3[2] == 0x31)) &&
            (((pbVar3[3] == 0x38 && (pbVar3[4] == 0x30)) &&
             ((pbVar3[5] == 0x33 && ((pbVar3[6] == 0x30 && (pbVar3[7] == 0)))))))) {
      puVar2 = &DAT_0011bc48;
      if (*param_1 == '`') {
        puVar2 = &DAT_0011bc60;
      }
      return puVar2;
    }
  }
  puVar2 = &DAT_0011bc58;
  if (param_2 == 9) {
    puVar2 = &DAT_0011bc50;
  }
  return puVar2;
}

