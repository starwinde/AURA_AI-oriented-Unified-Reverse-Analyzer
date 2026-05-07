
void FUN_001168f0(long param_1,undefined8 param_2)

{
  bool bVar1;
  undefined4 uVar2;
  byte *pbVar3;
  byte bVar4;
  ulong uVar5;
  undefined8 uVar6;
  _IO_FILE *p_Var7;
  char *pcVar8;
  undefined1 auStack_2c8 [19];
  char local_2b5 [637];
  long local_38;
  
  local_38 = *(long *)PTR___stack_chk_guard_0013ffd0;
  if (((DAT_00141291 & 1) != 0) && (uVar5 = FUN_0010aca0(4), (uVar5 & 1) != 0)) {
    FUN_0010b000(&DAT_001400f0);
    FUN_0010b000(&DAT_00140130);
    FUN_0010b000(&DAT_00140100);
  }
  if ((DAT_00140f30 & 1) != 0) {
    uVar2 = DAT_00140ef4;
    if (DAT_00140f2c == 4) {
      uVar2 = 0;
    }
    if ((*(byte *)(param_1 + 0xa8) & 1) == 0) {
      pcVar8 = "?";
    }
    else {
      pcVar8 = "?";
      if (*(ulong *)(param_1 + 0x20) != 0) {
        pcVar8 = local_2b5 + 1;
        local_2b5[1] = 0;
        uVar5 = *(ulong *)(param_1 + 0x20);
        do {
          pcVar8 = pcVar8 + -1;
          *pcVar8 = (char)uVar5 + (char)(uVar5 / 10) * -10 + '0';
          bVar1 = 9 < uVar5;
          uVar5 = uVar5 / 10;
        } while (bVar1);
      }
    }
    __printf_chk(2,&DAT_0011bcf0,uVar2,pcVar8);
  }
  if ((DAT_00140f28 & 1) != 0) {
    uVar2 = DAT_00140ef8;
    if (DAT_00140f2c == 4) {
      uVar2 = 0;
    }
    if ((*(byte *)(param_1 + 0xa8) & 1) == 0) {
      __printf_chk(2,&DAT_0011bcf0,uVar2,&DAT_0011bce8);
    }
    else {
      uVar6 = FUN_0010beb0(*(undefined8 *)(param_1 + 0x58),auStack_2c8,DAT_00141018,0x200,
                           DAT_00141010);
      __printf_chk(2,&DAT_0011bcf0,uVar2,uVar6);
    }
  }
  if ((DAT_0014101c & 1) != 0) {
    uVar2 = DAT_00140f0c;
    if (DAT_00140f2c == 4) {
      uVar2 = 0;
    }
    __printf_chk(2,&DAT_0011bcf0,uVar2,*(undefined8 *)(param_1 + 0xa0));
  }
  FUN_0010dc40(param_1,0,0,param_2);
  if (DAT_00140f80 != 0) {
    bVar4 = FUN_0010af10(*(undefined1 *)(param_1 + 0xa8),*(undefined4 *)(param_1 + 0x28),
                         *(undefined4 *)(param_1 + 0x98));
    if (bVar4 != 0) {
      p_Var7 = *(_IO_FILE **)PTR_stdout_0013ffc0;
      DAT_001402c0 = DAT_001402c0 + 1;
      pbVar3 = (byte *)p_Var7->_IO_write_ptr;
      if (pbVar3 < p_Var7->_IO_write_end) {
        p_Var7->_IO_write_ptr = (char *)(pbVar3 + 1);
        *pbVar3 = bVar4;
      }
      else {
        __overflow(p_Var7,(uint)bVar4);
      }
    }
  }
  if (local_38 - *(long *)PTR___stack_chk_guard_0013ffd0 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_0013ffd0,0,
                     local_38 - *(long *)PTR___stack_chk_guard_0013ffd0);
  }
  return;
}

