(use coops)
(use sdl)
(use vector-lib)
(use srfi-1)

(define entities '()) ; a vector of entities that are globally accessible

(define entities-ids '())
(load "resource-manager.scm")
; this block is all automatically generated
(define-generic (initialize obj args))
(define-generic (x obj))
(define-generic (x! obj))
(define-generic (y obj))
(define-generic (y! obj))
(define-generic (w obj))
(define-generic (h obj))
(define-generic (id obj))
(define-generic (x-speed obj))
(define-generic (y-speed obj))
(define-generic (events))
(define-generic (images obj))
(define-generic (close))

;now actual defined methods
(define-generic (queue-event! obj event))
(define-generic (draw! obj screen))
(define-generic (update! obj))
(define-generic (match-callback obj event-type))

(define-class <entity> ()
  ((x initform: 0 reader: x writer: x!)
   (x-speed initform: 0 accessor: x-speed)
   (y initform: 0 reader: y writer: y!)
   (y-speed initform: 0 accessor: y-speed)
   (w initform: 64 reader: w)
   (h initform: 64 reader: h)
   (id reader: id)
   (images initform: '() reader: images)
   (events initform: (make-queue) accessor: events)))

(define-method (initialize (self <entity>) initargs)
  (initialize-slots self initargs)
  (set! entities (append entities self)))

(define-method (delete (self <entity>))
  (for-each
   (lambda (img)
     (sdl-free-surface img))
   (images self))

  (remove!
   (lambda (entity)
     (eq? (id entity) (id self))
   entities)))

(define-method (draw! (self <entity>) scr)
  (sdl-blit-surface (image self) (make-sdl-rect (x self) (y self) (w self) (h self)) scr 0))

(define-method (update! (self <entity>))
  (let ((x (x self)) (y (y self)))
    (begin
      (define handle-events
	(lambda (queue)
	  (if (not (queue-empty? queue))
	      (begin
		(let ((event (queue-remove! queue)))
		  ((match-callback self (car event)) self (cadr event)))
		(handle-events queue)))))
      (handle-events (events self))
      (x! self (+ x (x-speed self)))
      (y! self (+ y (y-speed self)))
      (if 
       (and (< (y-speed self) 0) (< (y-speed self) 5))
       (set! (y-speed self) (+ (y-speed self) 0.5))))))

(define-method (queue-event! (self <entity>) event)
  (queue-add! (events self) event))

(define-method (match-callback (self <entity>) event-type)
  (cond
   ((equal? event-type ':move-x) (lambda (self arg) (set! (x-speed self) arg)))
   ((equal? event-type ':jump) (lambda (self arg) (set! (y-speed self) arg)))))
