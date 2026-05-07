
ulong emit_expr(uint *param_1,FILE *param_2,int param_3)

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
        __fprintf_chk(param_2,2,&DAT_001fc0e0,param_1 + 0x26);
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
            emit_expr(*(undefined8 *)(lVar8 + lVar1),param_2,0);
          } while ((uint)lVar12 < param_1[0x4a]);
        }
        goto LAB_00182fec;
      }
      if (uVar4 < 0x12) break;
      if (uVar4 == 0x14) {
        emit_expr(*(undefined8 *)(param_1 + 0x26),param_2,0xe);
        fputc(0x5b,param_2);
        emit_expr(*(undefined8 *)(param_1 + 0x28),param_2,0);
        uVar4 = fputc(0x5d,param_2);
        return (ulong)uVar4;
      }
      if (uVar4 < 0x15) {
        if (uVar4 != 0x12) {
          emit_expr(*(undefined8 *)(param_1 + 0x26),param_2,0xe);
          if ((char)param_1[0x3a] != '\0') {
            uVar6 = __fprintf_chk(param_2,2,&DAT_001fc2b0,param_1 + 0x28);
            return uVar6;
          }
          uVar6 = __fprintf_chk(param_2,2,&DAT_001fc2b8,param_1 + 0x28);
          return uVar6;
        }
        param_3 = 0xd;
        __fprintf_chk(param_2,2,&DAT_001fc0e8,param_1 + 0x28);
        param_1 = *(uint **)(param_1 + 0x26);
      }
      else {
        if (uVar4 != 0x15) {
LAB_00183028:
          uVar7 = hir_node_kind_str();
          uVar6 = __fprintf_chk(param_2,2,"/* ?%s? */",uVar7);
          return uVar6;
        }
        if (3 < param_3) {
          fputc(0x28,param_2);
          emit_expr(*(undefined8 *)(param_1 + 0x26),param_2,4);
          fwrite(&DAT_001f95a0,1,3,param_2);
          emit_expr(*(undefined8 *)(param_1 + 0x28),param_2,3);
          fwrite(&DAT_001f84d0,1,3,param_2);
          emit_expr(*(undefined8 *)(param_1 + 0x2a),param_2,3);
          goto LAB_00182fec;
        }
        param_3 = 3;
        emit_expr(*(undefined8 *)(param_1 + 0x26),param_2,4);
        fwrite(&DAT_001f95a0,1,3,param_2);
        emit_expr(*(undefined8 *)(param_1 + 0x28),param_2,3);
        fwrite(&DAT_001f84d0,1,3,param_2);
        param_1 = *(uint **)(param_1 + 0x2a);
      }
    }
    if (uVar4 == 0xf) {
      uVar4 = param_1[0x2a] - 2;
      if (uVar4 < 0x13) {
        iVar5 = *(int *)(CSWTCH_60 + (ulong)uVar4 * 4);
        if ((param_1[0x2a] - 0xf & 0xfffffffa) != 0) goto LAB_00183074;
        if (iVar5 < param_3) {
          fputc(0x28,param_2);
        }
        fwrite("(uint64_t)(",1,0xb,param_2);
        emit_expr(*(undefined8 *)(param_1 + 0x26),param_2,0);
        fputc(0x29,param_2);
        switch(param_1[0x2a]) {
        case 2:
          __fprintf_chk(param_2,2,&DAT_001f95a8,&DAT_001f94f8);
          break;
        case 3:
          __fprintf_chk(param_2,2,&DAT_001f95a8,&DAT_001f9500);
          break;
        case 4:
          __fprintf_chk(param_2,2,&DAT_001f95a8,&DAT_001f9508);
          break;
        case 5:
          __fprintf_chk(param_2,2,&DAT_001f95a8,&DAT_001f9510);
          break;
        case 6:
          __fprintf_chk(param_2,2,&DAT_001f95a8,&DAT_001f9518);
          break;
        case 7:
          __fprintf_chk(param_2,2,&DAT_001f95a8,"|");
          break;
        case 8:
          __fprintf_chk(param_2,2,&DAT_001f95a8,&DAT_001f9520);
          break;
        case 9:
          __fprintf_chk(param_2,2,&DAT_001f95a8,&DAT_001f9528);
          break;
        case 10:
          __fprintf_chk(param_2,2,&DAT_001f95a8,&DAT_001f9530);
          break;
        case 0xb:
          __fprintf_chk(param_2,2,&DAT_001f95a8,"==");
          break;
        case 0xc:
          __fprintf_chk(param_2,2,&DAT_001f95a8,&DAT_001f9538);
          break;
        case 0xd:
        case 0xf:
          __fprintf_chk(param_2,2,&DAT_001f95a8,&DAT_001f9540);
          break;
        case 0xe:
        case 0x10:
          __fprintf_chk(param_2,2,&DAT_001f95a8,&DAT_001f9548);
          break;
        case 0x11:
        case 0x13:
          __fprintf_chk(param_2,2,&DAT_001f95a8,&DAT_001f9550);
          break;
        case 0x12:
        case 0x14:
          __fprintf_chk(param_2,2,&DAT_001f95a8,&DAT_001f9558);
          break;
        default:
          __fprintf_chk(param_2,2,&DAT_001f95a8,&DAT_001fc298);
        }
        fwrite("(uint64_t)(",1,0xb,param_2);
        emit_expr(*(undefined8 *)(param_1 + 0x28),param_2,0);
        uVar4 = fputc(0x29,param_2);
        uVar6 = (ulong)uVar4;
      }
      else {
        iVar5 = 0;
LAB_00183074:
        if (iVar5 < param_3) {
          fputc(0x28,param_2);
        }
        emit_expr(*(undefined8 *)(param_1 + 0x26),param_2,iVar5);
        switch(param_1[0x2a]) {
        case 2:
          __fprintf_chk(param_2,2,&DAT_001f95a8,&DAT_001f94f8);
          break;
        case 3:
          __fprintf_chk(param_2,2,&DAT_001f95a8,&DAT_001f9500);
          break;
        case 4:
          __fprintf_chk(param_2,2,&DAT_001f95a8,&DAT_001f9508);
          break;
        case 5:
          __fprintf_chk(param_2,2,&DAT_001f95a8,&DAT_001f9510);
          break;
        case 6:
          __fprintf_chk(param_2,2,&DAT_001f95a8,&DAT_001f9518);
          break;
        case 7:
          __fprintf_chk(param_2,2,&DAT_001f95a8,"|");
          break;
        case 8:
          __fprintf_chk(param_2,2,&DAT_001f95a8,&DAT_001f9520);
          break;
        case 9:
          __fprintf_chk(param_2,2,&DAT_001f95a8,&DAT_001f9528);
          break;
        case 10:
          __fprintf_chk(param_2,2,&DAT_001f95a8,&DAT_001f9530);
          break;
        case 0xb:
          __fprintf_chk(param_2,2,&DAT_001f95a8,"==");
          break;
        case 0xc:
          __fprintf_chk(param_2,2,&DAT_001f95a8,&DAT_001f9538);
          break;
        case 0xd:
        case 0xf:
          __fprintf_chk(param_2,2,&DAT_001f95a8,&DAT_001f9540);
          break;
        case 0xe:
        case 0x10:
          __fprintf_chk(param_2,2,&DAT_001f95a8,&DAT_001f9548);
          break;
        case 0x11:
        case 0x13:
          __fprintf_chk(param_2,2,&DAT_001f95a8,&DAT_001f9550);
          break;
        case 0x12:
        case 0x14:
          __fprintf_chk(param_2,2,&DAT_001f95a8,&DAT_001f9558);
          break;
        default:
          __fprintf_chk(param_2,2,&DAT_001f95a8,&DAT_001fc298);
        }
        uVar6 = emit_expr(*(undefined8 *)(param_1 + 0x28),param_2,iVar5 + 1);
      }
      if (param_3 <= iVar5) {
        return uVar6;
      }
LAB_00182fec:
      uVar4 = fputc(0x29,param_2);
      return (ulong)uVar4;
    }
    if (uVar4 != 0x10) {
      if (uVar4 == 0xd) {
        if ((s_emit_func == 0) || (*(uint *)(s_emit_func + 0xdd0) == 0)) goto LAB_00182ec0;
        puVar14 = (uint *)(s_emit_func + 0x1d8);
        uVar4 = 0;
        break;
      }
      if (uVar4 != 0xe) goto LAB_00183028;
      if ((char)param_1[0x2a] != '\0') {
        uVar6 = __fprintf_chk(*(undefined8 *)(param_1 + 0x28),param_2,2,&DAT_001fc0d0);
        return uVar6;
      }
      uVar6 = *(ulong *)(param_1 + 0x26);
      if (((long)uVar6 < 0) || ((long)uVar6 < 0x100 && (char)param_1[0x22] == '\0')) {
        uVar6 = __fprintf_chk(param_2,2,&DAT_001fc0d8);
        return uVar6;
      }
      if (((long)uVar6 < 0x1001 || s_emit_fi == 0) || (*(uint *)(s_emit_fi + 0x20) == 0))
      goto LAB_0018310c;
      puVar9 = (ulong *)(*(long *)(s_emit_fi + 0x18) + 8);
      puVar15 = puVar9 + (ulong)*(uint *)(s_emit_fi + 0x20) * 7;
      goto LAB_001836e0;
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
                uVar7 = stack_var_name_prefix(lVar12);
                __fprintf_chk(param_2,2,"%s%ld",uVar7,lVar12);
                uVar6 = stack_var_record(lVar12);
                return uVar6;
              }
            }
          }
        }
        else {
          __ptr = &DAT_001f9508;
          if ((*piVar10 != 0xe) || ((char)piVar10[0x2a] != '\0')) goto LAB_00182f7c;
          lVar8 = *(long *)(piVar10 + 0x26);
          lVar12 = -lVar8;
          if (-1 < lVar8) {
            lVar12 = lVar8;
          }
          if (lVar12 < 0x1001 && lVar8 != 0) {
            uVar7 = stack_var_name_prefix(lVar12);
            __fprintf_chk(param_2,2,"%s%ld",uVar7,lVar12);
            uVar6 = stack_var_record(lVar12);
            return uVar6;
          }
        }
      }
      __ptr = &DAT_001f9508;
    }
    else if (uVar4 == 2) {
      __ptr = &DAT_001fc0b0;
    }
    else if (uVar4 < 3) {
      __ptr = &DAT_001f9500;
      if (uVar4 != 0) {
        __ptr = &DAT_001fc0a8;
      }
    }
    else {
      __ptr = &DAT_001f9518;
      if (uVar4 != 4) {
        __ptr = &DAT_001f9560;
      }
    }
