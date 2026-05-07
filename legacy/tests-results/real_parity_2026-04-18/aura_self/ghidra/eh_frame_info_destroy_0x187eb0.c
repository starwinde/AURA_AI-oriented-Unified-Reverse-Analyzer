
void eh_frame_info_destroy(undefined8 *param_1)

{
  if (param_1 != (undefined8 *)0x0) {
    free((void *)*param_1);
    free((void *)param_1[2]);
    free((void *)param_1[4]);
    free(param_1);
    return;
  }
  return;
}

