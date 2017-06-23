"""Root"""
import math
import cmath
##
#@brief root calculates any root
#@param n number which is index of root
#@param x number which is radicand
#@return result
def root(n, x):
    if n == 0:
         return math.nan
    if x == 0 and n < 0:
        return math.nan
    if x < 0 and n % 2 == 0:
        return math.nan
    if x < 0:
        result = cmath.exp((1/n) * cmath.log(x) )
        r = math.sqrt(round(math.pow(result.real, 2.0) + math.pow(result.imag, 2.0)))
        return -round(r)
    else:
        return math.pow(x, 1/n)
