open List;;

let flatten lol =
  match lol with
  |[] -> []
  | [head] -> head
  | [head : 'a list] -> lol head
