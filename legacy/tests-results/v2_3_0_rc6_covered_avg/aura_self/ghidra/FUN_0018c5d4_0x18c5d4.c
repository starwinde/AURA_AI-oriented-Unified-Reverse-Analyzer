
char * FUN_0018c5d4(undefined4 param_1)

{
  switch(param_1) {
  case 0:
    return "OK (CS_ERR_OK)";
  case 1:
    return "Out of memory (CS_ERR_MEM)";
  case 2:
    return "Invalid/unsupported architecture(CS_ERR_ARCH)";
  case 3:
    return "Invalid handle (CS_ERR_HANDLE)";
  case 4:
    return "Invalid csh (CS_ERR_CSH)";
  case 5:
    return "Invalid mode (CS_ERR_MODE)";
  case 6:
    return "Invalid option (CS_ERR_OPTION)";
  case 7:
    return "Details are unavailable (CS_ERR_DETAIL)";
  case 8:
    return "Dynamic memory management uninitialized (CS_ERR_MEMSETUP)";
  case 9:
    return "Different API version between core & binding (CS_ERR_VERSION)";
  case 10:
    return "Information irrelevant in diet engine (CS_ERR_DIET)";
  case 0xb:
    return "Information irrelevant for \'data\' instruction in SKIPDATA mode (CS_ERR_SKIPDATA)";
  case 0xc:
    return "AT&T syntax is unavailable (CS_ERR_X86_ATT)";
  case 0xd:
    return "INTEL syntax is unavailable (CS_ERR_X86_INTEL)";
  case 0xe:
    return "MASM syntax is unavailable (CS_ERR_X86_MASM)";
  default:
    return "Unknown error code";
  }
}

