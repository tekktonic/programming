open Sdl2;;
open Core.Std;;
  
let ordie a = match a with 
  |Ok a -> a
  |Error e -> failwith e

let force o = match o with
  | Some i -> i

module Position : sig
  type point = {x: int; y:int}
  type t = | Rect of Rect.rect | Point of point
  val to_point : t -> point
  val to_rect : t -> Texture.t -> Rect.rect
  val move : t -> int * int -> t
end = struct
  type point = {x:int; y:int}
  type t = | Rect of Rect.rect | Point of point
  let to_point self = match self with
    |Rect r -> {x=r.Rect.x;y=r.Rect.y}
    |Point p -> p
  let to_rect self reference = match self with
    |Rect r -> r
    |Point p -> begin let self = p in
			 let (w,h) = Texture.query reference in
			 {Rect.x=self.x;Rect.y=self.y;Rect.w=w;Rect.h=h}
		end
  let move self change =
    let (x, y) = change in
    match self with
    |Rect r -> Rect {Rect.x = x; Rect.y=y;Rect.w=r.w;Rect.h=r.h}
    |Point p -> Point {x=x;y=y}
end

module Draw : sig
  val draw : Render.t -> Texture.t -> ?pos:Position.t -> unit -> (unit, string) Core.Result.t
end = struct
  let draw renderer texture ?(pos=Position.Rect {Rect.x=0;Rect.y=0;Rect.w=0;Rect.h=0}) () =
    let srcrect = {Rect.x=0;Rect.y=0;Rect.w=0;Rect.h=0} in
    match pos with
    |Rect r -> Render.copy renderer texture srcrect r
    |Point p -> Render.copy renderer texture srcrect (Position.to_rect (Point p) texture)
end

(* module type Entity = sig *)
(*     type t *)
(*     val position : t -> Position.t *)
(*     val update : t -> t *)
(*     val texture : t -> Texture.t *)
(*     val set_speed : t -> (int * int) -> t *)
(*     val make : Render.t -> t *)
(*   end *)

let steptowards num target step_size =
  if num < target
  then begin
      if (num +. step_size) > target then target else num +. step_size
    end
  else if num > target
  then begin
      if (num -. step_size) < target then target else num -. step_size
    end
  else
    target
      
module Player = struct
  type t = {pos: Position.t; tex: Texture.t; x_speed: float; y_speed: float;font: Ttf.t;score:int}
  let texture self = self.tex;;
  let position self = self.pos;;
  let update self =  let p = Position.to_point self.pos in
		    {pos= (Position.move self.pos (p.Position.x + (Float.to_int self.x_speed), p.Position.y + (Float.to_int self.y_speed))); tex= self.tex; x_speed = steptowards self.x_speed 0. 0.2; y_speed = steptowards self.y_speed 0. 0.2; score= self.score;font= self.font}
  let set_speed self target =
    let (xs, ys) = target in
    {pos=self.pos;tex=self.tex;x_speed=xs;y_speed=ys;score=self.score;font=self.font}
  let set_score self change =
    {pos=self.pos;tex=self.tex;x_speed=self.x_speed;y_speed=self.y_speed;score=(self.score + change);font=self.font}
  let get_speed self = (self.x_speed, self.y_speed)
  let react self keys entities =
    let module Ke = Event.KeyboardEvent in

    (* love you lexical scope ❤ *)

    let ios = Ke.int_of_scancode in
    let self = (if Array.get keys (ios Ke.ScancodeDown) then let (xs, _) = get_speed self in set_speed self (xs, 5.) else self) in
    let self = (if Array.get keys (ios Ke.ScancodeUp) then let (xs, _) = get_speed self in set_speed self (xs, -5.) else self) in
    let self = (if Array.get keys (ios Ke.ScancodeRight) then let (_, ys) = get_speed self in set_speed self (5., ys) else self) in
    let self = (if Array.get keys (ios Ke.ScancodeLeft) then let (_, ys) = get_speed self in set_speed self (-5., ys) else self) in
    self

  let make renderer = {pos=Rect {Rect.x=0;Rect.y=0;Rect.w=32;Rect.h=32};tex= ordie (Image.load renderer "avatar.png");x_speed=0.0;y_speed=3.0;
		       font=ordie (Ttf.load "monofur.ttf" 20);score=0;}
end

module Coin = struct
  type t = {pos: Position.t; tex: Texture.t; points: int}
  let texture self = self.tex;;
  let position self = self.pos;;
  let update self = self

  let make renderer = let value = Random.float 1.0 in
		      {pos=Rect {Rect.x=0;Rect.y=0;Rect.w=force (Float.iround (100. *. value));Rect.h=force (Float.iround (100. *. value))};tex= ordie (Image.load renderer "avatar.png");points=force (Float.iround (100. *. value))}
end

type entity = |Player of Player.t|Coin of Coin.t
type entities = (string * entity) list

		
module Input : sig
  val register_key : Event.KeyboardEvent.keysym -> (Event.KeyboardEvent.t -> entities ->entities) -> unit
  val handle_key : Event.KeyboardEvent.t -> entities -> entities
  (* val wants_key : Event.KeyboardEvent.t -> entities -> (string * Event.t) list *)
end = struct
  let keybinds = Hashtbl.Poly.create ()
  
  let register_key : Event.KeyboardEvent.keysym -> (Event.KeyboardEvent.t -> entities -> entities) -> unit = fun key callback -> ignore (Hashtbl.add keybinds ~key ~data:callback)
											      
  let handle_key key entities = match (Hashtbl.find keybinds key.Event.KeyboardEvent.keysym) with
    |Some f -> f key entities
    |None -> entities

  (* let wants_key key entities  = *)
  (*   let module Ke = Event.KeyboardEvent in *)
  (*   Hashtbl.find_all key entities *)
end

   
