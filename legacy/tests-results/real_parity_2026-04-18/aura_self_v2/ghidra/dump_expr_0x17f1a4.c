
size_t dump_expr(uint *param_1,FILE *param_2)

{
  long lVar1;
  uint uVar2;
  undefined *puVar3;
  size_t sVar4;
  long lVar5;
  undefined8 uVar6;
  char *pcVar7;
  long lVar8;
  
joined_r0x0017f1b4:
  do {
    if (param_1 == (uint *)0x0) {
      sVar4 = fwrite("<null>",1,6,param_2);
      return sVar4;
    }
    uVar2 = *param_1;
    if (uVar2 == 0x11) {
LAB_0017f3c8:
      __fprintf_chk(param_2,2,&DAT_001fad78,param_1 + 0x26);
      if (param_1[0x4a] != 0) {
        lVar8 = 0;
        do {
          lVar5 = *(long *)(param_1 + 0x48);
          while( true ) {
            lVar1 = lVar8 * 8;
            lVar8 = lVar8 + 1;
            dump_expr(*(undefined8 *)(lVar5 + lVar1),param_2);
            if (param_1[0x4a] <= (uint)lVar8) goto LAB_0017f350;
            if ((uint)lVar8 == 0) break;
            fwrite(", ",1,2,param_2);
            lVar5 = *(long *)(param_1 + 0x48);
          }
        } while( true );
      }
      goto LAB_0017f350;
    }
    if (uVar2 < 0x12) {
      if (uVar2 == 0xe) {
        if ((char)param_1[0x2a] == '\0') {
          sVar4 = __fprintf_chk(param_2,2,&DAT_001fad70,*(undefined8 *)(param_1 + 0x26));
          return sVar4;
        }
        sVar4 = __fprintf_chk(*(undefined8 *)(param_1 + 0x28),param_2,2,&DAT_001fad68);
        return sVar4;
      }
      if (uVar2 < 0xf) {
        if (uVar2 != 0xc) {
          if (uVar2 == 0xd) {
            uVar2 = fputs((char *)(param_1 + 0x27),param_2);
            return (ulong)uVar2;
          }
LAB_0017f4bc:
          uVar6 = hir_node_kind_str();
          sVar4 = __fprintf_chk(param_2,2,&DAT_001fad90,uVar6);
          return sVar4;
        }
        goto LAB_0017f3c8;
      }
      if (uVar2 == 0xf) {
        fputc(0x28,param_2);
        dump_expr(*(undefined8 *)(param_1 + 0x26),param_2);
        switch(param_1[0x2a]) {
        case 2:
          pcVar7 = "+";
          break;
        case 3:
          pcVar7 = "-";
          break;
        case 4:
          pcVar7 = "*";
          break;
        case 5:
          pcVar7 = "/";
          break;
        case 6:
          pcVar7 = "&";
          break;
        case 7:
          pcVar7 = "|";
          break;
        case 8:
          pcVar7 = "^";
          break;
        case 9:
          pcVar7 = "<<";
          break;
        case 10:
          pcVar7 = ">>";
          break;
        case 0xb:
          pcVar7 = "==";
          break;
        case 0xc:
          pcVar7 = "!=";
          break;
        case 0xd:
        case 0xf:
          pcVar7 = "<";
          break;
        case 0xe:
        case 0x10:
          pcVar7 = "<=";
          break;
        case 0x11:
        case 0x13:
          pcVar7 = ">";
          break;
        case 0x12:
        case 0x14:
          pcVar7 = ">=";
          break;
        default:
          pcVar7 = "?";
        }
        __fprintf_chk(param_2,2,&DAT_001f8320,pcVar7);
        dump_expr(*(undefined8 *)(param_1 + 0x28),param_2);
LAB_0017f350:
        uVar2 = fputc(0x29,param_2);
        return (ulong)uVar2;
      }
      uVar2 = param_1[0x28];
      if (uVar2 == 2) {
        puVar3 = &DAT_001fad48;
      }
      else if (uVar2 < 3) {
        puVar3 = &DAT_001f8278;
        if (uVar2 != 0) {
          puVar3 = &DAT_001fad40;
        }
      }
      else if (uVar2 == 3) {
        puVar3 = &DAT_001f8280;
      }
      else {
        puVar3 = &DAT_001f8290;
        if (uVar2 != 4) {
          puVar3 = &DAT_001f82d8;
        }
      }
      fwrite(puVar3,1,1,param_2);
      param_1 = *(uint **)(param_1 + 0x26);
      goto joined_r0x0017f1b4;
    }
    if (uVar2 == 0x14) {
      dump_expr(*(undefined8 *)(param_1 + 0x26),param_2);
      fputc(0x5b,param_2);
      dump_expr(*(undefined8 *)(param_1 + 0x28),param_2);
      uVar2 = fputc(0x5d,param_2);
      return (ulong)uVar2;
    }
    if (0x14 < uVar2) {
      if (uVar2 == 0x15) {
        fputc(0x28,param_2);
        dump_expr(*(undefined8 *)(param_1 + 0x26),param_2);
        fwrite(&DAT_001f8318,1,3,param_2);
        dump_expr(*(undefined8 *)(param_1 + 0x28),param_2);
        fwrite(&DAT_001f7310,1,3,param_2);
        dump_expr(*(undefined8 *)(param_1 + 0x2a),param_2);
        uVar2 = fputc(0x29,param_2);
        return (ulong)uVar2;
      }
      goto LAB_0017f4bc;
    }
    if (uVar2 != 0x12) {
      dump_expr(*(undefined8 *)(param_1 + 0x26),param_2);
      puVar3 = &DAT_001fad58;
      if ((char)param_1[0x3a] != '\0') {
        puVar3 = &DAT_001fad50;
      }
      sVar4 = __fprintf_chk(param_2,2,&DAT_001fad88,puVar3,param_1 + 0x28);
      return sVar4;
    }
    __fprintf_chk(param_2,2,&DAT_001fad80,param_1 + 0x28);
    param_1 = *(uint **)(param_1 + 0x26);
  } while( true );
}

