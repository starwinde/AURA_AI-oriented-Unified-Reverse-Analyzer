
void FUN_001dbfb4(long param_1,undefined8 param_2,undefined8 param_3,long param_4,
                 undefined2 *param_5,undefined8 param_6)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  undefined8 uVar7;
  char cVar8;
  undefined2 uVar9;
  uint uVar10;
  void *__s;
  byte *pbVar11;
  long lVar12;
  long lVar13;
  long lVar14;
  ulong uVar15;
  ulong uVar16;
  undefined8 local_138;
  undefined8 uStack_130;
  undefined8 local_128;
  undefined8 local_120;
  undefined8 uStack_118;
  ulong local_110;
  undefined8 local_108;
  undefined8 local_100;
  undefined8 uStack_f8;
  undefined8 local_f0;
  undefined8 local_e8;
  undefined8 local_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 local_c0;
  undefined8 uStack_b8;
  undefined8 local_b0;
  undefined8 local_a8;
  undefined8 local_a0;
  ulong uStack_98;
  long local_90;
  undefined8 local_88;
  undefined8 local_80;
  ulong auStack_78 [3];
  undefined8 local_60;
  uint uStack_5c;
  ulong uStack_58;
  long local_50;
  long local_48;
  
  local_48 = *(long *)PTR___stack_chk_guard_005ffe88;
  __s = *(void **)(*(long *)(param_4 + 0x310) + 0xf0);
  local_50 = 0;
  uStack_118 = 0;
  local_120 = 0;
  local_108 = 0;
  local_110 = 0;
  uStack_f8 = 0;
  local_100 = 0;
  local_e8 = 0;
  local_f0 = 0;
  uStack_d8 = 0;
  local_e0 = 0;
  uStack_c8 = 0;
  uStack_d0 = 0;
  uStack_b8 = 0;
  local_c0 = 0;
  local_a8 = 0;
  local_b0 = 0;
  uStack_98 = 0;
  local_a0 = 0;
  local_88 = 0;
  local_90 = 0;
  auStack_78[0] = 0;
  local_80 = 0;
  auStack_78[2] = 0;
  auStack_78[1] = 0;
  uStack_58 = 0;
  local_60 = 0;
  local_138 = param_2;
  uStack_130 = param_3;
  local_128 = param_6;
  if (__s != (void *)0x0) {
    memset(__s,0,0x230);
  }
  if ((*(uint *)(param_1 + 4) >> 1 & 1) == 0) {
    if ((*(uint *)(param_1 + 4) >> 2 & 1) == 0) {
      iVar4 = FUN_001df554(&local_120,FUN_001dbf20,&local_138,param_6,2);
    }
    else {
      iVar4 = FUN_001df554(&local_120,FUN_001dbf20,&local_138,param_6,1);
    }
  }
  else {
    iVar4 = FUN_001df554(&local_120,FUN_001dbf20,&local_138,param_6,0);
  }
  if ((iVar4 == 0) && (*param_5 = (short)local_b0, local_90 != 0)) {
    FUN_0018ff00(param_4);
    FUN_0018ff90(param_4,uStack_98 & 0xffff);
    if (local_f0._6_1_ != '\0') {
      iVar4 = FUN_0018ffb0(param_4);
      if (iVar4 == 0x925) {
        FUN_0018ff90(param_4,0x3ba3);
      }
      else {
        iVar4 = FUN_0018ffb0(param_4);
        if (iVar4 == 0x924) {
          FUN_0018ff90(param_4,0x3b5c);
        }
      }
    }
    lVar12 = 0;
    local_80._0_3_ = (uint3)(ushort)local_80;
LAB_001dc100:
    cVar8 = *(char *)(local_50 + lVar12);
    lVar13 = lVar12;
    if (cVar8 != '\0') {
LAB_001dc110:
      pbVar11 = (byte *)(local_50 + lVar13);
      switch(cVar8) {
      case '\x01':
        goto switchD_001dc130_caseD_1;
      case '\x02':
      case '\x03':
      case '\x04':
      case '\x05':
      case '\x06':
      case '\a':
      case '\b':
      case '\t':
      case '\n':
      case '\v':
      case '\f':
      case '\r':
      case '\x0e':
      case '\x0f':
        goto switchD_001dc130_caseD_2;
      case '\x10':
        FUN_00190100(param_4,*(undefined2 *)(&DAT_00361b80 + (local_88 & 0xffffffff) * 2));
        break;
      case '\x11':
        if (7 < (local_88._4_4_ & 0xff)) goto switchD_001dc130_default;
        FUN_00190100(param_4,(local_88._4_4_ & 0xff) + 0x6d);
        break;
      case '\x12':
      case '\x13':
      case '\x14':
      case '\x15':
      case '\x1b':
      case '\x1c':
        bVar3 = local_80._2_1_;
        local_80._0_3_ = CONCAT12(local_80._2_1_ + 1,(ushort)local_80);
        bVar1 = pbVar11[1];
        bVar2 = *pbVar11;
        uVar15 = auStack_78[bVar3];
        uVar16 = uVar15;
        if (bVar1 == 1) {
          if (bVar2 == 0x14) goto LAB_001dc6e8;
          if (bVar2 < 0x15) {
            if (bVar2 != 0x12) {
              if (bVar2 == 0x13) goto LAB_001dc584;
LAB_001dc624:
              FUN_00190140(param_4,uVar15);
              break;
            }
LAB_001dc6d8:
            uVar16 = uVar15 | 0xffffffffffffff00;
            if ((uVar15 & 0x80) == 0) {
              uVar16 = uVar15;
            }
          }
          else {
            if (bVar2 != 0x1b) goto LAB_001dc624;
            uVar6 = (uint)uVar15;
            if (local_a8._6_1_ == '\x02') {
              if ((uVar6 >> 0xf & 1) != 0) {
                uVar16 = uVar15 | 0xffffffffffff0000;
              }
            }
            else if (local_a8._6_1_ == '\x04') {
              if ((int)uVar6 < 0) {
                uVar16 = uVar15 | 0xffffffff00000000;
              }
            }
            else {
              if (local_a8._6_1_ != '\x01') goto LAB_001dc624;
              if ((uVar6 >> 7 & 1) != 0) {
                uVar16 = uVar15 | 0xffffffffffffff00;
              }
            }
          }
        }
        else {
          if (bVar1 != 6) {
            if (bVar1 == 7) {
              if (uVar15 < 8) {
                FUN_00190140(param_4,uVar15);
                break;
              }
              uVar6 = FUN_0018ffb0(param_4);
              if (0x2559 < uVar6) goto LAB_001dc624;
              if (uVar6 < 0x24ff) {
                if (uVar6 == 0x2b0) {
                  uVar9 = 0x2b2;
                }
                else if (uVar6 < 0x2b1) {
                  if (uVar6 == 0x2ab) {
                    uVar9 = 0x2ac;
                  }
                  else if (uVar6 < 0x2ac) {
                    if (uVar6 == 0x2a7) {
                      uVar9 = 0x2a8;
                    }
                    else {
                      uVar9 = 0x2aa;
                      if (uVar6 != 0x2a9) goto LAB_001dc624;
                    }
                  }
                  else {
                    uVar9 = 0x2ae;
                    if (uVar6 != 0x2ad) goto LAB_001dc624;
                  }
                }
                else if (uVar6 == 0x2b8) {
                  uVar9 = 0x2ba;
                }
                else if (uVar6 == 699) {
                  uVar9 = 0x2bd;
                }
                else {
                  if (uVar6 != 0x2b3) goto LAB_001dc624;
                  uVar9 = 0x2b5;
                }
              }
              else {
                switch(uVar6) {
                case 0x24ff:
                  uVar9 = 0x2500;
                  break;
                default:
                  FUN_00190140(param_4,uVar15);
                  goto LAB_001dc0f4;
                case 0x2501:
                  uVar9 = 0x2502;
                  break;
                case 0x2503:
                  uVar9 = 0x2504;
                  break;
                case 0x2505:
                  uVar9 = 0x2506;
                  break;
                case 0x2543:
                  uVar9 = 0x2544;
                  break;
                case 0x2545:
                  uVar9 = 0x2546;
                  break;
                case 0x2547:
                  uVar9 = 0x2548;
                  break;
                case 0x2549:
                  uVar9 = 0x254a;
                  break;
                case 0x254b:
                  uVar9 = 0x254c;
                  break;
                case 0x254d:
                  uVar9 = 0x254e;
                  break;
                case 0x254f:
                  uVar9 = 0x2550;
                  break;
                case 0x2551:
                  uVar9 = 0x2552;
                  break;
                case 0x2553:
                  uVar9 = 0x2554;
                  break;
                case 0x2555:
                  uVar9 = 0x2556;
                  break;
                case 0x2557:
                  uVar9 = 0x2558;
                  break;
                case 0x2559:
                  uVar9 = 0x255a;
                }
              }
            }
            else if (bVar1 == 8) {
              if (uVar15 < 0x20) {
                FUN_00190140(param_4,uVar15);
                break;
              }
              uVar5 = FUN_0018ffb0(param_4);
              switch(uVar5) {
              case 0xd4e:
                uVar9 = 0xd4f;
                break;
              default:
                FUN_00190140(param_4,uVar15);
                goto LAB_001dc0f4;
              case 0xd50:
                uVar9 = 0xd51;
                break;
              case 0xd56:
                uVar9 = 0xd57;
                break;
              case 0xd5a:
                uVar9 = 0xd5b;
                break;
              case 0xd62:
                uVar9 = 0xd63;
                break;
              case 0xd66:
                uVar9 = 0xd67;
                break;
              case 0xd6e:
                uVar9 = 0xd6f;
                break;
              case 0xd72:
                uVar9 = 0xd73;
                break;
              case 0xd75:
                uVar9 = 0xd76;
                break;
              case 0xd7a:
                uVar9 = 0xd7b;
                break;
              case 0xd7c:
                uVar9 = 0xd7d;
                break;
              case 0xd7e:
                uVar9 = 0xd7f;
                break;
              case 0xd80:
                uVar9 = 0xd81;
                break;
              case 0xd86:
                uVar9 = 0xd87;
                break;
              case 0xd8a:
                uVar9 = 0xd8b;
                break;
              case 0xd92:
                uVar9 = 0xd93;
                break;
              case 0xd96:
                uVar9 = 0xd97;
                break;
              case 0xd9e:
                uVar9 = 0xd9f;
                break;
              case 0xda2:
                uVar9 = 0xda3;
                break;
              case 0xda5:
                uVar9 = 0xda6;
                break;
              case 0xdaa:
                uVar9 = 0xdab;
                break;
              case 0xdac:
                uVar9 = 0xdad;
                break;
              case 0xdaf:
                uVar9 = 0xdb1;
                break;
              case 0xdb4:
                uVar9 = 0xdba;
                break;
              case 0xdb6:
                uVar9 = 0xdb8;
                break;
              case 0xdbc:
                uVar9 = 0xdbe;
                break;
              case 0xdbf:
                uVar9 = 0xdc1;
                break;
              case 0xdc3:
                uVar9 = 0xdc5;
                break;
              case 0xdc8:
                uVar9 = 0xdce;
                break;
              case 0xdca:
                uVar9 = 0xdcc;
                break;
              case 0xdd0:
                uVar9 = 0xdd2;
                break;
              case 0xdd3:
                uVar9 = 0xdd5;
              }
            }
            else {
              if (bVar1 != 9) {
                if (bVar1 == 0x15) {
                  FUN_00190100(param_4,((uint)(uVar15 >> 4) & 0xfffffff) + 0xad);
                }
                else if (bVar1 == 0x16) {
                  FUN_00190100(param_4,((uint)(uVar15 >> 4) & 0xfffffff) + 0xcd);
                }
                else if (bVar1 == 0x14) {
                  FUN_00190100(param_4,((uint)(uVar15 >> 4) & 0xfffffff) + 0x8d);
                }
                else {
                  FUN_00190140(param_4,uVar15);
                  if (bVar1 == 0x11) {
                    FUN_00190100(param_4,(&DAT_00361e40)[uStack_118 & 0xffffffff]);
                  }
                }
                break;
              }
              if ((uVar15 < 8) && ((uVar15 & 3) != 3)) goto LAB_001dc590;
              iVar4 = FUN_0018ffb0(param_4);
              uVar9 = 0x2370;
              if (iVar4 - 0x2371U < 0x18d) {
                uVar9 = *(undefined2 *)(&DAT_00361e48 + (ulong)(iVar4 - 0x2371U) * 2);
              }
            }
            FUN_0018ff90(param_4,uVar9);
            goto LAB_001dc590;
          }
          if (bVar2 == 0x13) {
LAB_001dc584:
            uVar16 = uVar15 | 0xffffffffffff0000;
            if ((uVar15 & 0x8000) == 0) {
              uVar16 = uVar15;
            }
            goto LAB_001dc590;
          }
          if (bVar2 != 0x14) {
            if (bVar2 == 0x12) goto LAB_001dc6d8;
            goto LAB_001dc624;
          }
LAB_001dc6e8:
          uVar16 = uVar15 | 0xffffffff00000000;
          if ((uVar15 & 0x80000000) == 0) {
            uVar16 = uVar15;
          }
        }
LAB_001dc590:
        FUN_00190140(param_4,uVar16);
        break;
      case '\x16':
      case '\x17':
      case '\x18':
      case '\x19':
      case '\x1e':
        FUN_00190100(param_4,*(undefined2 *)(&DAT_00361b80 + (auStack_78[2] & 0xffffffff) * 2));
        break;
      case '\x1a':
        FUN_00190100(param_4,((byte)local_80 & 7) + 0x85);
        break;
      case '\x1d':
        FUN_00190140(param_4,local_f0._4_1_);
        break;
      case '\x1f':
        lVar13 = (ulong)pbVar11[1] * 2 + -0x3c;
        cVar8 = *(char *)(local_50 + lVar13);
        goto LAB_001dc110;
      case ' ':
        if ((int)local_c0 == 2) {
          uVar5 = 0x20;
          if ((local_f0 & 0x100000000000000) == 0) {
            uVar5 = 0x37;
          }
        }
        else if ((int)local_c0 == 1) {
          uVar5 = 0x39;
          if ((local_f0 & 0x100000000000000) == 0) {
            uVar5 = 0x20;
          }
        }
        else {
          uVar5 = 0x20;
          if ((local_f0 & 0x100000000000000) == 0) {
            uVar5 = 0x39;
          }
        }
        FUN_00190100(param_4,uVar5);
        FUN_00190100(param_4,(&DAT_00361e40)[uStack_118 & 0xffffffff]);
        break;
      case '!':
        if ((int)local_c0 == 2) {
          uVar5 = 0x1a;
          if ((local_f0 & 0x100000000000000) == 0) {
            uVar5 = 0x33;
          }
        }
        else if ((int)local_c0 == 1) {
          uVar5 = 0x10;
          if ((local_f0 & 0x100000000000000) == 0) {
            uVar5 = 0x1a;
          }
        }
        else {
          uVar5 = 0x1a;
          if ((local_f0 & 0x100000000000000) == 0) {
            uVar5 = 0x10;
          }
        }
        FUN_00190100(param_4,uVar5);
        break;
      default:
        goto switchD_001dc130_default;
      }
    }
    goto LAB_001dc0f4;
  }
