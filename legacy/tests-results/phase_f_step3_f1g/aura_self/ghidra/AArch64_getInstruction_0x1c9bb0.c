
void AArch64_getInstruction
               (long param_1,uint *param_2,ulong param_3,long param_4,undefined2 *param_5)

{
  uint uVar1;
  undefined *puVar2;
  bool bVar3;
  int iVar4;
  uint uVar5;
  void *__s;
  long lVar6;
  ulong uVar7;
  undefined8 uVar8;
  undefined2 uVar9;
  undefined1 auStack_48 [4];
  undefined1 local_44;
  undefined8 local_40;
  long local_38;
  
  local_38 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (param_3 < 4) {
LAB_001c9d38:
    uVar9 = 0;
    bVar3 = false;
  }
  else {
    __s = *(void **)(*(long *)(param_4 + 0x310) + 0xf0);
    if (__s != (void *)0x0) {
      memset(__s,0,0x228);
      lVar6 = *(long *)(*(long *)(param_4 + 0x310) + 0xf0);
      *(undefined4 *)(lVar6 + 0x68) = 0xffffffff;
      *(undefined4 *)(lVar6 + 0xa0) = 0xffffffff;
      *(undefined4 *)(lVar6 + 0xd8) = 0xffffffff;
      *(undefined4 *)(lVar6 + 0x110) = 0xffffffff;
      *(undefined4 *)(lVar6 + 0x148) = 0xffffffff;
      *(undefined4 *)(lVar6 + 0x180) = 0xffffffff;
      *(undefined4 *)(lVar6 + 0x1b8) = 0xffffffff;
      *(undefined4 *)(lVar6 + 0x1f0) = 0xffffffff;
    }
    uVar1 = *param_2;
    uVar5 = (uVar1 & 0xff00ff00) >> 8 | (uVar1 & 0xff00ff) << 8;
    uVar5 = uVar5 >> 0x10 | uVar5 << 0x10;
    if (-1 < *(int *)(param_1 + 4)) {
      uVar5 = uVar1;
    }
    iVar4 = decodeInstruction_4_isra_0(DecoderTable32,param_4,uVar5);
    if (iVar4 == 0) {
      iVar4 = decodeInstruction_4_isra_0(DecoderTableFallback32,param_4,uVar5);
      uVar5 = MCInst_getOpcode(param_4);
      if (uVar5 == 0xbf5) goto LAB_001c9f18;
      if (uVar5 < 0xbf6) {
        if (uVar5 != 0x6d4) {
          if (0x6d4 < uVar5) {
            if (uVar5 != 0xb3e) {
              if (uVar5 < 0xb3f) {
                if (uVar5 == 0xb39) goto LAB_001c9f18;
                if (uVar5 == 0xb3c) goto LAB_001c9da8;
              }
              else if (uVar5 == 0xb41) {
LAB_001c9da8:
                local_44 = 2;
                local_40 = 0;
                MCInst_insert0(param_4,2,auStack_48);
              }
              goto LAB_001c9d28;
            }
            goto LAB_001c9f18;
          }
          if (uVar5 != 0x6cf) {
            if ((uVar5 == 0x6d1) || (uVar5 == 0x6cc)) {
              local_44 = 1;
              local_40 = CONCAT44(local_40._4_4_,0x117);
              MCInst_insert0(param_4,2,auStack_48);
            }
            goto LAB_001c9d28;
          }
        }
LAB_001c9f58:
        local_44 = 2;
        local_40 = 0;
        MCInst_addOperand2(param_4,auStack_48);
        goto LAB_001c9d28;
      }
      if (uVar5 == 0x13db) goto LAB_001c9f18;
      if (uVar5 < 0x13dc) {
        if (uVar5 == 0xd7b) goto LAB_001c9ea0;
        if (uVar5 < 0xd7c) {
          if (uVar5 == 0xbfa) goto LAB_001c9f18;
          if ((uVar5 == 0xbfd) || (uVar5 == 0xbf8)) goto LAB_001c9da8;
        }
        else if (uVar5 - 0x10f6 < 9) {
          uVar7 = 0x155L >> ((ulong)(uVar5 - 0x10f6) & 0x3f);
joined_r0x001ca010:
          if ((uVar7 & 1) != 0) goto LAB_001c9f58;
        }
      }
      else {
        if (uVar5 == 0x14b7) goto LAB_001c9ea0;
        if (uVar5 < 0x14b8) {
          if (uVar5 == 0x13e0) goto LAB_001c9f18;
          if ((uVar5 == 0x13e3) || (uVar5 == 0x13de)) goto LAB_001c9da8;
        }
        else if (uVar5 - 0x16a4 < 7) {
          uVar7 = 0x55L >> ((ulong)(uVar5 - 0x16a4) & 0x3f);
          goto joined_r0x001ca010;
        }
      }
LAB_001c9d28:
      if (iVar4 == 0) {
        MCInst_clear(param_4);
        goto LAB_001c9d38;
      }
    }
    else {
      uVar5 = MCInst_getOpcode(param_4);
      if (uVar5 == 0xbf5) {
LAB_001c9f18:
        local_44 = 1;
        local_40 = CONCAT44(local_40._4_4_,0x117);
        MCInst_insert0(param_4,0,auStack_48);
        goto LAB_001c9d28;
      }
      if (uVar5 < 0xbf6) {
        if (uVar5 != 0x6d4) {
          if (0x6d4 < uVar5) {
            if (uVar5 != 0xb3e) {
              if (uVar5 < 0xb3f) {
                if (uVar5 == 0xb39) goto LAB_001c9f18;
                if (uVar5 == 0xb3c) goto LAB_001c9ef8;
              }
              else if (uVar5 == 0xb41) {
LAB_001c9ef8:
                local_44 = 2;
                local_40 = 0;
                MCInst_insert0(param_4,2,auStack_48);
              }
              goto LAB_001c9e7c;
            }
            goto LAB_001c9f18;
          }
          if (uVar5 != 0x6cf) {
            if ((uVar5 == 0x6d1) || (uVar5 == 0x6cc)) {
              local_44 = 1;
              local_40 = CONCAT44(local_40._4_4_,0x117);
              MCInst_insert0(param_4,2,auStack_48);
            }
            goto LAB_001c9e7c;
          }
        }
LAB_001c9e64:
        local_44 = 2;
        local_40 = 0;
        MCInst_addOperand2(param_4,auStack_48);
        goto LAB_001c9e7c;
      }
      if (uVar5 == 0x13db) goto LAB_001c9f18;
      if (uVar5 < 0x13dc) {
        if (uVar5 == 0xd7b) {
LAB_001c9ea0:
          local_44 = 1;
          local_40 = CONCAT44(local_40._4_4_,10);
          MCInst_insert0(param_4,0,auStack_48);
          uVar8 = MCInst_getOperand(param_4,2);
          MCInst_addOperand2(param_4,uVar8);
          goto LAB_001c9d28;
        }
        if (uVar5 < 0xd7c) {
          if (uVar5 == 0xbfa) goto LAB_001c9f18;
          if ((uVar5 == 0xbfd) || (uVar5 == 0xbf8)) goto LAB_001c9da8;
        }
        else if (uVar5 - 0x10f6 < 9) {
          uVar7 = 0x155L >> ((ulong)(uVar5 - 0x10f6) & 0x3f);
joined_r0x001c9fe4:
          if ((uVar7 & 1) != 0) goto LAB_001c9e64;
        }
      }
      else {
        if (uVar5 == 0x14b7) goto LAB_001c9ea0;
        if (uVar5 < 0x14b8) {
          if (uVar5 == 0x13e0) goto LAB_001c9f18;
          if ((uVar5 == 0x13e3) || (uVar5 == 0x13de)) goto LAB_001c9da8;
        }
        else if (uVar5 - 0x16a4 < 7) {
          uVar7 = 0x55L >> ((ulong)(uVar5 - 0x16a4) & 0x3f);
          goto joined_r0x001c9fe4;
        }
      }
    }
LAB_001c9e7c:
    bVar3 = iVar4 == 3;
    uVar9 = 4;
  }
  puVar2 = PTR___stack_chk_guard_005ffe88;
  *param_5 = uVar9;
  lVar6 = local_38 - *(long *)puVar2;
  if (lVar6 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(bVar3,puVar2,0,lVar6);
}

