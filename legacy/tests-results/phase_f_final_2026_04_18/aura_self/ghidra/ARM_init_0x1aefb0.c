
void ARM_init(undefined8 param_1)

{
  MCRegisterInfo_InitMCRegisterInfo
            (param_1,ARMRegDesc,0x121,0,0,&ARMMCRegisterClasses,0x67,0,0,ARMRegDiffLists,0,
             ARMSubRegIdxLists,0x39,0);
  return;
}

