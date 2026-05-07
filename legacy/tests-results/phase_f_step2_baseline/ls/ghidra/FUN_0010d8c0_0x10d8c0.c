
void FUN_0010d8c0(byte *param_1,undefined8 param_2,undefined4 param_3,long param_4,char param_5,
                 long param_6,long param_7)

{
  byte *pbVar1;
  char *pcVar2;
  byte bVar3;
  undefined *puVar4;
  size_t sVar5;
  ulong uVar6;
  void *__ptr;
  char *__ptr_00;
  _IO_FILE *p_Var7;
  byte bVar8;
  long lVar9;
  size_t local_2090;
  byte local_2071;
  byte *local_2070;
  byte local_2068 [968];
  undefined8 local_1ca0;
  long local_68;
  
  local_1ca0 = 0;
  local_68 = *(long *)PTR___stack_chk_guard_0013ffd0;
  local_2070 = local_2068;
  sVar5 = FUN_00112c20(&local_2070,param_1,param_2,param_3,0,&local_2071);
  puVar4 = PTR_stdout_0013ffc0;
  if (local_2071 != 0 && param_5 != '\0') {
    p_Var7 = *(_IO_FILE **)PTR_stdout_0013ffc0;
    pcVar2 = p_Var7->_IO_write_ptr;
    DAT_001402c0 = DAT_001402c0 + 1;
    if (pcVar2 < p_Var7->_IO_write_end) {
      p_Var7->_IO_write_ptr = pcVar2 + 1;
      *pcVar2 = ' ';
    }
    else {
      __overflow(p_Var7,0x20);
    }
  }
  if (param_4 != 0) {
    uVar6 = FUN_0010aca0(4);
    if ((uVar6 & 1) == 0) {
      FUN_0010b000(&DAT_001400f0);
      FUN_0010b000(param_4);
      FUN_0010b000(&DAT_00140100);
    }
    else {
      FUN_0010b000();
      FUN_0010b000(&DAT_00140100);
      FUN_0010b000(&DAT_001400f0);
      FUN_0010b000(param_4);
      FUN_0010b000(&DAT_00140100);
    }
  }
  bVar8 = DAT_00141280;
  local_2090 = sVar5;
  if (param_7 == 0) {
    lVar9 = 0;
    bVar8 = 0;
  }
  else {
    if ((DAT_00141280 & 1) == 0) {
      lVar9 = 0;
    }
    else if (((local_2071 | DAT_00140ef0 ^ 1) & 1) == 0) {
      p_Var7 = *(_IO_FILE **)puVar4;
      pbVar1 = (byte *)p_Var7->_IO_write_ptr;
      bVar3 = *local_2070;
      if (pbVar1 < p_Var7->_IO_write_end) {
        p_Var7->_IO_write_ptr = (char *)(pbVar1 + 1);
        *pbVar1 = bVar3;
      }
      else {
        __overflow(p_Var7,(uint)bVar3);
      }
      lVar9 = 1;
      local_2090 = sVar5 - 2;
    }
    else {
      lVar9 = 0;
      bVar8 = 0;
    }
    __ptr = (void *)FUN_0010d770(DAT_00141288,0);
    __ptr_00 = (char *)FUN_0010d770(param_7,1);
    pcVar2 = "/";
    if (*__ptr_00 == '/') {
      pcVar2 = "";
    }
    __printf_chk(2,&DAT_0011bcc0,__ptr,pcVar2);
    free(__ptr);
    free(__ptr_00);
  }
  if (param_6 == 0) {
    fwrite_unlocked(local_2070 + lVar9,1,local_2090,*(FILE **)puVar4);
    DAT_001402c0 = DAT_001402c0 + sVar5;
  }
  else {
    if ((DAT_00141290 & 1) != 0) {
      FUN_0010cce0(param_6);
    }
    fwrite_unlocked(local_2070 + lVar9,1,local_2090,*(FILE **)puVar4);
    DAT_001402c0 = DAT_001402c0 + sVar5;
    if ((DAT_00141290 & 1) != 0) {
      FUN_0010cce0(param_6);
    }
  }
  if ((param_7 != 0) && (fwrite_unlocked(&DAT_0011bcd8,1,6,*(FILE **)puVar4), (bVar8 & 1) != 0)) {
    p_Var7 = *(_IO_FILE **)puVar4;
    pbVar1 = (byte *)p_Var7->_IO_write_ptr;
    bVar8 = local_2070[sVar5 - 1];
    if (pbVar1 < p_Var7->_IO_write_end) {
      p_Var7->_IO_write_ptr = (char *)(pbVar1 + 1);
      *pbVar1 = bVar8;
    }
    else {
      __overflow(p_Var7,(uint)bVar8);
    }
  }
  if (local_2070 != param_1 && local_2068 != local_2070) {
    free(local_2070);
  }
  if (local_68 - *(long *)PTR___stack_chk_guard_0013ffd0 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(sVar5 + local_2071,PTR___stack_chk_guard_0013ffd0,0,
                   local_68 - *(long *)PTR___stack_chk_guard_0013ffd0);
}

