type foo = {x:int; y:int};;
let meh a = print_int a.x;;
let new_foo () = {x= 0; y= 0};;

type bar = {x:int; y:int; z:int};;

let new_bar () = {x = 0; y = 0; z = 0};;



let baz = new_bar ();;

meh baz
