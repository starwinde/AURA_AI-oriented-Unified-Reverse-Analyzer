
ulong func_id_normalize_bytes_part_0(void *param_1,ulong param_2,uint *param_3,int param_4)

{
  ulong __n;
  uint uVar1;
  byte bVar2;
  ulong uVar3;
  uint uVar4;
  ulong uVar5;
  ulong uVar6;
  long lVar7;
  
  __n = param_2;
  if (0x40 < param_2) {
    __n = 0x40;
  }
  memcpy(param_3,param_1,__n);
  if (param_4 == 4) {
    if (3 < param_2) {
      lVar7 = 3 - (long)param_3;
      do {
        uVar1 = *param_3;
        if ((uVar1 & 0x9f000000) == 0x90000000) {
          uVar4 = uVar1 & 0x9f00001f;
LAB_0016d250:
          if (uVar1 != uVar4) {
            *(char *)param_3 = (char)uVar4;
            *(char *)((long)param_3 + 1) = (char)(uVar4 >> 8);
            *(char *)((long)param_3 + 2) = (char)(uVar4 >> 0x10);
            *(char *)((long)param_3 + 3) = (char)(uVar4 >> 0x18);
          }
        }
        else {
          if ((uVar1 & 0x7c000000) == 0x14000000) {
            uVar4 = uVar1 & 0xfc000000;
            goto LAB_0016d250;
          }
          if (((uVar1 & 0x1f000000) == 0x11000000) || ((uVar1 & 0x3b000000) == 0x39000000)) {
            uVar4 = uVar1 & 0xffc003ff;
            goto LAB_0016d250;
          }
          if ((uVar1 & 0x1f000000) == 0x12000000) {
            uVar4 = uVar1 & 0xffe0001f;
            goto LAB_0016d250;
          }
        }
        param_3 = param_3 + 1;
      } while ((ulong)(lVar7 + (long)param_3) < __n);
    }
    return __n;
  }
  uVar6 = 0;
  if (param_2 == 0) {
    return __n;
  }
LAB_0016d118:
  do {
    uVar5 = uVar6;
    bVar2 = *(byte *)((long)param_3 + uVar5);
    uVar6 = uVar5 + 1;
    uVar3 = uVar6;
    if (bVar2 == 0x68) {
LAB_0016d158:
      uVar6 = uVar5 + 5;
      if (__n < uVar5 + 5) {
        uVar6 = __n;
      }
      if (uVar3 < uVar6) {
        memset((void *)((long)param_3 + uVar3),0,(uVar6 - uVar5) - 1);
      }
    }
    else {
      if (0x68 < bVar2) {
        if (bVar2 < 0xc0) {
          if (bVar2 < 0xb8) {
            if (bVar2 != 0x81) goto LAB_0016d184;
            if (__n <= uVar6) {
              return __n;
            }
            uVar3 = uVar5 + 2;
            uVar5 = uVar6;
          }
        }
        else if (1 < (byte)(bVar2 + 0x18)) goto LAB_0016d184;
        goto LAB_0016d158;
      }
      if (bVar2 == 0xf) {
        if (__n <= uVar6) {
          return __n;
        }
        if ((*(byte *)((long)param_3 + uVar6) & 0xf0) == 0x80) {
          uVar3 = uVar5 + 2;
          uVar5 = uVar6;
          goto LAB_0016d158;
        }
        goto LAB_0016d118;
      }
    }
LAB_0016d184:
    if (__n <= uVar6) {
      return __n;
    }
  } while( true );
}

