(use coops)

(defclass <isaac> ()
  ((position initform: (make <position> reader: position writer: position!))
   (draw initform: (make <drawable>) reader: position)
   (god reader: god) ; can't init god because I need to know myself
   (reactor initform: (make <reactor> reader: reactor)))

(define-method (initialize (self <isaac>) initargs)
  (initialize-slots self initargs)
  (set! (slot-value self god) (make <god> <bullet> self)); this looks ugly because it should be. god should not normally be writable
  self)




