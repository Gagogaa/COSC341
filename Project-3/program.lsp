;;;; Gregory Mann
;;;; Fall 2017
;;;; COSC 341
;;;; Project 3

;; Function 1
(defun f1 (L)
  (cond ((null (car L)) 0)
	((listp (car L)) (+ 1 (f1 (cdr L))))
	(t (+ 0 (f1 (cdr L))))))

;; Funciton 2
(defun f2 (L)
    (cond ((null (car L)) nil)
	  ((atom (car L)) t)
	  (t (f2 (cdr L)))))

;; Funciton 3
(defun f3 (L)
  (cond ((null (car L)) nil)
	((oddp (car L)) (append
			 (list (car L))
			 (f3 (cdr L))))
	(t (f3 (cdr L)))))

;; Funciton 4
(defun f4 (L)
  (cond ((null (cadr L)) (car L))
	(t (f4 (cdr L)))))

;; Funciton 5
(defun f5 (L)
  (cond ((null (car L)) nil)
	(t (append (f5 (cdr L))
		   (list (car L))))))

;; Function 6
(defun f6 (L)
  (cond ((listp (car L)) (car L))
	(t (f6 (cdr L)))))

;; Function 7
(defun f7 (L)
  (cond ((null (car L)) nil)
	((listp (car L)) (append
			  (list (car L))
			  (f7 (cdr L))))
	(t (f7 (cdr L)))))

;; Function 8
(defun f8 (L)
  (cond ((null (car L)) 1)
	((listp (car L)) (* (f8 (car L))
			    (f8 (cdr L))))
	((numberp (car L)) (* (car L)
			      (f8 (cdr L))))
	(t (f8 (cdr L)))))

;; Function 9
;; TODO: can I make my own working member function?
(defun f9 (L)
  (cond ((null (car L)) nil)
	((member (car L) (cdr L)) (f9 (cdr L)))
	(t (append (list (car L)) (f9 (cdr L))))))

;; Funciton 10
(defun f10 (L M)
  (cond ((null L) nil)
	((member (car L) M) (f10 (cdr L) M))
	(t (f10 (cdr L) M))))

;; Function 11
(defun f11 (N)
  (cond ((equal N 1) t)



	))
