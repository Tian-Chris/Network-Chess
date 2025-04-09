#include "layer.h"
#include "../global/pch.h"

// Layer constructor
Layer::Layer(const std::string& fileName, float gridSize)
    : gridSize(gridSize) {
    height = 0;
    length = 0;
    loadFromFile(fileName);
    //createSprites();
}

void Layer::loadFromFile(const std::string& fileName) {
    std::string fullName = "text/" + fileName;
    std::ifstream file(fullName);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << fileName << std::endl;
        return;
    }

    std::string line;

    // Read the first line for texture mapping
    std::getline(file, line);
    std::istringstream textureStream(line);
    int textureID;
    std::string textureFileName;
    while (textureStream >> textureID >> textureFileName) {
        // Prepend the folder path
        std::string fullPath = "images/" + textureFileName;

        // Load the texture and store it in the map
        sf::Texture texture;
        if (!texture.loadFromFile(fullPath)) {
            std::cerr << "Error: Could not load texture: " << fullPath << std::endl;
            return;
        }
        textures[textureID] = texture;
    }
    //cout << "loadFromFile middle \n";
    
    // Read the remaining lines for the grid
    while (std::getline(file, line)) {
        std::vector<Cell*> row;  // Store pointers to cells
        std::istringstream stream(line);
        int type;
        float x = 0.0f;
        //cout << "loadFromFile preloop \n";
        while (stream >> type) {
            //cout << "grid.size: " << grid.size() <<"\n";
            //cout << "x " << x <<"\n";
            //cout << "type: " << type <<"\n";
            // Only create a cell if the type is a valid texture ID
            if (textures.find(type) != textures.end()) {
                // Dynamically allocate a Cell object
                Cell* newCell = new Cell(sf::Vector2f(x * gridSize, grid.size() * gridSize), type, &textures);
                //cout << "prepush";
                row.push_back(newCell);  // Store pointer in the row
            } else {
                row.push_back(nullptr);  // Empty cell (nullptr)
            }
            x++;
            //cout << "out \n";
        }
        //cout << "out of loop \n";
        length = x;
        height++;
        grid.push_back(row);
        //cout << "after push \n";
    }
    //cout << "out \n";
}



// Create sprites based on grid data and texture mapping
// void Layer::createSprites() {
//     for (size_t y = 0; y < grid.size(); y++) {
//         for (size_t x = 0; x < grid[y].size(); x++) {
//             // Only create a sprite if the cell's type is valid
//             if (grid[y][x].spriteType != 0) {
//                 // Get the corresponding texture from the textures map
//                 sf::Sprite sprite(textures[grid[y][x].spriteType]);
//                 sprite.setPosition(grid[y][x].position);
//                 sprites.push_back(sprite);
//             }
//         }
//     }
// }


// Draw the grid's sprites to the window
void Layer::draw(sf::RenderWindow& window) {
    for (size_t y = 0; y < grid.size(); ++y) {
        for (size_t x = 0; x < grid[y].size(); ++x) {
            // Only draw if the pointer is not null
            if (grid[y][x] != nullptr) {
                window.draw(*grid[y][x]->sprite);
            }
        }
    }
}

void Layer::changeCell()
{

}

Layer::~Layer() {
    for (auto& row : grid) {
        for (auto& cell : row) {
            delete cell;  // Free each dynamically allocated cell
        }
    }
}

void Layer::downloadMap(const string& mystring)
{
    std::ofstream file(mystring);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file for writing: " << mystring << std::endl;
        return;
    }

    // Write the texture mapping
    for (const auto& pair : textures) {
        file << pair.first << " images/" << pair.second.getNativeHandle() << "\n";
    }

    // Write the grid data
    for (const auto& row : grid) {
        for (size_t i = 0; i < row.size(); ++i) {
            if (row[i] != nullptr) {
                file << row[i]->spriteType;
            }
            if (i < row.size() - 1) {
                file << " ";
            }
        }
        file << "\n";
    }

    file.close();
}
