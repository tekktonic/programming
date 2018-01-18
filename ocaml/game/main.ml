open Sdl;;
open Sdlloader;;
open Sdlvideo;;

class bonk x y =
object
  val x = x
  val y = y
  val spritesheet = load_image "bonk.png"
  method get_spritesheet = spritesheet
end;;

init [`VIDEO; `TIMER];;

let screen = set_video_mode 800 600 [];;

let bonk = new bonk 0 0;;

blit_surface ~src:(load_image "bonk.png") ~dst_rect: {r_x = 0; r_y = 0; r_w = 0; r_h = 0} ~dst:screen;;

flip screen;;

Sdltimer.delay 600;;
Sdl.quit ();;
