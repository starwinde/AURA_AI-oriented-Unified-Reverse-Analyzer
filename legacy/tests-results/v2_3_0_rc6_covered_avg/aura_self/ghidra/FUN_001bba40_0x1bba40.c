
void FUN_001bba40(long param_1,int param_2)

{
  if (param_2 != 3) {
    *(undefined **)(param_1 + 0x28) = PTR_FUN_005fff90;
    *(code **)(param_1 + 0x78) = FUN_001b0b10;
    return;
  }
  *(undefined **)(param_1 + 0x28) = PTR_FUN_005fff10;
  *(code **)(param_1 + 0x78) = FUN_001b0b30;
  return;
}

