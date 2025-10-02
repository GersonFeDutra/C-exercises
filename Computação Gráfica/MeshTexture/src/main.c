#pragma region Includes
    #include <GL/freeglut.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>
    #include <stdbool.h>

    #define STB_IMAGE_IMPLEMENTATION
    #include "stb_image.h"
#pragma endregion

#define MAX_MAT_NAME 256

#pragma region Types
    typedef struct {
        char name[MAX_MAT_NAME];
        GLuint texture_id; // 0 se sem textura
    } Material;

    typedef struct {
        float r, g, b, a;
    } Color;
    #define color_as_gl_float_ptr(c) (GLfloat*)(&c.r)

    typedef struct {
        float x, y, z;
    } Vec3;
    #define vec3_as_gl_float_ptr(v) (GLfloat*)(&v.x)

    typedef struct {
        float u, v;
    } Vec2;

    typedef struct {
        int vertex[3];
        int vertex_texture[3];
        int vertex_normal[3];
        int material_id; // índice do material para essa face (ou -1)
    } Face;
#pragma endregion

#pragma region Globals

    #pragma region Buffers
        Vec3* vertices = NULL;
        Vec2* texture_coords = NULL;
        Vec3* normals = NULL;
        Material* materials = NULL;
        Face* faces = NULL;
    #pragma endregion

    size_t vertex_count = 0, texture_coords_count = 0, normals_count = 0, materials_count = 0, faces_count = 0;
    // capacidades internas (mantém estado entre chamadas)
    static size_t vertex_cap = 0, tex_coords_cap = 0, normal_cap = 0, face_cap = 0, material_cap = 0;

    #pragma region Animation
        float angle = 0.0f;

        // bounding box do modelo
        float bbmin[3] = { 1e9f, 1e9f, 1e9f };
        float bbmax[3] = { -1e9f, -1e9f, -1e9f };
        float center[3] = {0};
    #pragma endregion
#pragma endregion

#pragma region Utils
/* utility: verifica se path é absoluto (Unix ou Windows) */
static int is_absolute_path(const char *p) {
    if (!p || !*p) return 0;
#if defined(_WIN32) || defined(_WIN64)
    // Windows: "C:\..." ou "\\server\..."
    if (isalpha((unsigned char)p[0]) && p[1] == ':') return 1;
    if (p[0] == '\\' && p[1] == '\\') return 1;
    return 0;
#else
    // Unix: começa com '/'
    return p[0] == '/';
#endif
}

/* utility: junta base_dir + sep + filename em out (outsize bytes) */
static void join_path(const char *base_dir, const char *sep, const char *name, char *out, size_t outsize) {
    if (!base_dir || !*base_dir) {
        // sem base, usar name direto
        snprintf(out, outsize, "%s", name);
        return;
    }
    // se name já for absoluto, apenas copie
    if (is_absolute_path(name)) {
        snprintf(out, outsize, "%s", name);
        return;
    }

    // concatenar com separador, cuidando se base_dir já termina com separador
    size_t bl = strlen(base_dir);
    if (bl > 0 && (base_dir[bl-1] == '/' || base_dir[bl-1] == '\\')) {
        snprintf(out, outsize, "%s%s", base_dir, name);
    } else {
        snprintf(out, outsize, "%s%s%s", base_dir, sep, name);
    }
}

/* utility: trim leading/trailing whitespace and surrounding quotes */
static void trim_and_strip_quotes(char *s) {
    // trim left
    char *p = s;
    while (*p && isspace((unsigned char)*p)) p++;
    if (p != s) memmove(s, p, strlen(p)+1);

    // trim right
    size_t len = strlen(s);
    while (len > 0 && isspace((unsigned char)s[len-1])) s[--len] = '\0';

    // remove surrounding quotes if present
    if (len >= 2 && ((s[0] == '"' && s[len-1] == '"') || (s[0] == '\'' && s[len-1] == '\''))) {
        memmove(s, s+1, len-2);
        s[len-2] = '\0';
    }
}
#pragma endregion

