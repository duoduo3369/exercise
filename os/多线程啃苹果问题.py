import threading
import time
import logging
import random

logging.basicConfig(level=logging.DEBUG,
                    format='(%(threadName)-10s) %(message)s',
                    )

mutex = threading.RLock()


class Counter(object):
    def __init__(self, start=0):
        self.value = start        
    def increment(self):        
        self.value = self.value + 1    
        logging.debug('Counter: %d', plate.counter.value)
    def decrement(self):        
        self.value = self.value - 1
        logging.debug('Counter: %d', plate.counter.value)
                    
def father(plate):
    while 1:
        mutex.acquire()
        if plate.counter.value is 0:            
            plate.counter.increment()
            plate.apple_number.increment()
            print 'father: put an apple'
        mutex.release()
        time.sleep(5*random.random())    

def mother(plate):
    while 1:
        mutex.acquire()
        if plate.counter.value is 0:            
            plate.counter.increment()
            plate.orange_number.increment()
            print 'mother: put an orange'
        mutex.release()
        time.sleep(5*random.random())    

def son(plate):
    while 1:
        mutex.acquire()
        if plate.counter.value is 1 and plate.apple_number.value is 1:            
            plate.counter.decrement()
            plate.apple_number.decrement()
            print 'son: eat an apple'
        mutex.release()
        time.sleep(5*random.random())    

def daughter(plate):
    while 1:
        mutex.acquire()
        if plate.counter.value is 1 and plate.orange_number.value is 1:            
            plate.counter.decrement()
            plate.orange_number.decrement()
            print 'daughter: eat an orange'
        mutex.release()
        time.sleep(5*random.random())   
class Plate(object):
    def __init__(self,):
        self.counter = Counter()
        self.apple_number = Counter()
        self.orange_number = Counter() 

if __name__ == '__main__':
    plate = Plate()
    father_thread = threading.Thread(name='father',target=father, args=(plate,))
    mother_thread = threading.Thread(name='mother',target=mother, args=(plate,))
    son_thread = threading.Thread(name='son',target=son, args=(plate,))
    daughter_thread = threading.Thread(name='daughter',target=daughter, args=(plate,))
    thread_list = [father_thread,mother_thread,son_thread,daughter_thread]

    for t in thread_list:
        t.start()
    
