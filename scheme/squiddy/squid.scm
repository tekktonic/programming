(require-extension coops)

(define-class <squid> ()
  (
   (position initform: (make-position 320 240) accessor: position)
   (sprite initform: (make-sprite "squiddy.png") accessor: sprite)
   (collider initform: (make-collider) accessor: collider)))