/*--- Funções estáticas auxiliares ---*/
#pragma region Helper Methods
/* Todas fecham o arquivo e chamam exit(1) em caso de falha de realloc. */
static void ensure_vertex_cap(size_t add, FILE *f) {
    if (vertex_count + add > vertex_cap) {
        size_t newcap = (vertex_cap == 0) ? 1024 : vertex_cap;
        while (vertex_count + add > newcap) newcap *= 2;
        Vec3* tmp = (Vec3*)realloc(vertices, newcap * sizeof(Vec3));
        if (!tmp) {
            fprintf(stderr, "realloc failed for vertices\n");
            if (f) fclose(f);
            exit(1);
        }
        vertices = tmp;
        vertex_cap = newcap;
    }
}

static void ensure_tex_cap(size_t add, FILE *f) {
    if (texture_coords_count + add > tex_coords_cap) {
        size_t newcap = (tex_coords_cap == 0) ? 1024 : tex_coords_cap;
        while (texture_coords_count + add > newcap) newcap *= 2;
        Vec2* tmp = (Vec2*)realloc(texture_coords, newcap * sizeof(Vec2));
        if (!tmp) {
            fprintf(stderr, "realloc failed for texture_coords\n");
            if (f) fclose(f);
            exit(1);
        }
        texture_coords = tmp;
        tex_coords_cap = newcap;
    }
}

/**
 * @brief Ensure that the normal buffer has enough capacity to store 'add' more normals.
 * If the buffer needs to be resized, it is doubled in size until it can hold
 * at least 'normals_count + add' normals.
 * If the reallocation fails, an error message is printed and the file is closed (if given).
 * The program then exits with code 1.
 * @param add The number of normals that need to be stored in the buffer.
 * @param f The file to be closed in case of reallocation failure. May be NULL.
 */
static void ensure_normal_cap(size_t add, FILE *file) {
    if (normals_count + add > normal_cap) {
        size_t newcap = (normal_cap == 0) ? 1024 : normal_cap;
        while (normals_count + add > newcap) newcap *= 2;
        Vec3* tmp = (Vec3*)realloc(normals, newcap * sizeof(Vec3));
        if (!tmp) {
            fprintf(stderr,"realloc failed for normals\n");
            if (file)
                fclose(file);
            exit(1);
        }
        normals = tmp;
        normal_cap = newcap;
    }
}


static void ensure_face_cap(size_t add, FILE *f) {
    if (faces_count + add > face_cap) {
        size_t newcap = (face_cap == 0) ? 1024 : face_cap;
        while (faces_count + add > newcap) newcap *= 2;
        Face* tmp = (Face*)realloc(faces, newcap * sizeof(Face));
        if (!tmp) {
            fprintf(stderr, "realloc failed for faces\n");
            if (f) fclose(f);
            exit(1);
        }
        faces = tmp;
        face_cap = newcap;
    }
}

/* util: garantir capacidade para materiais */
static void ensure_material_cap(size_t add) {
    if (materials_count + add > material_cap) {
        size_t newcap = (material_cap == 0) ? 8 : material_cap;
        while (materials_count + add > newcap) newcap *= 2;
        Material* tmp = (Material*)realloc(materials, newcap * sizeof(Material));
        if (!tmp) {
            fprintf(stderr, "realloc failed for materials\n");
            exit(1);
        }
        materials = tmp;
        material_cap = newcap;
    }
}

/* Procura material por nome, retorna -1 se não achar */
static int material_find(const char* name) {
    if (!name) return -1;
    for (size_t i = 0; i < materials_count; ++i) {
        if (strcmp(materials[i].name, name) == 0) return (int)i;
    }
    return -1;
}

/* adiciona material (sem textura ainda). retorna índice */
static int material_add(const char* name) {
    ensure_material_cap(1);
    materials[materials_count].texture_id = 0;
    materials[materials_count].name[0] = '\0';
    if (name) strncpy(materials[materials_count].name, name, MAX_MAT_NAME-1);
    materials[materials_count].name[MAX_MAT_NAME-1] = '\0';
    return (int)(materials_count++);
}

