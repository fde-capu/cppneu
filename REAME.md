# String : first string must be the name
# All rest is optional. Check header.h for defaults.
# string string string ... : verbal scale
# min:max:unit : custom measurable scale

# Id:
# ixxxx  id (xxxx as integer)
# same as nxxxx, or bxxxx for bias.

# Types:
# n|v|a|m|p|b|q
#			n:neuron
#			v:vital
#			a:action
#			m:measure
#			p:physical
#			b:bias
#			q:quiet

# Expressors:
# c|o|s|t
#			c:current
#			o:original threshold
#			s:short threshold
#			t:threshold

# About uF notation:
# For cases >= 0.0, < 1.0, "xxxx" represents "0.xxxx":
# For 1.0, use "1.0"

# oxxxx original threshold
# dxxxx damping 

# b n		Make n new bias
# x n		Make n new axons

# Axons:
# x in-val-out
#			in:		UID or Name
#			val:	uF notation multiplier
#			out:	UID or Name

# todo: h scale-name word word
