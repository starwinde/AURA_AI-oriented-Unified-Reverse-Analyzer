
undefined8 print_string_ptr(byte *param_1,long param_2)

{
  undefined1 uVar1;
  undefined1 *puVar2;
  undefined2 *puVar3;
  byte *__dest;
  byte *pbVar4;
  byte bVar5;
  long lVar6;
  byte *pbVar7;
  byte *pbVar8;
  
  if (param_2 == 0) {
    return 0;
  }
  if (param_1 == (byte *)0x0) {
    puVar3 = (undefined2 *)ensure(param_2,3);
    uVar1 = DAT_00209cf2;
    if (puVar3 == (undefined2 *)0x0) {
      return 0;
    }
    *puVar3 = DAT_00209cf0;
    *(undefined1 *)(puVar3 + 1) = uVar1;
  }
  else {
    lVar6 = 0;
    bVar5 = *param_1;
    pbVar4 = param_1;
    if (bVar5 == 0) {
      puVar2 = (undefined1 *)ensure(param_2,3);
      if (puVar2 == (undefined1 *)0x0) {
        return 0;
      }
      pbVar7 = (byte *)0x1;
      __dest = puVar2 + 1;
      pbVar4 = (byte *)0x0;
      pbVar8 = (byte *)0x2;
    }
    else {
      do {
        if (bVar5 == 0x22) {
LAB_001f0ac4:
          lVar6 = lVar6 + 1;
        }
        else {
          if (bVar5 < 0x23) {
            if (bVar5 < 0xb) {
              if (bVar5 < 8) {
LAB_001f0bc4:
                lVar6 = lVar6 + 5;
                goto LAB_001f0ac8;
              }
            }
            else if (1 < (byte)(bVar5 - 0xc)) {
              if (0x1f < bVar5) goto LAB_001f0ac8;
              goto LAB_001f0bc4;
            }
            goto LAB_001f0ac4;
          }
          if (bVar5 == 0x5c) goto LAB_001f0ac4;
        }
LAB_001f0ac8:
        pbVar4 = pbVar4 + 1;
        bVar5 = *pbVar4;
      } while (bVar5 != 0);
      pbVar4 = pbVar4 + (lVar6 - (long)param_1);
      puVar2 = (undefined1 *)ensure(param_2,pbVar4 + 3);
      if (puVar2 == (undefined1 *)0x0) {
        return 0;
      }
      __dest = puVar2 + 1;
      pbVar7 = pbVar4 + 1;
      pbVar8 = pbVar4 + 2;
      if (lVar6 != 0) {
        *puVar2 = 0x22;
        bVar5 = *param_1;
        do {
          while( true ) {
            if (bVar5 == 0) {
              puVar2[(long)pbVar7] = 0x22;
              puVar2[(long)pbVar8] = 0;
              return 1;
            }
            if (((bVar5 == 0x22 || bVar5 < 0x1f) || bVar5 == 0x1f) || bVar5 == 0x5c) break;
            *__dest = bVar5;
            __dest = __dest + 1;
            param_1 = param_1 + 1;
            bVar5 = *param_1;
          }
          *__dest = 0x5c;
          bVar5 = *param_1;
          if (bVar5 == 0xc) {
            bVar5 = 0x66;
LAB_001f0b50:
            __dest[1] = bVar5;
            pbVar4 = __dest + 1;
          }
          else {
            if (bVar5 < 0xd) {
              if (bVar5 == 9) {
                bVar5 = 0x74;
              }
              else if (bVar5 == 10) {
                bVar5 = 0x6e;
              }
              else {
                if (bVar5 != 8) goto LAB_001f0bf8;
                bVar5 = 0x62;
              }
              goto LAB_001f0b50;
            }
            if ((bVar5 == 0x22) || (bVar5 == 0x5c)) goto LAB_001f0b50;
            if (bVar5 == 0xd) {
              bVar5 = 0x72;
              goto LAB_001f0b50;
            }
LAB_001f0bf8:
            pbVar4 = __dest + 5;
            __sprintf_chk(__dest + 1,2,0xffffffffffffffff,"u%04x");
          }
          param_1 = param_1 + 1;
          bVar5 = *param_1;
          __dest = pbVar4 + 1;
        } while( true );
      }
    }
    *puVar2 = 0x22;
    memcpy(__dest,param_1,(size_t)pbVar4);
    puVar2[(long)pbVar7] = 0x22;
    puVar2[(long)pbVar8] = 0;
  }
  return 1;
}

