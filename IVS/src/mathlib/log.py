"""Natural logarithm"""
import math
##
#@brief log calculates natural logarithm
#@param x number from which its counted
#@return result
def log(x):
    n = 100
    if x <= 0.0:
        return math.nan
    elif x == 1.0:
        return 0.0
    elif x == math.e:
        return 1.0
    elif x == math.inf:
        return math.inf

    summ = 0
    if x < 1:
        multiple = 1-x
        x = multiple
        for i in range(n):
            summ += -x / (i+1)
            x *= multiple
    else:
        multiple = (x-1) / x
        x = multiple
        for i in range(n):
            summ += x / (i+1)
            x *= multiple
    return summ
