module Position : sig type t = { x : int; y : int; } end
module Rect :
  sig
    type rect = { x : int; y : int; w : int; h : int; }
    type t
    val t : rect Ctypes_static.typ
  end
module Error : sig val get_error : unit -> string end
module Init :
  sig
    val init_timer : int
    val init_audio : int
    val init_video : int
    val init_joystick : int
    val init_events : int
    val init_everything : int
    val init : int -> (unit, string) Core_kernel.Std_kernel._result
  end
module Window :
  sig
    type t
    val t : t Ctypes_static.typ
    val pos_undefined : int
    val make :
      string ->
      int ->
      int -> int -> int -> int -> (t, string) Core_kernel.Std_kernel._result
  end
module Texture :
  sig
    type t
    val t : t Ctypes_static.typ
    val exists : t -> bool
    val query : t -> int * int
    val free : t -> unit
  end
module Render :
  sig
    type t
    val t : t Ctypes_static.typ
    val make : Window.t -> int -> (t, string) Core_kernel.Std_kernel._result
    val copy :
      t ->
      Texture.t ->
      Rect.rect -> Rect.rect -> (unit, string) Core_kernel.Std_kernel._result
    val present : t -> unit
  end
module Image :
  sig
    val quit : unit -> unit -> unit
    val load_f : Render.t -> string -> Texture.t
    val load :
      Render.t ->
      string -> (Texture.t, string) Core_kernel.Std_kernel._result
  end
module Event :
  sig
    module WindowEvent :
      sig
        type window_event_f
        val window_event_f :
          window_event_f Ctypes.structure Ctypes_static.typ
        val etype :
          (int, window_event_f Ctypes.structure) Ctypes_static.field
        val timestamp :
          (int, window_event_f Ctypes.structure) Ctypes_static.field
        val windowID :
          (int, window_event_f Ctypes.structure) Ctypes_static.field
        val win : (int, window_event_f Ctypes.structure) Ctypes_static.field
        val data1 :
          (int, window_event_f Ctypes.structure) Ctypes_static.field
        val data2 :
          (int, window_event_f Ctypes.structure) Ctypes_static.field
        val window_data3 :
          (int, window_event_f Ctypes.structure) Ctypes_static.field
        val window_data4 :
          (int, window_event_f Ctypes.structure) Ctypes_static.field
        val window_data5 :
          (int, window_event_f Ctypes.structure) Ctypes_static.field
        val window_data6 :
          (int, window_event_f Ctypes.structure) Ctypes_static.field
        val window_data7 :
          (int, window_event_f Ctypes.structure) Ctypes_static.field
        val window_data8 :
          (int, window_event_f Ctypes.structure) Ctypes_static.field
        val window_data9 :
          (int, window_event_f Ctypes.structure) Ctypes_static.field
        val window_data10 :
          (int, window_event_f Ctypes.structure) Ctypes_static.field
        val window_data11 :
          (int, window_event_f Ctypes.structure) Ctypes_static.field
        val window_data12 :
          (int, window_event_f Ctypes.structure) Ctypes_static.field
        val window_data13 :
          (int, window_event_f Ctypes.structure) Ctypes_static.field
        val window_data14 :
          (int, window_event_f Ctypes.structure) Ctypes_static.field
        type t = {
          timestamp : int;
          window_id : int;
          data1 : int;
          data2 : int;
        }
        val of_window_event_f :
          (window_event_f, [ `Struct ]) Ctypes_static.structured -> t
      end
    module KeyboardEvent :
      sig
        val bool_of_int : int -> bool
        type keysym_f
        val keysym_f : keysym_f Ctypes.structure Ctypes_static.typ
        val scancode : (int, keysym_f Ctypes.structure) Ctypes_static.field
        val sym : (int, keysym_f Ctypes.structure) Ctypes_static.field
        val modkey :
          (Unsigned.uint16, keysym_f Ctypes.structure) Ctypes_static.field
        val unused :
          (Unsigned.uint32, keysym_f Ctypes.structure) Ctypes_static.field
        type key_event_f
        val key_event_f : key_event_f Ctypes.structure Ctypes_static.typ
        val etype :
          (Unsigned.uint32, key_event_f Ctypes.structure) Ctypes_static.field
        val timestamp :
          (Unsigned.uint32, key_event_f Ctypes.structure) Ctypes_static.field
        val windowID :
          (Unsigned.uint32, key_event_f Ctypes.structure) Ctypes_static.field
        val repeat :
          (Unsigned.uint8, key_event_f Ctypes.structure) Ctypes_static.field
        val padding :
          (Unsigned.uint16, key_event_f Ctypes.structure) Ctypes_static.field
        val keysym :
          (keysym_f Ctypes.structure, key_event_f Ctypes.structure)
          Ctypes_static.field
        type scancode =
            ScancodeUnknown
          | ScancodeZ
          | ScancodeUp
          | ScancodeDown
          | ScancodeLeft
          | ScancodeRight
          | ScancodeEsc
        val scancode_of_sdl_scancode : int -> scancode
        val int_of_scancode : scancode -> int
        type modkey =
            ModNone
          | ModLShift
          | ModRShift
          | ModLCtrl
          | ModRCtrl
          | ModLAlt
          | ModRAlt
          | ModLGui
          | ModRGui
          | ModNumLk
          | ModCaps
          | ModMode
        val modkey_of_sdl_modkey : Unsigned.uint16 -> modkey
        type keysym = { scancode : scancode; modkey : modkey; }
        type key_state = Released | Pressed
        val key_state_of_sdl_keystate : Unsigned.uint8 -> key_state
        type t = {
          timestamp : int;
          window_id : int;
          state : key_state;
          repeat : bool;
          keysym : keysym;
        }
        val of_key_event_f :
          (key_event_f, [ `Struct ]) Ctypes_static.structured -> t
        val state_f :
          int Ctypes_static.ptr -> Unsigned.uint8 Ctypes_static.ptr
        val state : unit -> bool array
      end
    type t = Quit | Window of WindowEvent.t | Key of KeyboardEvent.t | None
    type sdl_event
    val sdl_event : sdl_event Ctypes.union Ctypes_static.typ
    val etype : (int, sdl_event Ctypes.union) Ctypes_static.field
    val window :
      (WindowEvent.window_event_f Ctypes.structure, sdl_event Ctypes.union)
      Ctypes_static.field
    val keyboard :
      (KeyboardEvent.key_event_f Ctypes.structure, sdl_event Ctypes.union)
      Ctypes_static.field
    val event_of_sdl_event :
      (sdl_event, [ `Union ]) Ctypes_static.structured -> t
    val poll_event_f : sdl_event Ctypes.union Ctypes_static.ptr -> int
    val poll_event : unit -> t
  end
module Etc : sig val delay : int -> unit val quit : unit -> unit end
module Surface :
  sig
    type t
    val t : t Ctypes_static.typ
    val convert : Render.t -> t -> Texture.t
  end
module Color :
  sig
    type color = { r : int; g : int; b : int; a : int; }
    type t
    val t : color Ctypes_static.typ
    val red : color
    val green : color
    val blue : color
    val yellow : color
    val purple : color
    val cyan : color
  end
module Ttf :
  sig
    type t
    val t : t Ctypes_static.typ
    val load : string -> int -> (t, string) Core_kernel.Std_kernel._result
    val render : Render.t -> t -> string -> Color.color -> Texture.t
  end
