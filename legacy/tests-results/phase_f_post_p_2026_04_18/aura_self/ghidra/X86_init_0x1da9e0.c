
void X86_init(undefined8 param_1)

{
  MCRegisterInfo_InitMCRegisterInfo
            (param_1,X86RegDesc,0x115,0,0,&X86MCRegisterClasses,0x56,0,0,X86RegDiffLists,0,
             X86SubRegIdxLists,9,0);
  return;
}

