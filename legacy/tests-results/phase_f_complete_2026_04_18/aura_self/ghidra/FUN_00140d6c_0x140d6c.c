
int FUN_00140d6c(byte *param_1)

{
  byte bVar1;
  undefined *puVar2;
  int iVar3;
  uint __c;
  
  puVar2 = PTR_stdout_005fff40;
  putc(0x22,*(FILE **)PTR_stdout_005fff40);
  if (param_1 != (byte *)0x0) {
    bVar1 = *param_1;
    while (bVar1 != 0) {
      while ((__c = (uint)bVar1, __c != 0x22 && (__c != 0x5c))) {
        if (__c == 10) {
          putc(0x5c,*(FILE **)puVar2);
          putc(0x6e,*(FILE **)puVar2);
        }
        else if (__c == 0xd) {
          putc(0x5c,*(FILE **)puVar2);
          putc(0x72,*(FILE **)puVar2);
        }
        else if (__c == 9) {
          putc(0x5c,*(FILE **)puVar2);
          putc(0x74,*(FILE **)puVar2);
        }
        else if (__c < 0x20) {
          __printf_chk(2,"\\u%04x",__c);
        }
        else {
          putc(__c,*(FILE **)puVar2);
        }
        param_1 = param_1 + 1;
        bVar1 = *param_1;
        if (bVar1 == 0) goto LAB_00140e18;
      }
      putc(0x5c,*(FILE **)puVar2);
      putc(__c,*(FILE **)puVar2);
      param_1 = param_1 + 1;
      bVar1 = *param_1;
    }
  }
LAB_00140e18:
  iVar3 = putc(0x22,*(FILE **)puVar2);
  return iVar3;
}

