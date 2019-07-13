#include "rgb_matrix.h"

void rgb_matrix_set_color_overlay_multi(uint8_t ids[], uint8_t r, uint8_t g, uint8_t b, uint8_t a){
    foreach(id, ids){
        rgb_matrix_set_color_overlay(*id, RGB_BLUE, 255);
    }
}
