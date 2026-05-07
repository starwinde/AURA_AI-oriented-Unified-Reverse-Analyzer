# IrVal.type vs IrVal.sort — Stage 5 Phase B feasibility analysis

Phase 2-X-7 Stage 3 introduced `IrVal.sort` (an `IrSort {kind, width, align}`
triple modelled on RzIL Phase B) alongside the pre-existing `IrVal.type`
(an `IrType` enum). Stage 4 wired every `ir_validator` rule (1s–6s) through
`sort` only. That left an open question at the end of Stage 4:

> Does `type` still carry information the rest of the pipeline depends on,
> or has it become redundant with `sort`?

Stage 5 Phase B set out to answer that question and — if the answer was
"redundant" — retire `.type`. This document records the finding, which
is that `.type` **must be kept**.

## Survey numbers

Measured on `src/decompiler/` at the head of the Stage 5 branch:

| metric | count |
|---|---|
| files referencing `IrVal.type` / `IrInstr.dst.type` / `.srcs[i].type` | 22 |
| raw `.type` reads or writes inside `src/decompiler/` | 208 |
| raw `IR_TYPE_PTR` callers outside the lifter/bridge | 118 (across 16 files) |

Validator rules are already sort-only (Stage 4). Every other site listed
above still speaks in `IrType`.

## Why `.sort` cannot replace `.type`

`ir_sort_from_type()` (src/decompiler/ir_sort.c) collapses semantically
distinct `IrType`s onto the same `IrSort`:

| IrType | IrSort yielded | collision |
|---|---|---|
| `IR_TYPE_INT64` | `bv(64)` | — |
| `IR_TYPE_PTR`   | `bv(64)` (with 8-byte alignment hint) | **collides with `IR_TYPE_INT64`** |
| `IR_TYPE_MMX`   | `bv(64)` | **collides with `IR_TYPE_INT64`** |
| `IR_TYPE_VEC128`| `bv(128)` | unique |

The alignment hint on `ir_sort_ptr` is specifically marked as *ignored*
by `ir_sort_equal` (Stage 1 semantic — see `test_ir_sort.c` line 97).
So `sort` has no way to separate a pointer from a 64-bit integer.

## Call sites that rely on the distinction

- `type_inference.c:223-228` — walks the IR and bails on `def->dst.type
  == IR_TYPE_PTR` to avoid sign-extending pointers. A sort-only rewrite
  would drop this guard and introduce silent numeric-pointer confusion.
- `type_constraint.c` — 52 `.type` references driving the
  pointer-propagation constraint solver. All keyed on `IR_TYPE_PTR`
  propagation through COPY / ADD / SUB.
- `ptr_chain.c`, `struct_recovery.c`, `aggregate_types.c` — record layout
  recovery reads `IR_TYPE_PTR` to seed root-pointer sets.
- `IrInstr.dst_pointee_width` (decompiler.h:319) — its contract is
  literally "valid when `dst.type == IR_TYPE_PTR`". Retiring `.type`
  would leave that field without a gating predicate.
- AArch64 / x86_64 / RISC-V / MIPS / PPC lifters — every LEA /
  effective-address computation sets `.type = IR_TYPE_PTR` to mark the
  result as pointer-shaped before `type_inference` runs.

## Decision

**Keep `IrVal.type`.** Retirement is not a mechanical rewrite — it
would require a prior semantic enrichment of `IrSort` (a `PTR` kind or
equivalent) before ~200 call sites across 22 files could be migrated.
That enrichment was not part of the Stage 5 charter and is bigger than
the "Phase B 가 대규모 refactor 가 되면 (callsite 50+ 건)" safety cap
set at the top of the Stage.

Stage 5 therefore ships Phase A (opbuilder DSL macros) only. Any future
`.type` removal must first extend `IrSort` so that `bv(64) ≠ ptr(64) ≠
mmx(64)` is a first-class predicate, and must budget at least 20
distinct callsite-migration commits. That work is explicitly deferred —
track it as a follow-up item outside Stage 5.

## Alternative considered: keep both

`.sort` remains authoritative for `ir_validator` (Stage 4). `.type`
remains authoritative for pointer / vector / float-width inference and
for HIR emission. The two fields are kept consistent by `ir_val_new`
and by the explicit positional `{id, type, imm, sort}` init pattern. No
action item beyond this documentation.
