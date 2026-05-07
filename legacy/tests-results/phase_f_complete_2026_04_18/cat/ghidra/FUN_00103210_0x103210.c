
int FUN_00103210(FILE *param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  __off_t _Var4;
  
  iVar1 = fileno(param_1);
  if (-1 < iVar1) {
    iVar1 = __freading(param_1);
    if (iVar1 != 0) {
      iVar1 = fileno(param_1);
      _Var4 = lseek(iVar1,0,1);
      if (_Var4 == -1) goto LAB_00103294;
    }
    iVar1 = __freading(param_1);
    if ((iVar1 != 0) && (((uint)param_1->_flags >> 8 & 1) != 0)) {
      if ((param_1->_IO_read_end == param_1->_IO_read_ptr) &&
         ((param_1->_IO_write_ptr == param_1->_IO_write_base &&
          (param_1->_IO_save_base == (char *)0x0)))) {
        iVar1 = fileno(param_1);
        _Var4 = lseek(iVar1,0,1);
        if (_Var4 != -1) {
          param_1->_offset = _Var4;
          param_1->_flags = param_1->_flags & 0xffffffef;
        }
      }
      else {
        fseeko(param_1,0,1);
      }
    }
    iVar1 = fflush(param_1);
    if (iVar1 != 0) {
      piVar3 = __errno_location();
      iVar1 = *piVar3;
      iVar2 = fclose(param_1);
      if (iVar1 != 0) {
        iVar2 = -1;
        *piVar3 = iVar1;
      }
      return iVar2;
    }
  }
LAB_00103294:
  iVar1 = fclose(param_1);
  return iVar1;
}

