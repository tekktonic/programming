(use vector-lib)



(define 
  (lambda (vect item)
    (vector-append (vector-copy vect 0 (- item 1)) (vector-copy vect item))))
