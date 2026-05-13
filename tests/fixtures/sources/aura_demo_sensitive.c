/*
 * aura_demo_sensitive.c -- benign static-analysis demo fixture.
 *
 * This source intentionally hardcodes non-real demo values so AURA can show
 * sensitive-string detection, masking, and safe LLM/MCP export behavior.
 * It is not malware and should not be used as a live-execution sample.
 *
 * Copyright 2026 AURA Project Contributors
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>

static const char *demo_rrn = "900101-1234567";
static const char *demo_phone = "010-1234-5678";
static const char *demo_email = "student.demo@example.com";
static const char *demo_token = "sk-demo-1234567890abcdef";

static void print_demo_contact(void) {
    printf("rrn=%s\n", demo_rrn);
    printf("phone=%s\n", demo_phone);
    printf("email=%s\n", demo_email);
    printf("token=%s\n", demo_token);
}

int main(void) {
    print_demo_contact();
    return 0;
}