/**
 * @brief Calcula a normal de uma face (unitária).
 * 
 * @param a Primeira aresta do triângulo.
 * @param b Segunda aresta do triângulo.
 * @param c Terceira aresta do triângulo.
 * @param out Normal calculada (unitária).
 *
 * A normal é calculada como o produto vetorial das arestas do triângulo.
 * Se a normal for zero (ou seja muito pequena), a saída será (0,0,0).
 */
static void compute_face_normal(const Vec3 *a, const Vec3 *b, const Vec3 *c, Vec3 *out) {
    float ux = b->x - a->x, uy = b->y - a->y, uz = b->z - a->z;
    float vx = c->x - a->x, vy = c->y - a->y, vz = c->z - a->z;
    out->x = uy * vz - uz * vy;
    out->y = uz * vx - ux * vz;
    out->z = ux * vy - uy * vx;
    float len = sqrtf(out->x*out->x + out->y*out->y + out->z*out->z);
    if (len > 1e-9f) { out->x/=len; out->y/=len; out->z/=len; }
    else { out->x = out->y = out->z = 0.0f; }
}
#pragma endregion

#pragma region Loaders
/**
 * @brief Carrega uma textura com o stb_image e retorna o GLuint da textura carregada.
 * 
 * @param filename Nome do arquivo da textura.
 * 
 * Carrega uma textura com o stb_image e cria um GLuint para ela.
 * Se houver algum erro, imprime uma mensagem de erro e fecha o programa.
 * 
 * @return GLuint id da textura carregada.
GLuint load_texture(const char *filename) {
    int width, height, channels;
    unsigned char *data = stbi_load(filename, &width, &height, &channels, 4);
    if (!data) {
        fprintf(stderr, "Erro carregando textura: %s\n", filename);
        exit(1);
    }

    GLuint texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
    return texture_id;
}
 */

