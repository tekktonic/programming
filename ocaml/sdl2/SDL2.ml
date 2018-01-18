open Swig
type c_enum_type = [ 
  `unknown
]
type c_enum_value = [ 
  `Int of int
]

type c_obj = c_enum_value c_obj_t
let module_name = "SDL2"

exception BadArgs of string
exception BadMethodName of c_obj * string * string
exception NotObject of c_obj
exception NotEnumType of c_obj
exception LabelNotFromThisEnum of c_obj
exception InvalidDirectorCall of c_obj

external _SDL_INIT_EVERYTHING : c_obj -> Swig.c_obj = "_wrap_SDL_INIT_EVERYTHING" 
external _SDL_Init_f : c_obj list -> c_obj list = "_wrap_SDL_InitSDL2" ;;
let _SDL_Init arg = match _SDL_Init_f (fnhelper arg) with
  [] -> C_void
| [x] -> (if false then Gc.finalise 
  (fun x -> ignore ((invoke x) "~" C_void)) x) ; x
| lst -> C_list lst ;;
external f_init : unit -> unit = "f_SDL2_init" ;;
let _ = f_init ()
let enum_to_int x (v : c_obj) =
   match v with
     C_enum _y ->
     (let y = _y in match (x : c_enum_type) with
       `unknown ->          (match y with
           `Int x -> (Swig.C_int x)
           | _ -> raise (LabelNotFromThisEnum v))
) | _ -> (C_int (get_int v))
let _ = Callback.register "SDL2_enum_to_int" enum_to_int
let int_to_enum x y =
    match (x : c_enum_type) with
      `unknown -> C_enum (`Int y)
let _ = Callback.register "SDL2_int_to_enum" int_to_enum

  let rec swig_val t v = 
    match v with
        C_enum e -> enum_to_int t v
      | C_list l -> Swig.C_list (List.map (swig_val t) l)
      | C_array a -> Swig.C_array (Array.map (swig_val t) a)
      | _ -> Obj.magic v

