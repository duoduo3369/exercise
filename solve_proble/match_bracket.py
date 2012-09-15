
# coding=UTF8
import Queue
Stack = Queue.LifoQueue
bracket = {"{":"}",
           "[":"]",
           "(":")",
           }
def match_bracket(array):
    stack = Stack()
    push = stack.put
    pop = stack.get
    def is_match_left_bracket(stack,element):
        if stack.empty():
            return False
        else:
            last_bracket = stack.get()
            if bracket[last_bracket] == element:
                return True
            else:
                return False
            
    for element in array:
        if element in bracket:
            # 元素是括号的左边部分时，进栈
            push(element)
        else:
            if is_match_left_bracket(stack,element):
                continue
            else:
                return False
            
    if not stack.empty():
            return False
    return True

import unittest

class TestMatchBracket(unittest.TestCase):
    def test_match_bracket_1(self):
        self.assertTrue(match_bracket(list("")))
    def test_match_bracket_2(self):
        self.assertTrue(match_bracket(list("{}[]()")))
    def test_match_bracket_3(self):
        self.assertTrue(match_bracket(list("{[]}()")))
    def test_match_bracket_4(self):
        self.assertTrue(match_bracket(list("[({[[]]})]")))
    def test_match_bracket_5(self):
        self.assertTrue(match_bracket(list("{}")))
    def test_match_bracket_6(self):
        self.assertFalse(match_bracket(list("{")))
    def test_match_bracket_7(self):
        self.assertFalse(match_bracket(list("]")))
    def test_match_bracket_8(self):
        self.assertFalse(match_bracket(list("{]")))
    def test_match_bracket_9(self):
        self.assertFalse(match_bracket(list("{{}")))
    def test_match_bracket_10(self):
        self.assertFalse(match_bracket(list("{[)]}")))
        
def test():
    unittest.main()
    
