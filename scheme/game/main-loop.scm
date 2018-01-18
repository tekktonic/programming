(load "entity.scm")

(define screen (sdl-set-video-mode 640 480 0 (+ SDL_HWPALETTE SDL_HWSURFACE)))

(define entities '())

(define main-loop
  (lambda (entities screen)
       (define latest (make-sdl-event))
       (sdl-poll-event! latest)
       (call-with-current-continuation (lambda (break)
       (let ((event-type (sdl-event-type latest)))
	 (cond
	  ((equal? event-type SDL_QUIT) (exit))
	  ((equal? event-type SDL_KEYDOWN)
	   (let ((event (sdl-event-sym latest)))
	   (cond
	    ((equal? event SDLK_LEFT) (queue-event! ent '(:move-x -5)))
	    ((equal? event SDLK_RIGHT) (queue-event! ent '(:move-x 5)))
	    ((equal? event SDLK_SPACE) (queue-event! ent '(:jump 4)))
	    ((equal? event SDLK_r) (begin (display "Entering repl") (newline)(repl))))))


	  ((equal? event-type SDL_KEYUP)
	   (let ((event (sdl-event-sym latest)))
	   (cond

	    ((or (equal? event SDLK_RIGHT) (equal? event SDLK_LEFT)) (queue-event! ent '(:move-x 0))))))))))


       (update! (car entities))
       (draw! (car entities) screen)
       (sdl-flip screen)
       (sdl-delay 10)
       (main-loop entities screen)))

(main-loop entities screen)
