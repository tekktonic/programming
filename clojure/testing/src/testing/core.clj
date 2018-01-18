(ns testing.core
  (:gen-class)
  (:use testing.util))

(defn -main
  "I don't do a whole lot ... yet."
  [& args]
  ;; work around dangerous default behaviour in Clojure
  (alter-var-root #'*read-eval* (constantly false))
  (main-loop '(4 5 1 2 3 1 2 5 6))
  (println "Hello, World!"))


(defn main-loop
  "Instantiate a few 'objects', then run over a main loop with them"
  [initial-objects]
  (println initial-objects)
  (if (seq initial-objects)
    
    (main-loop (map-or-pmap update (remove (fn [i] (= i nil))initial-objects)))
    nil))

(defn update
  [obj]
  (if (< obj 10000)
    (* obj 4)
    nil))

;(defn map-or-pmap "Usage: (map-or-pmap fn sequence
;Run map or parallel map on a sequence based on the size of the sequence"
;  [fn seq]
;  (if (< (count seq) 20)
 ;   (map fn seq)
  ;  (pmap fn seq)))

;(defn replace-map-value "Usage: (replace-hash-value map key val)
;Simulate an in-place update on a hash table, using val to replace what's at key" 
;  [map key val]
;  (assoc (dissoc map key) key val))
