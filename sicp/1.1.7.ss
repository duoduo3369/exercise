;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname 1.1.7) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ())))
;; 牛顿法求平方根


(define (sqrt-it guess x)
 (if (good-enough? guess x)
  	 guess
	 (sqrt-it (improve guess x)
	     	   x)))

(define (improve guess x)
 	(average guess (/ x guess)))

(define (average x y)
 (/ (+ x y) 2))

(define (good-enough? guess x)
 (< (abs (- (square guess) x)) 0.0001))

(define (square x)
  (* x x))

(define (nowton-sqrt n)
  (sqrt-it 1.0 n))

(nowton-sqrt 8)