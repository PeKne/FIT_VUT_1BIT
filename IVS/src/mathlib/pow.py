"""Power"""
##
#@brief Calculates power expresions
#@param x base number
#@param n exponent
#@return result
def pow(x, n):
	if n == 0:
		return 1
	if n == 1:
		return x
	else:
		return x**n
