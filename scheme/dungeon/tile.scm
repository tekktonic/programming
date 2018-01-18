(use coops)

(define-class <tile> ()
  ((x reader: x)
   (y reader: y)
   (character accessor: character)
   (item initform: #f accessor: item)))

(define-method (initialize (self <tile>) initargs)
  (initialize-slots self initargs))
