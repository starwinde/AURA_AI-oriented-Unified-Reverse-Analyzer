
void AArch64_init(undefined8 param_1)

{
  MCRegisterInfo_InitMCRegisterInfo
            (param_1,AArch64RegDesc,0x2a2,0,0,&AArch64MCRegisterClasses,0xca,0,0,AArch64RegDiffLists
             ,0,AArch64SubRegIdxLists,100,0);
  return;
}

