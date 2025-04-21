#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../stb_image_write.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
    int width, height, channels;
    
    // Inicializa o histograma todo com zero
    unsigned int histograma[257] = {0};

    FILE* arq;
    char nome_arq[20] = "histograma.txt";

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
    for (int i = 0; i < width * height; i++) {
        int r = img[i * channels + 0];
        int g = img[i * channels + 1];
        int b = img[i * channels + 2];
        unsigned char gray = (r + g + b) / 3;

        // cada posição do histograma representa um tom de cinza, e quanto ele foi representado na imagem
        // O valor máximo do tom de cinza é 255, então o histograma vai de 0 a 256
        histograma[gray]++;
    }

    arq = fopen(nome_arq, "a+");

    // Verifica se o arquivo foi aberto corretamente
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nome_arq);
        free(gray_img);
        stbi_image_free(img);
        return 1;
    }

    // Escreve o histograma no arquivo e gera a estatística no arquivo "histograma.txt"
    for (unsigned int i = 0; i <= 256; i++) {
        fprintf(arq, "%u* Tom Cinza / Quantidade: %u\n", i, histograma[i]);
    }

    // Libera memória
    stbi_image_free(img);
    free(gray_img);

    fclose(arq);

    return 0;
}
