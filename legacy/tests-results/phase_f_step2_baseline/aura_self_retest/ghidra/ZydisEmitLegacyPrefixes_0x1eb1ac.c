
int ZydisEmitLegacyPrefixes(ulong *param_1,undefined8 param_2)

{
  bool bVar1;
  int iVar2;
  
  bVar1 = (int)param_1[1] - 2U < 4;
  if ((((((*param_1 & 0x8000000) == 0) || (iVar2 = ZydisEmitByte(0xfffffff0,param_2), -1 < iVar2))
       && ((bVar1 || ((((*param_1 & 0x1c0000000) == 0 ||
                       (iVar2 = ZydisEmitByte(0xfffffff2,param_2), -1 < iVar2)) &&
                      (((*param_1 & 0x230000000) == 0 ||
                       (iVar2 = ZydisEmitByte(0xfffffff3,param_2), -1 < iVar2)))))))) &&
      (((((*param_1 & 0x2400000000) == 0 || (iVar2 = ZydisEmitByte(0x2e,param_2), -1 < iVar2)) &&
        (((*param_1 & 0x4000000000) == 0 || (iVar2 = ZydisEmitByte(0x36,param_2), -1 < iVar2)))) &&
       (((((((*param_1 & 0x8800000000) == 0 || (iVar2 = ZydisEmitByte(0x3e,param_2), -1 < iVar2)) &&
           (((*param_1 & 0x10000000000) == 0 || (iVar2 = ZydisEmitByte(0x26,param_2), -1 < iVar2))))
          && (((*param_1 & 0x20000000000) == 0 || (iVar2 = ZydisEmitByte(100,param_2), -1 < iVar2)))
          ) && (((*param_1 & 0x40000000000) == 0 ||
                (iVar2 = ZydisEmitByte(0x65,param_2), -1 < iVar2)))) &&
        ((((*param_1 & 0x1000000000) == 0 || (iVar2 = ZydisEmitByte(0x3e,param_2), -1 < iVar2)) &&
         ((bVar1 || (((*param_1 & 0x80000000000) == 0 ||
                     (iVar2 = ZydisEmitByte(0x66,param_2), -1 < iVar2)))))))))))) &&
     (((*param_1 & 0x100000000000) == 0 || (iVar2 = ZydisEmitByte(0x67,param_2), -1 < iVar2)))) {
    iVar2 = 0x100000;
  }
  return iVar2;
}

