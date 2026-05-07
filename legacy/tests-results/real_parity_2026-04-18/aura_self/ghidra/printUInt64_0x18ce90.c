
void printUInt64(undefined8 param_1,ulong param_2)

{
  if (9 < param_2) {
    SStream_concat(param_1,"0x%lx",param_2);
    return;
  }
  SStream_concat(param_1,&DAT_001f9200,param_2);
  return;
}

