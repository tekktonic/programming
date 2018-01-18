open Unix;;
open String;;
open Array;;

type child = { 
  r: file_descr;
  w: file_descr;
  id: int;};;

let new_child prog args =
  let (parent_r, child_w) = pipe () in
  let (child_r, parent_w) = pipe () in
  let pid = 0 in 
  let pid =  create_process prog args child_w child_r stderr in
  {w = parent_w; r = parent_r; id = pid};;

let c = new_child "./pipe" [|"meh"|] in

let read_buf = String.create 5 in
let re = read c.r read_buf 0 5 in
print_endline read_buf;
write c.w "arg\n" 0 4;;


