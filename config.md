# String : first string must be the name
# All rest is optional. Check header.h for defaults.
# string string string ... : verbal scale
# min:max:unit : custom measurable scale
# ixxxx id (xxxx as integer)

# Types:
# v|a|m|p|b
#			v:vital
#			a:action
#			m:measure
#			p:physical
#			b:bias

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

# i42 Heart o111 d222 v s	0:260:bpm Frozen Slow Normal Peaced Accelerated Fast Hyper

# n Nose o01234567 p o Short Medium Long d1.0
# n Breath v t Empty Neutral Full 0.8
# n Eyes s Closed Normal "Wide Open" Popped d0.4
# n Humor Crappy Bad Medium Ok Good Enthusiastic Incredible
# n Tired s
# n Drop a

n a Sleep

# i0 b top m o o0

# i2 CustomBiasName o1.0 b o Clear Cloudy Rain Storm 0:100:umity

n 2
b 3

 x 3-555-0
# x 5