/* Carrega o MTL e resolve o caminho da textura relativo ao diretório do próprio MTL */
void load_mtl(const char *mtl_fullpath) {
    FILE *f = fopen(mtl_fullpath, "r");
    if (!f) {
        fprintf(stderr, "Erro abrindo MTL: %s\n", mtl_fullpath);
        return;
    }

    /* extrai diretório do mtl_fullpath (para resolver paths relativos) */
    #pragma region Base Directory
        char base_dir[1024] = {0};
        const char *p1 = strrchr(mtl_fullpath, '/');
        const char *p2 = strrchr(mtl_fullpath, '\\');
        const char *last_slash = p1 > p2 ? p1 : p2;
        if (last_slash) {
            size_t len = (size_t)(last_slash - mtl_fullpath);

            if (len >= sizeof(base_dir))
                len = sizeof(base_dir) - 1;

            memcpy(base_dir, mtl_fullpath, len);
            base_dir[len] = '\0';
        } else {
            base_dir[0] = '\0';
        }
    #pragma endregion

    const char sep[2] = { (strchr(mtl_fullpath, '\\') ? '\\' : '/'), '\0' };
    char line[1024];
    int current_material = -1;
    char token[512];

    while (fgets(line, sizeof(line), f)) {
        // new material
        if (sscanf(line, "newmtl %511s", token) == 1) {
            int idx = material_find(token);
            if (idx < 0)
                idx = material_add(token);
            current_material = idx;

            // assegura texture_id=0 por padrão
            materials[current_material].texture_id = 0;
            continue;
        }

        // procurar por "map_Kd" (padrão para textura difusa)
        if (strstr(line, "map_Kd") != NULL) {
            // 1. obter o resto da linha após "map_Kd"
            #pragma region Texture Name
                char tex_name_raw[512] = {0};
                // pega tudo após "map_Kd"
                const char *after = strstr(line, "map_Kd") + strlen("map_Kd");

                while (*after && isspace((unsigned char)*after))
                    ++after;

                // copia a parte restante até o final da linha
                strncpy(tex_name_raw, after, sizeof(tex_name_raw) - 1);
                trim_and_strip_quotes(tex_name_raw);
            #pragma endregion

            // 2. Resolver caminho: construir possíveis full paths para tentar:
            #pragma region Candidate Paths
                char candidate[1024];

                // 1) se tex_name_raw já for absoluto, use direto
                if (is_absolute_path(tex_name_raw)) {
                    snprintf(candidate, sizeof(candidate), "%s", tex_name_raw);
                } else {
                    // 2) caminho relativo ao diretório do MTL
                    join_path(base_dir, sep, tex_name_raw, candidate, sizeof(candidate));
                }
            #pragma endregion

            // 2.1 Como fallback, tente apenas o nome no cwd (tex_name_raw)
            // Tentaremos abrir candidate, se falhar vamos tentar tex_name_raw
            #pragma region Fallback
                // DEBUG: imprimir o que vamos tentar
                printf("[MTL] tentando carregar textura: '%s' (resolved: '%s')\n", tex_name_raw, candidate);

                // testar existência com fopen antes de stbi
                FILE *tf = fopen(candidate, "rb");
                if (!tf) {
                    // tentar fallback: nome simples (sem base_dir)
                    tf = fopen(tex_name_raw, "rb");
                    if (!tf) {
                        fprintf(stderr, "Falha ao localizar textura. Tentadas: '%s' e '%s'\n", candidate, tex_name_raw);
                        // pode continuar procurando outras linhas dentro do .mtl
                        continue;
                    } else
                        fclose(tf);
                } else {
                    fclose(tf);
                }
            #pragma endregion

            // 3. Carregar imagem com stb_image
            #pragma region Load Image
                int width, height, channels;
                unsigned char *data = stbi_load(candidate, &width, &height, &channels, 4);
                if (!data) {
                    fprintf(stderr, "Erro carregando textura com stb_image: %s\n", candidate);
                    fprintf(stderr, "stb_image failure reason: %s\n", stbi_failure_reason());
                    continue;
                }
            #pragma endregion

            // 4. Criar textura OpenGL (exemplo mínimo)
            #pragma region Create Texture
                GLuint texture_id;
                glGenTextures(1, &texture_id);
                glBindTexture(GL_TEXTURE_2D, texture_id);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                stbi_image_free(data);

                printf("[MTL] textura carregada com sucesso: %s -> texture_id=%u (width=%d height=%d)\n",
                        candidate, (unsigned)texture_id, width, height);
            #pragma endregion

            if (current_material < 0) {
                // sem newmtl declarado antes: crie material genérico
                current_material = material_add("generic");
            }
            // Associa a textura ao material atual
            materials[current_material].texture_id = texture_id;
            continue;
        }
        // ignorar outras linhas
    }

    fclose(f);
}

