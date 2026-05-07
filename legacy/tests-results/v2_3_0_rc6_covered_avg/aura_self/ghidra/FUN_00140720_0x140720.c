
char * FUN_00140720(undefined4 param_1)

{
  switch(param_1) {
  case 0:
    return "OK";
  case 0xfffffff6:
    return "Patch/encode error";
  case 0xfffffff7:
    return "LLM error";
  case 0xfffffff8:
    return "Disassembly error";
  case 0xfffffff9:
    return "Parse error";
  case 0xfffffffa:
    return "Not found";
  case 0xfffffffb:
    return "Not supported";
  case 0xfffffffc:
    return "Invalid argument";
  case 0xfffffffd:
    return "I/O error";
  case 0xfffffffe:
    return "Out of memory";
  case 0xffffffff:
    return "Generic error";
  default:
    return "Unknown error";
  }
}

