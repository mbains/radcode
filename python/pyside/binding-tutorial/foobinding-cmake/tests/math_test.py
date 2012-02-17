#!/usr/bin/env python
# -*- coding: utf-8 -*-

'''Test cases for foo bindings module.'''

import unittest
import foo

class MathTest(unittest.TestCase):

    def testMath(self):
        '''Test case for Math class from foo module.'''
        val = 5
        math = foo.Math()
        self.assertEqual(math.squared(5), 5 * 5)

if __name__ == '__main__':
    unittest.main()

