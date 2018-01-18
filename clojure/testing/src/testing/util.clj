(ns testing.core
  (:gen-class))
(defn map-or-pmap "Usage: (map-or-pmap fn sequence
Run map or parallel map on a sequence based on the size of the sequence"
  [fn seq]
  (if (< (count seq) 20)
    (map fn seq)
    (pmap fn seq)))

(defn replace-map-value "Usage: (replace-hash-value map key val)
Simulate an in-place update on a hash table, using val to replace what's at key" 
  [map key val]
  (assoc (dissoc map key) key val))
