
ulong FUN_001831e0(uint *param_1,FILE *param_2,int param_3)

{
  long lVar1;
  int *piVar2;
  byte bVar3;
  uint uVar4;
  int iVar5;
  ulong uVar6;
  undefined *__ptr;
  undefined8 uVar7;
  long lVar8;
  ulong *puVar9;
  int *piVar10;
  ulong uVar11;
  long lVar12;
  ulong uVar13;
  uint *puVar14;
  ulong *puVar15;
  ulong uVar16;
  
  do {
    while( true ) {
      if (param_1 == (uint *)0x0) {
        uVar6 = fwrite("/* null */",1,10,param_2);
        return uVar6;
      }
      uVar4 = *param_1;
      if (uVar4 == 0x11) {
        __fprintf_chk(param_2,2,&DAT_001fd640,param_1 + 0x26);
        lVar12 = 0;
        if (param_1[0x4a] != 0) {
          do {
            if ((int)lVar12 == 0) {
              lVar8 = *(long *)(param_1 + 0x48);
            }
            else {
              fwrite(", ",1,2,param_2);
              lVar8 = *(long *)(param_1 + 0x48);
            }
            lVar1 = lVar12 * 8;
            lVar12 = lVar12 + 1;
            FUN_001831e0(*(undefined8 *)(lVar8 + lVar1),param_2,0);
          } while ((uint)lVar12 < param_1[0x4a]);
        }
        goto LAB_0018355c;
      }
      if (uVar4 < 0x12) break;
      if (uVar4 == 0x14) {
        FUN_001831e0(*(undefined8 *)(param_1 + 0x26),param_2,0xe);
        fputc(0x5b,param_2);
        FUN_001831e0(*(undefined8 *)(param_1 + 0x28),param_2,0);
        uVar4 = fputc(0x5d,param_2);
        return (ulong)uVar4;
      }
      if (uVar4 < 0x15) {
        if (uVar4 != 0x12) {
          FUN_001831e0(*(undefined8 *)(param_1 + 0x26),param_2,0xe);
          if ((char)param_1[0x3a] != '\0') {
            uVar6 = __fprintf_chk(param_2,2,&DAT_001fd810,param_1 + 0x28);
            return uVar6;
          }
          uVar6 = __fprintf_chk(param_2,2,&DAT_001fd818,param_1 + 0x28);
          return uVar6;
        }
        param_3 = 0xd;
        __fprintf_chk(param_2,2,&DAT_001fd648,param_1 + 0x28);
        param_1 = *(uint **)(param_1 + 0x26);
      }
      else {
        if (uVar4 != 0x15) {
LAB_00183598:
          uVar7 = FUN_00181750();
          uVar6 = __fprintf_chk(param_2,2,"/* ?%s? */",uVar7);
          return uVar6;
        }
        if (3 < param_3) {
          fputc(0x28,param_2);
          FUN_001831e0(*(undefined8 *)(param_1 + 0x26),param_2,4);
          fwrite(&DAT_001fab00,1,3,param_2);
          FUN_001831e0(*(undefined8 *)(param_1 + 0x28),param_2,3);
          fwrite(&DAT_001f9a30,1,3,param_2);
          FUN_001831e0(*(undefined8 *)(param_1 + 0x2a),param_2,3);
          goto LAB_0018355c;
        }
        param_3 = 3;
        FUN_001831e0(*(undefined8 *)(param_1 + 0x26),param_2,4);
        fwrite(&DAT_001fab00,1,3,param_2);
        FUN_001831e0(*(undefined8 *)(param_1 + 0x28),param_2,3);
        fwrite(&DAT_001f9a30,1,3,param_2);
        param_1 = *(uint **)(param_1 + 0x2a);
      }
    }
    if (uVar4 == 0xf) {
      uVar4 = param_1[0x2a] - 2;
      if (uVar4 < 0x13) {
        iVar5 = *(int *)(&DAT_0020ca60 + (ulong)uVar4 * 4);
        if ((param_1[0x2a] - 0xf & 0xfffffffa) != 0) goto LAB_001835e4;
        if (iVar5 < param_3) {
          fputc(0x28,param_2);
        }
        fwrite("(uint64_t)(",1,0xb,param_2);
        FUN_001831e0(*(undefined8 *)(param_1 + 0x26),param_2,0);
        fputc(0x29,param_2);
        switch(param_1[0x2a]) {
        case 2:
          __fprintf_chk(param_2,2,&DAT_001fab08,&DAT_001faa58);
          break;
        case 3:
          __fprintf_chk(param_2,2,&DAT_001fab08,&DAT_001faa60);
          break;
        case 4:
          __fprintf_chk(param_2,2,&DAT_001fab08,&DAT_001faa68);
          break;
        case 5:
          __fprintf_chk(param_2,2,&DAT_001fab08,&DAT_001faa70);
          break;
        case 6:
          __fprintf_chk(param_2,2,&DAT_001fab08,&DAT_001faa78);
          break;
        case 7:
          __fprintf_chk(param_2,2,&DAT_001fab08,"|");
          break;
        case 8:
          __fprintf_chk(param_2,2,&DAT_001fab08,&DAT_001faa80);
          break;
        case 9:
          __fprintf_chk(param_2,2,&DAT_001fab08,&DAT_001faa88);
          break;
        case 10:
          __fprintf_chk(param_2,2,&DAT_001fab08,&DAT_001faa90);
          break;
        case 0xb:
          __fprintf_chk(param_2,2,&DAT_001fab08,"==");
          break;
        case 0xc:
          __fprintf_chk(param_2,2,&DAT_001fab08,&DAT_001faa98);
          break;
        case 0xd:
        case 0xf:
          __fprintf_chk(param_2,2,&DAT_001fab08,&DAT_001faaa0);
          break;
        case 0xe:
        case 0x10:
          __fprintf_chk(param_2,2,&DAT_001fab08,&DAT_001faaa8);
          break;
        case 0x11:
        case 0x13:
          __fprintf_chk(param_2,2,&DAT_001fab08,&DAT_001faab0);
          break;
        case 0x12:
        case 0x14:
          __fprintf_chk(param_2,2,&DAT_001fab08,&DAT_001faab8);
          break;
        default:
          __fprintf_chk(param_2,2,&DAT_001fab08,&DAT_001fd7f8);
        }
        fwrite("(uint64_t)(",1,0xb,param_2);
        FUN_001831e0(*(undefined8 *)(param_1 + 0x28),param_2,0);
        uVar4 = fputc(0x29,param_2);
        uVar6 = (ulong)uVar4;
      }
      else {
        iVar5 = 0;
LAB_001835e4:
        if (iVar5 < param_3) {
          fputc(0x28,param_2);
        }
        FUN_001831e0(*(undefined8 *)(param_1 + 0x26),param_2,iVar5);
        switch(param_1[0x2a]) {
        case 2:
          __fprintf_chk(param_2,2,&DAT_001fab08,&DAT_001faa58);
          break;
        case 3:
          __fprintf_chk(param_2,2,&DAT_001fab08,&DAT_001faa60);
          break;
        case 4:
          __fprintf_chk(param_2,2,&DAT_001fab08,&DAT_001faa68);
          break;
        case 5:
          __fprintf_chk(param_2,2,&DAT_001fab08,&DAT_001faa70);
          break;
        case 6:
          __fprintf_chk(param_2,2,&DAT_001fab08,&DAT_001faa78);
          break;
        case 7:
          __fprintf_chk(param_2,2,&DAT_001fab08,"|");
          break;
        case 8:
          __fprintf_chk(param_2,2,&DAT_001fab08,&DAT_001faa80);
          break;
        case 9:
          __fprintf_chk(param_2,2,&DAT_001fab08,&DAT_001faa88);
          break;
        case 10:
          __fprintf_chk(param_2,2,&DAT_001fab08,&DAT_001faa90);
          break;
        case 0xb:
          __fprintf_chk(param_2,2,&DAT_001fab08,"==");
          break;
        case 0xc:
          __fprintf_chk(param_2,2,&DAT_001fab08,&DAT_001faa98);
          break;
        case 0xd:
        case 0xf:
          __fprintf_chk(param_2,2,&DAT_001fab08,&DAT_001faaa0);
          break;
        case 0xe:
        case 0x10:
          __fprintf_chk(param_2,2,&DAT_001fab08,&DAT_001faaa8);
          break;
        case 0x11:
        case 0x13:
          __fprintf_chk(param_2,2,&DAT_001fab08,&DAT_001faab0);
          break;
        case 0x12:
        case 0x14:
          __fprintf_chk(param_2,2,&DAT_001fab08,&DAT_001faab8);
          break;
        default:
          __fprintf_chk(param_2,2,&DAT_001fab08,&DAT_001fd7f8);
        }
        uVar6 = FUN_001831e0(*(undefined8 *)(param_1 + 0x28),param_2,iVar5 + 1);
      }
      if (param_3 <= iVar5) {
        return uVar6;
      }
LAB_0018355c:
      uVar4 = fputc(0x29,param_2);
      return (ulong)uVar4;
    }
    if (uVar4 != 0x10) {
      if (uVar4 == 0xd) {
        if ((DAT_00600890 == 0) || (*(uint *)(DAT_00600890 + 0xdd0) == 0)) goto LAB_00183430;
        puVar14 = (uint *)(DAT_00600890 + 0x1d8);
        uVar4 = 0;
        break;
      }
      if (uVar4 != 0xe) goto LAB_00183598;
      if ((char)param_1[0x2a] != '\0') {
        uVar6 = __fprintf_chk(*(undefined8 *)(param_1 + 0x28),param_2,2,&DAT_001fd630);
        return uVar6;
      }
      uVar6 = *(ulong *)(param_1 + 0x26);
      if (((long)uVar6 < 0) || ((long)uVar6 < 0x100 && (char)param_1[0x22] == '\0')) {
        uVar6 = __fprintf_chk(param_2,2,&DAT_001fd638);
        return uVar6;
      }
      if (((long)uVar6 < 0x1001 || DAT_00600898 == 0) || (*(uint *)(DAT_00600898 + 0x20) == 0))
      goto LAB_0018367c;
      puVar9 = (ulong *)(*(long *)(DAT_00600898 + 0x18) + 8);
      puVar15 = puVar9 + (ulong)*(uint *)(DAT_00600898 + 0x20) * 7;
      goto LAB_00183c50;
    }
    uVar4 = param_1[0x28];
    if (uVar4 == 3) {
      piVar10 = *(int **)(param_1 + 0x26);
      if (piVar10 != (int *)0x0) {
        if (*piVar10 == 0xf) {
          if (piVar10[0x2a] - 2U < 2) {
            piVar2 = *(int **)(piVar10 + 0x26);
            piVar10 = *(int **)(piVar10 + 0x28);
            if (((piVar2 != (int *)0x0 && piVar10 != (int *)0x0) && (*piVar2 == 0xd)) &&
               ((char)piVar2[0x27] != '\0')) {
              piVar2 = piVar2 + 0x27;
              iVar5 = strcmp((char *)piVar2,"sp");
              if ((((((iVar5 == 0) || (iVar5 = strcmp((char *)piVar2,"rsp"), iVar5 == 0)) ||
                    ((iVar5 = strcmp((char *)piVar2,"esp"), iVar5 == 0 ||
                     ((iVar5 = strcmp((char *)piVar2,"fp"), iVar5 == 0 ||
                      (iVar5 = strcmp((char *)piVar2,"rbp"), iVar5 == 0)))))) ||
                   (iVar5 = strcmp((char *)piVar2,"ebp"), iVar5 == 0)) ||
                  (((iVar5 = strcmp((char *)piVar2,"x29"), iVar5 == 0 ||
                    (iVar5 = strcmp((char *)piVar2,"x31"), iVar5 == 0)) ||
                   (iVar5 = strcmp((char *)piVar2,"r13"), iVar5 == 0)))) &&
                 ((*piVar10 == 0xe && ((char)piVar10[0x2a] == '\0')))) {
                lVar8 = *(long *)(piVar10 + 0x26);
                lVar12 = -lVar8;
                if (-1 < lVar8) {
                  lVar12 = lVar8;
                }
                uVar7 = FUN_001830f0(lVar12);
                __fprintf_chk(param_2,2,"%s%ld",uVar7,lVar12);
                uVar6 = FUN_00182d90(lVar12);
                return uVar6;
              }
            }
          }
        }
        else {
          __ptr = &DAT_001faa68;
          if ((*piVar10 != 0xe) || ((char)piVar10[0x2a] != '\0')) goto LAB_001834ec;
          lVar8 = *(long *)(piVar10 + 0x26);
          lVar12 = -lVar8;
          if (-1 < lVar8) {
            lVar12 = lVar8;
          }
          if (lVar12 < 0x1001 && lVar8 != 0) {
            uVar7 = FUN_001830f0(lVar12);
            __fprintf_chk(param_2,2,"%s%ld",uVar7,lVar12);
            uVar6 = FUN_00182d90(lVar12);
            return uVar6;
          }
        }
      }
      __ptr = &DAT_001faa68;
    }
    else if (uVar4 == 2) {
      __ptr = &DAT_001fd610;
    }
    else if (uVar4 < 3) {
      __ptr = &DAT_001faa60;
      if (uVar4 != 0) {
        __ptr = &DAT_001fd608;
      }
    }
    else {
      __ptr = &DAT_001faa78;
      if (uVar4 != 4) {
        __ptr = &DAT_001faac0;
      }
    }
LAB_001834ec:
    param_3 = 0xd;
    fwrite(__ptr,1,1,param_2);
    param_1 = *(uint **)(param_1 + 0x26);
  } while( true );
LAB_00183408:
  if ((*puVar14 != 0xffffffff) && (*puVar14 == param_1[0x26])) {
    lVar12 = (ulong)uVar4 * 0xcc + 0x110;
    if (*(char *)(DAT_00600890 + lVar12) != '\0') {
      uVar4 = fputs((char *)(DAT_00600890 + lVar12),param_2);
      return (ulong)uVar4;
    }
    goto LAB_00183430;
  }
  uVar4 = uVar4 + 1;
  puVar14 = puVar14 + 0x33;
  if (uVar4 == *(uint *)(DAT_00600890 + 0xdd0)) {
LAB_00183430:
    if ((char)param_1[0x27] != '\0') {
      uVar4 = fputs((char *)(param_1 + 0x27),param_2);
      return (ulong)uVar4;
    }
    uVar6 = __fprintf_chk(param_2,2,&DAT_001faad0,param_1[0x26]);
    return uVar6;
  }
  goto LAB_00183408;
LAB_00183cc4:
  bVar3 = *(byte *)(puVar9[4] + (uVar6 - uVar16) + uVar13);
  if (bVar3 == 0) {
    if (uVar13 != 0) {
      uVar6 = __fprintf_chk(param_2,2,"\"%.*s\"",uVar13 & 0xffffffff);
      return uVar6;
    }
    goto LAB_0018367c;
  }
  if ((((0x1f >= bVar3 && bVar3 != 0xd) && bVar3 != 9) &&
       ((0x1f < bVar3 || bVar3 == 0xd) || bVar3 != 10)) || (uVar13 = uVar13 + 1, uVar11 <= uVar13))
  goto LAB_0018367c;
  goto LAB_00183cc4;
  while (puVar9 = puVar9 + 7, puVar9 != puVar15) {
LAB_00183c50:
    if ((((puVar9[4] != 0) && (puVar9[2] != 0)) && ((puVar9[5] & 1) != 0)) &&
       ((uVar16 = *puVar9, uVar16 <= uVar6 && (uVar11 = puVar9[2] + uVar16, uVar6 < uVar11)))) {
      uVar11 = uVar11 - uVar6;
      uVar13 = 0;
      if (0x40 < uVar11) {
        uVar11 = 0x40;
      }
      goto LAB_00183cc4;
    }
  }
LAB_0018367c:
  uVar6 = __fprintf_chk(param_2,2,"0x%lx");
  return uVar6;
}