/* --- Carregar .obj usando realloc growth strategy e as funções acima --- */
int load_obj(const char *filename) {
    /* Se já existirem dados de uma carga anterior, liberamos para recarregar */
    if (vertices) { free(vertices); vertices = NULL; vertex_count = 0; vertex_cap = 0; }
    if (texture_coords) { free(texture_coords); texture_coords = NULL; texture_coords_count = 0; tex_coords_cap = 0; }
    if (faces) { free(faces); faces = NULL; faces_count = 0; face_cap = 0; }

    // Calcule o diretório base do arquivo .obj (por ex. "Tree" para "Tree/Tree.obj")
    #pragma region Base Directory
        char base_dir[1024] = {0};
        const char *last_slash = NULL;
        // procurar por '/' ou '\' (portável)
        const char *p1 = strrchr(filename, '/');
        const char *p2 = strrchr(filename, '\\');
        last_slash = p1 > p2 ? p1 : p2;
        if (last_slash) {
            size_t len = (size_t)(last_slash - filename);
            if (len >= sizeof(base_dir)) len = sizeof(base_dir) - 1;
            memcpy(base_dir, filename, len);
            base_dir[len] = '\0';
        } else {
            // sem diretório: base_dir fica vazio -> indica diretório atual
            base_dir[0] = '\0';
        }

        // determinar separador a usar (prefere o separador encontrado em filename)
        const char sep[2] = { (strchr(filename, '\\') ? '\\' : '/'), '\0' };
    #pragma endregion

    FILE *f = fopen(filename, "r");
    if (!f) {
        fprintf(stderr, "Erro abrindo OBJ %s\n", filename);
        exit(1);
    }

    char line[1024];
    size_t ignored_count = 0;
    int current_material = -1; // índice do material atual nas faces; default -1

    bool is_unsupported_format = false;

    while (fgets(line, sizeof(line), f)) {
        if (line[0] == 'v' && line[1] == ' ') { // vertices
            Vec3 v;
            if (sscanf(line, "v %f %f %f", &v.x, &v.y, &v.z) == 3) {
                ensure_vertex_cap(1, f);
                vertices[vertex_count++] = v;
            }
        } else if (line[0] == 'v' && line[1] == 't') { // texture_coords
            Vec2 t;
            /* vt u v  (v pode faltar em alguns OBJs) */
            if (sscanf(line, "vt %f %f", &t.u, &t.v) >= 1) {
                if (sscanf(line, "vt %f %f", &t.u, &t.v) != 2) t.v = 0.0f;
                ensure_tex_cap(1, f);
                texture_coords[texture_coords_count++] = t;
            }
        } else if (strncmp(line, "mtllib", 6) == 0) { // mtllib
            char mtl_file[512] = {0};
            if (sscanf(line, "mtllib %511s", mtl_file) == 1) {
                char fullmtl[1024];

                // se o mtl_file já for um caminho absoluto, join_path deixa como está
                join_path(base_dir, sep, mtl_file, fullmtl, sizeof(fullmtl));
                load_mtl(fullmtl); // isso pode adicionar materiais
            }
        } else if (strncmp(line, "usemtl", 6) == 0) {
            char material_name[512] = {0};
            if (sscanf(line, "usemtl %511s", material_name) == 1) {
                int idx = material_find(material_name);
                if (idx < 0) {
                    // material referenciado mas não definido no .mtl -> criar placeholder
                    idx = material_add(material_name);
                }
                current_material = idx;
                // debug
                printf("[OBJ] usemtl -> %s (idx=%d)\n", material_name, current_material);
            }
        } else if (line[0] == 'f' && (line[1] == ' ' || line[1] == '\t')) { // faces
            // parsing robusto (suporta v/vt/vn, v//vn, v/vt, v v v)
            Face face;
            face.material_id = current_material; // atribui o material atual
            int vertex[3], vertex_texture[3], vertex_normal[3];

            // Tenta v/vt/vn
            int matches = sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d",
                                &vertex[0], &vertex_texture[0], &vertex_normal[0],
                                &vertex[1], &vertex_texture[1], &vertex_normal[1],
                                &vertex[2], &vertex_texture[2], &vertex_normal[2]);
            if (matches == 9) {
                for (int j = 0; j < 3; ++j) {
                    face.vertex[j] = vertex[j];
                    face.vertex_texture[j] = vertex_texture[j];
                    face.vertex_normal[j] = vertex_normal[j];
                }
                ensure_face_cap(1, f);
                faces[faces_count++] = face;
            } else {
                // Tenta v//vn
                matches = sscanf(line, "f %d//%d %d//%d %d//%d",
                                &vertex[0], &vertex_normal[0],
                                &vertex[1], &vertex_normal[1],
                                &vertex[2], &vertex_normal[2]);
                if (matches == 6) {
                    for (int j = 0; j < 3; ++j) {
                        face.vertex[j]  = vertex[j];
                        face.vertex_texture[j] = vertex_texture[j];
                        face.vertex_normal[j] = vertex_normal[j];
                    }
                    ensure_face_cap(1, f);
                    faces[faces_count++] = face;
                } else {
                    // Tenta v/vt
                    matches = sscanf(line, "f %d/%d %d/%d %d/%d",
                                    &vertex[0], &vertex_texture[0],
                                    &vertex[1], &vertex_texture[1],
                                    &vertex[2], &vertex_texture[2]);
                    if (matches == 6) {
                        for (int j = 0; j < 3; j++) {
                            face.vertex[j]  = vertex[j];
                            face.vertex_texture[j] = vertex_texture[j];
                            face.vertex_normal[j] = 0;
                        }
                        ensure_face_cap(1, f);
                        faces[faces_count++] = face;
                    } else {
                        // Tenta v v v
                        matches = sscanf(line, "f %d %d %d", &vertex[0], &vertex[1], &vertex[2]);
                        if (matches == 3) {
                            for (int j = 0; j < 3; ++j) {
                                face.vertex[j]  = vertex[j];
                                face.vertex_normal[j] = face.vertex_texture[j] = 0;
                            }
                            ensure_face_cap(1, f);
                            faces[faces_count++] = face;
                        }
                        else {
                            // formato não suportado (ngon etc.) -> ignorar
                            is_unsupported_format = true;
                        }
                    }
                }
            }
        }
        else if (line[0]=='v' && line[1]=='n') {
            Vec3 n;
            if (sscanf(line, "vn %f %f %f", &n.x, &n.y, &n.z) == 3) {
                ensure_normal_cap(1, f);
                normals[normals_count++] = n;
            }
        }
        else {
            /* outras linhas (o, s, etc.) ignoradas aqui */
            if (!isblank(*line) && line[0] != EOF)
                ++ignored_count;
        }
    }
    if (is_unsupported_format) {
        fprintf(stderr, "Formato de arquivo desconhecido na leitura das faces\n");
        return EXIT_FAILURE;
    }
    if (ignored_count)
        printf("%zu linhas ignoradas\n", ignored_count);

    fclose(f);

    #pragma region Patch Missing Normals
    for (size_t i = 0; i < faces_count; ++i) { // percorre faces
        bool any_invalid = false;
        for (int j = 0; j < 3; ++j) {
            int vn_idx = faces[i].vertex_normal[j]; // seu código usa 1-based
            if (vn_idx <= 0 || vn_idx > (int)normals_count) {
                any_invalid = true;
                break;
            }
        }

        if (!any_invalid) continue; // face já tem todas as normals válidas

        // calcula normal da face (a, b, c são posições)
        Vec3 a = vertices[ faces[i].vertex[0] - 1 ];
        Vec3 b = vertices[ faces[i].vertex[1] - 1 ];
        Vec3 c = vertices[ faces[i].vertex[2] - 1 ];
        Vec3 fn;
        compute_face_normal(&a, &b, &c, &fn);

        // anexa normal à lista de normals e obtenha índice 1-based
        ensure_normal_cap(1, NULL);
        normals[normals_count] = fn;
        normals_count++;
        int new_normal_index = (int)normals_count; // 1-based index para OBJ-style

        // preencha apenas as posições de vertex_normal inválidas com esse índice
        for (int j = 0; j < 3; ++j) {
            int vn_idx = faces[i].vertex_normal[j];
            if (vn_idx <= 0 || vn_idx > (int)normals_count-1) {
                faces[i].vertex_normal[j] = new_normal_index;
            }
        }
    }
    #pragma endregion

    /* Opcional: reduzir (shrink) as alocações para o tamanho real */
    #pragma region Shrink allocations
        if (vertex_cap > vertex_count) {
            Vec3* tmp = (Vec3*)realloc(vertices, (vertex_count ? vertex_count : 1) * sizeof(Vec3));
            if (tmp) {
                vertices = tmp;
                vertex_cap = vertex_count;
            }
        }
        if (tex_coords_cap > texture_coords_count) {
            Vec2* tmp = (Vec2*)realloc(texture_coords, (texture_coords_count ? texture_coords_count : 1) * sizeof(Vec2));
            if (tmp) {
                texture_coords = tmp;
                tex_coords_cap = texture_coords_count;
            }
        }
        if (normal_cap > normals_count) {
            Vec3* tmp = (Vec3*)realloc(normals, (normals_count ? normals_count : 1) * sizeof(Vec3));
            if (tmp) {
                normals = tmp;
                normal_cap = normals_count;
            }
        }
        if (face_cap > faces_count) {
            Face* tmp = (Face*)realloc(faces, (faces_count ? faces_count : 1) * sizeof(Face));
            if (tmp) {
                faces = tmp;
                face_cap = faces_count;
            }
        }
    #pragma endregion

    return EXIT_SUCCESS;
}
#pragma endregion

