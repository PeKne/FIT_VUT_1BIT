"""Factorial"""
import math
##
#@brief factorial calculates factorial of number (must be integer)
#@param x number from which its counted
#@return result
def factorial(x):
	helpX = x + 0.0
	if not helpX.is_integer():
		return math.nan
	elif x < 0:
		return math.nan
	elif x == 0:
		return 1
	else:
		return x * factorial(x-1)
