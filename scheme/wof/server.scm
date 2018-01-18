(require-extension srfi-13)
(require-extension posix)
(require-extension tcp6)
(require-extension matchable)

(define-syntax spawn-and-run
  (syntax-rules ()
    ((spawn-and-run <fn> ...)
     (begin
       (define pid (process-fork))
       (if (= pid 0)
	   (<fn> ...))))))

(define safe-split
  (lambda (s)
    (if (not (eof-object? s))
	(string-split s)
	'())))

(define handle-connection
  (lambda (in-sock out-sock)
    (define connection-mainloop
      (lambda (in-sock out-sock)
	(define tokens (safe-split (read-line in-sock)))
	(match tokens
	       [() '()]
	       [("quit" . ()) '()]
	       [(x . y) 
		(begin (write-line x out-sock) (connection-mainloop in-sock out-sock))])))
    (connection-mainloop in-sock out-sock)
    (close-input-port in-sock)
    (close-output-port out-sock)))


(define main
  (lambda ()
    (define main-loop (lambda ()
      (define-values (in-sock out-sock) (tcp-accept listener))
      (display "got a listener!")
      (newline)
      (spawn-and-run handle-connection in-sock out-sock)
      (main-loop)))

    (define listener (tcp-listen 1337))
    (main-loop)
    (tcp-close listener)))

(main)
      
    
