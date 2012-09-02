;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname factorial) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ())))
(define (factorial n)
  (if (= n 1)
      1
      (* n 
         (factorial (- n 1))
                )))

;(factorial 5)

(define (factorial-line n)
  (factorial-iter 1 1 n)
  )
  (define (factorial-iter product counter max-count)
    (if (> counter max-count)
        product
        (factorial-iter (* counter product)
                        (+ counter 1)                        
                        max-count)))
  
 
(factorial-line 5)