# 03b — `tests/decompiler/*` typed-emit fmemopen callsite 마이그레이션

**Status**: ready-for-agent
**Depends on**: 01, 03a (helper 패턴 참조)
**Spawned from**: 03a (2026-05-03)

## 배경

03a 진행 중 grep 재측정에서 `dwarf_emit_types` / `pdb_emit_types` / `exc_flow_emit` / `sr_emit_typedefs` 4개 emit API 가 fmemopen-backed FILE\* 로 사용되는 12 callsite 발견. 03a 의 single-helper 명세 (`ir_emit_pseudoc_with_strbuf`) 로는 처리 불가하여 별도 이슈로 분리.

## 영향 파일 + callsite

| 파일 | callsites | emit API |
|---|---|---|
| tests/decompiler/test_dwarf_types.c | 4 | `dwarf_emit_types`, `dwarf_emit_enriched` |
| tests/decompiler/test_pdb_types.c | 4 | `pdb_emit_types`, `pdb_emit_enriched` |
| tests/decompiler/test_exception_flow.c | 3 | `exc_flow_emit` |
| tests/decompiler/test_struct_recovery.c | 1 | `sr_emit_typedefs` |
| **합계** | **12** | 4 distinct |

## DoD

- [ ] 4 emit API 각각에 thin `_with_strbuf` 어댑터 추가 (03a 의 `ir_emit_pseudoc_with_strbuf` 와 동일 패턴: `tmpfile() + fread + aura_strbuf_append`)
- [ ] 4 헤더에 신규 변형 선언
- [ ] 12 callsite 의 fmemopen 제거, AuraStrBuf 로 치환
- [ ] `grep -E 'open_memstream|fmemopen' tests/decompiler/` 결과 0
- [ ] Linux ctest: 영향 받는 4 테스트 GREEN

## 신규 helper 명세

```c
/* src/decompiler/types/dwarf.c (or wherever dwarf_emit_types lives) */
AuraError dwarf_emit_types_with_strbuf(const DwarfInfo *dw, AuraStrBuf *out);
AuraError dwarf_emit_enriched_with_strbuf(const IrFunc *func,
                                          const DwarfInfo *dw,
                                          AuraStrBuf *out);

/* src/decompiler/types/pdb.c (or wherever pdb_emit_types lives) */
AuraError pdb_emit_types_with_strbuf(const PdbInfo *pdb, AuraStrBuf *out);
AuraError pdb_emit_enriched_with_strbuf(const IrFunc *func,
                                        const PdbInfo *pdb,
                                        AuraStrBuf *out);

/* src/decompiler/exception_flow.c */
AuraError exc_flow_emit_with_strbuf(const IrFunc *func, const Cfg *cfg,
                                    const EhFrameInfo *eh,
                                    const SehInfo *seh,
                                    AuraStrBuf *out);

/* src/decompiler/struct_recovery.c */
AuraError sr_emit_typedefs_with_strbuf(const SRResult *result,
                                       AuraStrBuf *out);
```

각각 본체는 03a 의 `ir_emit_pseudoc_with_strbuf` 패턴 그대로 (~30 LOC).

## 비고

- 03a 와 같은 `tmpfile() + fread` 모델 (issue 01 단절 정책은 production emit core 만 해당, FILE*-only API 어댑터엔 미적용)
- production 본체 무수정
- 신규 API 들은 export 표면을 늘리지만 callsite 가 test 내부로 한정되므로 GUI/pipeline 영향 0
- 03a 가 완료된 직후 진행 시 컨텍스트 일관성 ↑
