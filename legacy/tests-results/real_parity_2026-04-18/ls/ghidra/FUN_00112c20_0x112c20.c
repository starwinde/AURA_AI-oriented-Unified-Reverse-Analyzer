
byte * FUN_00112c20(undefined8 *param_1,byte *param_2,uint *param_3,int param_4,undefined8 *param_5,
                   byte *param_6)

{
  uint *puVar1;
  uint uVar2;
  long lVar3;
  bool bVar4;
  undefined *puVar5;
  bool bVar6;
  byte bVar7;
  int iVar8;
  byte *pbVar9;
  size_t sVar10;
  ushort **ppuVar11;
  int *piVar12;
  byte *pbVar13;
  ulong uVar14;
  byte *pbVar15;
  size_t sVar16;
  byte *pbVar17;
  byte *unaff_x20;
  byte *__dest;
  wchar_t local_74;
  mbstate_t local_70;
  long local_68;
  
  puVar1 = &DAT_00140f48;
  if (param_3 != (uint *)0x0) {
    puVar1 = param_3;
  }
  uVar2 = *puVar1;
  __dest = (byte *)*param_1;
  local_68 = *(long *)PTR___stack_chk_guard_0013ffd0;
  bVar6 = (bool)(uVar2 < 3 & DAT_00141430);
  if ((uVar2 < 3 & DAT_00141430) == 0) {
    if (param_4 == 0) {
      pbVar9 = (byte *)strlen((char *)param_2);
      __dest = param_2;
    }
    else {
      bVar4 = false;
LAB_00112e44:
      piVar12 = __errno_location();
      iVar8 = *piVar12;
      pbVar9 = (byte *)FUN_00111270(__dest,0x2000,param_2,uVar2,puVar1[1],puVar1 + 2,
                                    *(undefined8 *)(puVar1 + 10),*(undefined8 *)(puVar1 + 0xc));
      *piVar12 = iVar8;
      if ((byte *)0x1fff < pbVar9) {
        pbVar13 = pbVar9 + 1;
        __dest = malloc((size_t)pbVar13);
        if (__dest == (byte *)0x0) {
LAB_001130b0:
                    /* WARNING: Subroutine does not return */
          FUN_0010d454();
        }
        iVar8 = *piVar12;
        FUN_00111270(__dest,pbVar13,param_2,*puVar1,puVar1[1],puVar1 + 2,
                     *(undefined8 *)(puVar1 + 10),*(undefined8 *)(puVar1 + 0xc),pbVar13);
        *piVar12 = iVar8;
      }
      bVar6 = true;
      if (*param_2 == *__dest) {
        pbVar13 = (byte *)strlen((char *)param_2);
        bVar6 = pbVar13 != pbVar9;
      }
      if (bVar4) goto LAB_00112db8;
    }
    if (param_5 == (undefined8 *)0x0) {
      if ((DAT_00141280 & 1) == 0) {
        *param_6 = 0;
        goto LAB_00112d10;
      }
LAB_00112d60:
      bVar7 = (bVar6 ^ 1U) & DAT_00140ef0;
      goto LAB_00112d74;
    }
    sVar10 = __ctype_get_mb_cur_max();
    if (sVar10 < 2) {
      if (__dest < __dest + (long)pbVar9) {
        ppuVar11 = __ctype_b_loc();
        unaff_x20 = (byte *)0x0;
        pbVar13 = __dest;
        do {
          pbVar15 = pbVar13 + 1;
          unaff_x20 = unaff_x20 + ((ulong)((*ppuVar11)[*pbVar13] >> 0xe) & 1);
          pbVar13 = pbVar15;
        } while (__dest + (long)pbVar9 != pbVar15);
      }
      else {
        unaff_x20 = (byte *)0x0;
      }
    }
    else {
      iVar8 = FUN_00112a50(__dest,pbVar9);
      unaff_x20 = (byte *)(long)iVar8;
    }
    if ((DAT_00141280 & 1) != 0) goto LAB_00112d60;
    *param_6 = 0;
  }
  else {
    if (param_4 != 0) {
      bVar4 = true;
      goto LAB_00112e44;
    }
    pbVar9 = (byte *)strlen((char *)param_2);
    if (((byte *)0x1fff < pbVar9) && (__dest = malloc((size_t)(pbVar9 + 1)), __dest == (byte *)0x0))
    goto LAB_001130b0;
    memcpy(__dest,param_2,(size_t)(pbVar9 + 1));
    bVar6 = false;
LAB_00112db8:
    pbVar13 = __dest + (long)pbVar9;
    sVar10 = __ctype_get_mb_cur_max();
    if (sVar10 < 2) {
      unaff_x20 = pbVar9;
      if (__dest < pbVar13) {
        ppuVar11 = __ctype_b_loc();
        pbVar15 = __dest;
        do {
          if (((*ppuVar11)[*pbVar15] >> 0xe & 1) == 0) {
            *pbVar15 = 0x3f;
          }
          pbVar15 = pbVar15 + 1;
        } while (pbVar15 != pbVar13);
      }
    }
    else if (__dest < pbVar13) {
      unaff_x20 = (byte *)0x0;
      pbVar17 = __dest;
      pbVar15 = __dest;
      do {
        bVar7 = *pbVar15;
        if (bVar7 < 0x60) {
          if (0x40 < bVar7) goto LAB_00112e14;
          if (0x23 < bVar7) {
            if (0x1a < (byte)(bVar7 - 0x25)) goto LAB_00112f54;
            goto LAB_00112e14;
          }
          if (0x1f < bVar7) goto LAB_00112e14;
LAB_00112f54:
          local_70.__count = 0;
          local_70.__value = (_union_27)0x0;
          do {
            sVar10 = mbrtowc(&local_74,(char *)pbVar15,(long)pbVar13 - (long)pbVar15,&local_70);
            if ((long)pbVar13 - (long)pbVar15 == 0 || sVar10 < 0xfffffffffffffffe) {
              if (sVar10 == 0xffffffffffffffff) goto LAB_00113090;
              if (sVar10 == 0xfffffffffffffffe) goto LAB_00112fe4;
              if (sVar10 == 0) {
                sVar10 = 1;
              }
              iVar8 = wcwidth(local_74);
              if (iVar8 < 0) goto LAB_00112f84;
              sVar16 = 0;
              do {
                pbVar17[sVar16] = pbVar15[sVar16];
                sVar16 = sVar16 + 1;
              } while (sVar16 != sVar10);
              pbVar15 = pbVar15 + sVar10;
              pbVar9 = pbVar17 + sVar10;
              unaff_x20 = unaff_x20 + iVar8;
            }
            else {
              uVar14 = FUN_0010ba30(0);
              if ((uVar14 & 1) != 0) {
                if (sVar10 == 0xffffffffffffffff) {
LAB_00113090:
                  bVar7 = 0x3f;
                  goto LAB_00112e14;
                }
LAB_00112fe4:
                *pbVar17 = 0x3f;
                pbVar9 = pbVar17 + (1 - (long)__dest);
                unaff_x20 = unaff_x20 + 1;
                goto LAB_00112f00;
              }
              sVar10 = 1;
              local_74 = (wchar_t)*pbVar15;
              iVar8 = wcwidth(local_74);
              if (iVar8 < 0) {
LAB_00112f84:
                pbVar15 = pbVar15 + sVar10;
                unaff_x20 = unaff_x20 + 1;
                pbVar9 = pbVar17 + 1;
                *pbVar17 = 0x3f;
              }
              else {
                bVar7 = *pbVar15;
                unaff_x20 = unaff_x20 + iVar8;
                pbVar15 = pbVar15 + 1;
                *pbVar17 = bVar7;
                pbVar9 = pbVar17 + 1;
              }
            }
            iVar8 = mbsinit(&local_70);
            pbVar17 = pbVar9;
          } while (iVar8 == 0);
        }
        else {
          if (0x1d < (byte)(bVar7 + 0x9f)) goto LAB_00112f54;
LAB_00112e14:
          pbVar15 = pbVar15 + 1;
          unaff_x20 = unaff_x20 + 1;
          pbVar9 = pbVar17 + 1;
          *pbVar17 = bVar7;
        }
        pbVar17 = pbVar9;
      } while (pbVar15 < pbVar13);
      pbVar9 = pbVar9 + -(long)__dest;
    }
    else {
      pbVar9 = (byte *)0x0;
      unaff_x20 = (byte *)0x0;
    }
LAB_00112f00:
    bVar7 = DAT_00141280;
    if ((DAT_00141280 & 1) != 0) goto LAB_00112d60;
LAB_00112d74:
    *param_6 = bVar7;
    if (param_5 == (undefined8 *)0x0) goto LAB_00112d10;
  }
  *param_5 = unaff_x20;
LAB_00112d10:
  puVar5 = PTR___stack_chk_guard_0013ffd0;
  *param_1 = __dest;
  lVar3 = local_68 - *(long *)puVar5;
  if (lVar3 == 0) {
    return pbVar9;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(puVar5,0,lVar3);
}

