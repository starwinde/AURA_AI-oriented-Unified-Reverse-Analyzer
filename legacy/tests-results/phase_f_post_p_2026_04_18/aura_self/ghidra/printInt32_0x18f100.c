
void printInt32(undefined8 param_1,int param_2)

{
  if (param_2 < 0) {
    if (param_2 < -9) {
      if (param_2 != -0x80000000) {
        param_2 = -param_2;
      }
      SStream_concat(param_1,"-0x%x",param_2);
      return;
    }
    SStream_concat(param_1,&DAT_001fc850,-param_2);
    return;
  }
  if (9 < param_2) {
    SStream_concat(param_1,&DAT_001fc838);
    return;
  }
  SStream_concat(param_1,&DAT_001fc840);
  return;
}