#pragma region GLUT callbacks
void display() {
    glClearColor(0.2f, 0.3f, 0.35f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // camera/projection: está configurado no `reshape`
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    gluLookAt(0, 2, 6,   0, 0, 0,   0, 1, 0);

    // habilitar transparência
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);

    //glDisable(GL_ALPHA_TEST);
    // Remover artefatos - descartar pixels totalmente transparentes (para folhas)
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.01f); // descarta pixels com alpha baixo

#pragma region Lighting
    //glDisable(GL_LIGHTING); // Mas eu quero... depois
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);

    Color lightColor = (Color){1.0f, 0.5f, 0.5f, 1.0f}; // White light
    Vec3 light_pos = { 0.0f, 0.5f, 0.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, vec3_as_gl_float_ptr(light_pos));
    glLightfv(GL_LIGHT0, GL_AMBIENT, color_as_gl_float_ptr(lightColor));   // Ambient light
    glLightfv(GL_LIGHT0, GL_DIFFUSE, color_as_gl_float_ptr(lightColor));   // Diffuse light
    glLightfv(GL_LIGHT0, GL_SPECULAR, color_as_gl_float_ptr(lightColor));  // Specular light

    glPushMatrix();
        glTranslatef(light_pos.x, light_pos.y, light_pos.z);
        glutSolidTeapot(0.1f);
    glPopMatrix();

    light_pos.x = -1.0f; light_pos.y = 1.5f; light_pos.z = -2.0f;
    glLightfv(GL_LIGHT0, GL_POSITION, vec3_as_gl_float_ptr(light_pos));

    lightColor.r = 0.5f; lightColor.g = 1.0f; lightColor.b = 0.5f; // green
    glLightfv(GL_LIGHT1, GL_AMBIENT, color_as_gl_float_ptr(lightColor));   // Ambient light
    glLightfv(GL_LIGHT1, GL_DIFFUSE, color_as_gl_float_ptr(lightColor));   // Diffuse light
    glLightfv(GL_LIGHT1, GL_SPECULAR, color_as_gl_float_ptr(lightColor));  // Specular light

    glPushMatrix();
        glTranslatef(light_pos.x, light_pos.y, light_pos.z);
        glutSolidTeapot(0.1f);
    glPopMatrix();

    light_pos.x = -light_pos.x; light_pos.z = -light_pos.z; // inverte x e z
    lightColor.r = 0.5f; lightColor.g = 0.5f; lightColor.b = 1.0f; // blue
    glLightfv(GL_LIGHT2, GL_POSITION, vec3_as_gl_float_ptr(light_pos));

    glLightfv(GL_LIGHT2, GL_AMBIENT, color_as_gl_float_ptr(lightColor));   // Ambient light
    glLightfv(GL_LIGHT2, GL_DIFFUSE, color_as_gl_float_ptr(lightColor));   // Diffuse light
    glLightfv(GL_LIGHT2, GL_SPECULAR, color_as_gl_float_ptr(lightColor));  // Specular light

    glPushMatrix();
        glTranslatef(light_pos.x, light_pos.y, light_pos.z);
        glutSolidTeapot(0.1f);
    glPopMatrix();

    //glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
