/*
 * aura_smoke.c — orchestrator_smoke fixture source.
 *
 * Compiled into:
 *   tests/fixtures/bin/elf_smoke.x86_64      (Linux,   gcc)
 *   tests/fixtures/bin/pe_smoke.x86_64.exe   (Windows, MSVC cl)
 *
 * Regenerate via scripts/rebuild_fixtures.{sh,ps1} when a deterministic
 * change to the fixture is intentional. Invariant gates (CONTEXT.md) are
 * white-box and absorb byte-level variation, so day-to-day compiler updates
 * do not require regeneration.
 *
 * Functions are deliberately simple but distinct so Rizin's analysis emits
 * stable per-function entries. `aura_helper_add` is the rename target used
 * by the override round-trip invariant.
 *
 * Copyright 2026 AURA Project Contributors
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>

int aura_helper_add(int a, int b) {
    return a + b;
}

int aura_helper_mul(int a, int b) {
    return a * b;
}

int aura_helper_sub(int a, int b) {
    return a - b;
}

int main(void) {
    int s = aura_helper_add(2, 3);
    int p = aura_helper_mul(s, 4);
    int d = aura_helper_sub(p, 1);
    printf("%d\n", d);
    return 0;
}
