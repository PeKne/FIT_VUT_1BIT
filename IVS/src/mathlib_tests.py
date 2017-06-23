"""@package mathlibtests
This module contains tests for the mathlib module.
"""

import unittest
import random

import mathlib
import math

class TestNaturalLogarithm(unittest.TestCase):
    """Tests for the natural logarithm function."""

    def test_zero(self):
        """Tests whether a not-a-number is returned when passing 0.0 as an argument."""
        self.assertTrue(math.isnan(mathlib.log(0.0)))

    def test_lessThanZero(self):
        """Tests whether a not-a-number is returned when passing an argument
        that is less than zero.
        """
        self.assertTrue(math.isnan(mathlib.log(-1.0)))

    def test_one(self):
        """Tests whether 0.0 is returned when passing 1.0 as an argument."""
        self.assertEqual(mathlib.log(1.0), 0.0)

    def test_eulersNumber(self):
        """Tests whether 1.0 is returned when passing Eulers's number as an argument."""
        self.assertEqual(mathlib.log(math.e), 1.0)

    def test_arbitraryArgument(self):
        """Tests if mathlib.log returns the same value as math.log for an arbitrary argument."""
        # random.random() returns a value from the interval [0.0, 1.0).
        # 0.0 is an ilagal argument for the natural logarithm.
        # That is why 1.0 is added.
        randomFloat = random.random() + 1.0
        self.assertAlmostEqual(mathlib.log(randomFloat), math.log(randomFloat))

    def test_positiveInfinity(self): # NOTE: negative infinity should be covered by test_lessThanZero.
        """Tests whether a positive infinity is returned when passing a positive infinity as an argument."""
        self.assertEqual(mathlib.log(math.inf), math.inf)

class TestIntegerPower(unittest.TestCase) :
    """Tests of function pow which power first arg. with second arg. and returns result"""
    def rand_int(self):
        return random.randint(0, 2147483647)

    def setUp(self):
        self.randINT = self.rand_int()

    def test_ZeroPower(self):
        """Tests power of zero"""
        self.assertEqual(mathlib.pow(0,0), 1)
        self.assertEqual(mathlib.pow(1,0), 1)
        self.assertEqual(mathlib.pow(2,0), 1)
        self.assertEqual(mathlib.pow(3,0), 1)
        self.assertEqual(mathlib.pow(6,0), 1)
        self.assertEqual(mathlib.pow(255,0), 1)
        self.assertEqual(mathlib.pow(12000,0), 1)
        self.assertEqual(mathlib.pow(self.randINT,0),1)

    def test_OnePower(self):
        """Tests power of one"""
        self.assertEqual(mathlib.pow(0,1), 0)
        self.assertEqual(mathlib.pow(1,1), 1)
        self.assertEqual(mathlib.pow(4,1), 4)
        self.assertEqual(mathlib.pow(505,1), 505)
        self.assertEqual(mathlib.pow(22,1), 22)
        self.assertEqual(mathlib.pow(480,1), 480)
        self.assertEqual(mathlib.pow(244,1), 244)
        self.assertEqual(mathlib.pow(self.randINT,1), self.randINT)

    def test_TwoPower(self) :
        """Tests power of two"""
        self.assertEqual(mathlib.pow(0, 2), 0)
        self.assertEqual(mathlib.pow(1, 2), 1)
        self.assertEqual(mathlib.pow(2, 2), 4)
        self.assertEqual(mathlib.pow(15, 2), 225)
        self.assertEqual(mathlib.pow(24, 2), 576)
        self.assertEqual(mathlib.pow(self.randINT, 2), self.randINT*self.randINT)

    def test_RandPower(self) :
        """Tests power of random number"""
        self.assertEqual(mathlib.pow(self.randINT,0),1)
        self.assertEqual(mathlib.pow(self.randINT,1), self.randINT)
        self.assertEqual(mathlib.pow(self.randINT, 2), self.randINT*self.randINT)
        self.assertEqual(mathlib.pow(0, self.randINT), 0)
        self.assertEqual(mathlib.pow(1, self.randINT), 1)

    def test_OtherValues(self) :
        """Tests power function of other values"""
        self.assertEqual(mathlib.pow(3, 4), 81)
        self.assertEqual(mathlib.pow(9, 9), 387420489)
        self.assertEqual(mathlib.pow(18, 7), 612220032)
        self.assertEqual(mathlib.pow(247, 3), 15069223)
        self.assertEqual(mathlib.pow(13, 5), 371293)
        self.assertEqual(mathlib.pow(11, 7), 19487171)
        self.assertEqual(mathlib.pow(8, 7), 2097152)
        self.assertEqual(mathlib.pow(33, 3), 35937)
        self.assertEqual(mathlib.pow(19, 5), 2476099)
        self.assertEqual(mathlib.pow(13, 6), 4826809)
        self.assertEqual(mathlib.pow(12, 8), 429981696)
        self.assertEqual(mathlib.pow(11, 3), 1331)
        self.assertEqual(mathlib.pow(22, 6), 113379904)
        self.assertEqual(mathlib.pow(42, 2), 1764)
        self.assertEqual(mathlib.pow(17, 4), 83521)

