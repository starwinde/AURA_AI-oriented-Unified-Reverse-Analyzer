
void printInt64Bang(undefined8 param_1,long param_2)

{
  if (param_2 < 0) {
    if (param_2 < -9) {
      if (param_2 != -0x8000000000000000) {
        param_2 = -param_2;
      }
      SStream_concat(param_1,"#-0x%lx",param_2);
      return;
    }
    SStream_concat(param_1,"#-%lu",-param_2);
    return;
  }
  if (9 < param_2) {
    SStream_concat(param_1,"#0x%lx");
    return;
  }
  SStream_concat(param_1,&DAT_001fcbb0);
  return;
}

