
void ARM_post_printer(long param_1,int *param_2,char *param_3,long param_4)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  size_t __n;
  ulong uVar4;
  int *piVar5;
  char *pcVar6;
  long lVar7;
  
  if (*(int *)(param_1 + 0x60) != 3) {
    return;
  }
  uVar1 = *(uint *)(param_4 + 8);
  lVar7 = *(long *)(param_2 + 0x3c);
  if (((*(byte *)(param_4 + 0x335) & 1) == 0) &&
     (pcVar6 = strrchr(param_3,0x21), pcVar6 == (char *)0x0)) {
    if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 4 & 1) == 0) {
      if (uVar1 < 0x29f) {
        if (uVar1 < 0x267) {
          if ((uVar1 != 0xa3) && (uVar1 != 0xd4)) goto LAB_001bbac8;
        }
        else {
          uVar4 = 1L << ((ulong)(uVar1 - 0x267) & 0x3f);
          if ((uVar4 & 0xc4210081001111) == 0) {
            uVar4 = uVar4 & 0x8420100002222;
            goto joined_r0x001bbc68;
          }
        }
LAB_001bbc80:
        *(undefined2 *)(lVar7 + 0x79) = 0x101;
      }
      else if (uVar1 - 0x33b < 0x35) {
        uVar4 = 1L << ((ulong)(uVar1 - 0x33b) & 0x3f);
        if ((uVar4 & 0x18804080001111) != 0) goto LAB_001bbc80;
        uVar4 = uVar4 & 0x1008000002222;
        goto joined_r0x001bbc68;
      }
    }
    else if (uVar1 < 0xb3e) {
      if (0xb05 < uVar1) {
        uVar4 = 1L << ((ulong)(uVar1 - 0xb06) & 0x3f);
        if ((uVar4 & 0x40810202081111) != 0) goto LAB_001bbc80;
        uVar4 = uVar4 & 0x81020404102222;
joined_r0x001bbc68:
        if (uVar4 != 0) goto LAB_001bbac0;
      }
    }
    else if (uVar1 - 0xbcd < 0x2f) {
      uVar4 = 1L << ((ulong)(uVar1 - 0xbcd) & 0x3f);
      if ((uVar4 & 0x208084001111) != 0) goto LAB_001bbc80;
      uVar4 = uVar4 & 0x410108002222;
      goto joined_r0x001bbc68;
    }
  }
  else {
LAB_001bbac0:
    *(undefined1 *)(lVar7 + 0x79) = 1;
  }
LAB_001bbac8:
  if ((*(byte *)(lVar7 + 0x78) & 1) == 0) {
    iVar2 = *param_2;
    piVar5 = &insn_update_flgs;
    do {
      if (iVar2 == *piVar5) {
        pcVar6 = *(char **)(piVar5 + 2);
        __n = strlen(pcVar6);
        iVar3 = strncmp(param_3,pcVar6,__n);
        if (iVar3 == 0) {
          uVar4 = 0;
          *(undefined1 *)(lVar7 + 0x78) = 1;
          goto LAB_001bbb40;
        }
      }
      piVar5 = piVar5 + 4;
    } while (piVar5 != (int *)&reg_name_maps);
  }
LAB_001bbb58:
  if (*(int *)(lVar7 + 0x74) == 0) {
    *(undefined4 *)(lVar7 + 0x74) = 0xf;
  }
  if (uVar1 == 0x2aa) {
    *(undefined1 *)(lVar7 + 0x80) = 2;
    *(undefined8 *)(lVar7 + 0x94) = 0xb00000001;
    *(undefined1 *)(lVar7 + 0xb1) = 2;
    *(undefined8 *)(lVar7 + 0xc4) = 0xa00000001;
    *(undefined1 *)(lVar7 + 0xe1) = 1;
  }
  return;
  while (uVar4 = uVar4 + 1, uVar4 != 0x14) {
LAB_001bbb40:
    if (*(short *)(lVar7 + 0x2a + uVar4 * 2) == 0) {
      *(undefined2 *)(lVar7 + (uVar4 & 0xffffffff) * 2 + 0x2a) = 3;
      break;
    }
  }
  goto LAB_001bbb58;
}

