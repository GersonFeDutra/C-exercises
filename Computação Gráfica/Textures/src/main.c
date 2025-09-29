// texture_demo.c
// Compilar: gcc texture_demo.c -o texture_demo -lGL -lGLU -lglut
// Execute: ./texture_demo
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

static GLuint texId = 0;
static int winW = 800, winH = 600;

GLuint load_texture(const char *filename) {
    int w, h, channels;
    unsigned char *data = stbi_load(filename, &w, &h, &channels, 0);
    if (!data) {
        fprintf(stderr, "Falha ao carregar imagem %s\n", filename);
        return 0;
    }

    GLenum format;
    if (channels == 1) format = GL_RED;
    else if (channels == 3) format = GL_RGB;
    else if (channels == 4) format = GL_RGBA;
    else format = GL_RGB;

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // envia dados + gera mipmaps (compatível com OpenGL antigo)
    gluBuild2DMipmaps(GL_TEXTURE_2D, format, w, h, format, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
    return tex;
}


/* Simple 24-bit BMP loader (no compression). Returns pixel data (RGB) or NULL.
   width/height are output parameters. Caller must free() the returned buffer. */
unsigned char* load_bmp_24(const char* filename, int* width, int* height) {
    FILE* f = fopen(filename, "rb");
    if (!f) {
        perror("fopen");
        return NULL;
    }

    unsigned char header[54];
    if (fread(header, 1, 54, f) != 54) { fclose(f); return NULL; }
    if (header[0] != 'B' || header[1] != 'M') { fclose(f); return NULL; }

    unsigned int dataOffset = *(int*)&header[0x0A];
    unsigned int w = *(int*)&header[0x12];
    unsigned int h = *(int*)&header[0x16];
    unsigned short bpp = *(short*)&header[0x1C];
    unsigned int compression = *(int*)&header[0x1E];

    if (bpp != 24 || compression != 0) {
        fprintf(stderr, "Only uncompressed 24-bit BMP supported. bpp=%u comp=%u\n", bpp, compression);
        fclose(f);
        return NULL;
    }

    // BMP rows are padded to 4-byte boundaries
    int row_padded = (w * 3 + 3) & (~3);
    unsigned char* data = (unsigned char*)malloc(w * h * 3);
    if (!data) { fclose(f); return NULL; }

    unsigned char* row = (unsigned char*)malloc(row_padded);
    if (!row) { free(data); fclose(f); return NULL; }

    fseek(f, dataOffset, SEEK_SET);

    // BMP stores pixels bottom-to-top
    for (unsigned int y = 0; y < h; ++y) {
        if (fread(row, 1, row_padded, f) != (size_t)row_padded) {
            free(row); free(data); fclose(f); return NULL;
        }
        for (unsigned int x = 0; x < w; ++x) {
            unsigned char b = row[x*3 + 0];
            unsigned char g = row[x*3 + 1];
            unsigned char r = row[x*3 + 2];
            // store as RGB
            unsigned int dest_index = ((h - 1 - y) * w + x) * 3; // flip to top-to-bottom
            data[dest_index + 0] = r;
            data[dest_index + 1] = g;
            data[dest_index + 2] = b;
        }
    }

    free(row);
    fclose(f);
    *width = (int)w;
    *height = (int)h;
    return data;
}

void create_texture_from_bmp(const char* path) {
    int w, h;
    unsigned char* pixels = load_bmp_24(path, &w, &h);
    if (!pixels) {
        fprintf(stderr, "Falha ao carregar BMP: %s\n", path);
        return;
    }

    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);

    // configurações básicas de textura
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // envia dados para GPU
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);

    // Gere mipmaps para melhorar qualidade quando escalada
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, w, h, GL_RGB, GL_UNSIGNED_BYTE, pixels);

    free(pixels);
    glBindTexture(GL_TEXTURE_2D, 0);
    printf("Texture carregada: %s (%dx%d), texId=%u\n", path, w, h, texId);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texId);

    // Desenha uma quad cobrindo o centro da tela
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-0.8f, -0.8f);
        glTexCoord2f(1.0f, 0.0f); glVertex2f( 0.8f, -0.8f);
        glTexCoord2f(1.0f, 1.0f); glVertex2f( 0.8f,  0.8f);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-0.8f,  0.8f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

    glutSwapBuffers();
}

void reshape(int w, int h) {
    winW = w; winH = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // usa uma projeção ortográfica simples pra 2D
    if (w <= h) {
        float ar = (float)h / (float)w;
        glOrtho(-1.0, 1.0, -ar, ar, -1.0, 1.0);
    } else {
        float ar = (float)w / (float)h;
        glOrtho(-ar, ar, -1.0, 1.0, -1.0, 1.0);
    }
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    (void)x; (void)y;
    if (key == 27 || key == 'q' || key == 'Q') {
        if (texId) glDeleteTextures(1, &texId);
        exit(0);
    }
}

int main(int argc, char** argv) {
    const char* bmpfile = "texture.bmp";
    if (argc >= 2) bmpfile = argv[1];

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(winW, winH);
    glutCreateWindow("OpenGL Texture + FreeGLUT - demo");

    const char* img_file = "texture.png";
    texId = load_texture(img_file); // ou .jpg

    if (!texId) {
        fprintf(stderr, "Erro: não foi possível carregar a textura %s\n", img_file);
        return 1;
    }

    glEnable(GL_DEPTH_TEST);

    //create_texture_from_bmp(bmpfile);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}
