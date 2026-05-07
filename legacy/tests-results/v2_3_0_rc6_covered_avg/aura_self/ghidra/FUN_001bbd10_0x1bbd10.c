
void FUN_001bbd10(long param_1,undefined8 param_2,undefined8 param_3)

{
  byte *pbVar1;
  byte bVar2;
  char cVar3;
  uint uVar4;
  bool bVar5;
  char cVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  undefined4 uVar11;
  long lVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  long lVar16;
  ulong uVar17;
  undefined8 uVar18;
  ulong uVar19;
  byte *pbVar20;
  undefined1 auStack_418 [960];
  long local_58;
  
  local_58 = *(long *)PTR___stack_chk_guard_005ffe88;
  uVar7 = FUN_0018ffb0(param_1,0);
  if (uVar7 == 0x370) {
    FUN_0018ffd0(param_1,2);
    iVar8 = FUN_00190080();
    if (iVar8 == 0xc) {
      FUN_0018ffd0(param_1,3);
      lVar12 = FUN_001900a0();
      if (lVar12 == -4) {
        FUN_00190370(param_2,&DAT_001fa110);
        FUN_0018ffa0(param_1,0x80);
        FUN_001b35e4(param_1,4,param_2);
        FUN_00190370(param_2,&DAT_001fe728);
        lVar12 = *(long *)(param_1 + 800);
        FUN_0018ffd0(param_1,1);
        FUN_00190080();
        uVar18 = (**(code **)(lVar12 + 0x78))();
        FUN_00190370(param_2,uVar18);
        if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
          lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          *(undefined4 *)(lVar12 + (ulong)*(byte *)(lVar12 + 0x80) * 0x30 + 0x94) = 1;
          FUN_0018ffd0(param_1);
          uVar11 = FUN_00190080();
          uVar18 = *(undefined8 *)(param_1 + 800);
          lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          *(undefined4 *)(lVar12 + (ulong)*(byte *)(lVar12 + 0x80) * 0x30 + 0x98) = uVar11;
          uVar11 = FUN_0018ffb0(param_1);
          bVar2 = *(byte *)(param_1 + 0x366);
          lVar12 = FUN_001bddc0(uVar18,uVar11);
          if (lVar12 == 0) {
            cVar6 = '\0';
          }
          else {
            cVar6 = *(char *)(lVar12 + (ulong)bVar2);
            if (cVar6 == -0x80) {
              cVar6 = '\0';
            }
          }
          lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          cVar3 = *(char *)(lVar12 + 0x80);
          *(char *)(lVar12 + (ulong)*(byte *)(lVar12 + 0x80) * 0x30 + 0xb1) = cVar6;
          *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
          *(char *)(lVar12 + 0x80) = cVar3 + '\x01';
        }
LAB_001bc9ec:
        lVar12 = local_58 - *(long *)PTR___stack_chk_guard_005ffe88;
        if (lVar12 == 0) {
          FUN_00190370(param_2,&DAT_001f96c0,0);
          return;
        }
        goto LAB_001bd9e4;
      }
    }
    goto LAB_001bbe90;
  }
  if (0x370 < uVar7) {
    if (uVar7 == 0xa49) {
LAB_001bc8f4:
      FUN_0018ffd0(param_1,0);
      iVar8 = FUN_00190080();
      if (iVar8 != 0xc) goto LAB_001bbe90;
      FUN_00190370(param_2,"vpush");
      uVar18 = 0x18b;
LAB_001bc920:
      FUN_0018ffa0(param_1,uVar18);
      FUN_001b35e4(param_1,2,param_2);
      FUN_00190370(param_2,&DAT_001fe348);
LAB_001bbe28:
      lVar12 = local_58 - *(long *)PTR___stack_chk_guard_005ffe88;
      if (lVar12 == 0) {
        uVar18 = 4;
LAB_001bc338:
        FUN_001b10d4(param_1,uVar18,param_2);
        return;
      }
      goto LAB_001bd9e4;
    }
    if (uVar7 < 0xa4a) {
      if (uVar7 == 0x696) {
LAB_001bc204:
        FUN_0018ffd0(param_1,0);
        iVar8 = FUN_00190080();
        if (iVar8 == 0xc) {
          FUN_00190370(param_2,&DAT_001fe738);
          uVar18 = 0x18a;
          goto LAB_001bc920;
        }
      }
      else if (uVar7 < 0x697) {
        if (uVar7 == 0x387) goto LAB_001bc0b4;
        if (uVar7 == 0x692) goto LAB_001bc204;
      }
      else if (uVar7 == 0xa45) goto LAB_001bc8f4;
    }
    else {
      if (uVar7 == 0xc0f) {
LAB_001bc0b4:
        FUN_00190370(param_2,"tsb\tcsync");
        lVar12 = local_58 - *(long *)PTR___stack_chk_guard_005ffe88;
        if (lVar12 == 0) {
          FUN_0018ffa0(param_1,0x10b,0);
          return;
        }
        goto LAB_001bd9e4;
      }
      if (uVar7 < 0xc10) {
        if (uVar7 == 0xb17) {
LAB_001bc6dc:
          FUN_0018ffd0(param_1,0);
          iVar8 = FUN_00190080();
          if ((iVar8 == 0xc) && (uVar9 = FUN_0018ffe0(param_1), 5 < uVar9)) {
            FUN_00190370(param_2,&DAT_001fa118);
            FUN_0018ffa0(param_1,0x7f);
            FUN_001b35e4(param_1,2,param_2);
            if (uVar7 == 0xb17) {
              FUN_00190370(param_2,&DAT_001fe678);
            }
            FUN_00190370(param_2,&DAT_001fe348);
            *(undefined1 *)(param_1 + 0x366) = 1;
            iVar8 = *(int *)(*(long *)(param_1 + 800) + 0x60);
joined_r0x001bbdf4:
            if (iVar8 != 0) {
              lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
              bVar2 = *(byte *)(lVar12 + 0x28);
              *(undefined2 *)(lVar12 + (ulong)bVar2 * 2) = 0xc;
              *(byte *)(lVar12 + 0x28) = bVar2 + 1;
              bVar2 = *(byte *)(lVar12 + 0x52);
              *(undefined2 *)(lVar12 + (ulong)bVar2 * 2 + 0x2a) = 0xc;
              *(byte *)(lVar12 + 0x52) = bVar2 + 1;
            }
            goto LAB_001bbe28;
          }
        }
        else if (uVar7 == 0xbe3) goto LAB_001bbd80;
      }
      else if (uVar7 == 0xc5d) {
        uVar7 = 3;
        bVar5 = true;
        FUN_0018ffd0(param_1,0);
        iVar8 = FUN_00190080();
        while (uVar9 = FUN_0018ffe0(param_1), uVar7 < uVar9) {
          FUN_0018ffd0(param_1,uVar7);
          uVar7 = uVar7 + 1;
          iVar10 = FUN_00190080();
          if (iVar10 == iVar8) {
            bVar5 = false;
          }
        }
        FUN_00190370(param_2,&DAT_001fe740);
        FUN_0018ffa0(param_1,0x4f);
        FUN_001b35e4(param_1,1,param_2);
        FUN_00190370(param_2,&DAT_001fe348);
        uVar18 = (**(code **)(*(long *)(param_1 + 800) + 0x78))(iVar8);
        FUN_00190370(param_2,uVar18);
        if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
          lVar16 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          bVar2 = *(byte *)(lVar16 + 0x80);
          lVar12 = lVar16 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10;
          *(undefined4 *)(lVar12 + 0x94) = 1;
          *(int *)(lVar12 + 0x98) = iVar8;
          *(undefined1 *)(lVar12 + 0xb1) = 3;
          *(byte *)(lVar16 + 0x80) = bVar2 + 1;
        }
        if (bVar5) {
          *(undefined1 *)(param_1 + 0x335) = 1;
          FUN_00190370(param_2,&DAT_001fd610);
        }
        FUN_00190370(param_2,", ");
        lVar12 = local_58 - *(long *)PTR___stack_chk_guard_005ffe88;
        if (lVar12 == 0) {
          uVar18 = 3;
          goto LAB_001bc338;
        }
        goto LAB_001bd9dc;
      }
    }
    goto LAB_001bbe90;
  }
  if (uVar7 != 0x2b0) {
    if (uVar7 < 0x2b1) {
      if (uVar7 == 0x28a) {
LAB_001bcb68:
        uVar18 = FUN_001e7490(param_3,2);
        FUN_0018ffd0(param_1,0);
        uVar11 = FUN_00190080();
        uVar17 = FUN_001e74b4(uVar18,uVar11);
        if ((uVar17 & 1) != 0) {
          FUN_0018fec0(auStack_418);
          uVar9 = 0;
          FUN_0018ff90(auStack_418,uVar7);
LAB_001bd7bc:
          uVar18 = FUN_001e7490(param_3,0x15);
          uVar11 = FUN_001e7300(param_3,uVar11,9,uVar18);
          FUN_00190100(auStack_418,uVar11);
          for (uVar9 = uVar9 + 2; uVar7 = FUN_0018ffe0(param_1), uVar9 < uVar7; uVar9 = uVar9 + 1) {
            uVar18 = FUN_0018ffd0(param_1,uVar9);
            FUN_0018fff0(auStack_418,uVar18);
          }
          FUN_001b4fd0(auStack_418,param_2);
          goto LAB_001bc07c;
        }
      }
      else if (uVar7 < 0x28b) {
        if (uVar7 == 0x262) goto LAB_001bcb68;
        if (uVar7 == 0x27a) goto LAB_001bc6dc;
      }
      else if (uVar7 == 0x29d) {
        FUN_0018ffd0(param_1,2);
        iVar8 = FUN_00190080();
        if (iVar8 == 0xc) {
          FUN_0018ffd0(param_1,4);
          uVar7 = FUN_001900a0();
          if ((uVar7 & 0xfff) == 4) {
            FUN_00190370(param_2,&DAT_001fa118);
            FUN_0018ffa0(param_1,0x7f);
            FUN_001b35e4(param_1,5,param_2);
            FUN_00190370(param_2,&DAT_001fe728);
            lVar12 = *(long *)(param_1 + 800);
            FUN_0018ffd0(param_1,0);
            FUN_00190080();
            uVar18 = (**(code **)(lVar12 + 0x78))();
            FUN_00190370(param_2,uVar18);
            if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
              lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
              *(undefined4 *)(lVar12 + (ulong)*(byte *)(lVar12 + 0x80) * 0x30 + 0x94) = 1;
              FUN_0018ffd0(param_1,0);
              uVar11 = FUN_00190080();
              lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
              cVar6 = *(char *)(lVar12 + 0x80);
              lVar16 = lVar12 + (ulong)*(byte *)(lVar12 + 0x80) * 0x30;
              *(undefined4 *)(lVar16 + 0x98) = uVar11;
              *(undefined1 *)(lVar16 + 0xb1) = 2;
              *(char *)(lVar12 + 0x80) = cVar6 + '\x01';
              cVar6 = *(char *)(lVar12 + 0x28);
              *(undefined2 *)(lVar12 + (ulong)*(byte *)(lVar12 + 0x28) * 2) = 0xc;
              *(char *)(lVar12 + 0x28) = cVar6 + '\x01';
              cVar6 = *(char *)(lVar12 + 0x52);
              *(undefined2 *)(lVar12 + (ulong)*(byte *)(lVar12 + 0x52) * 2 + 0x2a) = 0xc;
              *(char *)(lVar12 + 0x52) = cVar6 + '\x01';
            }
            goto LAB_001bc9ec;
          }
        }
      }
    }
    else if (uVar7 == 0x34d) {
LAB_001bca38:
      uVar18 = FUN_001e7490(param_3,2);
      bVar5 = uVar7 == 0x365 || uVar7 == 0x34d;
      uVar9 = (uint)bVar5;
      FUN_0018ffd0(param_1,bVar5);
      uVar11 = FUN_00190080();
      uVar17 = FUN_001e74b4(uVar18,uVar11);
      if ((uVar17 & 1) != 0) {
        FUN_0018fec0(auStack_418);
        FUN_0018ff90(auStack_418,uVar7);
        uVar18 = FUN_0018ffd0(param_1,0);
        FUN_0018fff0(auStack_418,uVar18);
        goto LAB_001bd7bc;
      }
    }
    else if (uVar7 < 0x34e) {
      if (uVar7 == 0x2b1) {
        uVar18 = FUN_0018ffd0(param_1,0);
        uVar13 = FUN_0018ffd0(param_1,1);
        uVar14 = FUN_0018ffd0(param_1,2);
        FUN_0018ffd0(param_1,3);
        uVar9 = FUN_001900a0();
        uVar7 = uVar9 & 7;
        if (uVar7 == 3) {
          FUN_00190370(param_2,&DAT_001fa828);
          FUN_0018ffa0(param_1,99);
        }
        else if ((uVar9 >> 2 & 1) == 0) {
          if (uVar7 == 1) {
            FUN_00190370(param_2,&DAT_001fa830);
            FUN_0018ffa0(param_1,10);
          }
          else {
            if (uVar7 != 2) goto LAB_001bd6b4;
            FUN_00190370(param_2,&DAT_001fa820);
            FUN_0018ffa0(param_1,0x62);
          }
        }
        else if (uVar7 == 4) {
          FUN_00190370(param_2,"ror");
          FUN_0018ffa0(param_1,0x93);
        }
        else if (uVar7 == 5) {
          FUN_00190370(param_2,&DAT_001fdf70);
          FUN_0018ffa0(param_1,0x94);
        }
        else {
LAB_001bd6b4:
          FUN_00190370(param_2,&DAT_001fe648);
        }
        FUN_0018ffd0(param_1,6);
        iVar8 = FUN_00190080();
        if ((iVar8 != 0) &&
           (FUN_00190370(param_2,"s"), *(int *)(*(long *)(param_1 + 800) + 0x60) != 0)) {
          *(undefined1 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x78) = 1;
        }
        FUN_001b35e4(param_1,4,param_2);
        FUN_00190370(param_2,&DAT_001fe348);
        lVar12 = *(long *)(param_1 + 800);
        FUN_00190080(uVar18);
        uVar15 = (**(code **)(lVar12 + 0x78))();
        FUN_00190370(param_2,uVar15);
        if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
          lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          *(undefined4 *)(lVar12 + (ulong)*(byte *)(lVar12 + 0x80) * 0x30 + 0x94) = 1;
          uVar11 = FUN_00190080(uVar18);
          lVar16 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          bVar2 = *(byte *)(lVar16 + 0x80);
          lVar12 = lVar16 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10;
          *(undefined4 *)(lVar12 + 0x98) = uVar11;
          *(undefined1 *)(lVar12 + 0xb1) = 2;
          *(byte *)(lVar16 + 0x80) = bVar2 + 1;
        }
        FUN_00190370(param_2,", ");
        lVar12 = *(long *)(param_1 + 800);
        FUN_00190080(uVar13);
        uVar18 = (**(code **)(lVar12 + 0x78))();
        FUN_00190370(param_2,uVar18);
        if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
          lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          *(undefined4 *)(lVar12 + (ulong)*(byte *)(lVar12 + 0x80) * 0x30 + 0x94) = 1;
          uVar11 = FUN_00190080(uVar13);
          lVar16 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          bVar2 = *(byte *)(lVar16 + 0x80);
          lVar12 = lVar16 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10;
          *(undefined4 *)(lVar12 + 0x98) = uVar11;
          *(undefined1 *)(lVar12 + 0xb1) = 1;
          *(byte *)(lVar16 + 0x80) = bVar2 + 1;
        }
        FUN_00190370(param_2,", ");
        lVar12 = *(long *)(param_1 + 800);
        FUN_00190080(uVar14);
        uVar18 = (**(code **)(lVar12 + 0x78))();
        FUN_00190370(param_2,uVar18);
        if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
          lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          *(undefined4 *)(lVar12 + (ulong)*(byte *)(lVar12 + 0x80) * 0x30 + 0x94) = 1;
          uVar11 = FUN_00190080(uVar14);
          lVar16 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          bVar2 = *(byte *)(lVar16 + 0x80);
          lVar12 = lVar16 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10;
          *(undefined4 *)(lVar12 + 0x98) = uVar11;
          *(undefined1 *)(lVar12 + 0xb1) = 1;
          *(byte *)(lVar16 + 0x80) = bVar2 + 1;
        }
        goto LAB_001bc07c;
      }
    }
    else if (uVar7 == 0x353) {
LAB_001bbd80:
      FUN_0018ffd0(param_1,0);
      iVar8 = FUN_00190080();
      if ((iVar8 == 0xc) && (uVar9 = FUN_0018ffe0(param_1), 5 < uVar9)) {
        FUN_00190370(param_2,&DAT_001fa110);
        FUN_0018ffa0(param_1,0x80);
        FUN_001b35e4(param_1,2,param_2);
        if (uVar7 == 0xbe3) {
          FUN_00190370(param_2,&DAT_001fe678);
        }
        FUN_00190370(param_2,&DAT_001fe348);
        iVar8 = *(int *)(*(long *)(param_1 + 800) + 0x60);
        goto joined_r0x001bbdf4;
      }
    }
    else if (uVar7 == 0x365) goto LAB_001bca38;
