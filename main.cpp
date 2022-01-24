#include <iostream>
#include <vector>
#include <random>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>


struct Rectangle
{
    int height = 0;
    int width = 3;

    int xLocation = 0;
    int yLocation = 0;

    sf::Color colour = sf::Color(160, 82, 45);
};


int randomGenerator(int min, int max);
void fillVector(Rectangle rect, std::vector<Rectangle>& vector, sf::Image image);
void paintVector(std::vector<Rectangle>& vector, sf::Image& image);
void bubbleSort(std::vector<Rectangle>& vector, sf::Image& image, sf::RenderWindow& window, sf::Texture texture, sf::Sprite sprite);


int main()
{
    int width = 1000;
    int height = 800;
    bool isSpacePressed = false;

    sf::RenderWindow window(sf::VideoMode(width, height), "Bubble Sort");
    sf::Event event;

    sf::Image image;
    image.create(width, height);

    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            image.setPixel(i, j, sf::Color(255, 255, 255));
        }
    }

    sf::Texture texture;
    texture.loadFromImage(image);
    sf::Sprite sprite;
    sprite.setTexture(texture);

    Rectangle rectangle;
    std::vector<Rectangle> rectanglesVector;

    fillVector(rectangle, rectanglesVector, image);
    paintVector(rectanglesVector, image);


    while (window.isOpen())
    {
        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Space || sf::Keyboard::Enter)
                {
                    isSpacePressed = true;
                }
            }
        }


        window.clear();


        texture.loadFromImage(image);    
        sprite.setTexture(texture);

        if(isSpacePressed)
        {
            bubbleSort(rectanglesVector, image, window, texture, sprite); // Value and reference passes seems equal?
            isSpacePressed = false;
        }

        window.draw(sprite);


        window.display();
    }

    return 0;    
}


int randomGenerator(int min, int max)
{
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    std::uniform_int_distribution<> distribution(min, max);

    return distribution(generator);
}


void fillVector(Rectangle rect, std::vector<Rectangle>& vector, sf::Image image)
{
    int xOffset = 0;
    
    while(xOffset < image.getSize().x)
    {
        rect.height = randomGenerator(1, (image.getSize().y - 50));
        if(rect.height < 5)
            rect.height = 5;
        

        rect.xLocation = xOffset;
        rect.yLocation = image.getSize().y - rect.height;

        vector.push_back(rect);

        xOffset += 5;
    }
}


void paintVector(std::vector<Rectangle>& vector, sf::Image& image)
{
    for(int i = 0; i < vector.size(); i++)
    {
        for(int x = 0; x < vector[i].width; x++)
        {
            for(int y = 0; y < vector[i].height; y++)
            {
                image.setPixel(vector[i].xLocation + x, vector[i].yLocation + y, vector[i].colour);
            }
        }
    }
}


void bubbleSort(std::vector<Rectangle>& vector, sf::Image& image, sf::RenderWindow& window, sf::Texture texture, sf::Sprite sprite)
{
    Rectangle tempRect;
    int tempX;

    for(int i = 0; i < vector.size(); i++)
    {
        for(int j = 0; j < vector.size() -1; j++)
        {
            if(vector[j].height > vector[j + 1].height)
            {
                window.clear();
                // Move bigger rectangle where the smaller is
                for(int x = 0; x < vector[j].width; x++)
                {
                    for(int y = 0; y < vector[j].height; y++)
                    {
                        image.setPixel(vector[j + 1].xLocation + x, vector[j].yLocation + y, vector[j].colour);
                    }
                }                    

                // Delete bigger rectangle
                for(int x = 0; x < vector[j].width; x++)
                {
                    for(int y = 0; y < vector[j].height; y++)
                    {
                        image.setPixel(vector[j].xLocation + x, vector[j].yLocation + y, sf::Color::White);
                    }
                }

                // Redraw smaller rectangle
                for(int x = 0; x < vector[j + 1].width; x++)
                {
                    for(int y = 0; y < vector[j + 1].height; y++)
                    {
                        image.setPixel(vector[j].xLocation + x, vector[j + 1].yLocation + y, vector[j].colour);
                    }
                }
                // Swap and display
                std::swap(vector[j], vector[j + 1]);
                std::swap(vector[j].xLocation, vector[j + 1].xLocation);

                texture.loadFromImage(image);    
                sprite.setTexture(texture);
                window.draw(sprite);
                window.display();
            }
        }
    }
}