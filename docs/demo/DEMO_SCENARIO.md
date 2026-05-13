# AURA Demo Scenario

## 5-Minute Explanation

저희 프로젝트는 리버스 엔지니어링 결과를 LLM과 안전하게 연동하기 위한 보조 도구입니다. 기존의 Rizin/Ghidra 같은 분석 엔진은 그대로 활용하되, 그 결과를 AURA에서 통합해서 보여주고, LLM으로 넘어가기 전에 주민등록번호, 전화번호, 이메일 같은 민감정보를 자동으로 마스킹합니다.

핵심은 자체 디컴파일러를 새로 만드는 것이 아니라, 기존 분석 결과를 LLM에 넘길 때 발생할 수 있는 개인정보 노출 위험을 줄이는 보호 계층을 구현한 것입니다.

## 2-Minute Demo

1. 민감정보가 포함된 benign 테스트 EXE를 AURA에 추가합니다.
2. Analyze를 눌러 외부 엔진 기반 분석을 실행합니다.
3. Demo 화면에서 `Analyze -> Detect -> Mask -> Export` 흐름을 보여줍니다.
4. 주민등록번호, 전화번호, 이메일, 토큰형 문자열이 `900*********67` 같은 형태로 마스킹된 것을 보여줍니다.
5. LLM/MCP Export Preview에서 `original_included: false`와 마스킹된 전송 값만 포함되는 것을 보여줍니다.
6. 결론: LLM을 이용한 리버스 엔지니어링 보조는 유지하면서 민감정보 노출 위험을 줄입니다.

## Demo Fixture Build

데모용 소스는 악성코드가 아닌 benign 정적 분석 fixture입니다.

```powershell
cl /nologo /O2 tests\fixtures\sources\aura_demo_sensitive.c /Fe:.scratch\aura_demo_sensitive.exe
```

Visual Studio 개발자 PowerShell이 아닌 일반 PowerShell에서 `cl`이 없다면, CMake 빌드 환경 또는 설치된 MSVC Developer PowerShell에서 위 명령을 실행합니다.

## Demo Success Criteria

- 설명 없이도 화면에서 원본 값이 마스킹된 것을 알 수 있어야 한다.
- LLM/MCP로 나가는 JSON에 원본 민감정보가 없어야 한다.
- GUI Demo 화면에 분석, 탐지, 마스킹, 전송 흐름이 순서대로 보여야 한다.
- 발표자가 Rizin/Ghidra 내부 구현보다 AURA가 만든 보호 흐름을 먼저 설명해야 한다.

## Team Speaking Rule

프로젝트를 설명할 때 먼저 “자체 디컴파일러”를 말하지 않는다. 먼저 다음 문장으로 시작한다.

> AURA는 리버스 엔지니어링 결과를 LLM에 안전하게 넘기기 위해 민감정보를 자동 마스킹하는 보호형 분석 환경입니다.

