(require-extension lowdown) ; markdown->html
(require-extension posix) ; changing directories mainly
(require-extension irregex) ; regex support yeah!

(define config (open-input-file 

(change-directory blogs)

(define files (reverse (sort (glob "*.blog") string<=?)))

(write-string 
 (irregex-replace "\\${body}" template all-posts)
 #f
 index)


