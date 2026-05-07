
void mm_lookup_part_0_isra_0(char *param_1,uint *param_2)

{
  char cVar1;
  
  cVar1 = *param_1;
  while (cVar1 == ' ') {
    param_1 = param_1 + 1;
    cVar1 = *param_1;
  }
  if ((((cVar1 == 'm') && (param_1[1] == 'm')) && (((byte)param_1[2] - 0x30 & 0xff) < 8)) &&
     (9 < (byte)(param_1[3] - 0x30U))) {
    *param_2 = (byte)param_1[2] - 0x30;
    return;
  }
  return;
}

