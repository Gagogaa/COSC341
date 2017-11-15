;;;; Gregory Mann
;;;; Fall 2017
;;;; COSC 341
;;;; Project 3

;; Function 1
;; Takes a list L and returns the number of lists L contains.
(defun f1 (L)
  (cond ((null (car L)) 0) ; '()' has zero elements and '()' == 'nil'
                           ; so 'nil' has zero elements.
	((listp (car L)) (+ 1 (f1 (cdr L))))
	(t (+ 0 (f1 (cdr L))))))

;; Funciton 2
;; Takes a list L and returns T if it contains an atom and nil otherwise.
(defun f2 (L)
    (cond ((null (car L)) nil)
	  ((atom (car L)) t)
	  (t (f2 (cdr L)))))

;; Funciton 3
;; Takes a list L and returns a list containing only the odd numbers in L.
(defun f3 (L)
  (cond ((null (car L)) nil)
	((oddp (car L)) (cons
			 (car L)
			 (f3 (cdr L))))
	(t (f3 (cdr L)))))

;; Funciton 4
;; Takes a list L and returns the last element in L.
(defun f4 (L)
  (cond ((null (cadr L)) (car L))
	(t (f4 (cdr L)))))

;; Funciton 5
;; Takes a list L and returns the inverse of the list.
(defun f5 (L)
  (cond ((null (car L)) nil)
	(t (append (f5 (cdr L))
		   (list (car L))))))

;; Function 6
;; Takes a list L and returns the first list within L.
(defun f6 (L)
  ;; No default needed because '(listp nil)' => 'T' so nil will be returned.
  (cond ((listp (car L)) (car L))
	(t (f6 (cdr L)))))

;; Function 7
;; Takes a list L and returns a list contining the lists winthin L.
(defun f7 (L)
  (cond ((null (car L)) nil)
	;; If '(car L)' is a list then concatinate it with the lists in '(cdr L)'
	((listp (car L)) (cons
			  (car L)
			  (f7 (cdr L))))
	(t (f7 (cdr L)))))

;; Function 8
;; Takes a list of integers L and returns the product of every integer
;; in L and the lists within L.
(defun f8 (L)
  (cond ((null (car L)) 1)
	;; If '(car L)' is a list multiply the product of every element
	;; in that list and the product of the lists in '(cdr L)'
	((listp (car L)) (* (f8 (car L))
			    (f8 (cdr L))))
	((numberp (car L)) (* (car L)
			      (f8 (cdr L))))
	(t (f8 (cdr L)))))

;; Function 9
;; Takes a symbol x and a list L. Returns T if x is in L and nil otherwise.
(defun my-member (x L)
  (cond ((null L) nil)
	((equal x (car L)) t)
	(t (my-member x (cdr L)))))

;; Takes a list L and reutrns a list contining no duplicats.
(defun f9 (L)
  (cond ((null (car L)) nil)
	((my-member (car L) (cdr L)) (f9 (cdr L)))
	(t (cons (car L) (f9 (cdr L))))))

;; Funciton 10
;; Takes two lists L and M and reutrns a list contining the
;; intersecting elements within L and M.
(defun f10 (L M)
  (cond ((null L) nil)
	;; If '(car L)' is a member of M concatinate '(car L)'
	;; with the intersection of '(cdr L)' and M.
	((my-member (car L) M) (cons (car L) (f10 (cdr L) M)))
	(t (f10 (cdr L) M))))

;; Function 11
;; Retruns T if x is prime and nil if not. n is a helper variable.
(defun primep (x n)
  (cond ((equal n 1) t)
	((equal (mod x n) 0) nil)
	(t (primep x (- n 1)))))

;; Takes a number N and returns T if the number if prime and false otherwise.
(defun f11 (N)
  (primep N (- N 1)))

;; Function 12
;; Takes a number x and a list of numbers L and inserts x into L in
;; acending order.
(defun insert (x L)
  (cond ((null L) (list x)) ; If the list is empty just return the
                            ; list containing the one element.
	((< x (car L)) (cons x L))
	(t (cons (car L) (insert x (cdr L))))))

;; Takes a list of integers L and returns the sorted list L.
(defun f12 (L)
  (cond ((null L) nil)
	(t (insert (car L) (f12 (cdr L))))))
