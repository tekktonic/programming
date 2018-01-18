(use coops)
(declare (uses tile))

(define foo (make <tile>))
(define-class <level> ()
  ((tiles accessor: tiles)))

(define-method (initialize (self <level>) initargs)
  (initialize-slots self initargs))
