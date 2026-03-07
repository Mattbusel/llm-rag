# llm-rag

Full retrieval-augmented generation pipeline in C++. Chunk, embed, store, retrieve, generate. One header.

![C++17](https://img.shields.io/badge/C%2B%2B-17-blue)
![License: MIT](https://img.shields.io/badge/License-MIT-green)
![Single Header](https://img.shields.io/badge/library-single--header-orange)

---

## 30-second quickstart

```cpp
#define LLM_RAG_IMPLEMENTATION
#include "llm_rag.hpp"
#include <cstdlib>
#include <iostream>

int main() {
    llm::RagConfig cfg;
    cfg.embed_api_key = std::getenv("OPENAI_API_KEY");
    cfg.llm_api_key   = std::getenv("OPENAI_API_KEY");

    llm::RagPipeline rag(cfg);

    rag.ingest("The Eiffel Tower was built in 1889 by Gustave Eiffel.", "paris");
    rag.ingest("Photosynthesis converts sunlight into glucose.", "biology");

    auto result = rag.query("Who built the Eiffel Tower?");
    std::cout << result.answer << "\n";
}
```

---

## Installation

```bash
cp include/llm_rag.hpp your-project/
```

Link with `-lcurl`.

---

## Pipeline

```
ingest(text) -> chunk -> embed -> store in flat binary index
query(q)     -> embed(q) -> cosine search -> build prompt -> generate
```

## API Reference

```cpp
llm::RagConfig cfg;
cfg.chunk_size    = 512;     // chars per chunk
cfg.chunk_overlap = 64;      // overlap between chunks
cfg.top_k         = 5;       // chunks to retrieve per query
cfg.embed_model   = "text-embedding-3-small";
cfg.llm_model     = "gpt-4o-mini";

llm::RagPipeline rag(cfg);

// Ingest
rag.ingest("Long document text...", "source_name");
rag.ingest_file("document.txt");
rag.save_index(); // persist .rag_index file

// Query
auto r = rag.query("What does the document say about X?");
std::cout << r.answer << "\n";
for (auto& c : r.retrieved_chunks)
    std::cout << c.text << "\n";

// Just retrieve, no generation
auto chunks = rag.retrieve("query");

// Chunking utility (standalone)
auto chunks = llm::chunk_text(text, 512, 64);
```

---

## Building

```bash
cmake -B build && cmake --build build
export OPENAI_API_KEY=sk-...
./build/chunk_demo  # no API needed
./build/basic_rag
```

---

## See Also

| Repo | What it does |
|------|-------------|
| [llm-stream](https://github.com/Mattbusel/llm-stream) | Stream OpenAI & Anthropic responses token by token |
| [llm-cache](https://github.com/Mattbusel/llm-cache) | Cache responses, skip redundant calls |
| [llm-cost](https://github.com/Mattbusel/llm-cost) | Token counting + cost estimation |
| [llm-retry](https://github.com/Mattbusel/llm-retry) | Retry with backoff + circuit breaker |
| [llm-format](https://github.com/Mattbusel/llm-format) | Structured output enforcement |
| [llm-embed](https://github.com/Mattbusel/llm-embed) | Text embeddings + nearest-neighbor search |
| [llm-pool](https://github.com/Mattbusel/llm-pool) | Concurrent request pool + rate limiting |
| [llm-log](https://github.com/Mattbusel/llm-log) | Structured JSONL logger for LLM calls |
| [llm-template](https://github.com/Mattbusel/llm-template) | Prompt templating with loops + conditionals |
| [llm-agent](https://github.com/Mattbusel/llm-agent) | Tool-calling agent loop |
| [llm-rag](https://github.com/Mattbusel/llm-rag) | Full RAG pipeline |
| [llm-eval](https://github.com/Mattbusel/llm-eval) | Consistency and quality evaluation |

---

## License

MIT — see [LICENSE](LICENSE).
