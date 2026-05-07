
void switchD_001d07f4::caseD_0(void)

{
  int iVar1;
  ulong uVar2;
  ulong unaff_x21;
  long in_stack_00000098;
  
  SStream_concat0();
  uVar2 = (unaff_x21 >> 0x37 & 0x3f) - 1;
  if (0x23 < uVar2) {
switchD_001d1088_caseD_18:
    if (in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printOperand();
    return;
  }
  switch(uVar2 & 0xffffffff) {
  case 0:
    if (in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printSVERegOp();
    return;
  case 1:
    printSVERegOp();
    break;
  case 2:
    goto switchD_001cca1c_default;
  case 3:
    printSVERegOp();
    break;
  case 4:
    printVRegOperand();
    break;
  case 5:
    printVectorIndex();
    break;
  case 6:
    if (in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printOperand();
    return;
  case 7:
    if (in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printComplexRotationOp();
    return;
  case 8:
    if (in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printCondCode();
    return;
  case 9:
    SStream_concat0();
    break;
  case 10:
    goto switchD_001d3be4_caseD_a;
  case 0xb:
    if (in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printComplexRotationOp();
    return;
  case 0xc:
    if (in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printSVERegOp();
    return;
  case 0xd:
    if (in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printImmHex();
    return;
  case 0xe:
    if (in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printExactFPImm_constprop_0();
    return;
  case 0xf:
    printSVERegOp();
    break;
  case 0x10:
    printSVERegOp();
    break;
  case 0x11:
    if (in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printExactFPImm_constprop_0();
    return;
  case 0x12:
    if (in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printVectorIndex();
    return;
  case 0x13:
    if (in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printExactFPImm_constprop_0();
    return;
  case 0x14:
    printImmScale();
    SStream_concat0();
    if (in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access();
    return;
  case 0x15:
    printImmScale();
    SStream_concat0();
    if (in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access();
    return;
  case 0x16:
    printImmScale();
    SStream_concat0();
    if (in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access();
    return;
  case 0x17:
    printImmScale();
    break;
  case 0x18:
    printImmScale();
    break;
  case 0x19:
    printImmScale();
    break;
  case 0x1a:
    printMemExtend_constprop_0();
    SStream_concat0();
    if (in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access();
    return;
  case 0x1b:
    printMemExtend_constprop_0();
    SStream_concat0();
    if (in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access();
    return;
  case 0x1c:
    printMemExtend_constprop_0();
    SStream_concat0();
    if (in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access();
    return;
  case 0x1d:
    printMemExtend_constprop_0();
    SStream_concat0();
    if (in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access();
    return;
  case 0x1e:
    printMemExtend_constprop_0();
    SStream_concat0();
    if (in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access();
    return;
  case 0x1f:
    printMemExtend_constprop_0();
    SStream_concat0();
    if (in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access();
    return;
  case 0x20:
    printMemExtend_constprop_0();
    SStream_concat0();
    if (in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access();
    return;
  case 0x21:
    printMemExtend_constprop_0();
    SStream_concat0();
    if (in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access();
    return;
  case 0x22:
    printMemExtend_constprop_0();
    SStream_concat0();
    if (in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access();
    return;
  case 0x23:
    printMemExtend_constprop_0();
    SStream_concat0();
    if (in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    set_mem_access();
    return;
  default:
    goto switchD_001d1088_caseD_18;
  }
  uVar2 = unaff_x21 >> 0x3d;
  if (uVar2 == 4) {
LAB_001d4bdc:
    if (in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    printComplexRotationOp();
    return;
  }
  if (4 < uVar2) {
    if (uVar2 == 5) {
      SStream_concat0();
      if (in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                         in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      set_mem_access();
      return;
    }
    if (uVar2 == 6) {
      SStream_concat0();
      if (in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                         in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88);
      }
      arm64_op_addVectorArrSpecifier();
      return;
    }
switchD_001cca1c_default:
    if (in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                       in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88);
    }
    return;
  }
  if (uVar2 != 2) {
    if (uVar2 != 3) {
      if (uVar2 == 1) {
        SStream_concat0();
        if (in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
          __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                           in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88);
        }
        arm64_op_addVectorArrSpecifier();
        return;
      }
      goto switchD_001cca1c_default;
    }
    SStream_concat0();
    MCInst_getOpcode();
    iVar1 = MCInst_getOpcode();
    if ((0xc < iVar1 - 0x77aU) || ((0x1505UL >> ((ulong)(iVar1 - 0x77aU) & 0x3f) & 1) == 0))
    goto LAB_001d4bdc;
  }
switchD_001d3be4_caseD_a:
  if (in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                     in_stack_00000098 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  printComplexRotationOp();
  return;
}