LAB_00182f7c:
    param_3 = 0xd;
    fwrite(__ptr,1,1,param_2);
    param_1 = *(uint **)(param_1 + 0x26);
  } while( true );
LAB_00182e98:
  if ((*puVar14 != 0xffffffff) && (*puVar14 == param_1[0x26])) {
    lVar12 = (ulong)uVar4 * 0xcc + 0x110;
    if (*(char *)(s_emit_func + lVar12) != '\0') {
      uVar4 = fputs((char *)(s_emit_func + lVar12),param_2);
      return (ulong)uVar4;
    }
    goto LAB_00182ec0;
  }
  uVar4 = uVar4 + 1;
  puVar14 = puVar14 + 0x33;
  if (uVar4 == *(uint *)(s_emit_func + 0xdd0)) {
LAB_00182ec0:
    if ((char)param_1[0x27] != '\0') {
      uVar4 = fputs((char *)(param_1 + 0x27),param_2);
      return (ulong)uVar4;
    }
    uVar6 = __fprintf_chk(param_2,2,&DAT_001f9570,param_1[0x26]);
    return uVar6;
  }
  goto LAB_00182e98;
LAB_00183754:
  bVar3 = *(byte *)(puVar9[4] + (uVar6 - uVar16) + uVar13);
  if (bVar3 == 0) {
    if (uVar13 != 0) {
      uVar6 = __fprintf_chk(param_2,2,"\"%.*s\"",uVar13 & 0xffffffff);
      return uVar6;
    }
    goto LAB_0018310c;
  }
  if ((((0x1f >= bVar3 && bVar3 != 0xd) && bVar3 != 9) &&
       ((0x1f < bVar3 || bVar3 == 0xd) || bVar3 != 10)) || (uVar13 = uVar13 + 1, uVar11 <= uVar13))
  goto LAB_0018310c;
  goto LAB_00183754;
  while (puVar9 = puVar9 + 7, puVar9 != puVar15) {
LAB_001836e0:
    if ((((puVar9[4] != 0) && (puVar9[2] != 0)) && ((puVar9[5] & 1) != 0)) &&
       ((uVar16 = *puVar9, uVar16 <= uVar6 && (uVar11 = puVar9[2] + uVar16, uVar6 < uVar11)))) {
      uVar11 = uVar11 - uVar6;
      uVar13 = 0;
      if (0x40 < uVar11) {
        uVar11 = 0x40;
      }
      goto LAB_00183754;
    }
  }
LAB_0018310c:
  uVar6 = __fprintf_chk(param_2,2,"0x%lx");
  return uVar6;
}

