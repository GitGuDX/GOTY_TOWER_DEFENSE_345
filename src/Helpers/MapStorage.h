#include <fstream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

class MapStorage {
private:
    std::string filename = "../SavedMaps/AverageMap.txt";

public:
    // Save Path and GridSize
    void saveData(const std::vector<sf::Vector2f>& path, const sf::Vector2i& gridSize) {
        std::ofstream file(filename);
        if (!file.is_open()) return;
    
        // Write GridSize as text (could be comma-separated or space-separated)
        file << gridSize.x << " " << gridSize.y << "\n";
    
        // Write Path size
        file << path.size() << "\n";
    
        // Write each path point
        for (const auto& point : path) {
            file << point.x << " " << point.y << "\n";  // Space-separated values
        }
    
        file.close();
    }
    

    // Load Path and GridSize
    bool loadData(std::vector<sf::Vector2f>& newPath, sf::Vector2i& gridSize) {
        std::ifstream file(filename);
        if (!file.is_open()) return false;

        // Read GridSize (space-separated values)
        file >> gridSize.x >> gridSize.y;
        //std::cout << "Loaded grid width: " << gridSize.x << ", height: " << gridSize.y << std::endl;

        // Read Path size
        size_t pathSize;
        file >> pathSize;
        //std::cout << "Path Size: " << pathSize << std::endl;

        if (pathSize <= 0) return false;

        // Resize vector to hold the path data
        newPath.clear();
        newPath.resize(pathSize);

        // Read each path point
        for (size_t i = 0; i < pathSize; ++i) {
            sf::Vector2f point;  // Create a Vector2i object to hold the point
            file >> point.x >> point.y;  // Read the x and y values into the Vector2i object
        
            // Optionally, you can print the point to debug
            //std::cout << "Read point: (" << point.x << ", " << point.y << ")" << std::endl;
        
            // Now push the point into the newPath vector
            newPath[i] = point;
        }

        file.close();
        return true;
    }
    
};
