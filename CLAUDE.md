# CLAUDE.md — llm-rag

## Build
```bash
cmake -B build && cmake --build build
```

## Key Constraint: SINGLE HEADER
`include/llm_rag.hpp` is the entire library. Never split into multiple files.

## Implementation Guard
```cpp
#define LLM_RAG_IMPLEMENTATION
#include "llm_rag.hpp"
```

## Common Mistakes
- Splitting the header
- Adding dependencies beyond libcurl
- Using exceptions in hot paths
- Forgetting RAII for resource handles
