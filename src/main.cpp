#include <sil/sil.hpp>
#include <iostream>
#include <algorithm>
#include "random.hpp"
#include <complex>

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

//exo6 cercle
void cercle(sil::Image& image)
{
    int centre_x = image.width() / 2;
    int centre_y = image.height() / 2;
    int rayon = 100;
    int epaisseur = 5;

    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            // j'utilise racine carrée pour avoir la distance réelle
            float distance = std::sqrt(std::pow(x - centre_x, 2) + std::pow(y - centre_y, 2));

            if (std::abs(distance - rayon) < epaisseur)
            {
                image.pixel(x, y) = glm::vec3{1.f};
            }
        }
    }
}



//niveau 2 

//exo1 miroir
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

//exo2 rotation a 90 

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
 //exo3 luminosité

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

//exo4  disque 

void disque(sil::Image& image)
{
    // on se met au milieu de l'image
    int centre_x = image.width() / 2;
    int centre_y = image.height() / 2;
    int rayon = 100;

    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            // equation du cercle : (x-a)² + (y-b)² <= R²
            // calcule distance au carré par rapport au centre
            int distance_sq = std::pow(x - centre_x, 2) + std::pow(y - centre_y, 2);
            
            if (distance_sq <= std::pow(rayon, 2))
            {
                //blanc
                image.pixel(x, y) = glm::vec3{1.f};
            }
        }
    }
}

//exo 5 mosaique

void mosaique(sil::Image& image)
{
    sil::Image nouvelle_image{image.width(), image.height()};
    
    int repetitions = 5; 

    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            int x_source = (x * repetitions) % image.width();
            int y_source = (y * repetitions) % image.height();
            
            nouvelle_image.pixel(x, y) = image.pixel(x_source, y_source);
        }
    }
    image = nouvelle_image;
}




// niveau 3 

//exo1 glitch 

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

//exo 2 rosace 

void rosace(sil::Image& image)
{
    for (glm::vec3& color : image.pixels()) 
    {
        color = glm::vec3{0.f};
    }

    int rayon = 100;
    int epaisseur = 3; 
    int centre_x = image.width() / 2;
    int centre_y = image.height() / 2;

    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {

            // Calcul de la distance du pixel au centre
            float distance = std::sqrt(std::pow(x - centre_x, 2) + std::pow(y - centre_y, 2));
            
            // Si  distance = rayon --> blanc
            if (std::abs(distance - rayon) < epaisseur)
            {
                image.pixel(x, y) = glm::vec3{1.f};
            }

            // 6 cercles
            for (int i = 0; i < 6; i++)
            {
                // position du cercle au centre
                float angle = i * (M_PI / 3.0f);  
                int cx = centre_x + rayon * std::cos(angle);
                int cy = centre_y + rayon * std::sin(angle);

                // si le pixel appartient au contour de ce cercle
                float dist_cercle = std::sqrt(std::pow(x - cx, 2) + std::pow(y - cy, 2));
                
                if (std::abs(dist_cercle - rayon) < epaisseur)
                {
                    image.pixel(x, y) = glm::vec3{1.f}; 
                }
            }
        }
    }
}

//exo3 mandelbrot 

void mandelbrot(sil::Image& image)
{
    // on parcourt toute l'image
    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            // il faut changer l'echelle de x et y
            // -2 a 2 pour bien voir la fractale
            float new_x = ((float)x / image.width() - 0.5f) * 4.f;
            float new_y = ((float)y / image.height() - 0.5f) * 4.f;

            // on definit les nombres complexes c et z
            std::complex<float> c{new_x, new_y};
            std::complex<float> z{0.f, 0.f}; 

            int compteur = 0;

            // calcul z = z * z + c et on s'arrete si z > 2 ou si 50 tours
            while (std::abs(z) < 2.f && compteur < 50)
            {
                z = z * z + c;
                compteur++;
            }

            float couleur = (float)compteur / 50.f;
            image.pixel(x, y) = glm::vec3{couleur};
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
    {
        sil::Image image{500, 500};
        disque(image);
        image.save("output/disque.png");
    }
    {
        sil::Image image{500, 500};
        cercle(image);
        image.save("output/cercle.png");
    }
    {
        sil::Image image{500, 500};
        rosace(image);
        image.save("output/rosace.png");
    }
    {
        sil::Image image{"images/logo.png"}; 
        mosaique(image);
        image.save("output/mosaique.png");
    }
    {
        sil::Image image{500, 500};
        mandelbrot(image);
        image.save("output/mandelbrot.png");
    }

}