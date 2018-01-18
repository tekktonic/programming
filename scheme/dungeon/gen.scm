(use coops)
(use srfi-1)
(use extras)

(define-class <tile> ()
  ((x reader: x)
   (y reader: y)
   (character accessor: character)
   (level accessor: level)
   (in-room initform: #f accessor: in-room?)
   (entity accessor: entity)
   (items initform: '() accessor: item)))

(define-method (initialize (self <tile>) initargs)
  (initialize-slots self initargs))

(define-class <level>
  ((tiles initform: '() accessor: tiles))
  ((width accessor: width))
  ((height accessor: height)))

(define-method (initialize (self <level>) initargs)
  (initialize-slots self initargs)
  (height self (random 100))
  (width self (random 100))
  )
