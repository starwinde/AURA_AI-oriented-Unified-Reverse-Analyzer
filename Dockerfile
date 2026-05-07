# AURA — AI-powered Unified Reverse Analyzer
# Multi-stage Docker build: build stage + minimal runtime

# ── Stage 1: Build ──────────────────────────────────────────────────────────
FROM ubuntu:24.04 AS builder

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    python3-minimal \
    libcurl4-openssl-dev \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /src
COPY . /src

# Build Capstone static library
RUN cmake -B third_party/capstone/build \
    -DCAPSTONE_BUILD_SHARED=OFF \
    -DCAPSTONE_BUILD_TESTS=OFF \
    third_party/capstone \
    && cmake --build third_party/capstone/build -j"$(nproc)"

# Build Zydis static library (zycore bundled)
RUN cmake -B third_party/zydis/build \
    -DZYDIS_BUILD_EXAMPLES=OFF \
    -DZYDIS_BUILD_TOOLS=OFF \
    -DZYDIS_BUILD_DOXYGEN=OFF \
    third_party/zydis \
    && cmake --build third_party/zydis/build -j"$(nproc)"

# Build AURA CLI (Release mode, GUI disabled)
RUN cmake -S . -B build \
    -DCMAKE_BUILD_TYPE=Release \
    -DAURA_BUILD_GUI=OFF \
    && cmake --build build --target aura -j"$(nproc)"

# ── Stage 2: Runtime ────────────────────────────────────────────────────────
FROM ubuntu:24.04 AS runtime

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
    libcurl4t64 \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

COPY --from=builder /src/build/aura /usr/local/bin/aura

ENTRYPOINT ["aura"]
CMD ["--version"]
