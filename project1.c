#define SOKOL_IMPL
#include "sokol_app.h"
#include "sokol_gfx.h"
#include "sokol_glue.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define GX_IMPL
#include "gx.h"

bool mouse;
int mouse_x;
int mouse_y;
float sprite_x;
float sprite_y;
float vx = 1;
float vy = -1;
float g = .05;
bool w;
bool w_prior;
bool a;
bool s;
bool d;
int jumpHeight;
int nonjump;

gx_sprite hi;

void init(void) {
    sg_setup(&(sg_desc){
        .context = sapp_sgcontext()
    });
    gx_setup();
    hi = gx_make_sprite("hinata.png");
}

void frame(void) {
    gx_begin_drawing();
    gx_draw_rect(0, 0, 800, 600, (sg_color) { .4f, .5f, 1.0f, 1.0f });

    if (w == true && w_prior == false && sprite_y == 450) {
        vy -= 4;
    }
    w_prior = w;

    if (a == true) {
        vx -= .5;
        if (vx < -2) {
            vx = -2;
        }
    } else if (d == true) {
        vx += .5;
        if (vx > 2) {
            vx = 2;
        }
    } else {
        if (sprite_y == 450) { // friction for ground to slow down
            vx *= .9;
        } 
    }

    sprite_x += vx;
    sprite_y += vy;
    vy += g;

    if (sprite_y > 450) {
        sprite_y = 450;
        vx = 0;
        vy = 0;
    }   

    

    gx_draw_sprite(sprite_x, sprite_y, &hi); 
    gx_end_drawing();
}


void cleanup(void) {
    gx_shutdown();
    sg_shutdown();
}

static void event(const sapp_event* ev) {
    switch (ev->type) {
        case SAPP_EVENTTYPE_MOUSE_DOWN:
            mouse = 1;
            break;
        case SAPP_EVENTTYPE_MOUSE_UP:
            mouse = 0;
            break;
        case SAPP_EVENTTYPE_MOUSE_MOVE:
            mouse_x = ev->mouse_x;
            mouse_y = ev->mouse_y;
            break;
        case SAPP_EVENTTYPE_KEY_DOWN:
            if (ev->key_code == SAPP_KEYCODE_W) {
                w = true;
            } else if (ev->key_code == SAPP_KEYCODE_A) {
                a = true;
            } else if (ev->key_code == SAPP_KEYCODE_S) {
                s = true;
            } else if (ev->key_code == SAPP_KEYCODE_D) {
                d = true;
            } break;
        case SAPP_EVENTTYPE_KEY_UP:
            if (ev->key_code == SAPP_KEYCODE_W) {
                w = false; // Check to see if this means that the key was let go
            } else if (ev->key_code == SAPP_KEYCODE_A) {
                a = false;
            } else if (ev->key_code == SAPP_KEYCODE_S) {
                s = false;
            } else if (ev->key_code == SAPP_KEYCODE_D) {
                d = false;
            } break;
        default:
            break;
 
    }
}

sapp_desc sokol_main(int argc, char* argv[]) {
    (void)argc; (void)argv;
    return (sapp_desc){
        .init_cb = init,
        .frame_cb = frame,
        .cleanup_cb = cleanup,
        .event_cb = event,
        .width = 800,
        .height = 600,
        .window_title = "test1",
    };
}
