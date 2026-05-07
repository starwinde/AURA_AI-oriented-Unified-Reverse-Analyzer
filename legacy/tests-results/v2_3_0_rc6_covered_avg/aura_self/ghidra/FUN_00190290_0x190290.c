
undefined8 FUN_00190290(long param_1,int param_2)

{
  char cVar1;
  char *pcVar2;
  
  pcVar2 = (char *)(param_1 + 0x336);
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
    if (cVar1 == param_2) {
      return 1;
    }
  } while (pcVar2 != (char *)(param_1 + 0x366));
  return 0;
}

