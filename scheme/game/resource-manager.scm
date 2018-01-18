(use coops)
(use sdl)
(use srfi-69)

(define-class <resource-manager> ()
  ((sprites initform: (make-hash-table))
   (sounds initform: (make-hash-table))))

(define-method (initialize (self <resource-manager>) initargs)
  (initialize-slots self initargs))

(define-method (get-sprite (self <resource-manager>) resource)
  (if (hash-table-exists? (slot-value self 'sprites) resource)
      (hash-table-set! (slot-value self 'sprites) (img-load (string-append "res/pictures/" (string-append resource ".png"))))))

(define resource-manager (make <resource-manager>))
