(use srfi-1)
(use sdl)
(use coops)

(define entities '())

(define-class <entity> ()
  ((x initform: 0 reader: x)
   (y initform: 0 reader: y)
   (w initform: 0 reader: w)
   (name initform: "entity" reader: name)
   (h initform: 0 reader: h)
   (color initform: (make-sdl-color 255 255 255) reader: color)))

(define-method (initialize (self <entity>) initargs)
  (initialize-slots self initargs))

(define-method (update (self <entity>)) #f)

(define-method (draw (self <entity>) screen)
  (sdl-fill-rect screen (make-sdl-rect (x self) (y self) (w self) (h self) (color self))))

(define dummy (make <entity>))

(define-class <player> (<entity>)
  ((y-speed initform: 0 accessor: y-speed)
   (x-speed initform: 0 accessor: x-speed)
   (name initform: "player" reader: name)
   (g initform: #f)))

(define-method (update (self <player>))
  ; we need to be sure to check where we will be, not where we area
  (let ((pos-x (+ (x self) (x-speed self) ;(/ (w self) 2)
)) (pos-y (+ (y self) (h self) (y-speed self) 1)))
    (if (nothing-at self pos-x pos-y)
;    (if (nothing-at-rect self pos-x pos-y (w self) 1)
	(if (< (y-speed self) 30)
	    (begin (set! (y-speed self) (+ (y-speed self) 3)) (set! (slot-value self 'g) #f)))
	(let ((collision-obj (get-at pos-x (+ 1 pos-y))))
	    (set! (slot-value self 'y) (- (y collision-obj) (h self)))
	    (set! (y-speed self) 0)
	(set! (slot-value self 'g) #t))))

  (set! (slot-value self 'x) (+ (x self) (x-speed self)))
  (set! (slot-value self 'y) (+ (y self) (y-speed self))))

(define-method (jump (self <player>))
  (if (slot-value self 'g)
      (begin
	(set! (y-speed self) -30)
	(set! (slot-value self 'g) #f))))

(define-method (move (self <player>) direction)
  (cond
   ((equal? direction 'left) (set! (x-speed self) -10))
   ((equal? direction 'right) (set! (x-speed self) 10))
   ((equal? direction 'stop) (set! (x-speed self) 0))))

(define-class <win> (<entity>)
  ((color initform: (make-sdl-color 255 255 0))
   (name initform: "name" reader: name)))

(define-method (update (self <win>))
  (let ((player (car entities)))
;  (if (or (< (+ (x self) (w self)) (x player)) (> (x self) (+ (x player) (w player))) (< (+ (y self) (h self)) (y player)) (> (y self) (+ (y player) (h player))))
    (display (nothing-at-rect self (x self) (y self) (w self) (h self)))
    (newline)
    (if (not (nothing-at-rect self (x self) (y self) (w self) (h self)))
      '()
      (exit))))


(define nothing-at
  (lambda (exclude pos-x pos-y)
    (define ents (remove (lambda (i) (eq? i exclude)) entities))
    (call/cc
     (lambda (break) 
       (for-each
	(lambda (i)
	  (if (and (<= (x i) pos-x) (>= (+ (x i) (w i)) pos-x) (<= (y i) pos-y) (>= (+ (y i) (h i)) pos-y))
	      (break #f))) ents)
       (break #t)))))

(define get-at
  (lambda (pos-x pos-y)
    (call/cc
     (lambda (break)
       (for-each
	(lambda (i)
	  (if (and (<= (x i) pos-x) (>= (+ (x i) (w i)) pos-x) (<= (y i) pos-y) (>= (+ (y i) (h i)) pos-y))
	      (begin (break i)))) entities)
       (break dummy)))))

(define nothing-at-rect
  (lambda (exclude pos-x pos-y pos-w pos-h)
    (define ents (remove (lambda (i) (eq? i exclude)) entities))
    (call/cc
     (lambda (break)
       (for-each
	(lambda (i)
	  (if (or (<= (+ pos-x pos-w) (x i)) (>= pos-x (+ (x i) (w i))) (<= (+ pos-y pos-h ) (y i)) (>= pos-y (+ (y i) (h i))))
	      (break #f))) entities)
       (break #t)))))

(define main
  (lambda (entities)
    (define screen (sdl-set-video-mode 640 480 32 SDL_HWSURFACE))
    (let ((event (make-sdl-event)) (player (car entities)))
      (define loop
	(lambda (entities)
	  (sdl-poll-event! event)
	  (let ((event-type (sdl-event-type event)))
	    (cond
	     ((equal? event-type SDL_QUIT) (begin (sdl-quit) (exit)))
	     ((equal? event-type SDL_KEYDOWN)
	      (begin
		(let ((key (sdl-event-sym event)))
		  (cond
		   ((equal? key SDLK_z) (jump player))
		   ((equal? key SDLK_RIGHT) (move player 'right))
		   ((equal? key SDLK_LEFT) (move player 'left))))))
	     ((equal? event-type SDL_KEYUP)
	      (begin
		(let ((key (sdl-event-sym event)))
		  (if (or (equal? key SDLK_RIGHT) (equal? key SDLK_LEFT))
		      (move player 'stop)))))))

	  (for-each
	   (lambda (entity)
	     (update entity)
;	     (draw entity screen)) entities)
	  (sdl-flip screen)
	  (sdl-fill-rect screen (make-sdl-rect 0 0 640 480) 0)
	  (sdl-delay (/ 1000 30))
	  (loop entities)))
    (loop entities))))

(set! entities (append entities (list (make <player> 'x 0 'y 0 'w 32 'h 32))))
(set! entities (append entities (list (make <entity> 'x 0 'w 128 'y 256 'h 32 'color (make-sdl-color 255 0 0)))))
(set! entities (append entities (list (make <entity> 'x 200 'w 128 'y 200 'h 32 'color (make-sdl-color 255 0 0)))))

(set! entities (append entities (list (make <win> 'x 256 'w 32 'y 150 'h 32))))

(main entities)