#pragma endregion

#pragma region Draw Model
    glPushMatrix();
    // opcional: transformar modelo para centralizar/escala
    // glTranslatef(...); glScalef(...);

    // aplica centralização e rotação
    glTranslatef(-center[0], -center[1], -center[2]);
    glRotatef(angle, 0.0f, 1.0f, 0.0f);

    glColor3f(1, 1, 1); // garante que a textura não seja multiplicada por cor preta ou modulação

    // Bind da textura principal (use o certo por material)
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_NORMALIZE);

    int last_mat = -2; // inválido inicialmente
    for  (size_t i = 0; i < faces_count; i++) {
        int material_id = faces[i].material_id;
        // se mudou o material -> terminar batch e iniciar novo
        if (material_id != last_mat) {
            if (last_mat != -2) {
                glEnd(); // finaliza batch anterior
            }
            // iniciar novo batch
            glBindTexture(GL_TEXTURE_2D, (material_id >= 0 && material_id < (int)materials_count) ? materials[material_id].texture_id : 0);
            glBegin(GL_TRIANGLES);
            last_mat = material_id;
        }

        // desenha a face i (3 vértices)
        for (int j = 0; j < 3; j++) {
            // Texture Coordinates
            int vti = faces[i].vertex_texture[j] - 1;
            if (vti >= 0 && vti < (int)texture_coords_count) {
                Vec2 t = texture_coords[vti];
                glTexCoord2f(t.u, t.v);
            } else {
                // fallback
                glTexCoord2f(0.0f, 0.0f);
            }

            // Normals
            int ni = faces[i].vertex_normal[j] - 1;
            Vec3 n = normals[ni];
            glNormal3f(n.x, n.y, n.z);

            // Faces
            int vi = faces[i].vertex[j] - 1; // .obj é 1-based
            Vec3 v = vertices[vi];
            glVertex3f(v.x, v.y, v.z);
        }
    }
    if (last_mat != -2) // fecha último batch
        glEnd();

    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