class TestBasicOperations(unittest.TestCase) :
    """Tests of functions: mathlib.sum, mathlib.sub, mathlib.mul, mathlib.div"""
    def rand_int(self):
        return random.randint(-2147483647, 2147483648)

    def rand_float(self):
        x = random.uniform(-1024.512, 2048.256)
        while x.is_integer():
            x = random.uniform(-1024.512, 2048.256)
        return x

    def setUp(self):
        self.randINT1 = self.rand_int()
        self.randINT2 = self.rand_int()
        self.randFLOAT1 = self.rand_float()
        self.randFLOAT2 = self.rand_float()

    def test_Sum(self):
        """Tests mathlib.sum"""
        self.assertEqual(mathlib.sum(0,0), 0)
        self.assertEqual(mathlib.sum(1,6), 7)
        self.assertEqual(mathlib.sum(0,4), 4)
        self.assertEqual(mathlib.sum(8,0), 8)
        self.assertEqual(mathlib.sum(-5,5), 0)
        self.assertEqual(mathlib.sum(-5,8), 3)
        self.assertEqual(mathlib.sum(-3,5), 2)
        self.assertEqual(mathlib.sum(-6,-9), -15)
        self.assertEqual(mathlib.sum(-7,0), -7)
        self.assertEqual(mathlib.sum(0,-7), -7)
        self.assertEqual(mathlib.sum(self.randFLOAT1, self.randFLOAT2), self.randFLOAT1+self.randFLOAT2)
        self.assertEqual(mathlib.sum(self.randINT1, self.randINT2), self.randINT1+self.randINT2)

    def test_Sub(self):
        """Tests mathlib.sub"""
        self.assertEqual(mathlib.sub(0,0), 0)
        self.assertEqual(mathlib.sub(1,6), -5)
        self.assertEqual(mathlib.sub(0,4), -4)
        self.assertEqual(mathlib.sub(8,0), 8)
        self.assertEqual(mathlib.sub(8,5), 3)
        self.assertEqual(mathlib.sub(-5,5), -10)
        self.assertEqual(mathlib.sub(-5,8), -13)
        self.assertEqual(mathlib.sub(-3,5), -8)
        self.assertEqual(mathlib.sub(-6,-9), 3)
        self.assertEqual(mathlib.sub(-7,0), -7)
        self.assertEqual(mathlib.sub(0,-7), 7)
        self.assertEqual(mathlib.sub(self.randFLOAT1, self.randFLOAT2), self.randFLOAT1-self.randFLOAT2)
        self.assertEqual(mathlib.sub(self.randINT1, self.randINT2), self.randINT1-self.randINT2)

    def test_Mul(self):
        """Tests mathlib.mul"""
        self.assertEqual(mathlib.mul(0,0), 0)
        self.assertEqual(mathlib.mul(1,6), 6)
        self.assertEqual(mathlib.mul(0,4), 0)
        self.assertEqual(mathlib.mul(8,0), 0)
        self.assertEqual(mathlib.mul(8,5), 40)
        self.assertEqual(mathlib.mul(-5,5), -25)
        self.assertEqual(mathlib.mul(3,-5), -15)
        self.assertEqual(mathlib.mul(-6,-9), 54)
        self.assertEqual(mathlib.mul(-7,0), 0)
        self.assertEqual(mathlib.mul(0,-7), 0)
        self.assertEqual(mathlib.mul(self.randFLOAT1, self.randFLOAT2), self.randFLOAT1*self.randFLOAT2)
        self.assertEqual(mathlib.mul(self.randINT1, self.randINT2), self.randINT1*self.randINT2)

    def test_Div(self):
        """Tests mathlib.div"""
        self.assertTrue(math.isnan(mathlib.div(0,0)))
        self.assertEqual(mathlib.div(1,5), 0.2)
        self.assertEqual(mathlib.div(0,4), 0)
        self.assertTrue(math.isnan(mathlib.div(8,0)))
        self.assertEqual(mathlib.div(8,5), 1.6)
        self.assertEqual(mathlib.div(-5,5), -1)
        self.assertEqual(mathlib.div(4,-5), -0.8)
        self.assertEqual(mathlib.div(-4,-2), 2)
        self.assertTrue(math.isnan(mathlib.div(-7,0)))
        self.assertEqual(mathlib.div(0,-7), 0)
        self.assertEqual(mathlib.div(self.randFLOAT1, self.randFLOAT2), self.randFLOAT1/self.randFLOAT2)
        self.assertEqual(mathlib.div(self.randINT1, self.randINT2), self.randINT1/self.randINT2)

