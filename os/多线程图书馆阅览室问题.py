# coding=utf8
import time
import logging
import random
import threading

logging.basicConfig(level=logging.DEBUG,
                    format='(%(threadName)-10s) %(message)s',
                    )

mutex = threading.RLock()


class Counter(object):
    def __init__(self, start=0):
        self.value = start        
    def increment(self):        
        self.value = self.value + 1    
        logging.debug('Counter: %d', counter.value)
    def decrement(self):        
        self.value = self.value - 1
        logging.debug('Counter: %d', counter.value)

def reader_in(counter):
    while 1:       
        if counter.value > 0:
            mutex.acquire()
            counter.decrement()
            mutex.release()
        time.sleep(random.random())

def reader_out(counter,seats=100):
    while 1:
        if counter.value < seats:
            mutex.acquire()
            counter.increment()
            mutex.release()
        time.sleep(random.random())

if __name__ == '__main__':
    seats = 50
    counter = Counter(start = seats)    
    reader_in_thread_1 = threading.Thread(name=u'reader_in_1',
                                        target=reader_in, args=(counter,))
    reader_in_thread_2 = threading.Thread(name=u'reader_in_2',
                                        target=reader_in, args=(counter,))
    reader_out_thread_1 = threading.Thread(name=u'reader_out',
                                         target=reader_out, args=(counter,seats))
    reader_out_thread_2 = threading.Thread(name=u'reader_out',
                                         target=reader_out, args=(counter,seats))
    
    reader_in_thread_1.start()
    reader_in_thread_2.start()
    reader_out_thread_1.start()
    reader_out_thread_2.start()
