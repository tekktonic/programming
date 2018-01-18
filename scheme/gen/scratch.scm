(use html-tags html-utils doctype regex regex-literals)

(define main 
  (lambda (argv)

    (define-syntax define-page
      (syntax-rules ()
	((_ t body1 ...)
	 (begin (define title t) (define body (string-append body1 ... "<div id='prev'><a href=" ))))))

    (define template (car argv))

    (xhtml-style? #t)

    (load template)
    (display
     (html-page body title: title doctype: doctype-xhtml-1.0-strict content-type: "application/xhtml+xml" charset: "UTF-8")
     (open-output-file (string-substitute #/\.tscm$/u ".html" template)))))

