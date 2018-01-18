open Sdl;;
open Sdlloader;;
open Sdlvideo;;
open List;;

class type entity rect image =
  object
    method get_rect : rect
    method get_image : surface
  end;;

class bonk = 
  fun x -> y ->
  object
    inherit entity
    val spritesheet = load_image "bonk.png"
    val x = x
	      
			       

let generate_cloud =
  {x= 0; y = 0; w = 60; h = 60; image = (create_RGB_surface [`HWSURFACE; `ASYNCBLIT] ~w:60 ~h:60 ~bpp:32 ~rmask:(Int32.of_int 0xffffff) ~gmask:(Int32.of_int 0xffffff) ~bmask:(Int32.of_int 0xffffff) ~amask:(Int32.of_int 0xffffff))};;

let generate_bonk = 
let cloud_draw screen c = 
  fill_rect ~rect:{r_x = c.x; r_y = c.y; r_w = c.w; r_h = c.h} screen (map_RGB screen white);;

let new_bonk cellx cellh =
  {x = 0; y = 0; w = 64; h = 64; image = (load_image "bonk.png")
init [`VIDEO; `TIMER];;
print_endline "I'm doing something!";;
Random.self_init;;
let screen = set_video_mode 640 480 [`HWSURFACE];;
let cloud = generate_cloud;;
cloud_draw screen cloud;;
flip screen;;
Sdltimer.delay 500;;
Sdl.quit ();;
