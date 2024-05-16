#include "assets.h"

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 256
#define DIGIT_LIMIT 6

static int is_end_number(unsigned char c)
{
    return c == ' ' || c == ',' || c == '\n';
}

int *load_map(const char *file_name, int *rows, int *cols)
{
    FILE *map_file = NULL;
    errno_t err = 0;
    size_t res = 0;
    unsigned char *buffer = NULL;
    char map_file_type = '\0';
    char row_buf[DIGIT_LIMIT] = {0};
    char col_buf[DIGIT_LIMIT] = {0};
    char tile_buf[DIGIT_LIMIT] = {0};
    int map_size = 0;
    int *map_data = NULL;
    int read_i = 0;
    int tile_i = 0;

    //------------------------------------------------------------------------
    // open file
    err = fopen_s(&map_file, file_name, "rb");
    if (map_file == NULL)
    {
        return NULL;
    }

    buffer = malloc(sizeof(unsigned char) * BUFFER_SIZE);

    //------------------------------------------------------------------------
    // read first byte to determine file type
    res = fread(buffer, sizeof(unsigned char), 1, map_file);
    if (res != 1)
    {
        free(buffer);
        fclose(map_file);
        return NULL;
    }
    map_file_type = buffer[0];

    // skip newline
    fread(buffer, sizeof(unsigned char), 1, map_file);

    //------------------------------------------------------------------------
    // read row count
    read_i = 0;
    do
    {
        res = fread(&(buffer[read_i++]), sizeof(unsigned char), 1, map_file);
    } while (buffer[read_i - 1] != '\n' && res > 0 && read_i < DIGIT_LIMIT - 1);

    for (int i = 0; i < read_i; i++)
    {
        row_buf[i] = buffer[i];
    }

    row_buf[read_i - 1] = '\0';

    sscanf_s(row_buf, "%d", rows);

    //------------------------------------------------------------------------
    // read column count
    read_i = 0;
    do
    {
        res = fread(&(buffer[read_i++]), sizeof(unsigned char), 1, map_file);
    } while (buffer[read_i - 1] != '\n' && res > 0 && read_i < DIGIT_LIMIT - 1);

    for (int i = 0; i < read_i; i++)
    {
        col_buf[i] = buffer[i];
    }

    col_buf[read_i - 1] = '\0';

    sscanf_s(col_buf, "%d", cols);

    //------------------------------------------------------------------------
    // read the tile data

    map_size = *rows * *cols;
    map_data = malloc(sizeof(int) * map_size);
    read_i = 0;

    while (tile_i < map_size && res)
    {
        do
        {
            res = fread(&(buffer[read_i++]), sizeof(unsigned char), 1, map_file);
        } while (res && !is_end_number(buffer[read_i - 1]));

        for (int i = 0; i < read_i; i++)
        {
            tile_buf[i] = buffer[i];
        }

        tile_buf[read_i - 1] = '\0';

        sscanf_s(tile_buf, "%d", &(map_data[tile_i++]));

        read_i = 0;

        // skip over the rest of the non digit characters
        do
        {
            res = fread(&(buffer[read_i++]), sizeof(unsigned char), 1, map_file);
        } while (res && is_end_number(buffer[read_i - 1]));

        if (res)
        {
            buffer[0] = buffer[read_i - 1];
        }

        read_i = 1;
    }

    free(buffer);
    fclose(map_file);

    return map_data;
}

int tort_load_all_assets(cr_app *app)
{
    // images
    if (cr_load_texture(app, "sprite-sheet.png") == NULL)
    {
        fprintf(stderr, "failed to load sprite sheet\n");
        return 0;
    }

    // fonts
    if (cr_load_font(app, "pokemon_fire_red.ttf", 16) == NULL)
    {
        fprintf(stderr, "failed to load pokemon_fire_red font\n");
        return 0;
    }

    // sounds

    return 1;
}
