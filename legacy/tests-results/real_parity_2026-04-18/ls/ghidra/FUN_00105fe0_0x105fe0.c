
byte FUN_00105fe0(undefined8 *param_1,long *param_2,byte param_3,long *param_4)

{
  byte bVar1;
  byte *pbVar2;
  byte *pbVar3;
  byte *pbVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  long lVar8;
  
  iVar7 = 0;
  uVar6 = (uint)*(byte *)*param_2;
  lVar8 = 0;
  uVar5 = 0;
  pbVar3 = (byte *)*param_1;
  pbVar2 = (byte *)*param_2;
LAB_0010600c:
  do {
    pbVar4 = pbVar3;
    if (iVar7 == 1) {
      if (uVar6 == 0) {
        *param_1 = pbVar3;
        *param_2 = (long)(pbVar2 + 1);
        *param_4 = lVar8;
        return 0;
      }
      uVar5 = uVar6 - 0x30 & 0xff;
      if (0x48 < uVar5) {
code_r0x00106050:
        uVar5 = uVar6;
        goto LAB_00106054;
      }
      switch(uVar6 - 0x30) {
      case 0:
      case 1:
      case 2:
      case 3:
      case 4:
      case 5:
      case 6:
      case 7:
        iVar7 = 2;
        goto LAB_00106060;
      default:
        goto code_r0x00106050;
      case 0xf:
        uVar5 = 0x7f;
        break;
      case 0x28:
      case 0x48:
        uVar6 = (uint)pbVar2[1];
        pbVar2 = pbVar2 + 1;
        uVar5 = 0;
        while( true ) {
          while (uVar6 < 0x47) {
            if (uVar6 < 0x41) {
              if (9 < (uVar6 - 0x30 & 0xff)) goto LAB_001062cc;
              uVar5 = uVar6 + uVar5 * 0x10;
              uVar6 = (uint)pbVar2[1];
              pbVar2 = pbVar2 + 1;
              uVar5 = (uVar5 & 0xff) - 0x30 & 0xff;
            }
            else {
              uVar5 = uVar6 + uVar5 * 0x10;
              pbVar2 = pbVar2 + 1;
              uVar6 = (uint)*pbVar2;
              uVar5 = (uVar5 & 0xff) - 0x37 & 0xff;
            }
          }
          if (5 < (uVar6 - 0x61 & 0xff)) break;
          uVar5 = uVar6 + uVar5 * 0x10;
          pbVar2 = pbVar2 + 1;
          uVar6 = (uint)*pbVar2;
          uVar5 = (uVar5 & 0xff) - 0x57 & 0xff;
        }
LAB_001062cc:
        pbVar4 = pbVar3 + 1;
        *pbVar3 = (byte)uVar5;
        lVar8 = lVar8 + 1;
        iVar7 = 0;
        uVar6 = (uint)*pbVar2;
        goto LAB_00106068;
      case 0x2f:
        uVar5 = 0x20;
        break;
      case 0x31:
        uVar5 = 7;
        break;
      case 0x32:
        uVar5 = 8;
        break;
      case 0x35:
        uVar5 = 0x1b;
        break;
      case 0x36:
        uVar5 = 0xc;
        break;
      case 0x3e:
        uVar5 = 10;
        break;
      case 0x42:
        uVar5 = 0xd;
        break;
      case 0x44:
        uVar5 = 9;
        break;
      case 0x46:
        uVar5 = 0xb;
      }
LAB_00106054:
      lVar8 = lVar8 + 1;
      iVar7 = 0;
      *pbVar3 = (byte)uVar5;
      pbVar4 = pbVar3 + 1;
LAB_00106060:
      uVar6 = (uint)pbVar2[1];
      pbVar2 = pbVar2 + 1;
    }
LAB_00106068:
    pbVar3 = pbVar4;
    if (iVar7 == 2) {
      while ((uVar6 - 0x30 & 0xff) < 8) {
        pbVar2 = pbVar2 + 1;
        uVar5 = (uVar6 + uVar5 * 8 & 0xff) - 0x30 & 0xff;
        uVar6 = (uint)*pbVar2;
      }
      *pbVar4 = (byte)uVar5;
      lVar8 = lVar8 + 1;
      uVar6 = (uint)*pbVar2;
      pbVar3 = pbVar4 + 1;
    }
    while (uVar6 != 0x5c) {
      if (uVar6 < 0x5d) {
        if (uVar6 == 0x3d) {
          if ((param_3 & 1) != 0) {
            *param_1 = pbVar3;
            *param_2 = (long)pbVar2;
            *param_4 = lVar8;
            return param_3;
          }
        }
        else if ((uVar6 < 0x3e) && ((uVar6 == 0 || (uVar6 == 0x3a)))) {
          *param_1 = pbVar3;
          *param_2 = (long)pbVar2;
          *param_4 = lVar8;
          return 1;
        }
      }
      else if (uVar6 == 0x5e) {
        bVar1 = pbVar2[1];
        if ((byte)(bVar1 - 0x40) < 0x3f) {
          *pbVar3 = bVar1 & 0x1f;
          lVar8 = lVar8 + 1;
          uVar6 = (uint)pbVar2[2];
          iVar7 = 0;
          pbVar3 = pbVar3 + 1;
          pbVar2 = pbVar2 + 2;
        }
        else {
          if (bVar1 != 0x3f) {
            *param_1 = pbVar3;
            *param_2 = (long)(pbVar2 + 1);
            *param_4 = lVar8;
            return 0;
          }
          *pbVar3 = 0x7f;
          lVar8 = lVar8 + 1;
          iVar7 = 0;
          uVar6 = (uint)pbVar2[1];
          pbVar3 = pbVar3 + 1;
          pbVar2 = pbVar2 + 1;
        }
        goto LAB_0010600c;
      }
      *pbVar3 = (byte)uVar6;
      lVar8 = lVar8 + 1;
      pbVar2 = pbVar2 + 1;
      pbVar3 = pbVar3 + 1;
      uVar6 = (uint)*pbVar2;
    }
    uVar6 = (uint)pbVar2[1];
    pbVar2 = pbVar2 + 1;
    iVar7 = 1;
  } while( true );
}

