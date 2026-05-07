# AURA 개발 환경 점검 결과

> 점검일: 2026-03-25
> 플랫폼: Linux (Ubuntu 24.04, arm64)

---

## 컴파일러

| 도구 | 버전 | 상태 | 비고 |
|------|------|------|------|
| GCC | 13.3.0 | ✅ | C11/C++17 지원 |
| Clang | — | ⚠️ 미설치 | 필요 시 `sudo apt install clang` |

---

## 빌드 도구

| 도구 | 버전 | 상태 |
|------|------|------|
| CMake | 3.28.3 | ✅ (≥ 3.16 충족) |
| Make | 4.3 | ✅ |

**빌드 시스템 확정 (D-2)**: **CMake** (2026-03-25 사용자 확정)

---

## 라이브러리 (PRD §4.2 기준)

| 라이브러리 | 요구 버전 | 설치 버전 | 출처 | 상태 |
|-----------|----------|----------|------|------|
| Capstone | ≥ 5.0 | **5.0** | third_party/ 소스 빌드 | ✅ |
| libcurl (런타임) | ≥ 7.0 | 8.5.0 | 시스템 | ✅ (런타임) |
| libcurl (dev) | — | 미설치 | — | ⚠️ Phase 6 전 설치 필요 |
| cJSON (런타임) | 최신 | 1.7.17 | 시스템 | ✅ (런타임) |
| cJSON (dev) | — | 미설치 | — | ⚠️ Phase 6 전 설치 필요 |
| jansson (런타임) | 최신 | 2.14 | 시스템 | ✅ (런타임) |
| jansson (dev) | — | 미설치 | — | ⚠️ Phase 6 전 설치 필요 |

---

## Capstone 빌드 정보

```
위치:   third_party/capstone/                (git tag: 5.0.1)
빌드:   third_party/capstone/build/libcapstone.a  (정적, 4.8MB)
아키텍처: x86/x86_64, ARM, ARM64 활성화
빌드 옵션:
  -DCMAKE_BUILD_TYPE=Release
  -DCAPSTONE_BUILD_TESTS=OFF
  -DCAPSTONE_BUILD_CSTOOL=OFF
  -DCAPSTONE_X86_SUPPORT=ON
  -DCAPSTONE_ARM_SUPPORT=ON
  -DCAPSTONE_ARM64_SUPPORT=ON
```

---

## 빌드 시스템 (CMakeLists.txt)

```bash
# 빌드
cmake -B build && make -C build -j$(nproc)

# 테스트
cd build && ctest

# 클린
make -C build clean

# 설치 (선택)
sudo make -C build install
```

`compile_commands.json` → `build/compile_commands.json` 심링크로 프로젝트 루트에 연결됨 (mcp-cpp 활성화).

---

## 이슈 현황

| 이슈 | 상태 | 비고 |
|------|------|------|
| Capstone 버전 불충족 (4.0.2) | ✅ 해결 | third_party/에서 5.0 소스 빌드 |
| D-2 빌드 시스템 미결 | ✅ 확정 | CMake 선택 (2026-03-25) |
| libcurl/cjson/jansson dev 패키지 미설치 | ⚠️ 보류 | Phase 6 (LLM 연동) 진입 전 설치 |

---

## Phase 6 전 필수 설치 명령

```bash
sudo apt install -y libcurl4-openssl-dev libcjson-dev libjansson-dev
```
