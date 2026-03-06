#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <time.h>
#include <stdlib.h>

#define REFRESH_RATE 100000

typedef struct {
    int x;
    float y;
    float speed;
    int trail_len;
} Drop;

void get_terminal_size(int *col, int *row) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    *col = w.ws_col;
    *row = w.ws_row;
}

void init_drops(Drop *drops, int cols) {
    for(int i = 0; i < cols; i++) {
        drops[i].x = i + 1;
        drops[i].y = 1;
        drops[i].speed = 0.1 + (float)(rand() % 100) / 100;
        drops[i].trail_len = 10 + rand() % 10;
    }
}

void clear_screen() {
    printf("\033[?25l\033[2J");
}

void print_pixels(int y, int x, int r, int g, int b, char c) {
    if(y < 1 ) return;

    printf("\033[%d;%dH\033[38;2;%d;%d;%dm%c", y, x, r, g, b, c);
}

char get_char(){
    return "01"[rand() % 2]; // Printable ASCII characters
}

// void mostra_drops (Drop *drops, int cols) {
//     for(int i = 0; i < cols; i++) {
//         printf("Drop %d: x=%d, y=%.1f, speed=%.2f, trail_len=%d\n", 
//             i, drops[i].x, drops[i].y, drops[i].speed, drops[i].trail_len);
//     }
// }

int main() {
    
    int width, height;

    get_terminal_size(&width, &height);

    srand(time(NULL));
    Drop *drops = malloc(width * sizeof(Drop));
    if (drops == NULL) {
        fprintf(stderr, "Failed to allocate memory for drops.\n");
        return 1;
    }
    init_drops(drops, width);
    // mostra_drops(drops, width);
    
    clear_screen();

    int new_width, new_height;
    while(1) {
        get_terminal_size(&new_width, &new_height);
        if (new_width != width || new_height != height) {
            width = new_width;
            height = new_height;
            drops = realloc(drops, width * sizeof(Drop));
            init_drops(drops, width);
            clear_screen();
        }

        for(int i = 0; i < width; i++) {
            int head_y = (int)drops[i].y;

            if(head_y > 0 && head_y <= height) {
                print_pixels(head_y, drops[i].x, 0, 255, 0, get_char());
            }

            for ( int j = 0; j < drops[i].trail_len; j++)
            {
                int trail_y = head_y - j;
                if (trail_y > 0 && trail_y <= height) {
                    
                    int brightness = 255 - (j * (255 / drops[i].trail_len));
                    print_pixels(trail_y, drops[i].x, 0, brightness, 0, get_char());
                }
            }

            // Move the drop down
            drops[i].y += drops[i].speed;

            if(drops[i].y - drops[i].trail_len > height) {
                drops[i].y = 0;
                drops[i].speed = 0.1 + (float)(rand() % 100) / 100;
            }           
        }
        
        // Update and display drops here
        usleep(REFRESH_RATE); // Sleep for a short time to control refresh rate
    }

    free(drops);

    return 0;
}