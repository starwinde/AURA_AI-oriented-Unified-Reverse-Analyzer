
undefined * FUN_001f22bc(uint param_1)

{
  if (param_1 == 0x73e) {
    return &DAT_0058b660;
  }
  if ((param_1 < 0x73f) && (param_1 < 0x1e4)) {
    if (0x1e0 < param_1) {
      return &DAT_0058b654;
    }
    if (param_1 < 0x189) {
      if (0x186 < param_1) {
LAB_001f23ec:
        return &DAT_0058b60c;
      }
      if (param_1 == 0x186) {
        return &DAT_0058b648;
      }
      if ((param_1 < 0x187) && (param_1 < 0x186)) {
        if (0x17b < param_1) goto LAB_001f23ec;
        if (param_1 == 0x17a) {
          return &DAT_0058b63c;
        }
        if ((param_1 < 0x17b) && (param_1 < 0x17a)) {
          if (0x177 < param_1) goto LAB_001f23ec;
          if (param_1 < 0x178) {
            if (0x175 < param_1) {
              return &DAT_0058b630;
            }
            if (param_1 == 0x175) {
              return &DAT_0058b624;
            }
            if (param_1 < 0x176) {
              if (param_1 == 0x174) {
                return &DAT_0058b618;
              }
              if (param_1 < 0x175) {
                if (param_1 == 0x47) {
                  return &DAT_0058b600;
                }
                if ((0x46 < param_1) && (param_1 - 0x172 < 2)) goto LAB_001f23ec;
              }
            }
          }
        }
      }
    }
  }
  return (undefined *)0x0;
}