#pragma endregion

    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        fprintf(stderr, "GL error after draw: 0x%04X\n", err);
    }

    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)width / (float)height, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 10.0,   // câmera bem longe no +Z
              0.0, 0.0, 0.0,    // olha para a origem
              0.0, 1.0, 0.0);   // up
}


void idle() {
    angle += 0.2f; // rotation speed
    if (angle > 360.0f) angle -= 360.0f;
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OBJ Loader Demo");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);

    const char* obj_file = "Tree/Tree.obj";
    if (argc == 2)
        obj_file = argv[1];
    int err = load_obj(obj_file);
    if (err != EXIT_SUCCESS) {
        fprintf(stderr, "Erro ao carregar o OBJ: %d\n", err);
        return err;
    }
    else {
        printf("OBJ carregado: %zu vertices, %zu texture_coords, %zu faces\n",
            vertex_count, texture_coords_count, faces_count);
        for (size_t i = 0; i < 5 && i < vertex_count; i++) {
            printf("v[%zu] = (%.2f, %.2f, %.2f)\n", i,
                vertices[i].x, vertices[i].y, vertices[i].z);
        }
        printf("Materials loaded: %zu\n", materials_count);
        for (size_t i = 0; i < materials_count; ++i) {
            printf("  material_id[%zu] name='%s' texture_id=%u\n", i, materials[i].name, (unsigned)materials[i].texture_id);
        }
    }

    // calcula bounding box
    for (size_t i = 0; i < vertex_count; i++) {
        if (vertices[i].x < bbmin[0]) bbmin[0] = vertices[i].x;
        if (vertices[i].y < bbmin[1]) bbmin[1] = vertices[i].y;
        if (vertices[i].z < bbmin[2]) bbmin[2] = vertices[i].z;
        if (vertices[i].x > bbmax[0]) bbmax[0] = vertices[i].x;
        if (vertices[i].y > bbmax[1]) bbmax[1] = vertices[i].y;
        if (vertices[i].z > bbmax[2]) bbmax[2] = vertices[i].z;
    }
    center[0] = (bbmin[0] + bbmax[0]) / 2.0f;
    center[1] = (bbmin[1] + bbmax[1]) / 2.0f;
    center[2] = (bbmin[2] + bbmax[2]) / 2.0f;

    printf("Bounding box: min(%.2f, %.2f, %.2f) max(%.2f, %.2f, %.2f)\n",
        bbmin[0], bbmin[1], bbmin[2], bbmax[0], bbmax[1], bbmax[2]);
    printf("Centro do modelo: (%.2f, %.2f, %.2f)\n",
        center[0], center[1], center[2]);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutMainLoop();

    return EXIT_SUCCESS;
}
