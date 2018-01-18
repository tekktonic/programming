(use coops)

(define-class <god> ()
  ((class)))

(define-method (initialize (self <god>) initargs)
  (initialize-slots self initargs))
