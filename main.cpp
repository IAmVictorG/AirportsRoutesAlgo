#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <queue>

std::map<std::string, std::vector<std::string>> convertToSimpleMap(std::multimap<std::string, std::string> routes) {
    std::map<std::string, std::vector<std::string>> simpleMapList;
    for (const auto& [key, value] : routes) {
        simpleMapList[key].push_back(value);
    }
    return simpleMapList;
}

std::vector<std::string> bfs(std::string start, std::string destination, std::map<std::string, std::vector<std::string>>& adjList) {
    std::queue<std::vector<std::string>> q;
    q.push({start});
    
    while (!q.empty()) {
        std::vector<std::string> path = q.front();
        q.pop();
        std::string current = path.back();
        
        if (current == destination) {
            return path;
        }
        
        for (const auto& next : adjList[current]) {
            std::vector<std::string> newPath = path;
            newPath.push_back(next);
            q.push(newPath);
        }
    }
    
    return {};
}

int main() {
    std::multimap<std::string, std::string> routesT = {
        {"DSM", "ORD"},
        {"ORD", "BGI"},
        {"BGI", "LGA"},
        {"SIN", "CDG"},
        {"CDG", "SIN"},
        {"CDG", "BUD"},
        {"DEL", "DOH"},
        {"DEL", "CDG"},
        {"TLV", "DEL"},
        {"EWR", "HND"},
        {"HND", "ICN"},
        {"HND", "JFK"},
        {"ICN", "JFK"},
        {"JFK", "LGA"},
        {"EYW", "LHR"},
        {"LHR", "SFO"},
        {"SFO", "SAN"},
        {"SFO", "DSM"},
        {"SAN", "EYW"}
    };
    
    std::map<std::string, std::vector<std::string>> simpleMapList = convertToSimpleMap(routesT);
    std::vector<std::string> path = bfs("LHR", "DSM", simpleMapList);
    
    for (const auto& airport : path) {
        std::cout << airport;
        if (&airport != &path.back()) {
            std::cout << " -> ";
        }
    }
	std::cout << std::endl;
    
    return 0;
}
