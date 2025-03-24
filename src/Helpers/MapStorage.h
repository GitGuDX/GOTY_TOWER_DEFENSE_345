#include <fstream>
#include <vector>
#include <string>

struct TileData {
    int x, y;
    int type;
};

class MapStorage {
private:
    std::string filename = "AverageMap";

public:
    void saveMap(const std::vector<std::vector<TileData>>& map) {
        std::ofstream file(filename, std::ios::binary);
        if (!file.is_open()) return;
        
        size_t rows = map.size();
        file.write(reinterpret_cast<const char*>(&rows), sizeof(rows));
        
        for (const auto& row : map) {
            size_t cols = row.size();
            file.write(reinterpret_cast<const char*>(&cols), sizeof(cols));
            file.write(reinterpret_cast<const char*>(row.data()), cols * sizeof(TileData));
        }
        file.close();
    }

    std::vector<std::vector<TileData>> loadMap() {
        std::vector<std::vector<TileData>> map;
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) return map;
        
        size_t rows;
        file.read(reinterpret_cast<char*>(&rows), sizeof(rows));
        map.resize(rows);
        
        for (auto& row : map) {
            size_t cols;
            file.read(reinterpret_cast<char*>(&cols), sizeof(cols));
            row.resize(cols);
            file.read(reinterpret_cast<char*>(row.data()), cols * sizeof(TileData));
        }
        file.close();
        return map;
    }
};