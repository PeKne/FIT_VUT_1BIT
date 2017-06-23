"""Basic math operations - division, multiplication, summation, subtraction"""
import math
##
#@brief sum calculates sum of two numbers
#@param x first number to be added
#@param n second number to be added
#@return result
def sum(x, n):
    return x+n
##
#@brief sub calculates the difference of two numbers
#@param x first number to be deducted
#@param n second number to be deducted
#@return result
def sub(x, n):
    return x-n
##
#@brief mul calculates multiple of two numbers
#@param x first number to be multiplied
#@param n second number to be multiplied
#@return result
def mul(x, n):
    return x*n
##
#@brief div calculates portion of two numbers
#@param x number to be divided
#@param n number that is the divisor
#@return result
def div(x, n):
	if n==0:
		return math.nan
	else:
		return x/n
