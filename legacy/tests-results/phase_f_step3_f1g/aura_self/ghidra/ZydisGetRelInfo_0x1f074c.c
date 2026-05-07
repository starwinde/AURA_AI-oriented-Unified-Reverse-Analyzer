
undefined1 * ZydisGetRelInfo(uint param_1)

{
  if (param_1 == 0x73e) {
    return info_lookup_0 + 0x60;
  }
  if ((param_1 < 0x73f) && (param_1 < 0x1e4)) {
    if (0x1e0 < param_1) {
      return info_lookup_0 + 0x54;
    }
    if (param_1 < 0x189) {
      if (0x186 < param_1) {
LAB_001f08e0:
        return info_lookup_0 + 0xc;
      }
      if (param_1 == 0x186) {
        return info_lookup_0 + 0x48;
      }
      if ((param_1 < 0x187) && (param_1 < 0x186)) {
        if (0x17b < param_1) goto LAB_001f08e0;
        if (param_1 == 0x17a) {
          return info_lookup_0 + 0x3c;
        }
        if ((param_1 < 0x17b) && (param_1 < 0x17a)) {
          if (0x177 < param_1) goto LAB_001f08e0;
          if (param_1 < 0x178) {
            if (0x175 < param_1) {
              return info_lookup_0 + 0x30;
            }
            if (param_1 == 0x175) {
              return info_lookup_0 + 0x24;
            }
            if (param_1 < 0x176) {
              if (param_1 == 0x174) {
                return info_lookup_0 + 0x18;
              }
              if (param_1 < 0x175) {
                if (param_1 == 0x47) {
                  return info_lookup_0;
                }
                if ((0x46 < param_1) && (param_1 - 0x172 < 2)) goto LAB_001f08e0;
              }
            }
          }
        }
      }
    }
  }
  return (undefined1 *)0x0;
}

