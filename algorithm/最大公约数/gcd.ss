;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname gcd) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ())))
;(define (remainder x y)
         ;(% x y))
(define (GCD a b)  
  (if (= (remainder a b) 0)
      b
      (GCD b (remainder a b))))

(GCD 12 3)