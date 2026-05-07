
void FUN_00147a40(FILE *param_1,byte *param_2)

{
  uint __c;
  
  __c = (uint)*param_2;
  if (*param_2 == 0) {
    return;
  }
  do {
    while (__c == 0x3c) {
      fwrite(&DAT_001f9e70,1,2,param_1);
LAB_00147a9c:
      param_2 = param_2 + 1;
      __c = (uint)*param_2;
      if (__c == 0) {
        return;
      }
    }
    if (__c < 0x3d) {
      if (__c == 10) {
        fwrite(&DAT_001f9e68,1,2,param_1);
      }
      else {
        if (__c != 0x22) goto LAB_00147b20;
        fwrite(&DAT_001f9e58,1,2,param_1);
      }
      goto LAB_00147a9c;
    }
    if (__c == 0x3e) {
      fwrite(&DAT_001f9e78,1,2,param_1);
      goto LAB_00147a9c;
    }
    if (__c != 0x5c) {
LAB_00147b20:
      fputc(__c,param_1);
      goto LAB_00147a9c;
    }
    fwrite(&DAT_001f9e60,1,2,param_1);
    param_2 = param_2 + 1;
    __c = (uint)*param_2;
    if (__c == 0) {
      return;
    }
  } while( true );
}

