;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname |1.11|) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ())))
(define (function-1-11 n)
  (if (< n 3)
      n
      (+ (function-1-11 (- n 1))
         (* 2 (function-1-11 (- n 2)))
         (* 3 (function-1-11 (- n 3))))))

(function-1-11 4)
(function-1-11 5)
(function-1-11 10)