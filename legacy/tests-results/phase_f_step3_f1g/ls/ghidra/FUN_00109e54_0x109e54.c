
ulong FUN_00109e54(undefined8 *param_1,undefined8 *param_2)

{
  uint uVar1;
  ulong uVar2;
  char *__s1;
  char *__s2;
  
  __s1 = (char *)*param_1;
  __s2 = (char *)*param_2;
  uVar2 = FUN_001110a0(__s1,__s2);
  if ((int)uVar2 == 0) {
    uVar1 = strcmp(__s1,__s2);
    return (ulong)uVar1;
  }
  return uVar2;
}

