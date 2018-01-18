open OcsfmlWindow
open OcsfmlGraphics
open OcsfmlSystem

let rotate l = match l with
| [] -> []
| [hd] -> [hd]
| [hd; sec] -> [sec; hd]
| hd :: sec :: tail -> List.append (sec :: tail) [hd]
;;

class real_sprite ?texture: OcsfmlGraphics.const_texture =
object
  inherit drawable (Sprite.to_drawable (Sprite.default ()))
  val mutable sprite = new sprite ~texture ()
  method destroy = sprite#destroy
  method draw : render_target -> BlendMode.t -> transform -> texture -> shader -> unit = sprite#draw render_target BlendMode.t transform texture shader
end
  
class player =
object
  val mutable sprites = [new real_sprite ~texture: (new texture (`File "Officer1.png")) (); new sprite ~texture: (new texture (`File "Officer2.png")) ()]

method update = sprites <- rotate sprites
method get_sprite = List.hd sprites
method get_tex = (List.hd sprites)#get_texture
end


let _ = begin
    let window = new render_window (VideoMode.create ~w:800 ~h:600 ()) "Window" in
    let clock = new clock in
    let bg = new sprite ~texture: (new texture (`File "forest.png")) () in
    let sprite = new player in
    let rec event_loop () =
      match window#poll_event with
      | Some e ->
	 let open Event in
	 begin
		  match e with
		  | Closed ->
		     window#close
		  | _ -> ()
	 end;
	 event_loop ()
      | _ -> () in

    let rec main_loop () =
      begin
	let dt = clock#get_elapsed_time in
	if window#is_open
	then begin
	    event_loop ();
	    if (Time.as_milliseconds dt) > 500
	    then begin
		window#clear ();
		window#draw bg;
		window#draw sprite#get_sprite;
		window#display;
		sprite#update;
		ignore clock#restart;
	      end;
		main_loop ();

	  end
      end in
    main_loop ();
    match sprite#get_tex with
    | Some t -> begin 
		t#destroy
	      end
    | _ -> ()
		 
end
