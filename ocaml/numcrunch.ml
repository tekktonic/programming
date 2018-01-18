let rec do_magic x = 
  if
    x = 100000
  then
    x
  else
    do_magic (x + 1);;

do_magic 1
