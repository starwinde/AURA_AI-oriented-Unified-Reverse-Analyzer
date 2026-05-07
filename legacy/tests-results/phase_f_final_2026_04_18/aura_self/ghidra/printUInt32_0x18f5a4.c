
void printUInt32(undefined8 param_1,uint param_2)

{
  if (9 < param_2) {
    SStream_concat(param_1,&DAT_001fcbf8,param_2);
    return;
  }
  SStream_concat(param_1,&DAT_001fcc00,param_2);
  return;
}

