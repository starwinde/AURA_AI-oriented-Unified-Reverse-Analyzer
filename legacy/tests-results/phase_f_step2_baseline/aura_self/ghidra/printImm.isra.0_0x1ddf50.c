
void printImm_isra_0(char param_1,long param_2,undefined8 param_3,ulong param_4,uint param_5)

{
  long lVar1;
  ulong uVar2;
  
  uVar2 = param_4;
  if ((param_5 & 1) == 0) {
    if (*(int *)(param_2 + 0x68) == 4) {
      if ((long)param_4 < 0) {
        if (param_4 != 0x8000000000000000) {
          lVar1 = -param_4;
          if (-10 < (long)param_4) {
            SStream_concat(param_3,&DAT_001fbb50,lVar1);
            return;
          }
          do {
            param_4 = param_4 >> 4;
          } while (0xf < param_4);
          if (param_4 < 10) {
            SStream_concat(param_3,"-%lxh",lVar1);
            return;
          }
          SStream_concat(param_3,"-0%lxh",lVar1);
          return;
        }
        goto LAB_001de144;
      }
      if ((long)param_4 < 10) goto LAB_001ddf88;
      if (param_4 < 0x10) goto LAB_001de0dc;
      do {
        param_4 = param_4 >> 4;
      } while (0xf < param_4);
      goto joined_r0x001ddff8;
    }
    if ((long)param_4 < 0) {
      if (param_4 == 0x8000000000000000) {
        SStream_concat0(param_3,"0x8000000000000000");
        return;
      }
      if (-10 < (long)param_4) {
        SStream_concat(param_3,&DAT_001fbb50,-param_4);
        return;
      }
      SStream_concat(param_3,"-0x%lx",-param_4);
      return;
    }
  }
  else {
    if (*(int *)(param_2 + 0x68) == 4) {
      if ((long)param_4 < 0) {
        if (param_1 == '\0') {
LAB_001de0f4:
          if (param_4 != 0x8000000000000000) goto LAB_001de108;
LAB_001de144:
          SStream_concat0(param_3,"8000000000000000h");
          return;
        }
        if (param_1 == '\x02') {
          param_4 = param_4 & 0xffff;
        }
        else if (param_1 == '\x04') {
          param_4 = param_4 & 0xffffffff;
        }
        else {
          if (param_1 != '\x01') goto LAB_001de0f4;
          param_4 = param_4 & 0xff;
        }
        for (; 0xf < param_4; param_4 = param_4 >> 4) {
LAB_001de108:
        }
      }
      else {
        if ((long)param_4 < 10) goto LAB_001ddf88;
        if (param_4 < 0x10) goto LAB_001de0dc;
        do {
          param_4 = param_4 >> 4;
        } while (0xf < param_4);
      }
joined_r0x001ddff8:
      if (param_4 < 10) {
        SStream_concat(param_3,&DAT_00201788);
        return;
      }
LAB_001de0dc:
      SStream_concat(param_3,"0%lxh");
      return;
    }
    if ((long)param_4 < 0) {
      if (param_1 != '\0') {
        if (param_1 == '\x02') {
          uVar2 = param_4 & 0xffff;
        }
        else if (param_1 == '\x04') {
          uVar2 = param_4 & 0xffffffff;
        }
        else {
          uVar2 = param_4 & 0xff;
          if (param_1 != '\x01') {
            uVar2 = param_4;
          }
        }
      }
      goto LAB_001ddf78;
    }
  }
  if ((long)param_4 < 10) {
LAB_001ddf88:
    SStream_concat(param_3,&DAT_001f9830);
    return;
  }
LAB_001ddf78:
  SStream_concat(param_3,"0x%lx",uVar2);
  return;
}

