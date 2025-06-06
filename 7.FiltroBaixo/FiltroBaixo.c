#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../stb_image_write.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
    int width, height, channels;

    // Kernel para filtro passa-baixa (média)
    // O filtro passa-baixa suaviza a imagem, removendo ruídos e detalhes
    int kernel[3][3] = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };

    // Carrega a imagem e verifica se imagem existe
    // forço canal de uma imagem em tons de cinza (.., 1);

    unsigned char *img = stbi_load("ImagemEscolhida.png", &width, &height, &channels, 1);
    if (!img) {
        printf("Erro ao carregar imagem\n");
        return 1;
    }

    printf("Imagem carregada: %dx%d (%d canais)\n", width, height, channels);

    // Aloca memória para a nova imagem
    unsigned char *gray_img = malloc(width * height);
    unsigned char *filtro_img = malloc(width * height);

    // Copia os valores da imagem original para gray_img
    for (int i = 0; i < width * height; i++) {
        gray_img[i] = img[i];
    }

    // Aplica o filtro passa-baixa
    // O filtro é aplicado a cada pixel da imagem, exceto nas bordas
    // O valor do pixel é calculado como a soma dos produtos dos valores dos pixels vizinhos pelo valor do kernel
    // O valor do pixel é mantido para o intervalo [0, 255]
    // O valor do pixel é armazenado na nova imagem filtro_img
    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            int soma = 0;

            for (int ky = -1; ky <= 1; ky++) {
                for (int kx = -1; kx <= 1; kx++) {
                    int nx = x + kx;
                    int ny = y + ky;

                    // Acessa o valor do pixel em cinza
                    int pixel = gray_img[ny * width + nx];
                    soma += pixel * kernel[ky + 1][kx + 1];
                }
            }

            // Divide a soma pelo total de elementos do kernel (9)
            soma /= 9;

            // Mantém para 0-255
            if (soma < 0) soma = 0;
            if (soma > 255) soma = 255;

            // Aplica o valor no resultado
            filtro_img[y * width + x] = soma;
        }
    }

    // Salva a imagem com imagem atualizada com filtro
    stbi_write_png("Gato-Baixo.png", width, height, 1, filtro_img, width);

    // Libera memória
    stbi_image_free(img);
    free(gray_img);
    free(filtro_img);

    printf("Imagem convertida e salva como 'Gato-Baixo.png'\n");

    return 0;
}