switchD_001dc130_default:
  uVar7 = 0;
LAB_001dc06c:
  if (local_48 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(uVar7,PTR___stack_chk_guard_005ffe88,0,
                   local_48 - *(long *)PTR___stack_chk_guard_005ffe88);
switchD_001dc130_caseD_2:
  bVar1 = pbVar11[1];
  if (bVar1 < 0xf) {
    if (10 < bVar1) {
      if ((uStack_5c - 0x15 & 0xffffffef) == 0) {
        if ((uint)local_f0 != 0) {
          if ((uint)local_f0 - 1 < 0x20) {
                    /* WARNING: Could not recover jumptable at 0x001dc308. Too many branches */
                    /* WARNING: Treating indirect jump as call */
            (*(code *)((long)*(short *)(&DAT_003614c4 + (ulong)((uint)local_f0 - 1) * 2) * 4 +
                      0x1dc30c))();
            return;
          }
          goto switchD_001dc130_default;
        }
        FUN_00190100(param_4,0);
        cVar8 = uStack_f8._4_1_;
        if ((int)uStack_f8 != 0) {
          if ((int)uStack_f8 - 0x11U < 0x80) {
            iVar4 = (int)*(short *)(&DAT_00361d40 + (ulong)((int)uStack_f8 - 0x11U) * 2);
            goto LAB_001dc684;
          }
          goto switchD_001dc130_default;
        }
        if (uStack_f8._4_1_ == '\x01') {
          iVar4 = 0;
          if ((uint)local_f0 == 0) {
            if ((int)local_c0 != 2) goto LAB_001dc830;
          }
          else if (((uint)local_f0 != 5) &&
                  ((0x1d < (uint)local_f0 || ((0x20202000UL >> (local_f0 & 0x3f) & 1) == 0))))
          goto LAB_001dc830;
        }
        else {
LAB_001dc830:
          iVar4 = 0x36;
          if (local_a8._5_1_ == '\x04') {
            iVar4 = 0x1e;
          }
        }
      }
      else {
        if (uStack_5c == 2) {
          uVar7 = 9;
LAB_001dc788:
          FUN_00190100(param_4,uVar7);
          iVar4 = 0x10;
          cVar8 = '\x01';
          goto LAB_001dc684;
        }
        if (uStack_5c < 3) {
          uVar7 = 9;
          if (uStack_5c == 0) {
            if ((int)uStack_58 == 0) goto switchD_001dc130_default;
            if ((int)local_c0 == 2) {
              if (local_120._4_1_ != 'g') {
                uVar5 = 0x35;
                if (local_a8._5_1_ == '\x04') {
                  uVar5 = 0x1d;
                }
                FUN_00190100(param_4,uVar5);
                iVar4 = 0;
                cVar8 = '\x01';
                goto LAB_001dc684;
              }
              FUN_00190100(param_4,0x1d);
            }
            else {
              FUN_00190100(param_4,0);
            }
LAB_001dc9f8:
            iVar4 = 0;
            cVar8 = '\x01';
            goto LAB_001dc684;
          }
        }
        else {
          if (uStack_5c != 3) {
            uVar7 = 6;
            if (uStack_5c == 4) goto LAB_001dc788;
            switch(uStack_5c) {
            case 5:
              FUN_00190100(param_4,0x39);
              break;
            case 6:
              FUN_00190100(param_4,0x10);
              break;
            case 7:
              FUN_00190100(param_4,6);
              break;
            case 8:
              FUN_00190100(param_4,9);
              break;
            case 9:
              FUN_00190100(param_4,0x105);
              break;
            case 10:
              FUN_00190100(param_4,0x106);
              break;
            case 0xb:
              FUN_00190100(param_4,0x107);
              break;
            case 0xc:
              FUN_00190100(param_4,0x108);
              break;
            case 0xd:
              FUN_00190100(param_4,0x109);
              break;
            case 0xe:
              FUN_00190100(param_4,0x10a);
              break;
            case 0xf:
              FUN_00190100(param_4,0x10b);
              break;
            case 0x10:
              FUN_00190100(param_4,0x10c);
              break;
            case 0x11:
              FUN_00190100(param_4,0x16);
              break;
            case 0x12:
              FUN_00190100(param_4,0x19);
              break;
            case 0x13:
              FUN_00190100(param_4,0x1b);
              break;
            case 0x14:
              FUN_00190100(param_4,0x18);
              break;
            case 0x15:
              FUN_00190100(param_4,0x1f8);
              break;
            case 0x16:
              FUN_00190100(param_4,0x17);
              break;
            case 0x17:
              FUN_00190100(param_4,0x20);
              break;
            case 0x18:
              FUN_00190100(param_4,0x1a);
              break;
            case 0x19:
              FUN_00190100(param_4,0xfd);
              break;
            case 0x1a:
              FUN_00190100(param_4,0xfe);
              break;
            case 0x1b:
              FUN_00190100(param_4,0xff);
              break;
            case 0x1c:
              FUN_00190100(param_4,0x100);
              break;
            case 0x1d:
              FUN_00190100(param_4,0x101);
              break;
            case 0x1e:
              FUN_00190100(param_4,0x102);
              break;
            case 0x1f:
              FUN_00190100(param_4,0x103);
              break;
            case 0x20:
              FUN_00190100(param_4,0x104);
              break;
            case 0x21:
              FUN_00190100(param_4,0x2f);
              break;
            case 0x22:
              FUN_00190100(param_4,0x32);
              break;
            case 0x23:
              FUN_00190100(param_4,0x34);
              break;
            case 0x24:
              FUN_00190100(param_4,0x31);
              break;
            case 0x25:
              FUN_00190100(param_4,0x1f9);
              break;
            case 0x26:
              FUN_00190100(param_4,0x30);
              break;
            case 0x27:
              FUN_00190100(param_4,0x37);
              break;
            case 0x28:
              FUN_00190100(param_4,0x33);
              break;
            case 0x29:
              FUN_00190100(param_4,0x7d);
              break;
            case 0x2a:
              FUN_00190100(param_4,0x7e);
              break;
            case 0x2b:
              FUN_00190100(param_4,0x7f);
              break;
            case 0x2c:
              FUN_00190100(param_4,0x80);
              break;
            case 0x2d:
              FUN_00190100(param_4,0x81);
              break;
            case 0x2e:
              FUN_00190100(param_4,0x82);
              break;
            case 0x2f:
              FUN_00190100(param_4,0x83);
              break;
            case 0x30:
              FUN_00190100(param_4,0x84);
              break;
            default:
              goto switchD_001dc130_default;
            }
            goto LAB_001dc9f8;
          }
          uVar7 = 6;
        }
        FUN_00190100(param_4,uVar7);
        iVar4 = 0x39;
        cVar8 = '\x01';
      }
LAB_001dc684:
      FUN_00190140(param_4,cVar8);
      FUN_00190100(param_4,iVar4);
      FUN_00190140(param_4,local_108);
      FUN_00190100(param_4,(&DAT_00361e40)[uStack_118 & 0xffffffff]);
      goto LAB_001dc0f4;
    }
    bVar1 = bVar1 - 2;
joined_r0x001dc654:
    if (3 < bVar1) goto switchD_001dc130_default;
  }
  else {
    if (0x17 < bVar1) {
      bVar1 = bVar1 - 0x19;
      goto joined_r0x001dc654;
    }
    if (bVar1 < 0x13) goto switchD_001dc130_default;
  }
  if ((uStack_5c - 0x15 & 0xffffffef) == 0) goto switchD_001dc130_default;
  switch(uStack_5c) {
  case 0x31:
    FUN_00190100(param_4,2);
    break;
  case 0x32:
    FUN_00190100(param_4,0xb);
    break;
  case 0x33:
    FUN_00190100(param_4,0x13);
    break;
  case 0x34:
    FUN_00190100(param_4,5);
    break;
  case 0x35:
    FUN_00190100(param_4,1);
    break;
  case 0x36:
    FUN_00190100(param_4,10);
    break;
  case 0x37:
    FUN_00190100(param_4,0xf);
    break;
  case 0x38:
    FUN_00190100(param_4,4);
    break;
  case 0x39:
    FUN_00190100(param_4,0xed);
    break;
  case 0x3a:
    FUN_00190100(param_4,0xee);
    break;
  case 0x3b:
    FUN_00190100(param_4,0xef);
    break;
  case 0x3c:
    FUN_00190100(param_4,0xf0);
    break;
  case 0x3d:
    FUN_00190100(param_4,0xf1);
    break;
  case 0x3e:
    FUN_00190100(param_4,0xf2);
    break;
  case 0x3f:
    FUN_00190100(param_4,0xf3);
    break;
  case 0x40:
    FUN_00190100(param_4,0xf4);
    break;
  case 0x41:
    FUN_00190100(param_4,0x3e);
    break;
  case 0x42:
    FUN_00190100(param_4,8);
    break;
  case 0x43:
    FUN_00190100(param_4,0x3b);
    break;
  case 0x44:
    FUN_00190100(param_4,0x12);
    break;
  case 0x45:
    FUN_00190100(param_4,3);
    break;
  case 0x46:
    FUN_00190100(param_4,0xd);
    break;
  case 0x47:
    FUN_00190100(param_4,0x15);
    break;
  case 0x48:
    FUN_00190100(param_4,9);
    break;
  case 0x49:
    FUN_00190100(param_4,0x3c);
    break;
  case 0x4a:
    FUN_00190100(param_4,6);
    break;
  case 0x4b:
    FUN_00190100(param_4,0x39);
    break;
  case 0x4c:
    FUN_00190100(param_4,0x10);
    break;
  case 0x4d:
    FUN_00190100(param_4,0x105);
    break;
  case 0x4e:
    FUN_00190100(param_4,0x106);
    break;
  case 0x4f:
    FUN_00190100(param_4,0x107);
    break;
  case 0x50:
    FUN_00190100(param_4,0x108);
    break;
  case 0x51:
    FUN_00190100(param_4,0x109);
    break;
  case 0x52:
    FUN_00190100(param_4,0x10a);
    break;
  case 0x53:
    FUN_00190100(param_4,0x10b);
    break;
  case 0x54:
    FUN_00190100(param_4,0x10c);
    break;
  case 0x55:
    FUN_00190100(param_4,0x16);
    break;
  case 0x56:
    FUN_00190100(param_4,0x19);
    break;
  case 0x57:
    FUN_00190100(param_4,0x1b);
    break;
  case 0x58:
    FUN_00190100(param_4,0x18);
    break;
  case 0x59:
    FUN_00190100(param_4,0x21);
    break;
  case 0x5a:
    FUN_00190100(param_4,0x17);
    break;
  case 0x5b:
    FUN_00190100(param_4,0x20);
    break;
  case 0x5c:
    FUN_00190100(param_4,0x1a);
    break;
  case 0x5d:
    FUN_00190100(param_4,0xfd);
    break;
  case 0x5e:
    FUN_00190100(param_4,0xfe);
    break;
  case 0x5f:
    FUN_00190100(param_4,0xff);
    break;
  case 0x60:
    FUN_00190100(param_4,0x100);
    break;
  case 0x61:
    FUN_00190100(param_4,0x101);
    break;
  case 0x62:
    FUN_00190100(param_4,0x102);
    break;
  case 99:
    FUN_00190100(param_4,0x103);
    break;
  case 100:
    FUN_00190100(param_4,0x104);
    break;
  case 0x65:
    FUN_00190100(param_4,0x2f);
    break;
  case 0x66:
    FUN_00190100(param_4,0x32);
    break;
  case 0x67:
    FUN_00190100(param_4,0x34);
    break;
  case 0x68:
    FUN_00190100(param_4,0x31);
    break;
  case 0x69:
    FUN_00190100(param_4,0x38);
    break;
  case 0x6a:
    FUN_00190100(param_4,0x30);
    break;
  case 0x6b:
    FUN_00190100(param_4,0x37);
    break;
  case 0x6c:
    FUN_00190100(param_4,0x33);
    break;
  case 0x6d:
    FUN_00190100(param_4,0x7d);
    break;
  case 0x6e:
    FUN_00190100(param_4,0x7e);
    break;
  case 0x6f:
    FUN_00190100(param_4,0x7f);
    break;
  case 0x70:
    FUN_00190100(param_4,0x80);
    break;
  case 0x71:
    FUN_00190100(param_4,0x81);
    break;
  case 0x72:
    FUN_00190100(param_4,0x82);
    break;
  case 0x73:
    FUN_00190100(param_4,0x83);
    break;
  case 0x74:
    FUN_00190100(param_4,0x84);
    break;
  case 0x75:
    FUN_00190100(param_4,0x75);
    break;
  case 0x76:
    FUN_00190100(param_4,0x76);
    break;
  case 0x77:
    FUN_00190100(param_4,0x77);
    break;
  case 0x78:
    FUN_00190100(param_4,0x78);
    break;
  case 0x79:
    FUN_00190100(param_4,0x79);
    break;
  case 0x7a:
    FUN_00190100(param_4,0x7a);
    break;
  case 0x7b:
    FUN_00190100(param_4,0x7b);
    break;
  case 0x7c:
    FUN_00190100(param_4,0x7c);
    break;
  case 0x7d:
    FUN_00190100(param_4,0x8d);
    break;
  case 0x7e:
    FUN_00190100(param_4,0x8e);
    break;
  case 0x7f:
    FUN_00190100(param_4,0x8f);
    break;
  case 0x80:
    FUN_00190100(param_4,0x90);
    break;
  case 0x81:
    FUN_00190100(param_4,0x91);
    break;
  case 0x82:
    FUN_00190100(param_4,0x92);
    break;
  case 0x83:
    FUN_00190100(param_4,0x93);
    break;
  case 0x84:
    FUN_00190100(param_4,0x94);
    break;
  case 0x85:
    FUN_00190100(param_4,0x95);
    break;
  case 0x86:
    FUN_00190100(param_4,0x96);
    break;
  case 0x87:
    FUN_00190100(param_4,0x97);
    break;
  case 0x88:
    FUN_00190100(param_4,0x98);
    break;
  case 0x89:
    FUN_00190100(param_4,0x99);
    break;
  case 0x8a:
    FUN_00190100(param_4,0x9a);
    break;
  case 0x8b:
    FUN_00190100(param_4,0x9b);
    break;
  case 0x8c:
    FUN_00190100(param_4,0x9c);
    break;
  case 0x8d:
    FUN_00190100(param_4,0x9d);
    break;
  case 0x8e:
    FUN_00190100(param_4,0x9e);
    break;
  case 0x8f:
    FUN_00190100(param_4,0x9f);
    break;
  case 0x90:
    FUN_00190100(param_4,0xa0);
    break;
  case 0x91:
    FUN_00190100(param_4,0xa1);
    break;
  case 0x92:
    FUN_00190100(param_4,0xa2);
    break;
  case 0x93:
    FUN_00190100(param_4,0xa3);
    break;
  case 0x94:
    FUN_00190100(param_4,0xa4);
    break;
  case 0x95:
    FUN_00190100(param_4,0xa5);
    break;
  case 0x96:
    FUN_00190100(param_4,0xa6);
    break;
  case 0x97:
    FUN_00190100(param_4,0xa7);
    break;
  case 0x98:
    FUN_00190100(param_4,0xa8);
    break;
  case 0x99:
    FUN_00190100(param_4,0xa9);
    break;
  case 0x9a:
    FUN_00190100(param_4,0xaa);
    break;
  case 0x9b:
    FUN_00190100(param_4,0xab);
    break;
  case 0x9c:
    FUN_00190100(param_4,0xac);
    break;
  case 0x9d:
    FUN_00190100(param_4,0xad);
    break;
  case 0x9e:
    FUN_00190100(param_4,0xae);
    break;
  case 0x9f:
    FUN_00190100(param_4,0xaf);
    break;
  case 0xa0:
    FUN_00190100(param_4,0xb0);
    break;
  case 0xa1:
    FUN_00190100(param_4,0xb1);
    break;
  case 0xa2:
    FUN_00190100(param_4,0xb2);
    break;
  case 0xa3:
    FUN_00190100(param_4,0xb3);
    break;
  case 0xa4:
    FUN_00190100(param_4,0xb4);
    break;
  case 0xa5:
    FUN_00190100(param_4,0xb5);
    break;
  case 0xa6:
    FUN_00190100(param_4,0xb6);
    break;
  case 0xa7:
    FUN_00190100(param_4,0xb7);
    break;
  case 0xa8:
    FUN_00190100(param_4,0xb8);
    break;
  case 0xa9:
    FUN_00190100(param_4,0xb9);
    break;
  case 0xaa:
    FUN_00190100(param_4,0xba);
    break;
  case 0xab:
    FUN_00190100(param_4,0xbb);
    break;
  case 0xac:
    FUN_00190100(param_4,0xbc);
    break;
  case 0xad:
    FUN_00190100(param_4,0xbd);
    break;
  case 0xae:
    FUN_00190100(param_4,0xbe);
    break;
  case 0xaf:
    FUN_00190100(param_4,0xbf);
    break;
  case 0xb0:
    FUN_00190100(param_4,0xc0);
    break;
  case 0xb1:
    FUN_00190100(param_4,0xc1);
    break;
  case 0xb2:
    FUN_00190100(param_4,0xc2);
    break;
  case 0xb3:
    FUN_00190100(param_4,0xc3);
    break;
  case 0xb4:
    FUN_00190100(param_4,0xc4);
    break;
  case 0xb5:
    FUN_00190100(param_4,0xc5);
    break;
  case 0xb6:
    FUN_00190100(param_4,0xc6);
    break;
  case 0xb7:
    FUN_00190100(param_4,199);
    break;
  case 0xb8:
    FUN_00190100(param_4,200);
    break;
  case 0xb9:
    FUN_00190100(param_4,0xc9);
    break;
  case 0xba:
    FUN_00190100(param_4,0xca);
    break;
  case 0xbb:
    FUN_00190100(param_4,0xcb);
    break;
  case 0xbc:
    FUN_00190100(param_4,0xcc);
    break;
  case 0xbd:
    FUN_00190100(param_4,0xcd);
    break;
  case 0xbe:
    FUN_00190100(param_4,0xce);
    break;
  case 0xbf:
    FUN_00190100(param_4,0xcf);
    break;
  case 0xc0:
    FUN_00190100(param_4,0xd0);
    break;
  case 0xc1:
    FUN_00190100(param_4,0xd1);
    break;
  case 0xc2:
    FUN_00190100(param_4,0xd2);
    break;
  case 0xc3:
    FUN_00190100(param_4,0xd3);
    break;
  case 0xc4:
    FUN_00190100(param_4,0xd4);
    break;
  case 0xc5:
    FUN_00190100(param_4,0xd5);
    break;
  case 0xc6:
    FUN_00190100(param_4,0xd6);
    break;
  case 199:
    FUN_00190100(param_4,0xd7);
    break;
  case 200:
    FUN_00190100(param_4,0xd8);
    break;
  case 0xc9:
    FUN_00190100(param_4,0xd9);
    break;
  case 0xca:
    FUN_00190100(param_4,0xda);
    break;
  case 0xcb:
    FUN_00190100(param_4,0xdb);
    break;
  case 0xcc:
    FUN_00190100(param_4,0xdc);
    break;
  case 0xcd:
    FUN_00190100(param_4,0xdd);
    break;
  case 0xce:
    FUN_00190100(param_4,0xde);
    break;
  case 0xcf:
    FUN_00190100(param_4,0xdf);
    break;
  case 0xd0:
    FUN_00190100(param_4,0xe0);
    break;
  case 0xd1:
    FUN_00190100(param_4,0xe1);
    break;
  case 0xd2:
    FUN_00190100(param_4,0xe2);
    break;
  case 0xd3:
    FUN_00190100(param_4,0xe3);
    break;
  case 0xd4:
    FUN_00190100(param_4,0xe4);
    break;
  case 0xd5:
    FUN_00190100(param_4,0xe5);
    break;
  case 0xd6:
    FUN_00190100(param_4,0xe6);
    break;
  case 0xd7:
    FUN_00190100(param_4,0xe7);
    break;
  case 0xd8:
    FUN_00190100(param_4,0xe8);
    break;
  case 0xd9:
    FUN_00190100(param_4,0xe9);
    break;
  case 0xda:
    FUN_00190100(param_4,0xea);
    break;
  case 0xdb:
    FUN_00190100(param_4,0xeb);
    break;
  case 0xdc:
    FUN_00190100(param_4,0xec);
    break;
  case 0xdd:
    FUN_00190100(param_4,0x6d);
    break;
  case 0xde:
    FUN_00190100(param_4,0x6e);
    break;
  case 0xdf:
    FUN_00190100(param_4,0x6f);
    break;
  case 0xe0:
    FUN_00190100(param_4,0x70);
    break;
  case 0xe1:
    FUN_00190100(param_4,0x71);
    break;
  case 0xe2:
    FUN_00190100(param_4,0x72);
    break;
  case 0xe3:
    FUN_00190100(param_4,0x73);
    break;
  case 0xe4:
    FUN_00190100(param_4,0x74);
    break;
  case 0xe5:
    FUN_00190100(param_4,0x1f);
    break;
  case 0xe6:
    FUN_00190100(param_4,0xc);
    break;
  case 0xe7:
    FUN_00190100(param_4,0x3f);
    break;
  case 0xe8:
    FUN_00190100(param_4,0x14);
    break;
  case 0xe9:
    FUN_00190100(param_4,0x23);
    break;
  case 0xea:
    FUN_00190100(param_4,0x24);
    break;
  case 0xeb:
    FUN_00190100(param_4,0x55);
    break;
  case 0xec:
    FUN_00190100(param_4,0x56);
    break;
  case 0xed:
    FUN_00190100(param_4,0x57);
    break;
  case 0xee:
    FUN_00190100(param_4,0x58);
    break;
  case 0xef:
    FUN_00190100(param_4,0x59);
    break;
  case 0xf0:
    FUN_00190100(param_4,0x5a);
    break;
  case 0xf1:
    FUN_00190100(param_4,0x5b);
    break;
  case 0xf2:
    FUN_00190100(param_4,0x5c);
    break;
  case 0xf3:
    FUN_00190100(param_4,0x5d);
    break;
  case 0xf4:
    FUN_00190100(param_4,0x5e);
    break;
  case 0xf5:
    FUN_00190100(param_4,0x5f);
    break;
  case 0xf6:
    FUN_00190100(param_4,0x60);
    break;
  case 0xf7:
    FUN_00190100(param_4,0x61);
    break;
  case 0xf8:
    FUN_00190100(param_4,0x62);
    break;
  case 0xf9:
    FUN_00190100(param_4,99);
    break;
  case 0xfa:
    FUN_00190100(param_4,100);
    break;
  case 0xfb:
    FUN_00190100(param_4,0x45);
    break;
  case 0xfc:
    FUN_00190100(param_4,0x46);
    break;
  case 0xfd:
    FUN_00190100(param_4,0x47);
    break;
  case 0xfe:
    FUN_00190100(param_4,0x48);
    break;
  case 0xff:
    FUN_00190100(param_4,0x49);
    break;
  case 0x100:
    FUN_00190100(param_4,0x4a);
    break;
  case 0x101:
    FUN_00190100(param_4,0x4b);
    break;
  case 0x102:
    FUN_00190100(param_4,0x4c);
    break;
  case 0x103:
    FUN_00190100(param_4,0x4d);
    break;
  case 0x104:
    FUN_00190100(param_4,0x4e);
    break;
  case 0x105:
    FUN_00190100(param_4,0x4f);
    break;
  case 0x106:
    FUN_00190100(param_4,0x50);
    break;
  case 0x107:
    FUN_00190100(param_4,0x51);
    break;
  case 0x108:
    FUN_00190100(param_4,0x52);
    break;
  case 0x109:
    FUN_00190100(param_4,0x53);
    break;
  case 0x10a:
    FUN_00190100(param_4,0x54);
    break;
  case 0x10b:
    FUN_00190100(param_4,0x41);
    break;
  case 0x10c:
    FUN_00190100(param_4,0x42);
    break;
  case 0x10d:
    FUN_00190100(param_4,0x43);
    break;
  case 0x10e:
    FUN_00190100(param_4,0x44);
    break;
  case 0x10f:
    FUN_00190100(param_4,0x35);
    break;
  default:
    goto switchD_001dc130_default;
  }
  goto LAB_001dc0f4;
switchD_001dc130_caseD_1:
  FUN_00190100(param_4,*(undefined2 *)(&DAT_00361b80 + (uStack_58 >> 0x20) * 2));
LAB_001dc0f4:
  lVar12 = lVar12 + 2;
  if (lVar12 == 0xc) goto LAB_001dc154;
  goto LAB_001dc100;
LAB_001dc154:
  *(undefined4 *)(param_4 + 0x330) = local_120._1_4_;
  *(undefined1 *)(param_4 + 0x334) = (undefined1)local_a0;
  *(char *)(param_4 + 0x3b8) = local_f0._6_1_;
  if (*(int *)(param_1 + 0x60) != 0) {
    lVar13 = *(long *)(param_4 + 0x310);
    lVar12 = *(long *)(lVar13 + 0xf0);
    if ((int)local_a8 == 0) {
      if ((char)local_100 == '\0') {
        *(char *)(lVar12 + 100) = local_a0._1_1_;
      }
      else {
        *(char *)(lVar12 + 100) = (char)local_100;
        if (local_100._1_1_ == '\0') {
          *(char *)(lVar12 + 0x65) = local_a0._1_1_;
        }
        else {
          *(char *)(lVar12 + 0x65) = local_100._1_1_;
          *(char *)(lVar12 + 0x66) = local_a0._1_1_;
        }
      }
    }
    else {
      *(undefined4 *)(lVar12 + 100) = local_e8._4_4_;
      lVar12 = *(long *)(lVar13 + 0xf0);
    }
    *(undefined1 *)(lVar12 + 0x228) = local_e0._2_1_;
    *(uint *)(lVar12 + 0x68) =
         CONCAT13(uStack_118._7_1_,
                  CONCAT12(uStack_118._5_1_,CONCAT11(local_a8._5_1_,local_120._5_1_)));
    uVar5 = FUN_001e5340(uStack_f8 & 0xffffffff);
    lVar14 = *(long *)(lVar13 + 0xf0);
    *(undefined4 *)(lVar12 + 0x78) = uVar5;
    *(char *)(lVar14 + 0x7c) = uStack_f8._4_1_;
    uVar5 = FUN_001e5330(local_f0 & 0xffffffff);
    lVar12 = *(long *)(lVar13 + 0xf0);
    *(undefined4 *)(lVar14 + 0x80) = uVar5;
    *(undefined8 *)(lVar12 + 0x70) = local_108;
    if ((local_110 & 1) != 0) {
      *(undefined1 *)(lVar12 + 0x229) = (undefined1)local_e0;
      *(char *)(lVar12 + 0x22a) = local_a8._6_1_;
    }
    *(char *)(lVar12 + 0x22b) = local_e0._1_1_;
    if (*(char *)(lVar12 + 0x22c) == '\0' && local_e0._1_1_ != '\0') {
      *(undefined1 *)(lVar12 + 0x22c) = local_a8._7_1_;
    }
  }
  uVar6 = (uint)local_f0._7_1_ << 1;
  if (local_e8._3_1_ == '\0') {
    uVar6 = (byte)local_e8 | uVar6;
    if (local_e8._2_1_ == -0xe) {
      uVar10 = uVar6 | 4;
    }
    else {
      uVar10 = uVar6;
      if (local_e8._2_1_ == -0xd) {
        uVar10 = uVar6 | 8;
        if (local_a0._1_1_ == -0x70) {
          uVar10 = uVar6;
        }
      }
    }
    uVar6 = -(uint)local_e8._1_1_ & 0x10 | uVar10;
  }
  uVar7 = 1;
  *(uint *)(param_4 + 0x32c) = uVar6;
  goto LAB_001dc06c;
}

