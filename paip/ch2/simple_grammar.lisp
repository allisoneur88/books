(defun sentence () (append (noun-phrase) (verb-phrase)))
(defun noun-phrase () (append (Article) (Noun)))
(defun verb-phrase () (append (Verb) (noun-phrase)))
(defun Article () (one-of '(the a)))
(defun Noun () (one-of '(man ball woman table)))
(defun Verb () (one-of '(hit took saw liked)))

(defun one-of (set)
  "Pick one element of set, and make a list of it."
  (list (random-elt set)))

(defun random-elt (choices)
  "Choose an element from a list at random."
  (elt choices (random (length choices))))

(sentence)
(noun-phrase)
(verb-phrase)
(Article)
(Noun)
(Verb)

(defparameter *simple-grammar*
  '((sentence -> (noun-phrase verb-phrase))
    (noun-phrase -> (Article Noun))
    (verb-phrase -> (Verb noun-phrase))
    (Article -> the a)
    (Noun -> man ball woman table)
    (Verb -> hit took saw liked))
  "A grammar for a trivial subset of English.")

(defvar *grammar* *simple-grammar*
  "The grammar used by generate. Initially this is
  *simple-grammar, but we can switch to other grammars.*")

(assoc 'noun *grammar*)

(defun rule-lhs (rule)
  "The left-hand side of a rule."
  (first rule))

(defun rule-rhs (rule)
  "The right-hand side of a rule."
  (rest (rest rule)))

(defun rewrites (category)
  "Return a list of possible rewrites for this category."
  (rule-rhs (assoc category *grammar*)))  

(rule-rhs (assoc 'noun *grammar*))
(rewrites 'sentence)

(defun mappend (fn the-list)
  "Apply fn to each element of list and append the results."
  (apply #'append (mapcar fn the-list)))

(defun generate (phrase)
  "Generate a random sentence or phrase."
  (cond ((listp phrase)
         (mappend #'generate phrase))
        ((rewrites phrase)
         (generate (random-elt (rewrites phrase))))
        (t (list phrase))))

(defun generate2 (phrase)
  (if (listp phrase)
      (mappend #'generate phrase)
      (let ((choices (rewrites phrase)))
       (if (null choices)
        (list phrase)
        (generate (random-elt choices))))))

(generate 'sentence)
(generate2 'sentence)

; ex. 2.1
; Write a version of generate that uses cond 
; but avoids calling rewrites twice.

(defun generate3 (phrase)
  (let ((choices (rewrites phrase)))
    (cond ((listp phrase)
           (mappend #'generate3 phrase))
          ((null choices)
           (list phrase))
          (t (generate3 (random-elt choices))))))

(generate3 'sentence)

; ex. 2.2
; Write a version of generate that explicitly differentiates
; between terminal symbols (those with no rewrite rools) and
; nonterminal symbols;

(defparameter *bigger-grammar*
  '((sentence -> (noun-phrase verb-phrase))
    (noun-phrase -> (Article Adj* Noun PP*) (Name) (Pronoun))
    (verb-phrase -> (Verb noun-phrase PP*))
    (PP* -> () (PP PP*))
    (Adj* -> () (Adj Adj*))
    (PP -> (Prep noun-phrase))
    (Prep -> to in by with on)
    (Adj -> big little blue green adiabatic)
    (Article -> the a)
    (Name -> Pat Kim Lee Terry Robin)
    (Noun -> man ball woman table)
    (Verb -> hit took saw liked)
    (Pronoun -> he she it these those that)))

(setf *grammar* *bigger-grammar*)

(generate 'sentence)

(defun generate-tree (phrase)
  "Generate a random sentence or phrase,
   with a complete parse tree."
  (cond ((listp phrase)
         (mapcar #'generate-tree phrase))
        ((rewrites phrase)
         (cons phrase
               (generate-tree (random-elt (rewrites phrase)))))
        (t (list phrase))))
   
(generate-tree 'sentence)

(defun generate-all (phrase)
  "Generate a list of all possible expansions of this phrase."
  (cond ((null phrase) (list nil))
        ((listp phrase)
         (combine-all (generate-all (first phrase))
                      (generate-all (rest phrase))))
        ((rewrites phrase)
         (mappend #'generate-all (rewrites phrase)))
        (t (list (list phrase)))))

(defun combine-all (xlist ylist)
  "Return a list of lists formed by appending a y to an x.
  E.g., (combine-all '((a) (b)) '((1) (2)))
  -> ((A 1) (B 1) (A 2) (B 2))"
  (mappend #'(lambda (y)
              (mapcar #'(lambda (x) (append x y)) xlist))
           ylist))

(generate-all 'sentence)
(setf *grammar* *bigger-grammar*)

; ex. 2.3
; Write a trivial grammar for some other language.
; This can be a natural language other than English,
; or perhaps a subset of a computer language.


(defparameter *russian-simple-grammar*
  '((sentence -> (Subject Predicate Complement))
    (Subject -> Человек Мужчина Женщина Мяч Машина)
    (Predicate -> ударил увидел полюбил взял)
    (Complement -> человека мужчину женщину мяч машину)))

(setf *grammar* *russian-simple-grammar*)

(generate 'sentence)

; ex. 2.4
; One of way of describing combine-all is that it calculates
; the cross-product of the function append on the argument
; lists. Write the higher-order function cross-product, and
; define combine-all in terms of it.
; The moral is to make your code as general as possible,
; because you never know you may want to do with it next.

(defun cross-product (fn xlist ylist)
  (mappend #'(lambda (y)
              (mapcar #'(lambda (x) (funcall fn x y)) xlist))
           ylist))

(defun combine-all2 (xlist ylist)
  (cross-product #'append xlist ylist))

(defun combine-all (xlist ylist)
  "Return a list of lists formed by appending a y to an x.
  E.g., (combine-all '((a) (b)) '((1) (2)))
  -> ((A 1) (B 1) (A 2) (B 2))"
  (mappend #'(lambda (y)
              (mapcar #'(lambda (x) (append x y)) xlist))
           ylist))

(trace combine-all)
(combine-all '((a) (b)) '((1) (2)))
(combine-all2 '((a) (b)) '((1) (2)))

(defun mappend (fn the-list)
  "Apply fn to each element of list and append the results."
  (apply #'append (mapcar fn the-list)))

(defun square (x) (* x x))
; mapcar aka map
(mapcar (lambda (x) (* x x)) '(1 2 3))
(mapcar #'square '(1 2 3))
;append
(append '(1 2 3) '(4 5 6) '() '(7 8 9))
;mappend
(defun self-and-double (x) (list x (+ x x)))
(mappend #'self-and-double '(5 6 7))

(defun combine-all (xlist ylist)
  "Return a list of lists formed by appending a y to an x.
  E.g., (combine-all '((a) (b)) '((1) (2)))
  -> ((A 1) (B 1) (A 2) (B 2))"
  (mappend #'(lambda (y)
              (mapcar #'(lambda (x) (append x y)) xlist))
           ylist))
; try to trace this
