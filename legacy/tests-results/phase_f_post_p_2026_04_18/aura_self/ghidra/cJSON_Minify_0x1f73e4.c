
void cJSON_Minify(byte *param_1)

{
  byte *pbVar1;
  byte *pbVar2;
  bool bVar3;
  byte bVar4;
  byte bVar5;
  byte *pbVar6;
  byte *pbVar7;
  
  if (param_1 != (byte *)0x0) {
    bVar4 = *param_1;
    pbVar6 = param_1;
    if (bVar4 == 0) {
      *param_1 = 0;
    }
    else {
      do {
        while( true ) {
          if (bVar4 == 0x22) {
            *pbVar6 = 0x22;
            pbVar1 = param_1 + 1;
            pbVar7 = pbVar6 + 1;
            bVar4 = param_1[1];
            while( true ) {
              pbVar6 = pbVar7;
              pbVar2 = pbVar1;
              if (bVar4 == 0) goto LAB_001f7434;
              param_1 = pbVar2 + 1;
              pbVar7 = pbVar6 + 1;
              *pbVar6 = bVar4;
              if (bVar4 == 0x22) break;
              bVar5 = pbVar2[1];
              bVar3 = bVar4 == 0x5c;
              pbVar1 = param_1;
              bVar4 = bVar5;
              if ((bVar3) && (bVar5 == 0x22)) {
                pbVar6[1] = 0x22;
                bVar4 = pbVar2[2];
                pbVar1 = pbVar2 + 2;
                pbVar7 = pbVar6 + 2;
              }
            }
            bVar4 = pbVar2[1];
            pbVar6 = pbVar7;
            goto joined_r0x001f751c;
          }
          if (0x22 < bVar4) break;
          if (bVar4 == 0xd) {
LAB_001f7420:
            bVar4 = param_1[1];
          }
          else {
            if (0xd < bVar4) {
              if (bVar4 != 0x20) goto LAB_001f7444;
              goto LAB_001f7420;
            }
            if ((byte)(bVar4 - 9) < 2) goto LAB_001f7420;
LAB_001f7444:
            *pbVar6 = bVar4;
            bVar4 = param_1[1];
            pbVar6 = pbVar6 + 1;
          }
LAB_001f7424:
          param_1 = param_1 + 1;
          if (bVar4 == 0) goto LAB_001f7434;
        }
        if (bVar4 != 0x2f) goto LAB_001f7444;
        bVar4 = param_1[1];
        if (bVar4 == 0x2f) {
          pbVar1 = param_1 + 2;
          param_1 = param_1 + 2;
          bVar5 = *pbVar1;
          do {
            if (bVar5 == 0) goto LAB_001f7434;
            param_1 = param_1 + 1;
            bVar4 = *param_1;
            bVar3 = bVar5 != 10;
            bVar5 = bVar4;
          } while (bVar3);
        }
        else {
          if (bVar4 != 0x2a) goto LAB_001f7424;
          pbVar1 = param_1 + 2;
          bVar4 = param_1[2];
          while( true ) {
            if (bVar4 == 0) goto LAB_001f7434;
            pbVar7 = pbVar1 + 1;
            if ((bVar4 == 0x2a) && (*pbVar7 == 0x2f)) break;
            pbVar1 = pbVar1 + 1;
            bVar4 = *pbVar7;
          }
          bVar4 = pbVar1[2];
          param_1 = pbVar1 + 2;
        }
joined_r0x001f751c:
      } while (bVar4 != 0);
LAB_001f7434:
      *pbVar6 = 0;
    }
  }
  return;
}

