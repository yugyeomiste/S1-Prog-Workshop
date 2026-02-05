#include <sil/sil.hpp>
#include <iostream>
#include <algorithm>

//niveau 1 j1&2

//exo1

void keep_green_only(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        color.r = 0.f;
        color.b = 0.f;
    }
    image.save("output/keep_green_only.png");
}

//exo2

void channels_swap(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        std::swap(color.r, color.b);
    }
    image.save("output/channels_swap.png");
}

//exo3

void noir_et_blanc(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        float moyenne = (color.r + color.g + color.b) / 3.f;

        color = glm::vec3{moyenne}; 
    }
}

//exo4

void negatif(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        color = glm::vec3{1.f} - color;
    }
}

//exo5 degrade
void degrade(sil::Image& image)
{
    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            float value = x / (float)(image.width() - 1);
            image.pixel(x, y) = glm::vec3{value};
        }
    }
}

//niveau 2 j3

//exo6 miroir
void miror(sil::Image& image)
{
    // test jusqu'a la moité
    for (int x = 0; x < image.width() / 2; x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            int x_oppose = image.width() - 1 - x;
            std::swap(image.pixel(x, y), image.pixel(x_oppose, y));
        }
    }
}

int main()
{
    {
        sil::Image image{"images/logo.png"}; 
        keep_green_only(image); 
        image.save("output/keep_green_only.png"); 
    }
    {
        sil::Image image{"images/logo.png"}; 
        channels_swap(image); 
        image.save("output/channels_swap.png"); 
    }
    {
        sil::Image image{"images/logo.png"}; 
        noir_et_blanc(image); 
        image.save("output/noir_et_blanc.png"); 
    }
    {
        sil::Image image{"images/logo.png"}; 
        negatif(image); 
        image.save("output/negatif.png"); 
    }
    {
        sil::Image image{300/*width*/, 200/*height*/}; //indice
        degrade(image);
        image.save("output/degrade.png");
    }
    {
        sil::Image image{"images/logo.png"}; 
        miror(image); 
        image.save("output/miroir.png"); 
    }
}