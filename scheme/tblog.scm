(require-extension lowdown) ; markdown->html
(require-extension posix) ; changing directories mainly
(require-extension irregex) ; regex support yeah!


(define output-directory "outdir")
(define blogs "blogdir")

(change-directory blogs)

(define files (reverse (sort (glob "*.blog") string<=?)))

(define make-posts
  (lambda (files)
    (map 
     (lambda (file)
       (define text (read-lines file))
       (let ((title (car text)) (lines (cdr text)))
	 (list title
	       (string-concatenate lines)
	       (irregex-replace
		'(: (submatch-named file (* nonl)) ".blog")
		file
		(lambda (s) (string-append (irregex-match-substring s 1) ".html")))))) files)))

(define generate-post
  (lambda (post)
    (define title (car post))
    (define text (cadr post))
    (define permalink (caddr post))

    (string-append
     "<div class=\"post\"><div class=\"title\">"
     title
     "</div>"
     (with-output-to-string
       (lambda () (markdown->html text))) 
     "<a href=\""
     permalink
     "\">Permalink</a></div><br/>")))

(define template (read-all "blogdir/template.html"))

(define posts (make-posts files))

(define all-posts
  (string-concatenate
   (map
    (lambda (post)
      (define filename (caddr post))
      (define permafile (open-output-file (string-append output-directory "/" filename)))
      (define generated (generate-post post))

      (write-string
       (string-append (irregex-replace "\\${body}" template generated) "\n")
       #f
       permafile)
      (close-output-port permafile)
      generated)
    posts)))

(define index (open-output-file (string-append output-directory "/index.html")))

(write-string 
 (irregex-replace "\\${body}" template all-posts)
 #f
 index)

(close-output-port index)

