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

# For cases below, "xxxx" represents "0.xxxx":
# oxxxx original threshold
# dxxxx damping 
# Use o1.0 if needed.

# b n		Make n new bias
# x n		Make n new axons

# todo: h scale-name word word
