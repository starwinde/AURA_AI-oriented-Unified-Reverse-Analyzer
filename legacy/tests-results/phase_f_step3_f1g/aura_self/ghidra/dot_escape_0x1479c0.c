
void dot_escape(FILE *param_1,byte *param_2)

{
  uint __c;
  
  __c = (uint)*param_2;
  if (*param_2 == 0) {
    return;
  }
  do {
    while (__c == 0x3c) {
      fwrite(&DAT_001f82a8,1,2,param_1);
LAB_00147a1c:
      param_2 = param_2 + 1;
      __c = (uint)*param_2;
      if (__c == 0) {
        return;
      }
    }
    if (__c < 0x3d) {
      if (__c == 10) {
        fwrite(&DAT_001f82a0,1,2,param_1);
      }
      else {
        if (__c != 0x22) goto LAB_00147aa0;
        fwrite(&DAT_001f8290,1,2,param_1);
      }
      goto LAB_00147a1c;
    }
    if (__c == 0x3e) {
      fwrite(&DAT_001f82b0,1,2,param_1);
      goto LAB_00147a1c;
    }
    if (__c != 0x5c) {
LAB_00147aa0:
      fputc(__c,param_1);
      goto LAB_00147a1c;
    }
    fwrite(&DAT_001f8298,1,2,param_1);
    param_2 = param_2 + 1;
    __c = (uint)*param_2;
    if (__c == 0) {
      return;
    }
  } while( true );
}

