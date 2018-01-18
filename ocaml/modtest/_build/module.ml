module type EModule = sig
    type t
    val make : unit -> t
    val update : t -> t
    val draw : int -> unit
    val react : t -> t
  end

module Me = struct
  include EModule
  type t = {x : int; y : int}
  let make () = {x=1; y=1}
  let update self = {x=self.y; y = self.y + 1}
  let draw i = Printf.printf "%d\n%!" i
  let react self = {x=self.y + 1; y = self.y}
end

module You = struct
  include EModule
  type t = {x : int; y : int}
  let make () = {x=1; y=1}
  let update self = {x=self.y; y = self.y - 1}
  let draw i = Printf.printf "%d\n%!" i
  let react self = {x=self.y - 1; y = self.y}
end

module type ET = module type of EModule;;
type entity = (module ET) * EModule.t;;

module Test : Entity = Me;;
let pair = (Test * Test.make ());;

    
