#include <sil/sil.hpp>
#include <iostream>
#include <algorithm>

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
}