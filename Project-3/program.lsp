;;;; Gregory Mann
;;;; Fall 2017
;;;; COSC 341
;;;; Project 3

;; Function 1
;; Takes a list L and returns the number of lists L contains.
(defun f1 (L)
  (cond ((null (car L)) 0)
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
  (cond ((listp (car L)) (car L))
	(t (f6 (cdr L)))))

;; Function 7
;; Takes a list L and returns a list contining the lists winthin L.
(defun f7 (L)
  (cond ((null (car L)) nil)
	((listp (car L)) (cons
			  (car L)
			  (f7 (cdr L))))
	(t (f7 (cdr L)))))

;; Function 8
;; Takes a list of integers L and returns the product of every integer in L and the lists within L.
(defun f8 (L)
  (cond ((null (car L)) 1)
	((listp (car L)) (* (f8 (car L))
			    (f8 (cdr L))))
	((numberp (car L)) (* (car L)
			      (f8 (cdr L))))
	(t (f8 (cdr L)))))

;; Function 9
;; Takes a symbol x and a list L. Returns T if x is in L and nil otherwise.
(defun my-working-version-of-member (x L)
  (cond ((null L) nil)
	((equal x (car L)) t)
	(t (my-working-version-of-member x (cdr L)))))

;; Takes a list L and reutrns a list contining no duplicats.
(defun f9 (L)
  (cond ((null (car L)) nil)
	((my-working-version-of-member (car L) (cdr L)) (f9 (cdr L)))
	(t (cons (car L) (f9 (cdr L))))))

;; Funciton 10
;; Takes two lists L and M and reutrns a list contining the intersecting elements within L and M.
(defun f10 (L M)
  (cond ((null L) nil)
	((my-working-version-of-member (car L) M) (cons (car L) (f10 (cdr L) M)))
	(t (f10 (cdr L) M))))

;; Function 11
;; TODO: We can't use the built in mod function :C
(setq count -1)
(defun f11 (N)
  (cond	((equal count -1) (setq count (- N 1)) (f11 N))
	((equal 1 count) (setq count -1) t)
	((equal 0 (mod N count)) (setq count -1) nil)
	(t (setq count (- count 1)) (f11 N))))

;; Function 12
(defun insert (x L)
  (cond ((null L) (list x))
	((< x (car L)) (cons x L))
	(t (cons (car L) (insert x (cdr L))))))

(defun f12 (L)
  (cond ((null L) nil)
	(t (insert (car L) (f12 (cdr L))))))
