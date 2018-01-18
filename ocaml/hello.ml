let rec count_up x =
  if x == 25
  then
      print_int x
  else
  (
    print_endline (string_of_int x);
    count_up (x + 1)
  );;


count_up 1
