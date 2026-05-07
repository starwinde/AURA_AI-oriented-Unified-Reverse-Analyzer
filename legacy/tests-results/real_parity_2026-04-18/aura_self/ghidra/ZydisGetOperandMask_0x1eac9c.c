
ushort ZydisGetOperandMask(long param_1)

{
  undefined1 local_4;
  undefined1 local_3;
  undefined2 local_2;
  
  local_2 = (ushort)*(byte *)(param_1 + 0x28);
  local_4 = 3;
  for (local_3 = 0; local_3 < *(byte *)(param_1 + 0x28); local_3 = local_3 + 1) {
    local_2 = (ushort)(*(int *)(param_1 + (long)(int)(uint)local_3 * 0x40 + 0x30) + -1 <<
                      (ulong)(local_4 & 0x1f)) | local_2;
    local_4 = local_4 + 2;
  }
  return local_2;
}

