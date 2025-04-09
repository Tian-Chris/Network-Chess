#ifndef LAYER_H
#define LAYER_H

#include <vector>
#include <unordered_map>
#include <string>
#include "cell.h"


class Layer {
public:
    Layer(float gridSize);
    Layer(const std::string& fileName, float gridSize);
    ~Layer();
    void draw(sf::RenderWindow& window);
    /**
     * @brief Load the layer from a file in the folder images/
     */
    void loadFromFile(const std::string& fileName);

    /**
     * @brief Save the current layer to a file in the folder images/
     * @param mystring The name of the file to save the layer
     */
    void saveLayer(const std::string& mystring);
    void changeCell(size_t x, size_t y, int newType); //unfinished
    void clearLayer();
    void addCell(int x, int y, std::unique_ptr<Cell> cell); //unfinished
    void removeCell(size_t x, size_t y); //added new method

    /**
     * @brief Get the type of the cell at the specified coordinates
     * @param x The x coordinate of the cell
     * @param y The y coordinate of the cell
     * @return Returns -1 if nullptr or out of bounds
     */
    int getCellType(size_t x, size_t y);

    /**
     * @brief Get the name of the cell at the specified coordinates
     * @param x The x coordinate of the cell
     * @param y The y coordinate of the cell
     * @return Returns "Empty" if cell type == 0, returns an error message (Error: Ptr is nullptr) if nullptr or out of bounds
     */
    std::string getCellName(size_t x, size_t y);

    private:
    std::string name; //Layer name
    std::vector<std::vector<std::unique_ptr<Cell>>> grid; // Changed to unique_ptr
    std::unordered_map<int, sf::Texture> textures;  // Map texture IDs to textures
    std::unordered_map<int, std::string> textureFileNames;

    //pixel width of each grid
    float gridSize;
    int height;
    int length;
};

#endif