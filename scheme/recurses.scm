(define fib10k (lambda (i last)
  (if (< i 10000)
      (fib10k (+ i last) i)
      (display i))))

(fib10k 1 0)