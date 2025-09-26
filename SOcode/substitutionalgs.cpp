#include <iostream>
#include <string>
#include <string_view> 
#include <filesystem>
#include <fstream>
#include <unordered_map>
#include <list>
#include <queue>
#include <vector>

// Pre-processar o arquivo de trace para extrair os acessos de página
std::vector<long long> preprocess_trace(const std::string& filename) {
    std::ifstream trace_file(filename);
    if (!trace_file) {
        std::cerr << "Erro ao abrir o arquivo de trace: " << filename << std::endl;
        exit(1);
    }

    std::vector<long long> requests;
    std::string access;
    while (trace_file >> access) {
        if (access.back() == ',') {
            access.pop_back();
        }
        requests.push_back(std::stoll(access, nullptr, 16)); // Converter de hexadecimal para inteiro
    }
    return requests;
}


int optimal_alg(int pages, const std::vector<long long>& requests, bool debug) {
    if (requests.empty()) return 0;
    int faults = 0;
    std::unordered_map<long long, bool> page_set; // Mapa para lookup rápido
    std::list<long long> page_list;               // Lista para manter a ordem e iterar

    //Construir um mapa de futuras utilizações
    std::unordered_map<long long, std::queue<int>> future_uses;
    for (int i = 0; i < requests.size(); ++i) {
        future_uses[requests[i]].push(i);
    }
    
     for (int i = 0; i < requests.size(); ++i) {
        long long current_page_request = requests[i];
        
        // Remover a utilização atual da fila de futuras utilizações
        future_uses[current_page_request].pop();

        // Se a página não está na memória (Page Fault)
        if (page_set.find(current_page_request) == page_set.end()) {
            faults++;

            // Se houver espaço livre, basta adicionar a página
            if (page_list.size() < pages) {
                page_set[current_page_request] = true;
                page_list.push_back(current_page_request);
                continue;
            }

            // A memória está cheia, encontre a página a ser substituída
            long long page_to_replace = -1;
            int furthest_distance = -1;

            // Encontre a página que será usada mais longe no futuro
            for (long long page_in_memory : page_list) {
                // Se uma página nunca for usada novamente, é a melhor vitima
                if (future_uses[page_in_memory].empty()) {
                    page_to_replace = page_in_memory;
                    break;
                }

                // Caso contrário, encontre o que tem a próxima utilização mais distante
                if (future_uses[page_in_memory].front() > furthest_distance) {
                    furthest_distance = future_uses[page_in_memory].front();
                    page_to_replace = page_in_memory;
                }
            }

            // Substituir a página
            page_set.erase(page_to_replace);
            page_list.remove(page_to_replace);
            if (debug) {
                std::cout << "[Otimo] Substituindo página " << page_to_replace << " por " << current_page_request << std::endl;
            }

            // Adicionar a nova página
            page_set[current_page_request] = true;
            page_list.push_back(current_page_request);
        }
    }
    return faults;
}

// Implementação do algoritmo FIFO
int fifo(int pages, const std::vector<long long>& requests, bool debug){
    int faults = 0;
    std::unordered_map<long long, bool> page_map; // Mapa para lookup rápido
    std::queue<long long> page_queue;             // Fila para rastrear a ordem das páginas

    for (long long page : requests) {
        if (page_map.find(page) == page_map.end()) { // Página não está na memória
            faults++;
            if (page_queue.size() >= pages) {
                // Memória cheia, remover a página mais antiga
                long long page_to_replace = page_queue.front();
                page_queue.pop();
                page_map.erase(page_to_replace);
                if (debug) {
                    std::cout << "[FIFO] Substituindo página " << page_to_replace << " por " << page << std::endl;
                }
            }
            // Adicionar a nova página
            page_map[page] = true;
            page_queue.push(page);
        }
    }
    return faults;
}
int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Uso: " << argv[0] << " <trace_file> <num_pages> [debug]" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    int pages = std::stoi(argv[2]);
    bool debug = (argc > 3 && std::string(argv[3]) == "debug");

    // Pre-processar o arquivo de trace
    std::vector<long long> requests = preprocess_trace(filename);

    // Executar algoritmos nos dados em memória
    int faults_optimal = optimal_alg(pages, requests, debug);
    int faults_fifo = fifo(pages, requests, debug);

    std::cout << "Faults (Ótimo): " << faults_optimal << std::endl;
    std::cout << "Faults (FIFO): " << faults_fifo << std::endl;
    return 0;
}