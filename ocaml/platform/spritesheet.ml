open Sdl;;
open Sdlvideo;;

type spritesheet = {
  sheet: surface;
}

let load_sheet string =
    {sheet = Sdlloader.load_image string};;

let get_sprite sheet dest pos =
  let (x, y) = pos in

  set_clip_rect sheet.sheet (rect ((surface_info dest).w * x) ((surface_info dest).h * y) ((surface_info dest).w) ((surface_info dest).h));
  blit_surface ~src:sheet.sheet ~dst:dest ();
  (* This returns unit, which I would've returned anyway *)
  unset_clip_rect sheet.sheet;;


Sdl.init [`VIDEO];;

let screen = set_video_mode 640 480 [`HWSURFACE];;

let sheet = load_sheet "bonk.png";;
let sprite = create_RGB_surface_format screen [`HWSURFACE; `SRCALPHA] 32 48;;

let dummyrect = rect 0 0 640 480;;

let rec loop () =
  fill_rect screen (Int32.of_int 0xff00ff);
  blit_surface ~src_rect:(rect 0 0 64 64) ~src:sprite ~dst:screen ();
  flip screen;
  loop ();;

loop ();;
