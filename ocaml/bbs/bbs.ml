open ANSITerminal;;
open String;;
open Netplex_sockserv;;


let rec break_text len string =
  if length string < len then
    string
  else
    concat "\n" [sub string 0 len; break_text len (sub string len  ((length string) - len))];;
  
print_string [red; on_black] (break_text 4 "abcdeffoobarbazmehwhee\n");;


let sock = create_server_socket "BBS" 
