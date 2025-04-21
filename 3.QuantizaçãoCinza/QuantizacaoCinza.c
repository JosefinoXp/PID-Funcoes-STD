#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../stb_image_write.h"

#include <stdio.h>
#include <stdlib.h>

// Definindo o limite para a conversão em preto e branco
// Se o valor for menor que 128, a cor será preta, se for maior ou igual a 128, a cor será branca
#define LIMIAR 128

// Definindo o número de camadas para a quantização
// O número de camadas deve ser uma potência de 2 (1, 2, 4, 8, 16, ...)
#define NUM_CAMADA 4

int main() {
    int width, height, channels;

    // Carrega a imagem e verifica se imagem existe
    unsigned char *img = stbi_load("input.png", &width, &height, &channels, 0);
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

        // quantiza o valor cinza
        // O valor cinza é dividido pelo número de camadas e multiplicado pelo número de camadas
        // Isso garante que o valor cinza seja um múltiplo do número de camadas
        // O valor cinza é dividido por 256/número de camadas e multiplicado por 256/número de camadas
        // Isso garante que o valor cinza seja um múltiplo do número de camadas
        unsigned int quantizado = (gray / (256 / NUM_CAMADA)) * (256 / NUM_CAMADA);

        gray_img[i * channels + 0] = quantizado;
        gray_img[i * channels + 1] = quantizado;
        gray_img[i * channels + 2] = quantizado;

        // Se houver canal alpha, copia ele
        if (channels == 4) {
            gray_img[i * channels + 3] = img[i * channels + 3];
        }
    }

    // Salva a imagem como PNG
    stbi_write_png("Quantizacao_cinza.png", width, height, channels, gray_img, width * channels);

    // Libera memória
    stbi_image_free(img);
    free(gray_img);

    printf("Imagem convertida e salva como 'Quantizacao_cinza.png'\n");

    return 0;
}
