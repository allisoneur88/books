(defun square (x)
  (* x x))
(square 12)

(defparameter x 10)
(+ x x)

(defparameter l '(first second third))
(first l)
(rest l)
(length l)
(cons 'Nul l)

(defun last-name (name)
  "Select the last name from a name represented as a list"
  (first (last name)))

(last-name (list 'Sasha 'D 'Ganshin))
(documentation 'last-name 'function)


(defun first-name (name)
  "Select the first name from a namce represented as a list"
  (first name))

(first-name (list 'Sasha 'D 'Ganshin))

(defparameter names
  '((Sasha D Ganshin) (Lena A Suslina) (Joseph A Ganshin)))

(mapcar #'first-name names)

(mapcar #'- '(1 2 3 4))
(mapcar #'+ '(1 2 3 4) '(10 20 30 40))

(defvar test-names
  '((John Q Public) (Malcolm X)
    (Admiral Grace Murray Hopper) (Spot)
    (Aristotle) (A A Milne) (Z Z Top)
    (Sir Larry Olivier) (Miss Scarlett)))

(mapcar #'last-name test-names)
(mapcar #'first-name test-names)

(defparameter *titles*
  '(Mr Mrs Miss Ms Sir Madam Dr Admiral Major General)
  "A list of titles that can appear at the start of the name")

(defun first-name (name)
  (if (member (first name) *titles*)
      (first-name (rest name))
      (first name)))

(mapcar #'first-name test-names)
(trace first-name)
(first-name '(Madam Admiral General Paula Tabletop))
(untrace first-name)

(mapcar #'square '(1 2 3 4 5))

(defun mappend (fn the-list)
  "Apply fn to each element of list and append the results"
  (apply #'append (mapcar fn the-list)))

(apply #'+ '(1 2 3 4))

(apply #'append '((1 2 3) (a b c)))

(defun self-and-double (x) (list x (+ x x)))

(self-and-double 5)

(mappend #'self-and-double '(1 10 100))

(defun mappend2 (fn the-list)
  "Alternative mappend without using mapcar"
  (if (null the-list)
      nil
      (append (funcall fn (first the-list))
              (mappend2 fn (rest the-list)))))

(mappend2 #'self-and-double '(1 10 100))

(funcall #'+ 1 2 3)
(apply #'+ '(1 2 3))

((lambda (x) (* x x)) 5)
(funcall #'(lambda (x) (* x x)) 5)

(mappend #'(lambda (l) (list l (reverse l))) '((1 2 3) (a b c)))

(length "a string")
(length "")


(defparameter *titles*
  '(Mr Mrs Miss Ms Sir Madam Dr Admiral Major General)
  "A list of titles that can appear at the start of the name")

(defun first-name (name)
  (if (member (first name) *titles*)
      (first-name (rest name))
      (first name)))

; ex. 1.1 
; Define a version of last-name that handles "Rex Morgan MD,"
; "Morton Downey, Jr." and whatever other cases you can think of.
(defparameter *endings*
  '(Md Jr)
  "A list of endings that can appear at the end of the name")

(defun last-name (name)
  (if (member (first (last name)) *endings*)
      (last-name (butlast name))
      (first (last name))))
  

(last-name '(Morton Downey Jr))

; ex. 1.2
; Write a function to exponentiate, or raise a number
; to an integer power
(defun power (base exp)
  (if (= exp 0)
      1
      (* base (power base (- exp 1)))))

(power 3 2)

; ex. 1.3
; Write a function that counts the number of atoms in an expression
; For example: (count-atoms '(a (b) c)) => 3

(defun count-atoms (exp)
  (if (null exp)
      0
      (if (atom (first exp))
       (+ 1 (count-atoms (rest exp)))
       (+ (count-atoms (first exp)) (count-atoms (rest exp))))))


(count-atoms '(a b c))
(count-atoms '(a (b) c d))
(count-atoms '(a () c d e))

; ex. 1.4
; Write a function that counts the number of times an expression
; occurs anywhere within another expression
; For example: (count-anywhere 'a '(a ((a) b) a)) => 3
       
(defun count-anywhere (needle haystack)
  (if (null haystack)
      0
      (if (atom (first haystack))
       (if (eq (first haystack) needle)
        (+ 1 (count-anywhere needle (rest haystack)))
        (count-anywhere needle (rest haystack)))
       (+ (count-anywhere needle (first haystack)) (count-anywhere needle (rest haystack))))))

(count-anywhere 'a '(a ((a) b) a))

; ex. 1.5
; Write a function to compute the dot product of two sequences 
; of numbers, represented as lists. The dot product is computed
; by multiplying corresponding elements and then adding up
; the resulting products. For example:
; (dot-product '(10 20) '(3 4)) => 110 // (10*3 + 20*4)

(defun dot-product (l1 l2)
  (if (or (null l1) (null l2))
      0
      (+ (* (first l1) (first l2)) (dot-product (rest l1) (rest l2)))))

(dot-product '(10 20) '(3 4))
