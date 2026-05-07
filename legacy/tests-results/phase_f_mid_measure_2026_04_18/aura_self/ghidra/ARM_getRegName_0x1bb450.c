
void ARM_getRegName(long param_1,int param_2)

{
  if (param_2 != 3) {
    *(undefined **)(param_1 + 0x28) = PTR_ARM_reg_name_005fff90;
    *(code **)(param_1 + 0x78) = getRegisterName;
    return;
  }
  *(undefined **)(param_1 + 0x28) = PTR_ARM_reg_name2_005fff10;
  *(code **)(param_1 + 0x78) = getRegisterName_digit;
  return;
}

