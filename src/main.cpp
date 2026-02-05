#include <sil/sil.hpp>
#include <iostream>
#include <algorithm>
#include "random.hpp"

//niveau 1 j1&2

//exo1

void keep_green_only(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        color.r = 0.f;
        color.b = 0.f;
    }
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
        // moyenne des 3 couleurs pour le gris
        float moyenne = (color.r + color.g + color.b) / 3.f;

        color = glm::vec3{moyenne}; 
    }
}

//exo4

void negatif(sil::Image& image)
{
    // inversement des couleurs (1 - couleur)
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

//ex07 rotation a 90 

void rotation(sil::Image& image)
{
    // creation d'un nouvelle image 
    sil::Image nouvelle_image{image.height(), image.width()};

    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            // formule pour tourner a 90 
            nouvelle_image.pixel(image.height() - 1 - y, x) = image.pixel(x, y);
        }
    }
    // remplace l'image de base avec nouvelle
    image = nouvelle_image;
}
 //exo 8 luminosité

void luminosite(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        //  Puissance 0.5 (racine carree) pour eclaircir
        color.r = std::pow(color.r, 0.5f);
        color.g = std::pow(color.g, 0.5f);
        color.b = std::pow(color.b, 0.5f);
    }
}

// niveau 3 

//ex0 9 glitch 

void glitch(sil::Image& image)
{
    for (int i = 0; i < 100; i++)
    {
        // random taille du rectangle 
        int largeur_rect = random_int(10, 40);
        int hauteur_rect = random_int(2, 10);

        // coordonnees de depart
        int x1 = random_int(0, image.width() - 1 - largeur_rect);
        int y1 = random_int(0, image.height() - 1 - hauteur_rect);

        // coordonnees d'arrivee
        int x2 = random_int(0, image.width() - 1 - largeur_rect);
        int y2 = random_int(0, image.height() - 1 - hauteur_rect);

        for (int x = 0; x < largeur_rect; x++)
        {
            for (int y = 0; y < hauteur_rect; y++)
            {
                // Echange du pixel 1 et pixel 2
                std::swap(image.pixel(x1 + x, y1 + y), image.pixel(x2 + x, y2 + y));
            }
        }
    }
}

int main()
{

    set_random_seed(0);

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
    {
        sil::Image image{"images/logo.png"}; 
        rotation(image); 
        image.save("output/rotation.png"); 
    }
    {
        sil::Image image{"images/logo.png"}; 
        glitch(image); 
        image.save("output/glitch.png"); 
    }
    {
        sil::Image image{"images/photo.jpg"}; 
        luminosite(image);
        image.save("output/luminosite.png");
    }
}