#include "layer.h"
#include "../global/pch.h"

// Layer constructor
Layer::Layer(float gridSize) 
    : gridSize(gridSize)
{
    height = 0;
    length = 0;
    name = "Empty";
}

Layer::Layer(const std::string& fileName, float gridSize)
    : gridSize(gridSize) {
    height = 0;
    length = 0;
    name = fileName;
    loadFromFile(fileName);
}

Layer::~Layer() {
    // No need to delete cell as we are using unique_ptr
}

void Layer::loadFromFile(const std::string& fileName) {
    clearLayer();
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
    
        // Save the int-string pair in the textureFileNames map
        textureFileNames[textureID] = textureFileName;
    }
    //cout << "loadFromFile middle \n";
    
    // Read the remaining lines for the grid
    while (std::getline(file, line)) {
        std::vector<std::unique_ptr<Cell>> row;  // Store pointers to cells
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
                auto newCell = std::make_unique<Cell>(sf::Vector2f(x * gridSize, grid.size() * gridSize), type, textures);
                //cout << "prepush";
                row.push_back(std::move(newCell));  // Store pointer in the row
            } else {
                row.push_back(nullptr);  // Empty cell (nullptr)
            }
            x++;
            //cout << "out \n";
        }
        //cout << "out of loop \n";
        length = x;
        height++;
        grid.push_back(std::move(row));
        //cout << "after push \n";
    }
    //cout << "out \n";
}

void Layer::clearLayer() {
    grid.clear();
}

// Draw the grid's sprites to the window
void Layer::draw(sf::RenderWindow& window) {
    for (size_t y = 0; y < grid.size(); ++y) {
        for (size_t x = 0; x < grid[y].size(); ++x) {
            // Only draw if the pointer is not null
            if (grid[y][x]) {
                window.draw(*grid[y][x]->sprite);
            }
        }
    }
}

void Layer::changeCell(size_t x, size_t y, int newType) {
    if (x < grid.size() && y < grid[x].size() && textures.find(newType) != textures.end()) {
        grid[y][x] = std::make_unique<Cell>(sf::Vector2f(x * gridSize, y * gridSize), newType, textures);    
    }
}

void Layer::saveLayer(const std::string& mystring)
{
    std::ofstream file(mystring);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file for writing: " << mystring << std::endl;
        return;
    }

    // Write the texture mapping
    for (const auto& pair : textureFileNames) {
        file << pair.first << " " << pair.second; // Write the texture ID and file name directly
    }
    file << "\n";

    // Write the grid data
    for (const auto& row : grid) {
        for (size_t i = 0; i < row.size(); ++i) {
            if (row[i] != nullptr) {
                file << row[i]->spriteType;
            } else {
                file << "0"; // Write 0 for empty cells
            }
            if (i < row.size() - 1) {
                file << " ";
            }
        }
        file << "\n";
    }

    file.close();
}

int Layer::getCellType(size_t x, size_t y)
{
    if (x < grid.size() && y < grid[x].size() && grid[y][x] != nullptr) {
        return grid[y][x]->spriteType;
    }
    return -1;  // Return -1 if the cell is nullptr or out of bounds
}

string Layer::getCellName(size_t x, size_t y)
{
    int type = getCellType(x, y);
        if(type == -1)
        {
            return "Error: Ptr is nullptr";
        }
        if(type == 0)
        {
            return "Empty";
        }
    return textureFileNames[type];
}