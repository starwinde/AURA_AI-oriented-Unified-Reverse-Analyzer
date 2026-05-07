
void printInt32BangDec(undefined8 param_1,int param_2)

{
  if (param_2 < 0) {
    if (param_2 != -0x80000000) {
      param_2 = -param_2;
    }
    SStream_concat(param_1,&DAT_001fb4b8,param_2);
    return;
  }
  SStream_concat(param_1,&DAT_001fb4b0);
  return;
}