class TestFactorial(unittest.TestCase) :
    """Tests of mathlib.factorial"""
    def rand_positive_int(self):
        return random.randint(0, 50)

    def rand_float(self):
        x = random.uniform(-1024.512, 2048.256)
        while x.is_integer():
            x = random.uniform(-1024.512, 2048.256)
        return x

    def test_Factorial(self):
        """Tests mathlib.factorial"""
        randPositiveINT = self.rand_positive_int()
        randFLOAT1 = self.rand_float()
        self.assertEqual(mathlib.factorial(0), 1)
        self.assertEqual(mathlib.factorial(4), 24)
        self.assertTrue(math.isnan(mathlib.factorial(-5)))
        self.assertTrue(math.isnan(mathlib.factorial(4.532)))
        self.assertTrue(math.isnan(mathlib.factorial(randFLOAT1))) # QUESTION: is this correct? randFLOAT1 could be 2 for example. FIXED
        self.assertEqual(mathlib.factorial(randPositiveINT), math.factorial(randPositiveINT))

class TestRoot(unittest.TestCase) :
    """Tests of mathlib.root"""
    def rand_int(self):
        return random.randint(-2147483647, 2147483648)

    def rand_positive_int(self):
        return random.randint(0, 2147483648) 

    def rand_float(self):
        x = random.uniform(-1024.512, 2048.256)
        while x.is_integer():
            x = random.uniform(-1024.512, 2048.256)
        return x

    def test_Root(self):
        """Tests mathlib.root"""
        randINT1 = self.rand_int()
        randFLOAT1 = self.rand_float()
        randPositiveINT = self.rand_positive_int()
        #mathlib.root(x, n) x is number, n is mathlib.root order
        self.assertTrue(math.isnan(mathlib.root(randINT1, 0)))
        self.assertEqual(mathlib.root(randINT1, 1), randINT1)
        self.assertTrue(math.isnan(mathlib.root(0, -randPositiveINT)))
        self.assertEqual(mathlib.root(0, randPositiveINT), 0)
        self.assertEqual(mathlib.root(4, -2), 0.5)
        self.assertTrue(math.isnan(mathlib.root(-4, 2)))
        self.assertEqual(mathlib.root(4, 2), 2)
        self.assertEqual(mathlib.root(27, 3), 3)
        self.assertEqual(mathlib.root(-27, 3), -3)
        self.assertEqual(mathlib.root(1, 2), 1)
        self.assertTrue(math.isclose(mathlib.root(80, 5), 2.402248868))

if __name__ == '__main__':
    unittest.main()
