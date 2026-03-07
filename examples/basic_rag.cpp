#define LLM_RAG_IMPLEMENTATION
#include "llm_rag.hpp"
#include <cstdlib>
#include <iostream>
int main() {
    const char* ekey = std::getenv("OPENAI_API_KEY");
    const char* lkey = std::getenv("OPENAI_API_KEY");
    if (!ekey || !ekey[0]) { std::cerr << "OPENAI_API_KEY not set\n"; return 1; }
    llm::RagConfig cfg;
    cfg.embed_api_key = ekey;
    cfg.llm_api_key   = lkey;
    cfg.chunk_size    = 200;
    cfg.chunk_overlap = 30;
    cfg.top_k         = 2;
    cfg.index_path    = ".rag_demo";
    llm::RagPipeline rag(cfg);
    // Ingest 3 hardcoded passages
    rag.ingest("The Eiffel Tower was built in 1889 for the World Fair in Paris. "
               "It was designed by Gustave Eiffel and stands 330 meters tall.", "paris_doc");
    rag.ingest("Photosynthesis is the process by which plants use sunlight, water, "
               "and carbon dioxide to produce oxygen and energy in the form of glucose.", "biology_doc");
    rag.ingest("The Python programming language was created by Guido van Rossum "
               "and first released in 1991. It emphasizes code readability.", "python_doc");
    std::cout << "Ingested " << rag.chunk_count() << " chunks.\n\n";
    std::string question = "Who designed the Eiffel Tower?";
    std::cout << "Question: " << question << "\n";
    auto result = rag.query(question);
    std::cout << "\nRetrieved " << result.retrieved_chunks.size() << " chunks:\n";
    for (const auto& c : result.retrieved_chunks)
        std::cout << "  [" << c.source << "] " << c.text.substr(0, 80) << "...\n";
    std::cout << "\nAnswer: " << result.answer << "\n";
    return 0;
}
