
/* WARNING: Type propagation algorithm not settling */

uint DecodeRegListOperand_isra_0(long param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  
  uVar1 = MCInst_getOpcode();
  if (uVar1 != 0xb15) {
    if (uVar1 < 0xb16) {
      if ((6 < uVar1 - 0x276) || ((0x55UL >> ((ulong)(uVar1 - 0x276) & 0x3f) & 1) == 0)) {
LAB_00194fd8:
        if (param_2 != 0) {
          if ((param_2 & 1) != 0) {
            MCOperand_CreateReg0(param_1,0x42);
          }
          if ((param_2 >> 1 & 1) != 0) {
            MCOperand_CreateReg0(param_1,0x43);
          }
          if ((param_2 >> 2 & 1) != 0) {
            MCOperand_CreateReg0(param_1,0x44);
          }
          if ((param_2 >> 3 & 1) != 0) {
            MCOperand_CreateReg0(param_1,0x45);
          }
          if ((param_2 >> 4 & 1) != 0) {
            MCOperand_CreateReg0(param_1,0x46);
          }
          if ((param_2 >> 5 & 1) != 0) {
            MCOperand_CreateReg0(param_1,0x47);
          }
          if ((param_2 >> 6 & 1) != 0) {
            MCOperand_CreateReg0(param_1,0x48);
          }
          if ((param_2 >> 7 & 1) != 0) {
            MCOperand_CreateReg0(param_1,0x49);
          }
          if ((param_2 >> 8 & 1) != 0) {
            MCOperand_CreateReg0(param_1,0x4a);
          }
          if ((param_2 >> 9 & 1) != 0) {
            MCOperand_CreateReg0(param_1,0x4b);
          }
          if ((param_2 >> 10 & 1) != 0) {
            MCOperand_CreateReg0(param_1,0x4c);
          }
          if ((param_2 >> 0xb & 1) != 0) {
            MCOperand_CreateReg0(param_1,0x4d);
          }
          if ((param_2 >> 0xc & 1) != 0) {
            MCOperand_CreateReg0(param_1,0x4e);
          }
          if ((param_2 >> 0xd & 1) != 0) {
            MCOperand_CreateReg0(param_1,0xc);
          }
          if ((param_2 >> 0xe & 1) != 0) {
            MCOperand_CreateReg0(param_1,10);
          }
          if ((param_2 >> 0xf & 1) != 0) {
            MCOperand_CreateReg0(param_1,0xb);
          }
          return 3;
        }
        return 0;
      }
    }
    else if (((uVar1 - 0xbe3 & 0xfffffffd) != 0) && (uVar1 != 0xb17)) goto LAB_00194fd8;
  }
  MCInst_getOperand(param_1,0);
  iVar2 = MCOperand_getReg();
  if (param_2 != 0) {
    uVar1 = param_2 & 1;
    if ((param_2 & 1) == 0) {
      uVar1 = 3;
    }
    else {
      MCOperand_CreateReg0(param_1,0x42);
      iVar3 = MCOperand_getReg(param_1 + (ulong)*(byte *)(param_1 + 4) * 0x10);
      if (iVar2 != iVar3) {
        uVar1 = 3;
      }
    }
    if ((param_2 >> 1 & 1) != 0) {
      MCOperand_CreateReg0(param_1,0x43);
      iVar3 = MCOperand_getReg(param_1 + (ulong)*(byte *)(param_1 + 4) * 0x10);
      if (iVar2 == iVar3) {
        uVar1 = 1;
      }
    }
    if ((param_2 >> 2 & 1) != 0) {
      MCOperand_CreateReg0(param_1,0x44);
      iVar3 = MCOperand_getReg(param_1 + (ulong)*(byte *)(param_1 + 4) * 0x10);
      if (iVar2 == iVar3) {
        uVar1 = 1;
      }
    }
    if ((param_2 >> 3 & 1) != 0) {
      MCOperand_CreateReg0(param_1,0x45);
      iVar3 = MCOperand_getReg(param_1 + (ulong)*(byte *)(param_1 + 4) * 0x10);
      if (iVar2 == iVar3) {
        uVar1 = 1;
      }
    }
    if ((param_2 >> 4 & 1) != 0) {
      MCOperand_CreateReg0(param_1,0x46);
      iVar3 = MCOperand_getReg(param_1 + (ulong)*(byte *)(param_1 + 4) * 0x10);
      if (iVar2 == iVar3) {
        uVar1 = 1;
      }
    }
    if ((param_2 >> 5 & 1) != 0) {
      MCOperand_CreateReg0(param_1,0x47);
      iVar3 = MCOperand_getReg(param_1 + (ulong)*(byte *)(param_1 + 4) * 0x10);
      if (iVar2 == iVar3) {
        uVar1 = 1;
      }
    }
    if ((param_2 >> 6 & 1) != 0) {
      MCOperand_CreateReg0(param_1,0x48);
      iVar3 = MCOperand_getReg(param_1 + (ulong)*(byte *)(param_1 + 4) * 0x10);
      if (iVar2 == iVar3) {
        uVar1 = 1;
      }
    }
    if ((param_2 >> 7 & 1) != 0) {
      MCOperand_CreateReg0(param_1,0x49);
      iVar3 = MCOperand_getReg(param_1 + (ulong)*(byte *)(param_1 + 4) * 0x10);
      if (iVar2 == iVar3) {
        uVar1 = 1;
      }
    }
    if ((param_2 >> 8 & 1) != 0) {
      MCOperand_CreateReg0(param_1,0x4a);
      iVar3 = MCOperand_getReg(param_1 + (ulong)*(byte *)(param_1 + 4) * 0x10);
      if (iVar2 == iVar3) {
        uVar1 = 1;
      }
    }
    if ((param_2 >> 9 & 1) != 0) {
      MCOperand_CreateReg0(param_1,0x4b);
      iVar3 = MCOperand_getReg(param_1 + (ulong)*(byte *)(param_1 + 4) * 0x10);
      if (iVar2 == iVar3) {
        uVar1 = 1;
      }
    }
    if ((param_2 >> 10 & 1) != 0) {
      MCOperand_CreateReg0(param_1,0x4c);
      iVar3 = MCOperand_getReg(param_1 + (ulong)*(byte *)(param_1 + 4) * 0x10);
      if (iVar2 == iVar3) {
        uVar1 = 1;
      }
    }
    if ((param_2 >> 0xb & 1) != 0) {
      MCOperand_CreateReg0(param_1,0x4d);
      iVar3 = MCOperand_getReg(param_1 + (ulong)*(byte *)(param_1 + 4) * 0x10);
      if (iVar2 == iVar3) {
        uVar1 = 1;
      }
    }
    if ((param_2 >> 0xc & 1) != 0) {
      MCOperand_CreateReg0(param_1,0x4e);
      iVar3 = MCOperand_getReg(param_1 + (ulong)*(byte *)(param_1 + 4) * 0x10);
      if (iVar2 == iVar3) {
        uVar1 = 1;
      }
    }
    if ((param_2 >> 0xd & 1) != 0) {
      MCOperand_CreateReg0(param_1,0xc);
      iVar3 = MCOperand_getReg(param_1 + (ulong)*(byte *)(param_1 + 4) * 0x10);
      if (iVar2 == iVar3) {
        uVar1 = 1;
      }
    }
    if ((param_2 >> 0xe & 1) != 0) {
      MCOperand_CreateReg0(param_1,10);
      iVar3 = MCOperand_getReg(param_1 + (ulong)*(byte *)(param_1 + 4) * 0x10);
      if (iVar2 == iVar3) {
        uVar1 = 1;
      }
    }
    if ((param_2 >> 0xf & 1) != 0) {
      MCOperand_CreateReg0(param_1,0xb);
      iVar3 = MCOperand_getReg(param_1 + (ulong)*(byte *)(param_1 + 4) * 0x10);
      if (iVar2 == iVar3) {
        uVar1 = 1;
      }
    }
    return uVar1;
  }
  return 0;
}

