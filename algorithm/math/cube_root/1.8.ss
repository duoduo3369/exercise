;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname |1.8|) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ())))


(define (cube-root-iter guess x)
 (if (good-enough? guess x)
  	 guess
	 (cube-root-iter (improve guess x)
	     	   x)))

(define (improve guess x)
   (/ (+ (/ x 
           (square guess)) 
        (* 2 guess))
     3)
  )

(define (average x y)
 (/ (+ x y) 2))

(define (good-enough? guess x)
 (< (abs (- (cube guess)  x)) 0.0001))


(define (cube x)
  (* x x x))
(define (square x)
  (* x x))

(define (cube-root n)
  (cube-root-iter 1.0 n))

(cube-root 8)