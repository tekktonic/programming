(ns defs.object
  (:gen-class))


; Crash course on my understanding of multis:
; these basically say "Define a multi named foo, which takes an object obj, and then pick your methods based on the :object-type key in the obj map
(defmulti update 
  "Usage: (update object) -> object
The ignorant update, it pays no attention to what's going on around it, just does where it needs to go"
[obj] (obj :object-type))

(defmulti think 
"Usage: (think object event-queue) -> object
Thoughtful update, just processes and reacts to its event queue"
[obj event-queue] (obj :object-type))

(defmulti draw-info 
"Usage: (draw-info object) -> {:x x, :y y, :w w, :h h, :depth depth}
Return the drawing info for an object. This allows drawing to be done in parallel as long as we first do a sort based on depth, I think."
[obj] (obj :object-type))
