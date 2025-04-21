#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../stb_image_write.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
    int width, height, channels;

    // Carrega a imagem e verifica se imagem existe
    unsigned char *img = stbi_load("ImagemEscolhida.png", &width, &height, &channels, 0);
    if (!img) {
        printf("Erro ao carregar imagem\n");
        return 1;
    }

    printf("Imagem carregada: %dx%d (%d canais)\n", width, height, channels);

    // Aloca memória para a nova imagem
    unsigned char *gray_img = malloc(width * height * channels);

    // Converte para tons de cinza
    // A média dos valores RGB é usada para calcular o valor cinza
    for (int i = 0; i < width * height; i++) {
        int r = img[i * channels + 0];
        int g = img[i * channels + 1];
        int b = img[i * channels + 2];
        unsigned char gray = (r + g + b) / 3;

        // Atribui o valor cinza a todos os canais RGB
        gray_img[i * channels + 0] = gray;
        gray_img[i * channels + 1] = gray;
        gray_img[i * channels + 2] = gray;

        // Se houver canal alpha, copia ele
        if (channels == 4) {
            gray_img[i * channels + 3] = img[i * channels + 3];
        }
    }

    // Salva a imagem como PNG
    stbi_write_png("Gato-Cinza.png", width, height, channels, gray_img, width * channels);

    // Libera memória
    stbi_image_free(img);
    free(gray_img);

    printf("Imagem convertida e salva como 'Gato-Cinza.png'\n");

    return 0;
}