LAB_001bbe90:
    *(undefined8 *)(param_1 + 0x3b0) = param_3;
    uVar7 = FUN_0018ffb0(param_1);
    if (uVar7 == 0xaf7) {
      iVar8 = FUN_0018ffe0(param_1);
      if (iVar8 == 3) {
        FUN_0018ffd0(param_1,0);
        uVar17 = FUN_00190030();
        if ((uVar17 & 1) != 0) {
          FUN_0018ffd0(param_1,0);
          lVar12 = FUN_001900a0();
          if (((lVar12 == 0) &&
              (uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x79),
              (uVar17 & 1) != 0)) &&
             (uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x5b),
             (uVar17 & 1) != 0)) {
            pbVar20 = &DAT_001fe6c0;
            goto LAB_001bc434;
          }
        }
      }
      iVar8 = FUN_0018ffe0(param_1);
      if (iVar8 == 3) {
        FUN_0018ffd0(param_1,0);
        uVar17 = FUN_00190030();
        if ((uVar17 & 1) != 0) {
          FUN_0018ffd0(param_1,0);
          lVar12 = FUN_001900a0();
          if (((lVar12 == 1) &&
              (uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x79),
              (uVar17 & 1) != 0)) &&
             (uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x5b),
             (uVar17 & 1) != 0)) {
            pbVar20 = &DAT_001fe6b0;
            goto LAB_001bc434;
          }
        }
      }
      iVar8 = FUN_0018ffe0(param_1);
      if (iVar8 == 3) {
        FUN_0018ffd0(param_1,0);
        uVar17 = FUN_00190030();
        if ((uVar17 & 1) != 0) {
          FUN_0018ffd0(param_1,0);
          lVar12 = FUN_001900a0();
          if (((lVar12 == 2) &&
              (uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x79),
              (uVar17 & 1) != 0)) &&
             (uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x5b),
             (uVar17 & 1) != 0)) {
            pbVar20 = &DAT_001fe6a0;
            goto LAB_001bc434;
          }
        }
      }
      iVar8 = FUN_0018ffe0(param_1);
      if (iVar8 == 3) {
        FUN_0018ffd0(param_1,0);
        uVar17 = FUN_00190030();
        if ((uVar17 & 1) != 0) {
          FUN_0018ffd0(param_1,0);
          lVar12 = FUN_001900a0();
          if (((lVar12 == 3) &&
              (uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x79),
              (uVar17 & 1) != 0)) &&
             (uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x5b),
             (uVar17 & 1) != 0)) {
            pbVar20 = &DAT_001fe690;
            goto LAB_001bc434;
          }
        }
      }
      iVar8 = FUN_0018ffe0(param_1);
      if (iVar8 == 3) {
        FUN_0018ffd0(param_1,0);
        uVar17 = FUN_00190030();
        if ((uVar17 & 1) != 0) {
          FUN_0018ffd0(param_1,0);
          lVar12 = FUN_001900a0();
          if (((lVar12 == 4) &&
              (uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x79),
              (uVar17 & 1) != 0)) &&
             (uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x5b),
             (uVar17 & 1) != 0)) {
            pbVar20 = &DAT_001fe680;
            goto LAB_001bc434;
          }
        }
      }
      iVar8 = FUN_0018ffe0(param_1);
      if (iVar8 == 3) {
        FUN_0018ffd0(param_1,0);
        uVar17 = FUN_00190030();
        if ((uVar17 & 1) != 0) {
          FUN_0018ffd0(param_1,0);
          lVar12 = FUN_001900a0();
          if (((lVar12 == 5) &&
              (uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x79),
              (uVar17 & 1) != 0)) &&
             ((uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x5b),
              (uVar17 & 1) != 0 &&
              (uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x71),
              (uVar17 & 1) != 0)))) {
            pbVar20 = &DAT_001fe670;
            goto LAB_001bc434;
          }
        }
      }
      iVar8 = FUN_0018ffe0(param_1);
      if (iVar8 == 3) {
        FUN_0018ffd0(param_1,0);
        uVar17 = FUN_00190030();
        if ((uVar17 & 1) != 0) {
          FUN_0018ffd0(param_1,0);
          lVar12 = FUN_001900a0();
          if ((((lVar12 == 0x10) &&
               (uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x79),
               (uVar17 & 1) != 0)) &&
              (uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x5b),
              (uVar17 & 1) != 0)) &&
             (uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x4f),
             (uVar17 & 1) != 0)) {
            pbVar20 = &DAT_001fe660;
            goto LAB_001bc434;
          }
        }
      }
      iVar8 = FUN_0018ffe0(param_1);
      if (iVar8 == 3) {
        FUN_0018ffd0(param_1,0);
        uVar17 = FUN_00190030();
        if ((uVar17 & 1) != 0) {
          FUN_0018ffd0(param_1,0);
          lVar12 = FUN_001900a0();
          if ((lVar12 == 0x14) &&
             (uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x79),
             (uVar17 & 1) != 0)) {
            uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x5b);
joined_r0x001bc6b4:
            if ((uVar17 & 1) != 0) {
              pbVar20 = &DAT_001fe640;
              goto LAB_001bc434;
            }
          }
        }
      }
    }
    else if (uVar7 < 0xaf8) {
      if (uVar7 == 0x25a) {
        iVar8 = FUN_0018ffe0(param_1);
        if (iVar8 == 3) {
          FUN_0018ffd0(param_1,0);
          uVar17 = FUN_00190030();
          if ((uVar17 & 1) != 0) {
            FUN_0018ffd0(param_1,0);
            lVar12 = FUN_001900a0();
            if (((lVar12 == 0) &&
                (uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x79),
                (uVar17 & 1) == 0)) &&
               (uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x6a),
               (uVar17 & 1) != 0)) {
LAB_001bcc00:
              pbVar20 = &DAT_001fe718;
              goto LAB_001bc434;
            }
          }
        }
        iVar8 = FUN_0018ffe0(param_1);
        if (iVar8 == 3) {
          FUN_0018ffd0(param_1,0);
          uVar17 = FUN_00190030();
          if ((uVar17 & 1) != 0) {
            FUN_0018ffd0(param_1,0);
            lVar12 = FUN_001900a0();
            if (((lVar12 == 1) &&
                (uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x79),
                (uVar17 & 1) == 0)) &&
               (uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x6a),
               (uVar17 & 1) != 0)) {
LAB_001bcd20:
              pbVar20 = &DAT_001fe708;
              goto LAB_001bc434;
            }
          }
        }
        iVar8 = FUN_0018ffe0(param_1);
        if (iVar8 == 3) {
          FUN_0018ffd0(param_1,0);
          uVar17 = FUN_00190030();
          if ((uVar17 & 1) != 0) {
            FUN_0018ffd0(param_1,0);
            lVar12 = FUN_001900a0();
            if (((lVar12 == 2) &&
                (uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x79),
                (uVar17 & 1) == 0)) &&
               (uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x6a),
               (uVar17 & 1) != 0)) {
LAB_001bce48:
              pbVar20 = &DAT_001fe700;
              goto LAB_001bc434;
            }
          }
        }
        iVar8 = FUN_0018ffe0(param_1);
        if (iVar8 == 3) {
          FUN_0018ffd0(param_1,0);
          uVar17 = FUN_00190030();
          if ((uVar17 & 1) != 0) {
            FUN_0018ffd0(param_1,0);
            lVar12 = FUN_001900a0();
            if (((lVar12 == 3) &&
                (uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x79),
                (uVar17 & 1) == 0)) &&
               (uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x6a),
               (uVar17 & 1) != 0)) {
LAB_001bcf70:
              pbVar20 = &DAT_001fe6f8;
              goto LAB_001bc434;
            }
          }
        }
        iVar8 = FUN_0018ffe0(param_1);
        if (iVar8 == 3) {
          FUN_0018ffd0(param_1,0);
          uVar17 = FUN_00190030();
          if ((uVar17 & 1) != 0) {
            FUN_0018ffd0(param_1,0);
            lVar12 = FUN_001900a0();
            if (((lVar12 == 4) &&
                (uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x79),
                (uVar17 & 1) == 0)) &&
               (uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x6a),
               (uVar17 & 1) != 0)) {
LAB_001bd098:
              pbVar20 = &DAT_001fe6f0;
              goto LAB_001bc434;
            }
          }
        }
        iVar8 = FUN_0018ffe0(param_1);
        if (iVar8 == 3) {
          FUN_0018ffd0(param_1,0);
          uVar17 = FUN_00190030();
          if ((uVar17 & 1) != 0) {
            FUN_0018ffd0(param_1,0);
            lVar12 = FUN_001900a0();
            if (((lVar12 == 5) &&
                (uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x79),
                (uVar17 & 1) == 0)) &&
               (uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x71),
               (uVar17 & 1) != 0)) {
LAB_001bc1d4:
              pbVar20 = &DAT_001fe6e0;
              goto LAB_001bc434;
            }
          }
        }
        iVar8 = FUN_0018ffe0(param_1);
        if (iVar8 == 3) {
          FUN_0018ffd0(param_1,0);
          uVar17 = FUN_00190030();
          if ((uVar17 & 1) != 0) {
            FUN_0018ffd0(param_1,0);
            lVar12 = FUN_001900a0();
            if (((lVar12 == 0x10) &&
                (uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x79),
                (uVar17 & 1) == 0)) &&
               (uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x4f),
               (uVar17 & 1) != 0)) {
              pbVar20 = &DAT_001fe6d8;
              goto LAB_001bc434;
            }
          }
        }
        iVar8 = FUN_0018ffe0(param_1);
        if (iVar8 == 3) {
          FUN_0018ffd0(param_1,0);
          uVar17 = FUN_00190030();
          if ((uVar17 & 1) != 0) {
            FUN_0018ffd0(param_1,0);
            lVar12 = FUN_001900a0();
            if ((lVar12 == 0x14) &&
               (uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x79),
               (uVar17 & 1) == 0)) {
              uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x6a);
              goto joined_r0x001bc6b4;
            }
          }
        }
      }
      else if (uVar7 == 0xaf3) {
        iVar8 = FUN_0018ffe0(param_1);
        if (iVar8 == 3) {
          FUN_0018ffd0(param_1,0);
          uVar17 = FUN_00190030();
          if ((uVar17 & 1) != 0) {
            FUN_0018ffd0(param_1,0);
            lVar12 = FUN_001900a0();
            if ((lVar12 == 0xc) &&
               (uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x2b),
               (uVar17 & 1) != 0)) {
              pbVar20 = &DAT_001fe6d0;
              goto LAB_001bc434;
            }
          }
        }
      }
      else if ((uVar7 == 0x24a) && (iVar8 = FUN_0018ffe0(param_1), iVar8 == 1)) {
        FUN_0018ffd0(param_1,0);
        uVar17 = FUN_00190030();
        if ((uVar17 & 1) != 0) {
          FUN_0018ffd0(param_1,0);
          lVar12 = FUN_001900a0();
          if (((lVar12 == 0xc) &&
              (uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x79),
              (uVar17 & 1) == 0)) &&
             (uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x2b),
             (uVar17 & 1) != 0)) {
            pbVar20 = &DAT_001fe720;
LAB_001bc434:
            lVar16 = FUN_00190780(pbVar20);
            uVar19 = (ulong)*pbVar20;
            uVar17 = 0;
            do {
              if ((int)uVar19 == 0x24) break;
              if ((int)uVar19 == 0) {
                *(undefined1 *)(lVar16 + uVar17) = 0;
                FUN_00190370(param_2,lVar16);
                lVar12 = local_58 - *(long *)PTR___stack_chk_guard_005ffe88;
                if (lVar12 == 0) {
                  (**(code **)PTR_PTR_005fff60)(lVar16,*(code **)PTR_PTR_005fff60,0);
                  return;
                }
                goto LAB_001bd9dc;
              }
              uVar17 = (ulong)((int)uVar17 + 1);
              bVar2 = pbVar20[uVar17];
              uVar19 = (ulong)bVar2;
            } while (bVar2 != 0x20 && bVar2 != 9);
            *(undefined1 *)(lVar16 + uVar17) = 0;
            FUN_00190370(param_2,lVar16);
            (**(code **)PTR_PTR_005fff60)(lVar16);
            if ((0x100000200U >> (uVar19 & 0x3f) & 1) != 0) {
              uVar17 = (ulong)((int)uVar17 + 1);
              FUN_00190370(param_2,&DAT_001fe568);
            }
            bVar2 = pbVar20[uVar17];
            do {
              iVar8 = (int)uVar17;
              uVar17 = (ulong)(iVar8 + 1);
              if (bVar2 == 0x24) {
                pbVar1 = pbVar20 + uVar17;
                if (*pbVar1 == 0xff) {
                  if (pbVar20[iVar8 + 3] == 1) {
                    uVar17 = (ulong)(iVar8 + 4);
                    FUN_001b35e4(param_1,pbVar20[iVar8 + 2U] - 1,param_2);
                  }
                  else {
                    uVar17 = (ulong)(iVar8 + 4);
                  }
                }
                else {
                  uVar17 = (ulong)(iVar8 + 2U);
                  FUN_001b1900(param_1,*pbVar1 - 1,param_2);
                }
              }
              else {
                if (bVar2 == 0x5b) {
                  FUN_001b3500(param_1,1);
                }
                else if ((bVar2 == 0x5d) && (*(int *)(*(long *)(param_1 + 800) + 0x60) == 3)) {
                  lVar12 = *(long *)(param_1 + 0x310);
                  *(undefined1 *)(*(long *)(param_1 + 800) + 0x6c) = 0;
                  lVar12 = *(long *)(lVar12 + 0xf0);
                  *(char *)(lVar12 + 0x80) = *(char *)(lVar12 + 0x80) + '\x01';
                }
                FUN_001903d0(param_2,bVar2);
              }
              bVar2 = pbVar20[uVar17];
            } while (bVar2 != 0);
            goto LAB_001bc07c;
          }
        }
      }
    }
    else if (uVar7 == 0xbff) {
      iVar8 = FUN_0018ffe0(param_1);
      if (iVar8 == 3) {
        FUN_0018ffd0(param_1,0);
        uVar17 = FUN_00190030();
        if ((uVar17 & 1) != 0) {
          FUN_0018ffd0(param_1,0);
          lVar12 = FUN_001900a0();
          if (((lVar12 == 0) &&
              (uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x79),
              (uVar17 & 1) != 0)) &&
             ((uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x5b),
              (uVar17 & 1) != 0 &&
              (uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x65),
              (uVar17 & 1) != 0)))) {
            pbVar20 = &DAT_001fe650;
            goto LAB_001bc434;
          }
        }
      }
    }
    else if (uVar7 == 0xc58) {
      iVar8 = FUN_0018ffe0(param_1);
      if (iVar8 == 3) {
        FUN_0018ffd0(param_1,0);
        uVar17 = FUN_00190030();
        if ((uVar17 & 1) != 0) {
          FUN_0018ffd0(param_1,0);
          lVar12 = FUN_001900a0();
          if (((lVar12 == 0) &&
              (uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x79),
              (uVar17 & 1) != 0)) &&
             (uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x6b),
             (uVar17 & 1) != 0)) goto LAB_001bcc00;
        }
      }
      iVar8 = FUN_0018ffe0(param_1);
      if (iVar8 == 3) {
        FUN_0018ffd0(param_1,0);
        uVar17 = FUN_00190030();
        if ((uVar17 & 1) != 0) {
          FUN_0018ffd0(param_1,0);
          lVar12 = FUN_001900a0();
          if (((lVar12 == 1) &&
              (uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x79),
              (uVar17 & 1) != 0)) &&
             (uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x6b),
             (uVar17 & 1) != 0)) goto LAB_001bcd20;
        }
      }
      iVar8 = FUN_0018ffe0(param_1);
      if (iVar8 == 3) {
        FUN_0018ffd0(param_1,0);
        uVar17 = FUN_00190030();
        if ((uVar17 & 1) != 0) {
          FUN_0018ffd0(param_1,0);
          lVar12 = FUN_001900a0();
          if (((lVar12 == 2) &&
              (uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x79),
              (uVar17 & 1) != 0)) &&
             (uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x6b),
             (uVar17 & 1) != 0)) goto LAB_001bce48;
        }
      }
      iVar8 = FUN_0018ffe0(param_1);
      if (iVar8 == 3) {
        FUN_0018ffd0(param_1,0);
        uVar17 = FUN_00190030();
        if ((uVar17 & 1) != 0) {
          FUN_0018ffd0(param_1,0);
          lVar12 = FUN_001900a0();
          if (((lVar12 == 3) &&
              (uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x79),
              (uVar17 & 1) != 0)) &&
             (uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x6b),
             (uVar17 & 1) != 0)) goto LAB_001bcf70;
        }
      }
      iVar8 = FUN_0018ffe0(param_1);
      if (iVar8 == 3) {
        FUN_0018ffd0(param_1,0);
        uVar17 = FUN_00190030();
        if ((uVar17 & 1) != 0) {
          FUN_0018ffd0(param_1,0);
          lVar12 = FUN_001900a0();
          if (((lVar12 == 4) &&
              (uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x79),
              (uVar17 & 1) != 0)) &&
             (uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x6b),
             (uVar17 & 1) != 0)) goto LAB_001bd098;
        }
      }
      iVar8 = FUN_0018ffe0(param_1);
      if (iVar8 == 3) {
        FUN_0018ffd0(param_1,0);
        uVar17 = FUN_00190030();
        if ((uVar17 & 1) != 0) {
          FUN_0018ffd0(param_1,0);
          lVar12 = FUN_001900a0();
          if (((lVar12 == 5) &&
              (uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x79),
              (uVar17 & 1) != 0)) &&
             ((uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x5b),
              (uVar17 & 1) != 0 &&
              (uVar17 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x71),
              (uVar17 & 1) != 0)))) goto LAB_001bc1d4;
        }
      }
    }
    lVar12 = local_58 - *(long *)PTR___stack_chk_guard_005ffe88;
    if (lVar12 == 0) {
      FUN_001b4fd0(param_1,param_2,0);
      return;
    }
