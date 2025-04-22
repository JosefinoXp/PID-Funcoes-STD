#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../stb_image_write.h"

#include <stdio.h>
#include <stdlib.h>

// define o limite para a conversão em preto e branco
// Se o valor for menor que 128, a cor será preta, se for maior ou igual a 128, a cor será branca
#define LIMIAR 128

int main() {
    int width, height, channels;

    // Carrega a imagem e verifica se imagem existe
    unsigned char *img = stbi_load("Gato-Cinza.png", &width, &height, &channels, 0);
    if (!img) {
        printf("Erro ao carregar imagem\n");
        return 1;
    }

    printf("Imagem carregada: %dx%d (%d canais)\n", width, height, channels);

    // Aloca memória para a nova imagem
    unsigned char *gray_img = malloc(width * height * channels);

    // Converte para tons de branco e preto
    for (int i = 0; i < width * height; i++) {
        int r = img[i * channels + 0];
        int g = img[i * channels + 1];
        int b = img[i * channels + 2];
        unsigned char gray = (r + g + b) / 3;


        if (gray < LIMIAR) {
            gray_img[i * channels + 0] = 0;
            gray_img[i * channels + 1] = 0;
            gray_img[i * channels + 2] = 0;
        }

        else {
            gray_img[i * channels + 0] = 255;
            gray_img[i * channels + 1] = 255;
            gray_img[i * channels + 2] = 255;
        }
        

        // Se houver canal alpha, copia ele
        if (channels == 4) {
            gray_img[i * channels + 3] = img[i * channels + 3];
        }
    }

    // Salva a imagem como PNG
    stbi_write_png("Gato-PretoBranco.png", width, height, channels, gray_img, width * channels);

    // Libera memória
    stbi_image_free(img);
    free(gray_img);

    printf("Imagem convertida e salva como 'Gato-PretoBranco.png'\n");

    return 0;
}
