(require-extension ncurses srfi-25)

(define doit (lambda ()
(define w 79);sane defaults
(define h 24)

(initscr)
;(start_color)

(define integer->number (lambda (i) (* i 1.0)))
(set!-values (h w) (getmaxyx stdscr))
(printw (number->string w))
(refresh)
(define infinite-loop (lambda () (infinite-loop)) )
(infinite-loop)))
