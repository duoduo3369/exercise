;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-advanced-reader.ss" "lang")((modname fast_fibonacci) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #t #t none #f ())))
;T(pq):(a,b)=>(bq+aq+ap, bp+aq)
;T(pq):(bq+aq+ap, bp+aq)=>((bp+aq)q + (bq+aq+ap)q + (bq+aq+ap)p,
;                          (bp+aq)p + (bq+aq+ap)q)
;      => (2bpq+2aqq+bqq+2apq+app, bpp+2apq+bqq+aqq)
;      => (b(2pq+qq)+a(2pq+qq)+a(qq+pp), b(qq+pp)+a(2pq+qq))
;q' = 2pq+qq
;p' = qq+pp
;
(define (fib n)
  (fib-iter 1 0 0 1 n))

(define (fib-iter a b p q count)
  (cond ((= count 0) b)
        ((even? count) 
         (fib-iter a
                   b
                   (+ (* p p) (* q q))
                   (+ (* 2 p q ) (* q q))
                   (/ count 2)))
        (else (fib-iter (+ (* b q) (* a q) (* a p))
                        (+ (* b p) (* a q))
                        p
                        q
                        (- count 1)))))