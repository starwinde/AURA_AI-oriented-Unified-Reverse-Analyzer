
void _printOperand(long param_1,undefined8 param_2,undefined8 param_3)

{
  char cVar1;
  undefined8 uVar2;
  ulong uVar3;
  undefined *puVar4;
  undefined8 uVar5;
  undefined *puVar6;
  long lVar7;
  ulong uVar8;
  undefined1 uStack_39;
  long local_38;
  
  local_38 = *(long *)PTR___stack_chk_guard_005ffe88;
  uVar2 = MCInst_getOperand(param_1,param_2,0);
  uVar3 = MCOperand_isReg();
  if ((uVar3 & 1) == 0) {
    uVar3 = MCOperand_isImm(uVar2);
    if ((uVar3 & 1) != 0) {
      uVar5 = MCInst_getOpcode(param_1);
      cVar1 = X86_immediate_size(uVar5,&uStack_39);
      uVar3 = MCOperand_getImm(uVar2);
      if ((long)uVar3 < 0) {
        if (*(int *)(*(long *)(param_1 + 800) + 100) == 0) {
          if ((long)uVar3 < -9) {
            SStream_concat(param_3,"$-0x%lx",-uVar3);
          }
          else {
            SStream_concat(param_3,"$-%lu",-uVar3);
          }
        }
        else {
          uVar8 = uVar3;
          if (cVar1 != '\0') {
            if (cVar1 == '\x02') {
              uVar8 = uVar3 & 0xffff;
            }
            else if (cVar1 == '\x04') {
              uVar8 = uVar3 & 0xffffffff;
            }
            else {
              uVar8 = uVar3 & 0xff;
              if (cVar1 != '\x01') {
                uVar8 = uVar3;
              }
            }
          }
          SStream_concat(param_3,"$0x%lx",uVar8);
        }
      }
      else if ((long)uVar3 < 10) {
        SStream_concat(param_3,&DAT_001fddf8);
      }
      else {
        SStream_concat(param_3,"$0x%lx");
      }
    }
    lVar7 = local_38 - *(long *)PTR___stack_chk_guard_005ffe88;
    puVar6 = (undefined *)0x0;
    puVar4 = PTR___stack_chk_guard_005ffe88;
    if (lVar7 == 0) {
      return;
    }
  }
  else {
    puVar4 = (undefined *)MCOperand_getReg(uVar2);
    lVar7 = 0;
    puVar6 = PTR___stack_chk_guard_005ffe88;
    if (local_38 == *(long *)PTR___stack_chk_guard_005ffe88) {
      SStream_concat(param_3,&DAT_001fddd8,
                     &AsmStrs_0 + *(ushort *)(RegAsmOffset_1 + (ulong)((int)puVar4 - 1) * 2));
      return;
    }
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(puVar4,puVar6,lVar7);
}

