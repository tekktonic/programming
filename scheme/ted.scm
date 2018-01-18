(define forward-char 
  (lambda (buffer cursor)
    (if (= (string-length buffer) cursor)
	'()
	(+ cursor 1))))

(define back-char 
  (lambda (cursor)
    (if (= 0 cursor)
	'()
	(- cursor 1))))

(define find-char-forward
  (lambda (buffer cursor char)
    (string-index buffer char cursor)))

(define find-char-backward
  (lambda (buffer cursor char)
    (string-index buffer char 0 (- cursor 1))))

(define insert-char
  (lambda (buffer cursor char)
	  (values (string-append (string-append (substring buffer 0 cursor) (string char)) (substring buffer cursor (string-length buffer))) 
		  (+ cursor 1))))

(define delete-char
  (lambda ()
    (set! buffer (string-append (substring buffer 0 (if (= cursor 0) (cursor) (- cursor 1))) (substring buffer cursor (string-length buffer))))
    (set! cursor (- cursor 1))))