LAB_001bd9e4:
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,lVar12);
  }
  uVar18 = FUN_0018ffd0(param_1,0);
  uVar13 = FUN_0018ffd0(param_1,1);
  uVar14 = FUN_0018ffd0(param_1,2);
  uVar9 = FUN_001900a0();
  uVar7 = uVar9 & 7;
  if (uVar7 == 3) {
    FUN_00190370(param_2,&DAT_001fa828);
    FUN_0018ffa0(param_1,99);
  }
  else if ((uVar9 >> 2 & 1) == 0) {
    if (uVar7 == 1) {
      FUN_00190370(param_2,&DAT_001fa830);
      FUN_0018ffa0(param_1,10);
    }
    else {
      if (uVar7 != 2) goto LAB_001bd708;
      FUN_00190370(param_2,&DAT_001fa820);
      FUN_0018ffa0(param_1,0x62);
    }
  }
  else if (uVar7 == 4) {
    FUN_00190370(param_2,"ror");
    FUN_0018ffa0(param_1,0x93);
  }
  else if (uVar7 == 5) {
    FUN_00190370(param_2,&DAT_001fdf70);
    FUN_0018ffa0(param_1,0x94);
  }
  else {
LAB_001bd708:
    FUN_00190370(param_2,&DAT_001fe648);
  }
  FUN_0018ffd0(param_1,5);
  iVar8 = FUN_00190080();
  if ((iVar8 != 0) && (FUN_00190370(param_2,"s"), *(int *)(*(long *)(param_1 + 800) + 0x60) != 0)) {
    *(undefined1 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x78) = 1;
  }
  FUN_001b35e4(param_1,3,param_2);
  FUN_00190370(param_2,&DAT_001fe348);
  lVar12 = *(long *)(param_1 + 800);
  FUN_00190080(uVar18);
  uVar15 = (**(code **)(lVar12 + 0x78))();
  FUN_00190370(param_2,uVar15);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    *(undefined4 *)(lVar12 + (ulong)*(byte *)(lVar12 + 0x80) * 0x30 + 0x94) = 1;
    uVar11 = FUN_00190080(uVar18);
    lVar16 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar2 = *(byte *)(lVar16 + 0x80);
    lVar12 = lVar16 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10;
    *(undefined4 *)(lVar12 + 0x98) = uVar11;
    *(undefined1 *)(lVar12 + 0xb1) = 2;
    *(byte *)(lVar16 + 0x80) = bVar2 + 1;
  }
  FUN_00190370(param_2,", ");
  lVar12 = *(long *)(param_1 + 800);
  FUN_00190080(uVar13);
  uVar18 = (**(code **)(lVar12 + 0x78))();
  FUN_00190370(param_2,uVar18);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    *(undefined4 *)(lVar12 + (ulong)*(byte *)(lVar12 + 0x80) * 0x30 + 0x94) = 1;
    uVar11 = FUN_00190080(uVar13);
    lVar16 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar2 = *(byte *)(lVar16 + 0x80);
    lVar12 = lVar16 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10;
    *(undefined4 *)(lVar12 + 0x98) = uVar11;
    *(undefined1 *)(lVar12 + 0xb1) = 1;
    *(byte *)(lVar16 + 0x80) = bVar2 + 1;
  }
  if (uVar7 != 5) {
    FUN_00190370(param_2,", ");
    uVar17 = FUN_001900a0(uVar14);
    uVar9 = (uint)(uVar17 >> 3) & 0x1fffffff;
    if ((uVar17 >> 3 & 0x1fffffff) == 0) {
      uVar9 = 0x20;
    }
    FUN_001906d0(param_2,uVar9);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar12 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      uVar4 = *(byte *)(lVar12 + 0x80) - 1;
      lVar12 = lVar12 + ((-(ulong)(uVar4 >> 0x1f) & 0xfffffffe00000000 | (ulong)uVar4 << 1) +
                        (long)(int)uVar4) * 0x10;
      *(uint *)(lVar12 + 0x8c) = uVar7;
      *(uint *)(lVar12 + 0x90) = uVar9;
    }
  }
LAB_001bc07c:
  lVar12 = local_58 - *(long *)PTR___stack_chk_guard_005ffe88;
  if (lVar12 == 0) {
    return;
  }
LAB_001bd9dc:
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,lVar12);
}

