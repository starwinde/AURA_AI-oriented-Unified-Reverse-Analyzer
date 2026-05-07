
undefined8 DecodeBankedReg_isra_0(undefined8 param_1,undefined4 param_2)

{
  long lVar1;
  
  lVar1 = lookupBankedRegByEncoding(param_2);
  if (lVar1 != 0) {
    MCOperand_CreateImm0(param_1,param_2);
    return 3;
  }
  return 0;
}

