open Unix;;

let dirwrap dir = begin
    let fix_dir dirh =
    
      try
	Some (readdir dirh)
      with
	End_of_file -> None
    in
    let dirh = opendir dir in
    let rec loop () =
      match fix_dir dirh with
      | Some dir -> List.append ["/home/danny/.opam/system/lib/" ^ dir] (loop ())
      | None -> []
    in
    loop ()
  end in

    let rec intersperse item ls = try
	List.append [item; (List.hd ls)] (intersperse item (List.tl ls))
      with
      | Failure _ -> [] in
    
    let is_directory file = match file with
      | "." -> false
      | ".." -> false
      | _ -> (lstat  file).st_kind = S_DIR in
    
    
    let args = "ocamlbrowser" :: (List.filter is_directory (dirwrap "/home/danny/.opam/system/lib") |> intersperse "-I") in

    execvp "ocamlbrowser" (Array.of_list args);;
