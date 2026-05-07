
char ZydisGetMaxAddressSize(undefined4 *param_1)

{
  char local_1;
  
  local_1 = ZydisGetAszFromHint(param_1[8]);
  if (local_1 == '\0') {
    local_1 = ZydisGetMachineModeWidth(*param_1);
  }
  return local_1;
}

