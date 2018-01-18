let dom = new Js_of_ocaml.Dom_html.document in
    let elm = dom#getElementById "score" in
    elm#innerHTML "foobar";;
    
